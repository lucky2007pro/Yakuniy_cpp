#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class HistoryForm : public Form {
		DataGridView^ dgv;
		Label^ lblCount;
	public:
		HistoryForm() {
			this->Text = AppSettings::Translate(L"Barcha ijaralar tarixi", L"Borrow history", L"История аренды");
			this->Size = System::Drawing::Size(820, 520);
			this->StartPosition = FormStartPosition::CenterParent;
			this->BackColor = AppSettings::PageBackColor();
			this->MinimumSize = System::Drawing::Size(720, 460);

			Label^ title = gcnew Label();
			title->Text = AppSettings::Translate(L"Ijaralar tarixi", L"Borrow history", L"История аренды");
			title->Location = Point(24, 20);
			title->Size = System::Drawing::Size(420, 40);
			title->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 20.0F, FontStyle::Bold);
			title->ForeColor = AppSettings::TextColor();
			this->Controls->Add(title);

			lblCount = gcnew Label();
			lblCount->Text = AppSettings::Translate(L"Yuklanmoqda", L"Loading", L"Загрузка");
			lblCount->Location = Point(26, 60);
			lblCount->Size = System::Drawing::Size(420, 24);
			lblCount->ForeColor = AppSettings::MutedTextColor();
			this->Controls->Add(lblCount);

			Panel^ gridCard = gcnew Panel();
			gridCard->Location = Point(24, 102);
			gridCard->Size = System::Drawing::Size(756, 360);
			gridCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			gridCard->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(gridCard, 8);
			this->Controls->Add(gridCard);

			dgv = gcnew DataGridView();
			dgv->Location = Point(12, 12);
			dgv->Size = System::Drawing::Size(732, 336);
			dgv->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleGrid(dgv);
			dgv->ColumnCount = 5;
			dgv->Columns[0]->Name = AppSettings::Translate(L"Kitobxon", L"Reader", L"Читатель");
			dgv->Columns[1]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
			dgv->Columns[2]->Name = AppSettings::Translate(L"Berilgan sana", L"Issue date", L"Дата выдачи");
			dgv->Columns[3]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
			dgv->Columns[4]->Name = AppSettings::Translate(L"Holati", L"Status", L"Статус");
			gridCard->Controls->Add(dgv);

			LoadData();
		}
	private:
		void LoadData() {
			int count = 0;
			if (File::Exists("issues.txt")) {
				array<String^>^ lines = File::ReadAllLines("issues.txt");
				for each (String^ line in lines) {
					array<String^>^ p = line->Split('|');
					if (p->Length >= 4) {
						String^ status = AppSettings::Translate(L"Kutilmoqda", L"Pending", L"Ожидается");
						Color rowColor = AppSettings::SurfaceColor();
						try {
							DateTime dt = DateTime::ParseExact(p[3], "dd.MM.yyyy", nullptr);
							if (DateTime::Now > dt) {
								status = AppSettings::Translate(L"Muddat o'tgan", L"Overdue", L"Просрочено");
								rowColor = AppSettings::DarkMode ? Color::FromArgb(88, 42, 42) : Color::FromArgb(254, 226, 226);
							}
						}
						catch (...) {}

						int idx = dgv->Rows->Add(p[0], p[1], p[2], p[3], status);
						dgv->Rows[idx]->DefaultCellStyle->BackColor = rowColor;
						count++;
					}
				}
			}

			lblCount->Text = String::Format(
				AppSettings::Translate(L"Jami yozuvlar: {0}", L"Total records: {0}", L"Всего записей: {0}"),
				count
			);
		}
	};
}
