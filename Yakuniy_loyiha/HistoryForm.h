#pragma once

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class HistoryForm : public Form {
		DataGridView^ dgv;
	public:
		HistoryForm() {
			this->Text = L"Barcha ijaralar tarixi";
			this->Size = System::Drawing::Size(700, 450);
			this->StartPosition = FormStartPosition::CenterParent;
			this->BackColor = Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;

			dgv = gcnew DataGridView();
			dgv->Dock = DockStyle::Fill;
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dgv->BackgroundColor = Color::FromArgb(248, 249, 250);
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
			dgv->RowHeadersVisible = false;
			dgv->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			dgv->ColumnCount = 5;
			dgv->Columns[0]->Name = L"Kitobxon";
			dgv->Columns[1]->Name = L"Kitob";
			dgv->Columns[2]->Name = L"Berilgan sana";
			dgv->Columns[3]->Name = L"Qaytarish muddati";
			dgv->Columns[4]->Name = L"Holati";
			this->Controls->Add(dgv);

			LoadData();
		}
	private:
		void LoadData() {
			if (File::Exists("issues.txt")) {
				array<String^>^ lines = File::ReadAllLines("issues.txt");
				for each (String^ line in lines) {
					array<String^>^ p = line->Split('|');
					if (p->Length >= 4) {
						String^ status = L"Kutilmoqda";
						Color rowColor = Color::White;
						try {
							DateTime dt = DateTime::ParseExact(p[3], "dd.MM.yyyy", nullptr);
							if (DateTime::Now > dt) {
								status = L"Muddat o'tgan!";
								rowColor = Color::FromArgb(255, 200, 200); // Qizil/pushti rang
							}
						} catch (...) {}
						
						int idx = dgv->Rows->Add(p[0], p[1], p[2], p[3], status);
						dgv->Rows[idx]->DefaultCellStyle->BackColor = rowColor;
					}
				}
			}
		}
	};
}