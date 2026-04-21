#pragma once

namespace Yakuniyloyiha {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class SettingsForm : public Form {
	public:
		SettingsForm() {
			this->Text = L"Sozlamalar";
			this->Size = System::Drawing::Size(300, 220);
			this->BackColor = Color::White;
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;

			Label^ lblV = gcnew Label();
			lblV->Text = L"Dastur tili:";
			lblV->Location = Point(20, 20);
			lblV->AutoSize = true;
			lblV->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			this->Controls->Add(lblV);

			ComboBox^ cmb = gcnew ComboBox();
			cmb->Items->Add(L"O'zbekcha");
			cmb->Items->Add(L"English");
			cmb->Items->Add(L"Русский");
			cmb->SelectedIndex = 0;
			cmb->Location = Point(20, 50);
			cmb->Size = System::Drawing::Size(240, 25);
			cmb->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			cmb->DropDownStyle = ComboBoxStyle::DropDownList;
			this->Controls->Add(cmb);

			CheckBox^ chb = gcnew CheckBox();
			chb->Text = L"Tungi rejim (Tez kunda)";
			chb->Location = Point(20, 90);
			chb->Width = 200;
			chb->Enabled = false; // hozircha dark light ishlamaydi
			chb->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
			this->Controls->Add(chb);

			Button^ btnOk = gcnew Button();
			btnOk->Text = L"Saqlash";
			btnOk->Location = Point(100, 130);
			btnOk->Size = System::Drawing::Size(100, 35);
			btnOk->BackColor = Color::FromArgb(40, 44, 52);
			btnOk->ForeColor = Color::White;
			btnOk->FlatStyle = FlatStyle::Flat;
         btnOk->FlatAppearance->BorderSize = 0;
			btnOk->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Controls->Add(btnOk);
		}
	};
}