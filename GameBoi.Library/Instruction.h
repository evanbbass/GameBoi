#pragma once
#include <string>

namespace GameBoi
{
	struct Instruction
	{
		const char* Disassebly; // String disassebly
		int32_t OperandLength; // Length of the operand of the instructions
		int32_t Cycles; // Number of CPU clock cycles the instruction takes
	};
}