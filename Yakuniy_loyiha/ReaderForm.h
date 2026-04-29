#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class ReaderForm : public Form {
		TextBox^ txtID;
		Button^ btnLogin;
		DataGridView^ dgv;
	public:
		ReaderForm() {
			this->Text = AppSettings::Translate(L"O'quvchi Paneli", L"Reader Panel", L"Панель читателя");
			this->Size = System::Drawing::Size(600, 400);
			this->BackColor = AppSettings::DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;

			Label^ l = gcnew Label();
			l->Text = AppSettings::Translate(L"F.I.Sh kiriting:", L"Enter full name:", L"Введите ФИО:");
			l->Location = Point(20, 20);
			l->AutoSize = true;
			l->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			l->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			this->Controls->Add(l);

			txtID = gcnew TextBox();
			txtID->Location = Point(140, 18);
			txtID->Size = System::Drawing::Size(200, 25);
			txtID->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			txtID->BackColor = AppSettings::DarkMode ? Color::FromArgb(36, 39, 41) : Color::White;
			txtID->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			this->Controls->Add(txtID);

			btnLogin = gcnew Button();
			btnLogin->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");

			btnLogin->Location = Point(360, 15);
			btnLogin->Size = System::Drawing::Size(80, 30);
			btnLogin->BackColor = Color::FromArgb(40, 44, 52);
			btnLogin->ForeColor = Color::White;
			btnLogin->FlatStyle = FlatStyle::Flat;
           btnLogin->FlatAppearance->BorderSize = 0;
			btnLogin->Click += gcnew EventHandler(this, &ReaderForm::btnLogin_Click);
			this->Controls->Add(btnLogin);

			dgv = gcnew DataGridView();
			dgv->Location = Point(20, 60);
			dgv->Size = System::Drawing::Size(540, 280);
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dgv->BackgroundColor = AppSettings::DarkMode ? Color::FromArgb(36, 39, 41) : Color::FromArgb(248, 249, 250);
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
			dgv->RowHeadersVisible = false;
           dgv->EnableHeadersVisualStyles = false;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = AppSettings::DarkMode ? Color::FromArgb(44, 48, 50) : Color::FromArgb(240, 240, 240);
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			dgv->DefaultCellStyle->BackColor = AppSettings::DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
			dgv->DefaultCellStyle->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			dgv->ColumnCount = 3;
			dgv->Columns[0]->Name = AppSettings::Translate(L"Kitob nomi", L"Book title", L"Название книги");
			dgv->Columns[1]->Name = AppSettings::Translate(L"Olingan sana", L"Issue date", L"Дата выдачи");
			dgv->Columns[2]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
			this->Controls->Add(dgv);
		}

	private:
		void btnLogin_Click(Object^ sender, EventArgs^ e) {
			dgv->Rows->Clear();
			String^ rname = txtID->Text->ToLower();
			if (String::IsNullOrWhiteSpace(rname)) {
				MessageBox::Show(AppSettings::Translate(L"Iltimos, ismingizni kiriting.", L"Please enter your name.", L"Пожалуйста, введите имя."));
				return;
			}

			if (File::Exists("issues.txt")) {
				array<String^>^ lines = File::ReadAllLines("issues.txt");
				for each (String^ line in lines) {
					array<String^>^ p = line->Split('|');
					if (p->Length >= 4 && p[0]->ToLower()->Contains(rname)) {
						dgv->Rows->Add(p[1], p[2], p[3]);
					}
				}
			}
			if (dgv->Rows->Count == 0) {
				MessageBox::Show(
					AppSettings::Translate(L"Sizda ijaraga olingan kitoblar topilmadi.", L"No borrowed books were found.", L"У вас нет взятых книг."),
					AppSettings::Translate(L"Xabar", L"Info", L"Инфо")
				);
			}
		}
	};
}