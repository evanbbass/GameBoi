// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include "Memory.h"

using namespace std;

int main(int argc, char* argv[])
{
	argc;
	argv;

	cout << "Size of Cartridge: 0x" << hex << sizeof(GameBoi::Cartridge) << endl;
	cout << "Size of Memory: 0x" << hex << sizeof(GameBoi::Memory) << endl;

	return 0;
}
