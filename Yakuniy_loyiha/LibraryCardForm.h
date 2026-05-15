#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

using namespace System;
using namespace System::Net;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class LibraryCardForm : public System::Windows::Forms::Form {
public:
    LibraryCardForm(String^ readerToken) {
        _readerToken = readerToken;
        InitializeComponent();
        LoadLibraries();
    }

private:
    String^ _readerToken;

    ComboBox^    cmbLibrary;
    Button^      btnBrowse;
    Button^      btnUpload;
    PictureBox^  picPreview;
    Label^       lblFileName;
    Label^       lblStatus;
    Label^       lblTitle;
    String^      _selectedImagePath;

    void InitializeComponent() {
        this->Text        = "Kutubxona kartasi yuklash";
        this->Size        = System::Drawing::Size(420, 400);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->BackColor   = Color::White;
        this->Font        = gcnew System::Drawing::Font("Segoe UI", 9.5f);

        // Header
        Panel^ header = gcnew Panel();
        header->BackColor = Color::FromArgb(5, 150, 105);
        header->Size = System::Drawing::Size(420, 54);
        header->Location = System::Drawing::Point(0, 0);

        lblTitle = gcnew Label();
        lblTitle->Text      = "Kutubxona kartasi yuklash";
        lblTitle->ForeColor = Color::White;
        lblTitle->Font      = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
        lblTitle->AutoSize  = true;
        lblTitle->Location  = System::Drawing::Point(16, 14);
        header->Controls->Add(lblTitle);
        this->Controls->Add(header);

        int y = 70;

        // Kutubxona
        Label^ lblLib = gcnew Label(); lblLib->Text = "Kutubxona tanlang:";
        lblLib->Location = System::Drawing::Point(16, y); lblLib->AutoSize = true;
        this->Controls->Add(lblLib); y += 22;

        cmbLibrary = gcnew ComboBox();
        cmbLibrary->Location     = System::Drawing::Point(16, y);
        cmbLibrary->Size         = System::Drawing::Size(378, 28);
        cmbLibrary->DropDownStyle= ComboBoxStyle::DropDownList;
        this->Controls->Add(cmbLibrary); y += 42;

        // Rasm tanlash
        Label^ lblImg = gcnew Label(); lblImg->Text = "Karta rasmi:";
        lblImg->Location = System::Drawing::Point(16, y); lblImg->AutoSize = true;
        this->Controls->Add(lblImg); y += 22;

        picPreview = gcnew PictureBox();
        picPreview->Location  = System::Drawing::Point(16, y);
        picPreview->Size      = System::Drawing::Size(200, 120);
        picPreview->SizeMode  = PictureBoxSizeMode::Zoom;
        picPreview->BackColor = Color::FromArgb(241, 245, 249);
        picPreview->BorderStyle = BorderStyle::FixedSingle;
        this->Controls->Add(picPreview);

        btnBrowse = gcnew Button();
        btnBrowse->Text      = "Rasm tanlash...";
        btnBrowse->Location  = System::Drawing::Point(226, y);
        btnBrowse->Size      = System::Drawing::Size(168, 36);
        btnBrowse->BackColor = Color::FromArgb(241, 245, 249);
        btnBrowse->FlatStyle = FlatStyle::Flat;
        btnBrowse->FlatAppearance->BorderColor = Color::FromArgb(203, 213, 225);
        btnBrowse->Cursor    = Cursors::Hand;
        btnBrowse->Click    += gcnew EventHandler(this, &LibraryCardForm::OnBrowseClick);
        this->Controls->Add(btnBrowse);

        lblFileName = gcnew Label();
        lblFileName->Text     = "Fayl tanlanmagan";
        lblFileName->Location = System::Drawing::Point(226, y + 44);
        lblFileName->Size     = System::Drawing::Size(168, 36);
        lblFileName->ForeColor= Color::FromArgb(148, 163, 184);
        lblFileName->Font     = gcnew System::Drawing::Font("Segoe UI", 8.5f);
        this->Controls->Add(lblFileName);

        y += 136;

        lblStatus = gcnew Label();
        lblStatus->Location = System::Drawing::Point(16, y);
        lblStatus->Size     = System::Drawing::Size(378, 24);
        lblStatus->Font     = gcnew System::Drawing::Font("Segoe UI", 9.0f);
        this->Controls->Add(lblStatus); y += 30;

        btnUpload = gcnew Button();
        btnUpload->Text      = "Yuklash";
        btnUpload->Location  = System::Drawing::Point(16, y);
        btnUpload->Size      = System::Drawing::Size(180, 38);
        btnUpload->BackColor = Color::FromArgb(5, 150, 105);
        btnUpload->ForeColor = Color::White;
        btnUpload->FlatStyle = FlatStyle::Flat;
        btnUpload->FlatAppearance->BorderSize = 0;
        btnUpload->Font      = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnUpload->Cursor    = Cursors::Hand;
        btnUpload->Enabled   = false;
        btnUpload->Click    += gcnew EventHandler(this, &LibraryCardForm::OnUploadClick);
        this->Controls->Add(btnUpload);

        Button^ btnClose = gcnew Button();
        btnClose->Text      = "Yopish";
        btnClose->Location  = System::Drawing::Point(210, y);
        btnClose->Size      = System::Drawing::Size(184, 38);
        btnClose->BackColor = Color::FromArgb(241, 245, 249);
        btnClose->FlatStyle = FlatStyle::Flat;
        btnClose->FlatAppearance->BorderColor = Color::FromArgb(203, 213, 225);
        btnClose->Cursor    = Cursors::Hand;
        btnClose->Click    += gcnew EventHandler(this, &LibraryCardForm::OnCloseClick);
        this->Controls->Add(btnClose);
    }

    void LoadLibraries() {
        try {
            String^ url = AppSettings::GetApiBase() + "/api/libraries/";
            auto req = (HttpWebRequest^)WebRequest::Create(url);
            req->Method = "GET"; req->Timeout = 6000;
            auto resp = (HttpWebResponse^)req->GetResponse();
            auto rd = gcnew StreamReader(resp->GetResponseStream(), Encoding::UTF8);
            String^ json = rd->ReadToEnd();

            // Simple JSON array parse for id and name
            cmbLibrary->Items->Clear();
            cmbLibrary->Items->Add("— Kutubxona tanlang —");
            cmbLibrary->SelectedIndex = 0;

            array<String^>^ parts = json->Split(gcnew array<String^>{"{\"id\":"}, StringSplitOptions::RemoveEmptyEntries);
            for (int i = 1; i < parts->Length; i++) {
                int commaIdx = parts[i]->IndexOf(",");
                String^ id = commaIdx > 0 ? parts[i]->Substring(0, commaIdx)->Trim() : "";
                int nameStart = parts[i]->IndexOf("\"name\":\"");
                if (nameStart < 0) continue;
                nameStart += 8;
                int nameEnd = parts[i]->IndexOf("\"", nameStart);
                String^ name = nameEnd > nameStart ? parts[i]->Substring(nameStart, nameEnd - nameStart) : "";
                if (id->Length > 0 && name->Length > 0)
                    cmbLibrary->Items->Add(id + "|" + name);
            }
        } catch (...) {
            cmbLibrary->Items->Add("— Kutubxonalar yuklanmadi —");
            cmbLibrary->SelectedIndex = 0;
        }
    }

    void OnBrowseClick(Object^ sender, EventArgs^ e) {
        OpenFileDialog^ dlg = gcnew OpenFileDialog();
        dlg->Filter = "Rasmlar (*.jpg;*.jpeg;*.png)|*.jpg;*.jpeg;*.png";
        dlg->Title  = "Karta rasmi tanlang";
        if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            _selectedImagePath = dlg->FileName;
            lblFileName->Text  = Path::GetFileName(dlg->FileName);
            try {
                picPreview->Image = Image::FromFile(dlg->FileName);
            } catch (...) {}
            btnUpload->Enabled = (cmbLibrary->SelectedIndex > 0);
            lblStatus->Text = "";
        }
    }

    void OnUploadClick(Object^ sender, EventArgs^ e) {
        if (cmbLibrary->SelectedIndex <= 0) {
            lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
            lblStatus->Text = "Kutubxona tanlanmagan.";
            return;
        }
        if (String::IsNullOrEmpty(_selectedImagePath)) {
            lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
            lblStatus->Text = "Rasm tanlanmagan.";
            return;
        }

        String^ selected = cmbLibrary->SelectedItem->ToString();
        int pipeIdx = selected->IndexOf("|");
        String^ libraryId = pipeIdx > 0 ? selected->Substring(0, pipeIdx) : "";

        try {
            btnUpload->Enabled = false;
            lblStatus->ForeColor = Color::FromArgb(37, 99, 235);
            lblStatus->Text = "Yuklanmoqda...";

            auto imgBytes = File::ReadAllBytes(_selectedImagePath);
            String^ ext = Path::GetExtension(_selectedImagePath)->ToLower()->TrimStart('.');
            String^ base64 = "data:image/" + (ext == "jpg" ? "jpeg" : ext) + ";base64," +
                              System::Convert::ToBase64String(imgBytes);

            String^ json = "{\"library\":" + libraryId + ",\"card_image_base64\":\"" + base64 + "\"}";
            String^ apiUrl = AppSettings::GetApiBase() + "/api/readers/library-cards/";

            auto req = (HttpWebRequest^)WebRequest::Create(apiUrl);
            req->Method      = "POST";
            req->ContentType = "application/json";
            req->Timeout     = 30000;
            req->Headers->Add("X-Reader-Token", _readerToken);
            auto bytes = Encoding::UTF8->GetBytes(json);
            req->ContentLength = bytes->Length;
            auto stream = req->GetRequestStream();
            stream->Write(bytes, 0, bytes->Length);
            stream->Close();

            int statusCode = 200;
            String^ respBody = "";
            try {
                auto resp = (HttpWebResponse^)req->GetResponse();
                statusCode = (int)resp->StatusCode;
                auto rd = gcnew StreamReader(resp->GetResponseStream(), Encoding::UTF8);
                respBody = rd->ReadToEnd();
            } catch (WebException^ we) {
                if (we->Response != nullptr) {
                    statusCode = (int)((HttpWebResponse^)we->Response)->StatusCode;
                    auto rd = gcnew StreamReader(we->Response->GetResponseStream(), Encoding::UTF8);
                    respBody = rd->ReadToEnd();
                }
            }

            if (statusCode == 200 || statusCode == 201) {
                lblStatus->ForeColor = Color::FromArgb(5, 150, 105);
                lblStatus->Text = "Karta muvaffaqiyatli yuklandi! Admin tasdig'ini kuting.";
                btnUpload->Enabled = false;
            } else {
                String^ err = GetJsonValue(respBody, "detail");
                if (err->Length == 0) err = "Yuklashda xato yuz berdi.";
                lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
                lblStatus->Text = err;
                btnUpload->Enabled = true;
            }
        } catch (Exception^ ex) {
            lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
            lblStatus->Text = "Xato: " + ex->Message;
            btnUpload->Enabled = true;
        }
    }

    void OnCloseClick(Object^ sender, EventArgs^ e) { this->Close(); }

    String^ GetJsonValue(String^ json, String^ key) {
        String^ search = "\"" + key + "\":\"";
        int idx = json->IndexOf(search);
        if (idx < 0) return "";
        idx += search->Length;
        int end = json->IndexOf("\"", idx);
        if (end < 0) return "";
        return json->Substring(idx, end - idx);
    }
};

} // namespace Yakuniyloyiha
