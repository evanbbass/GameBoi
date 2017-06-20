// Program.cpp : main project file.

#include "stdafx.h"
#include "MainWindow.h"
//#include "GameBoy.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GameBoiDebugger;
//using namespace GameBoi;

int main(array<System::String^>^)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	//GameBoy gameBoy;
	MainWindow form/*(gameBoy)*/;
	Application::Run(%form);
}
