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
		Label^ lblStatus;
	public:
		ReaderForm() {
			this->Text = AppSettings::Translate(L"O'quvchi paneli", L"Reader panel", L"Панель читателя");
			this->Size = System::Drawing::Size(760, 500);
			this->BackColor = AppSettings::PageBackColor();
			this->StartPosition = FormStartPosition::CenterParent;
			this->MinimumSize = System::Drawing::Size(700, 460);

			Panel^ hero = gcnew Panel();
			hero->Location = Point(22, 20);
			hero->Size = System::Drawing::Size(700, 112);
			hero->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			hero->BackColor = AppSettings::PrimaryColor();
			AppSettings::MakeRounded(hero, 8);
			this->Controls->Add(hero);

			Label^ title = gcnew Label();
			title->Text = AppSettings::Translate(L"O'quvchi kabineti", L"Reader dashboard", L"Кабинет читателя");
			title->Location = Point(22, 18);
			title->Size = System::Drawing::Size(420, 38);
			title->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 19.0F, FontStyle::Bold);
			title->ForeColor = Color::White;
			title->BackColor = Color::Transparent;
			hero->Controls->Add(title);

			Label^ hint = gcnew Label();
			hint->Text = AppSettings::Translate(L"Ismingizni kiriting va ijaradagi kitoblaringizni kuzating", L"Enter your name and track borrowed books", L"Введите имя и отслеживайте выданные книги");
			hint->Location = Point(24, 58);
			hint->Size = System::Drawing::Size(620, 24);
			hint->ForeColor = Color::FromArgb(219, 234, 254);
			hint->BackColor = Color::Transparent;
			hero->Controls->Add(hint);

			Panel^ searchCard = gcnew Panel();
			searchCard->Location = Point(22, 150);
			searchCard->Size = System::Drawing::Size(700, 72);
			searchCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			searchCard->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(searchCard, 8);
			this->Controls->Add(searchCard);

			Label^ l = gcnew Label();
			l->Text = AppSettings::Translate(L"F.I.Sh", L"Full name", L"ФИО");
			l->Location = Point(18, 12);
			l->Size = System::Drawing::Size(110, 22);
			l->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			l->ForeColor = AppSettings::TextColor();
			searchCard->Controls->Add(l);

			txtID = gcnew TextBox();
			txtID->Location = Point(18, 36);
			txtID->Size = System::Drawing::Size(450, 28);
			AppSettings::StyleInput(txtID);
			searchCard->Controls->Add(txtID);

			btnLogin = gcnew Button();
			btnLogin->Text = AppSettings::Translate(L"Ko'rish", L"View", L"Открыть");
			btnLogin->Location = Point(490, 32);
			btnLogin->Size = System::Drawing::Size(184, 34);
			AppSettings::StyleButton(btnLogin, AppSettings::PrimaryColor(), Color::White);
			btnLogin->Click += gcnew EventHandler(this, &ReaderForm::btnLogin_Click);
			searchCard->Controls->Add(btnLogin);

			lblStatus = gcnew Label();
			lblStatus->Text = AppSettings::Translate(L"Natijalar shu yerda ko'rinadi", L"Results will appear here", L"Результаты появятся здесь");
			lblStatus->Location = Point(24, 238);
			lblStatus->Size = System::Drawing::Size(650, 24);
			lblStatus->ForeColor = AppSettings::MutedTextColor();
			this->Controls->Add(lblStatus);

			Panel^ gridCard = gcnew Panel();
			gridCard->Location = Point(22, 270);
			gridCard->Size = System::Drawing::Size(700, 180);
			gridCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			gridCard->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(gridCard, 8);
			this->Controls->Add(gridCard);

			dgv = gcnew DataGridView();
			dgv->Location = Point(12, 12);
			dgv->Size = System::Drawing::Size(676, 156);
			dgv->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::StyleGrid(dgv);
			dgv->ColumnCount = 3;
			dgv->Columns[0]->Name = AppSettings::Translate(L"Kitob nomi", L"Book title", L"Название книги");
			dgv->Columns[1]->Name = AppSettings::Translate(L"Olingan sana", L"Issue date", L"Дата выдачи");
			dgv->Columns[2]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
			gridCard->Controls->Add(dgv);
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

			lblStatus->Text = String::Format(
				AppSettings::Translate(L"Topilgan ijaralar: {0}", L"Borrowed books found: {0}", L"Найдено выдач: {0}"),
				dgv->Rows->Count
			);

			if (dgv->Rows->Count == 0) {
				MessageBox::Show(
					AppSettings::Translate(L"Sizda ijaraga olingan kitoblar topilmadi.", L"No borrowed books were found.", L"У вас нет взятых книг."),
					AppSettings::Translate(L"Xabar", L"Info", L"Инфо")
				);
			}
		}
	};
}
