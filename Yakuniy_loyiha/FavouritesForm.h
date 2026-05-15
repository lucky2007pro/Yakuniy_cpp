#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Text::RegularExpressions;
using namespace System::Net;
using namespace System::Collections::Generic;

// Favs format: id|title|author|coverUrl|status|sectionName
public ref class FavouritesForm : public Form {
public:
    String^ serverUrl;

    FavouritesForm(String^ srvUrl) {
        serverUrl = srvUrl;
        this->Text = AppSettings::Translate(L"❤ Sevimli kitoblar", L"❤ Favourites", L"❤ Избранное");
        this->Size = System::Drawing::Size(1100, 720);
        this->StartPosition = FormStartPosition::CenterParent;
        this->BackColor = AppSettings::PageBackColor();
        this->MinimumSize = System::Drawing::Size(800, 560);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

        // Header
        Panel^ header = gcnew Panel();
        header->Dock = DockStyle::Top;
        header->Height = 90;
        AppSettings::EnableGradientBackground(header,
            Color::FromArgb(220, 38, 38),
            Color::FromArgb(239, 68, 68));

        Label^ hTitle = gcnew Label();
        hTitle->Text = AppSettings::Translate(L"❤ Sevimli kitoblar", L"❤ Favourites", L"❤ Избранное");
        hTitle->Location = Point(22, 14);
        hTitle->AutoSize = true;
        AppSettings::StyleHeaderTitle(hTitle);
        hTitle->ForeColor = Color::White;
        header->Controls->Add(hTitle);

        Label^ hSub = gcnew Label();
        hSub->Text = AppSettings::Translate(
            L"Yoqtirgan kitoblaringiz shu yerda saqlanadi",
            L"Your bookmarked books are saved here",
            L"Ваши отмеченные книги сохраняются здесь");
        hSub->Location = Point(24, 52);
        hSub->AutoSize = true;
        AppSettings::StyleHeaderSubtitle(hSub);
        hSub->ForeColor = Color::FromArgb(254, 202, 202);
        header->Controls->Add(hSub);

        this->Controls->Add(header);

        // Action bar
        Panel^ actionBar = gcnew Panel();
        actionBar->Location = Point(0, 90);
        actionBar->Size = System::Drawing::Size(this->ClientSize.Width, 44);
        actionBar->Anchor = static_cast<AnchorStyles>(
            AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
        actionBar->BackColor = AppSettings::SurfaceColor();

        lblCount = gcnew Label();
        lblCount->Text = L"";
        lblCount->AutoSize = true;
        lblCount->Location = Point(18, 12);
        AppSettings::StyleBodyText(lblCount);
        actionBar->Controls->Add(lblCount);

        Button^ btnClearAll = gcnew Button();
        btnClearAll->Text = AppSettings::Translate(L"Hammasini o'chirish", L"Clear all", L"Очистить всё");
        btnClearAll->Size = System::Drawing::Size(148, 30);
        btnClearAll->Location = Point(this->ClientSize.Width - 165, 6);
        btnClearAll->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
        AppSettings::StyleModernButton(btnClearAll, false);
        btnClearAll->BackColor = Color::FromArgb(220, 38, 38);
        btnClearAll->ForeColor = Color::White;
        btnClearAll->FlatAppearance->BorderSize = 0;
        btnClearAll->Click += gcnew EventHandler(this, &FavouritesForm::btnClearAll_Click);
        actionBar->Controls->Add(btnClearAll);
        this->Controls->Add(actionBar);

        // Results panel
        flp = gcnew FlowLayoutPanel();
        flp->Location = Point(12, 144);
        flp->Anchor = static_cast<AnchorStyles>(
            AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
        flp->Size = System::Drawing::Size(this->ClientSize.Width - 24, this->ClientSize.Height - 156);
        flp->AutoScroll = true;
        flp->WrapContents = true;
        flp->BackColor = AppSettings::PageBackColor();
        flp->Padding = System::Windows::Forms::Padding(8);
        this->Controls->Add(flp);

        LoadFavs();
    }

    static String^ FavsFilePath() {
        String^ dir = Path::Combine(
            Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData),
            L"TATULibrary");
        if (!Directory::Exists(dir)) Directory::CreateDirectory(dir);
        return Path::Combine(dir, L"favourites.txt");
    }

    static List<array<String^>^>^ ReadFavs() {
        auto list = gcnew List<array<String^>^>();
        String^ path = FavsFilePath();
        if (!File::Exists(path)) return list;
        array<String^>^ lines = File::ReadAllLines(path, System::Text::Encoding::UTF8);
        for each (String^ line in lines) {
            if (String::IsNullOrWhiteSpace(line)) continue;
            array<String^>^ parts = line->Split('|');
            if (parts->Length >= 6) list->Add(parts);
        }
        return list;
    }

    static void WriteFavs(List<array<String^>^>^ list) {
        String^ path = FavsFilePath();
        auto sb = gcnew System::Text::StringBuilder();
        for each (array<String^>^ parts in list) {
            sb->AppendLine(String::Join(L"|", parts));
        }
        File::WriteAllText(path, sb->ToString(), System::Text::Encoding::UTF8);
    }

    static bool IsFav(String^ bookId) {
        for each (array<String^>^ p in ReadFavs()) {
            if (p[0] == bookId) return true;
        }
        return false;
    }

    static void AddFav(String^ id, String^ title, String^ author, String^ cover, String^ status, String^ section) {
        auto list = ReadFavs();
        for (int i = list->Count - 1; i >= 0; i--)
            if (list[i][0] == id) list->RemoveAt(i);
        list->Insert(0, gcnew array<String^>{id, title, author, cover, status, section});
        WriteFavs(list);
    }

    static void RemoveFav(String^ bookId) {
        auto list = ReadFavs();
        for (int i = list->Count - 1; i >= 0; i--)
            if (list[i][0] == bookId) list->RemoveAt(i);
        WriteFavs(list);
    }

    static void ToggleFav(String^ id, String^ title, String^ author, String^ cover, String^ status, String^ section) {
        if (IsFav(id)) RemoveFav(id);
        else AddFav(id, title, author, cover, status, section);
    }

private:
    FlowLayoutPanel^ flp;
    Label^ lblCount;

    void LoadFavs() {
        flp->SuspendLayout();
        flp->Controls->Clear();
        auto list = ReadFavs();

        if (list->Count == 0) {
            Panel^ empty = gcnew Panel();
            empty->Size = System::Drawing::Size(360, 140);
            empty->Margin = System::Windows::Forms::Padding(20);
            AppSettings::StyleSurfacePanel(empty, 14, true);
            Label^ emLbl = gcnew Label();
            emLbl->Text = AppSettings::Translate(
                L"❤ Hali sevimli kitob yo'q.\nKitob kartasidagi ❤ tugmasini bosing.",
                L"❤ No favourites yet.\nClick the ❤ button on a book card.",
                L"❤ Нет избранных. Нажмите ❤ на карточке книги.");
            emLbl->Dock = DockStyle::Fill;
            emLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            emLbl->Font = gcnew Drawing::Font(L"Segoe UI", 11.0f);
            AppSettings::StyleBodyText(emLbl);
            empty->Controls->Add(emLbl);
            flp->Controls->Add(empty);
        }

        lblCount->Text = String::Format(
            AppSettings::Translate(L"Jami: {0} ta sevimli", L"Total: {0} favourites", L"Всего: {0} избранных"),
            list->Count);

        for each (array<String^>^ p in list) {
            String^ bid = p[0];
            String^ title = p[1];
            String^ author = p[2];
            String^ cover = p[3];
            String^ status = p[4];
            bool avail = (status == AppSettings::Translate(L"Mavjud", L"Available", L"Доступно") || status == L"Mavjud" || status == L"Available");

            Panel^ card = gcnew Panel();
            card->Size = System::Drawing::Size(230, 310);
            card->Margin = System::Windows::Forms::Padding(10);
            card->BackColor = AppSettings::SurfaceColor();
            card->Cursor = Cursors::Hand;
            MakeRound(card, 12);

            PictureBox^ pb = gcnew PictureBox();
            pb->Size = System::Drawing::Size(230, 180);
            pb->Location = Point(0, 0);
            pb->SizeMode = PictureBoxSizeMode::StretchImage;
            pb->BackColor = AppSettings::DarkMode
                ? Color::FromArgb(30, 35, 45) : Color::FromArgb(226, 232, 240);
            if (!String::IsNullOrEmpty(cover) && cover != L"null") {
                try {
                    WebClient^ wc = gcnew WebClient();
                    array<Byte>^ data = wc->DownloadData(cover);
                    pb->Image = Image::FromStream(gcnew MemoryStream(data));
                } catch (...) {}
            }
            card->Controls->Add(pb);

            Label^ lblT = gcnew Label();
            lblT->Text = title;
            lblT->Location = Point(10, 188);
            lblT->Size = System::Drawing::Size(210, 40);
            lblT->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.5F, FontStyle::Bold);
            lblT->ForeColor = AppSettings::TextColor();
            lblT->AutoEllipsis = true;
            card->Controls->Add(lblT);

            Label^ lblA = gcnew Label();
            lblA->Text = author;
            lblA->Location = Point(10, 230);
            lblA->Size = System::Drawing::Size(210, 18);
            lblA->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            lblA->ForeColor = AppSettings::MutedTextColor();
            lblA->AutoEllipsis = true;
            card->Controls->Add(lblA);

            Label^ lblS = gcnew Label();
            lblS->Text = status;
            lblS->Location = Point(10, 250);
            lblS->AutoSize = true;
            lblS->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            lblS->ForeColor = avail ? AppSettings::SuccessColor() : AppSettings::WarningColor();
            card->Controls->Add(lblS);

            Button^ btnRm = gcnew Button();
            btnRm->Text = L"✕";
            btnRm->Size = System::Drawing::Size(28, 28);
            btnRm->Location = Point(196, 4);
            btnRm->FlatStyle = FlatStyle::Flat;
            btnRm->FlatAppearance->BorderSize = 0;
            btnRm->BackColor = Color::FromArgb(180, 220, 38, 38);
            btnRm->ForeColor = Color::White;
            btnRm->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            btnRm->Cursor = Cursors::Hand;
            btnRm->Tag = bid;
            btnRm->Click += gcnew EventHandler(this, &FavouritesForm::btnRemove_Click);
            MakeRound(btnRm, 14);
            card->Controls->Add(btnRm);
            btnRm->BringToFront();

            flp->Controls->Add(card);
        }
        flp->ResumeLayout();
    }

    void MakeRound(Control^ c, int r) {
        GraphicsPath^ p = gcnew GraphicsPath();
        p->StartFigure();
        p->AddArc(0, 0, r, r, 180, 90);
        p->AddArc(c->Width - r, 0, r, r, 270, 90);
        p->AddArc(c->Width - r, c->Height - r, r, r, 0, 90);
        p->AddArc(0, c->Height - r, r, r, 90, 90);
        p->CloseFigure();
        c->Region = gcnew Drawing::Region(p);
    }

    void btnRemove_Click(Object^ sender, EventArgs^ e) {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn == nullptr) return;
        RemoveFav(btn->Tag->ToString());
        LoadFavs();
    }

    void btnClearAll_Click(Object^ sender, EventArgs^ e) {
        auto dr = MessageBox::Show(
            AppSettings::Translate(L"Barcha sevimlini o'chirasizmi?", L"Clear all favourites?", L"Очистить все избранные?"),
            AppSettings::Translate(L"Tasdiqlash", L"Confirm", L"Подтверждение"),
            MessageBoxButtons::YesNo, MessageBoxIcon::Question);
        if (dr != System::Windows::Forms::DialogResult::Yes) return;
        File::Delete(FavsFilePath());
        LoadFavs();
    }
};
}
