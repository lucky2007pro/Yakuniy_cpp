#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class HistoryForm : public Form {
		DataGridView^ dgv;
	public:
		HistoryForm() {
			this->Text = AppSettings::Translate(L"Barcha ijaralar tarixi", L"Borrow history", L"История аренды");
			this->Size = System::Drawing::Size(700, 450);
			this->StartPosition = FormStartPosition::CenterParent;
			this->BackColor = AppSettings::DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;

			dgv = gcnew DataGridView();
			dgv->Dock = DockStyle::Fill;
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dgv->BackgroundColor = AppSettings::DarkMode ? Color::FromArgb(36, 39, 41) : Color::FromArgb(248, 249, 250);
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
			dgv->RowHeadersVisible = false;
			dgv->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			dgv->EnableHeadersVisualStyles = false;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = AppSettings::DarkMode ? Color::FromArgb(44, 48, 50) : Color::FromArgb(240, 240, 240);
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			dgv->DefaultCellStyle->BackColor = AppSettings::DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
			dgv->DefaultCellStyle->ForeColor = AppSettings::DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);

			dgv->ColumnCount = 5;
			dgv->Columns[0]->Name = AppSettings::Translate(L"Kitobxon", L"Reader", L"Читатель");
			dgv->Columns[1]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
			dgv->Columns[2]->Name = AppSettings::Translate(L"Berilgan sana", L"Issue date", L"Дата выдачи");
			dgv->Columns[3]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
			dgv->Columns[4]->Name = AppSettings::Translate(L"Holati", L"Status", L"Статус");

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
						String^ status = AppSettings::Translate(L"Kutilmoqda", L"Pending", L"Ожидается");
						Color rowColor = AppSettings::DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
						try {
							DateTime dt = DateTime::ParseExact(p[3], "dd.MM.yyyy", nullptr);
							if (DateTime::Now > dt) {
								status = AppSettings::Translate(L"Muddat o'tgan!", L"Overdue!", L"Просрочено!");
								rowColor = AppSettings::DarkMode ? Color::FromArgb(90, 50, 50) : Color::FromArgb(255, 200, 200);
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