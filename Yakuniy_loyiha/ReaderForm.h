#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class ReaderForm : public Form {
		TextBox^ txtID;
		Button^ btnSearch;
		DataGridView^ dgv;
		Label^ lblStatus;
	public:
		ReaderForm() {
			this->Text = AppSettings::Translate(L"O'quvchi paneli", L"Reader panel", L"Панель читателя");
			this->Size = System::Drawing::Size(900, 750);
			this->BackColor = AppSettings::PageBackColor();
			this->StartPosition = FormStartPosition::CenterParent;
			this->MinimumSize = System::Drawing::Size(800, 680);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

			// === MODERN HEADER ===
			Panel^ header = gcnew Panel();
			header->Location = Point(0, 0);
			header->Size = System::Drawing::Size(this->ClientSize.Width, 160);
			header->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::EnableGradientBackground(header, AppSettings::GradientAccentStart(), AppSettings::GradientWarmEnd());

			Panel^ iconBadge = gcnew Panel();
			iconBadge->Location = Point(20, 20);
			iconBadge->Size = System::Drawing::Size(78, 78);
			iconBadge->BackColor = Color::FromArgb(235, 255, 255, 255);
			AppSettings::MakeRounded(iconBadge, 39);
			header->Controls->Add(iconBadge);

			Label^ iconLabel = gcnew Label();
			iconLabel->Text = L"👤";
			iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 38.0F);
			iconLabel->Dock = DockStyle::Fill;
			iconLabel->TextAlign = ContentAlignment::MiddleCenter;
			iconLabel->ForeColor = AppSettings::TextColor();
			iconLabel->BackColor = Color::Transparent;
			iconBadge->Controls->Add(iconLabel);

			Label^ title = gcnew Label();
			title->Text = AppSettings::Translate(L"O'quvchi paneli", L"Reader panel", L"Панель читателя");
			title->Location = Point(116, 26);
			title->Size = System::Drawing::Size(520, 40);
			AppSettings::StyleHeaderTitle(title);
			header->Controls->Add(title);

			Label^ subtitle = gcnew Label();
			subtitle->Text = AppSettings::Translate(L"O'z kitoblaringizni kuzating va boshqarishni osonlashtiring", L"Track your books and manage borrowings easily", L"Отслеживайте книги и управляйте ими");
			AppSettings::StyleHeaderSubtitle(subtitle);
			subtitle->Location = Point(118, 68);
			subtitle->Size = System::Drawing::Size(560, 34);
			header->Controls->Add(subtitle);

			this->Controls->Add(header);

			// === SEARCH SECTION ===
			Panel^ searchCard = gcnew Panel();
			searchCard->Location = Point(20, 190);
			searchCard->Size = System::Drawing::Size(this->ClientSize.Width - 40, 120);
			searchCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(searchCard, 18, false);
			System::Windows::Forms::Padding^ p = gcnew System::Windows::Forms::Padding(20);
			searchCard->Padding = *p;
			this->Controls->Add(searchCard);

			Label^ lblSearch = gcnew Label();
			lblSearch->Text = AppSettings::Translate(L"👤 Ismingiz", L"👤 Your name", L"👤 Ваше имя");
			lblSearch->Location = Point(14, 10);
			lblSearch->Size = System::Drawing::Size(400, 28);
			AppSettings::StyleSectionTitle(lblSearch);
			lblSearch->AutoSize = true;
			searchCard->Controls->Add(lblSearch);

			Label^ hint = gcnew Label();
			hint->Text = AppSettings::Translate(L"O'quvchi nomi kiriting (to'liq yoki qismiy)", L"Enter reader name (full or partial)", L"Введите имя читателя");
			hint->Location = Point(14, 40);
			hint->Size = System::Drawing::Size(400, 20);
			AppSettings::StyleBodyText(hint);
			hint->AutoSize = true;
			searchCard->Controls->Add(hint);

			txtID = gcnew TextBox();
			txtID->Location = Point(14, 64);
			txtID->Size = System::Drawing::Size(this->ClientSize.Width - 140, 36);
			txtID->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
			AppSettings::StyleInput(txtID);
			searchCard->Controls->Add(txtID);

			btnSearch = gcnew Button();
			btnSearch->Text = AppSettings::Translate(L"🔍 Qidiruv", L"🔍 Search", L"🔍 Поиск");
			btnSearch->Location = Point(this->ClientSize.Width - 110, 64);
			btnSearch->Size = System::Drawing::Size(90, 36);
			AppSettings::StyleModernButton(btnSearch, true);
			btnSearch->Click += gcnew EventHandler(this, &ReaderForm::btnSearch_Click);
			searchCard->Controls->Add(btnSearch);

			// === STATUS ===
			lblStatus = gcnew Label();
			lblStatus->Text = AppSettings::Translate(L"🔍 Qidirish natijalarini shu yerda ko'rasiz", L"🔍 Search results will appear below", L"🔍 Результаты появятся ниже");
			lblStatus->Location = Point(20, 320);
			lblStatus->Size = System::Drawing::Size(800, 24);
			AppSettings::StyleBodyText(lblStatus);
			this->Controls->Add(lblStatus);

			// Add info card
			Panel^ infoCard = gcnew Panel();
			infoCard->Location = Point(20, 350);
			infoCard->Size = System::Drawing::Size(this->ClientSize.Width - 40, 50);
			infoCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(infoCard, 14, true);
			
			Label^ infoLabel = gcnew Label();
			infoLabel->Text = AppSettings::Translate(L"ℹ️ Qidirish natijalarini tez ko'rish uchun ismingiz uchun qismiy nom ham kiritishingiz mumkin", L"ℹ️ You can use partial names for faster results", L"ℹ️ Используйте частичные имена");
			AppSettings::StyleBodyText(infoLabel);
			infoLabel->Dock = DockStyle::Fill;
			infoLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			infoCard->Controls->Add(infoLabel);
			this->Controls->Add(infoCard);

			// === RESULTS GRID ===
			Panel^ gridCard = gcnew Panel();
			gridCard->Location = Point(20, 414);
			gridCard->Size = System::Drawing::Size(this->ClientSize.Width - 40, this->ClientSize.Height - 454);
			gridCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleSurfacePanel(gridCard, 18, false);
			this->Controls->Add(gridCard);

			dgv = gcnew DataGridView();
			dgv->Location = Point(12, 12);
			dgv->Size = System::Drawing::Size(this->ClientSize.Width - 64, this->ClientSize.Height - 478);
			dgv->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleGrid(dgv);
			dgv->ColumnCount = 3;
			dgv->Columns[0]->Name = AppSettings::Translate(L"📚 Kitob nomi", L"📚 Book title", L"📚 Название");
			dgv->Columns[1]->Name = AppSettings::Translate(L"📅 Olingan sana", L"📅 Issue date", L"📅 Дата выдачи");
			dgv->Columns[2]->Name = AppSettings::Translate(L"⏳ Qaytarish muddati", L"⏳ Return date", L"⏳ Срок возврата");
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			gridCard->Controls->Add(dgv);
		}

	private:
		void btnSearch_Click(Object^ sender, EventArgs^ e) {
			dgv->Rows->Clear();
			String^ rname = txtID->Text->ToLower();
			if (String::IsNullOrWhiteSpace(rname)) {
				MessageBox::Show(
					AppSettings::Translate(L"Iltimos, ismingizni kiriting.", L"Please enter your name.", L"Пожалуйста, введите имя."),
					AppSettings::Translate(L"Ehtiyoj", L"Required", L"Требуется")
				);
				return;
			}

			int found = 0;
			if (File::Exists("issues.txt")) {
				array<String^>^ lines = File::ReadAllLines("issues.txt");
				for each (String^ line in lines) {
					array<String^>^ p = line->Split('|');
					if (p->Length >= 4 && p[0]->ToLower()->Contains(rname)) {
						dgv->Rows->Add(p[1], p[2], p[3]);
						found++;
					}
				}
			}

			lblStatus->Text = String::Format(
				AppSettings::Translate(L"📖 Topilgan ijara: {0}", L"📖 Found borrowings: {0}", L"📖 Найдено выдач: {0}"),
				found
			);

			if (found == 0) {
				MessageBox::Show(
					AppSettings::Translate(L"Sizga tegishli ijaralar topilmadi.", L"No borrowings found for you.", L"Для вас не найдено выдач."),
					AppSettings::Translate(L"Natija yo'q", L"No results", L"Нет результатов")
				);
			}
		}
	};
}
