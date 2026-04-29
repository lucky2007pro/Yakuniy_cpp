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

			Color bg = DarkMode ? Color::FromArgb(24, 26, 27) : Color::White;
			Color panel = DarkMode ? Color::FromArgb(36, 39, 41) : Color::FromArgb(245, 245, 245);
			Color text = DarkMode ? Color::FromArgb(236, 240, 241) : Color::FromArgb(33, 37, 41);
			Color muted = DarkMode ? Color::FromArgb(170, 176, 180) : Color::FromArgb(108, 117, 125);

			form->BackColor = bg;
			form->ForeColor = text;
			ApplyThemeToControls(form->Controls, bg, panel, text, muted);
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
						btn->BackColor = DarkMode ? Color::FromArgb(70, 130, 180) : Color::FromArgb(40, 44, 52);
						btn->ForeColor = Color::White;
					}
					else {
						btn->BackColor = panel;
						btn->ForeColor = text;
					}
				}
				else if (dynamic_cast<TextBox^>(c) != nullptr) {
					TextBox^ tb = (TextBox^)c;
					tb->BackColor = panel;
					tb->ForeColor = text;
				}
				else if (dynamic_cast<ComboBox^>(c) != nullptr) {
					ComboBox^ cb = (ComboBox^)c;
					cb->BackColor = panel;
					cb->ForeColor = text;
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
					DataGridView^ dgv = (DataGridView^)c;
					dgv->BackgroundColor = panel;
					dgv->GridColor = DarkMode ? Color::FromArgb(64, 64, 64) : Color::FromArgb(220, 220, 220);
					dgv->DefaultCellStyle->BackColor = bg;
					dgv->DefaultCellStyle->ForeColor = text;
					dgv->ColumnHeadersDefaultCellStyle->BackColor = panel;
					dgv->ColumnHeadersDefaultCellStyle->ForeColor = text;
					dgv->EnableHeadersVisualStyles = false;
				}
				else if (dynamic_cast<Panel^>(c) != nullptr) {
					if (c->Size.Height <= 2) c->BackColor = DarkMode ? Color::FromArgb(58, 62, 65) : Color::FromArgb(230, 230, 230);
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
