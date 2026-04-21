#pragma once

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
			this->Text = L"O'quvchi Paneli";
			this->Size = System::Drawing::Size(600, 400);
			this->BackColor = Color::White;
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;

			Label^ l = gcnew Label();
			l->Text = L"F.I.Sh kiriting:";
			l->Location = Point(20, 20);
			l->AutoSize = true;
			l->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			this->Controls->Add(l);

			txtID = gcnew TextBox();
			txtID->Location = Point(140, 18);
			txtID->Size = System::Drawing::Size(200, 25);
			txtID->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			this->Controls->Add(txtID);

			btnLogin = gcnew Button();
			btnLogin->Text = L"Kirish";
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
			dgv->BackgroundColor = Color::FromArgb(248, 249, 250);
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
			dgv->RowHeadersVisible = false;
           dgv->EnableHeadersVisualStyles = false;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(240, 240, 240);
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::FromArgb(33, 37, 41);
			dgv->ColumnCount = 3;
			dgv->Columns[0]->Name = L"Kitob nomi";
			dgv->Columns[1]->Name = L"Olingan sana";
			dgv->Columns[2]->Name = L"Qaytarish muddati";
			this->Controls->Add(dgv);
		}
	private:
		void btnLogin_Click(Object^ sender, EventArgs^ e) {
			dgv->Rows->Clear();
			String^ rname = txtID->Text->ToLower();
			if (String::IsNullOrWhiteSpace(rname)) {
				MessageBox::Show(L"Iltimos, ismingizni kiriting.");
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
				MessageBox::Show(L"Sizda ijaraga olingan kitoblar topilmadi.", L"Xabar");
			}
		}
	};
}