#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

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
			this->Size = System::Drawing::Size(470, 330);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			Label^ title = gcnew Label();
			title->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
			title->Location = Point(24, 22);
			title->Size = System::Drawing::Size(400, 38);
			title->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 20.0F, FontStyle::Bold);
			title->ForeColor = AppSettings::TextColor();
			this->Controls->Add(title);

			Label^ subtitle = gcnew Label();
			subtitle->Text = AppSettings::Translate(L"Til va ko'rinishni o'zingizga moslang", L"Personalize language and appearance", L"Настройте язык и внешний вид");
			subtitle->Location = Point(26, 62);
			subtitle->Size = System::Drawing::Size(400, 24);
			subtitle->ForeColor = AppSettings::MutedTextColor();
			this->Controls->Add(subtitle);

			Panel^ card = gcnew Panel();
			card->Location = Point(24, 108);
			card->Size = System::Drawing::Size(405, 120);
			card->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(card, 8);
			this->Controls->Add(card);

			lblLanguage = gcnew Label();
			lblLanguage->Text = AppSettings::Translate(L"Dastur tili", L"Application language", L"Язык приложения");
			lblLanguage->Location = Point(18, 16);
			lblLanguage->Size = System::Drawing::Size(350, 24);
			lblLanguage->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.5F, FontStyle::Bold);
			lblLanguage->ForeColor = AppSettings::TextColor();
			card->Controls->Add(lblLanguage);

			cmbLanguage = gcnew ComboBox();
			cmbLanguage->Items->Add(L"O'zbekcha");
			cmbLanguage->Items->Add(L"English");
			cmbLanguage->Items->Add(L"Русский");
			cmbLanguage->Location = Point(18, 44);
			cmbLanguage->Size = System::Drawing::Size(360, 28);
			cmbLanguage->DropDownStyle = ComboBoxStyle::DropDownList;
			if (AppSettings::CurrentLanguage == AppLanguage::English) cmbLanguage->SelectedIndex = 1;
			else if (AppSettings::CurrentLanguage == AppLanguage::Russian) cmbLanguage->SelectedIndex = 2;
			else cmbLanguage->SelectedIndex = 0;
			AppSettings::StyleInput(cmbLanguage);
			card->Controls->Add(cmbLanguage);

			chkDarkMode = gcnew CheckBox();
			chkDarkMode->Text = AppSettings::Translate(L"Qorong'u rejimni yoqish", L"Enable dark mode", L"Включить темный режим");
			chkDarkMode->Location = Point(18, 84);
			chkDarkMode->Width = 360;
			chkDarkMode->Checked = AppSettings::DarkMode;
			chkDarkMode->ForeColor = AppSettings::TextColor();
			chkDarkMode->BackColor = AppSettings::SurfaceColor();
			card->Controls->Add(chkDarkMode);

			btnSave = gcnew Button();
			btnSave->Text = AppSettings::Translate(L"Saqlash", L"Save", L"Сохранить");
			btnSave->Location = Point(212, 248);
			btnSave->Size = System::Drawing::Size(104, 36);
			AppSettings::StyleButton(btnSave, AppSettings::PrimaryColor(), Color::White);
			btnSave->Click += gcnew EventHandler(this, &SettingsForm::btnSave_Click);
			this->Controls->Add(btnSave);

			btnCancel = gcnew Button();
			btnCancel->Text = AppSettings::Translate(L"Bekor qilish", L"Cancel", L"Отмена");
			btnCancel->Location = Point(326, 248);
			btnCancel->Size = System::Drawing::Size(104, 36);
			AppSettings::StyleButton(btnCancel, AppSettings::SurfaceColor(), AppSettings::TextColor());
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
