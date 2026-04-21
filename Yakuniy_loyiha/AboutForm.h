#pragma once

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			this->Text = L"Dastur haqida";
			this->Size = System::Drawing::Size(400, 300);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->BackColor = System::Drawing::Color::White;
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = L"Unilibrary tizimi";
			titleLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 16.0F, System::Drawing::FontStyle::Bold);
			titleLabel->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
			titleLabel->AutoSize = true;
			titleLabel->Location = System::Drawing::Point(30, 30);
			this->Controls->Add(titleLabel);

			Label^ versionLabel = gcnew Label();
			versionLabel->Text = L"Versiya: 1.0.0";
			versionLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
			versionLabel->ForeColor = System::Drawing::Color::FromArgb(108, 117, 125);
			versionLabel->AutoSize = true;
			versionLabel->Location = System::Drawing::Point(30, 70);
			this->Controls->Add(versionLabel);

			Label^ descLabel = gcnew Label();
			descLabel->Text = L"Ushbu dastur talabalar va keng ommaga mo'ljallangan\nbo'lib, kutubxona tizimini qidirish va kitoblarni\nmasofadan bron qilish hamda boshqarish \nuchun xizmat qiladi.";
			descLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
			descLabel->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
			descLabel->AutoSize = true;
			descLabel->Location = System::Drawing::Point(30, 110);
			this->Controls->Add(descLabel);

			Button^ btnClose = gcnew Button();
			btnClose->Text = L"Yopish";
			btnClose->Location = System::Drawing::Point(140, 200);
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
			divider->Location = System::Drawing::Point(30, 92);
			divider->Size = System::Drawing::Size(330, 1);
			this->Controls->Add(divider);
		}
	};
}
