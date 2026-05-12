#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			this->Text = AppSettings::Translate(L"Dastur haqida", L"About app", L"О программе");
			this->Size = System::Drawing::Size(650, 850);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
			this->MaximizeBox = true;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			this->MaximumSize = System::Drawing::Size(800, 1000);

			// === PREMIUM HEADER WITH GRADIENT ===
			Panel^ header = gcnew Panel();
			header->Location = Point(0, 0);
			header->Size = System::Drawing::Size(this->ClientSize.Width, 220);
			header->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::EnableGradientBackground(header, AppSettings::GradientPrimaryStart(), AppSettings::GradientPrimaryEnd());

			// Icon with badge
			Panel^ iconBg = gcnew Panel();
			iconBg->Location = Point(20, 20);
			iconBg->Size = System::Drawing::Size(80, 80);
			iconBg->BackColor = Color::FromArgb(235, 255, 255, 255);
			AppSettings::MakeRounded(iconBg, 40);
			header->Controls->Add(iconBg);

			Label^ iconLabel = gcnew Label();
			iconLabel->Text = L"📚";
			iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 40.0F);
			iconLabel->AutoSize = false;
			iconLabel->Size = System::Drawing::Size(80, 80);
			iconLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			iconLabel->ForeColor = AppSettings::TextColor();
			iconLabel->BackColor = Color::Transparent;
			iconBg->Controls->Add(iconLabel);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = AppSettings::Translate(L"TATU Kutubxona", L"TATU Library", L"Библиотека ТАТУ");
			AppSettings::StyleHeaderTitle(titleLabel);
			titleLabel->Location = Point(122, 24);
			titleLabel->Size = System::Drawing::Size(420, 40);
			titleLabel->AutoEllipsis = true;
			header->Controls->Add(titleLabel);

			Label^ taglineLabel = gcnew Label();
			taglineLabel->Text = AppSettings::Translate(L"Zamonaviy kitob qidirish tizimi", L"Modern book discovery system", L"Современная система поиска");
			AppSettings::StyleHeaderSubtitle(taglineLabel);
			taglineLabel->Location = Point(124, 68);
			taglineLabel->Size = System::Drawing::Size(430, 32);
			header->Controls->Add(taglineLabel);

			// Version badge
			Panel^ versionBadge = gcnew Panel();
			versionBadge->Location = Point(120, 102);
			versionBadge->Size = System::Drawing::Size(120, 36);
			versionBadge->BackColor = Color::FromArgb(255, 255, 255);
			AppSettings::MakeRounded(versionBadge, 18);
			header->Controls->Add(versionBadge);

			Label^ versionLabel = gcnew Label();
			versionLabel->Text = L"✓ v1.0.0";
			versionLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
			versionLabel->ForeColor = AppSettings::SuccessColor();
			versionLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			versionLabel->BackColor = Color::Transparent;
			versionLabel->Dock = DockStyle::Fill;
			versionBadge->Controls->Add(versionLabel);

			// Status indicators
			int statusX = 280;
			AddStatusBadge(header, statusX, 102, L"🌍 Online", AppSettings::SuccessColor());
			AddStatusBadge(header, statusX + 140, 102, L"⚡ Fast", AppSettings::PrimaryColor());

			this->Controls->Add(header);

			// === FEATURE CARDS IN GRID ===
			int cardY = 250;
			int cardX = 20;
			int cardWidth = (this->ClientSize.Width - 60) / 2;

			AddPremiumCard(
				L"🔍",
				AppSettings::Translate(L"Tez qidiruv", L"Fast Search", L"Быстрый поиск"),
				AppSettings::Translate(L"Kitoblarni nom yoki muallif bo'yicha", L"Search by title or author", L"Поиск по названию"),
				cardX, cardY, cardWidth, AppSettings::GradientPrimaryStart()
			);

			AddPremiumCard(
				L"📍",
				AppSettings::Translate(L"Yaqin kutubxonalar", L"Nearby", L"Ближайшие"),
				AppSettings::Translate(L"GPS orqali eng yaqin kutubxonalarni", L"Find nearest via GPS", L"Поиск по GPS"),
				cardX + cardWidth + 20, cardY, cardWidth, AppSettings::GradientAccentStart()
			);

			cardY += 180;
			AddPremiumCard(
				L"📱",
				AppSettings::Translate(L"E-kitoblar", L"E-Books", L"Электронные"),
				AppSettings::Translate(L"To'g'ri telefonda e-kitoblarni o'qing", L"Read on mobile", L"Читай на телефоне"),
				cardX, cardY, cardWidth, AppSettings::GradientWarmStart()
			);

			AddPremiumCard(
				L"⭐",
				AppSettings::Translate(L"Baholash", L"Ratings", L"Оценки"),
				AppSettings::Translate(L"Kitoblarni baholang va sharhlar yozing", L"Rate and review books", L"Оценивайте книги"),
				cardX + cardWidth + 20, cardY, cardWidth, AppSettings::SuccessColor()
			);

			// === FOOTER ===
			Button^ btnClose = gcnew Button();
			btnClose->Text = AppSettings::Translate(L"Yopish", L"Close", L"Закрыть");
			btnClose->Location = Point(this->ClientSize.Width - 140, this->ClientSize.Height - 50);
			btnClose->Size = System::Drawing::Size(120, 40);
			btnClose->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			AppSettings::StyleModernButton(btnClose, true);
			this->Controls->Add(btnClose);

			AppSettings::ApplyTheme(this);
		}

	private:
		void AddStatusBadge(Panel^ parent, int x, int y, String^ text, Color bgColor) {
			Panel^ badge = gcnew Panel();
			badge->Location = Point(x, y);
			badge->Size = System::Drawing::Size(100, 36);
			badge->BackColor = bgColor;
			AppSettings::MakeRounded(badge, 18);
			parent->Controls->Add(badge);

			Label^ lbl = gcnew Label();
			lbl->Text = text;
			lbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 9.5F, FontStyle::Bold);
			lbl->ForeColor = Color::White;
			lbl->Dock = DockStyle::Fill;
			lbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			lbl->BackColor = Color::Transparent;
			badge->Controls->Add(lbl);
		}

		void AddPremiumCard(String^ emoji, String^ title, String^ desc, int x, int y, int width, Color accentColor) {
			Panel^ card = gcnew Panel();
			card->Location = Point(x, y);
			card->Size = System::Drawing::Size(width, 160);
			AppSettings::StyleSurfacePanel(card, 18, false);
			card->Padding = System::Windows::Forms::Padding(18);
			this->Controls->Add(card);

			// Accent bar at top
			Panel^ accentBar = gcnew Panel();
			accentBar->Location = Point(0, 0);
			accentBar->Size = System::Drawing::Size(width, 5);
			AppSettings::StyleAccentStrip(accentBar, accentColor, 16);
			card->Controls->Add(accentBar);

			Label^ emojiLabel = gcnew Label();
			emojiLabel->Text = emoji;
			emojiLabel->Font = gcnew Drawing::Font(L"Segoe UI", 40.0F);
			emojiLabel->AutoSize = false;
			emojiLabel->Size = System::Drawing::Size(80, 80);
			emojiLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			emojiLabel->ForeColor = accentColor;
			emojiLabel->BackColor = Color::Transparent;
			emojiLabel->Location = Point(10, 10);
			card->Controls->Add(emojiLabel);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = title;
			AppSettings::StyleSectionTitle(titleLabel);
			titleLabel->AutoSize = true;
			titleLabel->Location = Point(100, 18);
			card->Controls->Add(titleLabel);

			Label^ descLabel = gcnew Label();
			descLabel->Text = desc;
			AppSettings::StyleBodyText(descLabel);
			descLabel->AutoSize = false;
			descLabel->Size = System::Drawing::Size(width - 110, 70);
			descLabel->Location = Point(100, 50);
			card->Controls->Add(descLabel);
		}
	};
}
