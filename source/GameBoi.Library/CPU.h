#pragma once

#include "MemoryMap.h"
#include "Registers.h"
#include "Instruction.h"
#include <map>

namespace GameBoiLibraryTest
{
	class TestCPUInstructions;
}

namespace GameBoi
{
	class CPU final
	{
		friend class GameBoiLibraryTest::TestCPUInstructions;

	public:
		explicit CPU(MemoryMap& memory);

		int32_t StepCPU();

		void Reset();

		Registers& GetRegisters();
		const Registers& GetRegisters() const;
		MemoryMap& GetMemoryMap();
		const MemoryMap& GetMemoryMap() const;

		bool GetInterruptMasterEnabled() const;
		uint8_t GetInterruptEnabledRegister() const;
		uint8_t GetInterruptFlagRegister() const;

		static int32_t GetOperandLength(uint8_t opcode);
		static std::string GetDisassembly(uint8_t opcode, uint16_t operand = 0);

		static const int32_t CPUClockSpeed = 4194304; // Hz

	private:
		Registers mRegisters;
		MemoryMap& mMemory;
		bool mInterruptMasterEnabled;
		bool mHalted;
		bool mEnableInterruptsAfterNextInstruction;
		bool mDisableInterruptsAfterNextInstruction;

		static const std::map<uint8_t, Instruction> OpcodeInstructionMap;
		static const std::map<uint8_t, Instruction> OpcodeInstructionMap_PrefixCB;

		void HandleInterrupts();

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
		void LDH_an_A(uint16_t operand);
		void LDH_A_an(uint16_t operand);

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

		#pragma region 8-Bit ALU

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

		#pragma region 16-Bit Arithmetic

		// ADD HL,n
		void ADD_HL_BC(uint16_t operand);
		void ADD_HL_DE(uint16_t operand);
		void ADD_HL_HL(uint16_t operand);
		void ADD_HL_SP(uint16_t operand);

		// ADD SP,n
		void ADD_SP_n(uint16_t operand);

		// INC nn
		void INC_BC(uint16_t operand);
		void INC_DE(uint16_t operand);
		void INC_HL(uint16_t operand);
		void INC_SP(uint16_t operand);

		// DEC nn
		void DEC_BC(uint16_t operand);
		void DEC_DE(uint16_t operand);
		void DEC_HL(uint16_t operand);
		void DEC_SP(uint16_t operand);

		#pragma endregion

		#pragma region Miscellaneous

		// SWAP n
		void SWAP_A(uint16_t operand);
		void SWAP_B(uint16_t operand);
		void SWAP_C(uint16_t operand);
		void SWAP_D(uint16_t operand);
		void SWAP_E(uint16_t operand);
		void SWAP_H(uint16_t operand);
		void SWAP_L(uint16_t operand);
		void SWAP_aHL(uint16_t operand);

		// DAA
		void DAA(uint16_t operand);

		// CPL
		void CPL(uint16_t operand);

		// CCF
		void CCF(uint16_t operand);

		// SCF
		void SCF(uint16_t operand);

		// NOP
		void NOP(uint16_t operand);

		// HALT
		void HALT(uint16_t operand);

		// STOP
		void STOP(uint16_t operand);

		// Interrupts
		void DI(uint16_t operand);
		void EI(uint16_t operand);

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate A
		void RLCA(uint16_t operand);
		void RLA(uint16_t operand);
		void RRCA(uint16_t operand);
		void RRA(uint16_t operand);

		// RLC n
		void RLC_A(uint16_t operand);
		void RLC_B(uint16_t operand);
		void RLC_C(uint16_t operand);
		void RLC_D(uint16_t operand);
		void RLC_E(uint16_t operand);
		void RLC_H(uint16_t operand);
		void RLC_L(uint16_t operand);
		void RLC_aHL(uint16_t operand);

		// RL n
		void RL_A(uint16_t operand);
		void RL_B(uint16_t operand);
		void RL_C(uint16_t operand);
		void RL_D(uint16_t operand);
		void RL_E(uint16_t operand);
		void RL_H(uint16_t operand);
		void RL_L(uint16_t operand);
		void RL_aHL(uint16_t operand);

		// RRC n
		void RRC_A(uint16_t operand);
		void RRC_B(uint16_t operand);
		void RRC_C(uint16_t operand);
		void RRC_D(uint16_t operand);
		void RRC_E(uint16_t operand);
		void RRC_H(uint16_t operand);
		void RRC_L(uint16_t operand);
		void RRC_aHL(uint16_t operand);

		// RR n
		void RR_A(uint16_t operand);
		void RR_B(uint16_t operand);
		void RR_C(uint16_t operand);
		void RR_D(uint16_t operand);
		void RR_E(uint16_t operand);
		void RR_H(uint16_t operand);
		void RR_L(uint16_t operand);
		void RR_aHL(uint16_t operand);

		// SLA n
		void SLA_A(uint16_t operand);
		void SLA_B(uint16_t operand);
		void SLA_C(uint16_t operand);
		void SLA_D(uint16_t operand);
		void SLA_E(uint16_t operand);
		void SLA_H(uint16_t operand);
		void SLA_L(uint16_t operand);
		void SLA_aHL(uint16_t operand);

		// SRA n
		void SRA_A(uint16_t operand);
		void SRA_B(uint16_t operand);
		void SRA_C(uint16_t operand);
		void SRA_D(uint16_t operand);
		void SRA_E(uint16_t operand);
		void SRA_H(uint16_t operand);
		void SRA_L(uint16_t operand);
		void SRA_aHL(uint16_t operand);

		// SRL n
		void SRL_A(uint16_t operand);
		void SRL_B(uint16_t operand);
		void SRL_C(uint16_t operand);
		void SRL_D(uint16_t operand);
		void SRL_E(uint16_t operand);
		void SRL_H(uint16_t operand);
		void SRL_L(uint16_t operand);
		void SRL_aHL(uint16_t operand);

		#pragma endregion

		#pragma region Bit Opcodes

		// BIT b,r
		void BIT_0_A(uint16_t operand);
		void BIT_1_A(uint16_t operand);
		void BIT_2_A(uint16_t operand);
		void BIT_3_A(uint16_t operand);
		void BIT_4_A(uint16_t operand);
		void BIT_5_A(uint16_t operand);
		void BIT_6_A(uint16_t operand);
		void BIT_7_A(uint16_t operand);
		void BIT_0_B(uint16_t operand);
		void BIT_1_B(uint16_t operand);
		void BIT_2_B(uint16_t operand);
		void BIT_3_B(uint16_t operand);
		void BIT_4_B(uint16_t operand);
		void BIT_5_B(uint16_t operand);
		void BIT_6_B(uint16_t operand);
		void BIT_7_B(uint16_t operand);
		void BIT_0_C(uint16_t operand);
		void BIT_1_C(uint16_t operand);
		void BIT_2_C(uint16_t operand);
		void BIT_3_C(uint16_t operand);
		void BIT_4_C(uint16_t operand);
		void BIT_5_C(uint16_t operand);
		void BIT_6_C(uint16_t operand);
		void BIT_7_C(uint16_t operand);
		void BIT_0_D(uint16_t operand);
		void BIT_1_D(uint16_t operand);
		void BIT_2_D(uint16_t operand);
		void BIT_3_D(uint16_t operand);
		void BIT_4_D(uint16_t operand);
		void BIT_5_D(uint16_t operand);
		void BIT_6_D(uint16_t operand);
		void BIT_7_D(uint16_t operand);
		void BIT_0_E(uint16_t operand);
		void BIT_1_E(uint16_t operand);
		void BIT_2_E(uint16_t operand);
		void BIT_3_E(uint16_t operand);
		void BIT_4_E(uint16_t operand);
		void BIT_5_E(uint16_t operand);
		void BIT_6_E(uint16_t operand);
		void BIT_7_E(uint16_t operand);
		void BIT_0_H(uint16_t operand);
		void BIT_1_H(uint16_t operand);
		void BIT_2_H(uint16_t operand);
		void BIT_3_H(uint16_t operand);
		void BIT_4_H(uint16_t operand);
		void BIT_5_H(uint16_t operand);
		void BIT_6_H(uint16_t operand);
		void BIT_7_H(uint16_t operand);
		void BIT_0_L(uint16_t operand);
		void BIT_1_L(uint16_t operand);
		void BIT_2_L(uint16_t operand);
		void BIT_3_L(uint16_t operand);
		void BIT_4_L(uint16_t operand);
		void BIT_5_L(uint16_t operand);
		void BIT_6_L(uint16_t operand);
		void BIT_7_L(uint16_t operand);
		void BIT_0_aHL(uint16_t operand);
		void BIT_1_aHL(uint16_t operand);
		void BIT_2_aHL(uint16_t operand);
		void BIT_3_aHL(uint16_t operand);
		void BIT_4_aHL(uint16_t operand);
		void BIT_5_aHL(uint16_t operand);
		void BIT_6_aHL(uint16_t operand);
		void BIT_7_aHL(uint16_t operand);

		// SET b,r
		void SET_0_A(uint16_t operand);
		void SET_1_A(uint16_t operand);
		void SET_2_A(uint16_t operand);
		void SET_3_A(uint16_t operand);
		void SET_4_A(uint16_t operand);
		void SET_5_A(uint16_t operand);
		void SET_6_A(uint16_t operand);
		void SET_7_A(uint16_t operand);
		void SET_0_B(uint16_t operand);
		void SET_1_B(uint16_t operand);
		void SET_2_B(uint16_t operand);
		void SET_3_B(uint16_t operand);
		void SET_4_B(uint16_t operand);
		void SET_5_B(uint16_t operand);
		void SET_6_B(uint16_t operand);
		void SET_7_B(uint16_t operand);
		void SET_0_C(uint16_t operand);
		void SET_1_C(uint16_t operand);
		void SET_2_C(uint16_t operand);
		void SET_3_C(uint16_t operand);
		void SET_4_C(uint16_t operand);
		void SET_5_C(uint16_t operand);
		void SET_6_C(uint16_t operand);
		void SET_7_C(uint16_t operand);
		void SET_0_D(uint16_t operand);
		void SET_1_D(uint16_t operand);
		void SET_2_D(uint16_t operand);
		void SET_3_D(uint16_t operand);
		void SET_4_D(uint16_t operand);
		void SET_5_D(uint16_t operand);
		void SET_6_D(uint16_t operand);
		void SET_7_D(uint16_t operand);
		void SET_0_E(uint16_t operand);
		void SET_1_E(uint16_t operand);
		void SET_2_E(uint16_t operand);
		void SET_3_E(uint16_t operand);
		void SET_4_E(uint16_t operand);
		void SET_5_E(uint16_t operand);
		void SET_6_E(uint16_t operand);
		void SET_7_E(uint16_t operand);
		void SET_0_H(uint16_t operand);
		void SET_1_H(uint16_t operand);
		void SET_2_H(uint16_t operand);
		void SET_3_H(uint16_t operand);
		void SET_4_H(uint16_t operand);
		void SET_5_H(uint16_t operand);
		void SET_6_H(uint16_t operand);
		void SET_7_H(uint16_t operand);
		void SET_0_L(uint16_t operand);
		void SET_1_L(uint16_t operand);
		void SET_2_L(uint16_t operand);
		void SET_3_L(uint16_t operand);
		void SET_4_L(uint16_t operand);
		void SET_5_L(uint16_t operand);
		void SET_6_L(uint16_t operand);
		void SET_7_L(uint16_t operand);
		void SET_0_aHL(uint16_t operand);
		void SET_1_aHL(uint16_t operand);
		void SET_2_aHL(uint16_t operand);
		void SET_3_aHL(uint16_t operand);
		void SET_4_aHL(uint16_t operand);
		void SET_5_aHL(uint16_t operand);
		void SET_6_aHL(uint16_t operand);
		void SET_7_aHL(uint16_t operand);

		// RES b,r
		void RES_0_A(uint16_t operand);
		void RES_1_A(uint16_t operand);
		void RES_2_A(uint16_t operand);
		void RES_3_A(uint16_t operand);
		void RES_4_A(uint16_t operand);
		void RES_5_A(uint16_t operand);
		void RES_6_A(uint16_t operand);
		void RES_7_A(uint16_t operand);
		void RES_0_B(uint16_t operand);
		void RES_1_B(uint16_t operand);
		void RES_2_B(uint16_t operand);
		void RES_3_B(uint16_t operand);
		void RES_4_B(uint16_t operand);
		void RES_5_B(uint16_t operand);
		void RES_6_B(uint16_t operand);
		void RES_7_B(uint16_t operand);
		void RES_0_C(uint16_t operand);
		void RES_1_C(uint16_t operand);
		void RES_2_C(uint16_t operand);
		void RES_3_C(uint16_t operand);
		void RES_4_C(uint16_t operand);
		void RES_5_C(uint16_t operand);
		void RES_6_C(uint16_t operand);
		void RES_7_C(uint16_t operand);
		void RES_0_D(uint16_t operand);
		void RES_1_D(uint16_t operand);
		void RES_2_D(uint16_t operand);
		void RES_3_D(uint16_t operand);
		void RES_4_D(uint16_t operand);
		void RES_5_D(uint16_t operand);
		void RES_6_D(uint16_t operand);
		void RES_7_D(uint16_t operand);
		void RES_0_E(uint16_t operand);
		void RES_1_E(uint16_t operand);
		void RES_2_E(uint16_t operand);
		void RES_3_E(uint16_t operand);
		void RES_4_E(uint16_t operand);
		void RES_5_E(uint16_t operand);
		void RES_6_E(uint16_t operand);
		void RES_7_E(uint16_t operand);
		void RES_0_H(uint16_t operand);
		void RES_1_H(uint16_t operand);
		void RES_2_H(uint16_t operand);
		void RES_3_H(uint16_t operand);
		void RES_4_H(uint16_t operand);
		void RES_5_H(uint16_t operand);
		void RES_6_H(uint16_t operand);
		void RES_7_H(uint16_t operand);
		void RES_0_L(uint16_t operand);
		void RES_1_L(uint16_t operand);
		void RES_2_L(uint16_t operand);
		void RES_3_L(uint16_t operand);
		void RES_4_L(uint16_t operand);
		void RES_5_L(uint16_t operand);
		void RES_6_L(uint16_t operand);
		void RES_7_L(uint16_t operand);
		void RES_0_aHL(uint16_t operand);
		void RES_1_aHL(uint16_t operand);
		void RES_2_aHL(uint16_t operand);
		void RES_3_aHL(uint16_t operand);
		void RES_4_aHL(uint16_t operand);
		void RES_5_aHL(uint16_t operand);
		void RES_6_aHL(uint16_t operand);
		void RES_7_aHL(uint16_t operand);

		#pragma endregion

		#pragma region Jumps

		// JP nn
		void JP_nn(uint16_t operand);

		// JP cc,nn
		void JP_NZ_nn(uint16_t operand);
		void JP_Z_nn(uint16_t operand);
		void JP_NC_nn(uint16_t operand);
		void JP_C_nn(uint16_t operand);

		// JP (HL)
		void JP_aHL(uint16_t operand);

		// JR n
		void JR_n(uint16_t operand);

		// JR cc,n
		void JR_NZ_n(uint16_t operand);
		void JR_Z_n(uint16_t operand);
		void JR_NC_n(uint16_t operand);
		void JR_C_n(uint16_t operand);

		#pragma endregion

		#pragma region Calls

		// CALL nn
		void CALL_nn(uint16_t operand);

		// CALL cc,nn
		void CALL_NZ_nn(uint16_t operand);
		void CALL_Z_nn(uint16_t operand);
		void CALL_NC_nn(uint16_t operand);
		void CALL_C_nn(uint16_t operand);

		#pragma endregion

		#pragma region Restarts

		// RST n
		void RST_00(uint16_t operand);
		void RST_08(uint16_t operand);
		void RST_10(uint16_t operand);
		void RST_18(uint16_t operand);
		void RST_20(uint16_t operand);
		void RST_28(uint16_t operand);
		void RST_30(uint16_t operand);
		void RST_38(uint16_t operand);

		#pragma endregion

		#pragma region Returns

		// RET
		void RET(uint16_t operand);

		// RET cc
		void RET_NZ(uint16_t operand);
		void RET_Z(uint16_t operand);
		void RET_NC(uint16_t operand);
		void RET_C(uint16_t operand);

		// RETI
		void RETI(uint16_t operand);

		#pragma endregion
	};
}
