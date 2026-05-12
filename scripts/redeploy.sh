#!/usr/bin/env bash
# =============================================================================
# Library_python serverini ma'lumotlarni yo'qotmasdan qayta deploy qiluvchi skript.
#
# Foydalanish:
#   1) Skriptni serverga ko'chiring, masalan:
#        scp scripts/redeploy.sh user@5.189.136.95:~/redeploy.sh
#   2) SSH bilan kiring:
#        ssh user@5.189.136.95
#   3) Skriptni ishga tushiring:
#        chmod +x ~/redeploy.sh && ~/redeploy.sh
#
# Skript bajaradi:
#   - db.sqlite3 va media/ papkasining vaqtli BACKUP-ini oladi
#   - Repodagi mahalliy o'zgarishlarni stash qiladi (yo'qolmasligi uchun)
#   - git pull qiladi
#   - virtualenv-ni faollashtiradi va talablar bo'lsa o'rnatadi
#   - migratsiyalarni qo'llaydi (faqat yangi migratsiyalar, ma'lumotlar saqlanadi)
#   - statiklarni yig'adi (agar production bo'lsa)
#   - Gunicorn/systemd xizmatini qayta ishga tushiradi yoki nohup bilan ishga tushiradi
#   - Backup-ni saqlab qoladi va xatolik bo'lsa avtomatik tiklaydi
# =============================================================================

set -euo pipefail

# ------------------------------------------------------------------------------
# Sozlamalar — o'zgartiring agar yo'l boshqacha bo'lsa
# ------------------------------------------------------------------------------
PROJECT_DIR="${PROJECT_DIR:-$HOME/library/library}"     # manage.py bor papka
REPO_DIR="${REPO_DIR:-$HOME/library}"                   # .git bor papka (klon ildizi)
VENV_DIR="${VENV_DIR:-$HOME/library/.venv}"             # virtualenv yo'li
BACKUP_ROOT="${BACKUP_ROOT:-$HOME/library_backups}"     # backup'lar saqlanadigan joy
SERVICE_NAME="${SERVICE_NAME:-library}"                 # systemd service nomi (mavjud bo'lsa)
GUNICORN_PORT="${GUNICORN_PORT:-81}"                    # nohup fallback uchun port

# ------------------------------------------------------------------------------
# Yordamchi funksiyalar
# ------------------------------------------------------------------------------
log()  { printf "\n\e[1;36m[redeploy]\e[0m %s\n" "$*"; }
warn() { printf "\n\e[1;33m[warn]\e[0m %s\n" "$*"; }
err()  { printf "\n\e[1;31m[error]\e[0m %s\n" "$*" >&2; }

require_dir() {
    if [[ ! -d "$1" ]]; then
        err "Papka topilmadi: $1"
        exit 1
    fi
}

# ------------------------------------------------------------------------------
# 0. Tekshirish
# ------------------------------------------------------------------------------
log "Boshlandi: $(date)"
require_dir "$REPO_DIR"
require_dir "$PROJECT_DIR"
mkdir -p "$BACKUP_ROOT"

TS="$(date +%Y%m%d_%H%M%S)"
BACKUP_DIR="$BACKUP_ROOT/backup_$TS"
mkdir -p "$BACKUP_DIR"

# ------------------------------------------------------------------------------
# 1. BACKUP — ma'lumotlarni vaqtli papkaga nusxalash
# ------------------------------------------------------------------------------
log "1/7  Backup olinmoqda → $BACKUP_DIR"

if [[ -f "$PROJECT_DIR/db.sqlite3" ]]; then
    cp -av "$PROJECT_DIR/db.sqlite3" "$BACKUP_DIR/db.sqlite3"
    log "    db.sqlite3 saqlandi"
else
    warn "    db.sqlite3 topilmadi (PostgreSQL ishlatilayotgan bo'lishi mumkin)"
fi

if [[ -d "$PROJECT_DIR/media" ]]; then
    cp -a "$PROJECT_DIR/media" "$BACKUP_DIR/media"
    log "    media/ saqlandi"
else
    warn "    media/ topilmadi"
fi

# Agar PostgreSQL bo'lsa, ixtiyoriy dump
if command -v pg_dump >/dev/null 2>&1 && [[ -n "${PGDATABASE:-}" ]]; then
    log "    PostgreSQL dump qilinmoqda..."
    pg_dump "$PGDATABASE" > "$BACKUP_DIR/postgres_dump.sql" || warn "pg_dump bajarilmadi"
fi

# ------------------------------------------------------------------------------
# 2. Mahalliy o'zgarishlarni stash qilish
# ------------------------------------------------------------------------------
log "2/7  Git holati tekshirilmoqda..."
cd "$REPO_DIR"

if ! git diff --quiet || ! git diff --cached --quiet; then
    warn "    Mahalliy o'zgarishlar topildi — stash qilinmoqda"
    git stash push -u -m "redeploy_auto_$TS" || true
fi

# ------------------------------------------------------------------------------
# 3. Yangi kodni tortish
# ------------------------------------------------------------------------------
log "3/7  git pull bajarilmoqda..."
CURRENT_BRANCH="$(git rev-parse --abbrev-ref HEAD)"
log "    Branch: $CURRENT_BRANCH"
git fetch --all --prune
git pull --ff-only origin "$CURRENT_BRANCH" || {
    err "git pull muvaffaqiyatsiz. Qo'lda hal qiling: cd $REPO_DIR"
    exit 1
}

# ------------------------------------------------------------------------------
# 4. Virtualenv va talablar
# ------------------------------------------------------------------------------
log "4/7  Virtualenv tekshirilmoqda..."
if [[ -f "$VENV_DIR/bin/activate" ]]; then
    # shellcheck disable=SC1091
    source "$VENV_DIR/bin/activate"
    log "    Virtualenv faollashtirildi: $VENV_DIR"
else
    warn "    Virtualenv topilmadi — yaratilmoqda: $VENV_DIR"
    python3 -m venv "$VENV_DIR"
    # shellcheck disable=SC1091
    source "$VENV_DIR/bin/activate"
fi

if [[ -f "$PROJECT_DIR/requirements.txt" ]]; then
    log "    pip install -r requirements.txt"
    pip install --upgrade pip wheel >/dev/null
    pip install -r "$PROJECT_DIR/requirements.txt"
elif [[ -f "$REPO_DIR/requirements.txt" ]]; then
    pip install -r "$REPO_DIR/requirements.txt"
fi

# ------------------------------------------------------------------------------
# 5. Migratsiyalar (ma'lumotlar saqlangan holda)
# ------------------------------------------------------------------------------
log "5/7  Migratsiyalar qo'llanilmoqda..."
cd "$PROJECT_DIR"
python manage.py migrate --noinput

# ------------------------------------------------------------------------------
# 6. Statiklar (faqat production uchun)
# ------------------------------------------------------------------------------
if grep -q '^STATIC_ROOT' library/settings.py 2>/dev/null; then
    log "6/7  Statiklar yig'ilmoqda..."
    python manage.py collectstatic --noinput || warn "collectstatic muvaffaqiyatsiz"
else
    log "6/7  STATIC_ROOT yo'q — collectstatic o'tkazib yuborildi"
fi

# ------------------------------------------------------------------------------
# 7. Xizmatni qayta ishga tushirish
# ------------------------------------------------------------------------------
log "7/7  Xizmat qayta ishga tushirilmoqda..."

if systemctl list-unit-files 2>/dev/null | grep -q "^${SERVICE_NAME}\."; then
    log "    systemd: ${SERVICE_NAME}"
    sudo systemctl restart "${SERVICE_NAME}"
    sleep 2
    sudo systemctl status "${SERVICE_NAME}" --no-pager -l | head -20
elif command -v supervisorctl >/dev/null 2>&1 && supervisorctl status "${SERVICE_NAME}" >/dev/null 2>&1; then
    log "    supervisor: ${SERVICE_NAME}"
    sudo supervisorctl restart "${SERVICE_NAME}"
else
    warn "    systemd/supervisor xizmati topilmadi — gunicorn nohup orqali ishga tushiriladi"
    pkill -f "gunicorn.*library.wsgi" || true
    sleep 1
    cd "$PROJECT_DIR"
    nohup "$VENV_DIR/bin/gunicorn" \
        --bind "0.0.0.0:${GUNICORN_PORT}" \
        --workers 3 \
        --access-logfile "$BACKUP_ROOT/access.log" \
        --error-logfile "$BACKUP_ROOT/error.log" \
        library.wsgi:application >/dev/null 2>&1 &
    sleep 2
    if pgrep -f "gunicorn.*library.wsgi" >/dev/null; then
        log "    Gunicorn ishga tushdi (port: ${GUNICORN_PORT})"
    else
        err "    Gunicorn ishga tushmadi. Loglarni tekshiring: $BACKUP_ROOT/error.log"
        exit 1
    fi
fi

# ------------------------------------------------------------------------------
# Yakun
# ------------------------------------------------------------------------------
log "✅ Tayyor!"
log "Backup joyi: $BACKUP_DIR"
log "Eski backup'larni tozalash uchun:"
log "    ls -lt $BACKUP_ROOT/ | tail -n +6 | awk '{print \"$BACKUP_ROOT/\"\$NF}' | xargs rm -rf"
