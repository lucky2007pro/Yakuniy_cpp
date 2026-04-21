#pragma once
#include "AdminForm.h"
#include "AboutForm.h"
#include "StatisticsForm.h"
#include "ReaderForm.h"
#include "SettingsForm.h"
#include "HistoryForm.h"

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

			this->cmbFilterLibrary = (gcnew System::Windows::Forms::ComboBox());
			this->cmbFilterSection = (gcnew System::Windows::Forms::ComboBox());
            this->cmbRadius = (gcnew System::Windows::Forms::ComboBox());
            this->chkEbookOnly = (gcnew System::Windows::Forms::CheckBox());
			this->btnShowAll = (gcnew System::Windows::Forms::Button());
			this->lblFilterLib = (gcnew System::Windows::Forms::Label());
			this->lblFilterSec = (gcnew System::Windows::Forms::Label());
			this->lblRadius = (gcnew System::Windows::Forms::Label());
			this->lblMarquee = (gcnew System::Windows::Forms::Label());
			this->marqueeTimer = (gcnew System::Windows::Forms::Timer());

			this->Controls->Add(this->cmbFilterLibrary);
			this->Controls->Add(this->cmbFilterSection);
          this->Controls->Add(this->cmbRadius);
          this->Controls->Add(this->chkEbookOnly);
			this->Controls->Add(this->btnShowAll);
			this->Controls->Add(this->lblFilterLib);
			this->Controls->Add(this->lblFilterSec);
			this->Controls->Add(this->lblRadius);
			this->Controls->Add(this->lblMarquee);

			this->cmbFilterLibrary->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->cmbFilterSection->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->cmbRadius->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->chkEbookOnly->CheckedChanged += gcnew System::EventHandler(this, &MyForm::OnFiltersChanged);
			this->marqueeTimer->Interval = 10;
			this->marqueeTimer->Tick += gcnew System::EventHandler(this, &MyForm::marqueeTimer_Tick);

			ApplyModernStyle();
			FetchUserLocation();
			LoadDataFilters();
			LoadBooksToGrid();
           this->marqueeTimer->Start();
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
	private: System::Windows::Forms::Button^ btnShowAll;
	private: System::Windows::Forms::Button^ btnAbout;
	private: System::Windows::Forms::Button^ btnStat;
	private: System::Windows::Forms::Button^ btnReader;
	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Button^ btnHistory;
	private: System::Windows::Forms::Label^ lblFilterLib;
	private: System::Windows::Forms::Label^ lblFilterSec;
	private: System::Windows::Forms::Label^ lblRadius;
 private: System::Windows::Forms::Label^ lblMarquee;
	private: System::Windows::Forms::Timer^ marqueeTimer;
	private: int marqueeStep = 1;
	private: bool isUiUpdating = false;

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
			Match^ matchLat = Regex::Match(json, "\"lat\":([\\d\\.]+)");
			Match^ matchLon = Regex::Match(json, "\"lon\":([\\d\\.]+)");

			if (matchLat->Success && matchLon->Success) {
				userLat = Double::Parse(matchLat->Groups[1]->Value, System::Globalization::CultureInfo::InvariantCulture);
				userLon = Double::Parse(matchLon->Groups[1]->Value, System::Globalization::CultureInfo::InvariantCulture);
				isLocationFetched = true;
			}
		}
		catch (Exception^) {
			// Xatolik yuz bersa standart(default) koordinatalar qoladi
		}
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
		Color darkBg = System::Drawing::Color::White;
		Color panelBg = System::Drawing::Color::FromArgb(245, 245, 245);
		Color accentColor = System::Drawing::Color::FromArgb(40, 44, 52);
		Color textColor = System::Drawing::Color::FromArgb(33, 37, 41);
		Color textMuted = System::Drawing::Color::FromArgb(108, 117, 125);

		this->BackColor = darkBg;
		this->ForeColor = textColor;
		this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

		lblSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold));
		lblSearch->ForeColor = textColor;
		txtSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.0F));
		txtSearch->BackColor = panelBg;
		txtSearch->ForeColor = textColor;
		txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

       lblSearch->Location = System::Drawing::Point(20, 25);
		txtSearch->Location = System::Drawing::Point(230, 22);
		txtSearch->Size = System::Drawing::Size(270, 30);

        array<Button^>^ buttons = { btnSearch, btnReader, btnStat, btnHistory, btnAbout, btnSettings, btnAdmin, btnShowAll };
		for each (Button^ btn in buttons) {
			if (btn != nullptr) {
				btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				btn->FlatAppearance->BorderSize = 0;
				btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold));
				btn->ForeColor = textColor;
				btn->Cursor = System::Windows::Forms::Cursors::Hand;
				btn->Height = 35;
			}
		}

		btnSearch->Location = System::Drawing::Point(510, 20);
		btnSearch->Size = System::Drawing::Size(80, 35);
		btnSearch->BackColor = accentColor;
		btnSearch->ForeColor = System::Drawing::Color::White;

		btnReader->Location = System::Drawing::Point(600, 20);
		btnReader->Size = System::Drawing::Size(90, 35);
		btnReader->BackColor = panelBg;
		btnReader->ForeColor = textColor;
		btnReader->Text = L"O'quvchi";

		btnStat->Location = System::Drawing::Point(700, 20);
		btnStat->Size = System::Drawing::Size(90, 35);
		btnStat->BackColor = panelBg;
		btnStat->ForeColor = textColor;

		btnHistory->Location = System::Drawing::Point(800, 20);
		btnHistory->Size = System::Drawing::Size(80, 35);
		btnHistory->BackColor = panelBg;
		btnHistory->ForeColor = textColor;

		btnAbout->Location = System::Drawing::Point(890, 20);
		btnAbout->Size = System::Drawing::Size(80, 35);
		btnAbout->BackColor = panelBg;
		btnAbout->ForeColor = textColor;

        btnSettings->Location = System::Drawing::Point(980, 20);
		btnSettings->Size = System::Drawing::Size(105, 35);
		btnSettings->BackColor = panelBg;
		btnSettings->ForeColor = textColor;
		btnSettings->Text = L"Sozlamalar";

		btnAdmin->Location = System::Drawing::Point(1095, 20);
		btnAdmin->Size = System::Drawing::Size(100, 35);
		btnAdmin->BackColor = accentColor;
		btnAdmin->ForeColor = System::Drawing::Color::White;

		lblFilterLib->Text = L"Kutubxona:";
		lblFilterLib->ForeColor = textMuted;
		lblFilterLib->Location = System::Drawing::Point(20, 70);
		cmbFilterLibrary->Location = System::Drawing::Point(115, 68);
		cmbFilterLibrary->Size = System::Drawing::Size(200, 30);
		cmbFilterLibrary->BackColor = panelBg;
		cmbFilterLibrary->ForeColor = textColor;
		cmbFilterLibrary->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbFilterLibrary->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

		lblFilterSec->Text = L"Bo'lim:";
		lblFilterSec->ForeColor = textMuted;
		lblFilterSec->Location = System::Drawing::Point(335, 70);
		cmbFilterSection->Location = System::Drawing::Point(395, 68);
		cmbFilterSection->Size = System::Drawing::Size(180, 30);
		cmbFilterSection->BackColor = panelBg;
		cmbFilterSection->ForeColor = textColor;
		cmbFilterSection->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbFilterSection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

		lblRadius->Text = L"Radius:";
		lblRadius->ForeColor = textMuted;
		lblRadius->Location = System::Drawing::Point(590, 70);
		cmbRadius->Location = System::Drawing::Point(650, 68);
		cmbRadius->Size = System::Drawing::Size(130, 30);
		cmbRadius->BackColor = panelBg;
		cmbRadius->ForeColor = textColor;
		cmbRadius->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		cmbRadius->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

		chkEbookOnly->Text = L"Faqat e-kitob";
		chkEbookOnly->ForeColor = textColor;
		chkEbookOnly->Location = System::Drawing::Point(800, 70);
		chkEbookOnly->AutoSize = true;

		btnShowAll->Text = L"Barchasi";
        btnShowAll->Location = System::Drawing::Point(940, 65);
		btnShowAll->Size = System::Drawing::Size(120, 35);
		btnShowAll->BackColor = panelBg;

		lblMarquee->Text = L"TATU Library";
		lblMarquee->AutoSize = true;
		lblMarquee->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, System::Drawing::FontStyle::Bold);
		lblMarquee->ForeColor = System::Drawing::Color::FromArgb(52, 73, 94);
		lblMarquee->BackColor = System::Drawing::Color::Transparent;
        lblMarquee->Location = System::Drawing::Point(-lblMarquee->PreferredWidth, 108);

     flpResults->Location = System::Drawing::Point(20, 150);
		flpResults->Size = System::Drawing::Size(1180, 450);
		flpResults->BackColor = darkBg;
		flpResults->AutoScroll = true;

		lblMarquee->BringToFront();

      MakeRounded(btnSearch, 6); MakeRounded(btnAdmin, 6); MakeRounded(btnShowAll, 6); MakeRounded(btnStat, 6); MakeRounded(btnAbout, 6); MakeRounded(btnReader, 6); MakeRounded(btnSettings, 6); MakeRounded(btnHistory, 6);
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
		if (File::Exists("libraries.txt")) {
			array<String^>^ lines = File::ReadAllLines("libraries.txt");
			for each(String^ line in lines) {
				array<String^>^ parts = line->Split('|');
				if (parts->Length >= 1) {
					cmbFilterLibrary->Items->Add(parts[0]);
				}
			}
		}
		cmbFilterLibrary->SelectedIndex = 0;

		cmbFilterSection->Items->Clear();
		cmbFilterSection->Items->Add(L"Barchasi");
		if (File::Exists("sections.txt")) {
			array<String^>^ lines = File::ReadAllLines("sections.txt");
			for each(String^ line in lines) cmbFilterSection->Items->Add(line);
		}
		cmbFilterSection->SelectedIndex = 0;

		cmbRadius->Items->Clear();
		cmbRadius->Items->Add(L"Barchasi");
		cmbRadius->Items->Add(L"2 km");
		cmbRadius->Items->Add(L"5 km");
		cmbRadius->Items->Add(L"10 km");
		cmbRadius->Items->Add(L"20 km");
		cmbRadius->SelectedIndex = 0;
       isUiUpdating = false;
	}

	private: System::Void LoadBooksToGrid() {
      flpResults->SuspendLayout();
		flpResults->Controls->Clear();

		System::Drawing::Bitmap^ emptyImage = gcnew System::Drawing::Bitmap(1, 1);

		String^ search = txtSearch->Text != nullptr ? txtSearch->Text->ToLower() : L"";
		String^ libFilter = cmbFilterLibrary->Text != nullptr ? cmbFilterLibrary->Text : L"Barchasi";
		String^ secFilter = cmbFilterSection->Text != nullptr ? cmbFilterSection->Text : L"Barchasi";
		String^ radiusFilter = cmbRadius->Text != nullptr ? cmbRadius->Text : L"Barchasi";
		bool onlyEbooks = chkEbookOnly != nullptr && chkEbookOnly->Checked;
		double maxRadius = -1;
		if (radiusFilter != L"Barchasi") {
			String^ num = radiusFilter->Replace(L" km", L"");
			double parsed = 0;
			if (Double::TryParse(num, parsed)) maxRadius = parsed;
		}

		System::Collections::Generic::List<String^>^ issuedBooks = gcnew System::Collections::Generic::List<String^>();
		if (File::Exists("issues.txt")) {
			array<String^>^ issLines = File::ReadAllLines("issues.txt");
			for each (String^ l in issLines) {
				array<String^>^ p = l->Split('|');
				if (p->Length >= 2) {
					if (!issuedBooks->Contains(p[1]->ToLower())) {
						issuedBooks->Add(p[1]->ToLower());
					}
				}
			}
		}

		System::Collections::Generic::Dictionary<String^, array<double>^>^ libsMap = gcnew System::Collections::Generic::Dictionary<String^, array<double>^>();
		if (File::Exists("libraries.txt")) {
			array<String^>^ libLines = File::ReadAllLines("libraries.txt");
			for each (String^ l in libLines) {
				array<String^>^ p = l->Split('|');
				if (p->Length >= 3) {
					try {
						array<double>^ coords = gcnew array<double>(2);
						coords[0] = Double::Parse(p[1], System::Globalization::CultureInfo::InvariantCulture);
						coords[1] = Double::Parse(p[2], System::Globalization::CultureInfo::InvariantCulture);
						libsMap->Add(p[0], coords);
					} catch (...) {}
				}
			}
		}

		if (File::Exists("books.txt")) {
			System::Collections::Generic::List<array<Object^>^>^ results = gcnew System::Collections::Generic::List<array<Object^>^>();

			array<String^>^ lines = File::ReadAllLines("books.txt");
			for each (String^ line in lines) {
				array<String^>^ parts = line->Split('|');
               if (parts->Length >= 5) {
					String^ ebookPathRaw = parts->Length > 6 ? parts[6] : L"";
					if (onlyEbooks && String::IsNullOrWhiteSpace(ebookPathRaw)) {
						continue;
					}
					bool matchSearch = String::IsNullOrWhiteSpace(search) || parts[0]->ToLower()->Contains(search) || parts[1]->ToLower()->Contains(search);
					bool matchLib = (libFilter == L"Barchasi" || libFilter == parts[1]);
					bool matchSec = (secFilter == L"Barchasi" || secFilter == parts[2]);

					if (matchSearch && matchLib && matchSec) {
						double libLat = 41.3110; 
						double libLon = 69.2401;

						if (libsMap->ContainsKey(parts[1])) {
							array<double>^ libCoords = libsMap[parts[1]];
							libLat = libCoords[0];
							libLon = libCoords[1];
						} else {
							if (parts[1] == L"Markaziy Kutubxona") { libLat = 41.311081; libLon = 69.240562; }
							else if (parts[1] == L"Shahar Kutubxonasi") { libLat = 41.2995; libLon = 69.2401; }
							else if (parts[1] == L"Talabalar Kutubxonasi") { libLat = 41.3456; libLon = 69.2874; }
						}

						double dist = CalculateDistance(userLat, userLon, libLat, libLon);
						if (maxRadius > 0 && dist > maxRadius) {
							continue;
						}

						Image^ img = emptyImage;
						if (parts->Length > 5 && !String::IsNullOrWhiteSpace(parts[5])) {
							String^ path1 = parts[5];
							String^ path2 = Path::Combine(Application::StartupPath, parts[5]);
							String^ finalPath = L"";

							if (File::Exists(path1)) finalPath = path1;
							else if (File::Exists(path2)) finalPath = path2;

							if (finalPath != L"") {
								try { 
									FileStream^ fs = gcnew FileStream(finalPath, FileMode::Open, FileAccess::Read);
									img = Image::FromStream(fs);
									fs->Close(); 
								} catch (...) {}
							}
						}

						String^ holat = issuedBooks->Contains(parts[0]->ToLower()) ? L"Berilgan (Band)" : L"Mavjud";

                       array<Object^>^ row = gcnew array<Object^>(12);
						row[0] = img;
						row[1] = parts[0];
						row[2] = parts[1];
						row[3] = parts[2];
						row[4] = parts[3];
						row[5] = parts[4];
						row[6] = Math::Round(dist, 2).ToString() + L" km";
						row[7] = holat;
						row[8] = dist.ToString(System::Globalization::CultureInfo::InvariantCulture); 
						row[9] = libLat.ToString(System::Globalization::CultureInfo::InvariantCulture);
						row[10] = libLon.ToString(System::Globalization::CultureInfo::InvariantCulture);
						row[11] = parts->Length > 6 ? parts[6] : L"";

						results->Add(row);
					}
				}
			}

			results->Sort(gcnew Comparison<array<Object^>^>(this, &MyForm::CompareDistance));

         for (int i = 0; i < results->Count; i++) {
				array<Object^>^ res = results[i];
				Panel^ card = gcnew Panel();
				card->Size = System::Drawing::Size(200, 310);
				card->BackColor = System::Drawing::Color::FromArgb(248, 249, 250);
				card->Margin = System::Windows::Forms::Padding(10, 10, 15, 20);
				MakeRounded(card, 8); // Tish tishini kamaytirish uchun 15 dan 8 ga tushirildi
				card->Cursor = Cursors::Hand;

				PictureBox^ pb = gcnew PictureBox();
				pb->Size = System::Drawing::Size(200, 180);
				pb->Location = System::Drawing::Point(0, 0);
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->Image = dynamic_cast<Image^>(res[0]);
				if (pb->Image == emptyImage) { pb->BackColor = System::Drawing::Color::FromArgb(230, 230, 230); }
				pb->Cursor = Cursors::Hand;

				Label^ lblTitle = gcnew Label();
				lblTitle->Text = res[1]->ToString();
				lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, System::Drawing::FontStyle::Bold);
				lblTitle->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
				lblTitle->AutoSize = false;
				lblTitle->Size = System::Drawing::Size(180, 45); 
				lblTitle->Location = System::Drawing::Point(10, 195);
				lblTitle->Cursor = Cursors::Hand;

				Label^ lblDist = gcnew Label();
				lblDist->Text = res[6]->ToString() + " • " + res[3]->ToString();
				lblDist->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Regular);
				lblDist->ForeColor = System::Drawing::Color::FromArgb(108, 117, 125);
				lblDist->AutoSize = true;
				lblDist->Location = System::Drawing::Point(10, 245);
				lblDist->Cursor = Cursors::Hand;

				Label^ lblStat = gcnew Label();
				lblStat->Text = res[7]->ToString();
				lblStat->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold);
				lblStat->Location = System::Drawing::Point(10, 270);
				lblStat->AutoSize = true;
				lblStat->ForeColor = (res[7]->ToString() == L"Berilgan (Band)") ? System::Drawing::Color::FromArgb(255, 99, 132) : System::Drawing::Color::FromArgb(46, 204, 113);
				lblStat->Cursor = Cursors::Hand;

				EventHandler^ clickHnd = gcnew EventHandler(this, &MyForm::Card_Click);
				bool hasEbook = (res->Length > 11 && res[11] != nullptr && !String::IsNullOrWhiteSpace(res[11]->ToString()));

				if (hasEbook) {
					Label^ lblEbook = gcnew Label();
					lblEbook->Text = L"E-kitob";
					lblEbook->AutoSize = true;
					lblEbook->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);
					lblEbook->ForeColor = System::Drawing::Color::White;
					lblEbook->Location = System::Drawing::Point(130, 10);
					lblEbook->Padding = System::Windows::Forms::Padding(6, 2, 6, 2);
					lblEbook->Cursor = Cursors::Hand;
					lblEbook->Tag = res;
					lblEbook->Click += clickHnd;
					card->Controls->Add(lblEbook);
				}

				if (i == 0) {
					Label^ lblNearest = gcnew Label();
					lblNearest->Text = L"Eng yaqin";
					lblNearest->AutoSize = true;
					lblNearest->BackColor = System::Drawing::Color::FromArgb(46, 204, 113);
					lblNearest->ForeColor = System::Drawing::Color::White;
					lblNearest->Location = System::Drawing::Point(10, 10);
					lblNearest->Padding = System::Windows::Forms::Padding(6, 2, 6, 2);
					lblNearest->Cursor = Cursors::Hand;
					lblNearest->Tag = res;
					lblNearest->Click += clickHnd;
					card->Controls->Add(lblNearest);
				}

				card->Click += clickHnd;
				pb->Click += clickHnd;
				lblTitle->Click += clickHnd;
				lblDist->Click += clickHnd;
				lblStat->Click += clickHnd;

				card->Tag = res;
				pb->Tag = res;
				lblTitle->Tag = res;
				lblDist->Tag = res;
				lblStat->Tag = res;

				card->Controls->Add(pb);
				card->Controls->Add(lblTitle);
				card->Controls->Add(lblDist);
				card->Controls->Add(lblStat);

				flpResults->Controls->Add(card);
			}
		}
       flpResults->ResumeLayout();
	}

	private: System::Void Card_Click(System::Object^ sender, System::EventArgs^ e) {
		Control^ ctrl = dynamic_cast<Control^>(sender);
		if (ctrl != nullptr && ctrl->Tag != nullptr) {
			array<Object^>^ res = dynamic_cast<array<Object^>^>(ctrl->Tag);
			ShowBookDetails(res);
		}
	}

	private: System::Void ShowBookDetails(array<Object^>^ res) {
		Form^ fd = gcnew Form();
		fd->Text = L"Kitob haqida ma'lumot";
		fd->Size = System::Drawing::Size(600, 420);
		fd->BackColor = System::Drawing::Color::White;
		fd->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
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
		if (pb->Image == nullptr || pb->Image->Size == emptyImage->Size) { pb->BackColor = System::Drawing::Color::FromArgb(230, 230, 230); }
		MakeRounded(pb, 10);
		fd->Controls->Add(pb);

		Color txtColor = System::Drawing::Color::FromArgb(33, 37, 41);
		Color mutColor = System::Drawing::Color::FromArgb(108, 117, 125);

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
		l1->Text = L"Kutubxona: " + res[2]->ToString();
		l1->Location = System::Drawing::Point(230, yp);
		l1->AutoSize = true;
		l1->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l1->ForeColor = mutColor;
		fd->Controls->Add(l1);
		yp += 30;

		Label^ l2 = gcnew Label();
		l2->Text = L"Bo'lim: " + res[3]->ToString();
		l2->Location = System::Drawing::Point(230, yp);
		l2->AutoSize = true;
		l2->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l2->ForeColor = mutColor;
		fd->Controls->Add(l2);
		yp += 30;

		Label^ l3 = gcnew Label();
		l3->Text = L"Joylashuv: " + res[4]->ToString() + L" / " + res[5]->ToString();
		l3->Location = System::Drawing::Point(230, yp);
		l3->AutoSize = true;
		l3->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l3->ForeColor = mutColor;
		fd->Controls->Add(l3);
		yp += 30;

		Label^ l4 = gcnew Label();
		l4->Text = L"Masofa: " + res[6]->ToString();
		l4->Location = System::Drawing::Point(230, yp);
		l4->AutoSize = true;
		l4->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Regular);
		l4->ForeColor = mutColor;
		fd->Controls->Add(l4);
		yp += 35;

		Color statColor = (res[7]->ToString() == L"Berilgan (Band)") ? System::Drawing::Color::FromArgb(255, 99, 132) : System::Drawing::Color::FromArgb(46, 204, 113);

		Label^ lst = gcnew Label();
		lst->Text = L"Holati: " + res[7]->ToString();
		lst->Location = System::Drawing::Point(230, yp);
		lst->AutoSize = true;
		lst->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, System::Drawing::FontStyle::Bold);
		lst->ForeColor = statColor;
		fd->Controls->Add(lst);

		Button^ btnOk = gcnew Button();
		btnOk->Text = L"Yopish";
		btnOk->Location = System::Drawing::Point(430, 310);
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
		btnMap->Text = L"Yo'nalish";
		btnMap->Location = System::Drawing::Point(290, 310);
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
		btnEbook->Text = L"E-kitob";
		btnEbook->Location = System::Drawing::Point(150, 310);
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

		fd->AcceptButton = btnOk;
		fd->ShowDialog();
	}

	private: System::Void btnAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ prompt = gcnew Form();
		prompt->Width = 300;
		prompt->Height = 160;
		prompt->Text = L"Autentifikatsiya";
		prompt->StartPosition = FormStartPosition::CenterParent;
		prompt->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		prompt->MaximizeBox = false;
		prompt->MinimizeBox = false;

		Label^ textLabel = gcnew Label();
		textLabel->Left = 20;
		textLabel->Top = 20;
		textLabel->Text = L"Admin parolini kiriting:";
		textLabel->AutoSize = true;

		TextBox^ inputBox = gcnew TextBox();
		inputBox->Left = 20;
		inputBox->Top = 45;
		inputBox->Width = 240;
		inputBox->PasswordChar = '*';

		Button^ confirmation = gcnew Button();
		confirmation->Text = L"Kirish";
		confirmation->Left = 160;
		confirmation->Top = 75;
		confirmation->Width = 100;
		confirmation->DialogResult = System::Windows::Forms::DialogResult::OK;

		prompt->Controls->Add(textLabel);
		prompt->Controls->Add(inputBox);
		prompt->Controls->Add(confirmation);
		prompt->AcceptButton = confirmation;

		if (prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (inputBox->Text == L"TATU2026") {
				AdminForm^ adminForm = gcnew AdminForm();
				adminForm->ShowDialog();
				LoadDataFilters();
				LoadBooksToGrid();
           this->marqueeTimer->Start();
			}
			else {
				MessageBox::Show(L"Parol noto'g'ri!", L"Xatolik", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	private: System::Void btnAbout_Click(System::Object^ sender, System::EventArgs^ e) {
		AboutForm^ infoForm = gcnew AboutForm();
		infoForm->ShowDialog();
	}

	private: System::Void btnStat_Click(System::Object^ sender, System::EventArgs^ e) {
		StatisticsForm^ statForm = gcnew StatisticsForm();
		statForm->ShowDialog();
	}

	private: System::Void btnReader_Click(System::Object^ sender, System::EventArgs^ e) {
		ReaderForm^ rF = gcnew ReaderForm();
		rF->ShowDialog();
	}

	private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		SettingsForm^ sF = gcnew SettingsForm();
		sF->ShowDialog();
	}

	private: System::Void btnHistory_Click(System::Object^ sender, System::EventArgs^ e) {
		HistoryForm^ hF = gcnew HistoryForm();
		hF->ShowDialog();
	}

	private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadBooksToGrid();
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
			MessageBox::Show(L"Bu kitob uchun elektron fayl biriktirilmagan.", L"Ma'lumot", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		String^ fullPath = File::Exists(ebookPath) ? ebookPath : Path::Combine(Application::StartupPath, ebookPath);
		if (!File::Exists(fullPath)) {
			MessageBox::Show(L"E-kitob fayli topilmadi.", L"Xatolik", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
      if (chkEbookOnly != nullptr) chkEbookOnly->Checked = false;
      isUiUpdating = false;
		LoadBooksToGrid();
	}

	private: int CompareDistance(array<Object^>^ a, array<Object^>^ b) {
		double dist1 = Double::Parse(a[8]->ToString(), System::Globalization::CultureInfo::InvariantCulture);
		double dist2 = Double::Parse(b[8]->ToString(), System::Globalization::CultureInfo::InvariantCulture);
		return dist1.CompareTo(dist2);
	}

	private: System::Void marqueeTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (lblMarquee == nullptr) return;
		lblMarquee->Left += marqueeStep;
		if (lblMarquee->Left > this->ClientSize.Width) {
			lblMarquee->Left = -lblMarquee->Width;
		}
	}

	};
}
