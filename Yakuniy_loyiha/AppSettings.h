#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Drawing::Drawing2D;
using namespace System::Collections::Generic;

namespace Yakuniyloyiha {

	public enum class AppLanguage {
		Uzbek = 0,
		English = 1,
		Russian = 2
	};

	public ref class AppSettings abstract sealed {
	public:
		static AppLanguage CurrentLanguage = AppLanguage::Uzbek;
		static bool DarkMode = false;

		static String^ Translate(String^ uz, String^ en, String^ ru) {
			switch (CurrentLanguage) {
			case AppLanguage::English: return en;
			case AppLanguage::Russian: return ru;
			default: return uz;
			}
		}

		static void Load() {
			String^ path = GetSettingsPath();
			if (!File::Exists(path)) return;

			try {
				array<String^>^ lines = File::ReadAllLines(path);
				for each (String ^ line in lines) {
					if (String::IsNullOrWhiteSpace(line) || !line->Contains("=")) continue;
					array<String^>^ kv = line->Split(gcnew array<wchar_t>{ '=' }, 2);
					if (kv->Length < 2) continue;

					String^ key = kv[0]->Trim()->ToLowerInvariant();
					String^ val = kv[1]->Trim();

					if (key == "language") {
						String^ v = val->ToLowerInvariant();
						if (v == "english") CurrentLanguage = AppLanguage::English;
						else if (v == "russian") CurrentLanguage = AppLanguage::Russian;
						else CurrentLanguage = AppLanguage::Uzbek;
					}
					else if (key == "darkmode") {
						DarkMode = (val->ToLowerInvariant() == "true" || val == "1");
					}
				}
			}
			catch (Exception^) {
			}
		}

		static void Save() {
			String^ languageValue = "uzbek";
			if (CurrentLanguage == AppLanguage::English) languageValue = "english";
			else if (CurrentLanguage == AppLanguage::Russian) languageValue = "russian";

			array<String^>^ lines = gcnew array<String^>{
				"language=" + languageValue,
				"darkMode=" + (DarkMode ? "true" : "false")
			};

			try {
				File::WriteAllLines(GetSettingsPath(), lines);
			}
			catch (Exception^) {
			}
		}

		// === CREATIVE PREMIUM GRADIENT SYSTEM ===
		static Color GradientPrimaryStart() {
			return DarkMode ? Color::FromArgb(38, 207, 219) : Color::FromArgb(112, 170, 206);
		}

		static Color GradientPrimaryEnd() {
			return DarkMode ? Color::FromArgb(111, 132, 255) : Color::FromArgb(60, 110, 150);
		}

		static Color GradientAccentStart() {
			return DarkMode ? Color::FromArgb(34, 187, 211) : Color::FromArgb(73, 198, 217);
		}

		static Color GradientAccentEnd() {
			return DarkMode ? Color::FromArgb(88, 110, 230) : Color::FromArgb(105, 130, 247);
		}

		static Color GradientWarmStart() {
			return DarkMode ? Color::FromArgb(241, 198, 104) : Color::FromArgb(245, 212, 126);
		}

		static Color GradientWarmEnd() {
			return DarkMode ? Color::FromArgb(240, 141, 70) : Color::FromArgb(244, 160, 84);
		}

		static Color CardHoverColor() {
			return DarkMode ? Color::FromArgb(46, 69, 111) : Color::FromArgb(53, 71, 89);
		}

		static Color CardElevatedColor() {
			return DarkMode ? Color::FromArgb(38, 53, 85) : Color::FromArgb(245, 245, 250);
		}

		static Color SidebarColor() {
			return DarkMode ? Color::FromArgb(30, 166, 191) : Color::FromArgb(45, 162, 179);
		}

		static void ApplyTheme(Form^ form) {
			if (form == nullptr) return;

			Color bg = PageBackColor();
			Color panel = SurfaceColor();
			Color text = TextColor();
			Color muted = MutedTextColor();

			form->BackColor = bg;
			form->ForeColor = text;
			form->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Regular);
			ApplyThemeToControls(form->Controls, bg, panel, text, muted);
		}

		static Color PageBackColor() {
			return DarkMode ? Color::FromArgb(23, 36, 61) : Color::FromArgb(112, 170, 206);
		}

		static Color SurfaceColor() {
			return DarkMode ? Color::FromArgb(36, 55, 88) : Color::FromArgb(43, 61, 79);
		}

		static Color ElevatedColor() {
			return DarkMode ? Color::FromArgb(44, 65, 101) : Color::FromArgb(245, 245, 250);
		}

		static Color TextColor() {
			return DarkMode ? Color::FromArgb(246, 249, 255) : Color::FromArgb(20, 30, 50);
		}

		static Color MutedTextColor() {
			return DarkMode ? Color::FromArgb(169, 186, 212) : Color::FromArgb(60, 80, 100);
		}

		static Color BorderColor() {
			return DarkMode ? Color::FromArgb(71, 101, 142) : Color::FromArgb(45, 162, 179);
		}

		static Color PrimaryColor() {
			return DarkMode ? Color::FromArgb(78, 127, 255) : Color::FromArgb(45, 162, 179);
		}

		static Color PrimaryHoverColor() {
			return DarkMode ? Color::FromArgb(106, 151, 255) : Color::FromArgb(35, 142, 159);
		}

		static Color PrimaryTextColor() {
			return DarkMode ? Color::FromArgb(10, 20, 40) : Color::White;
		}

		static Color SecondaryColor() {
			return DarkMode ? Color::FromArgb(232, 198, 104) : Color::FromArgb(255, 180, 80);
		}

		static Color SuccessColor() {
			return DarkMode ? Color::FromArgb(50, 220, 120) : Color::FromArgb(30, 180, 100);
		}

		static Color DangerColor() {
			return DarkMode ? Color::FromArgb(255, 80, 100) : Color::FromArgb(220, 50, 50);
		}

		static Color WarningColor() {
			return DarkMode ? Color::FromArgb(255, 200, 80) : Color::FromArgb(255, 140, 0);
		}

		static void MakeRounded(Control^ ctrl, int radius) {
			if (ctrl == nullptr || ctrl->Width <= 0 || ctrl->Height <= 0) return;
			GraphicsPath^ path = gcnew GraphicsPath();
			path->StartFigure();
			path->AddArc(0, 0, radius, radius, 180, 90);
			path->AddArc(ctrl->Width - radius, 0, radius, radius, 270, 90);
			path->AddArc(ctrl->Width - radius, ctrl->Height - radius, radius, radius, 0, 90);
			path->AddArc(0, ctrl->Height - radius, radius, radius, 90, 90);
			path->CloseFigure();
			ctrl->Region = gcnew Region(path);
		}

		static System::Collections::Generic::List<String^>^ ExtractJsonObjects(String^ json) {
			System::Collections::Generic::List<String^>^ result = gcnew System::Collections::Generic::List<String^>();
			if (String::IsNullOrEmpty(json)) return result;
			int braceCount = 0;
			int startIndex = -1;
			bool inString = false;
			for (int i = 0; i < json->Length; i++) {
				wchar_t c = json[i];
				if (c == L'"' && (i == 0 || json[i - 1] != L'\\')) {
					inString = !inString;
				}
				if (!inString) {
					if (c == L'{') {
						if (braceCount == 0) startIndex = i;
						braceCount++;
					} else if (c == L'}') {
						braceCount--;
						if (braceCount == 0 && startIndex != -1) {
							result->Add(json->Substring(startIndex, i - startIndex + 1));
							startIndex = -1;
						}
					}
				}
			}
			return result;
		}

		static void StyleButton(Button^ btn, Color backColor, Color foreColor) {
			if (btn == nullptr) return;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->BackColor = backColor;
			btn->ForeColor = foreColor;
			btn->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			btn->Cursor = Cursors::Hand;
			btn->Height = 40;
			MakeRounded(btn, 10);
		}

		static void StyleModernButton(Button^ btn, bool isPrimary) {
			if (btn == nullptr) return;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
			btn->Cursor = Cursors::Hand;
			btn->Height = 44;
			MakeRounded(btn, 12);

			if (isPrimary) {
				btn->BackColor = PrimaryColor();
				btn->ForeColor = PrimaryTextColor();
				btn->FlatAppearance->MouseOverBackColor = PrimaryHoverColor();
			}
			else {
				btn->BackColor = ElevatedColor();
				btn->ForeColor = TextColor();
				btn->FlatAppearance->BorderSize = 2;
				btn->FlatAppearance->BorderColor = BorderColor();
				btn->FlatAppearance->MouseOverBackColor = CardHoverColor();
			}
		}

		static void EnableGradientBackground(Control^ ctrl, Color start, Color end) {
			if (ctrl == nullptr) return;
			gradientMap[ctrl] = gcnew cli::array<Color>(2) { start, end };
			ctrl->Paint -= gcnew PaintEventHandler(&AppSettings::PaintGradientBackground);
			ctrl->Paint += gcnew PaintEventHandler(&AppSettings::PaintGradientBackground);
			ctrl->Resize -= gcnew EventHandler(&AppSettings::RefreshGradientControl);
			ctrl->Resize += gcnew EventHandler(&AppSettings::RefreshGradientControl);
			ctrl->Invalidate();
		}

		static void StyleSurfacePanel(Panel^ panel, int radius, bool elevated) {
			if (panel == nullptr) return;
			panel->BackColor = elevated ? CardElevatedColor() : SurfaceColor();
			MakeRounded(panel, radius);
		}

		static void StyleAccentStrip(Panel^ panel, Color color, int radius) {
			if (panel == nullptr) return;
			panel->BackColor = color;
			MakeRounded(panel, radius);
		}

		static void StyleHeaderTitle(Label^ label) {
			if (label == nullptr) return;
			label->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 20.0F, FontStyle::Bold);
			label->ForeColor = Color::White;
			label->BackColor = Color::Transparent;
		}

		static void StyleHeaderSubtitle(Label^ label) {
			if (label == nullptr) return;
			label->Font = gcnew Drawing::Font(L"Segoe UI", 10.2F, FontStyle::Regular);
			label->ForeColor = Color::FromArgb(225, 240, 255);
			label->BackColor = Color::Transparent;
		}

		static void StyleSectionTitle(Label^ label) {
			if (label == nullptr) return;
			label->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 12.5F, FontStyle::Bold);
			label->ForeColor = TextColor();
			label->BackColor = Color::Transparent;
		}

		static void StyleBodyText(Label^ label) {
			if (label == nullptr) return;
			label->Font = gcnew Drawing::Font(L"Segoe UI", 9.6F, FontStyle::Regular);
			label->ForeColor = MutedTextColor();
			label->BackColor = Color::Transparent;
		}

		static void StyleMetricLabel(Label^ label, Color accentColor) {
			if (label == nullptr) return;
			label->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 42.0F, FontStyle::Bold);
			label->ForeColor = accentColor;
			label->BackColor = Color::Transparent;
		}

		static void StyleInput(Control^ input) {
			if (input == nullptr) return;
			input->BackColor = Color::White;
			input->ForeColor = Color::Black;
			input->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F, FontStyle::Regular);
			TextBox^ tb = dynamic_cast<TextBox^>(input);
			if (tb != nullptr) {
				tb->BorderStyle = BorderStyle::FixedSingle;
				tb->ForeColor = Color::Black;
			}
			ComboBox^ cb = dynamic_cast<ComboBox^>(input);
			if (cb != nullptr) {
				cb->FlatStyle = FlatStyle::Flat;
				cb->ForeColor = Color::Black;
			}
		}

		static void StyleGrid(DataGridView^ dgv) {
			if (dgv == nullptr) return;
			dgv->BackgroundColor = Color::White;
			dgv->BorderStyle = BorderStyle::None;
			dgv->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			dgv->GridColor = BorderColor();
			dgv->EnableHeadersVisualStyles = false;
			dgv->RowHeadersVisible = false;
			dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			dgv->AllowUserToAddRows = false;
			dgv->ReadOnly = true;
			dgv->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
			dgv->ColumnHeadersHeight = 45;
			dgv->RowTemplate->Height = 40;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = PrimaryColor();
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			dgv->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 11.0F, FontStyle::Bold);
			dgv->DefaultCellStyle->BackColor = Color::White;
			dgv->DefaultCellStyle->ForeColor = Color::Black;
			dgv->DefaultCellStyle->SelectionBackColor = PrimaryColor();
			dgv->DefaultCellStyle->SelectionForeColor = Color::White;
			dgv->DefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Regular);
			dgv->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 245, 250);
		}

		static void StyleModernCard(Panel^ card, bool isElevated) {
			if (card == nullptr) return;
			card->BackColor = isElevated ? CardElevatedColor() : SurfaceColor();
			MakeRounded(card, 18);
			if (isElevated) {
				card->BorderStyle = BorderStyle::FixedSingle;
			}
		}

		static Panel^ CreatePremiumCard(int width, int height, int radius, Color bgColor) {
			Panel^ card = gcnew Panel();
			card->Size = System::Drawing::Size(width, height);
			card->BackColor = bgColor;
			MakeRounded(card, radius);
			return card;
		}

	private:
		static Dictionary<Control^, cli::array<Color>^>^ gradientMap = gcnew Dictionary<Control^, cli::array<Color>^>();

		static String^ GetSettingsPath() {
			return Path::Combine(Application::StartupPath, "app_settings.txt");
		}

		static void RefreshGradientControl(Object^ sender, EventArgs^ e) {
			Control^ ctrl = dynamic_cast<Control^>(sender);
			if (ctrl != nullptr) ctrl->Invalidate();
		}

		static void PaintGradientBackground(Object^ sender, PaintEventArgs^ e) {
			Control^ ctrl = dynamic_cast<Control^>(sender);
			if (ctrl == nullptr || !gradientMap->ContainsKey(ctrl)) return;

			cli::array<Color>^ colors = gradientMap[ctrl];
			if (colors == nullptr || colors->Length < 2) return;

			Rectangle rect = ctrl->ClientRectangle;
			if (rect.Width <= 0 || rect.Height <= 0) return;

			e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
			LinearGradientBrush^ brush = gcnew LinearGradientBrush(
				Point(rect.Left, rect.Top),
				Point(rect.Right, rect.Bottom),
				colors[0],
				colors[1]
			);
			e->Graphics->FillRectangle(brush, rect);
			delete brush;
		}

		static void ApplyThemeToControls(Control::ControlCollection^ controls, Color bg, Color panel, Color text, Color muted) {
			for each (Control ^ c in controls) {
				if (dynamic_cast<Button^>(c) != nullptr) {
					Button^ btn = (Button^)c;
					StyleButton(btn, PrimaryColor(), Color::White);
				}
				else if (dynamic_cast<TextBox^>(c) != nullptr) {
					StyleInput(c);
				}
				else if (dynamic_cast<ComboBox^>(c) != nullptr) {
					StyleInput(c);
				}
				else if (dynamic_cast<CheckBox^>(c) != nullptr) {
					Color pColor = (c->Parent != nullptr) ? c->Parent->BackColor : bg;
					// If background is dark (R+G+B < 380), use white text. Otherwise use normal text.
					bool isDark = (pColor.R + pColor.G + pColor.B) < 380;
					c->ForeColor = isDark ? Color::White : text;
					c->BackColor = Color::Transparent;
				}
				else if (dynamic_cast<Label^>(c) != nullptr) {
					Label^ lbl = (Label^)c;
					Color pColor = (c->Parent != nullptr) ? c->Parent->BackColor : bg;
					bool isDark = (pColor.R + pColor.G + pColor.B) < 380;
					lbl->ForeColor = isDark ? (lbl->Font->Bold ? Color::White : Color::FromArgb(200, 210, 220)) : (lbl->Font->Bold ? text : muted);
					if (lbl->BackColor != Color::Transparent) lbl->BackColor = Color::Transparent;
				}
				else if (dynamic_cast<DataGridView^>(c) != nullptr) {
					StyleGrid((DataGridView^)c);
				}
				else if (dynamic_cast<Panel^>(c) != nullptr) {
					if (c->Size.Height <= 2) c->BackColor = BorderColor();
					else if (c->BackColor != Color::Transparent) c->BackColor = panel;
				}
				else {
					c->BackColor = bg;
					c->ForeColor = text;
				}

				if (c->Controls != nullptr && c->Controls->Count > 0) {
					ApplyThemeToControls(c->Controls, bg, panel, text, muted);
				}
			}
		}
	};
}
