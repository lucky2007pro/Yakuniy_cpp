#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class StatisticsForm : public System::Windows::Forms::Form
	{
	public:
		StatisticsForm(void)
		{
			this->Text = AppSettings::Translate(L"Statistika", L"Statistics", L"Статистика");
			this->Size = System::Drawing::Size(560, 430);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = AppSettings::Translate(L"Tizim statistikasi", L"System statistics", L"Статистика системы");
			titleLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 20.0F, FontStyle::Bold);
			titleLabel->ForeColor = AppSettings::TextColor();
			titleLabel->Location = Point(24, 24);
			titleLabel->Size = System::Drawing::Size(480, 42);
			this->Controls->Add(titleLabel);

			Label^ subtitle = gcnew Label();
			subtitle->Text = AppSettings::Translate(L"Kutubxona faoliyati bo'yicha tezkor ko'rsatkichlar", L"Quick indicators for library activity", L"Быстрые показатели активности библиотеки");
			subtitle->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
			subtitle->ForeColor = AppSettings::MutedTextColor();
			subtitle->Location = Point(26, 66);
			subtitle->Size = System::Drawing::Size(480, 24);
			this->Controls->Add(subtitle);

			int books = File::Exists("books.txt") ? File::ReadAllLines("books.txt")->Length : 0;
			int readers = File::Exists("readers.txt") ? File::ReadAllLines("readers.txt")->Length : 0;
			int issues = File::Exists("issues.txt") ? File::ReadAllLines("issues.txt")->Length : 0;
			int libraries = File::Exists("libraries.txt") ? File::ReadAllLines("libraries.txt")->Length : 0;

			AddStatCard(AppSettings::Translate(L"Kitoblar", L"Books", L"Книги"), books.ToString(), Point(24, 112), AppSettings::PrimaryColor());
			AddStatCard(AppSettings::Translate(L"Kutubxonalar", L"Libraries", L"Библиотеки"), libraries.ToString(), Point(282, 112), Color::FromArgb(14, 165, 233));
			AddStatCard(AppSettings::Translate(L"Kitobxonlar", L"Readers", L"Читатели"), readers.ToString(), Point(24, 232), AppSettings::SuccessColor());
			AddStatCard(AppSettings::Translate(L"Ijaralar", L"Borrowed", L"Аренда"), issues.ToString(), Point(282, 232), AppSettings::WarningColor());

			Button^ btnClose = gcnew Button();
			btnClose->Text = AppSettings::Translate(L"Yopish", L"Close", L"Закрыть");
			btnClose->Location = Point(400, 350);
			btnClose->Size = System::Drawing::Size(120, 36);
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			AppSettings::StyleButton(btnClose, AppSettings::PrimaryColor(), Color::White);
			this->Controls->Add(btnClose);
		}

	private:
		void AddStatCard(String^ label, String^ val, Point location, Color accent) {
			Panel^ card = gcnew Panel();
			card->Location = location;
			card->Size = System::Drawing::Size(238, 96);
			card->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(card, 8);
			this->Controls->Add(card);

			Panel^ accentBar = gcnew Panel();
			accentBar->Location = Point(0, 0);
			accentBar->Size = System::Drawing::Size(6, 96);
			accentBar->BackColor = accent;
			card->Controls->Add(accentBar);

			Label^ lbl = gcnew Label();
			lbl->Text = label;
			lbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.5F, FontStyle::Bold);
			lbl->ForeColor = AppSettings::MutedTextColor();
			lbl->Location = Point(20, 16);
			lbl->Size = System::Drawing::Size(190, 24);
			card->Controls->Add(lbl);

			Label^ valLbl = gcnew Label();
			valLbl->Text = val;
			valLbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 25.0F, FontStyle::Bold);
			valLbl->ForeColor = AppSettings::TextColor();
			valLbl->Location = Point(18, 42);
			valLbl->Size = System::Drawing::Size(190, 44);
			card->Controls->Add(valLbl);
		}
	};
}
