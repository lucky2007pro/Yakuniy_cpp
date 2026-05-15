#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

using namespace System;
using namespace System::Net;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics;

public ref class BookDetailForm : public System::Windows::Forms::Form {
public:
    // Konstruktor: kitob ma'lumotlari bilan chaqiriladi
    BookDetailForm(String^ bookId, String^ readerToken) {
        _bookId      = bookId;
        _readerToken = readerToken;
        InitializeComponent();
        LoadBookDetails();
    }

private:
    String^ _bookId;
    String^ _readerToken;

    Panel^       headerPanel;
    Label^       lblTitle;
    Label^       lblAuthor;
    Label^       lblLibrary;
    Label^       lblSection;
    Label^       lblRating;
    Label^       lblViews;
    Label^       lblAvailable;
    RichTextBox^ rtbDescription;
    Button^      btnReserve;
    Button^      btnReadEbook;
    Label^       lblStatus;
    PictureBox^  picCover;

    void InitializeComponent() {
        this->Text        = "Kitob haqida";
        this->Size        = System::Drawing::Size(560, 520);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->BackColor   = Color::FromArgb(248, 250, 252);
        this->Font        = gcnew System::Drawing::Font("Segoe UI", 9.5f);

        // ── Header ──
        headerPanel = gcnew Panel();
        headerPanel->BackColor = Color::FromArgb(37, 99, 235);
        headerPanel->Size      = System::Drawing::Size(560, 60);
        headerPanel->Location  = System::Drawing::Point(0, 0);

        lblTitle = gcnew Label();
        lblTitle->Text      = "Yuklanmoqda...";
        lblTitle->ForeColor = Color::White;
        lblTitle->Font      = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
        lblTitle->Location  = System::Drawing::Point(16, 8);
        lblTitle->Size      = System::Drawing::Size(520, 26);
        headerPanel->Controls->Add(lblTitle);

        lblAuthor = gcnew Label();
        lblAuthor->ForeColor = Color::FromArgb(186, 213, 255);
        lblAuthor->Font      = gcnew System::Drawing::Font("Segoe UI", 9.0f);
        lblAuthor->Location  = System::Drawing::Point(17, 34);
        lblAuthor->Size      = System::Drawing::Size(520, 20);
        headerPanel->Controls->Add(lblAuthor);

        this->Controls->Add(headerPanel);

        // ── Rasm ──
        picCover = gcnew PictureBox();
        picCover->Location  = System::Drawing::Point(16, 72);
        picCover->Size      = System::Drawing::Size(100, 130);
        picCover->SizeMode  = PictureBoxSizeMode::Zoom;
        picCover->BackColor = Color::FromArgb(226, 232, 240);
        this->Controls->Add(picCover);

        // ── Ma'lumotlar ──
        int lx = 128, y = 76;

        lblLibrary = MakeInfoLabel(lx, y, "Kutubxona: —"); y += 26;
        lblSection = MakeInfoLabel(lx, y, "Bo'lim: —"); y += 26;
        lblRating  = MakeInfoLabel(lx, y, "Reyting: —"); y += 26;
        lblViews   = MakeInfoLabel(lx, y, "Ko'rishlar: —"); y += 26;
        lblAvailable= MakeInfoLabel(lx, y, "Holat: —"); y += 26;

        // ── Tavsif ──
        Label^ lblDesc = gcnew Label();
        lblDesc->Text     = "Tavsif:";
        lblDesc->Location = System::Drawing::Point(16, 214);
        lblDesc->AutoSize = true;
        lblDesc->Font     = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
        this->Controls->Add(lblDesc);

        rtbDescription = gcnew RichTextBox();
        rtbDescription->Location  = System::Drawing::Point(16, 234);
        rtbDescription->Size      = System::Drawing::Size(520, 120);
        rtbDescription->ReadOnly  = true;
        rtbDescription->BackColor = Color::White;
        rtbDescription->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        rtbDescription->Font      = gcnew System::Drawing::Font("Segoe UI", 9.5f);
        this->Controls->Add(rtbDescription);

        // ── Status label ──
        lblStatus = gcnew Label();
        lblStatus->Location  = System::Drawing::Point(16, 364);
        lblStatus->Size      = System::Drawing::Size(520, 24);
        lblStatus->ForeColor = Color::FromArgb(37, 99, 235);
        lblStatus->Font      = gcnew System::Drawing::Font("Segoe UI", 9.0f);
        this->Controls->Add(lblStatus);

        // ── Tugmalar ──
        btnReserve = gcnew Button();
        btnReserve->Text      = "Bron qilish";
        btnReserve->Location  = System::Drawing::Point(16, 396);
        btnReserve->Size      = System::Drawing::Size(150, 38);
        btnReserve->BackColor = Color::FromArgb(37, 99, 235);
        btnReserve->ForeColor = Color::White;
        btnReserve->FlatStyle = FlatStyle::Flat;
        btnReserve->FlatAppearance->BorderSize = 0;
        btnReserve->Font      = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnReserve->Cursor    = Cursors::Hand;
        btnReserve->Enabled   = false;
        btnReserve->Click    += gcnew EventHandler(this, &BookDetailForm::OnReserveClick);
        this->Controls->Add(btnReserve);

        btnReadEbook = gcnew Button();
        btnReadEbook->Text      = "E-kitob o'qish";
        btnReadEbook->Location  = System::Drawing::Point(178, 396);
        btnReadEbook->Size      = System::Drawing::Size(150, 38);
        btnReadEbook->BackColor = Color::FromArgb(5, 150, 105);
        btnReadEbook->ForeColor = Color::White;
        btnReadEbook->FlatStyle = FlatStyle::Flat;
        btnReadEbook->FlatAppearance->BorderSize = 0;
        btnReadEbook->Font      = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnReadEbook->Cursor    = Cursors::Hand;
        btnReadEbook->Enabled   = false;
        btnReadEbook->Click    += gcnew EventHandler(this, &BookDetailForm::OnEbookClick);
        this->Controls->Add(btnReadEbook);

        Button^ btnClose = gcnew Button();
        btnClose->Text      = "Yopish";
        btnClose->Location  = System::Drawing::Point(390, 396);
        btnClose->Size      = System::Drawing::Size(148, 38);
        btnClose->BackColor = Color::FromArgb(241, 245, 249);
        btnClose->ForeColor = Color::FromArgb(71, 85, 105);
        btnClose->FlatStyle = FlatStyle::Flat;
        btnClose->FlatAppearance->BorderColor = Color::FromArgb(226, 232, 240);
        btnClose->Font      = gcnew System::Drawing::Font("Segoe UI", 10);
        btnClose->Cursor    = Cursors::Hand;
        btnClose->Click    += gcnew EventHandler(this, &BookDetailForm::OnCloseClick);
        this->Controls->Add(btnClose);
    }

    Label^ MakeInfoLabel(int x, int y, String^ text) {
        Label^ lbl = gcnew Label();
        lbl->Text     = text;
        lbl->Location = System::Drawing::Point(x, y);
        lbl->Size     = System::Drawing::Size(400, 22);
        lbl->Font     = gcnew System::Drawing::Font("Segoe UI", 9.5f);
        lbl->ForeColor= Color::FromArgb(71, 85, 105);
        this->Controls->Add(lbl);
        return lbl;
    }

    String^ _ebookUrl;
    String^ _isAvailable;

    void LoadBookDetails() {
        try {
            String^ apiUrl = AppSettings::GetApiBase()
                             + "/api/books/" + _bookId + "/";
            auto req = (HttpWebRequest^)WebRequest::Create(apiUrl);
            req->Method  = "GET";
            req->Timeout = 8000;
            if (_readerToken->Length > 0)
                req->Headers->Add("X-Reader-Token", _readerToken);

            auto resp   = (HttpWebResponse^)req->GetResponse();
            auto reader = gcnew StreamReader(resp->GetResponseStream(), Encoding::UTF8);
            String^ json = reader->ReadToEnd();

            // Parse key fields
            String^ title    = GetJsonValue(json, "title");
            String^ author   = GetJsonValue(json, "author_name");
            String^ library  = GetJsonValue(json, "library_name");
            String^ section  = GetJsonValue(json, "section_name");
            String^ rating   = GetJsonValue(json, "average_rating");
            String^ views    = GetJsonValue(json, "view_count");
            String^ avail    = GetJsonValue(json, "is_available");
            String^ descr    = GetJsonValue(json, "description");
            String^ cover    = GetJsonValue(json, "cover_image");
            String^ ebook    = GetJsonValue(json, "ebook_file");
            _isAvailable     = avail;
            _ebookUrl        = ebook;

            lblTitle->Text   = title->Length > 0 ? title : "Noma'lum";
            lblAuthor->Text  = author->Length > 0 ? "Muallif: " + author : "";
            lblLibrary->Text = "Kutubxona: " + (library->Length > 0 ? library : "—");
            lblSection->Text = "Bo'lim: "    + (section->Length > 0 ? section : "—");
            lblRating->Text  = "Reyting: "   + (rating->Length  > 0 ? rating  : "—") + " / 5.0";
            lblViews->Text   = "Ko'rishlar: " + (views->Length > 0 ? views : "0");

            bool available = (avail == "true" || avail == "True");
            lblAvailable->Text      = "Holat: " + (available ? "Mavjud" : "Band");
            lblAvailable->ForeColor = available ? Color::FromArgb(5, 150, 105) : Color::FromArgb(220, 38, 38);

            rtbDescription->Text = descr->Length > 0 ? descr : "Tavsif mavjud emas.";

            btnReserve->Enabled   = available && _readerToken->Length > 0;
            btnReadEbook->Enabled = ebook->Length > 0;

            if (cover->Length > 0) {
                try {
                    String^ imgUrl = cover->StartsWith("http") ? cover
                        : AppSettings::GetApiBase() + cover;
                    auto wc = gcnew System::Net::WebClient();
                    auto imgData = wc->DownloadData(imgUrl);
                    auto ms = gcnew MemoryStream(imgData);
                    picCover->Image = Image::FromStream(ms);
                } catch (...) {}
            }
        } catch (Exception^ ex) {
            lblTitle->Text = "Ma'lumot olishda xato: " + ex->Message;
        }
    }

    void OnReserveClick(Object^ sender, EventArgs^ e) {
        if (_readerToken->Length == 0) {
            MessageBox::Show("Bron qilish uchun tizimga kiring.", "Kirish kerak",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        try {
            btnReserve->Enabled = false;
            lblStatus->Text = "Bron qilinmoqda...";

            String^ apiUrl = AppSettings::GetApiBase() + "/api/reservations/";
            String^ json   = "{\"book\":" + _bookId + "}";

            auto req = (HttpWebRequest^)WebRequest::Create(apiUrl);
            req->Method      = "POST";
            req->ContentType = "application/json";
            req->Timeout     = 8000;
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
                lblStatus->Text      = "";
                lblStatus->ForeColor = Color::FromArgb(5, 150, 105);
                MessageBox::Show("Kitob muvaffaqiyatli bron qilindi!", "Bron qilindi",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
                btnReserve->Enabled = false;
            } else {
                String^ err = GetJsonValue(respBody, "detail");
                if (err->Length == 0) err = GetJsonValue(respBody, "error");
                if (err->Length == 0) err = "Bronlashda xato yuz berdi.";
                lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
                lblStatus->Text = err;
                btnReserve->Enabled = true;
            }
        } catch (Exception^ ex) {
            lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
            lblStatus->Text = "Xato: " + ex->Message;
            btnReserve->Enabled = true;
        }
    }

    void OnEbookClick(Object^ sender, EventArgs^ e) {
        if (_ebookUrl->Length > 0) {
            String^ url = _ebookUrl->StartsWith("http") ? _ebookUrl
                : AppSettings::GetApiBase() + _ebookUrl;
            ProcessStartInfo^ psi = gcnew ProcessStartInfo(url);
            psi->UseShellExecute = true;
            Process::Start(psi);
        }
    }

    void OnCloseClick(Object^ sender, EventArgs^ e) {
        this->Close();
    }

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
