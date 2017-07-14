// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "GameBoyWindows.h"

using namespace std;
using namespace GameBoiWindows;

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		if (MessageBoxA(nullptr, "Please specify a .gb file", "Error!", MB_OK) == IDOK)
		{
			return -1;
		}
	}

	string cartridgeFileName = argv[1];
	GameBoyWindows gb(cartridgeFileName);
	gb.Run();

	return 0;
}
