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

		void PushWordToStack(uint16_t value);
		uint16_t PopWordFromStack();

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

		#pragma region 16-Bit Loads

		// LD n,nn
		void LD_BC_nn(uint16_t operand);
		void LD_DE_nn(uint16_t operand);
		void LD_HL_nn(uint16_t operand);
		void LD_SP_nn(uint16_t operand);

		// LD SP,HL
		void LD_SP_HL(uint16_t operand);

		// LD HL,SP+n
		void LD_HL_SP_n(uint16_t operand);

		// LD (nn),SP
		void LD_ann_SP(uint16_t operand);

		// PUSH nn
		void PUSH_AF(uint16_t operand);
		void PUSH_BC(uint16_t operand);
		void PUSH_DE(uint16_t operand);
		void PUSH_HL(uint16_t operand);

		// POP nn
		void POP_AF(uint16_t operand);
		void POP_BC(uint16_t operand);
		void POP_DE(uint16_t operand);
		void POP_HL(uint16_t operand);

		#pragma endregion

		#pragma region 8-bit ALU

		// ADD A,n
		void ADD_A_A(uint16_t operand);
		void ADD_A_B(uint16_t operand);
		void ADD_A_C(uint16_t operand);
		void ADD_A_D(uint16_t operand);
		void ADD_A_E(uint16_t operand);
		void ADD_A_H(uint16_t operand);
		void ADD_A_L(uint16_t operand);
		void ADD_A_aHL(uint16_t operand);
		void ADD_A_n(uint16_t operand);

		// ADC A,n
		void ADC_A_A(uint16_t operand);
		void ADC_A_B(uint16_t operand);
		void ADC_A_C(uint16_t operand);
		void ADC_A_D(uint16_t operand);
		void ADC_A_E(uint16_t operand);
		void ADC_A_H(uint16_t operand);
		void ADC_A_L(uint16_t operand);
		void ADC_A_aHL(uint16_t operand);
		void ADC_A_n(uint16_t operand);

		// SUB n
		void SUB_A(uint16_t operand);
		void SUB_B(uint16_t operand);
		void SUB_C(uint16_t operand);
		void SUB_D(uint16_t operand);
		void SUB_E(uint16_t operand);
		void SUB_H(uint16_t operand);
		void SUB_L(uint16_t operand);
		void SUB_aHL(uint16_t operand);
		void SUB_n(uint16_t operand);

		// ADC A,n
		void SBC_A_A(uint16_t operand);
		void SBC_A_B(uint16_t operand);
		void SBC_A_C(uint16_t operand);
		void SBC_A_D(uint16_t operand);
		void SBC_A_E(uint16_t operand);
		void SBC_A_H(uint16_t operand);
		void SBC_A_L(uint16_t operand);
		void SBC_A_aHL(uint16_t operand);
		void SBC_A_n(uint16_t operand);

		// AND n
		void AND_A(uint16_t operand);
		void AND_B(uint16_t operand);
		void AND_C(uint16_t operand);
		void AND_D(uint16_t operand);
		void AND_E(uint16_t operand);
		void AND_H(uint16_t operand);
		void AND_L(uint16_t operand);
		void AND_aHL(uint16_t operand);
		void AND_n(uint16_t operand);

		// OR n
		void OR_A(uint16_t operand);
		void OR_B(uint16_t operand);
		void OR_C(uint16_t operand);
		void OR_D(uint16_t operand);
		void OR_E(uint16_t operand);
		void OR_H(uint16_t operand);
		void OR_L(uint16_t operand);
		void OR_aHL(uint16_t operand);
		void OR_n(uint16_t operand);

		// XOR n
		void XOR_A(uint16_t operand);
		void XOR_B(uint16_t operand);
		void XOR_C(uint16_t operand);
		void XOR_D(uint16_t operand);
		void XOR_E(uint16_t operand);
		void XOR_H(uint16_t operand);
		void XOR_L(uint16_t operand);
		void XOR_aHL(uint16_t operand);
		void XOR_n(uint16_t operand);

		// CP n
		void CP_A(uint16_t operand);
		void CP_B(uint16_t operand);
		void CP_C(uint16_t operand);
		void CP_D(uint16_t operand);
		void CP_E(uint16_t operand);
		void CP_H(uint16_t operand);
		void CP_L(uint16_t operand);
		void CP_aHL(uint16_t operand);
		void CP_n(uint16_t operand);

		// INC n
		void INC_A(uint16_t operand);
		void INC_B(uint16_t operand);
		void INC_C(uint16_t operand);
		void INC_D(uint16_t operand);
		void INC_E(uint16_t operand);
		void INC_H(uint16_t operand);
		void INC_L(uint16_t operand);
		void INC_aHL(uint16_t operand);

		// DEC n
		void DEC_A(uint16_t operand);
		void DEC_B(uint16_t operand);
		void DEC_C(uint16_t operand);
		void DEC_D(uint16_t operand);
		void DEC_E(uint16_t operand);
		void DEC_H(uint16_t operand);
		void DEC_L(uint16_t operand);
		void DEC_aHL(uint16_t operand);

		#pragma endregion

		#pragma region Miscellaneous

		void NOP(uint16_t operand);

		#pragma endregion
	};
}
