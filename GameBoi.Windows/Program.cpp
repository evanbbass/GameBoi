// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include "MemoryMap.h"
#include "Registers.h"

using namespace std;
using namespace GameBoi;

int main(int argc, char* argv[])
{
	argc;
	argv;

	//Cartridge tetris("D:\\Users\\Evan\\Downloads\\Tetris (World).gb");
	//Cartridge red("D:\\Users\\Evan\\Downloads\\Pokemon - Red Version (USA, Europe).gb");
	//Cartridge gold("D:\\Users\\Evan\\Downloads\\Pokemon - Gold Version (USA, Europe).gbc");

	Cartridge tetris("C:\\Users\\ebass\\Downloads\\GB ROMs\\Tetris (World).gb");
	Cartridge red("C:\\Users\\ebass\\Downloads\\GB ROMs\\Pokemon - Red Version.gb");
	Cartridge gold("C:\\Users\\ebass\\Downloads\\GB ROMs\\Pokemon - Gold Version.gbc");

	return 0;
}
