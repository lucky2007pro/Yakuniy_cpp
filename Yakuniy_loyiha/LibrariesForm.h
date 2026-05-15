#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

using namespace System;
using namespace System::Net;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Text::RegularExpressions;
using namespace System::Diagnostics;

public ref class LibrariesForm : public System::Windows::Forms::Form {
public:
    LibrariesForm() {
        InitUI();
        LoadLibraries();
    }

private:
    FlowLayoutPanel^ flp;
    Label^           lblStatus;
    TextBox^         txtSearch;
    Button^          btnRefresh;

    String^ apiBase = L"http://5.189.136.95:81/api/";

    void InitUI() {
        this->Text = AppSettings::Translate(L"Kutubxonalar", L"Libraries", L"\u0411\u0438\u0431\u043b\u0438\u043e\u0442\u0435\u043a\u0438");
        this->Size = System::Drawing::Size(860, 620);
        this->StartPosition = FormStartPosition::CenterParent;
        this->MinimumSize = System::Drawing::Size(720, 500);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
        this->BackColor = AppSettings::PageBackColor();
        this->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);

        // ─ Header panel ─
        Panel^ header = gcnew Panel();
        header->Dock = DockStyle::Top;
        header->Height = 72;
        header->BackColor = AppSettings::NavbarColor();
        this->Controls->Add(header);

        // Header bottom border
        Panel^ hBorder = gcnew Panel();
        hBorder->Dock = DockStyle::Top;
        hBorder->Height = 1;
        hBorder->BackColor = AppSettings::NavbarBorderColor();
        this->Controls->Add(hBorder);

        Label^ lblTitle = gcnew Label();
        lblTitle->Text = AppSettings::Translate(
            L"Kutubxonalar roʿyxati",
            L"Library List",
            L"Список библиотек"
        );
        lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16.0F, FontStyle::Bold);
        lblTitle->ForeColor = AppSettings::TextColor();
        lblTitle->AutoSize = true;
        lblTitle->Location = System::Drawing::Point(20, 20);
        header->Controls->Add(lblTitle);

        // Search + refresh toolbar
        Panel^ toolbar = gcnew Panel();
        toolbar->Dock = DockStyle::Top;
        toolbar->Height = 54;
        toolbar->BackColor = AppSettings::PageBackColor();
        toolbar->Padding = System::Windows::Forms::Padding(14, 10, 14, 10);

        txtSearch = gcnew TextBox();
        AppSettings::StyleInput(txtSearch);
        txtSearch->Location = System::Drawing::Point(14, 12);
        txtSearch->Size = System::Drawing::Size(320, 30);
        txtSearch->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
        txtSearch->TextChanged += gcnew System::EventHandler(this, &LibrariesForm::txtSearch_TextChanged);
        toolbar->Controls->Add(txtSearch);

        btnRefresh = gcnew Button();
        btnRefresh->Text = AppSettings::Translate(L"Yangilash", L"Refresh", L"\u041e\u0431\u043d\u043e\u0432\u0438\u0442\u044c");
        btnRefresh->Location = System::Drawing::Point(342, 10);
        btnRefresh->Size = System::Drawing::Size(120, 32);
        btnRefresh->FlatStyle = FlatStyle::Flat;
        btnRefresh->FlatAppearance->BorderSize = 0;
        btnRefresh->BackColor = AppSettings::PrimaryColor();
        btnRefresh->ForeColor = System::Drawing::Color::White;
        btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F, FontStyle::Bold);
        btnRefresh->Cursor = Cursors::Hand;
        AppSettings::MakeRounded(btnRefresh, 8);
        btnRefresh->Click += gcnew System::EventHandler(this, &LibrariesForm::btnRefresh_Click);
        toolbar->Controls->Add(btnRefresh);

        lblStatus = gcnew Label();
        lblStatus->Text = AppSettings::Translate(L"Yuklanmoqda...", L"Loading...", L"\u0417\u0430\u0433\u0440\u0443\u0437\u043a\u0430...");
        lblStatus->AutoSize = true;
        lblStatus->ForeColor = AppSettings::MutedTextColor();
        lblStatus->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
        lblStatus->Location = System::Drawing::Point(474, 17);
        toolbar->Controls->Add(lblStatus);

        // FlowPanel for library cards
        flp = gcnew FlowLayoutPanel();
        flp->Dock = DockStyle::Fill;
        flp->AutoScroll = true;
        flp->WrapContents = true;
        flp->Padding = System::Windows::Forms::Padding(14);
        flp->BackColor = AppSettings::PageBackColor();

        // Add controls in correct order (Fill must come last)
        this->Controls->Add(flp);
        this->Controls->Add(toolbar);
    }

    void LoadLibraries() {
        flp->Controls->Clear();
        lblStatus->Text = AppSettings::Translate(L"Yuklanmoqda...", L"Loading...", L"Загрузка...");

        String^ filter = txtSearch != nullptr ? txtSearch->Text->Trim()->ToLower() : L"";

        try {
            WebClient^ cl = gcnew WebClient();
            cl->Encoding = System::Text::Encoding::UTF8;
            String^ json = cl->DownloadString(apiBase + "libraries/");

            // Use AppSettings::ExtractJsonObjects — handles strings & nested objects
            List<String^>^ topObjs = AppSettings::ExtractJsonObjects(json);

            int shown = 0;
            for (int i = 0; i < topObjs->Count; i++) {
                String^ obj = topObjs[i];

                Match^ mId    = Regex::Match(obj, L"\"id\":(\\d+)");
                Match^ mName  = Regex::Match(obj, L"\"name\":\"([^\"]+)\"");
                Match^ mAddr  = Regex::Match(obj, L"\"address\":\"([^\"]*)\"");
                Match^ mLat   = Regex::Match(obj, L"\"latitude\":\"?([\\d.]+)\"?");
                Match^ mLon   = Regex::Match(obj, L"\"longitude\":\"?([\\d.]+)\"?");
                Match^ mPhone = Regex::Match(obj, L"\"phone\":\"([^\"]*)\"");

                if (!mId->Success || !mName->Success) continue;

                String^ libId = mId->Groups[1]->Value;
                String^ name  = mName->Groups[1]->Value;
                String^ addr  = mAddr->Success ? mAddr->Groups[1]->Value : L"";
                String^ lat   = mLat->Success  ? mLat->Groups[1]->Value  : L"";
                String^ lon   = mLon->Success  ? mLon->Groups[1]->Value  : L"";
                String^ phone = mPhone->Success ? mPhone->Groups[1]->Value : L"";

                if (!String::IsNullOrWhiteSpace(filter) &&
                    !name->ToLower()->Contains(filter) &&
                    !addr->ToLower()->Contains(filter)) continue;

                flp->Controls->Add(BuildLibraryCard(libId, name, addr, lat, lon, phone));
                shown++;
            }

            lblStatus->Text = String::Format(
                AppSettings::Translate(L"{0} ta kutubxona topildi", L"{0} libraries found", L"\u041d\u0430\u0439\u0434\u0435\u043d\u043e {0} \u0431\u0438\u0431\u043b\u0438\u043e\u0442\u0435\u043a"),
                shown
            );
        }
        catch (Exception^) {
            lblStatus->Text = AppSettings::Translate(L"Yuklab boʻlolmadi.", L"Failed to load.", L"\u041d\u0435 \u0443\u0434\u0430\u043b\u043e\u0441\u044c \u0437\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c.");
        }
    }

    Panel^ BuildLibraryCard(String^ libId, String^ name, String^ addr,
                             String^ lat, String^ lon, String^ phone) {
        int cardW = 370;
        Panel^ card = gcnew Panel();
        card->Size = System::Drawing::Size(cardW, 165);
        card->BackColor = AppSettings::SurfaceColor();
        card->Margin = System::Windows::Forms::Padding(10);
        card->Cursor = Cursors::Default;
        AppSettings::MakeRounded(card, 12);

        // Icon badge
        Panel^ icon = gcnew Panel();
        icon->Size = System::Drawing::Size(44, 44);
        icon->Location = System::Drawing::Point(14, 18);
        icon->BackColor = System::Drawing::Color::FromArgb(239, 246, 255);
        AppSettings::MakeRounded(icon, 22);

        Label^ iconLbl = gcnew Label();
        iconLbl->Text = L"K";
        iconLbl->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16.0F, FontStyle::Bold);
        iconLbl->Dock = DockStyle::Fill;
        iconLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        iconLbl->ForeColor = System::Drawing::Color::FromArgb(37, 99, 235);
        iconLbl->BackColor = System::Drawing::Color::Transparent;
        icon->Controls->Add(iconLbl);
        card->Controls->Add(icon);

        // Name
        Label^ lblName = gcnew Label();
        lblName->Text = name;
        lblName->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
        lblName->ForeColor = AppSettings::TextColor();
        lblName->BackColor = System::Drawing::Color::Transparent;
        lblName->Location = System::Drawing::Point(68, 22);
        lblName->MaximumSize = System::Drawing::Size(cardW - 88, 0);
        lblName->AutoSize = true;
        card->Controls->Add(lblName);

        // Address
        Label^ lblAddr = gcnew Label();
        lblAddr->Text = String::IsNullOrWhiteSpace(addr)
            ? AppSettings::Translate(L"Manzil ko'rsatilmagan", L"Address not provided", L"Адрес не указан")
            : addr;
        lblAddr->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
        lblAddr->ForeColor = AppSettings::MutedTextColor();
        lblAddr->Location = System::Drawing::Point(68, 48);
        lblAddr->Size = System::Drawing::Size(cardW - 88, 20);
        lblAddr->AutoEllipsis = true;
        card->Controls->Add(lblAddr);

        // Phone
        if (!String::IsNullOrWhiteSpace(phone)) {
            Label^ lblPhone = gcnew Label();
            lblPhone->Text = L"Tel: " + phone;
            lblPhone->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
            lblPhone->ForeColor = AppSettings::MutedTextColor();
            lblPhone->Location = System::Drawing::Point(68, 70);
            lblPhone->Size = System::Drawing::Size(cardW - 82, 20);
            card->Controls->Add(lblPhone);
        }

        // Google Maps button
        bool hasCoords = (!String::IsNullOrWhiteSpace(lat) && !String::IsNullOrWhiteSpace(lon)
                          && lat != L"0" && lon != L"0");
        Button^ btnMap = gcnew Button();
        btnMap->Text = hasCoords
            ? AppSettings::Translate(L"Xaritada ko'rish", L"View on Map", L"На карте")
            : AppSettings::Translate(L"Google Maps", L"Google Maps", L"Google Maps");
        btnMap->Location = System::Drawing::Point(14, 118);
        btnMap->Size = System::Drawing::Size(172, 32);
        btnMap->FlatStyle = FlatStyle::Flat;
        btnMap->FlatAppearance->BorderSize = 0;
        btnMap->BackColor = System::Drawing::Color::FromArgb(37, 99, 235);
        btnMap->ForeColor = System::Drawing::Color::White;
        btnMap->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.0F, FontStyle::Bold);
        btnMap->Cursor = Cursors::Hand;
        AppSettings::MakeRounded(btnMap, 8);

        String^ mapsUrl;
        if (hasCoords)
            mapsUrl = String::Format("https://www.google.com/maps?q={0},{1}", lat, lon);
        else
            mapsUrl = "https://www.google.com/maps/search/" +
                      Uri::EscapeDataString(name + " " + addr);

        btnMap->Tag = mapsUrl;
        btnMap->Click += gcnew System::EventHandler(this, &LibrariesForm::btnMap_Click);
        card->Controls->Add(btnMap);

        // Books in library button
        Button^ btnBooks = gcnew Button();
        btnBooks->Text = AppSettings::Translate(L"Kitoblar", L"Books", L"Книги");
        btnBooks->Location = System::Drawing::Point(194, 118);
        btnBooks->Size = System::Drawing::Size(120, 32);
        btnBooks->FlatStyle = FlatStyle::Flat;
        btnBooks->FlatAppearance->BorderSize = 1;
        btnBooks->FlatAppearance->BorderColor = AppSettings::BorderColor();
        btnBooks->BackColor = AppSettings::NavbarColor();
        btnBooks->ForeColor = AppSettings::TextColor();
        btnBooks->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.0F, FontStyle::Bold);
        btnBooks->Cursor = Cursors::Hand;
        AppSettings::MakeRounded(btnBooks, 8);
        btnBooks->Tag = name;
        btnBooks->Click += gcnew System::EventHandler(this, &LibrariesForm::btnBooks_Click);
        card->Controls->Add(btnBooks);

        return card;
    }

    // Event handlers
    void btnMap_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn == nullptr || btn->Tag == nullptr) return;
        try {
            Process::Start(btn->Tag->ToString());
        } catch (...) {}
    }

    void btnBooks_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn == nullptr || btn->Tag == nullptr) return;
        MessageBox::Show(
            AppSettings::Translate(
                L"Bu kutubxona kitoblarini asosiy sahifada \"\uab Kutubxona \u00bb\" filtri orqali ko\u02bfring.",
                L"View books of this library using the Library filter on the main page.",
                L"\u041f\u0440\u043e\u0441\u043c\u043e\u0442\u0440\u0438\u0442\u0435 \u043a\u043d\u0438\u0433\u0438 \u0447\u0435\u0440\u0435\u0437 \u0444\u0438\u043b\u044c\u0442\u0440 \u00ab\u0411\u0438\u0431\u043b\u0438\u043e\u0442\u0435\u043a\u0430\u00bb."
            ) + "\n\n" + btn->Tag->ToString(),
            AppSettings::Translate(L"Kutubxona", L"Library", L"\u0411\u0438\u0431\u043b\u0438\u043e\u0442\u0435\u043a\u0430"),
            MessageBoxButtons::OK,
            MessageBoxIcon::Information
        );
    }

    void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadLibraries();
    }

    void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        LoadLibraries();
    }
};

} // namespace Yakuniyloyiha
