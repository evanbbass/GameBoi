#pragma once
#include <string>

namespace GameBoi
{
	struct Instruction
	{
		const char* Disassebly;
		int32_t OperandLength;
		int32_t Cycles;
	};
}