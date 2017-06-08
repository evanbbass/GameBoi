// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "MemoryMap.h"
#include "Registers.h"
#include "CPU.h"
#include "GameBoy.h"

using namespace std;
using namespace GameBoi;

void PrintOpcodes();
void PrintOpcodeChartToFile(const string&);

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

	//Cartridge carazu("Z:\\FALL16-STUDENTS\\mholtkamp\\carazu.gb");
	//carazu.DisassebleRomToFile("carazu.dis", 0x0000, 0x8000);

	GameBoy gb("C:\\Users\\ebass\\Downloads\\GB ROMs\\Tetris (World).gb");
	CPU& gbCpu = gb.GetCPU();
	
	while (true)
	{
		try
		{
			gbCpu.StepCPU();
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
			return -1;
		}
	}

	return 0;
}

void PrintOpcodes()
{
	cout << "Found Opcodes:" << endl;
	vector<uint8_t> unmappedOpcodes;
	vector<uint8_t> unmappedOpcodes_PrefixCB;
	for (uint16_t i = 0; i < 0x100; ++i)
	{
		uint8_t opcode = static_cast<uint8_t>(i);
		if (opcode == 0xCB)
		{
			for (uint16_t j = 0; j < 0x100; ++j)
			{
				uint8_t operand = static_cast<uint8_t>(j);
				try
				{
					cout << hex << "0xcb " << static_cast<int>(operand) << ": " << CPU::GetDisassembly(opcode, operand) << endl;
				}
				catch (...)
				{
					unmappedOpcodes_PrefixCB.push_back(operand);
				}
			}
		}
		else
		{
			try
			{
				cout << hex << "0x" << static_cast<int>(opcode) << ": " << CPU::GetDisassembly(opcode) << endl;
			}
			catch (...)
			{
				unmappedOpcodes.push_back(opcode);
			}
		}
	}
	cout << dec << 0x200 - (unmappedOpcodes.size() + unmappedOpcodes_PrefixCB.size()) << " total" << endl;

	cout << endl << "Unmapped Opcodes:" << endl;
	for (uint8_t opcode : unmappedOpcodes)
	{
		cout << hex << "0x" << static_cast<int>(opcode) << endl;
	}
	cout << dec << (unmappedOpcodes.size() + unmappedOpcodes_PrefixCB.size()) << " total" << endl;
}

void PrintOpcodeChartToFile(const string& filename)
{
	ofstream csv(filename);

	if (csv.good())
	{
		csv << "Standard Instructions" << endl;
		csv << ";x0;x1;x2;x3;x4;x5;x6;x7;x8;x9;xA;xB;xC;xD;xE;xF" << endl;
		for (int i = 0; i <= 0xF; ++i)
		{
			csv << hex << uppercase << i << "x;";

			for (int j = 0; j <= 0xF; ++j)
			{
				uint8_t opcode = static_cast<uint8_t>((i << 4) | j);
				if (opcode == 0xCB)
				{
					csv << "PREFIX CB";
				}
				else
				{
					try
					{
						csv << CPU::GetDisassembly(opcode);
					}
					catch (...)
					{
						
					}
				}

				csv << ";";
			}

			csv << endl;
		}

		csv << endl;
		csv << "Extended Instructions (PREFIX CB)" << endl;
		csv << ";x0;x1;x2;x3;x4;x5;x6;x7;x8;x9;xA;xB;xC;xD;xE;xF" << endl;
		for (int i = 0; i <= 0xF; ++i)
		{
			csv << hex << uppercase << i << "x;";

			for (int j = 0; j <= 0xF; ++j)
			{
				uint8_t operand = static_cast<uint8_t>((i << 4) | j);
				try
				{
					csv << CPU::GetDisassembly(0xCB, operand);
				}
				catch (...)
				{

				}

				csv << ";";
			}

			csv << endl;
		}
	}
}