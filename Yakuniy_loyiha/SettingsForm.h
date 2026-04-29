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
			this->Size = System::Drawing::Size(360, 250);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			lblLanguage = gcnew Label();
			lblLanguage->Text = AppSettings::Translate(L"Dastur tili:", L"Application language:", L"Язык приложения:");
			lblLanguage->Location = Point(20, 22);
			lblLanguage->AutoSize = true;
			lblLanguage->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			this->Controls->Add(lblLanguage);

			cmbLanguage = gcnew ComboBox();
			cmbLanguage->Items->Add(L"O'zbekcha");
			cmbLanguage->Items->Add(L"English");
			cmbLanguage->Items->Add(L"Русский");
			cmbLanguage->Location = Point(20, 52);
			cmbLanguage->Size = System::Drawing::Size(300, 25);
			cmbLanguage->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			cmbLanguage->DropDownStyle = ComboBoxStyle::DropDownList;
			if (AppSettings::CurrentLanguage == AppLanguage::English) cmbLanguage->SelectedIndex = 1;
			else if (AppSettings::CurrentLanguage == AppLanguage::Russian) cmbLanguage->SelectedIndex = 2;
			else cmbLanguage->SelectedIndex = 0;
			this->Controls->Add(cmbLanguage);

			chkDarkMode = gcnew CheckBox();
			chkDarkMode->Text = AppSettings::Translate(L"Qorong'u rejim", L"Dark mode", L"Темный режим");
			chkDarkMode->Location = Point(20, 95);
			chkDarkMode->Width = 300;
			chkDarkMode->Checked = AppSettings::DarkMode;
			chkDarkMode->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			this->Controls->Add(chkDarkMode);

			btnSave = gcnew Button();
			btnSave->Text = AppSettings::Translate(L"Saqlash", L"Save", L"Сохранить");
			btnSave->Location = Point(130, 150);
			btnSave->Size = System::Drawing::Size(90, 35);
			btnSave->BackColor = Color::FromArgb(40, 44, 52);
			btnSave->ForeColor = Color::White;
			btnSave->FlatStyle = FlatStyle::Flat;
			btnSave->FlatAppearance->BorderSize = 0;
			btnSave->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			btnSave->Click += gcnew EventHandler(this, &SettingsForm::btnSave_Click);
			this->Controls->Add(btnSave);

			btnCancel = gcnew Button();
			btnCancel->Text = AppSettings::Translate(L"Bekor qilish", L"Cancel", L"Отмена");
			btnCancel->Location = Point(230, 150);
			btnCancel->Size = System::Drawing::Size(90, 35);
			btnCancel->BackColor = Color::FromArgb(245, 245, 245);
			btnCancel->ForeColor = Color::FromArgb(33, 37, 41);
			btnCancel->FlatStyle = FlatStyle::Flat;
			btnCancel->FlatAppearance->BorderSize = 0;
			btnCancel->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Controls->Add(btnCancel);

			this->AcceptButton = btnSave;
			this->CancelButton = btnCancel;
			AppSettings::ApplyTheme(this);
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