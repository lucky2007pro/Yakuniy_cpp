#pragma once
#include "AdminForm.h"
#include "AboutForm.h"
#include "StatisticsForm.h"
#include "ReaderForm.h"
#include "SettingsForm.h"
#include "HistoryForm.h"
#include "AppSettings.h"

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net;
   using namespace System::Diagnostics;
   using namespace System::Reflection;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);

			this->cmbFilterLibrary = (gcnew System::Windows::Forms::ComboBox());
			this->cmbFilterSection = (gcnew System::Windows::Forms::ComboBox());
            this->cmbRadius = (gcnew System::Windows::Forms::ComboBox());
            this->chkEbookOnly = (gcnew System::Windows::Forms::CheckBox());
			this->cmbSort = (gcnew System::Windows::Forms::ComboBox());
			this->btnShowAll = (gcnew System::Windows::Forms::Button());
			this->lblFilterLib = (gcnew System::Windows::Forms::Label());
			this->lblFilterSec = (gcnew System::Windows::Forms::Label());
			this->lblRadius = (gcnew System::Windows::Forms::Label());
			this->lblSort = (gcnew System::Windows::Forms::Label());
			this->lblResultCount = (gcnew System::Windows::Forms::Label());
			this->lblLocationStatus = (gcnew System::Windows::Forms::Label());
			this->lblStatusFilter = (gcnew System::Windows::Forms::Label());
			this->btnStatusAll = (gcnew System::Windows::Forms::Button());
			this->btnStatusAvailable = (gcnew System::Windows::Forms::Button());
			this->btnStatusReserved = (gcnew System::Windows::Forms::Button());
			this->btnStatusIssued = (gcnew System::Windows::Forms::Button());
			this->lblMarquee = (gcnew System::Windows::Forms::Label());
			this->lblRecent = (gcnew System::Windows::Forms::Label());
			this->marqueeTimer = (gcnew System::Windows::Forms::Timer());
			this->searchDebounceTimer = (gcnew System::Windows::Forms::Timer());

			this->Controls->Add(this->cmbFilterLibrary);
			this->Controls->Add(this->cmbFilterSection);
          this->Controls->Add(this->cmbRadius);
          this->Controls->Add(this->chkEbookOnly);
			this->Controls->Add(this->cmbSort);
			this->Controls->Add(this->btnShowAll);
			this->Controls->Add(this->lblFilterLib);
			this->Controls->Add(this->lblFilterSec);
			this->Controls->Add(this->lblRadius);
			this->Controls->Add(this->lblSort);
			this->Controls->Add(this->lblResultCount);
			this->Controls->Add(this->lblLocationStatus);
			this->Controls->Add(this->lblStatusFilter);
			this->Controls->Add(this->btnStatusAll);
			this->Controls->Add(this->btnStatusAvailable);
			this->Controls->Add(this->btnStatusReserved);
			this->Controls->Add(this->btnStatusIssued);
			this->Controls->Add(this->lblMarquee);
			this->Controls->Add(this->lblRecent);

			this->cmbFilterLibrary->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->cmbFilterSection->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->cmbRadius->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->chkEbookOnly->CheckedChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->cmbSort->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->txtSearch->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::txtSearch_KeyDown);
			this->txtSearch->TextChanged += gcnew System::EventHandler(this, &MyForm::txtSearch_TextChanged);
			this->btnStatusAll->Click += gcnew System::EventHandler(this, &MyForm::btnStatusAll_Click);
			this->btnStatusAvailable->Click += gcnew System::EventHandler(this, &MyForm::btnStatusAvailable_Click);
			this->btnStatusReserved->Click += gcnew System::EventHandler(this, &MyForm::btnStatusReserved_Click);
			this->btnStatusIssued->Click += gcnew System::EventHandler(this, &MyForm::btnStatusIssued_Click);
			this->marqueeTimer->Interval = 10;
			this->marqueeTimer->Tick += gcnew System::EventHandler(this, &MyForm::marqueeTimer_Tick);
			this->searchDebounceTimer->Interval = 320;
			this->searchDebounceTimer->Tick += gcnew System::EventHandler(this, &MyForm::searchDebounceTimer_Tick);

			ApplyModernStyle();
			FetchUserLocation();
			LoadDataFilters();
			LoadBooksToGrid();
			marqueeStep = 0;
			if (marqueeTimer != nullptr) marqueeTimer->Stop();
			UpdateReaderButtonState();
			this->WindowState = FormWindowState::Maximized;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: System::Windows::Forms::Button^ btnAdmin;
	private: System::Windows::Forms::Label^ lblSearch;
	private: System::Windows::Forms::TextBox^ txtSearch;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::FlowLayoutPanel^ flpResults;
	private: System::Windows::Forms::ComboBox^ cmbFilterLibrary;
	private: System::Windows::Forms::ComboBox^ cmbFilterSection;
    private: System::Windows::Forms::ComboBox^ cmbRadius;
    private: System::Windows::Forms::CheckBox^ chkEbookOnly;
	private: System::Windows::Forms::ComboBox^ cmbSort;
	private: System::Windows::Forms::Button^ btnShowAll;
	private: System::Windows::Forms::Button^ btnAbout;
	private: System::Windows::Forms::Button^ btnStat;
	private: System::Windows::Forms::Button^ btnReader;
	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Button^ btnHistory;
	private: System::Windows::Forms::Label^ lblFilterLib;
	private: System::Windows::Forms::Label^ lblFilterSec;
	private: System::Windows::Forms::Label^ lblRadius;
	private: System::Windows::Forms::Label^ lblSort;
private: System::Windows::Forms::Label^ lblResultCount;
private: System::Windows::Forms::Label^ lblLocationStatus;
private: System::Windows::Forms::Label^ lblStatusFilter;
private: System::Windows::Forms::Button^ btnStatusAll;
private: System::Windows::Forms::Button^ btnStatusAvailable;
private: System::Windows::Forms::Button^ btnStatusReserved;
private: System::Windows::Forms::Button^ btnStatusIssued;
 private: System::Windows::Forms::Label^ lblMarquee;
 private: System::Windows::Forms::Label^ lblRecent;
	private: System::Windows::Forms::Timer^ marqueeTimer;
	private: System::Windows::Forms::Timer^ searchDebounceTimer;
	private: int marqueeStep = 1;
	private: bool isUiUpdating = false;
	private: String^ activeStatusFilter = L"all";
	private: System::Collections::Generic::List<String^>^ recentViewedTitles = gcnew System::Collections::Generic::List<String^>();
	private: 
		// Nerverd serverga o'tishda shu yerni o'zgartiring
		String^ serverUrl = L"http://5.189.136.95:81"; 
		String^ apiUrl = serverUrl + L"/api/";
		int currentReaderId = -1;
		String^ currentReaderName = L"";
		String^ currentReaderCardId = L"";
		String^ currentReaderToken = nullptr;
		bool currentReaderApproved = false;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAdmin = (gcnew System::Windows::Forms::Button());
			this->lblSearch = (gcnew System::Windows::Forms::Label());
			this->txtSearch = (gcnew System::Windows::Forms::TextBox());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->btnAbout = (gcnew System::Windows::Forms::Button());
			this->btnStat = (gcnew System::Windows::Forms::Button());
			this->btnReader = (gcnew System::Windows::Forms::Button());
			this->btnSettings = (gcnew System::Windows::Forms::Button());
			this->btnHistory = (gcnew System::Windows::Forms::Button());
			this->flpResults = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->SuspendLayout();
			// 
			// btnAdmin
			// 
			this->btnAdmin->Location = System::Drawing::Point(840, 12);
			this->btnAdmin->Name = L"btnAdmin";
			this->btnAdmin->Size = System::Drawing::Size(90, 30);
			this->btnAdmin->TabIndex = 0;
			this->btnAdmin->Text = L"Admin";
			this->btnAdmin->UseVisualStyleBackColor = true;
			this->btnAdmin->Click += gcnew System::EventHandler(this, &MyForm::btnAdmin_Click);
			// 
			// lblSearch
			// 
			this->lblSearch->AutoSize = true;
			this->lblSearch->Location = System::Drawing::Point(12, 19);
			this->lblSearch->Name = L"lblSearch";
			this->lblSearch->Size = System::Drawing::Size(123, 16);
			this->lblSearch->TabIndex = 1;
			this->lblSearch->Text = L"Kitob nomi (qidiruv):";
			// 
			// txtSearch
			// 
			this->txtSearch->Location = System::Drawing::Point(140, 16);
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->Size = System::Drawing::Size(350, 22);
			this->txtSearch->TabIndex = 2;
			// 
			// btnSearch
			// 
			this->btnSearch->BackColor = System::Drawing::Color::CornflowerBlue;
			this->btnSearch->Location = System::Drawing::Point(540, 12);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(90, 30);
			this->btnSearch->TabIndex = 3;
			this->btnSearch->Text = L"Izlash";
			this->btnSearch->UseVisualStyleBackColor = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &MyForm::btnSearch_Click);
			// 
			// btnStat
			// 
			this->btnStat->Location = System::Drawing::Point(640, 12);
			this->btnStat->Name = L"btnStat";
			this->btnStat->Size = System::Drawing::Size(90, 30);
			this->btnStat->TabIndex = 5;
			this->btnStat->Text = L"Statistika";
			this->btnStat->UseVisualStyleBackColor = true;
			this->btnStat->Click += gcnew System::EventHandler(this, &MyForm::btnStat_Click);
			// 
			// btnAbout
			// 
			this->btnAbout->Location = System::Drawing::Point(740, 12);
			this->btnAbout->Name = L"btnAbout";
			this->btnAbout->Size = System::Drawing::Size(90, 30);
			this->btnAbout->TabIndex = 6;
			this->btnAbout->Text = L"Haqida";
			this->btnAbout->UseVisualStyleBackColor = true;
			this->btnAbout->Click += gcnew System::EventHandler(this, &MyForm::btnAbout_Click);
         // 
			// btnReader
			// 
			this->btnReader->Location = System::Drawing::Point(840, 12);
			this->btnReader->Name = L"btnReader";
			this->btnReader->Size = System::Drawing::Size(90, 30);
			this->btnReader->TabIndex = 7;
			this->btnReader->Text = L"O'quvchi";
			this->btnReader->UseVisualStyleBackColor = true;
			this->btnReader->Click += gcnew System::EventHandler(this, &MyForm::btnReader_Click);
			// 
			// btnSettings
			// 
			this->btnSettings->Location = System::Drawing::Point(1030, 12);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(90, 30);
			this->btnSettings->TabIndex = 9;
			this->btnSettings->Text = L"Sozlamalar";
			this->btnSettings->UseVisualStyleBackColor = true;
			this->btnSettings->Click += gcnew System::EventHandler(this, &MyForm::btnSettings_Click);
			// 
			// btnHistory
			// 
			this->btnHistory->Location = System::Drawing::Point(930, 12);
			this->btnHistory->Name = L"btnHistory";
			this->btnHistory->Size = System::Drawing::Size(90, 30);
			this->btnHistory->TabIndex = 8;
			this->btnHistory->Text = L"Tarix";
			this->btnHistory->UseVisualStyleBackColor = true;
			this->btnHistory->Click += gcnew System::EventHandler(this, &MyForm::btnHistory_Click);
			// 
			// flpResults
			// 
			this->flpResults->AutoScroll = true;
			this->flpResults->Location = System::Drawing::Point(12, 58);
			this->flpResults->Name = L"flpResults";
          this->flpResults->Size = System::Drawing::Size(1200, 583);
			this->flpResults->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1230, 470);
			this->Controls->Add(this->flpResults);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->btnReader);
			this->Controls->Add(this->btnStat);
			this->Controls->Add(this->btnAbout);
			this->Controls->Add(this->btnHistory);
			this->Controls->Add(this->btnSettings);
			this->Controls->Add(this->txtSearch);
			this->Controls->Add(this->lblSearch);
			this->Controls->Add(this->btnAdmin);
			this->Name = L"MyForm";
			this->Text = L"Kutubxona Tizimi";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: double userLat = 41.311081; // Standart: Toshkent
	private: double userLon = 69.240562;
	private: bool isLocationFetched = false;

	private: System::Void FetchUserLocation() {
		try {
			WebClient^ client = gcnew WebClient();
			String^ json = client->DownloadString("http://ip-api.com/json/?fields=lat,lon");
			Match^ matchLat = Regex::Match(json, "\"lat\":(-?\\d+(?:\\.\\d+)?)");
			Match^ matchLon = Regex::Match(json, "\"lon\":(-?\\d+(?:\\.\\d+)?)");

			if (matchLat->Success && matchLon->Success) {
				userLat = ParseCoordinate(matchLat->Groups[1]->Value, userLat);
				userLon = ParseCoordinate(matchLon->Groups[1]->Value, userLon);
				isLocationFetched = true;
			}
		}
		catch (Exception^) {
			// Xatolik yuz bersa standart(default) koordinatalar qoladi
		}
	}

	private: double ParseCoordinate(String^ value, double fallback) {
		if (String::IsNullOrWhiteSpace(value) || value == L"null") return fallback;
		String^ normalized = value->Trim()->Replace(L",", L".");
		double parsed = fallback;
		if (Double::TryParse(normalized, System::Globalization::NumberStyles::Float, System::Globalization::CultureInfo::InvariantCulture, parsed)) {
			return parsed;
		}
		if (Double::TryParse(value, System::Globalization::NumberStyles::Float, System::Globalization::CultureInfo::CurrentCulture, parsed)) {
			return parsed;
		}
		return fallback;
	}

	private: String^ FormatDistance(double km) {
		if (km < 0) return L"";
		if (km < 1.0) {
			int meters = Math::Max(1, static_cast<int>(Math::Round(km * 1000.0)));
			return meters.ToString() + L" m";
		}
		if (km < 10.0) {
			return Math::Round(km, 2).ToString(System::Globalization::CultureInfo::InvariantCulture) + L" km";
		}
		return Math::Round(km, 1).ToString(System::Globalization::CultureInfo::InvariantCulture) + L" km";
	}

	private: int GetResponsiveCardWidth() {
		int available = flpResults != nullptr ? flpResults->ClientSize.Width - 24 : 320;
		if (available < 240) return 210;

		int gap = 14;
		int preferred = 250;
		int columns = Math::Max(1, available / preferred);
		int width = (available - ((columns + 1) * gap)) / columns;

		while (width > 320) {
			columns++;
			width = (available - ((columns + 1) * gap)) / columns;
		}

		while (columns > 1 && width < 205) {
			columns--;
			width = (available - ((columns + 1) * gap)) / columns;
		}

		if (width < 205) width = 205;
		if (width > 320) width = 320;
		return width;
	}

	private: System::Void UpdateResponsiveLayout() {
		if (flpResults == nullptr) return;

		int sidePadding = 14;
		int topAnchor = lblMarquee != nullptr ? lblMarquee->Bottom : 144;
		if (lblRecent != nullptr && lblRecent->Visible) {
			topAnchor = Math::Max(topAnchor, lblRecent->Bottom);
		}
		int topOffset = topAnchor + 14;
		int bottomPadding = 12;

		int panelWidth = Math::Max(220, this->ClientSize.Width - (sidePadding * 2));
		int panelHeight = Math::Max(180, this->ClientSize.Height - topOffset - bottomPadding);

		flpResults->Location = System::Drawing::Point(sidePadding, topOffset);
		flpResults->Size = System::Drawing::Size(panelWidth, panelHeight);
	}

	private: int PlaceHeaderButton(Button^ btn, int right, int topY, int width, int gap) {
		if (btn == nullptr) return right;
		right -= width;
		btn->Location = System::Drawing::Point(right, topY);
		btn->Size = System::Drawing::Size(width, 35);
		return right - gap;
	}

	private: System::Void UpdateHeaderLayout() {
		if (lblSearch == nullptr || txtSearch == nullptr || btnSearch == nullptr || lblMarquee == nullptr) return;

		int margin = 16;
		int gap = 10;
		int topY = 14;
		int row2Y = 62;
		int row3Y = 100;

		int right = this->ClientSize.Width - margin;
		right = PlaceHeaderButton(btnAdmin, right, topY, 96, gap);
		right = PlaceHeaderButton(btnSettings, right, topY, 105, gap);
		right = PlaceHeaderButton(btnAbout, right, topY, 82, gap);
		right = PlaceHeaderButton(btnHistory, right, topY, 82, gap);
		right = PlaceHeaderButton(btnStat, right, topY, 90, gap);
		right = PlaceHeaderButton(btnReader, right, topY, 108, gap);

		lblSearch->Location = System::Drawing::Point(margin, 20);
		int searchX = lblSearch->Right + 12;
		int searchBtnWidth = 88;
		int searchWidth = right - searchX - gap - searchBtnWidth;
		if (searchWidth < 200) searchWidth = 200;
		if (searchWidth > 560) searchWidth = 560;

		txtSearch->Location = System::Drawing::Point(searchX, 16);
		txtSearch->Size = System::Drawing::Size(searchWidth, 30);
		btnSearch->Location = System::Drawing::Point(txtSearch->Right + gap, topY);
		btnSearch->Size = System::Drawing::Size(searchBtnWidth, 35);

		int x = margin;
		lblFilterLib->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblFilterLib->Right + 6;
		cmbFilterLibrary->Location = System::Drawing::Point(x, row2Y);
		cmbFilterLibrary->Size = System::Drawing::Size(130, 30);
		x = cmbFilterLibrary->Right + 14;

		lblFilterSec->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblFilterSec->Right + 6;
		cmbFilterSection->Location = System::Drawing::Point(x, row2Y);
		cmbFilterSection->Size = System::Drawing::Size(130, 30);
		x = cmbFilterSection->Right + 14;

		lblRadius->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblRadius->Right + 6;
		cmbRadius->Location = System::Drawing::Point(x, row2Y);
		cmbRadius->Size = System::Drawing::Size(110, 30);
		x = cmbRadius->Right + 14;

		chkEbookOnly->Location = System::Drawing::Point(x, row2Y + 4);
		x = chkEbookOnly->Right + 14;

		lblSort->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblSort->Right + 6;
		cmbSort->Location = System::Drawing::Point(x, row2Y);
		cmbSort->Size = System::Drawing::Size(170, 30);

		btnShowAll->Size = System::Drawing::Size(108, 35);
		btnShowAll->Location = System::Drawing::Point(this->ClientSize.Width - margin - btnShowAll->Width, row2Y - 2);
		lblResultCount->AutoSize = true;
		lblResultCount->Location = System::Drawing::Point(Math::Max(margin, btnShowAll->Left - 210), row2Y + 6);

		int sx = margin;
		lblStatusFilter->Location = System::Drawing::Point(sx, row3Y + 4);
		sx = lblStatusFilter->Right + 8;
		btnStatusAll->Location = System::Drawing::Point(sx, row3Y);
		btnStatusAll->Size = System::Drawing::Size(85, 30);
		sx = btnStatusAll->Right + 8;
		btnStatusAvailable->Location = System::Drawing::Point(sx, row3Y);
		btnStatusAvailable->Size = System::Drawing::Size(95, 30);
		sx = btnStatusAvailable->Right + 8;
		btnStatusReserved->Location = System::Drawing::Point(sx, row3Y);
		btnStatusReserved->Size = System::Drawing::Size(110, 30);
		sx = btnStatusReserved->Right + 8;
		btnStatusIssued->Location = System::Drawing::Point(sx, row3Y);
		btnStatusIssued->Size = System::Drawing::Size(95, 30);

		lblMarquee->Top = row3Y + 38;
		lblMarquee->Left = Math::Max(20, (this->ClientSize.Width - lblMarquee->Width) / 2);

		if (lblRecent != nullptr) {
			lblRecent->Location = System::Drawing::Point(margin, lblMarquee->Bottom + 4);
			lblRecent->Size = System::Drawing::Size(Math::Max(280, this->ClientSize.Width - (margin * 2)), 22);
		}
		if (lblLocationStatus != nullptr) {
			lblLocationStatus->AutoSize = true;
			lblLocationStatus->Location = System::Drawing::Point(Math::Max(margin, this->ClientSize.Width - margin - lblLocationStatus->PreferredWidth), row3Y + 5);
		}
	}

	private: System::Void UpdateBookCardLayout() {
		if (flpResults == nullptr || flpResults->Controls->Count == 0) return;

		int cardWidth = GetResponsiveCardWidth();
		int imageHeight = static_cast<int>(cardWidth * 0.78);
		if (imageHeight < 138) imageHeight = 138;
		if (imageHeight > 210) imageHeight = 210;
		int cardHeight = imageHeight + 172;

		for each (Control^ ctrl in flpResults->Controls) {
			Panel^ card = dynamic_cast<Panel^>(ctrl);
			if (card == nullptr) continue;

			card->Size = System::Drawing::Size(cardWidth, cardHeight);
			MakeRounded(card, 12);

			PictureBox^ pb = nullptr;
			Label^ lblTitle = nullptr;
			Label^ lblDist = nullptr;
			Label^ lblStat = nullptr;
			Label^ lblMeta = nullptr;
			Button^ btnMiniRoute = nullptr;
			Button^ btnMiniOpen = nullptr;
			for each (Control^ child in card->Controls) {
				if (child->Name == L"cover") pb = dynamic_cast<PictureBox^>(child);
				else if (child->Name == L"title") lblTitle = dynamic_cast<Label^>(child);
				else if (child->Name == L"distance") lblDist = dynamic_cast<Label^>(child);
				else if (child->Name == L"status") lblStat = dynamic_cast<Label^>(child);
				else if (child->Name == L"meta") lblMeta = dynamic_cast<Label^>(child);
				else if (child->Name == L"route") btnMiniRoute = dynamic_cast<Button^>(child);
				else if (child->Name == L"open") btnMiniOpen = dynamic_cast<Button^>(child);
			}

			if (pb != nullptr) {
				pb->Size = System::Drawing::Size(cardWidth, imageHeight);
			}
			if (lblTitle != nullptr) {
				lblTitle->Location = System::Drawing::Point(10, imageHeight + 10);
				lblTitle->Size = System::Drawing::Size(cardWidth - 20, 45);
			}
			if (lblDist != nullptr) {
				lblDist->Location = System::Drawing::Point(10, imageHeight + 60);
				lblDist->MaximumSize = System::Drawing::Size(cardWidth - 20, 22);
			}
			if (lblStat != nullptr) {
				lblStat->Location = System::Drawing::Point(10, imageHeight + 88);
			}
			if (lblMeta != nullptr) {
				lblMeta->Location = System::Drawing::Point(10, imageHeight + 116);
				lblMeta->Size = System::Drawing::Size(cardWidth - 20, 22);
			}
			if (btnMiniRoute != nullptr) {
				btnMiniRoute->Location = System::Drawing::Point(10, imageHeight + 140);
				btnMiniRoute->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
			}
			if (btnMiniOpen != nullptr) {
				btnMiniOpen->Location = System::Drawing::Point(20 + ((cardWidth - 30) / 2), imageHeight + 140);
				btnMiniOpen->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
			}
		}
	}

	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		UpdateHeaderLayout();
		UpdateResponsiveLayout();
		UpdateBookCardLayout();
	}

	private: double CalculateDistance(double lat1, double lon1, double lat2, double lon2) {
		const double R = 6371.0; // Yer radiusi (km)
		double dLat = (lat2 - lat1) * Math::PI / 180.0;
		double dLon = (lon2 - lon1) * Math::PI / 180.0;

		double rLat1 = lat1 * Math::PI / 180.0;
		double rLat2 = lat2 * Math::PI / 180.0;

		double a = Math::Sin(dLat / 2) * Math::Sin(dLat / 2) +
				   Math::Cos(rLat1) * Math::Cos(rLat2) *
				   Math::Sin(dLon / 2) * Math::Sin(dLon / 2);

		double c = 2 * Math::Atan2(Math::Sqrt(a), Math::Sqrt(1 - a));
		return R * c;
	}

	private: System::Void ApplyModernStyle() {
		Color darkBg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(20, 24, 28) : System::Drawing::Color::FromArgb(246, 248, 252);
		Color panelBg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(32, 38, 46) : System::Drawing::Color::FromArgb(255, 255, 255);
		Color accentColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(76, 144, 255) : System::Drawing::Color::FromArgb(37, 99, 235);
		Color textColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(236, 240, 241) : System::Drawing::Color::FromArgb(33, 37, 41);
		Color textMuted = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);

		this->Text = AppSettings::Translate(L"Kutubxona Tizimi", L"Library System", L"Библиотечная система");
		lblSearch->Text = AppSettings::Translate(L"Kitob nomi (qidiruv):", L"Book title (search):", L"Название книги (поиск):");
		btnSearch->Text = AppSettings::Translate(L"Izlash", L"Search", L"Поиск");
		btnReader->Text = AppSettings::Translate(L"O'quvchi", L"Reader", L"Читатель");
		btnStat->Text = AppSettings::Translate(L"Statistika", L"Statistics", L"Статистика");
		btnAbout->Text = AppSettings::Translate(L"Haqida", L"About", L"О программе");
		btnHistory->Text = AppSettings::Translate(L"Tarix", L"History", L"История");
		btnSettings->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
		btnAdmin->Text = AppSettings::Translate(L"Admin", L"Admin", L"Админ");
		lblFilterLib->Text = AppSettings::Translate(L"Kutubxona:", L"Library:", L"Библиотека:");
		lblFilterSec->Text = AppSettings::Translate(L"Bo'lim:", L"Section:", L"Раздел:");
		lblRadius->Text = AppSettings::Translate(L"Radius:", L"Radius:", L"Радиус:");
		lblSort->Text = AppSettings::Translate(L"Tartiblash:", L"Sort:", L"Сортировка:");
		lblStatusFilter->Text = AppSettings::Translate(L"Holat:", L"Status:", L"Статус:");
		btnStatusAll->Text = AppSettings::Translate(L"Barchasi", L"All", L"Все");
		btnStatusAvailable->Text = AppSettings::Translate(L"Mavjud", L"Available", L"Доступно");
		btnStatusReserved->Text = AppSettings::Translate(L"Band", L"Reserved", L"Бронь");
		btnStatusIssued->Text = AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано");
		chkEbookOnly->Text = AppSettings::Translate(L"Faqat e-kitob", L"E-books only", L"Только эл. книги");
		btnShowAll->Text = AppSettings::Translate(L"Barchasi", L"Reset", L"Сброс");
		lblResultCount->Text = AppSettings::Translate(L"Natijalar: 0", L"Results: 0", L"Результаты: 0");
		lblMarquee->Text = AppSettings::Translate(L"TATU Library • Online band qilish mavjud", L"TATU Library • Online reservation available", L"Библиотека ТАТУ • Доступно онлайн-бронирование");
		if (lblRecent != nullptr) {
			if (recentViewedTitles->Count == 0) {
				lblRecent->Text = AppSettings::Translate(L"So'nggi ko'rilgan: hali yo'q", L"Recently viewed: none yet", L"Недавно просмотренные: пока нет");
			}
			else {
				lblRecent->Text = AppSettings::Translate(L"So'nggi ko'rilgan: ", L"Recently viewed: ", L"Недавно просмотренные: ") + String::Join(L" • ", recentViewedTitles->ToArray());
			}
		}

		this->BackColor = darkBg;
		this->ForeColor = textColor;
		this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

		lblSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, System::Drawing::FontStyle::Bold));
		lblSearch->ForeColor = textColor;
		lblSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);
		txtSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.5F));
		txtSearch->BackColor = panelBg;
		txtSearch->ForeColor = textColor;
		txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		txtSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);

       lblSearch->Location = System::Drawing::Point(20, 25);
		txtSearch->Location = System::Drawing::Point(230, 22);
		txtSearch->Size = System::Drawing::Size(270, 30);

        array<Button^>^ buttons = { btnSearch, btnReader, btnStat, btnHistory, btnAbout, btnSettings, btnAdmin, btnShowAll };
		for each (Button^ btn in buttons) {
			if (btn != nullptr) {
				btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btn->FlatAppearance->BorderSize = 0;
				btn->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold));
				btn->ForeColor = textColor;
				btn->Cursor = System::Windows::Forms::Cursors::Hand;
				btn->Height = 35;
			}
		}

		btnSearch->Location = System::Drawing::Point(510, 20);
		btnSearch->Size = System::Drawing::Size(80, 35);
		btnSearch->BackColor = accentColor;
		btnSearch->ForeColor = System::Drawing::Color::White;
		btnSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnReader->Location = System::Drawing::Point(600, 20);
		btnReader->Size = System::Drawing::Size(108, 35);
		btnReader->BackColor = panelBg;
		btnReader->ForeColor = textColor;
		btnReader->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
		btnReader->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnStat->Location = System::Drawing::Point(700, 20);
		btnStat->Size = System::Drawing::Size(90, 35);
		btnStat->BackColor = panelBg;
		btnStat->ForeColor = textColor;
		btnStat->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnHistory->Location = System::Drawing::Point(800, 20);
		btnHistory->Size = System::Drawing::Size(80, 35);
		btnHistory->BackColor = panelBg;
		btnHistory->ForeColor = textColor;
		btnHistory->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnAbout->Location = System::Drawing::Point(890, 20);
		btnAbout->Size = System::Drawing::Size(80, 35);
		btnAbout->BackColor = panelBg;
		btnAbout->ForeColor = textColor;
		btnAbout->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

        btnSettings->Location = System::Drawing::Point(980, 20);
		btnSettings->Size = System::Drawing::Size(105, 35);
		btnSettings->BackColor = panelBg;
		btnSettings->ForeColor = textColor;
		btnSettings->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
		btnSettings->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnAdmin->Location = System::Drawing::Point(1095, 20);
		btnAdmin->Size = System::Drawing::Size(100, 35);
		btnAdmin->BackColor = accentColor;
		btnAdmin->ForeColor = System::Drawing::Color::White;
		btnAdmin->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		lblFilterLib->Text = AppSettings::Translate(L"Kutubxona:", L"Library:", L"Библиотека:");
		lblFilterLib->ForeColor = textMuted;
		lblFilterLib->Location = System::Drawing::Point(20, 70);
		cmbFilterLibrary->Location = System::Drawing::Point(115, 68);
		cmbFilterLibrary->Size = System::Drawing::Size(200, 30);
		cmbFilterLibrary->BackColor = panelBg;
		cmbFilterLibrary->ForeColor = textColor;
		cmbFilterLibrary->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbFilterLibrary->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbFilterLibrary->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		lblFilterSec->Text = AppSettings::Translate(L"Bo'lim:", L"Section:", L"Раздел:");
		lblFilterSec->ForeColor = textMuted;
		lblFilterSec->Location = System::Drawing::Point(335, 70);
		cmbFilterSection->Location = System::Drawing::Point(395, 68);
		cmbFilterSection->Size = System::Drawing::Size(180, 30);
		cmbFilterSection->BackColor = panelBg;
		cmbFilterSection->ForeColor = textColor;
		cmbFilterSection->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbFilterSection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbFilterSection->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		lblRadius->Text = AppSettings::Translate(L"Radius:", L"Radius:", L"Радиус:");
		lblRadius->ForeColor = textMuted;
		lblSort->ForeColor = textMuted;
		lblResultCount->ForeColor = textMuted;
		lblStatusFilter->ForeColor = textMuted;
		if (lblLocationStatus != nullptr) {
			lblLocationStatus->Text = isLocationFetched
				? AppSettings::Translate(L"Joylashuv: aniqlandi", L"Location: detected", L"Геолокация: определена")
				: AppSettings::Translate(L"Joylashuv: Toshkent bo'yicha", L"Location: Tashkent fallback", L"Геолокация: по Ташкенту");
			lblLocationStatus->ForeColor = isLocationFetched
				? (AppSettings::DarkMode ? System::Drawing::Color::FromArgb(95, 220, 140) : System::Drawing::Color::FromArgb(20, 140, 82))
				: textMuted;
			lblLocationStatus->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
		}
		lblRadius->Location = System::Drawing::Point(590, 70);
		cmbRadius->Location = System::Drawing::Point(650, 68);
		cmbRadius->Size = System::Drawing::Size(130, 30);
		cmbRadius->BackColor = panelBg;
		cmbRadius->ForeColor = textColor;
		cmbRadius->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbRadius->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbRadius->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		lblSort->Location = System::Drawing::Point(940, 70);
		cmbSort->Location = System::Drawing::Point(1015, 68);
		cmbSort->Size = System::Drawing::Size(180, 30);
		cmbSort->BackColor = panelBg;
		cmbSort->ForeColor = textColor;
		cmbSort->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbSort->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbSort->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		chkEbookOnly->Text = AppSettings::Translate(L"Faqat e-kitob", L"E-books only", L"Только эл. книги");
		chkEbookOnly->ForeColor = textColor;
		chkEbookOnly->Location = System::Drawing::Point(800, 70);
		chkEbookOnly->AutoSize = true;
		chkEbookOnly->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		btnShowAll->Text = AppSettings::Translate(L"Barchasi", L"Reset", L"Сброс");
        btnShowAll->Location = System::Drawing::Point(940, 65);
		btnShowAll->Size = System::Drawing::Size(108, 35);
		btnShowAll->BackColor = panelBg;
		btnShowAll->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		array<Button^>^ statusButtons = { btnStatusAll, btnStatusAvailable, btnStatusReserved, btnStatusIssued };
		for each (Button ^ sb in statusButtons) {
			if (sb == nullptr) continue;
			sb->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			sb->FlatAppearance->BorderSize = 0;
			sb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold);
			sb->Cursor = System::Windows::Forms::Cursors::Hand;
			MakeRounded(sb, 12);
		}

		Color chipBg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(46, 54, 64) : System::Drawing::Color::FromArgb(232, 236, 243);
		Color chipFg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(220, 225, 230) : System::Drawing::Color::FromArgb(60, 70, 85);
		Color chipActiveBg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(37, 99, 235) : System::Drawing::Color::FromArgb(37, 99, 235);
		Color chipActiveFg = System::Drawing::Color::White;

		btnStatusAll->BackColor = activeStatusFilter == L"all" ? chipActiveBg : chipBg;
		btnStatusAll->ForeColor = activeStatusFilter == L"all" ? chipActiveFg : chipFg;
		btnStatusAvailable->BackColor = activeStatusFilter == L"available" ? chipActiveBg : chipBg;
		btnStatusAvailable->ForeColor = activeStatusFilter == L"available" ? chipActiveFg : chipFg;
		btnStatusReserved->BackColor = activeStatusFilter == L"reserved" ? chipActiveBg : chipBg;
		btnStatusReserved->ForeColor = activeStatusFilter == L"reserved" ? chipActiveFg : chipFg;
		btnStatusIssued->BackColor = activeStatusFilter == L"issued" ? chipActiveBg : chipBg;
		btnStatusIssued->ForeColor = activeStatusFilter == L"issued" ? chipActiveFg : chipFg;

		lblResultCount->AutoSize = true;
		lblResultCount->Location = System::Drawing::Point(1060, 72);
		lblResultCount->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		lblMarquee->Text = AppSettings::Translate(L"TATU Library • Online band qilish mavjud", L"TATU Library • Online reservation available", L"Библиотека ТАТУ • Доступно онлайн-бронирование");
		lblMarquee->AutoSize = true;
		lblMarquee->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12.0F, System::Drawing::FontStyle::Bold);
		lblMarquee->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(120, 190, 255) : System::Drawing::Color::FromArgb(26, 115, 232);
		lblMarquee->BackColor = System::Drawing::Color::Transparent;
        lblMarquee->Location = System::Drawing::Point(-lblMarquee->PreferredWidth, 136);

		if (lblRecent != nullptr) {
			lblRecent->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.4F, System::Drawing::FontStyle::Regular);
			lblRecent->ForeColor = textMuted;
			lblRecent->AutoEllipsis = true;
		}

	    flpResults->Location = System::Drawing::Point(14, 148);
		flpResults->Size = System::Drawing::Size(1200, 450);
		flpResults->BackColor = darkBg;
		flpResults->AutoScroll = true;
		flpResults->WrapContents = true;
		flpResults->Padding = System::Windows::Forms::Padding(10);
		flpResults->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);

		this->MinimumSize = System::Drawing::Size(1080, 680);
		if (this->ClientSize.Height < 620) {
			this->ClientSize = System::Drawing::Size(this->ClientSize.Width, 620);
		}

		UpdateHeaderLayout();
		lblMarquee->BringToFront();
		UpdateResponsiveLayout();
		UpdateReaderButtonState();

      MakeRounded(btnSearch, 8); MakeRounded(btnAdmin, 8); MakeRounded(btnShowAll, 8); MakeRounded(btnStat, 8); MakeRounded(btnAbout, 8); MakeRounded(btnReader, 8); MakeRounded(btnSettings, 8); MakeRounded(btnHistory, 8);
	}

	private: System::Void MakeRounded(Control^ ctrl, int radius) {
		System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
		path->StartFigure();
		path->AddArc(0, 0, radius, radius, 180, 90);
		path->AddArc(ctrl->Width - radius, 0, radius, radius, 270, 90);
		path->AddArc(ctrl->Width - radius, ctrl->Height - radius, radius, radius, 0, 90);
		path->AddArc(0, ctrl->Height - radius, radius, radius, 90, 90);
		path->CloseFigure();
		ctrl->Region = gcnew System::Drawing::Region(path);
	}

	private: System::Void EnableDoubleBuffer(Control^ ctrl) {
		if (ctrl == nullptr) return;
		PropertyInfo^ pi = ctrl->GetType()->GetProperty(L"DoubleBuffered", BindingFlags::NonPublic | BindingFlags::Instance);
		if (pi != nullptr) {
			pi->SetValue(ctrl, true, nullptr);
		}
	}

	private: System::Void LoadDataFilters() {
        isUiUpdating = true;
		cmbFilterLibrary->Items->Clear();
		cmbFilterLibrary->Items->Add(L"Barchasi");
		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			String^ json = client->DownloadString(apiUrl + "libraries/");
			MatchCollection^ matches = Regex::Matches(json, "\"name\":\"([^\"]+)\"");
			for each(Match^ m in matches) {
				cmbFilterLibrary->Items->Add(m->Groups[1]->Value);
			}
		} catch (...) {}
		cmbFilterLibrary->SelectedIndex = 0;

		cmbFilterSection->Items->Clear();
		cmbFilterSection->Items->Add(L"Barchasi");
		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			String^ json = client->DownloadString(apiUrl + "sections/");
			MatchCollection^ matches = Regex::Matches(json, "\"name\":\"([^\"]+)\"");
			for each(Match^ m in matches) {
				cmbFilterSection->Items->Add(m->Groups[1]->Value);
			}
		} catch (...) {}
		cmbFilterSection->SelectedIndex = 0;

		cmbRadius->Items->Clear();
		cmbRadius->Items->Add(L"Barchasi");
		cmbRadius->Items->Add(L"2 km");
		cmbRadius->Items->Add(L"5 km");
		cmbRadius->Items->Add(L"10 km");
		cmbRadius->Items->Add(L"20 km");
		cmbRadius->SelectedIndex = 0;

		cmbSort->Items->Clear();
		cmbSort->Items->Add(AppSettings::Translate(L"Yaqinlari avval", L"Nearest first", L"Сначала ближайшие"));
		cmbSort->Items->Add(AppSettings::Translate(L"Nomi A-Z", L"Title A-Z", L"Название А-Я"));
		cmbSort->Items->Add(AppSettings::Translate(L"Avval mavjudlar", L"Available first", L"Сначала доступные"));
		cmbSort->SelectedIndex = 0;
       isUiUpdating = false;
	}

	private: System::Void LoadBooksToGrid() {
        flpResults->SuspendLayout();
		flpResults->Controls->Clear();
		ShowLoadingSkeleton(6);
		flpResults->ResumeLayout();
		flpResults->Refresh();
		Application::DoEvents();
		flpResults->SuspendLayout();
		flpResults->Controls->Clear();

		System::Drawing::Bitmap^ emptyImage = gcnew System::Drawing::Bitmap(1, 1);

		String^ search = txtSearch->Text != nullptr ? txtSearch->Text->ToLower() : L"";
		String^ libFilter = cmbFilterLibrary->Text != nullptr ? cmbFilterLibrary->Text : L"Barchasi";
		String^ secFilter = cmbFilterSection->Text != nullptr ? cmbFilterSection->Text : L"Barchasi";
		String^ radiusFilter = cmbRadius->Text != nullptr ? cmbRadius->Text : L"Barchasi";
		int sortIndex = cmbSort != nullptr ? cmbSort->SelectedIndex : 0;
		bool onlyEbooks = chkEbookOnly != nullptr && chkEbookOnly->Checked;
		double maxRadius = -1;
		if (radiusFilter != L"Barchasi") {
			String^ num = radiusFilter->Replace(L" km", L"");
			double parsed = 0;
			if (Double::TryParse(num, parsed)) maxRadius = parsed;
		}

		System::Collections::Generic::List<String^>^ issuedBooks = gcnew System::Collections::Generic::List<String^>();
		System::Collections::Generic::List<String^>^ reservedBooks = gcnew System::Collections::Generic::List<String^>();
		// API dan berilgan kitoblarni yuklash
		try {
			WebClient^ issueCl = gcnew WebClient();
			issueCl->Encoding = System::Text::Encoding::UTF8;
			String^ issJson = issueCl->DownloadString(apiUrl + "issues/");
			MatchCollection^ issMatches = Regex::Matches(issJson, "\"book_title\":\"([^\"]+)\"");
			for each(Match^ m in issMatches) {
				String^ bTitle = m->Groups[1]->Value->ToLower();
				if (!issuedBooks->Contains(bTitle)) issuedBooks->Add(bTitle);
			}
		} catch (...) {}

		try {
			WebClient^ reservCl = gcnew WebClient();
			reservCl->Encoding = System::Text::Encoding::UTF8;
			String^ reservJson = reservCl->DownloadString(apiUrl + "reservations/");
			MatchCollection^ reservMatches = Regex::Matches(reservJson, "\"book_title\":\"([^\"]+)\"");
			for each(Match^ m in reservMatches) {
				String^ bTitle = m->Groups[1]->Value->ToLower();
				if (!reservedBooks->Contains(bTitle)) reservedBooks->Add(bTitle);
			}
		} catch (...) {}

		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			String^ json = client->DownloadString(apiUrl + "books/");
			
			// Regex to find book objects in JSON
			MatchCollection^ books = Regex::Matches(json, "\\{[^{}]+\\}");
			System::Collections::Generic::List<array<Object^>^>^ results = gcnew System::Collections::Generic::List<array<Object^>^>();

			for each(Match^ m in books) {
				String^ obj = m->Value;
				String^ title = Regex::Match(obj, "\"title\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ libName = Regex::Match(obj, "\"library_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ secName = Regex::Match(obj, "\"section_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ shelf = Regex::Match(obj, "\"shelf\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ row = Regex::Match(obj, "\"row\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ ebookPath = Regex::Match(obj, "\"ebook_file\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ coverImg = Regex::Match(obj, "\"cover_image\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ bookIdText = Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value;
				String^ libLatText = Regex::Match(obj, "\"library_latitude\":(-?[\\d\\.]+)")->Groups[1]->Value;
				String^ libLonText = Regex::Match(obj, "\"library_longitude\":(-?[\\d\\.]+)")->Groups[1]->Value;

				// Media URLlarni absolutga aylantirish (agar nisbiy bo'lsa)
				if (!String::IsNullOrEmpty(coverImg) && coverImg != "null" && !coverImg->StartsWith(L"http")) {
					coverImg = serverUrl + (coverImg->StartsWith(L"/") ? coverImg : (L"/" + coverImg));
				}
				if (!String::IsNullOrEmpty(ebookPath) && ebookPath != "null" && !ebookPath->StartsWith(L"http")) {
					ebookPath = serverUrl + (ebookPath->StartsWith(L"/") ? ebookPath : (L"/" + ebookPath));
				}

				// Coordinate fetching for distance calculation
				double libLat = ParseCoordinate(libLatText, 41.3110);
				double libLon = ParseCoordinate(libLonText, 69.2401);
				
				bool matchSearch = String::IsNullOrWhiteSpace(search) || title->ToLower()->Contains(search);
				bool matchLib = (libFilter == L"Barchasi" || libFilter == libName);
				bool matchSec = (secFilter == L"Barchasi" || secFilter == secName);

				bool hasEbook = !String::IsNullOrEmpty(ebookPath) && ebookPath != "null";
				if (onlyEbooks && !hasEbook) continue;

				if (matchSearch && matchLib && matchSec) {
					double dist = CalculateDistance(userLat, userLon, libLat, libLon);
					if (maxRadius > 0 && dist > maxRadius) continue;

					Image^ img = emptyImage;
					try {
						if (!String::IsNullOrEmpty(coverImg) && coverImg != "null") {
							WebClient^ imgCl = gcnew WebClient();
							array<Byte>^ data = imgCl->DownloadData(coverImg);
							MemoryStream^ ms = gcnew MemoryStream(data);
							img = Image::FromStream(ms);
						}
					} catch (...) {}
					
					String^ holat = L"Mavjud";
					if (issuedBooks->Contains(title->ToLower())) {
						holat = AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано");
					}
					else if (reservedBooks->Contains(title->ToLower())) {
						holat = AppSettings::Translate(L"Band qilingan", L"Reserved", L"Забронировано");
					}

					String^ availableText = AppSettings::Translate(L"Mavjud", L"Available", L"Доступно");
					String^ reservedText = AppSettings::Translate(L"Band qilingan", L"Reserved", L"Забронировано");
					String^ issuedText = AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано");
					bool statusMatches = true;
					if (activeStatusFilter == L"available") {
						statusMatches = (holat == availableText);
					}
					else if (activeStatusFilter == L"reserved") {
						statusMatches = (holat == reservedText);
					}
					else if (activeStatusFilter == L"issued") {
						statusMatches = (holat == issuedText);
					}
					if (!statusMatches) continue;

					array<Object^>^ resRow = gcnew array<Object^>(13);
					resRow[0] = img;
					resRow[1] = title;
					resRow[2] = libName;
					resRow[3] = secName;
					resRow[4] = shelf;
					resRow[5] = row;
					resRow[6] = FormatDistance(dist);
					resRow[7] = holat;
					resRow[8] = dist.ToString(System::Globalization::CultureInfo::InvariantCulture);
					resRow[9] = libLat.ToString(System::Globalization::CultureInfo::InvariantCulture);
					resRow[10] = libLon.ToString(System::Globalization::CultureInfo::InvariantCulture);
					resRow[11] = (ebookPath == "null") ? "" : ebookPath;
					resRow[12] = bookIdText;

					results->Add(resRow);
				}
			}

			if (sortIndex == 1) {
				results->Sort(gcnew Comparison<array<Object^>^>(this, &MyForm::CompareTitle));
			}
			else if (sortIndex == 2) {
				results->Sort(gcnew Comparison<array<Object^>^>(this, &MyForm::CompareAvailabilityThenDistance));
			}
			else {
				results->Sort(gcnew Comparison<array<Object^>^>(this, &MyForm::CompareDistance));
			}

			if (lblResultCount != nullptr) {
				String^ tpl = AppSettings::Translate(L"Natijalar: {0}", L"Results: {0}", L"Результаты: {0}");
				lblResultCount->Text = String::Format(tpl, results->Count);
			}

			if (results->Count == 0) {
				Panel^ emptyCard = gcnew Panel();
				emptyCard->Size = System::Drawing::Size(Math::Max(420, flpResults->ClientSize.Width - 80), 160);
				emptyCard->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(40, 45, 52) : System::Drawing::Color::White;
				emptyCard->Margin = System::Windows::Forms::Padding(18);
				MakeRounded(emptyCard, 14);

				Label^ emptyTitle = gcnew Label();
				emptyTitle->Text = AppSettings::Translate(L"Hech narsa topilmadi", L"No results found", L"Ничего не найдено");
				emptyTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.0F, System::Drawing::FontStyle::Bold);
				emptyTitle->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(230, 233, 238) : System::Drawing::Color::FromArgb(33, 37, 41);
				emptyTitle->Location = System::Drawing::Point(20, 24);
				emptyTitle->AutoSize = true;

				Label^ emptyHint = gcnew Label();
				emptyHint->Text = AppSettings::Translate(
					L"Filtrlarni yengillashtiring yoki qidiruvni tozalab ko'ring.",
					L"Try relaxing filters or clearing the search.",
					L"Попробуйте смягчить фильтры или очистить поиск."
				);
				emptyHint->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Regular);
				emptyHint->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);
				emptyHint->Location = System::Drawing::Point(22, 62);
				emptyHint->AutoSize = true;

				emptyCard->Controls->Add(emptyTitle);
				emptyCard->Controls->Add(emptyHint);
				flpResults->Controls->Add(emptyCard);
			}


			int cardWidth = GetResponsiveCardWidth();
			int imageHeight = static_cast<int>(cardWidth * 0.78);
			if (imageHeight < 138) imageHeight = 138;
			if (imageHeight > 210) imageHeight = 210;
			int cardHeight = imageHeight + 172;

			for (int i = 0; i < results->Count; i++) {
				array<Object^>^ res = results[i];
				Panel^ card = gcnew Panel();
				card->Size = System::Drawing::Size(cardWidth, cardHeight);
				card->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(40, 45, 52) : System::Drawing::Color::White;
				card->Margin = System::Windows::Forms::Padding(12);
				MakeRounded(card, 12);
				card->Cursor = Cursors::Hand;

				PictureBox^ pb = gcnew PictureBox();
				pb->Name = L"cover";
				pb->Size = System::Drawing::Size(cardWidth, imageHeight);
				pb->Location = System::Drawing::Point(0, 0);
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->Image = dynamic_cast<Image^>(res[0]);
				if (pb->Image == emptyImage) { pb->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(58, 65, 76) : System::Drawing::Color::FromArgb(226, 232, 240); }

				Label^ lblTitle = gcnew Label();
				lblTitle->Name = L"title";
				lblTitle->Text = res[1]->ToString();
				lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, System::Drawing::FontStyle::Bold);
				lblTitle->Size = System::Drawing::Size(cardWidth - 20, 45);
				lblTitle->Location = System::Drawing::Point(10, imageHeight + 10);
				lblTitle->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(236, 240, 241) : System::Drawing::Color::FromArgb(24, 30, 38);

				Label^ lblDist = gcnew Label();
				lblDist->Name = L"distance";
				lblDist->Text = AppSettings::Translate(L"Yaqinlik: ", L"Distance: ", L"Расстояние: ") + res[6]->ToString() + L" • " + res[2]->ToString();
				lblDist->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
				lblDist->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);
				lblDist->Location = System::Drawing::Point(10, imageHeight + 60);
				lblDist->Size = System::Drawing::Size(cardWidth - 20, 22);
				lblDist->AutoEllipsis = true;

				Label^ lblStat = gcnew Label();
				lblStat->Name = L"status";
				lblStat->Text = res[7]->ToString();
				lblStat->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold);
				lblStat->Location = System::Drawing::Point(10, imageHeight + 88);
				String^ statusText = res[7]->ToString();
				if (statusText == AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано")) {
					lblStat->ForeColor = System::Drawing::Color::FromArgb(255, 99, 132);
				}
				else if (statusText == AppSettings::Translate(L"Band qilingan", L"Reserved", L"Забронировано")) {
					lblStat->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(255, 201, 87) : System::Drawing::Color::FromArgb(240, 156, 0);
				}
				else {
					lblStat->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(95, 220, 140) : System::Drawing::Color::FromArgb(46, 204, 113);
				}
				lblStat->AutoSize = true;

				Label^ lblMeta = gcnew Label();
				lblMeta->Name = L"meta";
				lblMeta->Text = AppSettings::Translate(L"Bo'lim: ", L"Section: ", L"Раздел: ") + res[3]->ToString() + L" • " +
					AppSettings::Translate(L"Javon ", L"Shelf ", L"Стеллаж ") + res[4]->ToString() + L" / " +
					AppSettings::Translate(L"qator ", L"row ", L"ряд ") + res[5]->ToString();
				lblMeta->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular);
				lblMeta->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(148, 163, 184) : System::Drawing::Color::FromArgb(100, 116, 139);
				lblMeta->Location = System::Drawing::Point(10, imageHeight + 116);
				lblMeta->Size = System::Drawing::Size(cardWidth - 20, 22);
				lblMeta->AutoEllipsis = true;

				Button^ btnMiniRoute = gcnew Button();
				btnMiniRoute->Name = L"route";
				btnMiniRoute->Text = AppSettings::Translate(L"Yo'nalish", L"Route", L"Маршрут");
				btnMiniRoute->Location = System::Drawing::Point(10, imageHeight + 140);
				btnMiniRoute->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
				btnMiniRoute->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btnMiniRoute->FlatAppearance->BorderSize = 0;
				btnMiniRoute->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(37, 99, 235) : System::Drawing::Color::FromArgb(37, 99, 235);
				btnMiniRoute->ForeColor = System::Drawing::Color::White;
				btnMiniRoute->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 8.8F, System::Drawing::FontStyle::Bold);
				btnMiniRoute->Cursor = Cursors::Hand;
				MakeRounded(btnMiniRoute, 8);

				Button^ btnMiniOpen = gcnew Button();
				btnMiniOpen->Name = L"open";
				btnMiniOpen->Text = AppSettings::Translate(L"Ochish", L"Open", L"Открыть");
				btnMiniOpen->Location = System::Drawing::Point(20 + ((cardWidth - 30) / 2), imageHeight + 140);
				btnMiniOpen->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
				btnMiniOpen->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btnMiniOpen->FlatAppearance->BorderSize = 0;
				btnMiniOpen->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(51, 65, 85) : System::Drawing::Color::FromArgb(226, 232, 240);
				btnMiniOpen->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::White : System::Drawing::Color::FromArgb(30, 41, 59);
				btnMiniOpen->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 8.8F, System::Drawing::FontStyle::Bold);
				btnMiniOpen->Cursor = Cursors::Hand;
				MakeRounded(btnMiniOpen, 8);

				EventHandler^ clickHnd = gcnew EventHandler(this, &MyForm::Card_Click);
				EventHandler^ hoverInHnd = gcnew EventHandler(this, &MyForm::Card_MouseEnter);
				EventHandler^ hoverOutHnd = gcnew EventHandler(this, &MyForm::Card_MouseLeave);
				card->Click += clickHnd;
				pb->Click += clickHnd;
				lblTitle->Click += clickHnd;
				lblDist->Click += clickHnd;
				lblStat->Click += clickHnd;
				lblMeta->Click += clickHnd;
				btnMiniOpen->Click += clickHnd;
				btnMiniRoute->Click += gcnew EventHandler(this, &MyForm::btnMap_Click);
				card->MouseEnter += hoverInHnd;
				pb->MouseEnter += hoverInHnd;
				lblTitle->MouseEnter += hoverInHnd;
				lblDist->MouseEnter += hoverInHnd;
				lblStat->MouseEnter += hoverInHnd;
				lblMeta->MouseEnter += hoverInHnd;
				card->MouseLeave += hoverOutHnd;
				pb->MouseLeave += hoverOutHnd;
				lblTitle->MouseLeave += hoverOutHnd;
				lblDist->MouseLeave += hoverOutHnd;
				lblStat->MouseLeave += hoverOutHnd;
				lblMeta->MouseLeave += hoverOutHnd;

				card->Tag = res; pb->Tag = res; lblTitle->Tag = res; lblDist->Tag = res; lblStat->Tag = res; lblMeta->Tag = res; btnMiniRoute->Tag = res; btnMiniOpen->Tag = res;
				card->Controls->Add(pb); card->Controls->Add(lblTitle); card->Controls->Add(lblDist); card->Controls->Add(lblStat); card->Controls->Add(lblMeta); card->Controls->Add(btnMiniRoute); card->Controls->Add(btnMiniOpen);
				flpResults->Controls->Add(card);
			}
		} catch (...) {
			if (lblResultCount != nullptr) {
				lblResultCount->Text = AppSettings::Translate(L"Natijalar: 0", L"Results: 0", L"Результаты: 0");
			}
		}
		flpResults->ResumeLayout();
	}

	private: System::Void Card_Click(System::Object^ sender, System::EventArgs^ e) {
		Control^ ctrl = dynamic_cast<Control^>(sender);
		if (ctrl != nullptr && ctrl->Tag != nullptr) {
			array<Object^>^ res = dynamic_cast<array<Object^>^>(ctrl->Tag);
			if (res != nullptr && res->Length > 1 && res[1] != nullptr) {
				String^ t = res[1]->ToString();
				if (!String::IsNullOrWhiteSpace(t)) {
					String^ lower = t->ToLower();
					for (int i = recentViewedTitles->Count - 1; i >= 0; --i) {
						if (recentViewedTitles[i]->ToLower() == lower) {
							recentViewedTitles->RemoveAt(i);
						}
					}
					recentViewedTitles->Insert(0, t);
					while (recentViewedTitles->Count > 5) recentViewedTitles->RemoveAt(recentViewedTitles->Count - 1);
					ApplyModernStyle();
					UpdateHeaderLayout();
					UpdateResponsiveLayout();
				}
			}
			ShowBookDetails(res);
		}
	}

	private: System::Void Card_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		Control^ c = dynamic_cast<Control^>(sender);
		if (c == nullptr) return;
		Panel^ card = dynamic_cast<Panel^>(c);
		if (card == nullptr) card = dynamic_cast<Panel^>(c->Parent);
		if (card == nullptr) return;
		card->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(52, 58, 66) : System::Drawing::Color::FromArgb(242, 248, 255);
	}

	private: System::Void Card_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		Control^ c = dynamic_cast<Control^>(sender);
		if (c == nullptr) return;
		Panel^ card = dynamic_cast<Panel^>(c);
		if (card == nullptr) card = dynamic_cast<Panel^>(c->Parent);
		if (card == nullptr) return;
		card->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(40, 45, 52) : System::Drawing::Color::White;
	}

	private: System::Void ShowLoadingSkeleton(int count) {
		if (flpResults == nullptr) return;
		int cardWidth = GetResponsiveCardWidth();
		int imageHeight = static_cast<int>(cardWidth * 0.78);
		if (imageHeight < 138) imageHeight = 138;
		if (imageHeight > 210) imageHeight = 210;
		int cardHeight = imageHeight + 136;
		int n = Math::Max(2, count);

		for (int i = 0; i < n; i++) {
			Panel^ card = gcnew Panel();
			card->Size = System::Drawing::Size(cardWidth, cardHeight);
			card->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(40, 45, 52) : System::Drawing::Color::White;
			card->Margin = System::Windows::Forms::Padding(12);
			MakeRounded(card, 12);

			Panel^ imageBlock = gcnew Panel();
			imageBlock->Size = System::Drawing::Size(cardWidth, imageHeight);
			imageBlock->Location = System::Drawing::Point(0, 0);
			imageBlock->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(64, 70, 78) : System::Drawing::Color::FromArgb(230, 234, 240);

			Panel^ line1 = gcnew Panel();
			line1->Size = System::Drawing::Size(cardWidth - 36, 14);
			line1->Location = System::Drawing::Point(10, imageHeight + 14);
			line1->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(72, 78, 86) : System::Drawing::Color::FromArgb(236, 240, 245);

			Panel^ line2 = gcnew Panel();
			line2->Size = System::Drawing::Size(cardWidth - 72, 11);
			line2->Location = System::Drawing::Point(10, imageHeight + 38);
			line2->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(72, 78, 86) : System::Drawing::Color::FromArgb(236, 240, 245);

			Label^ loadingText = gcnew Label();
			loadingText->Text = AppSettings::Translate(L"Yuklanmoqda...", L"Loading...", L"Загрузка...");
			loadingText->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(130, 138, 145);
			loadingText->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, System::Drawing::FontStyle::Regular);
			loadingText->Location = System::Drawing::Point(10, imageHeight + 60);
			loadingText->AutoSize = true;

			card->Controls->Add(imageBlock);
			card->Controls->Add(line1);
			card->Controls->Add(line2);
			card->Controls->Add(loadingText);
			flpResults->Controls->Add(card);
		}
	}

	private: System::Void ShowBookDetails(array<Object^>^ res) {
		Form^ fd = gcnew Form();
		fd->Text = AppSettings::Translate(L"Kitob haqida ma'lumot", L"Book details", L"Информация о книге");
		fd->Size = System::Drawing::Size(660, 520);
		fd->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(24, 26, 27) : System::Drawing::Color::White;
		fd->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(236, 240, 241) : System::Drawing::Color::FromArgb(33, 37, 41);
		fd->StartPosition = FormStartPosition::CenterParent;
		fd->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		fd->MaximizeBox = false;
		fd->MinimizeBox = false;

		PictureBox^ pb = gcnew PictureBox();
		pb->Size = System::Drawing::Size(180, 240);
		pb->Location = System::Drawing::Point(30, 30);
		pb->SizeMode = PictureBoxSizeMode::StretchImage;
		if (res[0] != nullptr) { pb->Image = dynamic_cast<Image^>(res[0]); }
		System::Drawing::Bitmap^ emptyImage = gcnew System::Drawing::Bitmap(1, 1);
		if (pb->Image == nullptr || pb->Image->Size == emptyImage->Size) { pb->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(70, 70, 70) : System::Drawing::Color::FromArgb(230, 230, 230); }
		MakeRounded(pb, 10);
		fd->Controls->Add(pb);

		Color txtColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(236, 240, 241) : System::Drawing::Color::FromArgb(33, 37, 41);
		Color mutColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);

		Label^ t = gcnew Label();
		t->Text = res[1]->ToString();
		t->Location = System::Drawing::Point(230, 30);
		t->AutoSize = true;
		t->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, System::Drawing::FontStyle::Bold);
		t->ForeColor = txtColor;
		t->MaximumSize = System::Drawing::Size(320, 0); 
		fd->Controls->Add(t);

		int yp = 30 + t->Height + 20;

		Label^ l1 = gcnew Label();
		l1->Text = AppSettings::Translate(L"Kutubxona: ", L"Library: ", L"Библиотека: ") + res[2]->ToString();
		l1->Location = System::Drawing::Point(230, yp);
		l1->AutoSize = true;
		l1->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l1->ForeColor = mutColor;
		fd->Controls->Add(l1);
		yp += 30;

		Label^ l2 = gcnew Label();
		l2->Text = AppSettings::Translate(L"Bo'lim: ", L"Section: ", L"Раздел: ") + res[3]->ToString();
		l2->Location = System::Drawing::Point(230, yp);
		l2->AutoSize = true;
		l2->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l2->ForeColor = mutColor;
		fd->Controls->Add(l2);
		yp += 30;

		Label^ l3 = gcnew Label();
		l3->Text = AppSettings::Translate(L"Joylashuv: ", L"Location: ", L"Местоположение: ") + res[4]->ToString() + L" / " + res[5]->ToString();
		l3->Location = System::Drawing::Point(230, yp);
		l3->AutoSize = true;
		l3->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l3->ForeColor = mutColor;
		fd->Controls->Add(l3);
		yp += 30;

		Label^ l4 = gcnew Label();
		l4->Text = AppSettings::Translate(L"Masofa: ", L"Distance: ", L"Расстояние: ") + res[6]->ToString();
		l4->Location = System::Drawing::Point(230, yp);
		l4->AutoSize = true;
		l4->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l4->ForeColor = mutColor;
		fd->Controls->Add(l4);
		yp += 35;

		Color statColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(95, 220, 140) : System::Drawing::Color::FromArgb(46, 204, 113);
		if (res[7]->ToString() == AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано")) {
			statColor = System::Drawing::Color::FromArgb(255, 99, 132);
		}
		else if (res[7]->ToString() == AppSettings::Translate(L"Band qilingan", L"Reserved", L"Забронировано")) {
			statColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(255, 201, 87) : System::Drawing::Color::FromArgb(240, 156, 0);
		}

		Label^ lst = gcnew Label();
		lst->Text = AppSettings::Translate(L"Holati: ", L"Status: ", L"Статус: ") + res[7]->ToString();
		lst->Location = System::Drawing::Point(230, yp);
		lst->AutoSize = true;
		lst->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, System::Drawing::FontStyle::Bold);
		lst->ForeColor = statColor;
		fd->Controls->Add(lst);

		Button^ btnOk = gcnew Button();
		btnOk->Text = AppSettings::Translate(L"Yopish", L"Close", L"Закрыть");
		btnOk->Location = System::Drawing::Point(500, 430);
		btnOk->Size = System::Drawing::Size(120, 40);
		btnOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnOk->FlatAppearance->BorderSize = 0;
		btnOk->BackColor = System::Drawing::Color::FromArgb(40, 44, 52);
		btnOk->ForeColor = System::Drawing::Color::White;
		btnOk->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold);
		btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
		MakeRounded(btnOk, 10);
		fd->Controls->Add(btnOk);

		Button^ btnMap = gcnew Button();
		btnMap->Text = AppSettings::Translate(L"Yo'nalish", L"Route", L"Маршрут");
		btnMap->Location = System::Drawing::Point(360, 430);
		btnMap->Size = System::Drawing::Size(120, 40);
		btnMap->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnMap->FlatAppearance->BorderSize = 0;
		btnMap->BackColor = System::Drawing::Color::FromArgb(52, 152, 219);
		btnMap->ForeColor = System::Drawing::Color::White;
		btnMap->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold);
		btnMap->Tag = res;
		btnMap->Click += gcnew System::EventHandler(this, &MyForm::btnMap_Click);
		MakeRounded(btnMap, 10);
		fd->Controls->Add(btnMap);

		Button^ btnEbook = gcnew Button();
		btnEbook->Text = AppSettings::Translate(L"E-kitob", L"E-book", L"Эл. книга");
		btnEbook->Location = System::Drawing::Point(220, 430);
		btnEbook->Size = System::Drawing::Size(120, 40);
		btnEbook->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnEbook->FlatAppearance->BorderSize = 0;
		btnEbook->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);
		btnEbook->ForeColor = System::Drawing::Color::White;
		btnEbook->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold);
		btnEbook->Tag = res;
		btnEbook->Click += gcnew System::EventHandler(this, &MyForm::btnOpenEbook_Click);
		MakeRounded(btnEbook, 10);
		fd->Controls->Add(btnEbook);

		GroupBox^ reserveBox = gcnew GroupBox();
		reserveBox->Text = AppSettings::Translate(L"Masofadan band qilish", L"Remote reservation", L"Удаленное бронирование");
		reserveBox->Location = System::Drawing::Point(30, 285);
		reserveBox->Size = System::Drawing::Size(590, 130);
		reserveBox->ForeColor = txtColor;
		reserveBox->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.5F, System::Drawing::FontStyle::Bold);

		Label^ reserveInfo = gcnew Label();
		reserveInfo->AutoSize = false;
		reserveInfo->Location = System::Drawing::Point(16, 30);
		reserveInfo->Size = System::Drawing::Size(400, 78);
		reserveInfo->ForeColor = mutColor;
		reserveInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
		reserveInfo->Text = AppSettings::Translate(
			L"Band qilishdan oldin login qiling. Har bir kutubxona uchun alohida karta talab qilinishi mumkin.",
			L"Login first. A separate library card may be required for each library.",
			L"Сначала войдите. Для каждой библиотеки может требоваться отдельная карта."
		);
		reserveBox->Controls->Add(reserveInfo);

		Button^ btnReserve = gcnew Button();
		btnReserve->Text = AppSettings::Translate(L"Band qilish", L"Reserve", L"Забронировать");
		btnReserve->Location = System::Drawing::Point(430, 76);
		btnReserve->Size = System::Drawing::Size(140, 36);
		btnReserve->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnReserve->FlatAppearance->BorderSize = 0;
		btnReserve->BackColor = System::Drawing::Color::FromArgb(22, 160, 133);
		btnReserve->ForeColor = System::Drawing::Color::White;
		btnReserve->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold);
		btnReserve->Tag = res;
		btnReserve->Click += gcnew System::EventHandler(this, &MyForm::btnReserve_Click);
		MakeRounded(btnReserve, 10);

		bool canReserve = (res[7]->ToString() == AppSettings::Translate(L"Mavjud", L"Available", L"Доступно"));
		btnReserve->Enabled = canReserve;
		reserveInfo->Text = canReserve
			? reserveInfo->Text
			: AppSettings::Translate(L"Bu kitob hozircha band qilish uchun mavjud emas.", L"This book is currently unavailable for reservation.", L"Эта книга сейчас недоступна для бронирования.");

		reserveBox->Controls->Add(btnReserve);
		fd->Controls->Add(reserveBox);

		fd->AcceptButton = btnOk;
		AppSettings::ApplyTheme(fd);
		fd->ShowDialog();
	}

	private: String^ EscapeJson(String^ value) {
		if (String::IsNullOrEmpty(value)) return L"";
		return value->Replace(L"\\", L"\\\\")->Replace(L"\"", L"\\\"");
	}

	private: System::Void UpdateReaderButtonState() {
		if (btnReader == nullptr) return;

		if (String::IsNullOrWhiteSpace(currentReaderToken)) {
			btnReader->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
			btnReader->BackColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(34, 39, 45) : System::Drawing::Color::White;
			btnReader->ForeColor = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(236, 240, 241) : System::Drawing::Color::FromArgb(33, 37, 41);
			return;
		}

		if (currentReaderApproved) {
			btnReader->Text = AppSettings::Translate(L"Kabinet ✓", L"Account ✓", L"Аккаунт ✓");
			btnReader->BackColor = System::Drawing::Color::FromArgb(46, 204, 113);
			btnReader->ForeColor = System::Drawing::Color::White;
		}
		else {
			btnReader->Text = AppSettings::Translate(L"Tekshiruvda", L"Pending", L"Проверка");
			btnReader->BackColor = System::Drawing::Color::FromArgb(240, 156, 0);
			btnReader->ForeColor = System::Drawing::Color::White;
		}
	}

	private: bool LoginReader(String^ cardId, String^ password) {
		WebClient^ client = gcnew WebClient();
		client->Encoding = System::Text::Encoding::UTF8;
		client->Headers[HttpRequestHeader::ContentType] = "application/json";

		String^ loginJson = String::Format(
			"{{\"card_id\":\"{0}\",\"password\":\"{1}\"}}",
			EscapeJson(cardId), EscapeJson(password)
		);

		String^ response = client->UploadString(apiUrl + "readers/login/", "POST", loginJson);
		String^ token = Regex::Match(response, "\"token\":\"([^\"]+)\"")->Groups[1]->Value;
		String^ idText = Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value;
		String^ fullname = Regex::Match(response, "\"fullname\":\"([^\"]+)\"")->Groups[1]->Value;
		String^ cardIdText = Regex::Match(response, "\"card_id\":\"([^\"]+)\"")->Groups[1]->Value;
		String^ approvedText = Regex::Match(response, "\"is_approved\":(true|false)", RegexOptions::IgnoreCase)->Groups[1]->Value;

		if (String::IsNullOrWhiteSpace(token) || String::IsNullOrWhiteSpace(idText)) {
			throw gcnew Exception(AppSettings::Translate(L"Login javobi noto'g'ri.", L"Invalid login response.", L"Некорректный ответ логина."));
		}

		currentReaderId = Int32::Parse(idText);
		currentReaderName = fullname;
		currentReaderCardId = cardIdText;
		currentReaderToken = token;
		currentReaderApproved = (approvedText->ToLower() == "true");
		UpdateReaderButtonState();
		return true;
	}

	private: bool RegisterReader(String^ fullName, String^ phone, String^ password) {
		WebClient^ client = gcnew WebClient();
		client->Encoding = System::Text::Encoding::UTF8;
		client->Headers[HttpRequestHeader::ContentType] = "application/json";

		String^ payload = String::Format(
			"{{\"fullname\":\"{0}\",\"phone\":\"{1}\",\"password\":\"{2}\"}}",
			EscapeJson(fullName),
			EscapeJson(phone),
			EscapeJson(password)
		);

		client->UploadString(apiUrl + "readers/register/", "POST", payload);
		return true;
	}

	private: System::Void LogoutReader() {
		currentReaderId = -1;
		currentReaderName = L"";
		currentReaderCardId = L"";
		currentReaderToken = nullptr;
		currentReaderApproved = false;
		UpdateReaderButtonState();
	}

	private: System::Void LoadReaderLibraryCardsGrid(DataGridView^ dgvCards) {
		if (dgvCards != nullptr) dgvCards->Rows->Clear();
		if (currentReaderId <= 0 || dgvCards == nullptr || String::IsNullOrWhiteSpace(currentReaderToken)) return;

		try {
			WebClient^ cardsCl = gcnew WebClient();
			cardsCl->Encoding = System::Text::Encoding::UTF8;
			cardsCl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			cardsCl->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ cardsJson = cardsCl->DownloadString(apiUrl + "readers/library-cards/");
			MatchCollection^ cardRows = Regex::Matches(cardsJson, "\\{[^{}]+\\}");
			for each(Match^ m in cardRows) {
				String^ obj = m->Value;
				String^ libraryName = Regex::Match(obj, "\"library_name\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ updatedAt = Regex::Match(obj, "\"updated_at\":\"([^\"]*)\"")->Groups[1]->Value;
				if (String::IsNullOrWhiteSpace(libraryName)) continue;
				dgvCards->Rows->Add(libraryName, updatedAt);
			}
		}
		catch (...) {}
	}

	private: System::Void btnUploadLibraryCard_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentReaderId <= 0 || String::IsNullOrWhiteSpace(currentReaderToken)) return;

		try {
			WebClient^ libsCl = gcnew WebClient();
			libsCl->Encoding = System::Text::Encoding::UTF8;
			String^ libsJson = libsCl->DownloadString(apiUrl + "libraries/");
			MatchCollection^ libRows = Regex::Matches(libsJson, "\\{[^{}]+\\}");

			Form^ picker = gcnew Form();
			picker->Text = AppSettings::Translate(L"Kutubxona tanlash", L"Select library", L"Выберите библиотеку");
			picker->Size = System::Drawing::Size(430, 180);
			picker->StartPosition = FormStartPosition::CenterParent;
			picker->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			picker->MaximizeBox = false;
			picker->MinimizeBox = false;

			Label^ lbl = gcnew Label();
			lbl->Text = AppSettings::Translate(L"Karta yuklash uchun kutubxonani tanlang:", L"Select library to upload card:", L"Выберите библиотеку для загрузки карты:");
			lbl->AutoSize = true;
			lbl->Location = Point(18, 20);

			ComboBox^ cmbLibraries = gcnew ComboBox();
			cmbLibraries->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbLibraries->Location = Point(18, 48);
			cmbLibraries->Size = System::Drawing::Size(380, 30);

			for each(Match^ m in libRows) {
				String^ obj = m->Value;
				String^ idText = Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value;
				String^ name = Regex::Match(obj, "\"name\":\"([^\"]+)\"")->Groups[1]->Value;
				if (!String::IsNullOrWhiteSpace(idText) && !String::IsNullOrWhiteSpace(name)) {
					cmbLibraries->Items->Add(idText + L" - " + name);
				}
			}

			if (cmbLibraries->Items->Count > 0) cmbLibraries->SelectedIndex = 0;

			Button^ btnOk = gcnew Button();
			btnOk->Text = AppSettings::Translate(L"Davom etish", L"Continue", L"Продолжить");
			btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			btnOk->Location = Point(290, 90);
			btnOk->Size = System::Drawing::Size(108, 34);

			picker->Controls->Add(lbl);
			picker->Controls->Add(cmbLibraries);
			picker->Controls->Add(btnOk);
			picker->AcceptButton = btnOk;
			AppSettings::ApplyTheme(picker);

			if (picker->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
			if (cmbLibraries->SelectedItem == nullptr) return;

			String^ selectedLibrary = cmbLibraries->SelectedItem->ToString();
			String^ libraryIdText = Regex::Match(selectedLibrary, "^(\\d+)")->Groups[1]->Value;
			if (String::IsNullOrWhiteSpace(libraryIdText)) return;

			OpenFileDialog^ ofd = gcnew OpenFileDialog();
			ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
			if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
			if (!File::Exists(ofd->FileName)) return;

			array<Byte>^ cardBytes = File::ReadAllBytes(ofd->FileName);
			String^ cardB64 = Convert::ToBase64String(cardBytes);

			WebClient^ uploadCl = gcnew WebClient();
			uploadCl->Encoding = System::Text::Encoding::UTF8;
			uploadCl->Headers[HttpRequestHeader::ContentType] = "application/json";
			uploadCl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			uploadCl->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ payload = String::Format(
				"{{\"library\":{0},\"card_image_base64\":\"{1}\"}}",
				libraryIdText,
				EscapeJson(cardB64)
			);
			uploadCl->UploadString(apiUrl + "readers/library-cards/", "POST", payload);

			MessageBox::Show(
				AppSettings::Translate(L"Kutubxona kartasi saqlandi.", L"Library card saved.", L"Карта библиотеки сохранена."),
				AppSettings::Translate(L"Muvaffaqiyat", L"Success", L"Успешно"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);

			Button^ sourceBtn = dynamic_cast<Button^>(sender);
			if (sourceBtn != nullptr && sourceBtn->Tag != nullptr) {
				DataGridView^ dgvCards = dynamic_cast<DataGridView^>(sourceBtn->Tag);
				if (dgvCards != nullptr) LoadReaderLibraryCardsGrid(dgvCards);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				AppSettings::Translate(L"Karta yuklashda xatolik: ", L"Card upload error: ", L"Ошибка загрузки карты: ") + ex->Message,
				AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void LoadReaderActivityGrid(DataGridView^ dgvReservations, DataGridView^ dgvIssues) {
		if (dgvReservations != nullptr) dgvReservations->Rows->Clear();
		if (dgvIssues != nullptr) dgvIssues->Rows->Clear();
		if (currentReaderId <= 0) return;
		System::Collections::Generic::List<String^>^ issuedTitles = gcnew System::Collections::Generic::List<String^>();

		try {
			WebClient^ issueCl = gcnew WebClient();
			issueCl->Encoding = System::Text::Encoding::UTF8;
			String^ issueJson = issueCl->DownloadString(apiUrl + "issues/");
			MatchCollection^ issueRows = Regex::Matches(issueJson, "\\{[^{}]+\\}");
			for each(Match^ m in issueRows) {
				String^ obj = m->Value;
				String^ ridText = Regex::Match(obj, "\"reader\":(\\d+)")->Groups[1]->Value;
				if (String::IsNullOrWhiteSpace(ridText)) continue;
				if (Int32::Parse(ridText) != currentReaderId) continue;

				String^ bookTitle = Regex::Match(obj, "\"book_title\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ issueDate = Regex::Match(obj, "\"issue_date\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ returnDate = Regex::Match(obj, "\"return_date\":\"([^\"]*)\"")->Groups[1]->Value;
				if (!String::IsNullOrWhiteSpace(bookTitle) && !issuedTitles->Contains(bookTitle->ToLower())) {
					issuedTitles->Add(bookTitle->ToLower());
				}

				if (dgvIssues != nullptr) {
					dgvIssues->Rows->Add(bookTitle, issueDate, returnDate);
				}
			}
		}
		catch (...) {}

		try {
			WebClient^ reservCl = gcnew WebClient();
			reservCl->Encoding = System::Text::Encoding::UTF8;
			String^ reservJson = reservCl->DownloadString(apiUrl + "reservations/");
			MatchCollection^ reservRows = Regex::Matches(reservJson, "\\{[^{}]+\\}");
			for each(Match^ m in reservRows) {
				String^ obj = m->Value;
				String^ ridText = Regex::Match(obj, "\"reader\":(\\d+)")->Groups[1]->Value;
				if (String::IsNullOrWhiteSpace(ridText)) continue;
				if (Int32::Parse(ridText) != currentReaderId) continue;

				String^ bookTitle = Regex::Match(obj, "\"book_title\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ reservedAt = Regex::Match(obj, "\"reserved_at\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ note = Regex::Match(obj, "\"note\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ reserveStatus = issuedTitles->Contains(bookTitle->ToLower())
					? AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано")
					: AppSettings::Translate(L"Faol bron", L"Active reservation", L"Активная бронь");

				if (dgvReservations != nullptr) {
					dgvReservations->Rows->Add(bookTitle, reservedAt, note, reserveStatus);
				}
			}
		}
		catch (...) {}
	}

	private: System::Void ShowReaderDashboard() {
		Form^ dash = gcnew Form();
		dash->Text = AppSettings::Translate(L"Reader Dashboard", L"Reader Dashboard", L"Кабинет читателя");
		dash->Size = System::Drawing::Size(860, 560);
		dash->StartPosition = FormStartPosition::CenterParent;
		dash->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		dash->MaximizeBox = false;
		dash->MinimizeBox = false;

		Color panelBg = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(34, 39, 45) : System::Drawing::Color::White;
		Color textMuted = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);

		TabControl^ tabs = gcnew TabControl();
		tabs->Dock = DockStyle::Fill;

		TabPage^ profileTab = gcnew TabPage(AppSettings::Translate(L"Profil", L"Profile", L"Профиль"));
		TabPage^ activityTab = gcnew TabPage(AppSettings::Translate(L"Faollik", L"Activity", L"Активность"));

		Panel^ profileCard = gcnew Panel();
		profileCard->Location = Point(18, 18);
		profileCard->Size = System::Drawing::Size(790, 180);
		profileCard->BackColor = panelBg;
		MakeRounded(profileCard, 12);

		Label^ lblWelcome = gcnew Label();
		lblWelcome->Text = AppSettings::Translate(L"Xush kelibsiz", L"Welcome", L"Добро пожаловать") + L", " + currentReaderName;
		lblWelcome->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.0F, System::Drawing::FontStyle::Bold);
		lblWelcome->AutoSize = true;
		lblWelcome->Location = Point(20, 18);

		Label^ lblCard = gcnew Label();
		lblCard->Text = AppSettings::Translate(L"Karta ID", L"Card ID", L"ID карты") + L": " + currentReaderCardId;
		lblCard->ForeColor = textMuted;
		lblCard->AutoSize = true;
		lblCard->Location = Point(22, 62);

		Label^ lblStatus = gcnew Label();
		lblStatus->Text = currentReaderApproved
			? AppSettings::Translate(L"Status: Tasdiqlangan", L"Status: Approved", L"Статус: Одобрено")
			: AppSettings::Translate(L"Status: Admin tasdig'i kutilmoqda", L"Status: Waiting for admin approval", L"Статус: Ожидает одобрения администратора");
		lblStatus->AutoSize = true;
		lblStatus->Location = Point(22, 90);
		lblStatus->ForeColor = currentReaderApproved
			? System::Drawing::Color::FromArgb(46, 204, 113)
			: System::Drawing::Color::FromArgb(240, 156, 0);

		Button^ btnLogout = gcnew Button();
		btnLogout->Text = AppSettings::Translate(L"Chiqish", L"Logout", L"Выйти");
		btnLogout->Size = System::Drawing::Size(120, 36);
		btnLogout->Location = Point(650, 126);
		btnLogout->FlatStyle = FlatStyle::Flat;
		btnLogout->FlatAppearance->BorderSize = 0;
		btnLogout->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnLogout->ForeColor = System::Drawing::Color::White;
		btnLogout->Click += gcnew EventHandler(this, &MyForm::btnReaderLogout_Click);

		profileCard->Controls->Add(lblWelcome);
		profileCard->Controls->Add(lblCard);
		profileCard->Controls->Add(lblStatus);
		profileCard->Controls->Add(btnLogout);
		profileTab->Controls->Add(profileCard);

		Label^ lblCards = gcnew Label();
		lblCards->Text = AppSettings::Translate(L"Kutubxona kartalari", L"Library cards", L"Карты библиотек");
		lblCards->AutoSize = true;
		lblCards->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
		lblCards->Location = Point(18, 214);

		Button^ btnUploadCard = gcnew Button();
		btnUploadCard->Text = AppSettings::Translate(L"Karta yuklash / yangilash", L"Upload / update card", L"Загрузить / обновить карту");
		btnUploadCard->Size = System::Drawing::Size(220, 34);
		btnUploadCard->Location = Point(588, 208);
		btnUploadCard->FlatStyle = FlatStyle::Flat;
		btnUploadCard->FlatAppearance->BorderSize = 0;
		btnUploadCard->BackColor = System::Drawing::Color::FromArgb(13, 110, 253);
		btnUploadCard->ForeColor = System::Drawing::Color::White;
		btnUploadCard->Click += gcnew EventHandler(this, &MyForm::btnUploadLibraryCard_Click);

		DataGridView^ dgvCards = gcnew DataGridView();
		dgvCards->Location = Point(18, 246);
		dgvCards->Size = System::Drawing::Size(790, 250);
		dgvCards->AllowUserToAddRows = false;
		dgvCards->ReadOnly = true;
		dgvCards->RowHeadersVisible = false;
		dgvCards->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvCards->ColumnCount = 2;
		dgvCards->Columns[0]->Name = AppSettings::Translate(L"Kutubxona", L"Library", L"Библиотека");
		dgvCards->Columns[1]->Name = AppSettings::Translate(L"Yangilangan vaqti", L"Updated at", L"Обновлено");

		btnUploadCard->Tag = dgvCards;

		profileTab->Controls->Add(lblCards);
		profileTab->Controls->Add(btnUploadCard);
		profileTab->Controls->Add(dgvCards);

		Label^ lblRes = gcnew Label();
		lblRes->Text = AppSettings::Translate(L"Mening bronlarim", L"My reservations", L"Мои брони");
		lblRes->AutoSize = true;
		lblRes->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
		lblRes->Location = Point(18, 14);

		DataGridView^ dgvReservations = gcnew DataGridView();
		dgvReservations->Location = Point(18, 38);
		dgvReservations->Size = System::Drawing::Size(790, 180);
		dgvReservations->AllowUserToAddRows = false;
		dgvReservations->ReadOnly = true;
		dgvReservations->RowHeadersVisible = false;
		dgvReservations->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvReservations->ColumnCount = 4;
		dgvReservations->Columns[0]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
		dgvReservations->Columns[1]->Name = AppSettings::Translate(L"Band qilingan sana", L"Reserved at", L"Дата брони");
		dgvReservations->Columns[2]->Name = AppSettings::Translate(L"Izoh", L"Note", L"Примечание");
		dgvReservations->Columns[3]->Name = AppSettings::Translate(L"Holat", L"Status", L"Статус");

		Label^ lblIssued = gcnew Label();
		lblIssued->Text = AppSettings::Translate(L"Menda olingan kitoblar", L"My borrowed books", L"Мои выданные книги");
		lblIssued->AutoSize = true;
		lblIssued->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
		lblIssued->Location = Point(18, 232);

		DataGridView^ dgvMyIssues = gcnew DataGridView();
		dgvMyIssues->Location = Point(18, 256);
		dgvMyIssues->Size = System::Drawing::Size(790, 190);
		dgvMyIssues->AllowUserToAddRows = false;
		dgvMyIssues->ReadOnly = true;
		dgvMyIssues->RowHeadersVisible = false;
		dgvMyIssues->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvMyIssues->ColumnCount = 3;
		dgvMyIssues->Columns[0]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
		dgvMyIssues->Columns[1]->Name = AppSettings::Translate(L"Olingan sana", L"Issue date", L"Дата выдачи");
		dgvMyIssues->Columns[2]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");

		activityTab->Controls->Add(lblRes);
		activityTab->Controls->Add(dgvReservations);
		activityTab->Controls->Add(lblIssued);
		activityTab->Controls->Add(dgvMyIssues);

		tabs->TabPages->Add(profileTab);
		tabs->TabPages->Add(activityTab);
		dash->Controls->Add(tabs);

		LoadReaderActivityGrid(dgvReservations, dgvMyIssues);
		LoadReaderLibraryCardsGrid(dgvCards);
		AppSettings::ApplyTheme(dash);
		dash->ShowDialog();
	}

	private: System::Void btnReaderLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		LogoutReader();
		Button^ b = dynamic_cast<Button^>(sender);
		if (b != nullptr) {
			Form^ f = b->FindForm();
			if (f != nullptr) f->Close();
		}
	}

	private: bool EnsureReaderCanReserve() {
		if (String::IsNullOrWhiteSpace(currentReaderToken) || currentReaderId <= 0) {
			MessageBox::Show(
				AppSettings::Translate(L"Band qilish uchun avval tizimga kiring.", L"Please login before reserving.", L"Перед бронированием войдите в систему."),
				AppSettings::Translate(L"Kirish talab qilinadi", L"Login required", L"Требуется вход"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			return false;
		}

		if (!currentReaderApproved) {
			MessageBox::Show(
				AppSettings::Translate(L"Akkauntingiz admin tasdig'idan o'tmagan.", L"Your account is awaiting admin approval.", L"Ваш аккаунт ожидает одобрения администратора."),
				AppSettings::Translate(L"Tasdiq kutilmoqda", L"Approval pending", L"Ожидается одобрение"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning
			);
			return false;
		}

		return true;
	}

	private: System::Void btnReserve_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<Object^>^ res = dynamic_cast<array<Object^>^>(btn->Tag);
		if (res == nullptr || res->Length < 13) return;
		if (!EnsureReaderCanReserve()) return;

		String^ bookIdText = res[12] != nullptr ? res[12]->ToString() : L"";
		if (String::IsNullOrWhiteSpace(bookIdText)) {
			MessageBox::Show(AppSettings::Translate(L"Kitob ID topilmadi.", L"Book ID not found.", L"ID книги не найден."));
			return;
		}

		try {
			int bookId = Int32::Parse(bookIdText);
			String^ libraryName = res[2] != nullptr ? res[2]->ToString() : L"";

			String^ libraryCardB64 = L"";
			System::Windows::Forms::DialogResult uploadChoice = MessageBox::Show(
				AppSettings::Translate(
					L"Agar ushbu kutubxona uchun kartangiz avval yuklanmagan bo'lsa, ruxsatnoma rasmini yuklang. Hozir yuklaysizmi?",
					L"If your card for this library is not uploaded yet, upload permit image now. Upload now?",
					L"Если карта для этой библиотеки еще не загружена, загрузите изображение сейчас. Загрузить?"
				) + L"\n\n" + AppSettings::Translate(L"Kutubxona", L"Library", L"Библиотека") + L": " + libraryName,
				AppSettings::Translate(L"Kutubxona kartasi", L"Library card", L"Карта библиотеки"),
				MessageBoxButtons::YesNoCancel,
				MessageBoxIcon::Question
			);

			if (uploadChoice == System::Windows::Forms::DialogResult::Cancel) return;

			if (uploadChoice == System::Windows::Forms::DialogResult::Yes) {
				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
				if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
				if (!File::Exists(ofd->FileName)) return;

				array<Byte>^ cardBytes = File::ReadAllBytes(ofd->FileName);
				libraryCardB64 = Convert::ToBase64String(cardBytes);
			}

			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			client->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			client->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ reservJson = String::Format(
				"{{\"reader\":{0},\"book\":{1},\"note\":\"desktop_remote\",\"library_card_image_base64\":\"{2}\"}}",
				currentReaderId, bookId, EscapeJson(libraryCardB64)
			);
			client->UploadString(apiUrl + "reservations/", "POST", reservJson);

			MessageBox::Show(
				AppSettings::Translate(L"Kitob muvaffaqiyatli band qilindi.", L"Book reserved successfully.", L"Книга успешно забронирована."),
				AppSettings::Translate(L"Muvaffaqiyat", L"Success", L"Успешно"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);

			Form^ parentForm = btn->FindForm();
			if (parentForm != nullptr) parentForm->Close();
			LoadBooksToGrid();
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				AppSettings::Translate(L"Band qilishda xatolik: ", L"Reservation error: ", L"Ошибка бронирования: ") + ex->Message,
				AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void btnAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ prompt = gcnew Form();
		prompt->Width = 300;
		prompt->Height = 160;
		prompt->Text = AppSettings::Translate(L"Autentifikatsiya", L"Authentication", L"Аутентификация");
		prompt->StartPosition = FormStartPosition::CenterParent;
		prompt->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		prompt->MaximizeBox = false;
		prompt->MinimizeBox = false;

		Label^ textLabel = gcnew Label();
		textLabel->Left = 20;
		textLabel->Top = 20;
		textLabel->Text = AppSettings::Translate(L"Admin parolini kiriting:", L"Enter admin password:", L"Введите пароль администратора:");
		textLabel->AutoSize = true;

		TextBox^ inputBox = gcnew TextBox();
		inputBox->Left = 20;
		inputBox->Top = 45;
		inputBox->Width = 240;
		inputBox->PasswordChar = '*';

		Button^ confirmation = gcnew Button();
		confirmation->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
		confirmation->Left = 160;
		confirmation->Top = 75;
		confirmation->Width = 100;
		confirmation->DialogResult = System::Windows::Forms::DialogResult::OK;

		prompt->Controls->Add(textLabel);
		prompt->Controls->Add(inputBox);
		prompt->Controls->Add(confirmation);
		prompt->AcceptButton = confirmation;
		AppSettings::ApplyTheme(prompt);

		if (prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (inputBox->Text == L"TATU2026") {
				AdminForm^ adminForm = gcnew AdminForm();
				AppSettings::ApplyTheme(adminForm);
				adminForm->ShowDialog();
				LoadDataFilters();
				LoadBooksToGrid();
				if (this->marqueeTimer != nullptr) this->marqueeTimer->Stop();
			}
			else {
				MessageBox::Show(
					AppSettings::Translate(L"Parol noto'g'ri!", L"Incorrect password!", L"Неверный пароль!"),
					AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
			}
		}
	}

	private: System::Void btnAbout_Click(System::Object^ sender, System::EventArgs^ e) {
		AboutForm^ infoForm = gcnew AboutForm();
		AppSettings::ApplyTheme(infoForm);
		infoForm->ShowDialog();
	}

	private: System::Void btnStat_Click(System::Object^ sender, System::EventArgs^ e) {
		StatisticsForm^ statForm = gcnew StatisticsForm();
		AppSettings::ApplyTheme(statForm);
		statForm->ShowDialog();
	}

	private: System::Void btnReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!String::IsNullOrWhiteSpace(currentReaderToken)) {
			ShowReaderDashboard();
			return;
		}

		Form^ prompt = gcnew Form();
		prompt->Text = AppSettings::Translate(L"Reader autentifikatsiya", L"Reader authentication", L"Аутентификация читателя");
		prompt->Size = System::Drawing::Size(480, 520);
		prompt->MinimumSize = System::Drawing::Size(440, 480);
		prompt->StartPosition = FormStartPosition::CenterParent;
		prompt->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		prompt->MaximizeBox = false;
		prompt->MinimizeBox = false;

		TabControl^ tabs = gcnew TabControl();
		tabs->Dock = DockStyle::Fill;
		prompt->Controls->Add(tabs);

		// === Kirish (Login) Tab ===
		TabPage^ tabLogin = gcnew TabPage();
		tabLogin->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");

		int left = 20;
		int top = 18;
		int fieldW = 390;
		int lineH = 30;
		int gapY = 10;

		Label^ lblCardL = gcnew Label();
		lblCardL->Text = AppSettings::Translate(L"Karta ID", L"Card ID", L"ID карты");
		lblCardL->Location = Point(left, top);
		lblCardL->AutoSize = true;
		top += 22;

		TextBox^ txtCardL = gcnew TextBox();
		txtCardL->Location = Point(left, top);
		txtCardL->Size = System::Drawing::Size(fieldW, lineH);
		top += lineH + gapY;

		Label^ lblPasswordL = gcnew Label();
		lblPasswordL->Text = AppSettings::Translate(L"Parol", L"Password", L"Пароль");
		lblPasswordL->Location = Point(left, top);
		lblPasswordL->AutoSize = true;
		top += 22;

		TextBox^ txtPasswordL = gcnew TextBox();
		txtPasswordL->Location = Point(left, top);
		txtPasswordL->Size = System::Drawing::Size(fieldW, lineH);
		txtPasswordL->PasswordChar = '*';
		top += lineH + 18;

		Button^ btnLogin = gcnew Button();
		btnLogin->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
		btnLogin->Location = Point(left, top);
		btnLogin->Size = System::Drawing::Size(120, 36);
		btnLogin->DialogResult = System::Windows::Forms::DialogResult::No;

		tabLogin->Controls->Add(lblCardL);
		tabLogin->Controls->Add(txtCardL);
		tabLogin->Controls->Add(lblPasswordL);
		tabLogin->Controls->Add(txtPasswordL);
		tabLogin->Controls->Add(btnLogin);
		tabs->TabPages->Add(tabLogin);
		prompt->AcceptButton = btnLogin;

		// === Ro'yxatdan o'tish (Register) Tab ===
		TabPage^ tabReg = gcnew TabPage();
		tabReg->Text = AppSettings::Translate(L"Ro'yxatdan o'tish", L"Register", L"Регистрация");

		top = 18;

		Label^ lblName = gcnew Label();
		lblName->Text = AppSettings::Translate(L"F.I.Sh", L"Full name", L"ФИО");
		lblName->Location = Point(left, top);
		lblName->AutoSize = true;
		top += 22;

		TextBox^ txtName = gcnew TextBox();
		txtName->Location = Point(left, top);
		txtName->Size = System::Drawing::Size(fieldW, lineH);
		top += lineH + gapY;

		Label^ lblPhone = gcnew Label();
		lblPhone->Text = AppSettings::Translate(L"Telefon", L"Phone", L"Телефон");
		lblPhone->Location = Point(left, top);
		lblPhone->AutoSize = true;
		top += 22;

		TextBox^ txtPhone = gcnew TextBox();
		txtPhone->Location = Point(left, top);
		txtPhone->Size = System::Drawing::Size(fieldW, lineH);
		top += lineH + gapY;

		Label^ lblPasswordR = gcnew Label();
		lblPasswordR->Text = AppSettings::Translate(L"Parol", L"Password", L"Пароль");
		lblPasswordR->Location = Point(left, top);
		lblPasswordR->AutoSize = true;
		top += 22;

		TextBox^ txtPasswordR = gcnew TextBox();
		txtPasswordR->Location = Point(left, top);
		txtPasswordR->Size = System::Drawing::Size(fieldW, lineH);
		txtPasswordR->PasswordChar = '*';
		top += lineH + 18;

		Button^ btnRegister = gcnew Button();
		btnRegister->Text = AppSettings::Translate(L"Ro'yxatdan o'tish", L"Register", L"Регистрация");
		btnRegister->Location = Point(left, top);
		btnRegister->Size = System::Drawing::Size(140, 36);
		btnRegister->DialogResult = System::Windows::Forms::DialogResult::Yes;

		tabReg->Controls->Add(lblName);
		tabReg->Controls->Add(txtName);
		tabReg->Controls->Add(lblPhone);
		tabReg->Controls->Add(txtPhone);
		tabReg->Controls->Add(lblPasswordR);
		tabReg->Controls->Add(txtPasswordR);
		tabReg->Controls->Add(btnRegister);
		tabs->TabPages->Add(tabReg);

		AppSettings::ApplyTheme(prompt);

		System::Windows::Forms::DialogResult authResult = prompt->ShowDialog();
		if (authResult != System::Windows::Forms::DialogResult::No && authResult != System::Windows::Forms::DialogResult::Yes) return;

		try {
			if (authResult == System::Windows::Forms::DialogResult::No) {
				if (String::IsNullOrWhiteSpace(txtCardL->Text) || String::IsNullOrWhiteSpace(txtPasswordL->Text)) {
					MessageBox::Show(AppSettings::Translate(L"Karta ID va parolni kiriting.", L"Enter card ID and password.", L"Введите ID карты и пароль."));
					return;
				}
				LoginReader(txtCardL->Text->Trim(), txtPasswordL->Text);
				MessageBox::Show(
					currentReaderApproved
						? AppSettings::Translate(L"Kirish muvaffaqiyatli.", L"Login successful.", L"Вход выполнен.")
						: AppSettings::Translate(L"Kirish muvaffaqiyatli. Admin tasdiqlashi kutilmoqda.", L"Login successful. Awaiting admin approval.", L"Вход выполнен. Ожидается одобрение администратора."),
					AppSettings::Translate(L"Muvaffaqiyat", L"Success", L"Успешно"),
					MessageBoxButtons::OK,
					MessageBoxIcon::Information
				);
			}
			else {
				if (String::IsNullOrWhiteSpace(txtPasswordR->Text)
					|| String::IsNullOrWhiteSpace(txtName->Text) || String::IsNullOrWhiteSpace(txtPhone->Text)) {
					MessageBox::Show(AppSettings::Translate(L"Ro'yxatdan o'tish uchun barcha maydonlarni to'ldiring.", L"Fill all registration fields.", L"Заполните все поля регистрации."));
					return;
				}

				RegisterReader(txtName->Text->Trim(), txtPhone->Text->Trim(), txtPasswordR->Text);
				MessageBox::Show(
					AppSettings::Translate(L"Ro'yxatdan o'tdingiz. Endi admin tasdiqlashini kuting.", L"Registration completed. Please wait for admin approval.", L"Регистрация завершена. Дождитесь одобрения администратора."),
					AppSettings::Translate(L"Qabul qilindi", L"Submitted", L"Отправлено"),
					MessageBoxButtons::OK,
					MessageBoxIcon::Information
				);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				AppSettings::Translate(L"Autentifikatsiya xatosi: ", L"Authentication error: ", L"Ошибка аутентификации: ") + ex->Message,
				AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void OnPickCard_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		TextBox^ target = dynamic_cast<TextBox^>(btn->Tag);
		if (target == nullptr) return;
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			target->Text = ofd->FileName;
		}
	}

	private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		SettingsForm^ sF = gcnew SettingsForm();
		if (sF->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			ApplyModernStyle();
			LoadBooksToGrid();
		}
	}

	private: System::Void btnHistory_Click(System::Object^ sender, System::EventArgs^ e) {
		HistoryForm^ hF = gcnew HistoryForm();
		AppSettings::ApplyTheme(hF);
		hF->ShowDialog();
	}

	private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadBooksToGrid();
	}

	private: System::Void txtSearch_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e == nullptr) return;
		if (e->KeyCode == Keys::Enter) {
			e->SuppressKeyPress = true;
			if (searchDebounceTimer != nullptr) searchDebounceTimer->Stop();
			LoadBooksToGrid();
		}
	}

	private: System::Void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (isUiUpdating || searchDebounceTimer == nullptr) return;
		searchDebounceTimer->Stop();
		searchDebounceTimer->Start();
	}

	private: System::Void searchDebounceTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (searchDebounceTimer != nullptr) searchDebounceTimer->Stop();
		if (isUiUpdating) return;
		LoadBooksToGrid();
	}

	private: System::Void SetStatusFilter(String^ statusKey) {
		activeStatusFilter = String::IsNullOrWhiteSpace(statusKey) ? L"all" : statusKey;
		ApplyModernStyle();
		LoadBooksToGrid();
	}

	private: System::Void btnStatusAll_Click(System::Object^ sender, System::EventArgs^ e) {
		SetStatusFilter(L"all");
	}

	private: System::Void btnStatusAvailable_Click(System::Object^ sender, System::EventArgs^ e) {
		SetStatusFilter(L"available");
	}

	private: System::Void btnStatusReserved_Click(System::Object^ sender, System::EventArgs^ e) {
		SetStatusFilter(L"reserved");
	}

	private: System::Void btnStatusIssued_Click(System::Object^ sender, System::EventArgs^ e) {
		SetStatusFilter(L"issued");
	}

	private: System::Void OnFiltersChanged(System::Object^ sender, System::EventArgs^ e) {
      if (isUiUpdating) return;
		LoadBooksToGrid();
	}

	private: System::Void btnMap_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ b = dynamic_cast<Button^>(sender);
		if (b == nullptr || b->Tag == nullptr) return;
		array<Object^>^ res = dynamic_cast<array<Object^>^>(b->Tag);
		if (res == nullptr || res->Length < 11) return;

		String^ lat = res[9]->ToString();
		String^ lon = res[10]->ToString();
		String^ url = L"https://www.google.com/maps?q=" + lat + L"," + lon;
		Process::Start(url);
	}

	private: System::Void btnOpenEbook_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ b = dynamic_cast<Button^>(sender);
		if (b == nullptr || b->Tag == nullptr) return;
		array<Object^>^ res = dynamic_cast<array<Object^>^>(b->Tag);
		if (res == nullptr || res->Length < 12) return;

		String^ ebookPath = res[11] != nullptr ? res[11]->ToString() : L"";
		if (String::IsNullOrWhiteSpace(ebookPath)) {
			MessageBox::Show(
				AppSettings::Translate(L"Bu kitob uchun elektron fayl biriktirilmagan.", L"No electronic file is attached for this book.", L"Для этой книги не прикреплен электронный файл."),
				AppSettings::Translate(L"Ma'lumot", L"Information", L"Информация"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			return;
		}

		String^ fullPath = File::Exists(ebookPath) ? ebookPath : Path::Combine(Application::StartupPath, ebookPath);
		if (!File::Exists(fullPath)) {
			MessageBox::Show(
				AppSettings::Translate(L"E-kitob fayli topilmadi.", L"E-book file not found.", L"Файл электронной книги не найден."),
				AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
			return;
		}

		Process::Start(fullPath);
	}

	private: System::Void btnShowAll_Click(System::Object^ sender, System::EventArgs^ e) {
      isUiUpdating = true;
		txtSearch->Text = L"";
		if (cmbFilterLibrary->Items->Count > 0) cmbFilterLibrary->SelectedIndex = 0;
		if (cmbFilterSection->Items->Count > 0) cmbFilterSection->SelectedIndex = 0;
      if (cmbRadius->Items->Count > 0) cmbRadius->SelectedIndex = 0;
		if (cmbSort->Items->Count > 0) cmbSort->SelectedIndex = 0;
		activeStatusFilter = L"all";
      if (chkEbookOnly != nullptr) chkEbookOnly->Checked = false;
      isUiUpdating = false;
		ApplyModernStyle();
		LoadBooksToGrid();
	}

	private: int CompareDistance(array<Object^>^ a, array<Object^>^ b) {
		double dist1 = Double::Parse(a[8]->ToString(), System::Globalization::CultureInfo::InvariantCulture);
		double dist2 = Double::Parse(b[8]->ToString(), System::Globalization::CultureInfo::InvariantCulture);
		return dist1.CompareTo(dist2);
	}

	private: int CompareTitle(array<Object^>^ a, array<Object^>^ b) {
		String^ t1 = a[1] != nullptr ? a[1]->ToString() : L"";
		String^ t2 = b[1] != nullptr ? b[1]->ToString() : L"";
		return String::Compare(t1, t2, StringComparison::CurrentCultureIgnoreCase);
	}

	private: int CompareAvailabilityThenDistance(array<Object^>^ a, array<Object^>^ b) {
		String^ s1 = a[7] != nullptr ? a[7]->ToString() : L"";
		String^ s2 = b[7] != nullptr ? b[7]->ToString() : L"";
		String^ availableUz = L"Mavjud";
		String^ availableEn = L"Available";
		String^ availableRu = L"Доступно";

		bool aAvailable = (s1 == availableUz || s1 == availableEn || s1 == availableRu);
		bool bAvailable = (s2 == availableUz || s2 == availableEn || s2 == availableRu);
		if (aAvailable != bAvailable) {
			return aAvailable ? -1 : 1;
		}

		return CompareDistance(a, b);
	}

	private: System::Void marqueeTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (marqueeStep == 0) return;
		if (lblMarquee == nullptr) return;
		lblMarquee->Left += marqueeStep;
		if (lblMarquee->Left > this->ClientSize.Width) {
			lblMarquee->Left = -lblMarquee->Width;
		}
	}

	};
}
