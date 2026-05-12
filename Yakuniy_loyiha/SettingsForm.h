#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class SettingsForm : public Form {
	private:
		Label^ lblLanguage;
		ComboBox^ cmbLanguage;
		CheckBox^ chkDarkMode;
		Button^ btnSave;
		Button^ btnCancel;

	public:
		SettingsForm() {
			this->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
			this->Size = System::Drawing::Size(550, 600);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			// === MODERN HEADER ===
			Panel^ header = gcnew Panel();
			header->Location = Point(0, 0);
			header->Size = System::Drawing::Size(this->ClientSize.Width, 140);
			header->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::EnableGradientBackground(header, AppSettings::GradientAccentStart(), AppSettings::GradientPrimaryEnd());

			Panel^ iconBadge = gcnew Panel();
			iconBadge->Location = Point(20, 18);
			iconBadge->Size = System::Drawing::Size(70, 70);
			iconBadge->BackColor = Color::FromArgb(235, 255, 255, 255);
			AppSettings::MakeRounded(iconBadge, 35);
			header->Controls->Add(iconBadge);

			Label^ iconLabel = gcnew Label();
			iconLabel->Text = L"⚙️";
			iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 34.0F);
			iconLabel->Dock = DockStyle::Fill;
			iconLabel->TextAlign = ContentAlignment::MiddleCenter;
			iconLabel->ForeColor = AppSettings::TextColor();
			iconLabel->BackColor = Color::Transparent;
			iconBadge->Controls->Add(iconLabel);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
			AppSettings::StyleHeaderTitle(titleLabel);
			titleLabel->Location = Point(104, 22);
			titleLabel->Size = System::Drawing::Size(320, 38);
			titleLabel->AutoEllipsis = true;
			header->Controls->Add(titleLabel);

			Label^ subtitleLabel = gcnew Label();
			subtitleLabel->Text = AppSettings::Translate(L"Asosiy sozlamalarni mosla", L"Customize your preferences", L"Настройте ваши предпочтения");
			AppSettings::StyleHeaderSubtitle(subtitleLabel);
			subtitleLabel->Location = Point(106, 62);
			subtitleLabel->Size = System::Drawing::Size(360, 28);
			subtitleLabel->AutoEllipsis = true;
			header->Controls->Add(subtitleLabel);

			this->Controls->Add(header);

			// === SETTINGS SECTIONS ===
			int cardY = 160;
			int cardX = 20;
			int cardWidth = this->ClientSize.Width - 40;

			// === LANGUAGE SECTION ===
			Panel^ langCard = gcnew Panel();
			langCard->Location = Point(cardX, cardY);
			langCard->Size = System::Drawing::Size(cardWidth, 140);
			langCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(langCard, 18, false);
			System::Windows::Forms::Padding^ p = gcnew System::Windows::Forms::Padding(20);
			langCard->Padding = *p;
			
			// Add accent bar
			Panel^ langAccent = gcnew Panel();
			langAccent->Location = Point(0, 0);
			langAccent->Size = System::Drawing::Size(cardWidth, 5);
			AppSettings::StyleAccentStrip(langAccent, AppSettings::SecondaryColor(), 14);
			langCard->Controls->Add(langAccent);

			this->Controls->Add(langCard);

			Label^ langTitle = gcnew Label();
			langTitle->Text = AppSettings::Translate(L"🌐 Dastur tili", L"🌐 Application language", L"🌐 Язык приложения");
			AppSettings::StyleSectionTitle(langTitle);
			langTitle->AutoSize = true;
			langTitle->Location = Point(12, 10);
			langCard->Controls->Add(langTitle);

			Label^ langDesc = gcnew Label();
			langDesc->Text = AppSettings::Translate(L"Ilovani foydalanish tili", L"Choose your preferred language", L"Выберите язык интерфейса");
			AppSettings::StyleBodyText(langDesc);
			langDesc->AutoSize = true;
			langDesc->Location = Point(12, 38);
			langCard->Controls->Add(langDesc);

			cmbLanguage = gcnew ComboBox();
			cmbLanguage->Items->Add(L"🇺🇿  O'zbekcha");
			cmbLanguage->Items->Add(L"🇺🇸  English");
			cmbLanguage->Items->Add(L"🇷🇺  Русский");
			cmbLanguage->Location = Point(12, 62);
			cmbLanguage->Size = System::Drawing::Size(cardWidth - 64, 32);
			cmbLanguage->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbLanguage->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
			if (AppSettings::CurrentLanguage == AppLanguage::English) cmbLanguage->SelectedIndex = 1;
			else if (AppSettings::CurrentLanguage == AppLanguage::Russian) cmbLanguage->SelectedIndex = 2;
			else cmbLanguage->SelectedIndex = 0;
			AppSettings::StyleInput(cmbLanguage);
			langCard->Controls->Add(cmbLanguage);

			// === APPEARANCE SECTION ===
			cardY += 170;
			Panel^ darkCard = gcnew Panel();
			darkCard->Location = Point(cardX, cardY);
			darkCard->Size = System::Drawing::Size(cardWidth, 140);
			darkCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(darkCard, 18, false);
			System::Windows::Forms::Padding^ p2 = gcnew System::Windows::Forms::Padding(20);
			darkCard->Padding = *p2;
			
			// Add accent bar
			Panel^ accentBar = gcnew Panel();
			accentBar->Location = Point(0, 0);
			accentBar->Size = System::Drawing::Size(cardWidth, 5);
			AppSettings::StyleAccentStrip(accentBar, AppSettings::PrimaryColor(), 14);
			darkCard->Controls->Add(accentBar);

			this->Controls->Add(darkCard);

			Label^ darkTitle = gcnew Label();
			darkTitle->Text = AppSettings::Translate(L"🌙 Ko'rinish", L"🌙 Appearance", L"🌙 Внешний вид");
			AppSettings::StyleSectionTitle(darkTitle);
			darkTitle->AutoSize = true;
			darkTitle->Location = Point(12, 10);
			darkCard->Controls->Add(darkTitle);

			chkDarkMode = gcnew CheckBox();
			chkDarkMode->Text = AppSettings::Translate(L"Qorong'u rejim", L"Dark mode", L"Темный режим");
			chkDarkMode->Location = Point(12, 46);
			chkDarkMode->Width = cardWidth - 64;
			chkDarkMode->Height = 28;
			chkDarkMode->Checked = AppSettings::DarkMode;
			chkDarkMode->ForeColor = AppSettings::TextColor();
			chkDarkMode->BackColor = Color::Transparent;
			chkDarkMode->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
			darkCard->Controls->Add(chkDarkMode);

			Label^ darkDesc = gcnew Label();
			darkDesc->Text = AppSettings::Translate(L"Ko'zni o'zga qila oladigan tun rejimi", L"Easy on the eyes night mode", L"Удобный ночной режим");
			AppSettings::StyleBodyText(darkDesc);
			darkDesc->AutoSize = true;
			darkDesc->Location = Point(32, 76);
			darkCard->Controls->Add(darkDesc);

			// === BUTTONS ===
			btnSave = gcnew Button();
			btnSave->Text = AppSettings::Translate(L"Saqlash", L"Save changes", L"Сохранить");
			btnSave->Location = Point(cardWidth - 220, this->ClientSize.Height - 50);
			btnSave->Size = System::Drawing::Size(100, 38);
			btnSave->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			AppSettings::StyleModernButton(btnSave, true);
			btnSave->Click += gcnew EventHandler(this, &SettingsForm::btnSave_Click);
			this->Controls->Add(btnSave);

			btnCancel = gcnew Button();
			btnCancel->Text = AppSettings::Translate(L"Bekor", L"Cancel", L"Отмена");
			btnCancel->Location = Point(cardWidth - 106, this->ClientSize.Height - 50);
			btnCancel->Size = System::Drawing::Size(100, 38);
			btnCancel->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			AppSettings::StyleModernButton(btnCancel, false);
			btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Controls->Add(btnCancel);

			this->AcceptButton = btnSave;
			this->CancelButton = btnCancel;
		}

	private:
		System::Void btnSave_Click(Object^ sender, EventArgs^ e) {
			if (cmbLanguage->SelectedIndex == 1) AppSettings::CurrentLanguage = AppLanguage::English;
			else if (cmbLanguage->SelectedIndex == 2) AppSettings::CurrentLanguage = AppLanguage::Russian;
			else AppSettings::CurrentLanguage = AppLanguage::Uzbek;

			AppSettings::DarkMode = chkDarkMode->Checked;
			AppSettings::Save();
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
	};
}
