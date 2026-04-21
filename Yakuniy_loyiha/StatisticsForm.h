#pragma once

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class StatisticsForm : public System::Windows::Forms::Form
	{
	public:
		StatisticsForm(void)
		{
			this->Text = L"Statistika";
			this->Size = System::Drawing::Size(400, 350);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = System::Drawing::Color::White;
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = L"Tizim Statistikasi";
			titleLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 16.0F, System::Drawing::FontStyle::Bold);
			titleLabel->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
			titleLabel->AutoSize = true;
			titleLabel->Location = System::Drawing::Point(30, 30);
			this->Controls->Add(titleLabel);

			int books = File::Exists("books.txt") ? File::ReadAllLines("books.txt")->Length : 0;
			int readers = File::Exists("readers.txt") ? File::ReadAllLines("readers.txt")->Length : 0;
			int issues = File::Exists("issues.txt") ? File::ReadAllLines("issues.txt")->Length : 0;
			int libraries = File::Exists("libraries.txt") ? File::ReadAllLines("libraries.txt")->Length : 0;

			int y = 90;
			AddStatRow(L"📚 Barcha kitoblar soni:", books.ToString(), y); y += 30;
			AddStatRow(L"🏢 Kutubxonalar soni:", libraries.ToString(), y); y += 30;
			AddStatRow(L"👥 Faol kitobxonlar:", readers.ToString(), y); y += 30;
			AddStatRow(L"⏳ Ijaradagi kitoblar:", issues.ToString(), y); y += 30;

			Button^ btnClose = gcnew Button();
			btnClose->Text = L"Yopish";
			btnClose->Location = System::Drawing::Point(140, y + 30);
			btnClose->Size = System::Drawing::Size(100, 35);
			btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			btnClose->FlatAppearance->BorderSize = 0;
			btnClose->BackColor = System::Drawing::Color::FromArgb(40, 44, 52);
			btnClose->ForeColor = System::Drawing::Color::White;
			btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold);
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Controls->Add(btnClose);

			Panel^ divider = gcnew Panel();
			divider->BackColor = System::Drawing::Color::FromArgb(230, 230, 230);
			divider->Location = System::Drawing::Point(30, 80);
			divider->Size = System::Drawing::Size(330, 1);
			this->Controls->Add(divider);
		}

	private:
		void AddStatRow(String^ label, String^ val, int yPos) {
			Label^ lbl = gcnew Label();
			lbl->Text = label;
			lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
			lbl->ForeColor = System::Drawing::Color::FromArgb(108, 117, 125);
			lbl->AutoSize = true;
			lbl->Location = System::Drawing::Point(30, yPos);
			this->Controls->Add(lbl);

			Label^ valLbl = gcnew Label();
			valLbl->Text = val;
			valLbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold);
			valLbl->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
			valLbl->AutoSize = true;
			valLbl->Location = System::Drawing::Point(230, yPos);
			this->Controls->Add(valLbl);
		}
	};
}
