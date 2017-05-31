// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include "MemoryMap.h"
#include "Registers.h"
#include "CPU.h"

using namespace std;
using namespace GameBoi;

int main(int argc, char* argv[])
{
	argc;
	argv;

	//Cartridge tetris("D:\\Users\\Evan\\Downloads\\Tetris (World).gb");
	//Cartridge red("D:\\Users\\Evan\\Downloads\\Pokemon - Red Version (USA, Europe).gb");
	//Cartridge gold("D:\\Users\\Evan\\Downloads\\Pokemon - Gold Version (USA, Europe).gbc");

	//Cartridge tetris("C:\\Users\\ebass\\Downloads\\GB ROMs\\Tetris (World).gb");
	//Cartridge red("C:\\Users\\ebass\\Downloads\\GB ROMs\\Pokemon - Red Version.gb");
	//Cartridge gold("C:\\Users\\ebass\\Downloads\\GB ROMs\\Pokemon - Gold Version.gbc");

	cout << "Found Opcodes:" << endl;
	vector<uint8_t> unmappedOpcodes;
	for (uint8_t opcode = 0; opcode < 0xFF; ++opcode)
	{
		try
		{
			cout << hex << "0x" << static_cast<int>(opcode) << ": " << CPU::GetDisassembly(opcode) << endl;
		}
		catch(...)
		{
			unmappedOpcodes.push_back(opcode);
		}
	}
	cout << 0xFF - unmappedOpcodes.size() << " total" << endl;

	cout << endl << "Unmapped Opcodes:" << endl;
	for (uint8_t opcode : unmappedOpcodes)
	{
		cout << hex << "0x" << static_cast<int>(opcode) << endl;
	}
	cout << unmappedOpcodes.size() << " total" << endl;

	return 0;
}
