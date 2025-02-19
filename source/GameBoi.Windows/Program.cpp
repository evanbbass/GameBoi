// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "GameBoyWindows.h"

using namespace GameBoiWindows;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
	if (__argc <= 1)
	{
		if (MessageBoxA(nullptr, "Please specify a .gb file", "Error!", MB_OK) == IDOK)
		{
			return -1;
		}
	}

	std::string cartridgeFileName = __argv[1];
	std::unique_ptr<GameBoyWindows> gb = std::make_unique<GameBoyWindows>(cartridgeFileName);
	gb->Run();

	return 0;
}
