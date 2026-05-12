#pragma once
#include "AppSettings.h"

namespace Yakuniyloyiha {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;

	public ref class StatisticsForm : public System::Windows::Forms::Form
	{
	public:
		StatisticsForm(void)
		{
			this->Text = AppSettings::Translate(L"Statistika", L"Statistics", L"Статистика");
			this->Size = System::Drawing::Size(700, 850);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
			this->MaximizeBox = true;
			this->MinimizeBox = false;
			this->BackColor = AppSettings::PageBackColor();
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);

			// === MODERN HEADER ===
			Panel^ header = gcnew Panel();
			header->Location = Point(0, 0);
			header->Size = System::Drawing::Size(this->ClientSize.Width, 160);
			header->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
			AppSettings::EnableGradientBackground(header, AppSettings::GradientPrimaryStart(), AppSettings::GradientPrimaryEnd());

			Panel^ iconBadge = gcnew Panel();
			iconBadge->Location = Point(20, 20);
			iconBadge->Size = System::Drawing::Size(78, 78);
			iconBadge->BackColor = Color::FromArgb(235, 255, 255, 255);
			AppSettings::MakeRounded(iconBadge, 39);
			header->Controls->Add(iconBadge);

			Label^ iconLabel = gcnew Label();
			iconLabel->Text = L"📊";
			iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 38.0F);
			iconLabel->Dock = DockStyle::Fill;
			iconLabel->TextAlign = ContentAlignment::MiddleCenter;
			iconLabel->ForeColor = AppSettings::TextColor();
			iconLabel->BackColor = Color::Transparent;
			iconBadge->Controls->Add(iconLabel);

			Label^ titleLabel = gcnew Label();
			titleLabel->Text = AppSettings::Translate(L"Statistika", L"Statistics", L"Статистика");
			AppSettings::StyleHeaderTitle(titleLabel);
			titleLabel->Location = Point(122, 26);
			titleLabel->Size = System::Drawing::Size(420, 40);
			titleLabel->AutoEllipsis = true;
			header->Controls->Add(titleLabel);

			Label^ subtitleLabel = gcnew Label();
			subtitleLabel->Text = AppSettings::Translate(L"Tizim faoliyati bo'yicha real vaqt ko'rsatkichlari", L"Real-time system activity indicators", L"Показатели активности системы в реальном времени");
			AppSettings::StyleHeaderSubtitle(subtitleLabel);
			subtitleLabel->Location = Point(124, 68);
			subtitleLabel->Size = System::Drawing::Size(470, 34);
			subtitleLabel->AutoEllipsis = true;
			header->Controls->Add(subtitleLabel);

			this->Controls->Add(header);

			int books = File::Exists("books.txt") ? File::ReadAllLines("books.txt")->Length : 0;
			int readers = File::Exists("readers.txt") ? File::ReadAllLines("readers.txt")->Length : 0;
			int issues = File::Exists("issues.txt") ? File::ReadAllLines("issues.txt")->Length : 0;
			int libraries = File::Exists("libraries.txt") ? File::ReadAllLines("libraries.txt")->Length : 0;

			// === STAT CARDS IN 2x2 GRID ===
			int cardY = 190;
			int cardX = 20;
			int cardWidth = (this->ClientSize.Width - 60) / 2;
			
			AddPremiumKPICard(
				L"📚 Kitoblar", books.ToString(), cardX, cardY, cardWidth,
				AppSettings::GradientPrimaryStart(), AppSettings::GradientPrimaryEnd()
			);
			
			AddPremiumKPICard(
				L"🏛️ Kutubxonalar", libraries.ToString(), cardX + cardWidth + 20, cardY, cardWidth,
				AppSettings::GradientAccentStart(), AppSettings::GradientAccentEnd()
			);
			
			AddPremiumKPICard(
				L"👥 Kitobxonlar", readers.ToString(), cardX, cardY + 180, cardWidth,
				AppSettings::SuccessColor(), Color::FromArgb(80, 200, 150)
			);
			
			AddPremiumKPICard(
				L"📖 Ijaralar", issues.ToString(), cardX + cardWidth + 20, cardY + 180, cardWidth,
				AppSettings::WarningColor(), Color::FromArgb(255, 160, 0)
			);

			// === CHART PANEL ===
			chartValues = gcnew System::Collections::Generic::List<int>();
			chartLabels = gcnew System::Collections::Generic::List<String^>();
			chartValues->Add(books); chartLabels->Add(L"Kitoblar");
			chartValues->Add(libraries); chartLabels->Add(L"Kutubxonalar");
			chartValues->Add(readers); chartLabels->Add(L"Kitobxonlar");
			chartValues->Add(issues); chartLabels->Add(L"Ijaralar");

			Panel^ pnlChart = gcnew Panel();
			pnlChart->Location = Point(cardX, cardY + 360);
			pnlChart->Size = System::Drawing::Size(this->ClientSize.Width - 40, 240);
			AppSettings::StyleSurfacePanel(pnlChart, 18, false);
			pnlChart->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &StatisticsForm::pnlChart_Paint);
			this->Controls->Add(pnlChart);

			// === CLOSE BUTTON ===
			Button^ btnClose = gcnew Button();
			btnClose->Text = AppSettings::Translate(L"Yopish", L"Close", L"Закрыть");
			btnClose->Location = Point(this->ClientSize.Width - 140, this->ClientSize.Height - 60);
			btnClose->Size = System::Drawing::Size(120, 38);
			btnClose->Anchor = static_cast<AnchorStyles>(AnchorStyles::Right | AnchorStyles::Bottom);
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			AppSettings::StyleModernButton(btnClose, true);
			this->Controls->Add(btnClose);
		}

	private:
		System::Collections::Generic::List<int>^ chartValues;
		System::Collections::Generic::List<String^>^ chartLabels;

		System::Void pnlChart_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			Panel^ p = safe_cast<Panel^>(sender);
			
			// Draw Title
			g->DrawString(L"Tizim ko'rsatkichlari (Grafik)", gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.0F), gcnew SolidBrush(AppSettings::TextColor()), PointF(20, 15));
			
			if (chartValues == nullptr || chartValues->Count == 0) return;
			
			int maxVal = 10;
			for (int i = 0; i < chartValues->Count; i++) {
				if (chartValues[i] > maxVal) maxVal = chartValues[i];
			}
			
			int chartX = 40;
			int chartY = 50;
			int chartW = p->Width - 80;
			int chartH = p->Height - 80;
			
			// Draw axes
			Pen^ axisPen = gcnew Pen(Color::FromArgb(200, 200, 200), 2);
			g->DrawLine(axisPen, chartX, chartY, chartX, chartY + chartH);
			g->DrawLine(axisPen, chartX, chartY + chartH, chartX + chartW, chartY + chartH);
			
			int barWidth = 60;
			int spacing = (chartW - (chartValues->Count * barWidth)) / (chartValues->Count + 1);
			
			array<Color>^ colors = { AppSettings::PrimaryColor(), AppSettings::SecondaryColor(), AppSettings::SuccessColor(), AppSettings::WarningColor() };
			
			for (int i = 0; i < chartValues->Count; i++) {
				int val = chartValues[i];
				int barH = (int)((float)val / maxVal * (chartH - 20));
				if (barH < 5 && val > 0) barH = 5; // minimum height
				int x = chartX + spacing + i * (barWidth + spacing);
				int y = chartY + chartH - barH;
				
				Color c = colors[i % colors->Length];
				System::Drawing::Drawing2D::LinearGradientBrush^ b = gcnew System::Drawing::Drawing2D::LinearGradientBrush(
					Rectangle(x, y, barWidth, Math::Max(1, barH)),
					c, Color::FromArgb((int)(c.R * 0.8), (int)(c.G * 0.8), (int)(c.B * 0.8)), 90.0F
				);
				
				g->FillRectangle(b, x, y, barWidth, barH);
				
				// Value label
				String^ sVal = val.ToString();
				SizeF sizeVal = g->MeasureString(sVal, this->Font);
				g->DrawString(sVal, gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold), gcnew SolidBrush(AppSettings::TextColor()), (float)(x + barWidth/2) - (sizeVal.Width/2.0f), (float)(y - 20));
				
				// Name label
				String^ name = chartLabels[i];
				SizeF sizeName = g->MeasureString(name, this->Font);
				g->DrawString(name, this->Font, Brushes::DimGray, (float)(x + barWidth/2) - (sizeName.Width/2.0f), (float)(chartY + chartH + 5));
			}
		}
		void AddStatCard(String^ label, String^ val, Point location, Color gradStart, Color gradEnd) {
			Panel^ card = gcnew Panel();
			card->Location = location;
			card->Size = System::Drawing::Size(320, 160);
			card->BackColor = AppSettings::SurfaceColor();
			AppSettings::MakeRounded(card, 16);
			this->Controls->Add(card);

			// Top gradient accent
			Panel^ accentBar = gcnew Panel();
			accentBar->Location = Point(0, 0);
			accentBar->Size = System::Drawing::Size(320, 6);
			accentBar->BackColor = gradStart;
			AppSettings::MakeRounded(accentBar, 16);
			card->Controls->Add(accentBar);

			Label^ lbl = gcnew Label();
			lbl->Text = label;
			lbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 13.0F, FontStyle::Bold);
			lbl->ForeColor = AppSettings::TextColor();
			lbl->Location = Point(20, 20);
			lbl->Size = System::Drawing::Size(280, 32);
			card->Controls->Add(lbl);

			Label^ valLbl = gcnew Label();
			valLbl->Text = val;
			valLbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 44.0F, FontStyle::Bold);
			valLbl->ForeColor = gradStart;
			valLbl->Location = Point(20, 60);
			valLbl->Size = System::Drawing::Size(280, 70);
			valLbl->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			card->Controls->Add(valLbl);
		}

		void AddPremiumKPICard(String^ label, String^ val, int x, int y, int width, Color gradStart, Color gradEnd) {
			Panel^ card = gcnew Panel();
			card->Location = Point(x, y);
			card->Size = System::Drawing::Size(width, 160);
			AppSettings::StyleSurfacePanel(card, 18, false);
			this->Controls->Add(card);

			// Gradient accent bar at top
			Panel^ accentBar = gcnew Panel();
			accentBar->Location = Point(0, 0);
			accentBar->Size = System::Drawing::Size(width, 8);
			AppSettings::StyleAccentStrip(accentBar, gradStart, 18);
			card->Controls->Add(accentBar);

			Label^ lbl = gcnew Label();
			lbl->Text = label;
			AppSettings::StyleSectionTitle(lbl);
			lbl->Location = Point(20, 20);
			lbl->Size = System::Drawing::Size(280, 32);
			card->Controls->Add(lbl);

			Label^ valLbl = gcnew Label();
			valLbl->Text = val;
			AppSettings::StyleMetricLabel(valLbl, gradStart);
			valLbl->Location = Point(20, 58);
			valLbl->Size = System::Drawing::Size(280, 70);
			valLbl->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			card->Controls->Add(valLbl);
		}
	};
}
