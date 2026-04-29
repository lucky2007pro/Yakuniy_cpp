#pragma once

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Text::RegularExpressions;

	public ref class AdminForm : public System::Windows::Forms::Form
	{
	private: 
		// Nerverd serverga o'tishda shu yerni o'zgartiring
		String^ serverUrl = L"http://5.189.136.95:81"; 
		String^ apiUrl = serverUrl + L"/api/";

	private: System::Collections::Generic::Dictionary<String^, int>^ libIds = gcnew System::Collections::Generic::Dictionary<String^, int>();
	private: System::Collections::Generic::Dictionary<String^, int>^ secIds = gcnew System::Collections::Generic::Dictionary<String^, int>();
	private: System::Collections::Generic::Dictionary<String^, int>^ readerIds = gcnew System::Collections::Generic::Dictionary<String^, int>();
	private: System::Collections::Generic::Dictionary<int, int>^ issueRowToId = gcnew System::Collections::Generic::Dictionary<int, int>(); // rowIndex -> issueId
	private: System::Collections::Generic::Dictionary<String^, int>^ bookIds = gcnew System::Collections::Generic::Dictionary<String^, int>(); // bookTitle -> bookId
	public:
		AdminForm(void)
		{
          			this->insightsAnimTimer = gcnew System::Windows::Forms::Timer();
			this->insightsAnimTimer->Interval = 30;
			this->insightsAnimTimer->Tick += gcnew System::EventHandler(this, &AdminForm::insightsAnimTimer_Tick);
			InitializeComponent();
			this->Resize += gcnew System::EventHandler(this, &AdminForm::AdminForm_Resize);
			ApplyModernStyle();
			this->WindowState = FormWindowState::Maximized;
		}

	protected:
		~AdminForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPageBooks;
	private: System::Windows::Forms::TabPage^ tabPageLibraries;
	private: System::Windows::Forms::TabPage^ tabPageSections;
	private: System::Windows::Forms::TabPage^ tabPageReaders;
	private: System::Windows::Forms::TabPage^ tabPageIssues;
	private: System::Windows::Forms::TabPage^ tabPageInsights;

	// Books Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvBooks;
	private: System::Windows::Forms::TextBox^ txtBookName;
	private: System::Windows::Forms::ComboBox^ cmbBookLibrary;
	private: System::Windows::Forms::ComboBox^ cmbBookSection;
	private: System::Windows::Forms::TextBox^ txtBookShelf;
	private: System::Windows::Forms::TextBox^ txtBookRow;
	private: System::Windows::Forms::Button^ btnAddBook;
	private: System::Windows::Forms::Button^ btnEditBook;
	private: System::Windows::Forms::Button^ btnDeleteBook;
	private: System::Windows::Forms::Label^ lblBookName;
	private: System::Windows::Forms::Label^ lblBookLibrary;
	private: System::Windows::Forms::Label^ lblBookSection;
	private: System::Windows::Forms::Label^ lblBookShelf;
	private: System::Windows::Forms::Label^ lblBookRow;
	private: System::Windows::Forms::Button^ btnSelectImage;
   private: System::Windows::Forms::Button^ btnSelectEbook;
	private: System::Windows::Forms::Label^ lblImagePath;
   private: System::Windows::Forms::Label^ lblEbookPath;
	private: System::String^ selectedImagePath = L"";
	private: System::String^ selectedEbookPath = L"";

	// Libraries Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvLibraries;
	private: System::Windows::Forms::TextBox^ txtLibraryName;
	private: System::Windows::Forms::TextBox^ txtLibraryLat;
	private: System::Windows::Forms::TextBox^ txtLibraryLon;
	private: System::Windows::Forms::Button^ btnAddLibrary;
	private: System::Windows::Forms::Button^ btnDeleteLibrary;
	private: System::Windows::Forms::Label^ lblLibraryName;
	private: System::Windows::Forms::Label^ lblLibraryLat;
	private: System::Windows::Forms::Label^ lblLibraryLon;

	// Sections Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvSections;
	private: System::Windows::Forms::TextBox^ txtSectionName;
	private: System::Windows::Forms::Button^ btnAddSection;
	private: System::Windows::Forms::Button^ btnDeleteSection;
	private: System::Windows::Forms::Label^ lblSectionName;

	// Readers Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvReaders;
	private: System::Windows::Forms::TextBox^ txtReaderName;
	private: System::Windows::Forms::TextBox^ txtReaderPhone;
	private: System::Windows::Forms::TextBox^ txtReaderID;
	private: System::Windows::Forms::Button^ btnAddReader;
	private: System::Windows::Forms::Button^ btnDeleteReader;
	private: System::Windows::Forms::Button^ btnApproveReader;
	private: System::Windows::Forms::Button^ btnRejectReader;
	private: System::Windows::Forms::Button^ btnPreviewReaderCard;
	private: System::Windows::Forms::Label^ lblReadersPageTitle;
	private: System::Windows::Forms::Label^ lblReadersPageHint;

	// Issues Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvIssues;
	private: System::Windows::Forms::ComboBox^ cmbIssueReader;
	private: System::Windows::Forms::ComboBox^ cmbIssueBook;
	private: System::Windows::Forms::DateTimePicker^ dtpReturnDate;
	private: System::Windows::Forms::Button^ btnIssueBook;
	private: System::Windows::Forms::Button^ btnReturnBook;

	// Insights Tab Controls
	private: System::Windows::Forms::DataGridView^ dgvDemand;
	private: System::Windows::Forms::Panel^ pnlCardTotal;
	private: System::Windows::Forms::Panel^ pnlCardTop;
	private: System::Windows::Forms::Panel^ pnlCardReaders;
	private: System::Windows::Forms::Label^ lblTotalTitle;
	private: System::Windows::Forms::Label^ lblTotalValue;
	private: System::Windows::Forms::Label^ lblTopTitle;
	private: System::Windows::Forms::Label^ lblTopValue;
	private: System::Windows::Forms::Label^ lblReadersTitle;
	private: System::Windows::Forms::Label^ lblReadersValue;
	private: System::Windows::Forms::Panel^ pnlDonutChart;
	private: System::Windows::Forms::Timer^ insightsAnimTimer;
	private: int displayedTotalIssues = 0;
	private: int targetTotalIssues = 0;
	// Donut chart data
	private: System::Collections::Generic::List<System::Drawing::Color>^ chartColors;
	private: System::Collections::Generic::List<double>^ chartScores;
	private: System::Collections::Generic::List<String^>^ chartLabels;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPageBooks = (gcnew System::Windows::Forms::TabPage());
			this->tabPageLibraries = (gcnew System::Windows::Forms::TabPage());
			this->tabPageSections = (gcnew System::Windows::Forms::TabPage());
			this->tabPageReaders = (gcnew System::Windows::Forms::TabPage());
			this->tabPageIssues = (gcnew System::Windows::Forms::TabPage());
			this->tabPageInsights = (gcnew System::Windows::Forms::TabPage());

			// Readers & Issues Init
			this->dgvReaders = (gcnew System::Windows::Forms::DataGridView());
			this->txtReaderName = (gcnew System::Windows::Forms::TextBox());
			this->txtReaderPhone = (gcnew System::Windows::Forms::TextBox());
			this->txtReaderID = (gcnew System::Windows::Forms::TextBox());
			this->btnAddReader = (gcnew System::Windows::Forms::Button());
			this->btnDeleteReader = (gcnew System::Windows::Forms::Button());
			this->btnApproveReader = (gcnew System::Windows::Forms::Button());
			this->btnRejectReader = (gcnew System::Windows::Forms::Button());
			this->btnPreviewReaderCard = (gcnew System::Windows::Forms::Button());
			this->lblReadersPageTitle = (gcnew System::Windows::Forms::Label());
			this->lblReadersPageHint = (gcnew System::Windows::Forms::Label());

			this->dgvIssues = (gcnew System::Windows::Forms::DataGridView());
			this->cmbIssueReader = (gcnew System::Windows::Forms::ComboBox());
			this->cmbIssueBook = (gcnew System::Windows::Forms::ComboBox());
			this->dtpReturnDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnIssueBook = (gcnew System::Windows::Forms::Button());
			this->btnReturnBook = (gcnew System::Windows::Forms::Button());

			this->dgvDemand = (gcnew System::Windows::Forms::DataGridView());
			this->pnlCardTotal = (gcnew System::Windows::Forms::Panel());
			this->pnlCardTop = (gcnew System::Windows::Forms::Panel());
			this->pnlCardReaders = (gcnew System::Windows::Forms::Panel());
			this->pnlDonutChart = (gcnew System::Windows::Forms::Panel());
			this->lblTotalTitle = (gcnew System::Windows::Forms::Label());
			this->lblTotalValue = (gcnew System::Windows::Forms::Label());
			this->lblTopTitle = (gcnew System::Windows::Forms::Label());
			this->lblTopValue = (gcnew System::Windows::Forms::Label());
			this->lblReadersTitle = (gcnew System::Windows::Forms::Label());
			this->lblReadersValue = (gcnew System::Windows::Forms::Label());
			this->chartColors = gcnew System::Collections::Generic::List<System::Drawing::Color>();
			this->chartScores = gcnew System::Collections::Generic::List<double>();
			this->chartLabels = gcnew System::Collections::Generic::List<String^>();

			// Books Tab Controls
			this->dgvBooks = (gcnew System::Windows::Forms::DataGridView());
			this->txtBookName = (gcnew System::Windows::Forms::TextBox());
			this->cmbBookLibrary = (gcnew System::Windows::Forms::ComboBox());
			this->cmbBookSection = (gcnew System::Windows::Forms::ComboBox());
			this->txtBookShelf = (gcnew System::Windows::Forms::TextBox());
			this->txtBookRow = (gcnew System::Windows::Forms::TextBox());
			this->btnAddBook = (gcnew System::Windows::Forms::Button());
			this->btnEditBook = (gcnew System::Windows::Forms::Button());
			this->btnDeleteBook = (gcnew System::Windows::Forms::Button());
			this->btnSelectImage = (gcnew System::Windows::Forms::Button());
           this->btnSelectEbook = (gcnew System::Windows::Forms::Button());
			this->lblImagePath = (gcnew System::Windows::Forms::Label());
            this->lblEbookPath = (gcnew System::Windows::Forms::Label());
			this->lblBookName = (gcnew System::Windows::Forms::Label());
			this->lblBookLibrary = (gcnew System::Windows::Forms::Label());
			this->lblBookSection = (gcnew System::Windows::Forms::Label());
			this->lblBookShelf = (gcnew System::Windows::Forms::Label());
			this->lblBookRow = (gcnew System::Windows::Forms::Label());

			// Libraries Tab
			this->dgvLibraries = (gcnew System::Windows::Forms::DataGridView());
			this->txtLibraryName = (gcnew System::Windows::Forms::TextBox());
			this->txtLibraryLat = (gcnew System::Windows::Forms::TextBox());
			this->txtLibraryLon = (gcnew System::Windows::Forms::TextBox());
			this->btnAddLibrary = (gcnew System::Windows::Forms::Button());
			this->btnDeleteLibrary = (gcnew System::Windows::Forms::Button());
			this->lblLibraryName = (gcnew System::Windows::Forms::Label());
			this->lblLibraryLat = (gcnew System::Windows::Forms::Label());
			this->lblLibraryLon = (gcnew System::Windows::Forms::Label());

			// Sections Tab
			this->dgvSections = (gcnew System::Windows::Forms::DataGridView());
			this->txtSectionName = (gcnew System::Windows::Forms::TextBox());
			this->btnAddSection = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSection = (gcnew System::Windows::Forms::Button());
			this->lblSectionName = (gcnew System::Windows::Forms::Label());

			this->tabControl1->SuspendLayout();
			this->tabPageBooks->SuspendLayout();
			this->tabPageLibraries->SuspendLayout();
			this->tabPageSections->SuspendLayout();
			this->tabPageReaders->SuspendLayout();
			this->tabPageIssues->SuspendLayout();
         this->tabPageInsights->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvBooks))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvLibraries))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSections))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReaders))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvIssues))->BeginInit();
          (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvDemand))->BeginInit();
			this->SuspendLayout();

			// tabControl1
			this->tabControl1->Controls->Add(this->tabPageBooks);
			this->tabControl1->Controls->Add(this->tabPageLibraries);
			this->tabControl1->Controls->Add(this->tabPageSections);
			this->tabControl1->Controls->Add(this->tabPageReaders);
			this->tabControl1->Controls->Add(this->tabPageIssues);
          this->tabControl1->Controls->Add(this->tabPageInsights);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(800, 500);

			// tabPageBooks
			this->tabPageBooks->Controls->Add(this->dgvBooks);
			this->tabPageBooks->Controls->Add(this->btnAddBook);
			this->tabPageBooks->Controls->Add(this->btnEditBook);
			this->tabPageBooks->Controls->Add(this->btnDeleteBook);
			this->tabPageBooks->Controls->Add(this->txtBookName);
			this->tabPageBooks->Controls->Add(this->cmbBookLibrary);
			this->tabPageBooks->Controls->Add(this->cmbBookSection);
			this->tabPageBooks->Controls->Add(this->txtBookShelf);
			this->tabPageBooks->Controls->Add(this->txtBookRow);
			this->tabPageBooks->Controls->Add(this->lblBookName);
			this->tabPageBooks->Controls->Add(this->lblBookLibrary);
			this->tabPageBooks->Controls->Add(this->lblBookSection);
			this->tabPageBooks->Controls->Add(this->lblBookShelf);
			this->tabPageBooks->Controls->Add(this->lblBookRow);
			this->tabPageBooks->Controls->Add(this->btnSelectImage);
          this->tabPageBooks->Controls->Add(this->btnSelectEbook);
			this->tabPageBooks->Controls->Add(this->lblImagePath);
           this->tabPageBooks->Controls->Add(this->lblEbookPath);
			this->tabPageBooks->Location = System::Drawing::Point(4, 25);
			this->tabPageBooks->Name = L"tabPageBooks";
			this->tabPageBooks->Padding = System::Windows::Forms::Padding(3);
			this->tabPageBooks->Size = System::Drawing::Size(792, 471);
			this->tabPageBooks->Text = L"Kitoblar";
			this->tabPageBooks->UseVisualStyleBackColor = true;

			// Books Controls Setup
			this->dgvBooks->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvBooks->Location = System::Drawing::Point(250, 20);
			this->dgvBooks->Name = L"dgvBooks";
			this->dgvBooks->Size = System::Drawing::Size(520, 430);
			this->dgvBooks->ColumnCount = 8;
			this->dgvBooks->Columns[0]->Name = L"Nomi";
			this->dgvBooks->Columns[1]->Name = L"Kutubxona";
			this->dgvBooks->Columns[2]->Name = L"Bo'lim";
			this->dgvBooks->Columns[3]->Name = L"Tokcha";
			this->dgvBooks->Columns[4]->Name = L"Qator";
			this->dgvBooks->Columns[5]->Name = L"Rasm (Path)";
			this->dgvBooks->Columns[6]->Name = L"E-kitob (Path)";
			this->dgvBooks->Columns[7]->Name = L"ID";
			this->dgvBooks->Columns[7]->Visible = false;

			this->lblBookName->AutoSize = true;
			this->lblBookName->Location = System::Drawing::Point(10, 20);
			this->lblBookName->Text = L"Kitob nomi:";
			this->txtBookName->Location = System::Drawing::Point(10, 40);
			this->txtBookName->Size = System::Drawing::Size(200, 22);

			this->lblBookLibrary->AutoSize = true;
			this->lblBookLibrary->Location = System::Drawing::Point(10, 70);
			this->lblBookLibrary->Text = L"Kutubxona:";
			this->cmbBookLibrary->Location = System::Drawing::Point(10, 90);
			this->cmbBookLibrary->Size = System::Drawing::Size(200, 22);
			this->cmbBookLibrary->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Markaziy Kutubxona", L"Shahar Kutubxonasi", L"Talabalar Kutubxonasi" });

			this->lblBookSection->AutoSize = true;
			this->lblBookSection->Location = System::Drawing::Point(10, 120);
			this->lblBookSection->Text = L"Bo'lim:";
			this->cmbBookSection->Location = System::Drawing::Point(10, 140);
			this->cmbBookSection->Size = System::Drawing::Size(200, 22);
			this->cmbBookSection->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Matematika", L"Badiiy adabiyot", L"Romanlar" });

			this->lblBookShelf->AutoSize = true;
			this->lblBookShelf->Location = System::Drawing::Point(10, 170);
			this->lblBookShelf->Text = L"Tokcha:";
			this->txtBookShelf->Location = System::Drawing::Point(10, 190);
			this->txtBookShelf->Size = System::Drawing::Size(200, 22);

			this->lblBookRow->AutoSize = true;
			this->lblBookRow->Location = System::Drawing::Point(10, 220);
			this->lblBookRow->Text = L"Qator:";
			this->txtBookRow->Location = System::Drawing::Point(10, 240);
			this->txtBookRow->Size = System::Drawing::Size(200, 22);

			this->btnSelectImage->Location = System::Drawing::Point(10, 270);
			this->btnSelectImage->Size = System::Drawing::Size(90, 30);
			this->btnSelectImage->Text = L"Rasm...";
			this->btnSelectImage->Click += gcnew System::EventHandler(this, &AdminForm::btnSelectImage_Click);

			this->btnSelectEbook->Location = System::Drawing::Point(10, 305);
			this->btnSelectEbook->Size = System::Drawing::Size(90, 30);
			this->btnSelectEbook->Text = L"E-kitob...";
			this->btnSelectEbook->Click += gcnew System::EventHandler(this, &AdminForm::btnSelectEbook_Click);

			this->lblImagePath->AutoSize = true;
			this->lblImagePath->Location = System::Drawing::Point(110, 275);
			this->lblImagePath->Text = L"Rasm tanlanmadi";

			this->lblEbookPath->AutoSize = true;
			this->lblEbookPath->Location = System::Drawing::Point(110, 310);
			this->lblEbookPath->Text = L"E-kitob tanlanmadi";

			this->dgvBooks->SelectionChanged += gcnew System::EventHandler(this, &AdminForm::dgvBooks_SelectionChanged);

           this->btnAddBook->Location = System::Drawing::Point(10, 345);
			this->btnAddBook->Size = System::Drawing::Size(90, 30);
			this->btnAddBook->Text = L"Qo'shish";
			this->btnAddBook->Click += gcnew System::EventHandler(this, &AdminForm::btnAddBook_Click);

         this->btnEditBook->Location = System::Drawing::Point(110, 345);
			this->btnEditBook->Size = System::Drawing::Size(100, 30);
			this->btnEditBook->Text = L"Tahrirlash";
			this->btnEditBook->Click += gcnew System::EventHandler(this, &AdminForm::btnEditBook_Click);

            this->btnDeleteBook->Location = System::Drawing::Point(10, 385);
			this->btnDeleteBook->Size = System::Drawing::Size(200, 30);
			this->btnDeleteBook->Text = L"O'chirish";
			this->btnDeleteBook->Click += gcnew System::EventHandler(this, &AdminForm::btnDeleteBook_Click);

			// tabPageLibraries
			this->tabPageLibraries->Controls->Add(this->dgvLibraries);
			this->tabPageLibraries->Controls->Add(this->txtLibraryName);
			this->tabPageLibraries->Controls->Add(this->txtLibraryLat);
			this->tabPageLibraries->Controls->Add(this->txtLibraryLon);
			this->tabPageLibraries->Controls->Add(this->btnAddLibrary);
			this->tabPageLibraries->Controls->Add(this->btnDeleteLibrary);
			this->tabPageLibraries->Controls->Add(this->lblLibraryName);
			this->tabPageLibraries->Controls->Add(this->lblLibraryLat);
			this->tabPageLibraries->Controls->Add(this->lblLibraryLon);
			this->tabPageLibraries->Location = System::Drawing::Point(4, 25);
			this->tabPageLibraries->Name = L"tabPageLibraries";
			this->tabPageLibraries->Padding = System::Windows::Forms::Padding(3);
			this->tabPageLibraries->Size = System::Drawing::Size(792, 471);
			this->tabPageLibraries->Text = L"Kutubxonalar";
			this->tabPageLibraries->UseVisualStyleBackColor = true;

			this->dgvLibraries->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvLibraries->Location = System::Drawing::Point(250, 20);
			this->dgvLibraries->Name = L"dgvLibraries";
			this->dgvLibraries->Size = System::Drawing::Size(520, 430);
			this->dgvLibraries->ColumnCount = 3;
			this->dgvLibraries->Columns[0]->Name = L"Nomi";
			this->dgvLibraries->Columns[0]->Width = 200;
			this->dgvLibraries->Columns[1]->Name = L"Kenglik (Lat)";
			this->dgvLibraries->Columns[1]->Width = 100;
			this->dgvLibraries->Columns[2]->Name = L"Uzunlik (Lon)";
			this->dgvLibraries->Columns[2]->Width = 100;

			this->lblLibraryName->AutoSize = true;
			this->lblLibraryName->Location = System::Drawing::Point(10, 20);
			this->lblLibraryName->Text = L"Kutubxona nomi:";
			this->txtLibraryName->Location = System::Drawing::Point(10, 40);
			this->txtLibraryName->Size = System::Drawing::Size(200, 22);

			this->lblLibraryLat->AutoSize = true;
			this->lblLibraryLat->Location = System::Drawing::Point(10, 70);
			this->lblLibraryLat->Text = L"Kenglik (masalan 41.31):";
			this->txtLibraryLat->Location = System::Drawing::Point(10, 90);
			this->txtLibraryLat->Size = System::Drawing::Size(200, 22);

			this->lblLibraryLon->AutoSize = true;
			this->lblLibraryLon->Location = System::Drawing::Point(10, 120);
			this->lblLibraryLon->Text = L"Uzunlik (masalan 69.24):";
			this->txtLibraryLon->Location = System::Drawing::Point(10, 140);
			this->txtLibraryLon->Size = System::Drawing::Size(200, 22);

			this->btnAddLibrary->Location = System::Drawing::Point(10, 180);
			this->btnAddLibrary->Size = System::Drawing::Size(90, 30);
			this->btnAddLibrary->Text = L"Qo'shish";
			this->btnAddLibrary->Click += gcnew System::EventHandler(this, &AdminForm::btnAddLibrary_Click);

			this->btnDeleteLibrary->Location = System::Drawing::Point(120, 180);
			this->btnDeleteLibrary->Size = System::Drawing::Size(90, 30);
			this->btnDeleteLibrary->Text = L"O'chirish";
			this->btnDeleteLibrary->Click += gcnew System::EventHandler(this, &AdminForm::btnDeleteLibrary_Click);

			// tabPageSections
			this->tabPageSections->Controls->Add(this->dgvSections);
			this->tabPageSections->Controls->Add(this->txtSectionName);
			this->tabPageSections->Controls->Add(this->btnAddSection);
			this->tabPageSections->Controls->Add(this->btnDeleteSection);
			this->tabPageSections->Controls->Add(this->lblSectionName);
			this->tabPageSections->Location = System::Drawing::Point(4, 25);
			this->tabPageSections->Name = L"tabPageSections";
			this->tabPageSections->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSections->Size = System::Drawing::Size(792, 471);
			this->tabPageSections->Text = L"Bo'limlar";
			this->tabPageSections->UseVisualStyleBackColor = true;

			this->dgvSections->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvSections->Location = System::Drawing::Point(250, 20);
			this->dgvSections->Name = L"dgvSections";
			this->dgvSections->Size = System::Drawing::Size(520, 430);
			this->dgvSections->ColumnCount = 1;
			this->dgvSections->Columns[0]->Name = L"Nomi";
			this->dgvSections->Columns[0]->Width = 400;

			this->lblSectionName->AutoSize = true;
			this->lblSectionName->Location = System::Drawing::Point(10, 20);
			this->lblSectionName->Text = L"Bo'lim nomi:";
			this->txtSectionName->Location = System::Drawing::Point(10, 40);
			this->txtSectionName->Size = System::Drawing::Size(200, 22);

			this->btnAddSection->Location = System::Drawing::Point(10, 80);
			this->btnAddSection->Size = System::Drawing::Size(90, 30);
			this->btnAddSection->Text = L"Qo'shish";
			this->btnAddSection->Click += gcnew System::EventHandler(this, &AdminForm::btnAddSection_Click);

			this->btnDeleteSection->Location = System::Drawing::Point(120, 80);
			this->btnDeleteSection->Size = System::Drawing::Size(90, 30);
			this->btnDeleteSection->Text = L"O'chirish";
			this->btnDeleteSection->Click += gcnew System::EventHandler(this, &AdminForm::btnDeleteSection_Click);

			// tabPageReaders
			this->tabPageReaders->Controls->Add(this->dgvReaders);
			this->tabPageReaders->Controls->Add(this->txtReaderName);
			this->tabPageReaders->Controls->Add(this->txtReaderPhone);
			this->tabPageReaders->Controls->Add(this->txtReaderID);
			this->tabPageReaders->Controls->Add(this->btnAddReader);
			this->tabPageReaders->Controls->Add(this->btnDeleteReader);
			this->tabPageReaders->Controls->Add(this->btnApproveReader);
			this->tabPageReaders->Controls->Add(this->btnRejectReader);
			this->tabPageReaders->Controls->Add(this->btnPreviewReaderCard);
			this->tabPageReaders->Controls->Add(this->lblReadersPageTitle);
			this->tabPageReaders->Controls->Add(this->lblReadersPageHint);
			this->tabPageReaders->Location = System::Drawing::Point(4, 25);
			this->tabPageReaders->Name = L"tabPageReaders";
			this->tabPageReaders->Padding = System::Windows::Forms::Padding(3);
			this->tabPageReaders->Size = System::Drawing::Size(792, 471);
			this->tabPageReaders->Text = L"Kitobxonlar";
			this->tabPageReaders->UseVisualStyleBackColor = true;

			this->dgvReaders->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvReaders->Location = System::Drawing::Point(250, 20);
			this->dgvReaders->Name = L"dgvReaders";
			this->dgvReaders->Size = System::Drawing::Size(520, 430);
			this->dgvReaders->ColumnCount = 6;
			this->dgvReaders->Columns[0]->Name = L"F.I.Sh";
			this->dgvReaders->Columns[1]->Name = L"Telefon";
			this->dgvReaders->Columns[2]->Name = L"ID Karta";
			this->dgvReaders->Columns[3]->Name = L"Status";
			this->dgvReaders->Columns[4]->Name = L"ID";
			this->dgvReaders->Columns[4]->Visible = false;
			this->dgvReaders->Columns[5]->Name = L"KartaRasm";
			this->dgvReaders->Columns[5]->Visible = false;

			this->txtReaderName->Location = System::Drawing::Point(10, 40);
			this->txtReaderName->Size = System::Drawing::Size(200, 22);
			this->txtReaderName->Text = L""; 

			this->txtReaderPhone->Location = System::Drawing::Point(10, 80);
			this->txtReaderPhone->Size = System::Drawing::Size(200, 22);
			this->txtReaderPhone->Text = L"";

			this->txtReaderID->Location = System::Drawing::Point(10, 120);
			this->txtReaderID->Size = System::Drawing::Size(200, 22);
			this->txtReaderID->Text = L"";

			this->btnAddReader->Location = System::Drawing::Point(10, 160);
			this->btnAddReader->Size = System::Drawing::Size(90, 30);
			this->btnAddReader->Text = L"Qo'shish";
			this->btnAddReader->Click += gcnew System::EventHandler(this, &AdminForm::btnAddReader_Click);

			this->btnDeleteReader->Location = System::Drawing::Point(120, 160);
			this->btnDeleteReader->Size = System::Drawing::Size(90, 30);
			this->btnDeleteReader->Text = L"O'chirish";
			this->btnDeleteReader->Click += gcnew System::EventHandler(this, &AdminForm::btnDeleteReader_Click);

			this->btnApproveReader->Location = System::Drawing::Point(10, 200);
			this->btnApproveReader->Size = System::Drawing::Size(100, 30);
			this->btnApproveReader->Text = L"Tasdiqlash";
			this->btnApproveReader->Click += gcnew System::EventHandler(this, &AdminForm::btnApproveReader_Click);

			this->btnRejectReader->Location = System::Drawing::Point(120, 200);
			this->btnRejectReader->Size = System::Drawing::Size(90, 30);
			this->btnRejectReader->Text = L"Bloklash";
			this->btnRejectReader->Click += gcnew System::EventHandler(this, &AdminForm::btnRejectReader_Click);

			this->btnPreviewReaderCard->Location = System::Drawing::Point(10, 240);
			this->btnPreviewReaderCard->Size = System::Drawing::Size(200, 32);
			this->btnPreviewReaderCard->Text = L"Karta rasmini ko'rish";
			this->btnPreviewReaderCard->Click += gcnew System::EventHandler(this, &AdminForm::btnPreviewReaderCard_Click);

			this->lblReadersPageTitle->AutoSize = true;
			this->lblReadersPageTitle->Location = System::Drawing::Point(10, 16);
			this->lblReadersPageTitle->Text = L"Kitobxonlar boshqaruvi";

			this->lblReadersPageHint->AutoSize = true;
			this->lblReadersPageHint->Location = System::Drawing::Point(10, 284);
			this->lblReadersPageHint->Text = L"Avval jadvaldan kitobxon tanlang, keyin tasdiqlang yoki bloklang.";

			// tabPageIssues
			this->tabPageIssues->Controls->Add(this->dgvIssues);
			this->tabPageIssues->Controls->Add(this->cmbIssueReader);
			this->tabPageIssues->Controls->Add(this->cmbIssueBook);
			this->tabPageIssues->Controls->Add(this->dtpReturnDate);
			this->tabPageIssues->Controls->Add(this->btnIssueBook);
			this->tabPageIssues->Controls->Add(this->btnReturnBook);
			this->tabPageIssues->Location = System::Drawing::Point(4, 25);
			this->tabPageIssues->Name = L"tabPageIssues";
			this->tabPageIssues->Padding = System::Windows::Forms::Padding(3);
			this->tabPageIssues->Size = System::Drawing::Size(792, 471);
			this->tabPageIssues->Text = L"Qarzlar (Ijaralar)";
			this->tabPageIssues->UseVisualStyleBackColor = true;

			this->dgvIssues->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvIssues->Location = System::Drawing::Point(250, 20);
			this->dgvIssues->Name = L"dgvIssues";
			this->dgvIssues->Size = System::Drawing::Size(520, 430);
			this->dgvIssues->ColumnCount = 5;
			this->dgvIssues->Columns[0]->Name = L"Kitobxon";
			this->dgvIssues->Columns[1]->Name = L"Kitob";
			this->dgvIssues->Columns[2]->Name = L"Olingan";
			this->dgvIssues->Columns[3]->Name = L"Qaytarish muddati";
			this->dgvIssues->Columns[4]->Name = L"ID";
			this->dgvIssues->Columns[4]->Visible = false;

			this->cmbIssueReader->Location = System::Drawing::Point(10, 40);
			this->cmbIssueReader->Size = System::Drawing::Size(200, 22);

			this->cmbIssueBook->Location = System::Drawing::Point(10, 80);
			this->cmbIssueBook->Size = System::Drawing::Size(200, 22);

			this->dtpReturnDate->Location = System::Drawing::Point(10, 120);
			this->dtpReturnDate->Size = System::Drawing::Size(200, 22);

			this->btnIssueBook->Location = System::Drawing::Point(10, 160);
			this->btnIssueBook->Size = System::Drawing::Size(90, 30);
			this->btnIssueBook->Text = L"Berish";
			this->btnIssueBook->Click += gcnew System::EventHandler(this, &AdminForm::btnIssueBook_Click);

			this->btnReturnBook->Location = System::Drawing::Point(120, 160);
			this->btnReturnBook->Size = System::Drawing::Size(110, 30);
			this->btnReturnBook->Text = L"Qaytarib Olish";
			this->btnReturnBook->Click += gcnew System::EventHandler(this, &AdminForm::btnReturnBook_Click);

			// tabPageInsights
			this->tabPageInsights->Controls->Add(this->dgvDemand);
			this->tabPageInsights->Controls->Add(this->pnlCardTotal);
			this->tabPageInsights->Controls->Add(this->pnlCardTop);
			this->tabPageInsights->Controls->Add(this->pnlCardReaders);
			this->tabPageInsights->Controls->Add(this->pnlDonutChart);
			this->tabPageInsights->Location = System::Drawing::Point(4, 25);
			this->tabPageInsights->Name = L"tabPageInsights";
			this->tabPageInsights->Padding = System::Windows::Forms::Padding(3);
			this->tabPageInsights->Size = System::Drawing::Size(792, 471);
			this->tabPageInsights->Text = L"Smart Dashboard";
			this->tabPageInsights->UseVisualStyleBackColor = true;

			// Card 1: Jami ijaralar
			this->pnlCardTotal->Location = System::Drawing::Point(20, 15);
			this->pnlCardTotal->Size = System::Drawing::Size(230, 85);
			this->pnlCardTotal->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
			this->pnlCardTotal->Controls->Add(this->lblTotalTitle);
			this->pnlCardTotal->Controls->Add(this->lblTotalValue);

			this->lblTotalTitle->AutoSize = true;
			this->lblTotalTitle->Location = System::Drawing::Point(16, 12);
			this->lblTotalTitle->Text = L"Jami ijaralar";
			this->lblTotalTitle->ForeColor = System::Drawing::Color::White;

			this->lblTotalValue->AutoSize = true;
			this->lblTotalValue->Location = System::Drawing::Point(16, 40);
			this->lblTotalValue->Text = L"0";
			this->lblTotalValue->ForeColor = System::Drawing::Color::White;
			this->lblTotalValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18.0F, System::Drawing::FontStyle::Bold));

			// Card 2: Top kitob
			this->pnlCardTop->Location = System::Drawing::Point(270, 15);
			this->pnlCardTop->Size = System::Drawing::Size(280, 85);
			this->pnlCardTop->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);
			this->pnlCardTop->Controls->Add(this->lblTopTitle);
			this->pnlCardTop->Controls->Add(this->lblTopValue);

			this->lblTopTitle->AutoSize = true;
			this->lblTopTitle->Location = System::Drawing::Point(16, 12);
			this->lblTopTitle->Text = L"Top kitob";
			this->lblTopTitle->ForeColor = System::Drawing::Color::White;

			this->lblTopValue->AutoSize = false;
			this->lblTopValue->Location = System::Drawing::Point(16, 40);
			this->lblTopValue->Size = System::Drawing::Size(250, 38);
			this->lblTopValue->Text = L"-";
			this->lblTopValue->ForeColor = System::Drawing::Color::White;
			this->lblTopValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Bold));

			// Card 3: Kitobxonlar soni
			this->pnlCardReaders->Location = System::Drawing::Point(570, 15);
			this->pnlCardReaders->Size = System::Drawing::Size(200, 85);
			this->pnlCardReaders->BackColor = System::Drawing::Color::FromArgb(46, 204, 113);
			this->pnlCardReaders->Controls->Add(this->lblReadersTitle);
			this->pnlCardReaders->Controls->Add(this->lblReadersValue);

			this->lblReadersTitle->AutoSize = true;
			this->lblReadersTitle->Location = System::Drawing::Point(16, 12);
			this->lblReadersTitle->Text = L"Kitobxonlar";
			this->lblReadersTitle->ForeColor = System::Drawing::Color::White;
			this->lblReadersTitle->BackColor = System::Drawing::Color::Transparent;

			this->lblReadersValue->AutoSize = true;
			this->lblReadersValue->Location = System::Drawing::Point(16, 40);
			this->lblReadersValue->Text = L"0";
			this->lblReadersValue->ForeColor = System::Drawing::Color::White;
			this->lblReadersValue->BackColor = System::Drawing::Color::Transparent;
			this->lblReadersValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18.0F, System::Drawing::FontStyle::Bold));

			// Donut Chart panel
			this->pnlDonutChart->Location = System::Drawing::Point(20, 110);
			this->pnlDonutChart->Size = System::Drawing::Size(250, 250);
			this->pnlDonutChart->BackColor = System::Drawing::Color::White;
			this->pnlDonutChart->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DonutChart_Paint);

			// Demand jadval — donut yonida
			this->dgvDemand->Location = System::Drawing::Point(280, 110);
			this->dgvDemand->Size = System::Drawing::Size(490, 340);
			this->dgvDemand->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvDemand->ColumnCount = 3;
			this->dgvDemand->Columns[0]->Name = L"#";
			this->dgvDemand->Columns[1]->Name = L"Kitob";
			this->dgvDemand->Columns[2]->Name = L"Demand score";

			// 
			// AdminForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 500);
			this->Controls->Add(this->tabControl1);
			this->Name = L"AdminForm";
			this->Text = L"Admin Panel";
			this->tabControl1->ResumeLayout(false);
			this->tabPageBooks->ResumeLayout(false);
			this->tabPageBooks->PerformLayout();
			this->tabPageLibraries->ResumeLayout(false);
			this->tabPageLibraries->PerformLayout();
			this->tabPageSections->ResumeLayout(false);
			this->tabPageSections->PerformLayout();
			this->tabPageReaders->ResumeLayout(false);
			this->tabPageReaders->PerformLayout();
			this->tabPageIssues->ResumeLayout(false);
			this->tabPageIssues->PerformLayout();
           this->tabPageInsights->ResumeLayout(false);
			this->tabPageInsights->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvBooks))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvLibraries))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSections))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReaders))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvIssues))->EndInit();
          (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvDemand))->EndInit();
			this->ResumeLayout(false);

			// Load initial data
			LoadData();
		}
#pragma endregion

	private: System::Void ApplyModernStyle() {
		this->BackColor = System::Drawing::Color::White;
		this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

		// TabControl dizayni
		tabControl1->ItemSize = System::Drawing::Size(130, 40);
		tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
		tabPageBooks->BackColor = System::Drawing::Color::White;
		tabPageLibraries->BackColor = System::Drawing::Color::White;
		tabPageSections->BackColor = System::Drawing::Color::White;
		tabPageReaders->BackColor = System::Drawing::Color::White;
		tabPageIssues->BackColor = System::Drawing::Color::White;
		tabPageInsights->BackColor = System::Drawing::Color::White;

		// Tugmalar (Buttons)
     array<Button^>^ buttons = { btnAddBook, btnEditBook, btnAddLibrary, btnAddSection, btnDeleteBook, btnDeleteLibrary, btnDeleteSection, btnSelectImage, btnSelectEbook, btnAddReader, btnDeleteReader, btnApproveReader, btnRejectReader, btnIssueBook, btnReturnBook };
		for each (Button^ btn in buttons) {
			btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold));
			btn->ForeColor = System::Drawing::Color::White;
			btn->Cursor = System::Windows::Forms::Cursors::Hand;
			btn->Height = 35;
		}

		// Qo'shish va O'chirish ranglari
		btnAddBook->BackColor = System::Drawing::Color::FromArgb(40, 167, 69);
		btnAddLibrary->BackColor = System::Drawing::Color::FromArgb(40, 167, 69);
		btnAddSection->BackColor = System::Drawing::Color::FromArgb(40, 167, 69);
		btnAddReader->BackColor = System::Drawing::Color::FromArgb(40, 167, 69);
		btnIssueBook->BackColor = System::Drawing::Color::FromArgb(23, 162, 184);

		btnEditBook->BackColor = System::Drawing::Color::FromArgb(255, 193, 7);

		btnDeleteBook->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnDeleteLibrary->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnDeleteSection->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnDeleteReader->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnApproveReader->BackColor = System::Drawing::Color::FromArgb(40, 167, 69);
		btnRejectReader->BackColor = System::Drawing::Color::FromArgb(220, 53, 69);
		btnReturnBook->BackColor = System::Drawing::Color::FromArgb(255, 193, 7);

		if (lblReadersPageTitle != nullptr) {
			lblReadersPageTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12.0F, System::Drawing::FontStyle::Bold);
			lblReadersPageTitle->ForeColor = System::Drawing::Color::FromArgb(33, 37, 41);
		}
		if (lblReadersPageHint != nullptr) {
			lblReadersPageHint->ForeColor = System::Drawing::Color::FromArgb(108, 117, 125);
		}

		btnSelectImage->BackColor = System::Drawing::Color::FromArgb(0, 123, 255);
		btnSelectEbook->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);

		// 3D style dashboard cards
		pnlCardTotal->Tag = gcnew cli::array<System::Drawing::Color>(2) { System::Drawing::Color::FromArgb(33, 150, 243), System::Drawing::Color::FromArgb(21, 101, 192) };
		pnlCardTop->Tag = gcnew cli::array<System::Drawing::Color>(2) { System::Drawing::Color::FromArgb(111, 66, 193), System::Drawing::Color::FromArgb(81, 45, 168) };
		pnlCardReaders->Tag = gcnew cli::array<System::Drawing::Color>(2) { System::Drawing::Color::FromArgb(46, 204, 113), System::Drawing::Color::FromArgb(39, 174, 96) };
		pnlCardTotal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DashboardCard_Paint);
		pnlCardTop->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DashboardCard_Paint);
		pnlCardReaders->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DashboardCard_Paint);
		pnlCardTotal->MouseEnter += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseEnter);
		pnlCardTotal->MouseLeave += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseLeave);
		pnlCardTop->MouseEnter += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseEnter);
		pnlCardTop->MouseLeave += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseLeave);
		pnlCardReaders->MouseEnter += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseEnter);
		pnlCardReaders->MouseLeave += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseLeave);
		lblTotalTitle->BackColor = System::Drawing::Color::Transparent;
		lblTotalValue->BackColor = System::Drawing::Color::Transparent;
		lblTopTitle->BackColor = System::Drawing::Color::Transparent;
		lblTopValue->BackColor = System::Drawing::Color::Transparent;

		// Placeholder tizimi — GotFocus/LostFocus orqali
		Color placeholderColor = System::Drawing::Color::FromArgb(160, 160, 160);
		txtReaderName->Text = L"F.I.Sh kiriting";
		txtReaderName->ForeColor = placeholderColor;
		txtReaderName->Tag = L"F.I.Sh kiriting";
		txtReaderName->GotFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_GotFocus);
		txtReaderName->LostFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_LostFocus);

		txtReaderPhone->Text = L"Telefon (masalan +9989X)";
		txtReaderPhone->ForeColor = placeholderColor;
		txtReaderPhone->Tag = L"Telefon (masalan +9989X)";
		txtReaderPhone->GotFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_GotFocus);
		txtReaderPhone->LostFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_LostFocus);

		txtReaderID->Text = L"Pasport yoki ID";
		txtReaderID->ForeColor = placeholderColor;
		txtReaderID->Tag = L"Pasport yoki ID";
		txtReaderID->GotFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_GotFocus);
		txtReaderID->LostFocus += gcnew System::EventHandler(this, &AdminForm::Placeholder_LostFocus);

		// Vidjetlar dizayni
		array<Control^>^ inputs = { txtBookName, cmbBookLibrary, cmbBookSection, txtBookShelf, txtBookRow, txtLibraryName, txtLibraryLat, txtLibraryLon, txtSectionName, txtReaderName, txtReaderPhone, txtReaderID, cmbIssueReader, cmbIssueBook, dtpReturnDate };
		for each (Control^ ctrl in inputs) {
			if (ctrl->GetType() == TextBox::typeid) {
				(safe_cast<TextBox^>(ctrl))->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			}
			ctrl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.0F));
			ctrl->Height = 30;
		}

		// Jadvallar (DataGridView) dizayni
        array<DataGridView^>^ dgvs = { dgvBooks, dgvLibraries, dgvSections, dgvReaders, dgvIssues, dgvDemand };
		for each (DataGridView^ dgv in dgvs) {
			dgv->BackgroundColor = System::Drawing::Color::White;
			dgv->BorderStyle = System::Windows::Forms::BorderStyle::None;
			dgv->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			dgv->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::FromArgb(238, 245, 255);
			dgv->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dgv->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F));
			dgv->RowHeadersVisible = false;
			dgv->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			dgv->EnableHeadersVisualStyles = false;
			dgv->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
			dgv->ColumnHeadersDefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0F, System::Drawing::FontStyle::Bold));
			dgv->ColumnHeadersHeight = 40;
			dgv->RowTemplate->Height = 35;
			dgv->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
		}

		UpdateBooksTabLayout();
		UpdateReadersTabLayout();
		UpdateIssuesTabLayout();
	}

	private: System::Void UpdateBooksTabLayout() {
		if (tabPageBooks == nullptr || dgvBooks == nullptr) return;

		int tabW = tabPageBooks->ClientSize.Width;
		int tabH = tabPageBooks->ClientSize.Height;
		int margin = 14;
		int leftW = Math::Max(250, Math::Min(320, tabW / 3));
		if (tabW < 900) leftW = 240;

		int inputW = leftW - (margin * 2);
		int y = margin;

		if (lblBookName != nullptr) lblBookName->Location = System::Drawing::Point(margin, y);
		y += 18;
		if (txtBookName != nullptr) { txtBookName->Location = System::Drawing::Point(margin, y); txtBookName->Size = System::Drawing::Size(inputW, 30); }

		y += 42;
		if (lblBookLibrary != nullptr) lblBookLibrary->Location = System::Drawing::Point(margin, y);
		y += 18;
		if (cmbBookLibrary != nullptr) { cmbBookLibrary->Location = System::Drawing::Point(margin, y); cmbBookLibrary->Size = System::Drawing::Size(inputW, 30); }

		y += 42;
		if (lblBookSection != nullptr) lblBookSection->Location = System::Drawing::Point(margin, y);
		y += 18;
		if (cmbBookSection != nullptr) { cmbBookSection->Location = System::Drawing::Point(margin, y); cmbBookSection->Size = System::Drawing::Size(inputW, 30); }

		y += 42;
		if (lblBookShelf != nullptr) lblBookShelf->Location = System::Drawing::Point(margin, y);
		y += 18;
		if (txtBookShelf != nullptr) { txtBookShelf->Location = System::Drawing::Point(margin, y); txtBookShelf->Size = System::Drawing::Size(inputW, 30); }

		y += 42;
		if (lblBookRow != nullptr) lblBookRow->Location = System::Drawing::Point(margin, y);
		y += 18;
		if (txtBookRow != nullptr) { txtBookRow->Location = System::Drawing::Point(margin, y); txtBookRow->Size = System::Drawing::Size(inputW, 30); }

		y += 44;
		if (btnSelectImage != nullptr) { btnSelectImage->Location = System::Drawing::Point(margin, y); btnSelectImage->Size = System::Drawing::Size(100, 32); }
		if (lblImagePath != nullptr) { lblImagePath->Location = System::Drawing::Point(margin + 108, y + 8); lblImagePath->Size = System::Drawing::Size(inputW - 112, 22); }

		y += 38;
		if (btnSelectEbook != nullptr) { btnSelectEbook->Location = System::Drawing::Point(margin, y); btnSelectEbook->Size = System::Drawing::Size(100, 32); }
		if (lblEbookPath != nullptr) { lblEbookPath->Location = System::Drawing::Point(margin + 108, y + 8); lblEbookPath->Size = System::Drawing::Size(inputW - 112, 22); }

		y += 46;
		int btnW = Math::Max(78, (inputW - 12) / 2);
		if (btnAddBook != nullptr) { btnAddBook->Location = System::Drawing::Point(margin, y); btnAddBook->Size = System::Drawing::Size(btnW, 34); }
		if (btnEditBook != nullptr) { btnEditBook->Location = System::Drawing::Point(margin + btnW + 12, y); btnEditBook->Size = System::Drawing::Size(btnW, 34); }
		y += 42;
		if (btnDeleteBook != nullptr) { btnDeleteBook->Location = System::Drawing::Point(margin, y); btnDeleteBook->Size = System::Drawing::Size(inputW, 34); }

		int gridX = leftW;
		int gridY = margin;
		int gridW = Math::Max(420, tabW - gridX - margin);
		int gridH = Math::Max(280, tabH - (margin * 2));
		dgvBooks->Location = System::Drawing::Point(gridX, gridY);
		dgvBooks->Size = System::Drawing::Size(gridW, gridH);
	}

	private: System::Void UpdateReadersTabLayout() {
		if (tabPageReaders == nullptr || dgvReaders == nullptr) return;

		int tabW = tabPageReaders->ClientSize.Width;
		int tabH = tabPageReaders->ClientSize.Height;
		int margin = 14;
		int leftW = Math::Max(230, Math::Min(300, tabW / 3));
		if (tabW < 760) leftW = 220;

		if (lblReadersPageTitle != nullptr) lblReadersPageTitle->Location = System::Drawing::Point(margin, margin);
		if (txtReaderName != nullptr) txtReaderName->Location = System::Drawing::Point(margin, 56);
		if (txtReaderPhone != nullptr) txtReaderPhone->Location = System::Drawing::Point(margin, 98);
		if (txtReaderID != nullptr) txtReaderID->Location = System::Drawing::Point(margin, 140);

		if (txtReaderName != nullptr) txtReaderName->Size = System::Drawing::Size(leftW - (margin * 2), 30);
		if (txtReaderPhone != nullptr) txtReaderPhone->Size = System::Drawing::Size(leftW - (margin * 2), 30);
		if (txtReaderID != nullptr) txtReaderID->Size = System::Drawing::Size(leftW - (margin * 2), 30);

		if (btnAddReader != nullptr) { btnAddReader->Location = System::Drawing::Point(margin, 190); btnAddReader->Size = System::Drawing::Size(110, 34); }
		if (btnDeleteReader != nullptr) { btnDeleteReader->Location = System::Drawing::Point(margin + 120, 190); btnDeleteReader->Size = System::Drawing::Size(110, 34); }
		if (btnApproveReader != nullptr) { btnApproveReader->Location = System::Drawing::Point(margin, 232); btnApproveReader->Size = System::Drawing::Size(110, 34); }
		if (btnRejectReader != nullptr) { btnRejectReader->Location = System::Drawing::Point(margin + 120, 232); btnRejectReader->Size = System::Drawing::Size(110, 34); }
		if (btnPreviewReaderCard != nullptr) { btnPreviewReaderCard->Location = System::Drawing::Point(margin, 274); btnPreviewReaderCard->Size = System::Drawing::Size(Math::Max(170, leftW - (margin * 2)), 34); }

		if (lblReadersPageHint != nullptr) lblReadersPageHint->Location = System::Drawing::Point(margin, 316);

		int gridX = leftW;
		int gridY = margin;
		int gridW = Math::Max(360, tabW - gridX - margin);
		int gridH = Math::Max(250, tabH - (margin * 2));
		dgvReaders->Location = System::Drawing::Point(gridX, gridY);
		dgvReaders->Size = System::Drawing::Size(gridW, gridH);
	}

	private: System::Void UpdateIssuesTabLayout() {
		if (tabPageIssues == nullptr || dgvIssues == nullptr) return;

		int tabW = tabPageIssues->ClientSize.Width;
		int tabH = tabPageIssues->ClientSize.Height;
		int margin = 14;
		int leftW = Math::Max(240, Math::Min(300, tabW / 3));
		if (tabW < 860) leftW = 230;

		int inputW = leftW - (margin * 2);
		if (cmbIssueReader != nullptr) { cmbIssueReader->Location = System::Drawing::Point(margin, 48); cmbIssueReader->Size = System::Drawing::Size(inputW, 30); }
		if (cmbIssueBook != nullptr) { cmbIssueBook->Location = System::Drawing::Point(margin, 94); cmbIssueBook->Size = System::Drawing::Size(inputW, 30); }
		if (dtpReturnDate != nullptr) { dtpReturnDate->Location = System::Drawing::Point(margin, 140); dtpReturnDate->Size = System::Drawing::Size(inputW, 30); }

		if (btnIssueBook != nullptr) { btnIssueBook->Location = System::Drawing::Point(margin, 188); btnIssueBook->Size = System::Drawing::Size(110, 34); }
		if (btnReturnBook != nullptr) { btnReturnBook->Location = System::Drawing::Point(margin + 120, 188); btnReturnBook->Size = System::Drawing::Size(110, 34); }

		int gridX = leftW;
		int gridY = margin;
		int gridW = Math::Max(380, tabW - gridX - margin);
		int gridH = Math::Max(250, tabH - (margin * 2));
		dgvIssues->Location = System::Drawing::Point(gridX, gridY);
		dgvIssues->Size = System::Drawing::Size(gridW, gridH);
	}

	private: System::Void AdminForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		UpdateBooksTabLayout();
		UpdateReadersTabLayout();
		UpdateIssuesTabLayout();
	}

	private: System::Void btnApproveReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvReaders->SelectedRows->Count <= 0) {
			MessageBox::Show(L"Tasdiqlash uchun kitobxonni tanlang!");
			return;
		}

		try {
			DataGridViewRow^ row = dgvReaders->SelectedRows[0];
			String^ idStr = row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : "";
			if (String::IsNullOrWhiteSpace(idStr)) return;

			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			client->UploadString(apiUrl + "readers/" + idStr + "/", "PATCH", "{\"is_approved\":true,\"is_active\":true}");

			row->Cells[3]->Value = L"Tasdiqlangan";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Tasdiqlashda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnPreviewReaderCard_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvReaders->SelectedRows->Count <= 0) {
			MessageBox::Show(L"Karta ko'rish uchun kitobxonni tanlang!");
			return;
		}

		try {
			DataGridViewRow^ row = dgvReaders->SelectedRows[0];
			String^ cardImageUrl = row->Cells[5]->Value != nullptr ? row->Cells[5]->Value->ToString() : "";
			if (String::IsNullOrWhiteSpace(cardImageUrl) || cardImageUrl == "null") {
				MessageBox::Show(L"Bu kitobxon uchun karta rasmi topilmadi.");
				return;
			}

			if (!cardImageUrl->StartsWith(L"http")) {
				cardImageUrl = serverUrl + (cardImageUrl->StartsWith(L"/") ? cardImageUrl : (L"/" + cardImageUrl));
			}

			WebClient^ imgCl = gcnew WebClient();
			array<Byte>^ data = imgCl->DownloadData(cardImageUrl);
			MemoryStream^ ms = gcnew MemoryStream(data);
			Image^ cardImg = Image::FromStream(ms);

			Form^ preview = gcnew Form();
			preview->Text = L"Reader card preview";
			preview->Size = System::Drawing::Size(520, 680);
			preview->StartPosition = FormStartPosition::CenterParent;
			preview->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

			PictureBox^ pb = gcnew PictureBox();
			pb->Dock = DockStyle::Fill;
			pb->SizeMode = PictureBoxSizeMode::Zoom;
			pb->Image = cardImg;
			preview->Controls->Add(pb);

			preview->ShowDialog();
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Karta rasmini ochishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnRejectReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvReaders->SelectedRows->Count <= 0) {
			MessageBox::Show(L"Bloklash uchun kitobxonni tanlang!");
			return;
		}

		try {
			DataGridViewRow^ row = dgvReaders->SelectedRows[0];
			String^ idStr = row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : "";
			if (String::IsNullOrWhiteSpace(idStr)) return;

			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			client->UploadString(apiUrl + "readers/" + idStr + "/", "PATCH", "{\"is_approved\":false,\"is_active\":false}");

			row->Cells[3]->Value = L"Bloklangan";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Bloklashda xatolik: " + ex->Message);
		}
	}

	private: System::Void SaveData() {
		// Barcha ma'lumotlar to'g'ridan-to'g'ri API orqali saqlanadi.
		// Bu funksiya eski fayl-asosli saqlanishdan qoldi — endi zarur emas.
	}


	private: System::Void LoadData() {
		dgvBooks->Rows->Clear();
		dgvLibraries->Rows->Clear();
		dgvSections->Rows->Clear();
		dgvReaders->Rows->Clear();
		dgvIssues->Rows->Clear();
		cmbBookLibrary->Items->Clear();
		cmbBookSection->Items->Clear();
		cmbIssueReader->Items->Clear();
		cmbIssueBook->Items->Clear();

		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;

			// Load Libraries
			libIds->Clear();
			String^ libJson = client->DownloadString(apiUrl + "libraries/");
			MatchCollection^ libMatches = Regex::Matches(libJson, "\\{[^{}]+\\}");
			for each(Match^ m in libMatches) {
				String^ obj = m->Value;
				int id = Int32::Parse(Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value);
				String^ name = Regex::Match(obj, "\"name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ lat = Regex::Match(obj, "\"latitude\":([\\d\\.]+)")->Groups[1]->Value;
				String^ lon = Regex::Match(obj, "\"longitude\":([\\d\\.]+)")->Groups[1]->Value;
				dgvLibraries->Rows->Add(name, lat, lon);
				cmbBookLibrary->Items->Add(name);
				libIds[name] = id;
			}

			// Load Sections
			secIds->Clear();
			String^ secJson = client->DownloadString(apiUrl + "sections/");
			MatchCollection^ secMatches = Regex::Matches(secJson, "\\{[^{}]+\\}");
			for each(Match^ m in secMatches) {
				String^ obj = m->Value;
				int id = Int32::Parse(Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value);
				String^ name = Regex::Match(obj, "\"name\":\"([^\"]+)\"")->Groups[1]->Value;
				dgvSections->Rows->Add(name);
				cmbBookSection->Items->Add(name);
				secIds[name] = id;
			}

			// Load Books
			bookIds->Clear();
			String^ bookJson = client->DownloadString(apiUrl + "books/");
			MatchCollection^ bookMatches = Regex::Matches(bookJson, "\\{[^{}]+\\}");
			for each(Match^ m in bookMatches) {
				String^ obj = m->Value;
				int id = Int32::Parse(Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value);
				String^ title = Regex::Match(obj, "\"title\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ libName = Regex::Match(obj, "\"library_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ secName = Regex::Match(obj, "\"section_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ shelf = Regex::Match(obj, "\"shelf\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ row = Regex::Match(obj, "\"row\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ img = Regex::Match(obj, "\"cover_image\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ ebook = Regex::Match(obj, "\"ebook_file\":\"([^\"]+)\"")->Groups[1]->Value;

				if (img != "null" && !img->StartsWith(L"http")) img = serverUrl + (img->StartsWith(L"/") ? img : (L"/" + img));
				if (ebook != "null" && !ebook->StartsWith(L"http")) ebook = serverUrl + (ebook->StartsWith(L"/") ? ebook : (L"/" + ebook));

				dgvBooks->Rows->Add(title, libName, secName, shelf, row, (img == "null" ? "" : img), (ebook == "null" ? "" : ebook), id.ToString());
				cmbIssueBook->Items->Add(title);
				bookIds[title] = id;
			}

			// Load Readers from API
			readerIds->Clear();
			String^ readJson = client->DownloadString(apiUrl + "readers/");
			MatchCollection^ readMatches = Regex::Matches(readJson, "\\{[^{}]+\\}");
			for each(Match^ m in readMatches) {
				String^ obj = m->Value;
				int id = Int32::Parse(Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value);
				String^ fullname = Regex::Match(obj, "\"fullname\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ phone = Regex::Match(obj, "\"phone\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ cardId = Regex::Match(obj, "\"card_id\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ cardImage = Regex::Match(obj, "\"card_image\":\"([^\"]*)\"")->Groups[1]->Value;
				String^ approvedText = Regex::Match(obj, "\"is_approved\":(true|false)", RegexOptions::IgnoreCase)->Groups[1]->Value;
				bool isApproved = approvedText->ToLower() == "true";
				String^ statusText = isApproved ? L"Tasdiqlangan" : L"Kutilmoqda";
				dgvReaders->Rows->Add(fullname, phone, cardId, statusText, id.ToString(), cardImage);
				cmbIssueReader->Items->Add(fullname);
				readerIds[fullname] = id;
			}

			// Load Issues from API
			String^ issueJson = client->DownloadString(apiUrl + "issues/");
			MatchCollection^ issueMatches = Regex::Matches(issueJson, "\\{[^{}]+\\}");
			for each(Match^ m in issueMatches) {
				String^ obj = m->Value;
				int id = Int32::Parse(Regex::Match(obj, "\"id\":(\\d+)")->Groups[1]->Value);
				String^ readerName = Regex::Match(obj, "\"reader_name\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ bookTitle = Regex::Match(obj, "\"book_title\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ issueDate = Regex::Match(obj, "\"issue_date\":\"([^\"]+)\"")->Groups[1]->Value;
				String^ returnDate = Regex::Match(obj, "\"return_date\":\"([^\"]+)\"")->Groups[1]->Value;
				int rowIdx = dgvIssues->Rows->Add(readerName, bookTitle, issueDate, returnDate, id.ToString());
				try {
					DateTime dt = DateTime::Parse(returnDate);
					if (DateTime::Now > dt) {
						dgvIssues->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 200, 200);
					}
				} catch (...) {}
			}

		} catch (Exception^ ex) {
			MessageBox::Show(L"API dan ma'lumot yuklab bo'lmadi: " + ex->Message + L"\nServer ishlab turganligini tekshiring.");
		}

		if (cmbBookLibrary->Items->Count > 0) cmbBookLibrary->SelectedIndex = 0;
		if (cmbBookSection->Items->Count > 0) cmbBookSection->SelectedIndex = 0;
		if (cmbIssueReader->Items->Count > 0) cmbIssueReader->SelectedIndex = 0;
		if (cmbIssueBook->Items->Count > 0) cmbIssueBook->SelectedIndex = 0;
       LoadInsights();
	}

	private: System::Void LoadInsights() {
		dgvDemand->Rows->Clear();
		System::Collections::Generic::Dictionary<String^, double>^ scoreMap = gcnew System::Collections::Generic::Dictionary<String^, double>();
		int totalIssues = 0;

		// API dan yuklangan dgvIssues jadvalidan hisoblash
		for (int i = 0; i < dgvIssues->Rows->Count; i++) {
			DataGridViewRow^ r = dgvIssues->Rows[i];
			if (r->Cells[1]->Value == nullptr) continue;

			String^ book = r->Cells[1]->Value->ToString();
			double recencyBonus = 0.0;
			try {
				String^ issueDateStr = r->Cells[2]->Value != nullptr ? r->Cells[2]->Value->ToString() : "";
				if (!String::IsNullOrEmpty(issueDateStr)) {
					DateTime issueDate = DateTime::Parse(issueDateStr);
					double days = (DateTime::Now - issueDate).TotalDays;
					recencyBonus = Math::Max(0.0, (30.0 - days) / 30.0);
				}
			}
			catch (...) {}

			double score = 1.0 + recencyBonus;
			if (!scoreMap->ContainsKey(book)) scoreMap->Add(book, 0.0);
			scoreMap[book] += score;
			totalIssues++;
		}

       targetTotalIssues = totalIssues;
		displayedTotalIssues = 0;
		lblTotalValue->Text = L"0";
		lblReadersValue->Text = dgvReaders->Rows->Count.ToString();

		System::Collections::Generic::List<array<Object^>^>^ rows = gcnew System::Collections::Generic::List<array<Object^>^>();
		for each (System::Collections::Generic::KeyValuePair<String^, double> kv in scoreMap) {
			array<Object^>^ r = gcnew array<Object^>(2);
			r[0] = kv.Key;
			r[1] = kv.Value;
			rows->Add(r);
		}

     rows->Sort(gcnew Comparison<array<Object^>^>(this, &AdminForm::CompareDemandRows));

        array<Object^>^ topRow = rows->Count > 0 ? rows->default[0] : nullptr;
		String^ topBook = topRow != nullptr ? topRow[0]->ToString() : L"-";
		String^ topScore = topRow != nullptr ? safe_cast<double>(topRow[1]).ToString("F2") : L"0.00";
		lblTopValue->Text = topBook + L" (" + topScore + L")";

		// Donut chart ma'lumotlarini to'ldirish
		chartScores->Clear();
		chartLabels->Clear();
		chartColors->Clear();
		cli::array<System::Drawing::Color>^ palette = {
			System::Drawing::Color::FromArgb(255, 99, 132),
			System::Drawing::Color::FromArgb(54, 162, 235),
			System::Drawing::Color::FromArgb(255, 206, 86),
			System::Drawing::Color::FromArgb(75, 192, 192),
			System::Drawing::Color::FromArgb(153, 102, 255),
			System::Drawing::Color::FromArgb(255, 159, 64),
			System::Drawing::Color::FromArgb(46, 204, 113),
			System::Drawing::Color::FromArgb(231, 76, 60),
			System::Drawing::Color::FromArgb(52, 152, 219),
			System::Drawing::Color::FromArgb(241, 196, 15)
		};

		int limit = Math::Min(10, rows->Count);
		for (int i = 0; i < limit; i++) {
          array<Object^>^ item = rows->default[i];
			String^ book = item[0]->ToString();
			double score = safe_cast<double>(item[1]);
			chartScores->Add(score);
			chartLabels->Add(book);
			chartColors->Add(palette[i % palette->Length]);

			int rowIdx = dgvDemand->Rows->Add((i + 1).ToString(), book, score.ToString("F2"));
			if (score >= 3.0) dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 235, 238);
			else if (score >= 2.0) dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 248, 225);
			else dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(232, 245, 233);
		}

		// Donut chartni yangila
		if (pnlDonutChart != nullptr) pnlDonutChart->Invalidate();

		insightsAnimTimer->Stop();
		insightsAnimTimer->Start();
	}

	private: System::Void insightsAnimTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (displayedTotalIssues < targetTotalIssues) {
			displayedTotalIssues += Math::Max(1, (targetTotalIssues - displayedTotalIssues) / 6);
			if (displayedTotalIssues > targetTotalIssues) displayedTotalIssues = targetTotalIssues;
			lblTotalValue->Text = displayedTotalIssues.ToString();
		}
		else {
			insightsAnimTimer->Stop();
		}
	}

	private: System::Void DashboardCard_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Panel^ p = dynamic_cast<Panel^>(sender);
		if (p == nullptr) return;
		cli::array<System::Drawing::Color>^ colors = dynamic_cast<cli::array<System::Drawing::Color>^>(p->Tag);
		if (colors == nullptr || colors->Length < 2) return;

		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		System::Drawing::Rectangle r = p->ClientRectangle;
		r.Inflate(-1, -1);

		System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
		int radius = 16;
		path->AddArc(r.X, r.Y, radius, radius, 180, 90);
		path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
		path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
		path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
		path->CloseFigure();

		System::Drawing::Drawing2D::LinearGradientBrush^ brush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(r, colors[0], colors[1], 45.0f);
		e->Graphics->FillPath(brush, path);
		e->Graphics->DrawPath(gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(70, 255, 255, 255), 1.5f), path);

		delete brush;
		delete path;
	}

	private: System::Void DashboardCard_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		Panel^ p = dynamic_cast<Panel^>(sender);
		if (p != nullptr) p->Top -= 2;
	}

	private: System::Void DashboardCard_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		Panel^ p = dynamic_cast<Panel^>(sender);
		if (p != nullptr) p->Top += 2;
	}

	// Placeholder tizimi — focus bosganida tozalash, chiqsaniz qayta qo'yish
	private: System::Void Placeholder_GotFocus(System::Object^ sender, System::EventArgs^ e) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);
		if (tb != nullptr && tb->Tag != nullptr && tb->Text == tb->Tag->ToString()) {
			tb->Text = L"";
			tb->ForeColor = System::Drawing::Color::Black;
		}
	}

	private: System::Void Placeholder_LostFocus(System::Object^ sender, System::EventArgs^ e) {
		TextBox^ tb = dynamic_cast<TextBox^>(sender);
		if (tb != nullptr && tb->Tag != nullptr && String::IsNullOrWhiteSpace(tb->Text)) {
			tb->Text = tb->Tag->ToString();
			tb->ForeColor = System::Drawing::Color::FromArgb(160, 160, 160);
		}
	}

	// Donut chart chizish
	private: System::Void DonutChart_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Panel^ p = dynamic_cast<Panel^>(sender);
		if (p == nullptr || chartScores == nullptr || chartScores->Count == 0) {
			// Ma'lumot bo'lmasa "Ma'lumot yo'q" yozish
			e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			String^ msg = L"Ma'lumot yo'q";
			System::Drawing::Font^ fnt = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, System::Drawing::FontStyle::Italic);
			System::Drawing::SizeF sz = e->Graphics->MeasureString(msg, fnt);
			e->Graphics->DrawString(msg, fnt, System::Drawing::Brushes::Gray,
				(p->Width - sz.Width) / 2, (p->Height - sz.Height) / 2);
			return;
		}

		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		// Donut o'lchamlari
		int margin = 15;
		int chartSize = Math::Min(p->Width, p->Height) - margin * 2;
		int cx = p->Width / 2;
		int cy = (chartSize / 2) + margin;
		System::Drawing::Rectangle outerRect = System::Drawing::Rectangle(cx - chartSize / 2, cy - chartSize / 2, chartSize, chartSize);
		int innerSize = (int)(chartSize * 0.55);
		System::Drawing::Rectangle innerRect = System::Drawing::Rectangle(cx - innerSize / 2, cy - innerSize / 2, innerSize, innerSize);

		// Jami score
		double total = 0;
		for (int i = 0; i < chartScores->Count; i++) total += chartScores[i];
		if (total <= 0) return;

		// Sektorlar chizish
		float startAngle = -90.0f;
		for (int i = 0; i < chartScores->Count; i++) {
			float sweep = (float)(chartScores[i] / total * 360.0);
			if (sweep < 0.5f) sweep = 0.5f;
			System::Drawing::SolidBrush^ br = gcnew System::Drawing::SolidBrush(chartColors[i]);
			e->Graphics->FillPie(br, outerRect, startAngle, sweep);
			delete br;
			startAngle += sweep;
		}

		// Ichki doira (oq) — donut effekti
		e->Graphics->FillEllipse(System::Drawing::Brushes::White, innerRect);

		// Markaz matni
		System::Drawing::Font^ centerFont = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, System::Drawing::FontStyle::Bold);
		String^ centerText = chartScores->Count.ToString();
		System::Drawing::SizeF csz = e->Graphics->MeasureString(centerText, centerFont);
		e->Graphics->DrawString(centerText, centerFont, gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(40, 44, 52)),
			cx - csz.Width / 2, cy - csz.Height / 2 - 8);

		System::Drawing::Font^ subFont = gcnew System::Drawing::Font(L"Segoe UI", 8.0F, System::Drawing::FontStyle::Regular);
		String^ subText = L"kitob";
		System::Drawing::SizeF ssz = e->Graphics->MeasureString(subText, subFont);
		e->Graphics->DrawString(subText, subFont, System::Drawing::Brushes::Gray,
			cx - ssz.Width / 2, cy + csz.Height / 2 - 12);

		// Legend (donut ostida)
		int ly = cy + chartSize / 2 + 8;
		System::Drawing::Font^ legendFont = gcnew System::Drawing::Font(L"Segoe UI", 7.5F);
		int lx = 5;
		int maxLegends = Math::Min(5, chartLabels->Count);
		for (int i = 0; i < maxLegends; i++) {
			System::Drawing::SolidBrush^ lb = gcnew System::Drawing::SolidBrush(chartColors[i]);
			e->Graphics->FillRectangle(lb, lx, ly, 10, 10);
			delete lb;
			String^ lbl = chartLabels[i];
			if (lbl->Length > 12) lbl = lbl->Substring(0, 10) + L"..";
			e->Graphics->DrawString(lbl, legendFont, System::Drawing::Brushes::Black, (float)(lx + 13), (float)(ly - 2));
			lx += 55;
			if (lx > p->Width - 30) { lx = 5; ly += 16; }
		}
	}

	private: System::Void dgvBooks_SelectionChanged(System::Object^ sender, System::EventArgs^ e) {
		if (dgvBooks->SelectedRows->Count > 0) {
			DataGridViewRow^ row = dgvBooks->SelectedRows[0];
			txtBookName->Text = row->Cells[0]->Value != nullptr ? row->Cells[0]->Value->ToString() : "";
			cmbBookLibrary->Text = row->Cells[1]->Value != nullptr ? row->Cells[1]->Value->ToString() : "";
			cmbBookSection->Text = row->Cells[2]->Value != nullptr ? row->Cells[2]->Value->ToString() : "";
			txtBookShelf->Text = row->Cells[3]->Value != nullptr ? row->Cells[3]->Value->ToString() : "";
			txtBookRow->Text = row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : "";
			selectedImagePath = row->Cells[5]->Value != nullptr ? row->Cells[5]->Value->ToString() : "";
            selectedEbookPath = row->Cells[6]->Value != nullptr ? row->Cells[6]->Value->ToString() : "";
			lblImagePath->Text = String::IsNullOrEmpty(selectedImagePath) ? L"Rasm tanlanmadi" : L"Joriy rasm xotirada";
           lblEbookPath->Text = String::IsNullOrEmpty(selectedEbookPath) ? L"E-kitob tanlanmadi" : L"Joriy e-kitob xotirada";
		}
	}

	private: System::Void btnEditBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvBooks->SelectedRows->Count > 0) {
			if (txtBookName->Text == L"") {
				MessageBox::Show(L"Kitob nomi bo'sh bo'lishi mumkin emas!");
				return;
			}
			try {
				DataGridViewRow^ row = dgvBooks->SelectedRows[0];
				String^ id = row->Cells[7]->Value->ToString();
				int libId = libIds->ContainsKey(cmbBookLibrary->Text) ? libIds[cmbBookLibrary->Text] : 0;
				int secId = secIds->ContainsKey(cmbBookSection->Text) ? secIds[cmbBookSection->Text] : 0;

				WebClient^ client = gcnew WebClient();
				client->Encoding = System::Text::Encoding::UTF8;
				client->Headers[HttpRequestHeader::ContentType] = "application/json";
				String^ json = String::Format("{{\"title\":\"{0}\", \"library\":{1}, \"section\":{2}, \"shelf\":\"{3}\", \"row\":\"{4}\"}}",
					txtBookName->Text, libId, secId, txtBookShelf->Text, txtBookRow->Text);
				client->UploadString(apiUrl + "books/" + id + "/", "PATCH", json);

				// Fayllarni yuklash (agar o'zgargan bo'lsa va lokal bo'lsa)
				if (!String::IsNullOrEmpty(selectedImagePath) && File::Exists(selectedImagePath)) {
					client->UploadFile(apiUrl + "books/" + id + "/upload-cover/", "POST", selectedImagePath);
				}
				if (!String::IsNullOrEmpty(selectedEbookPath) && File::Exists(selectedEbookPath)) {
					client->UploadFile(apiUrl + "books/" + id + "/upload-ebook/", "POST", selectedEbookPath);
				}

				LoadData(); // Ro'yxatni yangilash
				MessageBox::Show(L"Kitob muvaffaqiyatli tahrirlandi!");
			} catch (Exception^ ex) {
				MessageBox::Show(L"Xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"Tahrirlash uchun ro'yxatdan kitob tanlang!");
		}
	}

	private: System::Void btnSelectEbook_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = L"E-kitob fayllari|*.pdf;*.epub;*.mobi";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			selectedEbookPath = ofd->FileName;
			lblEbookPath->Text = L"E-kitob tanlandi: " + Path::GetFileName(selectedEbookPath);
		}
	}

	private: System::Void btnSelectImage_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			selectedImagePath = ofd->FileName;
			lblImagePath->Text = L"Rasm tanlandi: " + Path::GetFileName(selectedImagePath);
		}
	}

	private: System::Void btnAddBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtBookName->Text == L"" || cmbBookLibrary->Text == L"" || cmbBookSection->Text == L"" || txtBookShelf->Text == L"" || txtBookRow->Text == L"") {
			MessageBox::Show(L"Barcha maydonlarni to'ldiring!");
			return;
		}
		
		try {
			int libId = libIds->ContainsKey(cmbBookLibrary->Text) ? libIds[cmbBookLibrary->Text] : 0;
			int secId = secIds->ContainsKey(cmbBookSection->Text) ? secIds[cmbBookSection->Text] : 0;

			if (libId == 0 || secId == 0) {
				MessageBox::Show(L"Kutubxona yoki Bo'lim topilmadi!");
				return;
			}

			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			
			String^ json = String::Format("{{\"title\":\"{0}\", \"library\":{1}, \"section\":{2}, \"shelf\":\"{3}\", \"row\":\"{4}\"}}",
				txtBookName->Text, libId, secId, txtBookShelf->Text, txtBookRow->Text);
			
			String^ response = client->UploadString(apiUrl + "books/", "POST", json);
			
			// Yangi kitob ID sini olish
			int newBookId = Int32::Parse(Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value);

			// Fayllarni yuklash
			if (!String::IsNullOrEmpty(selectedImagePath) && File::Exists(selectedImagePath)) {
				client->UploadFile(apiUrl + "books/" + newBookId + "/upload-cover/", "POST", selectedImagePath);
			}
			if (!String::IsNullOrEmpty(selectedEbookPath) && File::Exists(selectedEbookPath)) {
				client->UploadFile(apiUrl + "books/" + newBookId + "/upload-ebook/", "POST", selectedEbookPath);
			}

			LoadData();
			
			txtBookName->Text = L""; txtBookShelf->Text = L""; txtBookRow->Text = L"";
			selectedImagePath = L"";
			selectedEbookPath = L"";
			lblImagePath->Text = L"Rasm tanlanmadi";
			lblEbookPath->Text = L"E-kitob tanlanmadi";
			MessageBox::Show(L"Kitob muvaffaqiyatli qo'shildi!");
		} catch (Exception^ ex) {
			MessageBox::Show(L"APIga qo'shishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnDeleteBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvBooks->SelectedRows->Count > 0) {
			try {
				DataGridViewRow^ row = dgvBooks->SelectedRows[0];
				String^ id = row->Cells[7]->Value != nullptr ? row->Cells[7]->Value->ToString() : "";
				if (String::IsNullOrEmpty(id)) return;

				WebClient^ client = gcnew WebClient();
				client->UploadString(apiUrl + "books/" + id + "/", "DELETE", "");
				
				dgvBooks->Rows->RemoveAt(row->Index);
			} catch (Exception^ ex) {
				MessageBox::Show(L"API orqali o'chirishda xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnAddLibrary_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtLibraryName->Text == L"") {
			MessageBox::Show(L"Kutubxona nomini kiriting!");
			return;
		}
		String^ lat = txtLibraryLat->Text == L"" ? L"41.3110" : txtLibraryLat->Text;
		String^ lon = txtLibraryLon->Text == L"" ? L"69.2401" : txtLibraryLon->Text;

		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			String^ json = String::Format("{{\"name\":\"{0}\", \"latitude\":{1}, \"longitude\":{2}}}",
				txtLibraryName->Text, lat, lon);
			
			String^ response = client->UploadString(apiUrl + "libraries/", "POST", json);
			int newId = Int32::Parse(Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value);
			
			dgvLibraries->Rows->Add(txtLibraryName->Text, lat, lon);
			cmbBookLibrary->Items->Add(txtLibraryName->Text);
			libIds[txtLibraryName->Text] = newId;

			txtLibraryName->Text = L""; txtLibraryLat->Text = L""; txtLibraryLon->Text = L"";
		} catch (Exception^ ex) {
			MessageBox::Show(L"APIga qo'shishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnDeleteLibrary_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvLibraries->SelectedRows->Count > 0) {
			try {
				DataGridViewRow^ row = dgvLibraries->SelectedRows[0];
				String^ name = row->Cells[0]->Value->ToString();
				if (!libIds->ContainsKey(name)) return;
				
				int id = libIds[name];
				WebClient^ client = gcnew WebClient();
				client->UploadString(apiUrl + "libraries/" + id + "/", "DELETE", "");
				
				dgvLibraries->Rows->RemoveAt(row->Index);
				cmbBookLibrary->Items->Remove(name);
				libIds->Remove(name);
			} catch (Exception^ ex) {
				MessageBox::Show(L"API orqali o'chirishda xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnAddSection_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtSectionName->Text == L"") {
			MessageBox::Show(L"Bo'lim nomini kiriting!");
			return;
		}
		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			String^ json = String::Format("{{\"name\":\"{0}\"}}", txtSectionName->Text);
			
			String^ response = client->UploadString(apiUrl + "sections/", "POST", json);
			int newId = Int32::Parse(Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value);

			dgvSections->Rows->Add(txtSectionName->Text);
			cmbBookSection->Items->Add(txtSectionName->Text);
			secIds[txtSectionName->Text] = newId;

			txtSectionName->Text = L"";
		} catch (Exception^ ex) {
			MessageBox::Show(L"APIga qo'shishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnDeleteSection_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvSections->SelectedRows->Count > 0) {
			try {
				DataGridViewRow^ row = dgvSections->SelectedRows[0];
				String^ name = row->Cells[0]->Value->ToString();
				if (!secIds->ContainsKey(name)) return;
				
				int id = secIds[name];
				WebClient^ client = gcnew WebClient();
				client->UploadString(apiUrl + "sections/" + id + "/", "DELETE", "");
				
				dgvSections->Rows->RemoveAt(row->Index);
				cmbBookSection->Items->Remove(name);
				secIds->Remove(name);
			} catch (Exception^ ex) {
				MessageBox::Show(L"API orqali o'chirishda xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnAddReader_Click(System::Object^ sender, System::EventArgs^ e) {
		// Placeholder textlarni tekshirish
		String^ name = txtReaderName->Text;
		String^ phone = txtReaderPhone->Text;
		String^ cardId = txtReaderID->Text;
		if (name == L"" || phone == L"" || cardId == L""
			|| name == txtReaderName->Tag->ToString()
			|| phone == txtReaderPhone->Tag->ToString()
			|| cardId == txtReaderID->Tag->ToString()) {
			MessageBox::Show(L"Barcha maydonlarni to'ldiring!");
			return;
		}
		try {
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			String^ json = String::Format("{{\"fullname\":\"{0}\",\"phone\":\"{1}\",\"card_id\":\"{2}\"}}",
				name, phone, cardId);
			String^ response = client->UploadString(apiUrl + "readers/", "POST", json);
			int newId = Int32::Parse(Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value);
			dgvReaders->Rows->Add(name, phone, cardId, L"Kutilmoqda", newId.ToString());
			cmbIssueReader->Items->Add(name);
			readerIds[name] = newId;

			// Placeholder larni qayta o'rnatish
			Color placeholderColor = System::Drawing::Color::FromArgb(160, 160, 160);
			txtReaderName->Text = txtReaderName->Tag->ToString();
			txtReaderName->ForeColor = placeholderColor;
			txtReaderPhone->Text = txtReaderPhone->Tag->ToString();
			txtReaderPhone->ForeColor = placeholderColor;
			txtReaderID->Text = txtReaderID->Tag->ToString();
			txtReaderID->ForeColor = placeholderColor;
		} catch (Exception^ ex) {
			MessageBox::Show(L"APIga qo'shishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnDeleteReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvReaders->SelectedRows->Count > 0) {
			try {
				DataGridViewRow^ row = dgvReaders->SelectedRows[0];
				String^ idStr = row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : "";
				if (String::IsNullOrEmpty(idStr)) return;
				int id = Int32::Parse(idStr);
				WebClient^ client = gcnew WebClient();
				client->UploadString(apiUrl + "readers/" + id + "/", "DELETE", "");
				String^ name = row->Cells[0]->Value != nullptr ? row->Cells[0]->Value->ToString() : "";
				dgvReaders->Rows->RemoveAt(row->Index);
				cmbIssueReader->Items->Remove(name);
				if (readerIds->ContainsKey(name)) readerIds->Remove(name);
			} catch (Exception^ ex) {
				MessageBox::Show(L"API orqali o'chirishda xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnIssueBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbIssueReader->Text == L"" || cmbIssueBook->Text == L"") {
			MessageBox::Show(L"Kitobxon va Kitobni tanlang!");
			return;
		}
		if (!readerIds->ContainsKey(cmbIssueReader->Text) || !bookIds->ContainsKey(cmbIssueBook->Text)) {
			MessageBox::Show(L"Kitobxon yoki Kitob APIda topilmadi!");
			return;
		}
		try {
			int readerId = readerIds[cmbIssueReader->Text];
			int bookId = bookIds[cmbIssueBook->Text];
			String^ retDate = dtpReturnDate->Value.ToString("yyyy-MM-dd");
			WebClient^ client = gcnew WebClient();
			client->Encoding = System::Text::Encoding::UTF8;
			client->Headers[HttpRequestHeader::ContentType] = "application/json";
			String^ json = String::Format("{{\"reader\":{0},\"book\":{1},\"return_date\":\"{2}\"}}",
				readerId, bookId, retDate);
			String^ response = client->UploadString(apiUrl + "issues/", "POST", json);
			int newId = Int32::Parse(Regex::Match(response, "\"id\":(\\d+)")->Groups[1]->Value);
			String^ issueDate = Regex::Match(response, "\"issue_date\":\"([^\"]+)\"")->Groups[1]->Value;
			int rowIdx = dgvIssues->Rows->Add(cmbIssueReader->Text, cmbIssueBook->Text, issueDate, retDate, newId.ToString());
			// Muddati tekshirish
			try {
				DateTime dt = DateTime::Parse(retDate);
				if (DateTime::Now > dt) dgvIssues->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 200, 200);
			} catch (...) {}
			LoadInsights();
		} catch (Exception^ ex) {
			MessageBox::Show(L"APIga qo'shishda xatolik: " + ex->Message);
		}
	}

	private: System::Void btnReturnBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvIssues->SelectedRows->Count > 0) {
			try {
				DataGridViewRow^ row = dgvIssues->SelectedRows[0];
				String^ idStr = row->Cells[4]->Value != nullptr ? row->Cells[4]->Value->ToString() : "";
				if (String::IsNullOrEmpty(idStr)) return;
				int id = Int32::Parse(idStr);
				WebClient^ client = gcnew WebClient();
				client->UploadString(apiUrl + "issues/" + id + "/", "DELETE", "");
				dgvIssues->Rows->RemoveAt(row->Index);
				LoadInsights();
			} catch (Exception^ ex) {
				MessageBox::Show(L"API orqali qaytarishda xatolik: " + ex->Message);
			}
		} else {
			MessageBox::Show(L"Qaytarish uchun ro'yxatdan tanlang!");
		}
	}

	private: int CompareDemandRows(array<Object^>^ a, array<Object^>^ b) {
		double sa = safe_cast<double>(a[1]);
		double sb = safe_cast<double>(b[1]);
		return sb.CompareTo(sa);
	}

	};
}
