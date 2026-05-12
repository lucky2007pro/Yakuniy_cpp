#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class HistoryForm : public Form {
		DataGridView^ dgv;
		Label^ lblCount;
	public:
		HistoryForm() {
			this->Text = AppSettings::Translate(L"Ijaralar tarixi", L"Borrow history", L"История аренды");
			this->Size = System::Drawing::Size(950, 700);
			this->StartPosition = FormStartPosition::CenterParent;
			this->BackColor = AppSettings::PageBackColor();
			this->MinimumSize = System::Drawing::Size(820, 600);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

			// === MODERN HEADER ===
			Panel^ header = gcnew Panel();
			header->Location = Point(0, 0);
			header->Size = System::Drawing::Size(this->ClientSize.Width, 140);
			header->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::EnableGradientBackground(header, AppSettings::GradientAccentStart(), AppSettings::GradientAccentEnd());

			Panel^ iconBadge = gcnew Panel();
			iconBadge->Location = Point(20, 18);
			iconBadge->Size = System::Drawing::Size(70, 70);
			iconBadge->BackColor = Color::FromArgb(235, 255, 255, 255);
			AppSettings::MakeRounded(iconBadge, 35);
			header->Controls->Add(iconBadge);

			Label^ iconLabel = gcnew Label();
			iconLabel->Text = L"📜";
			iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 34.0F);
			iconLabel->Dock = DockStyle::Fill;
			iconLabel->TextAlign = ContentAlignment::MiddleCenter;
			iconLabel->ForeColor = AppSettings::TextColor();
			iconLabel->BackColor = Color::Transparent;
			iconBadge->Controls->Add(iconLabel);

			Label^ title = gcnew Label();
			title->Text = AppSettings::Translate(L"Ijaralar tarixi", L"Borrow history", L"История аренды");
			title->Location = Point(115, 22);
			title->Size = System::Drawing::Size(420, 38);
			AppSettings::StyleHeaderTitle(title);
			header->Controls->Add(title);

			Label^ subtitle = gcnew Label();
			subtitle->Text = AppSettings::Translate(L"Barcha ijara amallari va qaytarish tarixi", L"All borrowing activities and return dates", L"Все операции аренды и сроки возврата");
			AppSettings::StyleHeaderSubtitle(subtitle);
			subtitle->Location = Point(117, 60);
			subtitle->Size = System::Drawing::Size(480, 30);
			subtitle->AutoEllipsis = true;
			header->Controls->Add(subtitle);

			this->Controls->Add(header);

			lblCount = gcnew Label();
			lblCount->Text = AppSettings::Translate(L"Yuklanmoqda...", L"Loading...", L"Загрузка...");
			lblCount->Location = Point(20, 225);
			lblCount->Size = System::Drawing::Size(600, 24);
			AppSettings::StyleSectionTitle(lblCount);
			this->Controls->Add(lblCount);

			Panel^ gridCard = gcnew Panel();
			gridCard->Location = Point(20, 260);
			gridCard->Size = System::Drawing::Size(this->ClientSize.Width - 40, this->ClientSize.Height - 280);
			gridCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(gridCard, 18, false);
			this->Controls->Add(gridCard);

			dgv = gcnew DataGridView();
			dgv->Location = Point(12, 12);
			dgv->Size = System::Drawing::Size(gridCard->ClientSize.Width - 24, gridCard->ClientSize.Height - 24);
			dgv->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleGrid(dgv);
			dgv->ColumnCount = 5;
			dgv->Columns[0]->Name = AppSettings::Translate(L"Kitobxon", L"Reader", L"Читатель");
			dgv->Columns[1]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
			dgv->Columns[2]->Name = AppSettings::Translate(L"Berilgan sana", L"Issue date", L"Дата выдачи");
			dgv->Columns[3]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
			dgv->Columns[4]->Name = AppSettings::Translate(L"Holati", L"Status", L"Статус");
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
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
								status = AppSettings::Translate(L"⚠️ Muddat o'tgan", L"⚠️ Overdue", L"⚠️ Просрочено");
								rowColor = AppSettings::DarkMode ? Color::FromArgb(88, 42, 42) : Color::FromArgb(254, 226, 226);
							}
						}
						catch (...) {}

						int idx = dgv->Rows->Add(p[0], p[1], p[2], p[3], status);
						dgv->Rows[idx]->DefaultCellStyle->BackColor = rowColor;
						if (status->Contains(L"⚠️")) {
							dgv->Rows[idx]->DefaultCellStyle->ForeColor = AppSettings::DangerColor();
						}
						count++;
					}
				}
			}

			lblCount->Text = String::Format(
				AppSettings::Translate(L"📚 Jami yozuvlar: {0}", L"📚 Total records: {0}", L"📚 Всего записей: {0}"),
				count
			);

			// Add info card below count
			Panel^ infoCard = gcnew Panel();
			infoCard->Location = Point(20, 160);
			infoCard->Size = System::Drawing::Size(this->ClientSize.Width - 40, 50);
			infoCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(infoCard, 14, true);
			
			Label^ infoLabel = gcnew Label();
			infoLabel->Text = AppSettings::Translate(L"⏰ Barcha ijara amallari yotadigan joy", L"⏰ All borrowing operations", L"⏰ Все операции аренды");
			AppSettings::StyleBodyText(infoLabel);
			infoLabel->Dock = DockStyle::Fill;
			infoLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			infoCard->Controls->Add(infoLabel);
			this->Controls->Add(infoCard);
		}
	};
}
