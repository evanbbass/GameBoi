#pragma once

#include "CPU.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void PrintOpcodes()
{
	std::cout << "Found Opcodes:" << std::endl;
	std::vector<uint8_t> unmappedOpcodes;
	std::vector<uint8_t> unmappedOpcodes_PrefixCB;
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
					std::cout << std::hex << "0xcb " << static_cast<int>(operand) << ": " << GameBoi::CPU::GetDisassembly(opcode, operand) << std::endl;
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
				std::cout << std::hex << "0x" << static_cast<int>(opcode) << ": " << GameBoi::CPU::GetDisassembly(opcode) << std::endl;
			}
			catch (...)
			{
				unmappedOpcodes.push_back(opcode);
			}
		}
	}
	std::cout << std::dec << 0x200 - (unmappedOpcodes.size() + unmappedOpcodes_PrefixCB.size()) << " total" << std::endl;

	std::cout << std::endl << "Unmapped Opcodes:" << std::endl;
	for (uint8_t opcode : unmappedOpcodes)
	{
		std::cout << std::hex << "0x" << static_cast<int>(opcode) << std::endl;
	}
	std::cout << std::dec << (unmappedOpcodes.size() + unmappedOpcodes_PrefixCB.size()) << " total" << std::endl;
}

void PrintOpcodeChartToFile(const std::string& filename)
{
	std::ofstream csv(filename);

	if (csv.good())
	{
		csv << "Standard Instructions" << std::endl;
		csv << ";x0;x1;x2;x3;x4;x5;x6;x7;x8;x9;xA;xB;xC;xD;xE;xF" << std::endl;
		for (int i = 0; i <= 0xF; ++i)
		{
			csv << std::hex << std::uppercase << i << "x;";

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
						csv << GameBoi::CPU::GetDisassembly(opcode);
					}
					catch (...)
					{

					}
				}

				csv << ";";
			}

			csv << std::endl;
		}

		csv << std::endl;
		csv << "Extended Instructions (PREFIX CB)" << std::endl;
		csv << ";x0;x1;x2;x3;x4;x5;x6;x7;x8;x9;xA;xB;xC;xD;xE;xF" << std::endl;
		for (int i = 0; i <= 0xF; ++i)
		{
			csv << std::hex << std::uppercase << i << "x;";

			for (int j = 0; j <= 0xF; ++j)
			{
				uint8_t operand = static_cast<uint8_t>((i << 4) | j);
				try
				{
					csv << GameBoi::CPU::GetDisassembly(0xCB, operand);
				}
				catch (...)
				{

				}

				csv << ";";
			}

			csv << std::endl;
		}
	}
}