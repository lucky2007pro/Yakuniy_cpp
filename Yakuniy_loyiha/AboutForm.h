#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			this->Text = AppSettings::Translate(L"Dastur haqida", L"About app", L"О программе");
			this->Size = System::Drawing::Size(520, 390);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			Panel^ hero = gcnew Panel();
			hero->Location = Point(18, 18);
			hero->Size = System::Drawing::Size(468, 128);
			hero->BackColor = AppSettings::PrimaryColor();
			AppSettings::MakeRounded(hero, 8);
			this->Controls->Add(hero);

			Label^ badge = gcnew Label();
			badge->Text = AppSettings::Translate(L"UNILIBRARY", L"UNILIBRARY", L"UNILIBRARY");
			badge->AutoSize = true;
			badge->ForeColor = Color::FromArgb(219, 234, 254);
			badge->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 9.0F, FontStyle::Bold);
			badge->Location = Point(24, 18);
			badge->BackColor = Color::Transparent;
			hero->Controls->Add(badge);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = AppSettings::Translate(L"Kutubxona tajribasi yangi darajada", L"A better library experience", L"Новый уровень библиотеки");
			titleLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 18.0F, FontStyle::Bold);
			titleLabel->ForeColor = Color::White;
			titleLabel->Location = Point(22, 42);
			titleLabel->Size = System::Drawing::Size(420, 44);
			titleLabel->BackColor = Color::Transparent;
			hero->Controls->Add(titleLabel);

			Label^ versionLabel = gcnew Label();
			versionLabel->Text = AppSettings::Translate(L"Versiya 1.0.0  •  masofadan band qilish", L"Version 1.0.0  •  remote reservations", L"Версия 1.0.0  •  удаленная бронь");
			versionLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			versionLabel->ForeColor = Color::FromArgb(219, 234, 254);
			versionLabel->Location = Point(24, 88);
			versionLabel->Size = System::Drawing::Size(420, 24);
			versionLabel->BackColor = Color::Transparent;
			hero->Controls->Add(versionLabel);

			Panel^ card = gcnew Panel();
			card->Location = Point(18, 164);
			card->Size = System::Drawing::Size(468, 128);
			card->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(card, 8);
			this->Controls->Add(card);

			Label^ descLabel = gcnew Label();
			descLabel->Text = AppSettings::Translate(
				L"Talabalar va kitobxonlar kitob qidirishi, yaqin kutubxonani ko'rishi, e-kitoblarni ochishi va band qilish jarayonini tez bajarishi uchun yaratilgan.",
				L"Built so readers can search books, find nearby libraries, open e-books, and reserve titles quickly.",
				L"Создано для поиска книг, ближайших библиотек, открытия электронных книг и быстрого бронирования."
			);
			descLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
			descLabel->ForeColor = AppSettings::MutedTextColor();
			descLabel->Location = Point(22, 20);
			descLabel->Size = System::Drawing::Size(420, 58);
			card->Controls->Add(descLabel);

			Label^ featureLabel = gcnew Label();
			featureLabel->Text = AppSettings::Translate(L"Qidiruv  •  yo'nalish  •  bron  •  statistika", L"Search  •  route  •  reserve  •  statistics", L"Поиск  •  маршрут  •  бронь  •  статистика");
			featureLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			featureLabel->ForeColor = AppSettings::TextColor();
			featureLabel->Location = Point(22, 88);
			featureLabel->Size = System::Drawing::Size(420, 22);
			card->Controls->Add(featureLabel);

			Button^ btnClose = gcnew Button();
			btnClose->Text = AppSettings::Translate(L"Yopish", L"Close", L"Закрыть");
			btnClose->Location = Point(366, 310);
			btnClose->Size = System::Drawing::Size(120, 36);
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			AppSettings::StyleButton(btnClose, AppSettings::PrimaryColor(), Color::White);
			this->Controls->Add(btnClose);
		}
	};
}
