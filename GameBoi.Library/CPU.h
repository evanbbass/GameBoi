#pragma once
#include "MemoryMap.h"
#include "Registers.h"
#include "Instruction.h"
#include <map>

namespace GameBoi
{
	class CPU
	{
	public:
		explicit CPU(MemoryMap& memory);
		~CPU() = default;

		void StepCPU();

		void Reset();

		Registers& GetRegisters();
		const Registers& GetRegisters() const;
		MemoryMap& GetMemoryMap();
		const MemoryMap& GetMemoryMap() const;

		static int32_t GetOperandLength(uint8_t opcode);
		static std::string GetDisassembly(uint8_t opcode, uint16_t operand = 0);

	private:
		Registers mRegisters;
		MemoryMap& mMemory;

		static const std::map<uint8_t, Instruction> sOpcodeDisassembly;
		static const std::map<uint8_t, Instruction> sOpcodeDisassembly_PrefixCB;

		#pragma region  8-Bit Loads
		void LD_B_n(uint8_t value);
		void LD_C_n(uint8_t value);
		void LD_D_n(uint8_t value);
		void LD_E_n(uint8_t value);
		void LD_H_n(uint8_t value);
		void LD_L_n(uint8_t value);
		#pragma endregion
	};
}