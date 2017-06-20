#include "stdafx.h"
#include "MainWindow.h"

using namespace System;
using namespace Text::RegularExpressions;

namespace GameBoiDebugger {

	Void MainWindow::textBoxReg_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		sender;
		String^ character;
		character += e->KeyChar;
		String^ regex = L"[0-9a-fA-F]";

		if (Char::IsControl(e->KeyChar) || Regex::IsMatch(character, regex))
		{
			e->Handled = false;
		}
		else
		{
			e->Handled = true;
		}
	}
}