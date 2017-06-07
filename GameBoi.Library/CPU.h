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

		void UnimplementedInstruction(uint16_t operand);

		#pragma region  8-Bit Loads

		// LD nn,n
		void LD_B_n(uint16_t operand);
		void LD_C_n(uint16_t operand);
		void LD_D_n(uint16_t operand);
		void LD_E_n(uint16_t operand);
		void LD_H_n(uint16_t operand);
		void LD_L_n(uint16_t operand);

		// LD r1,r2
		void LD_A_A(uint16_t operand);
		void LD_A_B(uint16_t operand);
		void LD_A_C(uint16_t operand);
		void LD_A_D(uint16_t operand);
		void LD_A_E(uint16_t operand);
		void LD_A_H(uint16_t operand);
		void LD_A_L(uint16_t operand);
		void LD_A_aHL(uint16_t operand);
		void LD_B_B(uint16_t operand);
		void LD_B_C(uint16_t operand);
		void LD_B_D(uint16_t operand);
		void LD_B_E(uint16_t operand);
		void LD_B_H(uint16_t operand);
		void LD_B_L(uint16_t operand);
		void LD_B_aHL(uint16_t operand);
		void LD_C_B(uint16_t operand);
		void LD_C_C(uint16_t operand);
		void LD_C_D(uint16_t operand);
		void LD_C_E(uint16_t operand);
		void LD_C_H(uint16_t operand);
		void LD_C_L(uint16_t operand);
		void LD_C_aHL(uint16_t operand);
		void LD_D_B(uint16_t operand);
		void LD_D_C(uint16_t operand);
		void LD_D_D(uint16_t operand);
		void LD_D_E(uint16_t operand);
		void LD_D_H(uint16_t operand);
		void LD_D_L(uint16_t operand);
		void LD_D_aHL(uint16_t operand);
		void LD_E_B(uint16_t operand);
		void LD_E_C(uint16_t operand);
		void LD_E_D(uint16_t operand);
		void LD_E_E(uint16_t operand);
		void LD_E_H(uint16_t operand);
		void LD_E_L(uint16_t operand);
		void LD_E_aHL(uint16_t operand);
		void LD_H_B(uint16_t operand);
		void LD_H_C(uint16_t operand);
		void LD_H_D(uint16_t operand);
		void LD_H_E(uint16_t operand);
		void LD_H_H(uint16_t operand);
		void LD_H_L(uint16_t operand);
		void LD_H_aHL(uint16_t operand);
		void LD_L_B(uint16_t operand);
		void LD_L_C(uint16_t operand);
		void LD_L_D(uint16_t operand);
		void LD_L_E(uint16_t operand);
		void LD_L_H(uint16_t operand);
		void LD_L_L(uint16_t operand);
		void LD_L_aHL(uint16_t operand);
		void LD_aHL_B(uint16_t operand);
		void LD_aHL_C(uint16_t operand);
		void LD_aHL_D(uint16_t operand);
		void LD_aHL_E(uint16_t operand);
		void LD_aHL_H(uint16_t operand);
		void LD_aHL_L(uint16_t operand);
		void LD_aHL_n(uint16_t operand);

		// LD A,n
		void LD_A_aBC(uint16_t operand);
		void LD_A_aDE(uint16_t operand);
		void LD_A_ann(uint16_t operand);
		void LD_A_n(uint16_t operand);

		// LD n,A
		void LD_B_A(uint16_t operand);
		void LD_C_A(uint16_t operand);
		void LD_D_A(uint16_t operand);
		void LD_E_A(uint16_t operand);
		void LD_H_A(uint16_t operand);
		void LD_L_A(uint16_t operand);
		void LD_aBC_A(uint16_t operand);
		void LD_aDE_A(uint16_t operand);
		void LD_aHL_A(uint16_t operand);
		void LD_ann_A(uint16_t operand);

		// LD A,(C) and reverse
		void LD_A_aC(uint16_t operand);
		void LD_aC_A(uint16_t operand);

		// LD A,(HL-/+) and variations
		void LDD_A_aHL(uint16_t operand);
		void LDD_aHL_A(uint16_t operand);
		void LDI_A_aHL(uint16_t operand);
		void LDI_aHL_A(uint16_t operand);

		// LDH (n),A and reverse
		void LD_an_A(uint16_t operand);
		void LD_A_an(uint16_t operand);

		#pragma endregion

		#pragma region Miscellaneous

		void NOP(uint16_t operand);

		#pragma endregion
	};
}