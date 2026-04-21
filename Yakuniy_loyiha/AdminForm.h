#pragma once

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class AdminForm : public System::Windows::Forms::Form
	{
	public:
		AdminForm(void)
		{
          this->insightsAnimTimer = gcnew System::Windows::Forms::Timer();
			this->insightsAnimTimer->Interval = 30;
			this->insightsAnimTimer->Tick += gcnew System::EventHandler(this, &AdminForm::insightsAnimTimer_Tick);
			InitializeComponent();
			ApplyModernStyle();
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
	private: System::Windows::Forms::Label^ lblTotalTitle;
	private: System::Windows::Forms::Label^ lblTotalValue;
	private: System::Windows::Forms::Label^ lblTopTitle;
	private: System::Windows::Forms::Label^ lblTopValue;
	private: System::Windows::Forms::Timer^ insightsAnimTimer;
	private: int displayedTotalIssues = 0;
	private: int targetTotalIssues = 0;

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

			this->dgvIssues = (gcnew System::Windows::Forms::DataGridView());
			this->cmbIssueReader = (gcnew System::Windows::Forms::ComboBox());
			this->cmbIssueBook = (gcnew System::Windows::Forms::ComboBox());
			this->dtpReturnDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnIssueBook = (gcnew System::Windows::Forms::Button());
			this->btnReturnBook = (gcnew System::Windows::Forms::Button());

			this->dgvDemand = (gcnew System::Windows::Forms::DataGridView());
			this->pnlCardTotal = (gcnew System::Windows::Forms::Panel());
			this->pnlCardTop = (gcnew System::Windows::Forms::Panel());
			this->lblTotalTitle = (gcnew System::Windows::Forms::Label());
			this->lblTotalValue = (gcnew System::Windows::Forms::Label());
			this->lblTopTitle = (gcnew System::Windows::Forms::Label());
			this->lblTopValue = (gcnew System::Windows::Forms::Label());

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
            this->dgvBooks->ColumnCount = 7;
			this->dgvBooks->Columns[0]->Name = L"Nomi";
			this->dgvBooks->Columns[1]->Name = L"Kutubxona";
			this->dgvBooks->Columns[2]->Name = L"Bo'lim";
			this->dgvBooks->Columns[3]->Name = L"Tokcha";
			this->dgvBooks->Columns[4]->Name = L"Qator";
			this->dgvBooks->Columns[5]->Name = L"Rasm (Path)";
			this->dgvBooks->Columns[6]->Name = L"E-kitob (Path)";

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
			this->dgvReaders->ColumnCount = 3;
			this->dgvReaders->Columns[0]->Name = L"F.I.Sh";
			this->dgvReaders->Columns[1]->Name = L"Telefon";
			this->dgvReaders->Columns[2]->Name = L"ID Karta";

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
			this->dgvIssues->ColumnCount = 4;
			this->dgvIssues->Columns[0]->Name = L"Kitobxon";
			this->dgvIssues->Columns[1]->Name = L"Kitob";
			this->dgvIssues->Columns[2]->Name = L"Olingan";
			this->dgvIssues->Columns[3]->Name = L"Qaytarish muddati";

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
			this->tabPageInsights->Location = System::Drawing::Point(4, 25);
			this->tabPageInsights->Name = L"tabPageInsights";
			this->tabPageInsights->Padding = System::Windows::Forms::Padding(3);
			this->tabPageInsights->Size = System::Drawing::Size(792, 471);
			this->tabPageInsights->Text = L"Smart Dashboard";
			this->tabPageInsights->UseVisualStyleBackColor = true;

			this->pnlCardTotal->Location = System::Drawing::Point(20, 20);
			this->pnlCardTotal->Size = System::Drawing::Size(360, 90);
			this->pnlCardTotal->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
			this->pnlCardTotal->Controls->Add(this->lblTotalTitle);
			this->pnlCardTotal->Controls->Add(this->lblTotalValue);

			this->lblTotalTitle->AutoSize = true;
			this->lblTotalTitle->Location = System::Drawing::Point(16, 14);
			this->lblTotalTitle->Text = L"Jami ijaralar";
			this->lblTotalTitle->ForeColor = System::Drawing::Color::White;

			this->lblTotalValue->AutoSize = true;
			this->lblTotalValue->Location = System::Drawing::Point(16, 42);
			this->lblTotalValue->Text = L"0";
			this->lblTotalValue->ForeColor = System::Drawing::Color::White;
			this->lblTotalValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16.0F, System::Drawing::FontStyle::Bold));

			this->pnlCardTop->Location = System::Drawing::Point(410, 20);
			this->pnlCardTop->Size = System::Drawing::Size(360, 90);
			this->pnlCardTop->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);
			this->pnlCardTop->Controls->Add(this->lblTopTitle);
			this->pnlCardTop->Controls->Add(this->lblTopValue);

			this->lblTopTitle->AutoSize = true;
			this->lblTopTitle->Location = System::Drawing::Point(16, 14);
			this->lblTopTitle->Text = L"Top kitob";
			this->lblTopTitle->ForeColor = System::Drawing::Color::White;

			this->lblTopValue->AutoSize = false;
			this->lblTopValue->Location = System::Drawing::Point(16, 42);
			this->lblTopValue->Size = System::Drawing::Size(330, 40);
			this->lblTopValue->Text = L"-";
			this->lblTopValue->ForeColor = System::Drawing::Color::White;

			this->dgvDemand->Location = System::Drawing::Point(20, 130);
			this->dgvDemand->Size = System::Drawing::Size(750, 320);
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
     array<Button^>^ buttons = { btnAddBook, btnEditBook, btnAddLibrary, btnAddSection, btnDeleteBook, btnDeleteLibrary, btnDeleteSection, btnSelectImage, btnSelectEbook, btnAddReader, btnDeleteReader, btnIssueBook, btnReturnBook };
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
		btnReturnBook->BackColor = System::Drawing::Color::FromArgb(255, 193, 7);

		btnSelectImage->BackColor = System::Drawing::Color::FromArgb(0, 123, 255);
		btnSelectEbook->BackColor = System::Drawing::Color::FromArgb(111, 66, 193);

		// 3D style dashboard cards
		pnlCardTotal->Tag = gcnew cli::array<System::Drawing::Color>(2) { System::Drawing::Color::FromArgb(33, 150, 243), System::Drawing::Color::FromArgb(21, 101, 192) };
		pnlCardTop->Tag = gcnew cli::array<System::Drawing::Color>(2) { System::Drawing::Color::FromArgb(111, 66, 193), System::Drawing::Color::FromArgb(81, 45, 168) };
		pnlCardTotal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DashboardCard_Paint);
		pnlCardTop->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::DashboardCard_Paint);
		pnlCardTotal->MouseEnter += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseEnter);
		pnlCardTotal->MouseLeave += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseLeave);
		pnlCardTop->MouseEnter += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseEnter);
		pnlCardTop->MouseLeave += gcnew System::EventHandler(this, &AdminForm::DashboardCard_MouseLeave);
		lblTotalTitle->BackColor = System::Drawing::Color::Transparent;
		lblTotalValue->BackColor = System::Drawing::Color::Transparent;
		lblTopTitle->BackColor = System::Drawing::Color::Transparent;
		lblTopValue->BackColor = System::Drawing::Color::Transparent;

		// Placeholder qatorlari TextBoxlar uchun
		txtReaderName->Text = L"F.I.Sh kiriting";
		txtReaderPhone->Text = L"Telefon (masalan +9989X)";
		txtReaderID->Text = L"Pasport yoki ID";

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
	}

	private: System::Void SaveData() {
		try {
			StreamWriter^ sw = gcnew StreamWriter("books.txt");
			for (int i = 0; i < dgvBooks->Rows->Count; i++) {
				if (dgvBooks->Rows[i]->Cells[0]->Value != nullptr) {
                 String^ imgPath = dgvBooks->Rows[i]->Cells[5]->Value != nullptr ? dgvBooks->Rows[i]->Cells[5]->Value->ToString() : L"";
					String^ ebookPath = dgvBooks->Rows[i]->Cells[6]->Value != nullptr ? dgvBooks->Rows[i]->Cells[6]->Value->ToString() : L"";
					sw->WriteLine(dgvBooks->Rows[i]->Cells[0]->Value->ToString() + "|" +
						dgvBooks->Rows[i]->Cells[1]->Value->ToString() + "|" +
						dgvBooks->Rows[i]->Cells[2]->Value->ToString() + "|" +
						dgvBooks->Rows[i]->Cells[3]->Value->ToString() + "|" +
						dgvBooks->Rows[i]->Cells[4]->Value->ToString() + "|" +
                       imgPath + "|" + ebookPath);
				}
			}
			sw->Close();

			StreamWriter^ swLibs = gcnew StreamWriter("libraries.txt");
			for (int i = 0; i < dgvLibraries->Rows->Count; i++) {
				if (dgvLibraries->Rows[i]->Cells[0]->Value != nullptr) {
					String^ latStr = dgvLibraries->Rows[i]->Cells[1]->Value != nullptr ? dgvLibraries->Rows[i]->Cells[1]->Value->ToString() : L"0";
					String^ lonStr = dgvLibraries->Rows[i]->Cells[2]->Value != nullptr ? dgvLibraries->Rows[i]->Cells[2]->Value->ToString() : L"0";
					swLibs->WriteLine(dgvLibraries->Rows[i]->Cells[0]->Value->ToString() + "|" + latStr + "|" + lonStr);
				}
			}
			swLibs->Close();

			StreamWriter^ swSec = gcnew StreamWriter("sections.txt");
			for (int i = 0; i < dgvSections->Rows->Count; i++) {
				if (dgvSections->Rows[i]->Cells[0]->Value != nullptr) {
					swSec->WriteLine(dgvSections->Rows[i]->Cells[0]->Value->ToString());
				}
			}
			swSec->Close();

			StreamWriter^ swReaders = gcnew StreamWriter("readers.txt");
			for (int i = 0; i < dgvReaders->Rows->Count; i++) {
				if (dgvReaders->Rows[i]->Cells[0]->Value != nullptr) {
					swReaders->WriteLine(dgvReaders->Rows[i]->Cells[0]->Value->ToString() + "|" +
						dgvReaders->Rows[i]->Cells[1]->Value->ToString() + "|" +
						dgvReaders->Rows[i]->Cells[2]->Value->ToString());
				}
			}
			swReaders->Close();

			StreamWriter^ swIssues = gcnew StreamWriter("issues.txt");
			for (int i = 0; i < dgvIssues->Rows->Count; i++) {
				if (dgvIssues->Rows[i]->Cells[0]->Value != nullptr) {
					swIssues->WriteLine(dgvIssues->Rows[i]->Cells[0]->Value->ToString() + "|" +
						dgvIssues->Rows[i]->Cells[1]->Value->ToString() + "|" +
						dgvIssues->Rows[i]->Cells[2]->Value->ToString() + "|" +
						dgvIssues->Rows[i]->Cells[3]->Value->ToString());
				}
			}
			swIssues->Close();

		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Saqlashda xatolik: " + ex->Message);
		}
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

		if (File::Exists("books.txt")) {
			array<String^>^ lines = File::ReadAllLines("books.txt");
			for each (String^ line in lines) {
				array<String^>^ parts = line->Split('|');
               if (parts->Length >= 5) {
					String^ imgPath = parts->Length > 5 ? parts[5] : L"";
                 String^ ebookPath = parts->Length > 6 ? parts[6] : L"";
					dgvBooks->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], imgPath, ebookPath);
					cmbIssueBook->Items->Add(parts[0]);
				}
			}
		}

		if (File::Exists("libraries.txt")) {
			array<String^>^ lines = File::ReadAllLines("libraries.txt");
			for each (String^ line in lines) {
				array<String^>^ parts = line->Split('|');
				if (parts->Length >= 1) {
					String^ libName = parts[0];
					String^ libLat = parts->Length >= 3 ? parts[1] : L"41.3110";
					String^ libLon = parts->Length >= 3 ? parts[2] : L"69.2401";
					dgvLibraries->Rows->Add(libName, libLat, libLon);
					cmbBookLibrary->Items->Add(libName);
				}
			}
		}

		if (File::Exists("sections.txt")) {
			array<String^>^ lines = File::ReadAllLines("sections.txt");
			for each (String^ line in lines) {
				dgvSections->Rows->Add(line);
				cmbBookSection->Items->Add(line);
			}
		}

		if (File::Exists("readers.txt")) {
			array<String^>^ lines = File::ReadAllLines("readers.txt");
			for each (String^ line in lines) {
				array<String^>^ parts = line->Split('|');
				if (parts->Length == 3) {
					dgvReaders->Rows->Add(parts[0], parts[1], parts[2]);
					cmbIssueReader->Items->Add(parts[0]);
				}
			}
		}

		if (File::Exists("issues.txt")) {
			array<String^>^ lines = File::ReadAllLines("issues.txt");
			for each (String^ line in lines) {
				array<String^>^ parts = line->Split('|');
				if (parts->Length == 4) {
					int idx = dgvIssues->Rows->Add(parts[0], parts[1], parts[2], parts[3]);
					try {
						DateTime dt = DateTime::ParseExact(parts[3], "dd.MM.yyyy", nullptr);
						if (DateTime::Now > dt) {
							dgvIssues->Rows[idx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 200, 200);
						}
					} catch (...) {}
				}
			}
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

		if (File::Exists("issues.txt")) {
			array<String^>^ lines = File::ReadAllLines("issues.txt");
			for each (String^ line in lines) {
				array<String^>^ p = line->Split('|');
				if (p->Length < 4) continue;

				String^ book = p[1];
				double recencyBonus = 0.0;
				try {
					DateTime issueDate = DateTime::ParseExact(p[2], "dd.MM.yyyy", nullptr);
					double days = (DateTime::Now - issueDate).TotalDays;
					recencyBonus = Math::Max(0.0, (30.0 - days) / 30.0);
				}
				catch (...) {}

				double score = 1.0 + recencyBonus;
				if (!scoreMap->ContainsKey(book)) scoreMap->Add(book, 0.0);
				scoreMap[book] += score;
				totalIssues++;
			}
		}

       targetTotalIssues = totalIssues;
		displayedTotalIssues = 0;
		lblTotalValue->Text = L"0";

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

		int limit = Math::Min(10, rows->Count);
		for (int i = 0; i < limit; i++) {
          array<Object^>^ item = rows->default[i];
			String^ book = item[0]->ToString();
			double score = safe_cast<double>(item[1]);
			int rowIdx = dgvDemand->Rows->Add((i + 1).ToString(), book, score.ToString("F2"));
			if (score >= 3.0) dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 235, 238);
			else if (score >= 2.0) dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 248, 225);
			else dgvDemand->Rows[rowIdx]->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(232, 245, 233);
		}

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
			DataGridViewRow^ row = dgvBooks->SelectedRows[0];
			row->Cells[0]->Value = txtBookName->Text;
			row->Cells[1]->Value = cmbBookLibrary->Text;
			row->Cells[2]->Value = cmbBookSection->Text;
			row->Cells[3]->Value = txtBookShelf->Text;
			row->Cells[4]->Value = txtBookRow->Text;
			row->Cells[5]->Value = selectedImagePath;
         row->Cells[6]->Value = selectedEbookPath;
			SaveData();
		} else {
			MessageBox::Show(L"Tahrirlash uchun ro'yxatdan kitob tanlang!");
		}
	}

	private: System::Void btnSelectEbook_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = L"E-kitob fayllari|*.pdf;*.epub;*.mobi";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				String^ ebookDir = "EBooks";
				if (!Directory::Exists(ebookDir)) {
					Directory::CreateDirectory(ebookDir);
				}
				String^ ext = Path::GetExtension(ofd->FileName);
				String^ newFileName = Guid::NewGuid().ToString() + ext;
				String^ newPath = Path::Combine(ebookDir, newFileName);
				File::Copy(ofd->FileName, newPath, true);
				selectedEbookPath = newPath;
				lblEbookPath->Text = L"E-kitob muvaffaqiyatli yuklandi";
			}
			catch (Exception^) {
				selectedEbookPath = ofd->FileName;
				lblEbookPath->Text = L"Tanlandi (asl nusxadan)";
			}
		}
	}

	private: System::Void btnSelectImage_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Filter = L"Rasm fayllari|*.jpg;*.jpeg;*.png;*.bmp";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				String^ imgDir = "Images";
				if (!Directory::Exists(imgDir)) {
					Directory::CreateDirectory(imgDir);
				}
				String^ ext = Path::GetExtension(ofd->FileName);
				String^ newFileName = Guid::NewGuid().ToString() + ext;
				String^ newPath = Path::Combine(imgDir, newFileName);
				File::Copy(ofd->FileName, newPath, true);
				selectedImagePath = newPath;
				lblImagePath->Text = L"Rasm muvaffaqiyatli yuklandi";
			}
			catch (Exception^) {
				selectedImagePath = ofd->FileName;
				lblImagePath->Text = L"Tanlandi (asl nusxadan)";
			}
		}
	}

	private: System::Void btnAddBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtBookName->Text == L"" || cmbBookLibrary->Text == L"" || cmbBookSection->Text == L"" || txtBookShelf->Text == L"" || txtBookRow->Text == L"") {
			MessageBox::Show(L"Barcha maydonlarni to'ldiring!");
			return;
		}
        dgvBooks->Rows->Add(txtBookName->Text, cmbBookLibrary->Text, cmbBookSection->Text, txtBookShelf->Text, txtBookRow->Text, selectedImagePath, selectedEbookPath);
		txtBookName->Text = L""; txtBookShelf->Text = L""; txtBookRow->Text = L"";
		selectedImagePath = L"";
        selectedEbookPath = L"";
		lblImagePath->Text = L"Rasm tanlanmadi";
     lblEbookPath->Text = L"E-kitob tanlanmadi";
		SaveData();
	}

	private: System::Void btnDeleteBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvBooks->SelectedRows->Count > 0) {
			dgvBooks->Rows->RemoveAt(dgvBooks->SelectedRows[0]->Index);
			SaveData();
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

		dgvLibraries->Rows->Add(txtLibraryName->Text, lat, lon);
		cmbBookLibrary->Items->Add(txtLibraryName->Text);
		txtLibraryName->Text = L"";
		txtLibraryLat->Text = L"";
		txtLibraryLon->Text = L"";
		SaveData();
	}

	private: System::Void btnDeleteLibrary_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvLibraries->SelectedRows->Count > 0) {
			dgvLibraries->Rows->RemoveAt(dgvLibraries->SelectedRows[0]->Index);
			SaveData();
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnAddSection_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtSectionName->Text == L"") {
			MessageBox::Show(L"Bo'lim nomini kiriting!");
			return;
		}
		dgvSections->Rows->Add(txtSectionName->Text);
		cmbBookSection->Items->Add(txtSectionName->Text);
		txtSectionName->Text = L"";
		SaveData();
	}

	private: System::Void btnDeleteSection_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvSections->SelectedRows->Count > 0) {
			dgvSections->Rows->RemoveAt(dgvSections->SelectedRows[0]->Index);
			SaveData();
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnAddReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtReaderName->Text == L"" || txtReaderPhone->Text == L"" || txtReaderID->Text == L"") {
			MessageBox::Show(L"Barcha maydonlarni to'ldiring!");
			return;
		}
		dgvReaders->Rows->Add(txtReaderName->Text, txtReaderPhone->Text, txtReaderID->Text);
		cmbIssueReader->Items->Add(txtReaderName->Text);
		txtReaderName->Text = L""; txtReaderPhone->Text = L""; txtReaderID->Text = L"";
		SaveData();
	}

	private: System::Void btnDeleteReader_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvReaders->SelectedRows->Count > 0) {
			dgvReaders->Rows->RemoveAt(dgvReaders->SelectedRows[0]->Index);
			SaveData();
		} else {
			MessageBox::Show(L"O'chirish uchun butun qatorni tanlang!");
		}
	}

	private: System::Void btnIssueBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbIssueReader->Text == L"" || cmbIssueBook->Text == L"") {
			MessageBox::Show(L"Kitobxon va Kitobni tanlang!");
			return;
		}
		String^ giveDate = DateTime::Now.ToString("dd.MM.yyyy");
		String^ retDate = dtpReturnDate->Value.ToString("dd.MM.yyyy");
		dgvIssues->Rows->Add(cmbIssueReader->Text, cmbIssueBook->Text, giveDate, retDate);
		SaveData();
	}

	private: System::Void btnReturnBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dgvIssues->SelectedRows->Count > 0) {
			dgvIssues->Rows->RemoveAt(dgvIssues->SelectedRows[0]->Index);
			SaveData();
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
