#pragma once

namespace GameBoi
{
	class CPU;

	struct Instruction final
	{
		typedef void (CPU::*InstructionFunction)(uint16_t);

		Instruction(const char* disassembly, int32_t operandLength, int32_t cycles, InstructionFunction function) :
			Function(function), Disassebly(disassembly), OperandLength(operandLength), Cycles(cycles)
		{
		}

		InstructionFunction Function;
		const char* Disassebly; // String disassebly
		int32_t OperandLength; // Length of the operand of the instructions
		int32_t Cycles; // Number of CPU clock cycles the instruction takes
	};
}