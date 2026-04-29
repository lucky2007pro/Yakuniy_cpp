#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Windows::Forms;

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
			return DarkMode ? Color::FromArgb(10, 14, 23) : Color::FromArgb(245, 247, 251);
		}

		static Color SurfaceColor() {
			return DarkMode ? Color::FromArgb(22, 30, 46) : Color::White;
		}

		static Color ElevatedColor() {
			return DarkMode ? Color::FromArgb(30, 40, 59) : Color::FromArgb(232, 238, 247);
		}

		static Color TextColor() {
			return DarkMode ? Color::FromArgb(248, 250, 252) : Color::FromArgb(15, 23, 42);
		}

		static Color MutedTextColor() {
			return DarkMode ? Color::FromArgb(148, 163, 184) : Color::FromArgb(100, 116, 139);
		}

		static Color BorderColor() {
			return DarkMode ? Color::FromArgb(49, 63, 85) : Color::FromArgb(218, 226, 238);
		}

		static Color PrimaryColor() {
			return DarkMode ? Color::FromArgb(0, 242, 254) : Color::FromArgb(37, 99, 235);
		}

		static Color PrimaryHoverColor() {
			return DarkMode ? Color::FromArgb(79, 172, 254) : Color::FromArgb(29, 78, 216);
		}

		static Color PrimaryTextColor() {
			return DarkMode ? Color::FromArgb(5, 10, 18) : Color::White;
		}

		static Color SecondaryColor() {
			return DarkMode ? Color::FromArgb(161, 140, 209) : Color::FromArgb(99, 102, 241);
		}

		static Color SuccessColor() {
			return DarkMode ? Color::FromArgb(0, 230, 118) : Color::FromArgb(22, 163, 74);
		}

		static Color DangerColor() {
			return DarkMode ? Color::FromArgb(255, 23, 68) : Color::FromArgb(220, 38, 38);
		}

		static Color WarningColor() {
			return DarkMode ? Color::FromArgb(255, 201, 87) : Color::FromArgb(245, 158, 11);
		}

		static void MakeRounded(Control^ ctrl, int radius) {
			if (ctrl == nullptr || ctrl->Width <= 0 || ctrl->Height <= 0) return;
			System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
			path->StartFigure();
			path->AddArc(0, 0, radius, radius, 180, 90);
			path->AddArc(ctrl->Width - radius, 0, radius, radius, 270, 90);
			path->AddArc(ctrl->Width - radius, ctrl->Height - radius, radius, radius, 0, 90);
			path->AddArc(0, ctrl->Height - radius, radius, radius, 90, 90);
			path->CloseFigure();
			ctrl->Region = gcnew Region(path);
		}

		static void StyleButton(Button^ btn, Color backColor, Color foreColor) {
			if (btn == nullptr) return;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->BackColor = backColor;
			btn->ForeColor = foreColor;
			btn->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			btn->Cursor = Cursors::Hand;
			MakeRounded(btn, 10);
		}

		static void StyleInput(Control^ input) {
			if (input == nullptr) return;
			input->BackColor = SurfaceColor();
			input->ForeColor = TextColor();
			input->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F, FontStyle::Regular);
			TextBox^ tb = dynamic_cast<TextBox^>(input);
			if (tb != nullptr) tb->BorderStyle = BorderStyle::FixedSingle;
			ComboBox^ cb = dynamic_cast<ComboBox^>(input);
			if (cb != nullptr) cb->FlatStyle = FlatStyle::Flat;
		}

		static void StyleGrid(DataGridView^ dgv) {
			if (dgv == nullptr) return;
			dgv->BackgroundColor = SurfaceColor();
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
			dgv->ColumnHeadersHeight = 42;
			dgv->RowTemplate->Height = 38;
			dgv->ColumnHeadersDefaultCellStyle->BackColor = ElevatedColor();
			dgv->ColumnHeadersDefaultCellStyle->ForeColor = TextColor();
			dgv->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0F, FontStyle::Bold);
			dgv->DefaultCellStyle->BackColor = SurfaceColor();
			dgv->DefaultCellStyle->ForeColor = TextColor();
			dgv->DefaultCellStyle->SelectionBackColor = DarkMode ? Color::FromArgb(18, 93, 120) : Color::FromArgb(219, 234, 254);
			dgv->DefaultCellStyle->SelectionForeColor = TextColor();
			dgv->DefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Regular);
			dgv->AlternatingRowsDefaultCellStyle->BackColor = DarkMode ? Color::FromArgb(17, 25, 39) : Color::FromArgb(248, 250, 252);
		}

	private:
		static String^ GetSettingsPath() {
			return Path::Combine(Application::StartupPath, "app_settings.txt");
		}

		static void ApplyThemeToControls(Control::ControlCollection^ controls, Color bg, Color panel, Color text, Color muted) {
			for each (Control ^ c in controls) {
				if (dynamic_cast<Button^>(c) != nullptr) {
					Button^ btn = (Button^)c;
					if (btn->BackColor.ToArgb() == Color::FromArgb(40, 44, 52).ToArgb() || btn->ForeColor == Color::White) {
						StyleButton(btn, PrimaryColor(), Color::White);
					}
					else {
						StyleButton(btn, panel, text);
					}
				}
				else if (dynamic_cast<TextBox^>(c) != nullptr) {
					StyleInput(c);
				}
				else if (dynamic_cast<ComboBox^>(c) != nullptr) {
					StyleInput(c);
				}
				else if (dynamic_cast<CheckBox^>(c) != nullptr) {
					c->ForeColor = text;
					c->BackColor = bg;
				}
				else if (dynamic_cast<Label^>(c) != nullptr) {
					Label^ lbl = (Label^)c;
					lbl->ForeColor = lbl->Font->Bold ? text : muted;
					if (lbl->BackColor != Color::Transparent) lbl->BackColor = bg;
				}
				else if (dynamic_cast<DataGridView^>(c) != nullptr) {
					StyleGrid((DataGridView^)c);
				}
				else if (dynamic_cast<Panel^>(c) != nullptr) {
					if (c->Size.Height <= 2) c->BackColor = BorderColor();
					else c->BackColor = panel;
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
