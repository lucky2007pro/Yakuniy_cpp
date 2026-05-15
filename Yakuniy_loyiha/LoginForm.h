#pragma once
#include "AppSettings.h"
#include <vcclr.h>

#pragma comment(lib, "user32.lib")
extern "C" __declspec(dllimport) long long __stdcall SendMessageW(void*, unsigned int, unsigned long long, long long);
#define EM_SETCUEBANNER 0x1501

namespace Yakuniyloyiha {

using namespace System;
using namespace System::Net;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class LoginForm : public System::Windows::Forms::Form {
public:
    bool   IsLoggedIn;
    String^ ReaderToken;
    String^ ReaderName;
    String^ ReaderCardId;
    bool   ReaderApproved;

    LoginForm() {
        IsLoggedIn      = false;
        ReaderToken     = "";
        ReaderName      = "";
        ReaderCardId    = "";
        ReaderApproved  = false;
        InitializeComponent();
    }

private:
    static void SetPlaceholder(TextBox^ tb, String^ hint) {
        pin_ptr<const wchar_t> p = PtrToStringChars(hint);
        const wchar_t* raw = p;
        SendMessageW(tb->Handle.ToPointer(), EM_SETCUEBANNER, 1, (long long)raw);
    }

    bool isRegisterMode = false;

    TabControl^  tabs;
    TabPage^     tabLogin;
    TabPage^     tabRegister;

    // Login controls
    Label^       lblCardId;
    TextBox^     txtCardId;
    Label^       lblPassword;
    TextBox^     txtPassword;
    Button^      btnLogin;
    Label^       lblLoginError;

    // Register controls
    Label^       lblFullname;
    TextBox^     txtFullname;
    Label^       lblPhone;
    TextBox^     txtPhone;
    Label^       lblRegCardId;
    TextBox^     txtRegCardId;
    Label^       lblRegPassword;
    TextBox^     txtRegPassword;
    Button^      btnRegister;
    Label^       lblRegError;

    Label^       lblTitle;
    Label^       lblSubtitle;

    void InitializeComponent() {
        this->Text        = "TATU Kutubxona — Kirish";
        this->Size        = System::Drawing::Size(420, 520);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->BackColor   = Color::FromArgb(248, 250, 252);
        this->Font        = gcnew System::Drawing::Font("Segoe UI", 9.5f);

        // ── Header ──
        Panel^ header = gcnew Panel();
        header->BackColor = Color::FromArgb(37, 99, 235);
        header->Size = System::Drawing::Size(420, 72);
        header->Location = System::Drawing::Point(0, 0);

        lblTitle = gcnew Label();
        lblTitle->Text      = "TATU Kutubxona";
        lblTitle->ForeColor = Color::White;
        lblTitle->Font      = gcnew System::Drawing::Font("Segoe UI", 14, FontStyle::Bold);
        lblTitle->AutoSize  = true;
        lblTitle->Location  = System::Drawing::Point(20, 12);
        header->Controls->Add(lblTitle);

        lblSubtitle = gcnew Label();
        lblSubtitle->Text      = "Elektron kutubxona tizimi";
        lblSubtitle->ForeColor = Color::FromArgb(186, 213, 255);
        lblSubtitle->Font      = gcnew System::Drawing::Font("Segoe UI", 8.5f);
        lblSubtitle->AutoSize  = true;
        lblSubtitle->Location  = System::Drawing::Point(21, 40);
        header->Controls->Add(lblSubtitle);

        this->Controls->Add(header);

        // ── Tabs ──
        tabs = gcnew TabControl();
        tabs->Location = System::Drawing::Point(16, 84);
        tabs->Size     = System::Drawing::Size(388, 390);
        tabs->Font     = gcnew System::Drawing::Font("Segoe UI", 9.5f);

        tabLogin    = gcnew TabPage("  Kirish  ");
        tabRegister = gcnew TabPage("  Ro'yxatdan o'tish  ");

        BuildLoginTab();
        BuildRegisterTab();

        tabs->Controls->Add(tabLogin);
        tabs->Controls->Add(tabRegister);
        this->Controls->Add(tabs);
    }

    void BuildLoginTab() {
        tabLogin->Padding = System::Windows::Forms::Padding(12, 12, 12, 12);
        tabLogin->BackColor = Color::White;

        int y = 20;

        lblCardId = gcnew Label(); lblCardId->Text = "Kutubxona karta ID:";
        lblCardId->Location = System::Drawing::Point(12, y); lblCardId->AutoSize = true;
        tabLogin->Controls->Add(lblCardId); y += 22;

        txtCardId = gcnew TextBox(); txtCardId->Location = System::Drawing::Point(12, y);
        txtCardId->Size = System::Drawing::Size(350, 28); SetPlaceholder(txtCardId, "Masalan: TL-001");
        tabLogin->Controls->Add(txtCardId); y += 42;

        lblPassword = gcnew Label(); lblPassword->Text = "Parol:";
        lblPassword->Location = System::Drawing::Point(12, y); lblPassword->AutoSize = true;
        tabLogin->Controls->Add(lblPassword); y += 22;

        txtPassword = gcnew TextBox(); txtPassword->Location = System::Drawing::Point(12, y);
        txtPassword->Size = System::Drawing::Size(350, 28); txtPassword->UseSystemPasswordChar = true;
        SetPlaceholder(txtPassword, "Parol kiriting");
        tabLogin->Controls->Add(txtPassword); y += 50;

        btnLogin = gcnew Button();
        btnLogin->Text     = "Kirish";
        btnLogin->Location = System::Drawing::Point(12, y);
        btnLogin->Size     = System::Drawing::Size(350, 38);
        btnLogin->BackColor= Color::FromArgb(37, 99, 235);
        btnLogin->ForeColor= Color::White;
        btnLogin->FlatStyle= FlatStyle::Flat;
        btnLogin->FlatAppearance->BorderSize = 0;
        btnLogin->Font     = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnLogin->Cursor   = Cursors::Hand;
        btnLogin->Click   += gcnew EventHandler(this, &LoginForm::OnLoginClick);
        tabLogin->Controls->Add(btnLogin); y += 54;

        lblLoginError = gcnew Label();
        lblLoginError->Location  = System::Drawing::Point(12, y);
        lblLoginError->Size      = System::Drawing::Size(350, 48);
        lblLoginError->ForeColor = Color::FromArgb(185, 28, 28);
        lblLoginError->Font      = gcnew System::Drawing::Font("Segoe UI", 9.0f);
        lblLoginError->Visible   = false;
        tabLogin->Controls->Add(lblLoginError);
    }

    void BuildRegisterTab() {
        tabRegister->Padding = System::Windows::Forms::Padding(12, 8, 12, 12);
        tabRegister->BackColor = Color::White;

        int y = 16;

        lblFullname = gcnew Label(); lblFullname->Text = "To'liq ism:";
        lblFullname->Location = System::Drawing::Point(12, y); lblFullname->AutoSize = true;
        tabRegister->Controls->Add(lblFullname); y += 20;

        txtFullname = gcnew TextBox(); txtFullname->Location = System::Drawing::Point(12, y);
        txtFullname->Size = System::Drawing::Size(350, 26); SetPlaceholder(txtFullname, "Ism Familiya");
        tabRegister->Controls->Add(txtFullname); y += 36;

        lblPhone = gcnew Label(); lblPhone->Text = "Telefon:";
        lblPhone->Location = System::Drawing::Point(12, y); lblPhone->AutoSize = true;
        tabRegister->Controls->Add(lblPhone); y += 20;

        txtPhone = gcnew TextBox(); txtPhone->Location = System::Drawing::Point(12, y);
        txtPhone->Size = System::Drawing::Size(350, 26); SetPlaceholder(txtPhone, "+998901234567");
        tabRegister->Controls->Add(txtPhone); y += 36;

        lblRegCardId = gcnew Label(); lblRegCardId->Text = "Karta ID:";
        lblRegCardId->Location = System::Drawing::Point(12, y); lblRegCardId->AutoSize = true;
        tabRegister->Controls->Add(lblRegCardId); y += 20;

        txtRegCardId = gcnew TextBox(); txtRegCardId->Location = System::Drawing::Point(12, y);
        txtRegCardId->Size = System::Drawing::Size(350, 26); SetPlaceholder(txtRegCardId, "Masalan: TL-1234");
        tabRegister->Controls->Add(txtRegCardId); y += 36;

        lblRegPassword = gcnew Label(); lblRegPassword->Text = "Parol:";
        lblRegPassword->Location = System::Drawing::Point(12, y); lblRegPassword->AutoSize = true;
        tabRegister->Controls->Add(lblRegPassword); y += 20;

        txtRegPassword = gcnew TextBox(); txtRegPassword->Location = System::Drawing::Point(12, y);
        txtRegPassword->Size = System::Drawing::Size(350, 26); txtRegPassword->UseSystemPasswordChar = true;
        SetPlaceholder(txtRegPassword, "Kamida 6 belgi");
        tabRegister->Controls->Add(txtRegPassword); y += 44;

        btnRegister = gcnew Button();
        btnRegister->Text      = "Ro'yxatdan o'tish";
        btnRegister->Location  = System::Drawing::Point(12, y);
        btnRegister->Size      = System::Drawing::Size(350, 36);
        btnRegister->BackColor = Color::FromArgb(5, 150, 105);
        btnRegister->ForeColor = Color::White;
        btnRegister->FlatStyle = FlatStyle::Flat;
        btnRegister->FlatAppearance->BorderSize = 0;
        btnRegister->Font      = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnRegister->Cursor    = Cursors::Hand;
        btnRegister->Click    += gcnew EventHandler(this, &LoginForm::OnRegisterClick);
        tabRegister->Controls->Add(btnRegister); y += 50;

        lblRegError = gcnew Label();
        lblRegError->Location  = System::Drawing::Point(12, y);
        lblRegError->Size      = System::Drawing::Size(350, 42);
        lblRegError->ForeColor = Color::FromArgb(185, 28, 28);
        lblRegError->Font      = gcnew System::Drawing::Font("Segoe UI", 9.0f);
        lblRegError->Visible   = false;
        tabRegister->Controls->Add(lblRegError);
    }

    String^ PostJson(String^ url, String^ json) {
        try {
            auto req = (HttpWebRequest^)WebRequest::Create(url);
            req->Method      = "POST";
            req->ContentType = "application/json";
            req->Timeout     = 8000;
            auto bytes = Encoding::UTF8->GetBytes(json);
            req->ContentLength = bytes->Length;
            auto stream = req->GetRequestStream();
            stream->Write(bytes, 0, bytes->Length);
            stream->Close();
            auto resp   = (HttpWebResponse^)req->GetResponse();
            auto reader = gcnew StreamReader(resp->GetResponseStream(), Encoding::UTF8);
            return reader->ReadToEnd();
        } catch (WebException^ ex) {
            if (ex->Response != nullptr) {
                auto r = gcnew StreamReader(ex->Response->GetResponseStream(), Encoding::UTF8);
                return r->ReadToEnd();
            }
            return "{\"error\":\"" + ex->Message + "\"}";
        } catch (Exception^ ex) {
            return "{\"error\":\"" + ex->Message + "\"}";
        }
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

    bool GetJsonBool(String^ json, String^ key) {
        String^ search1 = "\"" + key + "\":true";
        String^ search2 = "\"" + key + "\": true";
        return json->IndexOf(search1) >= 0 || json->IndexOf(search2) >= 0;
    }

    void OnLoginClick(Object^ sender, EventArgs^ e) {
        String^ cardId   = txtCardId->Text->Trim();
        String^ password = txtPassword->Text;

        if (cardId->Length == 0 || password->Length == 0) {
            ShowError(lblLoginError, "Karta ID va parolni kiriting.");
            return;
        }

        btnLogin->Enabled = false;
        btnLogin->Text    = "Tekshirilmoqda...";

        String^ apiUrl = AppSettings::GetApiBase() + "/api/readers/login/";
        String^ json   = "{\"card_id\":\"" + cardId + "\",\"password\":\"" + password + "\"}";
        String^ resp   = PostJson(apiUrl, json);

        btnLogin->Enabled = true;
        btnLogin->Text    = "Kirish";

        String^ token = GetJsonValue(resp, "token");
        if (token->Length > 0) {
            ReaderToken    = token;
            ReaderName     = GetJsonValue(resp, "fullname");
            ReaderCardId   = GetJsonValue(resp, "card_id");
            ReaderApproved = GetJsonBool(resp, "is_active");
            IsLoggedIn     = true;
            lblLoginError->Visible = false;
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        } else {
            String^ err = GetJsonValue(resp, "detail");
            if (err->Length == 0) err = GetJsonValue(resp, "error");
            if (err->Length == 0) err = "Noto'g'ri karta ID yoki parol.";
            ShowError(lblLoginError, err);
        }
    }

    void OnRegisterClick(Object^ sender, EventArgs^ e) {
        String^ fullname = txtFullname->Text->Trim();
        String^ phone    = txtPhone->Text->Trim();
        String^ cardId   = txtRegCardId->Text->Trim();
        String^ password = txtRegPassword->Text;

        if (fullname->Length == 0 || phone->Length == 0 || cardId->Length == 0 || password->Length < 6) {
            ShowError(lblRegError, "Barcha maydonlar to'ldirilishi shart (parol kamida 6 belgi).");
            return;
        }

        btnRegister->Enabled = false;
        btnRegister->Text    = "Yuborilmoqda...";

        String^ apiUrl = AppSettings::GetApiBase() + "/api/readers/register/";
        String^ json   = "{\"fullname\":\"" + fullname + "\",\"phone\":\"" + phone +
                         "\",\"card_id\":\"" + cardId + "\",\"password\":\"" + password + "\"}";
        String^ resp   = PostJson(apiUrl, json);

        btnRegister->Enabled = true;
        btnRegister->Text    = "Ro'yxatdan o'tish";

        String^ token = GetJsonValue(resp, "token");
        if (token->Length > 0) {
            ReaderToken    = token;
            ReaderName     = fullname;
            ReaderCardId   = cardId;
            ReaderApproved = false;
            IsLoggedIn     = true;
            MessageBox::Show(
                "Muvaffaqiyatli ro'yxatdan o'tdingiz!\nAdmin tasdig'ini kuting.",
                "Xush kelibsiz",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        } else {
            String^ err = GetJsonValue(resp, "detail");
            if (err->Length == 0) err = GetJsonValue(resp, "error");
            if (err->Length == 0) err = "Ro'yxatdan o'tishda xato yuz berdi.";
            ShowError(lblRegError, err);
        }
    }

    void ShowError(Label^ lbl, String^ msg) {
        lbl->Text    = msg;
        lbl->Visible = true;
    }
};

} // namespace Yakuniyloyiha
