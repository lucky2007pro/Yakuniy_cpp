#pragma once
#include "AdminForm.h"
#include "AboutForm.h"
#include "LibrariesForm.h"
#include "StatisticsForm.h"
#include "ReaderForm.h"
#include "SettingsForm.h"
#include "HistoryForm.h"
#include "AppSettings.h"
#include "LoginForm.h"
#include "BookDetailForm.h"
#include "LibraryCardForm.h"
#include "FavouritesForm.h"

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
			this->txtAuthorFilter = (gcnew System::Windows::Forms::TextBox());
			this->lblAuthorFilter = (gcnew System::Windows::Forms::Label());
			this->btnFavourites = (gcnew System::Windows::Forms::Button());
			this->histPanel = (gcnew System::Windows::Forms::Panel());
			this->histList = (gcnew System::Windows::Forms::ListBox());
			this->btnLibraries = (gcnew System::Windows::Forms::Button());
			this->txtIsbnFilter = (gcnew System::Windows::Forms::TextBox());
			this->lblIsbnFilter = (gcnew System::Windows::Forms::Label());
			this->_toastPanel = (gcnew System::Windows::Forms::Panel());
			this->_toastLabel = (gcnew System::Windows::Forms::Label());
			this->_toastTimer = (gcnew System::Windows::Forms::Timer());

			this->Controls->Add(this->txtAuthorFilter);
			this->Controls->Add(this->lblAuthorFilter);
			this->Controls->Add(this->btnFavourites);
			this->Controls->Add(this->histPanel);
			this->Controls->Add(this->btnLibraries);
			this->Controls->Add(this->txtIsbnFilter);
			this->Controls->Add(this->lblIsbnFilter);
			this->_toastPanel->Controls->Add(this->_toastLabel);
			this->Controls->Add(this->_toastPanel);

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
			this->txtSearch->Enter += gcnew System::EventHandler(this, &MyForm::txtSearch_Enter_History);
			this->txtAuthorFilter->TextChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->btnLibraries->Click += gcnew System::EventHandler(this, &MyForm::btnLibraries_Click);
			this->txtIsbnFilter->TextChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->btnFavourites->Click += gcnew System::EventHandler(this, &MyForm::btnFavourites_Click);
			this->histList->Click += gcnew System::EventHandler(this, &MyForm::histList_Click);
			this->_toastTimer->Interval = 3200;
			this->_toastTimer->Tick += gcnew System::EventHandler(this, &MyForm::toastTimer_Tick);
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
	private: System::Windows::Forms::Button^ btnTopBooks;
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
private: System::Windows::Forms::Label^ lblAuthorFilter;
private: System::Windows::Forms::TextBox^ txtAuthorFilter;
private: System::Windows::Forms::Button^ btnFavourites;
private: System::Windows::Forms::Panel^ histPanel;
private: System::Windows::Forms::ListBox^ histList;
private: System::Windows::Forms::Button^ btnLibraries;
private: System::Windows::Forms::Panel^ _toastPanel;
private: System::Windows::Forms::Label^ _toastLabel;
private: System::Windows::Forms::Timer^ _toastTimer;
private: System::Windows::Forms::TextBox^ txtIsbnFilter;
private: System::Windows::Forms::Label^ lblIsbnFilter;
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
		String^ currentReaderPhone = L"";
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
			this->btnTopBooks = (gcnew System::Windows::Forms::Button());
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
			// btnTopBooks
			// 
			this->btnTopBooks->Location = System::Drawing::Point(540, 12);
		 this->btnTopBooks->Name = L"btnTopBooks";
		 this->btnTopBooks->Size = System::Drawing::Size(96, 30);
		 this->btnTopBooks->TabIndex = 9;
		 this->btnTopBooks->Text = L"Top kitoblar";
		 this->btnTopBooks->UseVisualStyleBackColor = true;
		 this->btnTopBooks->Click += gcnew System::EventHandler(this, &MyForm::btnTopBooks_Click);
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
			this->Controls->Add(this->btnTopBooks);
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
			return System::Convert::ToString(meters) + L" m";
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
		int topAnchor = 138; // Fixed: right after navbar border (136px + 2px border)
		int topOffset = topAnchor + 4;
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
		right = PlaceHeaderButton(btnLibraries, right, topY, 118, gap);
		right = PlaceHeaderButton(btnHistory, right, topY, 82, gap);
		right = PlaceHeaderButton(btnFavourites, right, topY, 118, gap);
		right = PlaceHeaderButton(btnStat, right, topY, 90, gap);
		right = PlaceHeaderButton(btnTopBooks, right, topY, 108, gap);
		right = PlaceHeaderButton(btnReader, right, topY, 108, gap);

		lblSearch->Location = System::Drawing::Point(margin, 18);
		lblSearch->Visible = false;
		int searchX = margin + 10; // Start search from left margin directly
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
		cmbFilterLibrary->Size = System::Drawing::Size(116, 30);
		x = cmbFilterLibrary->Right + 10;

		lblFilterSec->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblFilterSec->Right + 4;
		cmbFilterSection->Location = System::Drawing::Point(x, row2Y);
		cmbFilterSection->Size = System::Drawing::Size(116, 30);
		x = cmbFilterSection->Right + 10;

		lblRadius->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblRadius->Right + 4;
		cmbRadius->Location = System::Drawing::Point(x, row2Y);
		cmbRadius->Size = System::Drawing::Size(96, 30);
		x = cmbRadius->Right + 10;

		chkEbookOnly->Location = System::Drawing::Point(x, row2Y + 4);
		x = chkEbookOnly->Right + 14;

		lblSort->Location = System::Drawing::Point(x, row2Y + 3);
		x = lblSort->Right + 6;
		cmbSort->Location = System::Drawing::Point(x, row2Y);
		cmbSort->Size = System::Drawing::Size(170, 30);

		// Author + ISBN filters — placed after sort, shown if there is space
		if (lblAuthorFilter != nullptr && txtAuthorFilter != nullptr) {
			int ax = cmbSort->Right + 12;
			int ax2 = ax + Math::Max(50, lblAuthorFilter->PreferredWidth) + 4;
			int tw = 130;
			bool hasSpace = (btnShowAll != nullptr) && ((ax2 + tw + 8) < (btnShowAll->Left - 150));
			lblAuthorFilter->Location = System::Drawing::Point(ax, row2Y + 4);
			txtAuthorFilter->Location = System::Drawing::Point(ax2, row2Y);
			txtAuthorFilter->Size = System::Drawing::Size(tw, 30);
			lblAuthorFilter->Visible = hasSpace;
			txtAuthorFilter->Visible = hasSpace;

			// ISBN — after author filter
			if (lblIsbnFilter != nullptr && txtIsbnFilter != nullptr) {
				int ix = hasSpace ? (txtAuthorFilter->Right + 10) : ax;
				int ix2 = ix + 44;
				int tw2 = 110;
				bool hasSpace2 = (btnShowAll != nullptr) && ((ix2 + tw2 + 8) < (btnShowAll->Left));
				lblIsbnFilter->Location = System::Drawing::Point(ix, row2Y + 4);
				txtIsbnFilter->Location = System::Drawing::Point(ix2, row2Y);
				txtIsbnFilter->Size = System::Drawing::Size(tw2, 30);
				lblIsbnFilter->Visible = hasSpace && hasSpace2;
				txtIsbnFilter->Visible = hasSpace && hasSpace2;
			}
		}

		btnShowAll->Size = System::Drawing::Size(108, 35);
		btnShowAll->Location = System::Drawing::Point(this->ClientSize.Width - margin - btnShowAll->Width, row2Y - 2);
		lblResultCount->AutoSize = true;
		lblResultCount->Location = System::Drawing::Point(Math::Max(margin, btnShowAll->Left - 210), row2Y + 6);

		// Navbar panellarini kenglikka moslashtirish
		for each (Control^ c in this->Controls) {
			if (c->Name == L"__navbarStrip") { c->Size = System::Drawing::Size(this->ClientSize.Width, 136); break; }
		}
		for each (Control^ c in this->Controls) {
			if (c->Name == L"__navBorder") { c->Location = System::Drawing::Point(0, 136); c->Size = System::Drawing::Size(this->ClientSize.Width, 2); break; }
		}

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

		// Marquee — navbar ichida quyi band (row3Y + chip quyisi)
		lblMarquee->Top = 118;
		lblMarquee->Left = -Math::Max(200, lblMarquee->Width);

		if (lblRecent != nullptr) lblRecent->Visible = false;
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
		Color darkBg = AppSettings::PageBackColor();
		Color panelBg = AppSettings::SurfaceColor();
		Color accentColor = AppSettings::PrimaryColor();
		Color textColor = AppSettings::TextColor();
		Color textMuted = AppSettings::MutedTextColor();
		Color elevatedColor = AppSettings::ElevatedColor();

		this->Text = AppSettings::Translate(L"Kutubxona Tizimi", L"Library System", L"Библиотечная система");
		lblSearch->Text = L"";
		lblSearch->Visible = false; // Hidden — search starts from left
		lblSort->Text = AppSettings::Translate(L"Sort:", L"Sort:", L"Сорт:");
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
			lblRecent->Visible = false; // Hidden — saves space below navbar
		}

		this->BackColor = darkBg;
		this->ForeColor = textColor;
		this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

		// ─ Oq navbar paneli (saytdek) ─
		Panel^ navbarStrip = nullptr;
		for each (Control^ c in this->Controls) {
			if (c->Name == L"__navbarStrip") { navbarStrip = dynamic_cast<Panel^>(c); break; }
		}
		if (navbarStrip == nullptr) {
			navbarStrip = gcnew Panel();
			navbarStrip->Name = L"__navbarStrip";
			this->Controls->Add(navbarStrip);
		}
		navbarStrip->Location = System::Drawing::Point(0, 0);
		navbarStrip->Size = System::Drawing::Size(this->ClientSize.Width, 136);
		navbarStrip->BackColor = AppSettings::NavbarColor();
		navbarStrip->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
		navbarStrip->SendToBack();

		// ─ Navbar bottom border (1px, slate-200) ─
		Panel^ navBorder = nullptr;
		for each (Control^ c in this->Controls) {
			if (c->Name == L"__navBorder") { navBorder = dynamic_cast<Panel^>(c); break; }
		}
		if (navBorder == nullptr) {
			navBorder = gcnew Panel();
			navBorder->Name = L"__navBorder";
			this->Controls->Add(navBorder);
		}
		navBorder->Location = System::Drawing::Point(0, 136);
		navBorder->Size = System::Drawing::Size(this->ClientSize.Width, 2);
		navBorder->BackColor = AppSettings::NavbarBorderColor();
		navBorder->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
		navBorder->BringToFront();

		AppSettings::StyleSectionTitle(lblSearch);
		lblSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);
		AppSettings::StyleInput(txtSearch);
		txtSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.5F));
		txtSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);

       lblSearch->Location = System::Drawing::Point(20, 25);
		txtSearch->Location = System::Drawing::Point(230, 22);
		txtSearch->Size = System::Drawing::Size(270, 30);

		// Secondary tugmalar uchun border rangi — oq fonda ham ajralib tursin
		Color secondaryBtnBg = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(34, 39, 45)
			: System::Drawing::Color::FromArgb(244, 246, 250);
		Color secondaryBorder = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(55, 65, 81)
			: System::Drawing::Color::FromArgb(209, 213, 219);

        array<Button^>^ buttons = { btnSearch, btnReader, btnStat, btnHistory, btnAbout, btnSettings, btnAdmin, btnShowAll, btnTopBooks, btnFavourites };
		for each (Button^ btn in buttons) {
			if (btn != nullptr) {
				AppSettings::StyleModernButton(btn, true);
				btn->Height = 38;
			}
		}

		// Saytdek "nav link" ko'rinish — oq bg, slate rang, ingichka border
		array<Button^>^ navLinkBtns = { btnStat, btnHistory, btnAbout, btnSettings, btnTopBooks, btnLibraries };
		for each (Button^ sb in navLinkBtns) {
			if (sb == nullptr) continue;
			sb->BackColor = AppSettings::NavbarColor();
			sb->ForeColor = AppSettings::MutedTextColor();
			sb->FlatAppearance->BorderSize = 0;
			sb->FlatAppearance->MouseOverBackColor = AppSettings::CardHoverColor();
			sb->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.0F, System::Drawing::FontStyle::Bold);
		}
		// Reader/Login button — outline style
		if (btnReader != nullptr) {
			btnReader->BackColor = AppSettings::NavbarColor();
			btnReader->ForeColor = AppSettings::TextColor();
			btnReader->FlatAppearance->BorderSize = 1;
			btnReader->FlatAppearance->BorderColor = AppSettings::BorderColor();
			btnReader->FlatAppearance->MouseOverBackColor = AppSettings::CardHoverColor();
		}
		// Favourites — red accent like web
		if (btnFavourites != nullptr) {
			btnFavourites->BackColor = AppSettings::DarkMode
				? System::Drawing::Color::FromArgb(127, 29, 29)
				: System::Drawing::Color::FromArgb(254, 242, 242);
			btnFavourites->ForeColor = System::Drawing::Color::FromArgb(220, 38, 38);
			btnFavourites->FlatAppearance->BorderSize = 0;
			btnFavourites->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(254, 226, 226);
			btnFavourites->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.0F, System::Drawing::FontStyle::Bold);
		}
		// ShowAll (Reset) — outline
		if (btnShowAll != nullptr) {
			btnShowAll->BackColor = AppSettings::NavbarColor();
			btnShowAll->ForeColor = AppSettings::MutedTextColor();
			btnShowAll->FlatAppearance->BorderSize = 1;
			btnShowAll->FlatAppearance->BorderColor = AppSettings::BorderColor();
			btnShowAll->FlatAppearance->MouseOverBackColor = AppSettings::CardHoverColor();
		}

		btnSearch->Location = System::Drawing::Point(510, 20);
		btnSearch->Size = System::Drawing::Size(80, 35);
		btnSearch->BackColor = accentColor;
		btnSearch->ForeColor = AppSettings::PrimaryTextColor();
		btnSearch->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnReader->Location = System::Drawing::Point(600, 20);
		btnReader->Size = System::Drawing::Size(108, 35);
		btnReader->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
		btnReader->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnStat->Location = System::Drawing::Point(700, 20);
		btnStat->Size = System::Drawing::Size(90, 35);
		btnStat->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnHistory->Location = System::Drawing::Point(800, 20);
		btnHistory->Size = System::Drawing::Size(80, 35);
		btnHistory->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnAbout->Location = System::Drawing::Point(890, 20);
		btnAbout->Size = System::Drawing::Size(80, 35);
		btnAbout->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnSettings->Location = System::Drawing::Point(980, 20);
		btnSettings->Size = System::Drawing::Size(105, 35);
		btnSettings->Text = AppSettings::Translate(L"Sozlamalar", L"Settings", L"Настройки");
		btnSettings->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		btnLibraries->Text = AppSettings::Translate(L"Kutubxonalar", L"Libraries", L"Библиотеки");

		btnAdmin->Location = System::Drawing::Point(1095, 20);
		btnAdmin->Size = System::Drawing::Size(100, 35);
		btnAdmin->BackColor = accentColor;
		btnAdmin->ForeColor = AppSettings::PrimaryTextColor();
		btnAdmin->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		lblFilterLib->Text = AppSettings::Translate(L"Kutubxona:", L"Library:", L"Библиотека:");
		lblFilterLib->ForeColor = textMuted;
		lblFilterLib->Location = System::Drawing::Point(20, 70);
		cmbFilterLibrary->Location = System::Drawing::Point(115, 68);
		cmbFilterLibrary->Size = System::Drawing::Size(200, 30);
		AppSettings::StyleInput(cmbFilterLibrary);
		cmbFilterLibrary->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbFilterLibrary->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		lblFilterSec->Text = AppSettings::Translate(L"Bo'lim:", L"Section:", L"Раздел:");
		lblFilterSec->ForeColor = textMuted;
		lblFilterSec->Location = System::Drawing::Point(335, 70);
		cmbFilterSection->Location = System::Drawing::Point(395, 68);
		cmbFilterSection->Size = System::Drawing::Size(180, 30);
		AppSettings::StyleInput(cmbFilterSection);
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
				? AppSettings::SuccessColor()
				: textMuted;
			lblLocationStatus->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
		}
		lblRadius->Location = System::Drawing::Point(590, 70);
		cmbRadius->Location = System::Drawing::Point(650, 68);
		cmbRadius->Size = System::Drawing::Size(130, 30);
		AppSettings::StyleInput(cmbRadius);
		cmbRadius->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		cmbRadius->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left);

		lblSort->Location = System::Drawing::Point(940, 70);
		cmbSort->Location = System::Drawing::Point(1015, 68);
		cmbSort->Size = System::Drawing::Size(180, 30);
		AppSettings::StyleInput(cmbSort);
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
		// BackColor yuqoridagi secondary loop tomonidan o'rnatiladi — ko'rinadigan border bilan
		btnShowAll->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		array<Button^>^ statusButtons = { btnStatusAll, btnStatusAvailable, btnStatusReserved, btnStatusIssued };
		for each (Button ^ sb in statusButtons) {
			if (sb == nullptr) continue;
			sb->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			sb->FlatAppearance->BorderSize = 0;
			sb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold);
			sb->Cursor = System::Windows::Forms::Cursors::Hand;
			AppSettings::MakeRounded(sb, 12);
		}

		// Status chip ranglari (saytdek: faqat active chip to'liq rangli, qolganlar outline)
		Color chipNavBg   = AppSettings::NavbarColor();
		Color chipInactFg = textMuted;
		Color chipActBg   = accentColor;
		Color chipActFg   = System::Drawing::Color::White;
		Color chipBorderC = AppSettings::BorderColor();
		Color chipHover   = AppSettings::CardHoverColor();
		Color chipActHov  = AppSettings::PrimaryHoverColor();

		// btnStatusAll
		if (btnStatusAll != nullptr) {
			bool a = (activeStatusFilter == L"all");
			btnStatusAll->BackColor = a ? chipActBg : chipNavBg;
			btnStatusAll->ForeColor = a ? chipActFg : chipInactFg;
			btnStatusAll->FlatAppearance->BorderSize = a ? 0 : 1;
			btnStatusAll->FlatAppearance->BorderColor = chipBorderC;
			btnStatusAll->FlatAppearance->MouseOverBackColor = a ? chipActHov : chipHover;
		}
		// btnStatusAvailable
		if (btnStatusAvailable != nullptr) {
			bool a = (activeStatusFilter == L"available");
			btnStatusAvailable->BackColor = a ? chipActBg : chipNavBg;
			btnStatusAvailable->ForeColor = a ? chipActFg : chipInactFg;
			btnStatusAvailable->FlatAppearance->BorderSize = a ? 0 : 1;
			btnStatusAvailable->FlatAppearance->BorderColor = chipBorderC;
			btnStatusAvailable->FlatAppearance->MouseOverBackColor = a ? chipActHov : chipHover;
		}
		// btnStatusReserved
		if (btnStatusReserved != nullptr) {
			bool a = (activeStatusFilter == L"reserved");
			btnStatusReserved->BackColor = a ? chipActBg : chipNavBg;
			btnStatusReserved->ForeColor = a ? chipActFg : chipInactFg;
			btnStatusReserved->FlatAppearance->BorderSize = a ? 0 : 1;
			btnStatusReserved->FlatAppearance->BorderColor = chipBorderC;
			btnStatusReserved->FlatAppearance->MouseOverBackColor = a ? chipActHov : chipHover;
		}
		// btnStatusIssued
		if (btnStatusIssued != nullptr) {
			bool a = (activeStatusFilter == L"issued");
			btnStatusIssued->BackColor = a ? chipActBg : chipNavBg;
			btnStatusIssued->ForeColor = a ? chipActFg : chipInactFg;
			btnStatusIssued->FlatAppearance->BorderSize = a ? 0 : 1;
			btnStatusIssued->FlatAppearance->BorderColor = chipBorderC;
			btnStatusIssued->FlatAppearance->MouseOverBackColor = a ? chipActHov : chipHover;
		}

		lblResultCount->AutoSize = true;
		lblResultCount->Location = System::Drawing::Point(1060, 72);
		lblResultCount->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);

		// Author filter styling
		if (lblAuthorFilter != nullptr) {
			lblAuthorFilter->Text = AppSettings::Translate(L"Muallif:", L"Author:", L"Автор:");
			lblAuthorFilter->ForeColor = textMuted;
			lblAuthorFilter->AutoSize = true;
		}
		if (txtAuthorFilter != nullptr) {
			AppSettings::StyleInput(txtAuthorFilter);
			txtAuthorFilter->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
		}
		// btnFavourites label
		if (btnFavourites != nullptr) {
			btnFavourites->Text = AppSettings::Translate(L"❤ Sevimlilar", L"❤ Favourites", L"❤ Избранные");
		}
		// ISBN filter
		if (lblIsbnFilter != nullptr) {
			lblIsbnFilter->Text = L"ISBN:";
			lblIsbnFilter->ForeColor = textMuted;
			lblIsbnFilter->AutoSize = true;
		}
		if (txtIsbnFilter != nullptr) {
			AppSettings::StyleInput(txtIsbnFilter);
			txtIsbnFilter->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
		}
		// Toast panel
		if (_toastPanel != nullptr) {
			_toastPanel->Visible = false;
			_toastPanel->Size = System::Drawing::Size(310, 50);
			AppSettings::MakeRounded(_toastPanel, 10);
			_toastLabel->Dock = DockStyle::Fill;
			_toastLabel->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.5F);
			_toastLabel->ForeColor = System::Drawing::Color::White;
			_toastLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			_toastPanel->BringToFront();
		}
		// History popup panel
		if (histPanel != nullptr && histList != nullptr) {
			histPanel->BackColor = AppSettings::SurfaceColor();
			histPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			histPanel->Visible = false;
			histList->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
			histList->BackColor = AppSettings::SurfaceColor();
			histList->ForeColor = AppSettings::TextColor();
			histList->BorderStyle = System::Windows::Forms::BorderStyle::None;
			if (histPanel->Controls->Count == 0) { histPanel->Controls->Add(histList); histList->Dock = DockStyle::Fill; }
		}

		// Marquee — navbar ichida quyi qismda (past qatorda)
		lblMarquee->Text = AppSettings::Translate(L"TATU Library • Online band qilish mavjud", L"TATU Library • Online reservation available", L"Библиотека ТАТУ • Доступно онлайн-бронирование");
		lblMarquee->AutoSize = true;
		lblMarquee->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F);
		lblMarquee->ForeColor = textMuted;
		lblMarquee->BackColor = AppSettings::NavbarColor();
        lblMarquee->Location = System::Drawing::Point(-lblMarquee->PreferredWidth, 120);

	    flpResults->Location = System::Drawing::Point(14, 142);
		flpResults->Size = System::Drawing::Size(1200, 450);
		flpResults->BackColor = AppSettings::PageBackColor();
		flpResults->AutoScroll = true;
		flpResults->WrapContents = true;
		flpResults->Padding = System::Windows::Forms::Padding(12);
		flpResults->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);

		this->MinimumSize = System::Drawing::Size(1080, 680);
		if (this->ClientSize.Height < 620) {
			this->ClientSize = System::Drawing::Size(this->ClientSize.Width, 620);
		}

		UpdateHeaderLayout();
		lblMarquee->BringToFront();
		UpdateResponsiveLayout();
		UpdateReaderButtonState();
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

		// Qidiruv tarixini saqlash
		if (txtSearch != nullptr && !String::IsNullOrWhiteSpace(txtSearch->Text)) SaveSearchHistory(txtSearch->Text->Trim());
		if (histPanel != nullptr) histPanel->Visible = false;

		String^ authorFilter = (txtAuthorFilter != nullptr && !String::IsNullOrWhiteSpace(txtAuthorFilter->Text))
			? txtAuthorFilter->Text->ToLower()->Trim() : L"";
		String^ isbnFilter = (txtIsbnFilter != nullptr && !String::IsNullOrWhiteSpace(txtIsbnFilter->Text))
			? txtIsbnFilter->Text->Trim() : L"";
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
			String^ booksUrl = apiUrl + "books/?page_size=100";
			if (!String::IsNullOrWhiteSpace(isbnFilter))
				booksUrl += "&isbn=" + Uri::EscapeDataString(isbnFilter);
			String^ json = client->DownloadString(booksUrl);
			
			// Extract book objects in JSON securely
			System::Collections::Generic::List<String^>^ books = AppSettings::ExtractJsonObjects(json);
			System::Collections::Generic::List<array<Object^>^>^ results = gcnew System::Collections::Generic::List<array<Object^>^>();

			for each(String^ obj in books) {
				String^ title = Regex::Match(obj, "\"title\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ libName = Regex::Match(obj, "\"library_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ secName = Regex::Match(obj, "\"section_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ shelf = Regex::Match(obj, "\"shelf\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ row = Regex::Match(obj, "\"row\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ ebookPath = Regex::Match(obj, "\"ebook_file\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ coverImg = Regex::Match(obj, "\"cover_image\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ bookIdText = Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value;
				String^ libIdText = Regex::Match(obj, "\"library\":(\\d+)")->Groups[1]->Value;
				String^ libLatText = Regex::Match(obj, "\"library_latitude\":(-?[\\d\\.]+)")->Groups[1]->Value;
				String^ libLonText = Regex::Match(obj, "\"library_longitude\":(-?[\\d\\.]+)")->Groups[1]->Value;
				String^ authorName = Regex::Match(obj, "\"author_name\":\"([^\"]+)\"")->Groups[1]->Value;

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
				
				bool matchSearch = String::IsNullOrWhiteSpace(search) || title->ToLower()->Contains(search) || authorName->ToLower()->Contains(search);
				bool matchAuthor = String::IsNullOrWhiteSpace(authorFilter) || authorName->ToLower()->Contains(authorFilter);
				bool matchLib = (libFilter == L"Barchasi" || libFilter == libName);
				bool matchSec = (secFilter == L"Barchasi" || secFilter == secName);

				bool hasEbook = !String::IsNullOrEmpty(ebookPath) && ebookPath != "null";
				if (onlyEbooks && !hasEbook) continue;

				if (matchSearch && matchLib && matchSec && matchAuthor) {
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

					array<Object^>^ resRow = gcnew array<Object^>(16);
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
					resRow[12] = bookIdText;  // book ID
					resRow[13] = libIdText;   // library ID
					resRow[14] = authorName;  // author name
					resRow[15] = coverImg;    // cover URL for favourites

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
				emptyCard->BackColor = AppSettings::SurfaceColor();
				emptyCard->Margin = System::Windows::Forms::Padding(18);
				MakeRounded(emptyCard, 14);

				Label^ emptyTitle = gcnew Label();
				emptyTitle->Text = AppSettings::Translate(L"Hech narsa topilmadi", L"No results found", L"Ничего не найдено");
				emptyTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.0F, System::Drawing::FontStyle::Bold);
				emptyTitle->ForeColor = AppSettings::TextColor();
				emptyTitle->Location = System::Drawing::Point(20, 24);
				emptyTitle->AutoSize = true;

				Label^ emptyHint = gcnew Label();
				emptyHint->Text = AppSettings::Translate(
					L"Filtrlarni yengillashtiring yoki qidiruvni tozalab ko'ring.",
					L"Try relaxing filters or clearing the search.",
					L"Попробуйте смягчить фильтры или очистить поиск."
				);
				emptyHint->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Regular);
				emptyHint->ForeColor = AppSettings::MutedTextColor();
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
				card->BackColor = AppSettings::SurfaceColor();
				card->Margin = System::Windows::Forms::Padding(12);
				MakeRounded(card, 12);
				card->Cursor = Cursors::Hand;

				PictureBox^ pb = gcnew PictureBox();
				pb->Name = L"cover";
				pb->Size = System::Drawing::Size(cardWidth, imageHeight);
				pb->Location = System::Drawing::Point(0, 0);
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->Image = dynamic_cast<Image^>(res[0]);
				if (pb->Image == emptyImage) {
					pb->BackColor = AppSettings::DarkMode
						? System::Drawing::Color::FromArgb(22, 32, 54)
						: System::Drawing::Color::FromArgb(219, 234, 254); // blue-100
					Label^ noImgLbl = gcnew Label();
					noImgLbl->Text = AppSettings::Translate(L"Muqova\nyo'q", L"No\nCover", L"\u041dет\nобложки");
					noImgLbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, System::Drawing::FontStyle::Regular);
					noImgLbl->ForeColor = AppSettings::DarkMode
						? System::Drawing::Color::FromArgb(100, 140, 200)
						: System::Drawing::Color::FromArgb(96, 165, 250); // blue-400
					noImgLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					noImgLbl->Dock = DockStyle::Fill;
					noImgLbl->BackColor = System::Drawing::Color::Transparent;
					pb->Controls->Add(noImgLbl);
				}

				Label^ lblTitle = gcnew Label();
				lblTitle->Name = L"title";
				lblTitle->Text = res[1]->ToString();
				lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, System::Drawing::FontStyle::Bold);
				lblTitle->ForeColor = AppSettings::TextColor();

				Label^ lblDist = gcnew Label();
				lblDist->Name = L"distance";
				lblDist->Text = AppSettings::Translate(L"Yaqinlik: ", L"Distance: ", L"Расстояние: ") + res[6]->ToString() + L" • " + res[2]->ToString();
				lblDist->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
				lblDist->ForeColor = AppSettings::MutedTextColor();
				lblDist->Location = System::Drawing::Point(10, imageHeight + 60);
				lblDist->Size = System::Drawing::Size(cardWidth - 20, 22);
				lblDist->AutoEllipsis = true;

				Label^ lblStat = gcnew Label();
				lblStat->Name = L"status";
				String^ statusText = res[7]->ToString();
				System::Drawing::Color statColor;
				if (statusText == AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано")) {
					statColor = AppSettings::DangerColor();
					lblStat->Text = L"\u25cf " + statusText;
				}
				else if (statusText == AppSettings::Translate(L"Band qilingan", L"Reserved", L"Забронировано")) {
					statColor = AppSettings::WarningColor();
					lblStat->Text = L"\u25cf " + statusText;
				}
				else {
					statColor = AppSettings::SuccessColor();
					lblStat->Text = L"\u25cf " + statusText;
				}
				lblStat->ForeColor = statColor;
				lblStat->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.0F, System::Drawing::FontStyle::Bold);
				lblStat->Location = System::Drawing::Point(10, imageHeight + 86);
				lblStat->AutoSize = true;

				Label^ lblMeta = gcnew Label();
				lblMeta->Name = L"meta";
				lblMeta->Text = AppSettings::Translate(L"Bo'lim: ", L"Section: ", L"Раздел: ") + res[3]->ToString() + L" • " +
					AppSettings::Translate(L"Javon ", L"Shelf ", L"Стеллаж ") + res[4]->ToString() + L" / " +
					AppSettings::Translate(L"qator ", L"row ", L"ряд ") + res[5]->ToString();
				lblMeta->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular);
				lblMeta->ForeColor = AppSettings::MutedTextColor();
				lblMeta->Location = System::Drawing::Point(10, imageHeight + 116);
				lblMeta->Size = System::Drawing::Size(cardWidth - 20, 22);
				lblMeta->AutoEllipsis = true;

				Button^ btnMiniRoute = gcnew Button();
				btnMiniRoute->Name = L"route";
				btnMiniRoute->Text = AppSettings::Translate(L"Xarita", L"Map", L"Xarita");
				btnMiniRoute->Location = System::Drawing::Point(10, imageHeight + 140);
				btnMiniRoute->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
				btnMiniRoute->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btnMiniRoute->FlatAppearance->BorderSize = 1;
				btnMiniRoute->FlatAppearance->BorderColor = AppSettings::BorderColor();
				btnMiniRoute->BackColor = AppSettings::NavbarColor();
				btnMiniRoute->ForeColor = AppSettings::TextColor();
				btnMiniRoute->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 8.8F, System::Drawing::FontStyle::Bold);
				btnMiniRoute->Cursor = Cursors::Hand;
				MakeRounded(btnMiniRoute, 8);

				Button^ btnMiniOpen = gcnew Button();
				btnMiniOpen->Name = L"open";
				btnMiniOpen->Text = AppSettings::Translate(L"Batafsil", L"Details", L"Подробнее");
				btnMiniOpen->Location = System::Drawing::Point(20 + ((cardWidth - 30) / 2), imageHeight + 140);
				btnMiniOpen->Size = System::Drawing::Size((cardWidth - 30) / 2, 30);
				btnMiniOpen->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btnMiniOpen->FlatAppearance->BorderSize = 0;
				btnMiniOpen->BackColor = AppSettings::PrimaryColor();
				btnMiniOpen->ForeColor = System::Drawing::Color::White;
				btnMiniOpen->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 8.8F, System::Drawing::FontStyle::Bold);
				btnMiniOpen->Cursor = Cursors::Hand;
				MakeRounded(btnMiniOpen, 8);

				// Paint event: draws subtle rounded border
				card->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::Card_Paint);

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
				btnMiniRoute->Click += gcnew System::EventHandler(this, &MyForm::btnMap_Click);
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

				// Heart (sevimli) tugma
				{
					String^ bid = res[12] != nullptr ? res[12]->ToString() : L"";
					String^ aname = (res->Length > 14 && res[14] != nullptr) ? res[14]->ToString() : L"";
					String^ curl  = (res->Length > 15 && res[15] != nullptr) ? res[15]->ToString() : L"";
					bool fav = !String::IsNullOrWhiteSpace(bid) && FavouritesForm::IsFav(bid);
					Button^ btnHrt = gcnew Button();
					btnHrt->Name = L"heart";
					btnHrt->Text = fav ? L"❤" : L"♡";
					btnHrt->Size = System::Drawing::Size(28, 28);
					btnHrt->Location = System::Drawing::Point(cardWidth - 34, 6);
					btnHrt->FlatStyle = FlatStyle::Flat;
					btnHrt->FlatAppearance->BorderSize = 0;
					btnHrt->BackColor = System::Drawing::Color::FromArgb(fav ? 210 : 110, 220, 38, 38);
					btnHrt->ForeColor = System::Drawing::Color::White;
					btnHrt->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F);
					btnHrt->Cursor = Cursors::Hand;
					btnHrt->Tag = gcnew array<String^>{bid, res[1]->ToString(), aname, curl, res[7]->ToString(), res[3]->ToString()};
					btnHrt->Click += gcnew EventHandler(this, &MyForm::btnHeart_Click);
					MakeRounded(btnHrt, 14);
					card->Controls->Add(btnHrt);
					btnHrt->BringToFront();
				}

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

	private: System::Void Card_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Panel^ card = dynamic_cast<Panel^>(sender);
		if (card == nullptr) return;
		System::Drawing::Graphics^ g = e->Graphics;
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		// Draw 1px inside Region so border is fully visible (matches MakeRounded radius=12)
		int x = 1, y = 1, r = 11;
		int w = card->Width - 2, h = card->Height - 2;
		System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
		path->AddArc(x, y, r * 2, r * 2, 180, 90);
		path->AddArc(x + w - r * 2, y, r * 2, r * 2, 270, 90);
		path->AddArc(x + w - r * 2, y + h - r * 2, r * 2, r * 2, 0, 90);
		path->AddArc(x, y + h - r * 2, r * 2, r * 2, 90, 90);
		path->CloseFigure();
		System::Drawing::Color borderCol = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(55, 255, 255, 255)
			: System::Drawing::Color::FromArgb(180, 226, 232, 240); // slate-200
		System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(borderCol, 1.0F);
		g->DrawPath(pen, path);
	}

	private: System::Void Card_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		Control^ c = dynamic_cast<Control^>(sender);
		if (c == nullptr) return;
		Panel^ card = dynamic_cast<Panel^>(c);
		if (card == nullptr) card = dynamic_cast<Panel^>(c->Parent);
		if (card == nullptr) return;
		card->BackColor = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(26, 45, 62)
			: System::Drawing::Color::FromArgb(241, 245, 249); // slate-100
		card->Invalidate();
	}

	private: System::Void Card_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		Control^ c = dynamic_cast<Control^>(sender);
		if (c == nullptr) return;
		Panel^ card = dynamic_cast<Panel^>(c);
		if (card == nullptr) card = dynamic_cast<Panel^>(c->Parent);
		if (card == nullptr) return;
		card->BackColor = AppSettings::SurfaceColor();
		card->Invalidate();
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
			loadingText->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.5F, System::Drawing::FontStyle::Regular);
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
		fd->Size = System::Drawing::Size(660, 600);
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
		l1->Text = AppSettings::Translate(L"Kutubxona: ", L"Library: ", L"Библиотека") + res[2]->ToString();
		l1->Location = System::Drawing::Point(230, yp);
		l1->AutoSize = true;
		l1->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l1->ForeColor = mutColor;
		fd->Controls->Add(l1);
		yp += 30;

		Label^ l2 = gcnew Label();
		l2->Text = AppSettings::Translate(L"Bo'lim: ", L"Section: ", L"Раздел") + res[3]->ToString();
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
		btnOk->Location = System::Drawing::Point(500, 510);
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
		btnMap->Location = System::Drawing::Point(360, 510);
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
		btnEbook->Location = System::Drawing::Point(220, 510);
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
		reserveBox->Size = System::Drawing::Size(590, 140);
		reserveBox->ForeColor = txtColor;
		reserveBox->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.5F, System::Drawing::FontStyle::Bold);

		// Info label — tugmalarning tepasida, to'liq kenglikda (overlap yo'q)
		Label^ reserveInfo = gcnew Label();
		reserveInfo->AutoSize = false;
		reserveInfo->Location = System::Drawing::Point(16, 28);
		reserveInfo->Size = System::Drawing::Size(558, 48);
		reserveInfo->ForeColor = mutColor;
		reserveInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
		reserveInfo->Text = AppSettings::Translate(
			L"Band qilishdan oldin login qiling. Har bir kutubxona uchun alohida karta talab qilinishi mumkin.",
			L"Login first. A separate library card may be required for each library.",
			L"Сначала войдите. Для каждой библиотеки может требоваться отдельная карта."
		);
		reserveBox->Controls->Add(reserveInfo);

		// Baholash tugmasi — chap tomonda (info labeldan keyin alohida qatorda)
		Button^ btnRate = gcnew Button();
		btnRate->Text = AppSettings::Translate(L"★ Baholash", L"★ Rate", L"★ Оценить");
		btnRate->Location = System::Drawing::Point(16, 88);
		btnRate->Size = System::Drawing::Size(160, 40);
		btnRate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnRate->FlatAppearance->BorderSize = 0;
		btnRate->BackColor = System::Drawing::Color::FromArgb(243, 156, 18);
		btnRate->ForeColor = System::Drawing::Color::White;
		btnRate->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold);
		btnRate->Cursor = System::Windows::Forms::Cursors::Hand;
		btnRate->Tag = res;
		btnRate->Click += gcnew System::EventHandler(this, &MyForm::btnRateBook_Click);
		MakeRounded(btnRate, 10);
		reserveBox->Controls->Add(btnRate);

		// Band qilish tugmasi — o'ng tomonda
		Button^ btnReserve = gcnew Button();
		btnReserve->Text = AppSettings::Translate(L"Band qilish", L"Reserve", L"Забронировать");
		btnReserve->Location = System::Drawing::Point(414, 88);
		btnReserve->Size = System::Drawing::Size(160, 40);
		btnReserve->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnReserve->FlatAppearance->BorderSize = 0;
		btnReserve->BackColor = System::Drawing::Color::FromArgb(22, 160, 133);
		btnReserve->ForeColor = System::Drawing::Color::White;
		btnReserve->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold);
		btnReserve->Cursor = System::Windows::Forms::Cursors::Hand;
		btnReserve->Tag = res;
		btnReserve->Click += gcnew System::EventHandler(this, &MyForm::btnReserve_Click);
		MakeRounded(btnReserve, 10);

		bool canReserve = (res[7]->ToString() == AppSettings::Translate(L"Mavjud", L"Available", L"Доступно"));
		btnReserve->Enabled = canReserve;
		reserveInfo->Text = canReserve
			? reserveInfo->Text
			: AppSettings::Translate(L"Bu kitob hozircha band qilish uchun mavjud emas.", L"This book is currently unavailable for reservation.", L"Эта книга сейчас недоступна для бронирования.");

		reserveBox->Controls->Add(btnReserve);

		// Navbat tugmasi — kitob mavjud bo'lmasa ko'rsatiladi
		Button^ btnWaitlist = gcnew Button();
		btnWaitlist->Text = AppSettings::Translate(L"📋 Navbatga", L"📋 Waitlist", L"📋 Очередь");
		btnWaitlist->Location = System::Drawing::Point(200, 88);
		btnWaitlist->Size = System::Drawing::Size(188, 40);
		btnWaitlist->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnWaitlist->FlatAppearance->BorderSize = 0;
		btnWaitlist->BackColor = System::Drawing::Color::FromArgb(124, 58, 237);
		btnWaitlist->ForeColor = System::Drawing::Color::White;
		btnWaitlist->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F, System::Drawing::FontStyle::Bold);
		btnWaitlist->Cursor = System::Windows::Forms::Cursors::Hand;
		btnWaitlist->Tag = res;
		btnWaitlist->Visible = !canReserve;
		btnWaitlist->Click += gcnew System::EventHandler(this, &MyForm::btnWaitlist_Click);
		MakeRounded(btnWaitlist, 10);
		reserveBox->Controls->Add(btnWaitlist);

		fd->Controls->Add(reserveBox);

		// O'xshash kitoblar bo'limi
		{
			String^ secNameSim = res[3]->ToString();
			Label^ lblSim = gcnew Label();
			lblSim->Text = AppSettings::Translate(L"✨ O'xshash kitoblar:", L"✨ Similar books:", L"✨ Похожие книги:");
			lblSim->Location = System::Drawing::Point(30, 442);
			lblSim->AutoSize = true;
			lblSim->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			lblSim->ForeColor = AppSettings::TextColor();
			fd->Controls->Add(lblSim);

			FlowLayoutPanel^ flpSim = gcnew FlowLayoutPanel();
			flpSim->Location = System::Drawing::Point(170, 436);
			flpSim->Size = System::Drawing::Size(460, 52);
			flpSim->AutoScroll = false;
			flpSim->WrapContents = false;
			flpSim->BackColor = System::Drawing::Color::Transparent;
			fd->Controls->Add(flpSim);

			try {
				WebClient^ simCl = gcnew WebClient();
				simCl->Encoding = System::Text::Encoding::UTF8;
				String^ simJson = simCl->DownloadString(apiUrl + L"books/?limit=12");
				auto simItems = AppSettings::ExtractJsonObjects(simJson);
				String^ curTitleLow = res[1]->ToString()->ToLower();
				int added = 0;
				for each (String^ obj in simItems) {
					if (added >= 5) break;
					String^ st = Regex::Match(obj, "\"title\":\"([^\"]+)\"")->Groups[1]->Value;
					String^ ss = Regex::Match(obj, "\"section_name\":\"([^\"]+)\"")->Groups[1]->Value;
					if (st->ToLower() == curTitleLow || String::IsNullOrWhiteSpace(st)) continue;
					if (!String::IsNullOrWhiteSpace(secNameSim) && ss != secNameSim) continue;
					Button^ chip = gcnew Button();
					chip->Text = (st->Length > 14) ? st->Substring(0, 13) + L"…" : st;
					chip->Size = System::Drawing::Size(86, 40);
					chip->FlatStyle = FlatStyle::Flat;
					chip->FlatAppearance->BorderSize = 1;
					chip->FlatAppearance->BorderColor = AppSettings::BorderColor();
					chip->BackColor = AppSettings::ElevatedColor();
					chip->ForeColor = AppSettings::TextColor();
					chip->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.0F);
					chip->Margin = System::Windows::Forms::Padding(3);
					chip->Cursor = Cursors::Hand;
					MakeRounded(chip, 8);
					chip->Tag = st; // store title for click handler
					chip->Click += gcnew EventHandler(this, &MyForm::btnSimilarChip_Click);
					flpSim->Controls->Add(chip);
					added++;
				}
				if (added == 0) { lblSim->Visible = false; flpSim->Visible = false; }
			} catch (...) {
				lblSim->Visible = false; flpSim->Visible = false;
			}
		}

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

		// Rounded + flat styling — har holatda bir xil
		btnReader->FlatStyle = System::Windows::Forms::FlatStyle::Flat;

		if (String::IsNullOrWhiteSpace(currentReaderToken)) {
			// Login qilinmagan — subtle neutral fon + ko'rinadigan border (oq sahifada ham ajralib tursin)
			btnReader->Text = AppSettings::Translate(L"Kirish", L"Login", L"Вход");
			btnReader->BackColor = AppSettings::DarkMode
				? System::Drawing::Color::FromArgb(34, 39, 45)
				: System::Drawing::Color::FromArgb(244, 246, 250);
			btnReader->ForeColor = AppSettings::DarkMode
				? System::Drawing::Color::FromArgb(236, 240, 241)
				: System::Drawing::Color::FromArgb(33, 37, 41);
			btnReader->FlatAppearance->BorderSize = 1;
			btnReader->FlatAppearance->BorderColor = AppSettings::DarkMode
				? System::Drawing::Color::FromArgb(55, 65, 81)
				: System::Drawing::Color::FromArgb(209, 213, 219);
			MakeRounded(btnReader, 8);
			return;
		}

		// Login qilingan — to'liq rangli fon, border kerak emas
		btnReader->FlatAppearance->BorderSize = 0;
		btnReader->Text = AppSettings::Translate(L"Kabinet ✓", L"Account ✓", L"Аккаунт ✓");
		btnReader->BackColor = System::Drawing::Color::FromArgb(46, 204, 113);
		btnReader->ForeColor = System::Drawing::Color::White;
		MakeRounded(btnReader, 8);
	}

	private: bool LoginReader(String^ cardId, String^ password) {
		WebClient^ client = gcnew WebClient();
		client->Encoding = System::Text::Encoding::UTF8;
		client->Headers[HttpRequestHeader::ContentType] = "application/json";

		String^ loginJson = String::Format(
			"{{\"card_id\":\"{0}\",\"phone\":\"{0}\",\"password\":\"{1}\"}}",
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

	private: String^ RegisterReader(String^ fullName, String^ phone, String^ password) {
		WebClient^ client = gcnew WebClient();
		client->Encoding = System::Text::Encoding::UTF8;
		client->Headers[HttpRequestHeader::ContentType] = "application/json";

		String^ payload = String::Format(
			"{{\"fullname\":\"{0}\",\"phone\":\"{1}\",\"password\":\"{2}\"}}",
			EscapeJson(fullName),
			EscapeJson(phone),
			EscapeJson(password)
		);

		String^ response = client->UploadString(apiUrl + "readers/register/", "POST", payload);
		String^ generatedCardId = Regex::Match(response, "\"card_id\":\"([^\"]+)\"")->Groups[1]->Value;
		return generatedCardId;
	}

	private: System::Void LogoutReader() {
		currentReaderId = -1;
		currentReaderName = L"";
		currentReaderCardId = L"";
		currentReaderToken = nullptr;
		currentReaderApproved = false;
		UpdateReaderButtonState();
	}

	// Server bilan reader is_approved/is_active statusini real vaqtda
	// sinxronlashtiradigan yengil metod. Login bo'lmagan bo'lsa hech nima
	// qilmasdan false qaytaradi. Token noto'g'ri bo'lsa ham loyihaga zarar
	// keltirmaydi (avtomatik logout qilinmaydi - faqat oldingi qiymat saqlanadi).
	private: bool RefreshReaderStatus() {
		if (String::IsNullOrWhiteSpace(currentReaderToken) || currentReaderId <= 0) return false;
		try {
			WebClient^ cl = gcnew WebClient();
			cl->Encoding = System::Text::Encoding::UTF8;
			cl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			cl->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ resp = cl->DownloadString(apiUrl + "readers/refresh-status/");
			Match^ approvedM = Regex::Match(resp, "\"is_approved\"\\s*:\\s*(true|false)", RegexOptions::IgnoreCase);
			Match^ activeM = Regex::Match(resp, "\"is_active\"\\s*:\\s*(true|false)", RegexOptions::IgnoreCase);
			if (approvedM->Success) {
				bool newApproved = approvedM->Groups[1]->Value->ToLower() == "true";
				bool newActive = activeM->Success ? (activeM->Groups[1]->Value->ToLower() == "true") : true;
				bool changed = (newApproved != currentReaderApproved);
				currentReaderApproved = newApproved;
				if (!newActive) {
					// Server tomondan akkaunt bloklanganida — chiqib yuborish.
					LogoutReader();
					MessageBox::Show(
						AppSettings::Translate(L"Akkauntingiz bloklangan.", L"Your account is blocked.", L"Ваш аккаунт заблокирован"),
						AppSettings::Translate(L"Bloklandi", L"Blocked", L"Заблокирован"),
						MessageBoxButtons::OK,
						MessageBoxIcon::Warning
					);
					return true;
				}
				if (changed) UpdateReaderButtonState();
				return true;
			}
		}
		catch (...) {
			// Tarmoq xatoligida statusni o'zgartirmaymiz - oxirgi qiymat saqlanadi.
		}
		return false;
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
				String^ libraryName = Regex::Match(obj, "\"library_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ updatedAt = Regex::Match(obj, "\"updated_at\":\"([^\"]+)\"")->Groups[1]->Value;
				if (String::IsNullOrWhiteSpace(libraryName)) continue;
				dgvCards->Rows->Add(libraryName, updatedAt);
			}
		}
		catch (...) {}
	}

	private: System::Void btnUploadLibraryCard_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrWhiteSpace(currentReaderToken)) {
			MessageBox::Show(
				AppSettings::Translate(L"Karta yuklash uchun avval tizimga kiring.", L"Login first to upload card.", L"Войдите, чтобы загрузить карту."),
				AppSettings::Translate(L"Kirish kerak", L"Login required", L"Требуется вход"),
				MessageBoxButtons::OK, MessageBoxIcon::Information
			);
			return;
		}
		LibraryCardForm^ lcf = gcnew LibraryCardForm(currentReaderToken);
		AppSettings::ApplyTheme(lcf);
		lcf->ShowDialog();
		return;

		// ── Eski inline kod zaxira ──
		if (currentReaderId <= 0) return;
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
			String^ payload = String::Format("{{\"library\":{0},\"card_image_base64\":\"{1}\"}}",
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

				String^ resvIdText = Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value;
				String^ bookTitle = Regex::Match(obj, "\"book_title\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ reservedAt = Regex::Match(obj, "\"reserved_at\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ note = Regex::Match(obj, "\"note\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ reserveStatus = issuedTitles->Contains(bookTitle->ToLower())
					? AppSettings::Translate(L"Berilgan", L"Issued", L"Выдано")
					: AppSettings::Translate(L"Faol bron", L"Active reservation", L"Активная бронь");

				if (dgvReservations != nullptr) {
					int idx = dgvReservations->Rows->Add(bookTitle, reservedAt, note, reserveStatus, resvIdText);
					(void)idx;
				}
			}
		}
		catch (...) {}
	}

	// Foydalanuvchining tanlangan bronini bekor qilish (faqat o'zining bronini).
	private: System::Void btnCancelReservation_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<Object^>^ tagPair = dynamic_cast<array<Object^>^>(btn->Tag);
		if (tagPair == nullptr || tagPair->Length < 2) return;
		DataGridView^ dgvRes = dynamic_cast<DataGridView^>(tagPair[0]);
		DataGridView^ dgvIs = dynamic_cast<DataGridView^>(tagPair[1]);
		if (dgvRes == nullptr || dgvRes->SelectedRows->Count <= 0) {
			MessageBox::Show(
				AppSettings::Translate(L"Bekor qilish uchun bronni tanlang.", L"Select a reservation to cancel.", L"Выберите бронь для отмены."),
				AppSettings::Translate(L"Ma'lumot", L"Info", L"Информация"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			return;
		}

		DataGridViewRow^ row = dgvRes->SelectedRows[0];
		String^ resvId = row->Cells->Count > 4 && row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : L"";
		if (String::IsNullOrWhiteSpace(resvId)) return;

		System::Windows::Forms::DialogResult dr = MessageBox::Show(
			AppSettings::Translate(L"Tanlangan bronni bekor qilasizmi?", L"Cancel the selected reservation?", L"Отменить выбранную бронь?"),
			AppSettings::Translate(L"Tasdiqlash", L"Confirm", L"Подтверждение"),
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question
		);
		if (dr != System::Windows::Forms::DialogResult::Yes) return;

		try {
			WebClient^ cl = gcnew WebClient();
			cl->Encoding = System::Text::Encoding::UTF8;
			cl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			cl->Headers->Add("X-Reader-Token", currentReaderToken);
			cl->UploadString(apiUrl + "reservations/" + resvId + "/", "DELETE", "");

			MessageBox::Show(
				AppSettings::Translate(L"Bron bekor qilindi.", L"Reservation cancelled.", L"Бронь отменена."),
				AppSettings::Translate(L"Tayyor", L"Done", L"Готово"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			LoadReaderActivityGrid(dgvRes, dgvIs);
			LoadBooksToGrid();
		}
		catch (Exception^ ex) {
			MessageBox::Show(
				AppSettings::Translate(L"Bekor qilishda xatolik: ", L"Cancel failed: ", L"Не удалось отменить: ") + ex->Message,
				AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void ShowReaderDashboard() {
		// Kabinetni ochishdan oldin akkaunt statusini server bilan moslashtiramiz
		// (admin sizni endi tasdiqlagan bo'lishi mumkin yoki bloklagan bo'lishi mumkin).
		RefreshReaderStatus();
		if (String::IsNullOrWhiteSpace(currentReaderToken)) return;

		Form^ dash = gcnew Form();
		dash->Text = AppSettings::Translate(L"Reader Dashboard", L"Reader Dashboard", L"Кабинет читателя");
		dash->Size = System::Drawing::Size(860, 560);
		dash->StartPosition = FormStartPosition::CenterParent;
		dash->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		dash->MinimumSize = System::Drawing::Size(720, 520);

		Color panelBg = AppSettings::SurfaceColor();
		Color textMuted = AppSettings::DarkMode ? System::Drawing::Color::FromArgb(170, 176, 180) : System::Drawing::Color::FromArgb(108, 117, 125);
		Color textColor = AppSettings::TextColor();

		TabControl^ tabs = gcnew TabControl();
		tabs->Dock = DockStyle::Fill;
		tabs->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F);
		tabs->Padding = System::Drawing::Point(14, 6);

		TabPage^ profileTab = gcnew TabPage(AppSettings::Translate(L"👤 Profil", L"👤 Profile", L"👤 Профиль"));
		TabPage^ activityTab = gcnew TabPage(AppSettings::Translate(L"📊 Faollik", L"📊 Activity", L"📊 Активность"));

		Panel^ profileCard = gcnew Panel();
		profileCard->Location = Point(18, 18);
		profileCard->Size = System::Drawing::Size(790, 168);
		profileCard->BackColor = panelBg;
		MakeRounded(profileCard, 14);

		// Avatar — ism harfini ko'rsatuvchi dumaloq
		Panel^ avatar = gcnew Panel();
		avatar->Size = System::Drawing::Size(72, 72);
		avatar->Location = Point(22, 22);
		avatar->BackColor = System::Drawing::Color::FromArgb(99, 102, 241);
		MakeRounded(avatar, 36);

		Label^ lblAvatarText = gcnew Label();
		String^ initial = !String::IsNullOrEmpty(currentReaderName)
			? currentReaderName->Substring(0, 1)->ToUpper()
			: L"?";
		lblAvatarText->Text = initial;
		lblAvatarText->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 24.0F, FontStyle::Bold);
		lblAvatarText->ForeColor = System::Drawing::Color::White;
		lblAvatarText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblAvatarText->Dock = DockStyle::Fill;
		avatar->Controls->Add(lblAvatarText);

		Label^ lblWelcome = gcnew Label();
		lblWelcome->Text = currentReaderName;
		lblWelcome->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16.0F, FontStyle::Bold);
		lblWelcome->ForeColor = textColor;
		lblWelcome->AutoSize = true;
		lblWelcome->Location = Point(110, 24);

		Label^ lblWelcomeSub = gcnew Label();
		lblWelcomeSub->Text = AppSettings::Translate(L"Xush kelibsiz!", L"Welcome back!", L"Добро пожаловать!");
		lblWelcomeSub->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
		lblWelcomeSub->ForeColor = textMuted;
		lblWelcomeSub->AutoSize = true;
		lblWelcomeSub->Location = Point(110, 54);

		Label^ lblCard = gcnew Label();
		lblCard->Text = L"🪪  " + AppSettings::Translate(L"Karta ID", L"Card ID", L"ID карты") + L": " + currentReaderCardId;
		lblCard->ForeColor = textMuted;
		lblCard->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
		lblCard->AutoSize = true;
		lblCard->Location = Point(110, 86);

		// Status pill — yumaloq tabletka shaklida
		Panel^ statusPill = gcnew Panel();
		statusPill->Size = System::Drawing::Size(currentReaderApproved ? 168 : 200, 30);
		statusPill->Location = Point(110, 116);
		statusPill->BackColor = currentReaderApproved
			? System::Drawing::Color::FromArgb(46, 204, 113)
			: System::Drawing::Color::FromArgb(243, 156, 18);
		MakeRounded(statusPill, 15);

		Label^ lblStatus = gcnew Label();
		lblStatus->Text = currentReaderApproved
			? AppSettings::Translate(L"✓ Tasdiqlangan", L"✓ Approved", L"✓ Одобрено")
			: AppSettings::Translate(L"⏳ Tasdiq kutilmoqda", L"⏳ Pending approval", L"⏳ Ожидает одобрения");
		lblStatus->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F, System::Drawing::FontStyle::Bold);
		lblStatus->ForeColor = System::Drawing::Color::White;
		lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblStatus->Dock = DockStyle::Fill;
		statusPill->Controls->Add(lblStatus);

		Button^ btnLogout = gcnew Button();
		btnLogout->Text = AppSettings::Translate(L"Chiqish", L"Logout", L"Выйти");
		btnLogout->Size = System::Drawing::Size(120, 36);
		btnLogout->Location = Point(650, 118);
		btnLogout->FlatStyle = FlatStyle::Flat;
		btnLogout->FlatAppearance->BorderSize = 0;
		btnLogout->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnLogout->ForeColor = System::Drawing::Color::White;
		btnLogout->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold);
		btnLogout->Cursor = System::Windows::Forms::Cursors::Hand;
		btnLogout->Click += gcnew EventHandler(this, &MyForm::btnReaderLogout_Click);
		MakeRounded(btnLogout, 8);

		Button^ btnEditProfile = gcnew Button();
		btnEditProfile->Text = AppSettings::Translate(L"Tahrirlash", L"Edit", L"Изменить");
		btnEditProfile->Size = System::Drawing::Size(120, 36);
		btnEditProfile->Location = Point(520, 118);
		btnEditProfile->FlatStyle = FlatStyle::Flat;
		btnEditProfile->FlatAppearance->BorderSize = 0;
		btnEditProfile->BackColor = AppSettings::PrimaryColor();
		btnEditProfile->ForeColor = System::Drawing::Color::White;
		btnEditProfile->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F, System::Drawing::FontStyle::Bold);
		btnEditProfile->Cursor = System::Windows::Forms::Cursors::Hand;
		btnEditProfile->Click += gcnew EventHandler(this, &MyForm::btnEditProfile_Click);
		MakeRounded(btnEditProfile, 8);

		profileCard->Controls->Add(avatar);
		profileCard->Controls->Add(lblWelcome);
		profileCard->Controls->Add(lblWelcomeSub);
		profileCard->Controls->Add(lblCard);
		profileCard->Controls->Add(statusPill);
		profileCard->Controls->Add(btnEditProfile);
		profileCard->Controls->Add(btnLogout);
		profileTab->Controls->Add(profileCard);

		Label^ lblCards = gcnew Label();
		lblCards->Text = AppSettings::Translate(L"📚 Kutubxona kartalari", L"📚 Library cards", L"📚 Карты библиотек");
		lblCards->AutoSize = true;
		lblCards->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, System::Drawing::FontStyle::Bold);
		lblCards->ForeColor = textColor;
		lblCards->Location = Point(18, 204);

		Button^ btnUploadCard = gcnew Button();
		btnUploadCard->Text = AppSettings::Translate(L"+ Karta yuklash / yangilash", L"+ Upload / update card", L"+ Загрузить / обновить карту");
		btnUploadCard->Size = System::Drawing::Size(240, 34);
		btnUploadCard->Location = Point(568, 198);
		btnUploadCard->FlatStyle = FlatStyle::Flat;
		btnUploadCard->FlatAppearance->BorderSize = 0;
		btnUploadCard->BackColor = System::Drawing::Color::FromArgb(13, 110, 253);
		btnUploadCard->ForeColor = System::Drawing::Color::White;
		btnUploadCard->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F, FontStyle::Bold);
		btnUploadCard->Cursor = System::Windows::Forms::Cursors::Hand;
		btnUploadCard->Click += gcnew EventHandler(this, &MyForm::btnUploadLibraryCard_Click);
		MakeRounded(btnUploadCard, 8);

		DataGridView^ dgvCards = gcnew DataGridView();
		dgvCards->Location = Point(18, 240);
		dgvCards->Size = System::Drawing::Size(790, 240);
		dgvCards->AllowUserToAddRows = false;
		dgvCards->ReadOnly = true;
		dgvCards->RowHeadersVisible = false;
		dgvCards->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvCards->ColumnCount = 2;
		dgvCards->Columns[0]->Name = AppSettings::Translate(L"Kutubxona", L"Library", L"Библиотека");
		dgvCards->Columns[1]->Name = AppSettings::Translate(L"Yangilangan vaqti", L"Updated at", L"Обновлено");
		AppSettings::StyleGrid(dgvCards);

		btnUploadCard->Tag = dgvCards;

		profileTab->Controls->Add(lblCards);
		profileTab->Controls->Add(btnUploadCard);
		profileTab->Controls->Add(dgvCards);

		Label^ lblRes = gcnew Label();
		lblRes->Text = AppSettings::Translate(L"📌 Mening bronlarim", L"📌 My reservations", L"📌 Мои брони");
		lblRes->AutoSize = true;
		lblRes->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, FontStyle::Bold);
		lblRes->ForeColor = textColor;
		lblRes->Location = Point(18, 14);

		DataGridView^ dgvReservations = gcnew DataGridView();
		dgvReservations->Location = Point(18, 42);
		dgvReservations->Size = System::Drawing::Size(790, 146);
		dgvReservations->AllowUserToAddRows = false;
		dgvReservations->ReadOnly = true;
		dgvReservations->RowHeadersVisible = false;
		dgvReservations->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
		dgvReservations->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvReservations->ColumnCount = 5;
		dgvReservations->Columns[0]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
		dgvReservations->Columns[1]->Name = AppSettings::Translate(L"Band qilingan sana", L"Reserved at", L"Дата брони");
		dgvReservations->Columns[2]->Name = AppSettings::Translate(L"Izoh", L"Note", L"Примечание");
		dgvReservations->Columns[3]->Name = AppSettings::Translate(L"Holat", L"Status", L"Статус");
		dgvReservations->Columns[4]->Name = L"_id";
		dgvReservations->Columns[4]->Visible = false;
		AppSettings::StyleGrid(dgvReservations);

		Button^ btnCancelRes = gcnew Button();
		btnCancelRes->Text = AppSettings::Translate(L"✖ Tanlangan bronni bekor qilish", L"✖ Cancel selected reservation", L"✖ Отменить выбранную бронь");
		btnCancelRes->Size = System::Drawing::Size(280, 34);
		btnCancelRes->Location = Point(18, 196);
		btnCancelRes->FlatStyle = FlatStyle::Flat;
		btnCancelRes->FlatAppearance->BorderSize = 0;
		btnCancelRes->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnCancelRes->ForeColor = System::Drawing::Color::White;
		btnCancelRes->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F, FontStyle::Bold);
		btnCancelRes->Cursor = System::Windows::Forms::Cursors::Hand;
		btnCancelRes->Click += gcnew System::EventHandler(this, &MyForm::btnCancelReservation_Click);
		MakeRounded(btnCancelRes, 8);

		Label^ lblIssued = gcnew Label();
		lblIssued->Text = AppSettings::Translate(L"📖 Menda olingan kitoblar", L"📖 My borrowed books", L"📖 Мои выданные книги");
		lblIssued->AutoSize = true;
		lblIssued->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, FontStyle::Bold);
		lblIssued->ForeColor = textColor;
		lblIssued->Location = Point(18, 244);

		DataGridView^ dgvMyIssues = gcnew DataGridView();
		dgvMyIssues->Location = Point(18, 272);
		dgvMyIssues->Size = System::Drawing::Size(790, 174);
		dgvMyIssues->AllowUserToAddRows = false;
		dgvMyIssues->ReadOnly = true;
		dgvMyIssues->RowHeadersVisible = false;
		dgvMyIssues->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		dgvMyIssues->ColumnCount = 3;
		dgvMyIssues->Columns[0]->Name = AppSettings::Translate(L"Kitob", L"Book", L"Книга");
		dgvMyIssues->Columns[1]->Name = AppSettings::Translate(L"Olingan sana", L"Issue date", L"Дата выдачи");
		dgvMyIssues->Columns[2]->Name = AppSettings::Translate(L"Qaytarish muddati", L"Return date", L"Срок возврата");
		AppSettings::StyleGrid(dgvMyIssues);

		// Cancel tugmasiga gridlarning ikkalasini ham bog'laymiz
		array<Object^>^ cancelTag = gcnew array<Object^>(2);
		cancelTag[0] = dgvReservations;
		cancelTag[1] = dgvMyIssues;
		btnCancelRes->Tag = cancelTag;

		activityTab->Controls->Add(lblRes);
		activityTab->Controls->Add(dgvReservations);
		activityTab->Controls->Add(btnCancelRes);
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

	private: System::Void btnEditProfile_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ dlg = gcnew Form();
		dlg->Text = AppSettings::Translate(L"Profilni tahrirlash", L"Edit Profile", L"Редактировать профиль");
		dlg->Size = System::Drawing::Size(400, 350);
		dlg->StartPosition = FormStartPosition::CenterParent;
		dlg->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		dlg->MaximizeBox = false;
		dlg->MinimizeBox = false;

		int top = 20, left = 20, w = 340;

		Label^ lblName = gcnew Label();
		lblName->Text = AppSettings::Translate(L"F.I.Sh", L"Full Name", L"ФИО");
		lblName->Location = Point(left, top);
		lblName->AutoSize = true;
		top += 22;

		TextBox^ txtName = gcnew TextBox();
		txtName->Text = currentReaderName;
		txtName->Location = Point(left, top);
		txtName->Size = System::Drawing::Size(w, 28);
		top += 38;

		Label^ lblPhone = gcnew Label();
		lblPhone->Text = AppSettings::Translate(L"Telefon", L"Phone", L"Телефон");
		lblPhone->Location = Point(left, top);
		lblPhone->AutoSize = true;
		top += 22;

		TextBox^ txtPhone = gcnew TextBox();
		txtPhone->Text = currentReaderPhone;
		txtPhone->Location = Point(left, top);
		txtPhone->Size = System::Drawing::Size(w, 28);
		top += 38;

		Label^ lblPass = gcnew Label();
		lblPass->Text = AppSettings::Translate(L"Yangi parol (ixtiyoriy)", L"New Password (optional)", L"Новый пароль (необязательно)");
		lblPass->Location = Point(left, top);
		lblPass->AutoSize = true;
		top += 22;

		TextBox^ txtPass = gcnew TextBox();
		txtPass->PasswordChar = '*';
		txtPass->Location = Point(left, top);
		txtPass->Size = System::Drawing::Size(w, 28);
		top += 50;

		Button^ btnSave = gcnew Button();
		btnSave->Text = AppSettings::Translate(L"Saqlash", L"Save", L"Сохранить");
		btnSave->Location = Point(left + w - 100, top);
		btnSave->Size = System::Drawing::Size(100, 32);
		btnSave->DialogResult = System::Windows::Forms::DialogResult::OK;

		Button^ btnCancel = gcnew Button();
		btnCancel->Text = AppSettings::Translate(L"Bekor", L"Cancel", L"Отмена");
		btnCancel->Location = Point(left + w - 210, top);
		btnCancel->Size = System::Drawing::Size(100, 32);
		btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

		dlg->Controls->Add(lblName); dlg->Controls->Add(txtName);
		dlg->Controls->Add(lblPhone); dlg->Controls->Add(txtPhone);
		dlg->Controls->Add(lblPass); dlg->Controls->Add(txtPass);
		dlg->Controls->Add(btnSave); dlg->Controls->Add(btnCancel);
		dlg->AcceptButton = btnSave;
		dlg->CancelButton = btnCancel;
		AppSettings::ApplyTheme(dlg);

		if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				WebClient^ cl = gcnew WebClient();
				cl->Encoding = System::Text::Encoding::UTF8;
				cl->Headers[HttpRequestHeader::ContentType] = "application/json";
				cl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
				cl->Headers->Add("X-Reader-Token", currentReaderToken);

				String^ payload = String::Format("{{\"fullname\":\"{0}\",\"phone\":\"{1}\"", 
					EscapeJson(txtName->Text), EscapeJson(txtPhone->Text));
				
				if (!String::IsNullOrWhiteSpace(txtPass->Text)) {
					payload += String::Format(",\"password\":\"{0}\"", EscapeJson(txtPass->Text));
				}
				payload += "}";

				String^ resp = cl->UploadString(apiUrl + "readers/update-me/", "PUT", payload);
				
				// Update locals
				currentReaderName = txtName->Text;
				currentReaderPhone = txtPhone->Text;

				MessageBox::Show(
					AppSettings::Translate(L"Profil saqlandi! O'zgarishlar oynani qayta ochganda to'liq ko'rinadi.", L"Profile saved!", L"Профиль сохранен!"),
					AppSettings::Translate(L"Muvaffaqiyat", L"Success", L"Успешно"),
					MessageBoxButtons::OK, MessageBoxIcon::Information
				);
				
				// Oynani yopib qayta ochamiz (to update UI)
				Form^ dash = btnSave->FindForm();
				if (dash != nullptr) {
					dash->DialogResult = System::Windows::Forms::DialogResult::OK;
				}
			} catch (Exception^ ex) {
				MessageBox::Show(
					AppSettings::Translate(L"Xatolik: ", L"Error: ", L"Ошибка: ") + ex->Message,
					AppSettings::Translate(L"Xatolik", L"Error", L"Ошибка"),
					MessageBoxButtons::OK, MessageBoxIcon::Error
				);
			}
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
		// Foydalanuvchi admin tasdig'idan o'tmasdan ham band qila oladi.
		// Faqat login bo'lishi kerak.
		return true;
	}

	private: System::Void btnRateBook_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<Object^>^ res = dynamic_cast<array<Object^>^>(btn->Tag);
		if (res == nullptr || res->Length < 13) return;
		if (!EnsureReaderCanReserve()) return;

		String^ bookIdText = res[12] != nullptr ? res[12]->ToString() : L"";
		if (String::IsNullOrWhiteSpace(bookIdText)) return;

		Form^ dlg = gcnew Form();
		dlg->Text = AppSettings::Translate(L"Kitobni baholash", L"Rate the book", L"Оценить книгу");
		dlg->Size = System::Drawing::Size(420, 280);
		dlg->StartPosition = FormStartPosition::CenterParent;
		dlg->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		dlg->MaximizeBox = false;
		dlg->MinimizeBox = false;

		Label^ lbl = gcnew Label();
		lbl->Text = AppSettings::Translate(L"Reyting (1-5):", L"Rating (1-5):", L"Рейтинг (1-5):");
		lbl->Location = Point(20, 20);
		lbl->AutoSize = true;

		NumericUpDown^ num = gcnew NumericUpDown();
		num->Location = Point(20, 44);
		num->Size = System::Drawing::Size(80, 26);
		num->Minimum = 1; num->Maximum = 5; num->Value = 5;

		Label^ lbl2 = gcnew Label();
		lbl2->Text = AppSettings::Translate(L"Sharh (ixtiyoriy):", L"Review (optional):", L"Отзыв (необязательно):");
		lbl2->Location = Point(20, 80);
		lbl2->AutoSize = true;

		TextBox^ txtReview = gcnew TextBox();
		txtReview->Location = Point(20, 104);
		txtReview->Size = System::Drawing::Size(360, 70);
		txtReview->Multiline = true;

		// Yulduzli reyting UI
		Panel^ starPanel = gcnew Panel();
		starPanel->Location = Point(20, 44);
		starPanel->Size = System::Drawing::Size(200, 40);
		starPanel->BackColor = System::Drawing::Color::Transparent;
		starPanel->Tag = 5; // default selected rating

		for (int si = 0; si < 5; si++) {
			Button^ star = gcnew Button();
			star->Size = System::Drawing::Size(34, 34);
			star->Location = System::Drawing::Point(si * 38, 3);
			star->FlatStyle = FlatStyle::Flat;
			star->FlatAppearance->BorderSize = 0;
			star->BackColor = System::Drawing::Color::Transparent;
			star->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F);
			star->Text = L"★";
			star->ForeColor = System::Drawing::Color::FromArgb(245, 158, 11); // default all gold
			star->Cursor = System::Windows::Forms::Cursors::Hand;
			array<Object^>^ starTag = gcnew array<Object^>(2);
			starTag[0] = (Object^)(si + 1);
			starTag[1] = starPanel;
			star->Tag = starTag;
			star->Click += gcnew System::EventHandler(this, &MyForm::starButton_Click);
			starPanel->Controls->Add(star);
		}

		Button^ ok = gcnew Button();
		ok->Text = AppSettings::Translate(L"Saqlash", L"Save", L"Сохранить");
		ok->Location = Point(280, 188);
		ok->Size = System::Drawing::Size(100, 32);
		ok->BackColor = AppSettings::PrimaryColor();
		ok->ForeColor = System::Drawing::Color::White;
		ok->FlatStyle = FlatStyle::Flat;
		ok->FlatAppearance->BorderSize = 0;
		ok->DialogResult = System::Windows::Forms::DialogResult::OK;

		Button^ cancel = gcnew Button();
		cancel->Text = AppSettings::Translate(L"Bekor", L"Cancel", L"Отмена");
		cancel->Location = Point(170, 188);
		cancel->Size = System::Drawing::Size(100, 32);
		cancel->FlatStyle = FlatStyle::Flat;
		cancel->FlatAppearance->BorderSize = 1;
		cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

		dlg->Controls->Add(lbl); dlg->Controls->Add(starPanel);
		dlg->Controls->Add(lbl2); dlg->Controls->Add(txtReview);
		dlg->Controls->Add(ok); dlg->Controls->Add(cancel);
		dlg->AcceptButton = ok; dlg->CancelButton = cancel;
		dlg->Tag = starPanel;
		AppSettings::ApplyTheme(dlg);

		if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		int finalRating = 5;
		{
			Panel^ sp = dynamic_cast<Panel^>(dlg->Tag);
			if (sp != nullptr && sp->Tag != nullptr) {
				try { finalRating = (int)sp->Tag; } catch (...) { finalRating = 5; }
			}
		}

		try {
			WebClient^ cl = gcnew WebClient();
			cl->Encoding = System::Text::Encoding::UTF8;
			cl->Headers[HttpRequestHeader::ContentType] = "application/json";
			cl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			cl->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ payload = String::Format("{{\"rating\":{0},\"review\":\"{1}\"}}",
				finalRating, EscapeJson(txtReview->Text));
			cl->UploadString(apiUrl + "books/" + bookIdText + "/rate/", "POST", payload);
			ShowToast(AppSettings::Translate(L"★ Reyting saqlandi!", L"★ Rating saved!", L"★ Оценка сохранена!"), L"success");
		}
		catch (Exception^ ex) {
			ShowToast(AppSettings::Translate(L"Baholashda xato: ", L"Rating error: ", L"Ошибка: ") + ex->Message, L"error");
			}
	}

	// ─────────────────────────────────────────────────────────────────────────
	// Toast bildirisnoma
	// ─────────────────────────────────────────────────────────────────────────
	public: System::Void ShowToast(String^ msg, String^ type) {
		if (_toastPanel == nullptr || _toastLabel == nullptr) return;
		System::Drawing::Color bg, fg;
		if (type == L"success") { bg = System::Drawing::Color::FromArgb(22, 163, 74);  fg = System::Drawing::Color::White; }
		else if (type == L"error") { bg = System::Drawing::Color::FromArgb(220, 38, 38);  fg = System::Drawing::Color::White; }
		else if (type == L"warning") { bg = System::Drawing::Color::FromArgb(217, 119, 6);  fg = System::Drawing::Color::White; }
		else                        { bg = System::Drawing::Color::FromArgb(37, 99, 235);   fg = System::Drawing::Color::White; }
		_toastLabel->Text = msg;
		_toastPanel->BackColor = bg;
		_toastLabel->ForeColor = fg;
		int tw = Math::Min(340, this->ClientSize.Width - 40);
		_toastPanel->Size = System::Drawing::Size(tw, 50);
		_toastPanel->Location = System::Drawing::Point(
			this->ClientSize.Width - tw - 20,
			this->ClientSize.Height - 70
		);
		AppSettings::MakeRounded(_toastPanel, 10);
		_toastPanel->BringToFront();
		_toastPanel->Visible = true;
		if (_toastTimer != nullptr) { _toastTimer->Stop(); _toastTimer->Start(); }
	}

	private: System::Void toastTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (_toastTimer != nullptr) _toastTimer->Stop();
		if (_toastPanel != nullptr) _toastPanel->Visible = false;
	}

	// ─────────────────────────────────────────────────────────────────────────
	// Klaviatura yorliqlari: Ctrl+F qidiruv, F5 yangilash
	// ─────────────────────────────────────────────────────────────────────────
	protected: virtual bool ProcessCmdKey(System::Windows::Forms::Message% msg, System::Windows::Forms::Keys keyData) override {
		if (keyData == (System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F)) {
			if (txtSearch != nullptr) { txtSearch->Focus(); txtSearch->SelectAll(); }
			return true;
		}
		if (keyData == System::Windows::Forms::Keys::F5) {
			LoadBooksToGrid();
			return true;
		}
		if (keyData == (System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R)) {
			LoadBooksToGrid();
			return true;
		}
		return Form::ProcessCmdKey(msg, keyData);
	}

	// ─────────────────────────────────────────────────────────────────────────
	// Navbatga yozilish handler
	// ─────────────────────────────────────────────────────────────────────────
	private: System::Void btnWaitlist_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<Object^>^ res = dynamic_cast<array<Object^>^>(btn->Tag);
		if (res == nullptr || res->Length < 13) return;
		if (!EnsureReaderCanReserve()) return;

		String^ bookId = (res[12] != nullptr) ? res[12]->ToString() : L"";
		if (String::IsNullOrWhiteSpace(bookId)) return;

		try {
			WebClient^ cl = gcnew WebClient();
			cl->Encoding = System::Text::Encoding::UTF8;
			cl->Headers[HttpRequestHeader::ContentType] = "application/json";
			cl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
			cl->Headers->Add("X-Reader-Token", currentReaderToken);
			String^ payload = String::Format("{{\"book\":{0}}}", bookId);
			cl->UploadString(apiUrl + "waitlist/", "POST", payload);
			ShowToast(AppSettings::Translate(L"✓ Navbatga yozildingiz!", L"✓ Added to waitlist!", L"✓ Вы добавлены в очередь!"), L"success");
		}
		catch (Exception^ ex) {
			ShowToast(AppSettings::Translate(L"Navbatga yozilishda xato: ", L"Waitlist error: ", L"Ошибка: ") + ex->Message, L"error");
		}
	}

	// ─────────────────────────────────────────────────────────────────────────
	// Yulduz tugmasi bosilganda rang yangilanadi
	// ─────────────────────────────────────────────────────────────────────────
	private: System::Void starButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<Object^>^ tag = dynamic_cast<array<Object^>^>(btn->Tag);
		if (tag == nullptr || tag->Length < 2) return;
		int rating = (int)tag[0];
		Panel^ sp = dynamic_cast<Panel^>(tag[1]);
		if (sp == nullptr) return;
		sp->Tag = rating;
		for each (Control^ c in sp->Controls) {
			Button^ s = dynamic_cast<Button^>(c);
			if (s == nullptr) continue;
			array<Object^>^ st = dynamic_cast<array<Object^>^>(s->Tag);
			if (st == nullptr) continue;
			int sv = (int)st[0];
			s->ForeColor = (sv <= rating)
				? System::Drawing::Color::FromArgb(245, 158, 11)
				: System::Drawing::Color::FromArgb(200, 200, 200);
		}
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

		// library ID ni res[13] dan olish (mavjud bo'lsa)
		String^ libraryIdText = (res->Length > 13 && res[13] != nullptr) ? res[13]->ToString() : L"";

		try {
			int bookId = Int32::Parse(bookIdText);
			String^ libraryName = res[2] != nullptr ? res[2]->ToString() : L"";

			String^ libraryCardB64 = L"";
			bool cardApproved = false;

			// Avval serverdan bu kutubxona uchun karta holatini tekshiramiz
			if (!String::IsNullOrWhiteSpace(libraryIdText) && !String::IsNullOrWhiteSpace(currentReaderToken)) {
				try {
					WebClient^ checkCl = gcnew WebClient();
					checkCl->Encoding = System::Text::Encoding::UTF8;
					checkCl->Headers->Add("X-Reader-Token", currentReaderToken);
					checkCl->Headers->Add("Authorization", "Bearer " + currentReaderToken);
					String^ cardStatusJson = checkCl->DownloadString(
						apiUrl + "readers/check-library-card/?library=" + libraryIdText
					);
					// has_card va is_approved ni JSON dan olish
					bool hasCard = cardStatusJson->Contains("\"has_card\": true") || cardStatusJson->Contains("\"has_card\":true");
					cardApproved = cardStatusJson->Contains("\"is_approved\": true") || cardStatusJson->Contains("\"is_approved\":true");

					if (hasCard && !cardApproved) {
						// Karta bor lekin tasdiqlanmagan
						System::Windows::Forms::DialogResult pendingChoice = MessageBox::Show(
							AppSettings::Translate(
								L"Ushbu kutubxona uchun kartangiz admin tasdig'ini kutmoqda.\nYangi karta rasmi yuklaysizmi?",
								L"Your card for this library is pending admin approval.\nUpload a new card image?",
								L"Ваша карта для этой библиотеки ожидает подтверждения.\nЗагрузить новое изображение?"
							) + L"\n\n" + AppSettings::Translate(L"Kutubxona", L"Library", L"Библиотека") + ": " + libraryName,
							AppSettings::Translate(L"Kutubxona kartasi", L"Library card", L"Карта библиотеки"),
							MessageBoxButtons::YesNo,
							MessageBoxIcon::Warning
						);
						if (pendingChoice == System::Windows::Forms::DialogResult::No) return;
						// Yangi rasm yuklashga o'tamiz
					}
				} catch (...) {
					// Tekshirishda xatolik bo'lsa davom etamiz
				}
			}

			if (!cardApproved) {
				// Karta yo'q yoki tasdiqlanmagan — rasm so'rash
				System::Windows::Forms::DialogResult uploadChoice = MessageBox::Show(
					AppSettings::Translate(
						L"Ushbu kutubxona uchun kutubxona kartangizni yuklang (ruxsatnoma rasmi).",
						L"Please upload your library card image for this library.",
						L"Загрузите изображение вашей карты для этой библиотеки."
					) + L"\n\n" + AppSettings::Translate(L"Kutubxona", L"Library", L"Библиотека") + ": " + libraryName,
					AppSettings::Translate(L"Kutubxona kartasi kerak", L"Library card required", L"Требуется карта библиотеки"),
					MessageBoxButtons::OKCancel,
					MessageBoxIcon::Information
				);

				if (uploadChoice == System::Windows::Forms::DialogResult::Cancel) return;

				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
				if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
				if (!File::Exists(ofd->FileName)) return;

				array<Byte>^ cardBytes = File::ReadAllBytes(ofd->FileName);
				libraryCardB64 = Convert::ToBase64String(cardBytes);
			}
			// cardApproved == true bo'lsa libraryCardB64 bo'sh qoladi — server uni talab qilmaydi

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
				// Admin reader holatini o'zgartirgan bo'lishi mumkin — bosh sahifaga uyg'un.
				RefreshReaderStatus();
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

	private: System::Void btnLibraries_Click(System::Object^ sender, System::EventArgs^ e) {
		LibrariesForm^ lf = gcnew LibrariesForm();
		lf->ShowDialog();
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

		// Yangi LoginForm ishlatiladi
		LoginForm^ lf = gcnew LoginForm();
		AppSettings::ApplyTheme(lf);
		if (lf->ShowDialog() == System::Windows::Forms::DialogResult::OK && lf->IsLoggedIn) {
			currentReaderToken    = lf->ReaderToken;
			currentReaderName     = lf->ReaderName;
			currentReaderCardId   = lf->ReaderCardId;
			currentReaderApproved = lf->ReaderApproved;
			currentReaderId       = -1; // token-based, ID keyinroq kerak bo'lmaydi
			UpdateReaderButtonState();
			LoadBooksToGrid();
		}
		return;

		// ── Quyidagi eski inline kod zaxira sifatida saqlanadi ──
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
		lblCardL->Text = AppSettings::Translate(L"Telefon yoki Karta ID", L"Phone or Card ID", L"Телефон или ID карты");
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
					MessageBox::Show(AppSettings::Translate(L"Telefon yoki Karta ID va parolni kiriting.", L"Enter phone or card ID and password.", L"Введите телефон или ID карты и пароль."));
					return;
				}
				LoginReader(txtCardL->Text->Trim(), txtPasswordL->Text);
				MessageBox::Show(
					AppSettings::Translate(L"Kirish muvaffaqiyatli.", L"Login successful.", L"Вход выполнен."),
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

				String^ newCardId = RegisterReader(txtName->Text->Trim(), txtPhone->Text->Trim(), txtPasswordR->Text);
				String^ msg = AppSettings::Translate(
					L"Muvaffaqiyatli ro'yxatdan o'tdingiz. Tizimga kirish uchun Karta ID: " + newCardId + L". Buni saqlab qoling!",
					L"Registration successful. Your Login Card ID is: " + newCardId + L". Please save it!",
					L"Регистрация прошла успешно. Ваш ID карты для входа: " + newCardId + L". Пожалуйста, сохраните его!"
				);
				MessageBox::Show(
					msg,
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

	// Top kitoblar dialogini ochadi: 3 tab — eng ommabop, eng yuqori reytingdagi, eng ko'p o'qilgan.
	// Har bir tab kartalar ko'rinishida (FlowLayoutPanel) — bosh sahifaga uyg'un.
	private: System::Void btnTopBooks_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ dlg = gcnew Form();
		dlg->Text = AppSettings::Translate(L"Eng yaxshi kitoblar", L"Top books", L"Лучшие книги");
		dlg->Size = System::Drawing::Size(900, 620);
		dlg->StartPosition = FormStartPosition::CenterParent;
		dlg->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		dlg->MinimumSize = System::Drawing::Size(720, 520);

		TabControl^ tabs = gcnew TabControl();
		tabs->Dock = DockStyle::Fill;
		tabs->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0F);
		tabs->Padding = System::Drawing::Point(14, 6);

		TabPage^ tabPopular = gcnew TabPage(AppSettings::Translate(L"🔥 Eng ommabop", L"🔥 Most popular", L"🔥 Популярные"));
		TabPage^ tabRated   = gcnew TabPage(AppSettings::Translate(L"★ Yuqori reyting", L"★ Top rated", L"★ Высокий рейтинг"));
		TabPage^ tabRead    = gcnew TabPage(AppSettings::Translate(L"📚 Eng ko'p o'qilgan", L"📚 Most read", L"📚 Чаще всего читают"));

		FlowLayoutPanel^ flpPop   = BuildTopBooksFlow();
		FlowLayoutPanel^ flpRated = BuildTopBooksFlow();
		FlowLayoutPanel^ flpRead  = BuildTopBooksFlow();

		tabPopular->Controls->Add(flpPop);
		tabRated->Controls->Add(flpRated);
		tabRead->Controls->Add(flpRead);

		tabs->TabPages->Add(tabPopular);
		tabs->TabPages->Add(tabRated);
		tabs->TabPages->Add(tabRead);
		dlg->Controls->Add(tabs);

		LoadTopBooksFlow(flpPop,   L"popular");
		LoadTopBooksFlow(flpRated, L"top-rated");
		LoadTopBooksFlow(flpRead,  L"most-read");

		AppSettings::ApplyTheme(dlg);
		dlg->ShowDialog();
	}

	private: FlowLayoutPanel^ BuildTopBooksFlow() {
		FlowLayoutPanel^ flp = gcnew FlowLayoutPanel();
		flp->Dock = DockStyle::Fill;
		flp->AutoScroll = true;
		flp->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
		flp->WrapContents = false;
		flp->Padding = System::Windows::Forms::Padding(14, 12, 14, 12);
		return flp;
	}

	// Top kitoblar API'sidan ma'lumotni yuklab, FlowLayoutPanel ichiga karta-qatorlar qo'shadi.
	private: System::Void LoadTopBooksFlow(FlowLayoutPanel^ flp, String^ endpoint) {
		if (flp == nullptr) return;
		flp->Controls->Clear();

		// Yuklanish indikatori
		Label^ lblLoading = gcnew Label();
		lblLoading->Text = AppSettings::Translate(L"Yuklanmoqda…", L"Loading…", L"Загрузка…");
		lblLoading->AutoSize = true;
		lblLoading->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Italic);
		lblLoading->ForeColor = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(170, 176, 180)
			: System::Drawing::Color::FromArgb(108, 117, 125);
		flp->Controls->Add(lblLoading);
		flp->Refresh();

		String^ json = L"";
		try {
			WebClient^ cl = gcnew WebClient();
			cl->Encoding = System::Text::Encoding::UTF8;
			json = cl->DownloadString(apiUrl + "books/" + endpoint + "/?limit=20");
		}
		catch (Exception^ ex) {
			flp->Controls->Clear();
			Label^ lblErr = gcnew Label();
			lblErr->Text = AppSettings::Translate(L"Yuklashda xatolik: ", L"Failed to load: ", L"Ошибка загрузки: ") + ex->Message;
			lblErr->AutoSize = true;
			lblErr->ForeColor = System::Drawing::Color::FromArgb(220, 53, 69);
			flp->Controls->Add(lblErr);
			return;
		}

		flp->Controls->Clear();
		System::Collections::Generic::List<String^>^ items = AppSettings::ExtractJsonObjects(json);

		if (items->Count == 0) {
			Label^ lblEmpty = gcnew Label();
			lblEmpty->Text = AppSettings::Translate(
				L"Bu bo'limda hali kitoblar yo'q.",
				L"No books in this section yet.",
				L"В этом разделе пока нет книг."
			);
			lblEmpty->AutoSize = true;
			lblEmpty->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, FontStyle::Italic);
			lblEmpty->ForeColor = AppSettings::DarkMode
				? System::Drawing::Color::FromArgb(170, 176, 180)
				: System::Drawing::Color::FromArgb(108, 117, 125);
			flp->Controls->Add(lblEmpty);
			return;
		}

		int rank = 1;
		for each (String^ obj in items) {
			String^ title = Regex::Match(obj, "\"title\":\"([^\"]*)\"")->Groups[1]->Value;
			String^ author = Regex::Match(obj, "\"author_name\":\"([^\"]*)\"")->Groups[1]->Value;
			String^ libName = Regex::Match(obj, "\"library_name\":\"([^\"]*)\"")->Groups[1]->Value;
			String^ avg = Regex::Match(obj, "\"average_rating\":([\\d\\.]+)")->Groups[1]->Value;
			String^ cnt = Regex::Match(obj, "\"ratings_count\":(\\d+)")->Groups[1]->Value;
			String^ views = Regex::Match(obj, "\"view_count\":(\\d+)")->Groups[1]->Value;
			String^ issues = Regex::Match(obj, "\"issue_count\":(\\d+)")->Groups[1]->Value;
			if (String::IsNullOrEmpty(avg)) avg = L"0";
			if (String::IsNullOrEmpty(cnt)) cnt = L"0";
			if (String::IsNullOrEmpty(views)) views = L"0";
			if (String::IsNullOrEmpty(issues)) issues = L"0";

			Panel^ card = BuildTopBookCard(rank, title, author, libName, avg, cnt, views, issues);
			card->Width = flp->ClientSize.Width - 36;
			card->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			flp->Controls->Add(card);
			rank++;
		}
	}

	// Bitta top-book kartasini quradi (rank badge + matn bloklari).
	private: Panel^ BuildTopBookCard(int rank, String^ title, String^ author, String^ libName,
	                                 String^ avg, String^ cnt, String^ views, String^ issues) {
		Color cardBg = AppSettings::SurfaceColor();
		Color textColor = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(236, 240, 241)
			: System::Drawing::Color::FromArgb(33, 37, 41);
		Color mutedColor = AppSettings::DarkMode
			? System::Drawing::Color::FromArgb(170, 176, 180)
			: System::Drawing::Color::FromArgb(108, 117, 125);

		Panel^ card = gcnew Panel();
		card->Size = System::Drawing::Size(700, 92);
		card->BackColor = cardBg;
		card->Margin = System::Windows::Forms::Padding(0, 0, 0, 10);
		card->Padding = System::Windows::Forms::Padding(0);
		MakeRounded(card, 12);

		// Rank badge — top 3 uchun oltin/kumush/bronza, qolgani uchun ko'k
		Color badgeBg = System::Drawing::Color::FromArgb(99, 102, 241);
		if (rank == 1) badgeBg = System::Drawing::Color::FromArgb(241, 196, 15);
		else if (rank == 2) badgeBg = System::Drawing::Color::FromArgb(149, 165, 166);
		else if (rank == 3) badgeBg = System::Drawing::Color::FromArgb(205, 127, 50);

		Panel^ badge = gcnew Panel();
		badge->Size = System::Drawing::Size(58, 58);
		badge->Location = Point(16, 16);
		badge->BackColor = badgeBg;
		MakeRounded(badge, 29);

		Label^ lblRank = gcnew Label();
		lblRank->Text = L"#" + rank.ToString();
		lblRank->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.0F, FontStyle::Bold);
		lblRank->ForeColor = System::Drawing::Color::White;
		lblRank->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblRank->Dock = DockStyle::Fill;
		badge->Controls->Add(lblRank);

		// Sarlavha
		Label^ lblTitle = gcnew Label();
		lblTitle->Text = title;
		lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.5F, FontStyle::Bold);
		lblTitle->ForeColor = textColor;
		lblTitle->Location = Point(94, 14);
		lblTitle->AutoSize = false;
		lblTitle->Size = System::Drawing::Size(420, 22);

		// Muallif + kutubxona
		Label^ lblAuthor = gcnew Label();
		String^ subline = author;
		if (!String::IsNullOrEmpty(libName)) {
			subline = String::IsNullOrEmpty(author) ? libName : (author + L"  •  " + libName);
		}
		lblAuthor->Text = subline;
		lblAuthor->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
		lblAuthor->ForeColor = mutedColor;
		lblAuthor->Location = Point(94, 38);
		lblAuthor->AutoSize = false;
		lblAuthor->Size = System::Drawing::Size(420, 18);

		// Reyting yulduzlar
		Label^ lblStars = gcnew Label();
		double avgD = 0; Double::TryParse(avg, System::Globalization::NumberStyles::Float,
			System::Globalization::CultureInfo::InvariantCulture, avgD);
		String^ stars = L"";
		int full = (int)System::Math::Round(avgD);
		for (int i = 0; i < 5; i++) stars += (i < full ? L"★" : L"☆");
		lblStars->Text = stars + L"  " + avg + L"  (" + cnt + L")";
		lblStars->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
		lblStars->ForeColor = System::Drawing::Color::FromArgb(243, 156, 18);
		lblStars->Location = Point(94, 60);
		lblStars->AutoSize = false;
		lblStars->Size = System::Drawing::Size(220, 18);

		// Statistika chiplari
		Label^ lblStats = gcnew Label();
		lblStats->Text = AppSettings::Translate(L"👁 ", L"👁 ", L"👁 ") + views
			+ L"   " + AppSettings::Translate(L"📖 ", L"📖 ", L"📖 ") + issues;
		lblStats->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
		lblStats->ForeColor = mutedColor;
		lblStats->Location = Point(330, 60);
		lblStats->AutoSize = false;
		lblStats->Size = System::Drawing::Size(180, 18);

		card->Controls->Add(badge);
		card->Controls->Add(lblTitle);
		card->Controls->Add(lblAuthor);
		card->Controls->Add(lblStars);
		card->Controls->Add(lblStats);
		return card;
	}

	private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		if (histPanel != nullptr) histPanel->Visible = false;
		LoadBooksToGrid();
	}

	private: System::Void txtSearch_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e == nullptr) return;
		if (e->KeyCode == Keys::Enter) {
			e->SuppressKeyPress = true;
			if (searchDebounceTimer != nullptr) searchDebounceTimer->Stop();
			if (histPanel != nullptr) histPanel->Visible = false;
			LoadBooksToGrid();
		}
		if (e->KeyCode == Keys::Escape && histPanel != nullptr) histPanel->Visible = false;
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
		String^ origin = userLat.ToString(System::Globalization::CultureInfo::InvariantCulture) + L"," + userLon.ToString(System::Globalization::CultureInfo::InvariantCulture);
		String^ destination = lat + L"," + lon;
		String^ url = L"https://www.google.com/maps/dir/?api=1&origin=" + origin + L"&destination=" + destination + L"&travelmode=walking";
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
				AppSettings::Translate(L"Ma'lumot", L"Error", L"Ошибка"),
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
			return;
		}

		if (ebookPath->StartsWith(L"http://") || ebookPath->StartsWith(L"https://")) {
			Process::Start(ebookPath);
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
		if (txtAuthorFilter != nullptr) txtAuthorFilter->Text = L"";
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

	// ── Sevimlilar ──
	private: System::Void btnFavourites_Click(System::Object^ sender, System::EventArgs^ e) {
		FavouritesForm^ ff = gcnew FavouritesForm(serverUrl);
		AppSettings::ApplyTheme(ff);
		ff->ShowDialog();
	}

	private: System::Void btnHeart_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		array<String^>^ parts = dynamic_cast<array<String^>^>(btn->Tag);
		if (parts == nullptr || parts->Length < 6) return;
		FavouritesForm::ToggleFav(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]);
		bool nowFav = FavouritesForm::IsFav(parts[0]);
		btn->Text = nowFav ? L"❤" : L"♡";
		btn->BackColor = System::Drawing::Color::FromArgb(nowFav ? 210 : 110, 220, 38, 38);
	}

	// ── Qidiruv tarixi ──
	private: System::Void SaveSearchHistory(String^ query) {
		if (String::IsNullOrWhiteSpace(query)) return;
		try {
			String^ dir = System::IO::Path::Combine(
				Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData), L"TATULibrary");
			if (!System::IO::Directory::Exists(dir)) System::IO::Directory::CreateDirectory(dir);
			String^ path = System::IO::Path::Combine(dir, L"search_history.txt");
			auto lines = gcnew System::Collections::Generic::List<String^>();
			if (System::IO::File::Exists(path)) {
				for each (String^ l in System::IO::File::ReadAllLines(path, System::Text::Encoding::UTF8))
					if (!String::IsNullOrWhiteSpace(l) && l->Trim() != query->Trim()) lines->Add(l->Trim());
			}
			lines->Insert(0, query->Trim());
			while (lines->Count > 10) lines->RemoveAt(lines->Count - 1);
			System::IO::File::WriteAllLines(path, lines->ToArray(), System::Text::Encoding::UTF8);
		} catch (...) {}
	}

	private: System::Collections::Generic::List<String^>^ LoadSearchHistory() {
		auto result = gcnew System::Collections::Generic::List<String^>();
		try {
			String^ path = System::IO::Path::Combine(
				Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData),
				L"TATULibrary", L"search_history.txt");
			if (!System::IO::File::Exists(path)) return result;
			for each (String^ l in System::IO::File::ReadAllLines(path, System::Text::Encoding::UTF8))
				if (!String::IsNullOrWhiteSpace(l)) result->Add(l->Trim());
		} catch (...) {}
		return result;
	}

	private: System::Void txtSearch_Enter_History(System::Object^ sender, System::EventArgs^ e) {
		if (histPanel == nullptr || histList == nullptr) return;
		auto hist = LoadSearchHistory();
		if (hist->Count == 0) { histPanel->Visible = false; return; }
		histList->Items->Clear();
		for each (String^ h in hist) histList->Items->Add(h);
		int panelH = Math::Min(hist->Count, 6) * 22 + 8;
		histPanel->Location = System::Drawing::Point(txtSearch->Left, txtSearch->Bottom + 2);
		histPanel->Size = System::Drawing::Size(Math::Max(txtSearch->Width, 240), panelH);
		histPanel->Visible = true;
		histPanel->BringToFront();
	}

	private: System::Void histList_Click(System::Object^ sender, System::EventArgs^ e) {
		if (histList == nullptr || histList->SelectedItem == nullptr) return;
		txtSearch->Text = histList->SelectedItem->ToString();
		histPanel->Visible = false;
		LoadBooksToGrid();
	}

	private: System::Void btnSimilarChip_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = dynamic_cast<Button^>(sender);
		if (btn == nullptr || btn->Tag == nullptr) return;
		String^ simTitle = btn->Tag->ToString();
		if (String::IsNullOrWhiteSpace(simTitle)) return;
		Form^ parentForm = btn->FindForm();
		if (parentForm != nullptr) parentForm->Close();
		txtSearch->Text = simTitle;
		LoadBooksToGrid();
	}

	};
}
