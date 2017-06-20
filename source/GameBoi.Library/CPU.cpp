#include "pch.h"
#include "CPU.h"

using namespace std;

namespace GameBoi
{
	const map<uint8_t, Instruction> CPU::sOpcodeDisassembly
	{
		#pragma region 8-bit Loads

		// LD nn,n
		{ 0x06, { "LD   B,$%02X", 1, 8, &LD_B_n } }, // e.g. LD B,$AB
		{ 0x0E, { "LD   C,$%02X", 1, 8, &LD_C_n } }, // e.g. LD C,$AB
		{ 0x16, { "LD   D,$%02X", 1, 8, &LD_D_n } }, // e.g. LD D,$AB
		{ 0x1E, { "LD   E,$%02X", 1, 8, &LD_E_n } }, // e.g. LD E,$AB
		{ 0x26, { "LD   H,$%02X", 1, 8, &LD_H_n } }, // e.g. LD H,$AB
		{ 0x2E, { "LD   L,$%02X", 1, 8, &LD_L_n } }, // e.g. LD L,$AB

		// LD r1,r2
		{ 0x7F, { "LD   A,A", 0, 4, &LD_A_A } },
		{ 0x78, { "LD   A,B", 0, 4, &LD_A_B } },
		{ 0x79, { "LD   A,C", 0, 4, &LD_A_C } },
		{ 0x7A, { "LD   A,D", 0, 4, &LD_A_D } },
		{ 0x7B, { "LD   A,E", 0, 4, &LD_A_E } },
		{ 0x7C, { "LD   A,H", 0, 4, &LD_A_H } },
		{ 0x7D, { "LD   A,L", 0, 4, &LD_A_L } },
		{ 0x7E, { "LD   A,(HL)", 0, 8, &LD_A_aHL } },
		{ 0x40, { "LD   B,B", 0, 4, &LD_B_B } },
		{ 0x41, { "LD   B,C", 0, 4, &LD_B_C } },
		{ 0x42, { "LD   B,D", 0, 4, &LD_B_D } },
		{ 0x43, { "LD   B,E", 0, 4, &LD_B_E } },
		{ 0x44, { "LD   B,H", 0, 4, &LD_B_H } },
		{ 0x45, { "LD   B,L", 0, 4, &LD_B_L } },
		{ 0x46, { "LD   B,(HL)", 0, 8, &LD_B_aHL } },
		{ 0x48, { "LD   C,B", 0, 4, &LD_C_B } },
		{ 0x49, { "LD   C,C", 0, 4, &LD_C_C } },
		{ 0x4A, { "LD   C,D", 0, 4, &LD_C_D } },
		{ 0x4B, { "LD   C,E", 0, 4, &LD_C_E } },
		{ 0x4C, { "LD   C,H", 0, 4, &LD_C_H } },
		{ 0x4D, { "LD   C,L", 0, 4, &LD_C_L } },
		{ 0x4E, { "LD   C,(HL)", 0, 8, &LD_C_aHL } },
		{ 0x50, { "LD   D,B", 0, 4, &LD_D_B } },
		{ 0x51, { "LD   D,C", 0, 4, &LD_D_C } },
		{ 0x52, { "LD   D,D", 0, 4, &LD_D_D } },
		{ 0x53, { "LD   D,E", 0, 4, &LD_D_E } },
		{ 0x54, { "LD   D,H", 0, 4, &LD_D_H } },
		{ 0x55, { "LD   D,L", 0, 4, &LD_D_L } },
		{ 0x56, { "LD   D,(HL)", 0, 8, &LD_D_aHL } },
		{ 0x58, { "LD   E,B", 0, 4, &LD_E_B } },
		{ 0x59, { "LD   E,C", 0, 4, &LD_E_C } },
		{ 0x5A, { "LD   E,D", 0, 4, &LD_E_D } },
		{ 0x5B, { "LD   E,E", 0, 4, &LD_E_E } },
		{ 0x5C, { "LD   E,H", 0, 4, &LD_E_H } },
		{ 0x5D, { "LD   E,L", 0, 4, &LD_E_L } },
		{ 0x5E, { "LD   E,(HL)", 0, 8, &LD_E_aHL } },
		{ 0x60, { "LD   H,B", 0, 4, &LD_H_B } },
		{ 0x61, { "LD   H,C", 0, 4, &LD_H_C } },
		{ 0x62, { "LD   H,D", 0, 4, &LD_H_D } },
		{ 0x63, { "LD   H,E", 0, 4, &LD_H_E } },
		{ 0x64, { "LD   H,H", 0, 4, &LD_H_H } },
		{ 0x65, { "LD   H,L", 0, 4, &LD_H_L } },
		{ 0x66, { "LD   H,(HL)", 0, 8, &LD_H_aHL } },
		{ 0x68, { "LD   L,B", 0, 4, &LD_L_B } },
		{ 0x69, { "LD   L,C", 0, 4, &LD_L_C } },
		{ 0x6A, { "LD   L,D", 0, 4, &LD_L_D } },
		{ 0x6B, { "LD   L,E", 0, 4, &LD_L_E } },
		{ 0x6C, { "LD   L,H", 0, 4, &LD_L_H } },
		{ 0x6D, { "LD   L,L", 0, 4, &LD_L_L } },
		{ 0x6E, { "LD   L,(HL)", 0, 8, &LD_L_aHL } },
		{ 0x70, { "LD   (HL),B", 0, 8, &LD_aHL_B } },
		{ 0x71, { "LD   (HL),C", 0, 8, &LD_aHL_C } },
		{ 0x72, { "LD   (HL),D", 0, 8, &LD_aHL_D } },
		{ 0x73, { "LD   (HL),E", 0, 8, &LD_aHL_E } },
		{ 0x74, { "LD   (HL),H", 0, 8, &LD_aHL_H } },
		{ 0x75, { "LD   (HL),L", 0, 8, &LD_aHL_L } },
		{ 0x36, { "LD   (HL),$%02X", 1, 12, &LD_aHL_n } }, // e.g. LD (HL),$BC

		// LD A,n
		//{ 0x7F, { "LD   A,A", 0, 4, &LD_A_A } },
		//{ 0x78, { "LD   A,B", 0, 4, &LD_A_B } },
		//{ 0x79, { "LD   A,C", 0, 4, &LD_A_C } },
		//{ 0x7A, { "LD   A,D", 0, 4, &LD_A_D } },
		//{ 0x7B, { "LD   A,E", 0, 4, &LD_A_E } },
		//{ 0x7C, { "LD   A,H", 0, 4, &LD_A_H } },
		//{ 0x7D, { "LD   A,L", 0, 4, &LD_A_L } },
		{ 0x0A, { "LD   A,(BC)", 0, 8, &LD_A_aBC } },
		{ 0x1A, { "LD   A,(DE)", 0, 8, &LD_A_aDE } },
		//{ 0x7E, { "LD   A,(HL)", 0, 8, &LD_A_aHL } },
		{ 0xFA, { "LD   A,($%04X)", 2, 16, &LD_A_ann } }, // e.g. LD A,($1234)
		{ 0x3E, { "LD   A,$%02X", 1, 8, &LD_A_n } }, // e.g. LD A,$AB

		// LD n,A
		//{ 0x7F, { "LD  A,A", 0, 4, &LD_A_A } },
		{ 0x47, { "LD   B,A", 0, 4, &LD_B_A } },
		{ 0x4F, { "LD   C,A", 0, 4, &LD_C_A } },
		{ 0x57, { "LD   D,A", 0, 4, &LD_D_A } },
		{ 0x5F, { "LD   E,A", 0, 4, &LD_E_A } },
		{ 0x67, { "LD   H,A", 0, 4, &LD_H_A } },
		{ 0x6F, { "LD   L,A", 0, 4, &LD_L_A } },
		{ 0x02, { "LD   (BC),A", 0, 8, &LD_aBC_A } },
		{ 0x12, { "LD   (DE),A", 0, 8, &LD_aDE_A } },
		{ 0x77, { "LD   (HL),A", 0, 8, &LD_aHL_A } },
		{ 0xEA, { "LD   ($%04X),A", 2, 16, &LD_ann_A } }, // e.g. LD ($1234),A

		// LD A,($FF00+C) and reverse
		{ 0xF2, { "LD   A,(C)", 0, 8, &LD_A_aC } }, // also LD A,($FF00+C)
		{ 0xE2, { "LD   (C),A", 0, 8, &LD_aC_A } },

		// LD A,(HL-) and variations
		{ 0x3A, { "LD   A,(HL-)", 0, 8, &LDD_A_aHL } }, // also LD A,(HLD) or LDD A,(HL)
		{ 0x32, { "LD   (HL-),A", 0, 8, &LDD_aHL_A } }, // also LD (HLD),A or LDD (HL),A
		{ 0x2A, { "LD   A,(HL+)", 0, 8, &LDI_A_aHL } }, // also LD A,(HLI) or LDI A,(HL)
		{ 0x22, { "LD   (HL+),A", 0, 8, &LDI_aHL_A } }, // also LD (HLI),A or LDI (HL),A

		// LDH (n),A and reverse
		{ 0xE0, { "LD   ($%02X),A", 1, 12, &LD_an_A } },
		{ 0xF0, { "LD   A,($%02X)", 1, 12, &LD_A_an } },

		#pragma endregion

		#pragma region 16-bit loads

		// LD n,nn
		{ 0x01, { "LD   BC,$%04X", 2, 12, &LD_BC_nn } },
		{ 0x11, { "LD   DE,$%04X", 2, 12, &LD_DE_nn } },
		{ 0x21, { "LD   HL,$%04X", 2, 12, &LD_HL_nn } },
		{ 0x31, { "LD   SP,$%04X", 2, 12, &LD_SP_nn } },

		// LD, SP,HL
		{ 0xF9, { "LD   SP,HL", 0, 8, &LD_SP_HL } },

		// LD HL,SP+n
		{ 0xF8, { "LD   HL,SP+$%02X", 1, 12, &LD_HL_SP_n } }, // also LDHL SP,n

		// LD (nn),SP
		{ 0x08, { "LD   ($%04X),SP", 2, 20, &LD_ann_SP } },

		// PUSH nn
		{ 0xF5, { "PUSH AF", 0, 16, &PUSH_AF } },
		{ 0xC5, { "PUSH BC", 0, 16, &PUSH_BC } },
		{ 0xD5, { "PUSH DE", 0, 16, &PUSH_DE } },
		{ 0xE5, { "PUSH HL", 0, 16, &PUSH_HL } },

		// POP nn
		{ 0xF1, { "POP  AF", 0, 12, &POP_AF } },
		{ 0xC1, { "POP  BC", 0, 12, &POP_BC } },
		{ 0xD1, { "POP  DE", 0, 12, &POP_DE } },
		{ 0xE1, { "POP  HL", 0, 12, &POP_HL } },

		#pragma endregion

		#pragma region 8-bit ALU

		// ADD A,n
		{ 0x87, { "ADD  A,A", 0, 4, &ADD_A_A } },
		{ 0x80, { "ADD  A,B", 0, 4, &ADD_A_B } },
		{ 0x81, { "ADD  A,C", 0, 4, &ADD_A_C } },
		{ 0x82, { "ADD  A,D", 0, 4, &ADD_A_D } },
		{ 0x83, { "ADD  A,E", 0, 4, &ADD_A_E } },
		{ 0x84, { "ADD  A,H", 0, 4, &ADD_A_H } },
		{ 0x85, { "ADD  A,L", 0, 4, &ADD_A_L } },
		{ 0x86, { "ADD  A,(HL)", 0, 8, &ADD_A_aHL } },
		{ 0xC6, { "ADD  A,$%02X", 1, 8, &ADD_A_n } },

		// ADC A,n
		{ 0x8F, { "ADC  A,A", 0, 4, &ADC_A_A } },
		{ 0x88, { "ADC  A,B", 0, 4, &ADC_A_B } },
		{ 0x89, { "ADC  A,C", 0, 4, &ADC_A_C } },
		{ 0x8A, { "ADC  A,D", 0, 4, &ADC_A_D } },
		{ 0x8B, { "ADC  A,E", 0, 4, &ADC_A_E } },
		{ 0x8C, { "ADC  A,H", 0, 4, &ADC_A_H } },
		{ 0x8D, { "ADC  A,L", 0, 4, &ADC_A_L } },
		{ 0x8E, { "ADC  A,(HL)", 0, 8, &ADC_A_aHL } },
		{ 0xCE, { "ADC  A,$%02X", 1, 8, &ADC_A_n } },

		// SUB n
		{ 0x97, { "SUB  A", 0, 4, &SUB_A } },
		{ 0x90, { "SUB  B", 0, 4, &SUB_B } },
		{ 0x91, { "SUB  C", 0, 4, &SUB_C } },
		{ 0x92, { "SUB  D", 0, 4, &SUB_D } },
		{ 0x93, { "SUB  E", 0, 4, &SUB_E } },
		{ 0x94, { "SUB  H", 0, 4, &SUB_H } },
		{ 0x95, { "SUB  L", 0, 4, &SUB_L } },
		{ 0x96, { "SUB  (HL)", 0, 8, &SUB_aHL } },
		{ 0xD6, { "SUB  $%02X", 1, 8, &SUB_n } },

		// SBC A,n
		{ 0x9F, { "SBC  A,A", 0, 4, &SBC_A_A } },
		{ 0x98, { "SBC  A,B", 0, 4, &SBC_A_B } },
		{ 0x99, { "SBC  A,C", 0, 4, &SBC_A_C } },
		{ 0x9A, { "SBC  A,D", 0, 4, &SBC_A_D } },
		{ 0x9B, { "SBC  A,E", 0, 4, &SBC_A_E } },
		{ 0x9C, { "SBC  A,H", 0, 4, &SBC_A_H } },
		{ 0x9D, { "SBC  A,L", 0, 4, &SBC_A_L } },
		{ 0x9E, { "SBC  A,(HL)", 0, 8, &SBC_A_aHL } },
		{ 0xDE, { "SBC  A,$%02X", 1, 8, &SBC_A_n } }, // ?? Manual seems confused about this one

		// AND n
		{ 0xA7, { "AND  A", 0, 4, &AND_A } },
		{ 0xA0, { "AND  B", 0, 4, &AND_B } },
		{ 0xA1, { "AND  C", 0, 4, &AND_C } },
		{ 0xA2, { "AND  D", 0, 4, &AND_D } },
		{ 0xA3, { "AND  E", 0, 4, &AND_E } },
		{ 0xA4, { "AND  H", 0, 4, &AND_H } },
		{ 0xA5, { "AND  L", 0, 4, &AND_L } },
		{ 0xA6, { "AND  (HL)", 0, 8, &AND_aHL } },
		{ 0xE6, { "AND  $%02X", 1, 8, &AND_n } },

		// OR n
		{ 0xB7, { "OR   A", 0, 4, &OR_A } },
		{ 0xB0, { "OR   B", 0, 4, &OR_B } },
		{ 0xB1, { "OR   C", 0, 4, &OR_C } },
		{ 0xB2, { "OR   D", 0, 4, &OR_D } },
		{ 0xB3, { "OR   E", 0, 4, &OR_E } },
		{ 0xB4, { "OR   H", 0, 4, &OR_H } },
		{ 0xB5, { "OR   L", 0, 4, &OR_L } },
		{ 0xB6, { "OR   (HL)", 0, 8, &OR_aHL } },
		{ 0xF6, { "OR   $%02X", 1, 8, &OR_n } },

		// XOR n
		{ 0xAF, { "XOR  A", 0, 4, &XOR_A } },
		{ 0xA8, { "XOR  B", 0, 4, &XOR_B } },
		{ 0xA9, { "XOR  C", 0, 4, &XOR_C } },
		{ 0xAA, { "XOR  D", 0, 4, &XOR_D } },
		{ 0xAB, { "XOR  E", 0, 4, &XOR_E } },
		{ 0xAC, { "XOR  H", 0, 4, &XOR_H } },
		{ 0xAD, { "XOR  L", 0, 4, &XOR_L } },
		{ 0xAE, { "XOR  (HL)", 0, 8, &XOR_aHL } },
		{ 0xEE, { "XOR  $%02X", 1, 8, &XOR_n } },

		// CP n
		{ 0xBF, { "CP   A", 0, 4, &CP_A } },
		{ 0xB8, { "CP   B", 0, 4, &CP_B } },
		{ 0xB9, { "CP   C", 0, 4, &CP_C } },
		{ 0xBA, { "CP   D", 0, 4, &CP_D } },
		{ 0xBB, { "CP   E", 0, 4, &CP_E } },
		{ 0xBC, { "CP   H", 0, 4, &CP_H } },
		{ 0xBD, { "CP   L", 0, 4, &CP_L } },
		{ 0xBE, { "CP   (HL)", 0, 8, &CP_aHL } },
		{ 0xFE, { "CP   $%02X", 1, 8, &CP_n } },

		// INC n
		{ 0x3C, { "INC  A", 0, 4, &INC_A } },
		{ 0x04, { "INC  B", 0, 4, &INC_B } },
		{ 0x0C, { "INC  C", 0, 4, &INC_C } },
		{ 0x14, { "INC  D", 0, 4, &INC_D } },
		{ 0x1C, { "INC  E", 0, 4, &INC_E } },
		{ 0x24, { "INC  H", 0, 4, &INC_H } },
		{ 0x2C, { "INC  L", 0, 4, &INC_L } },
		{ 0x34, { "INC  (HL)", 0, 12, &INC_aHL } },

		// DEC n
		{ 0x3D, { "DEC  A", 0, 4, &DEC_A } },
		{ 0x05, { "DEC  B", 0, 4, &DEC_B } },
		{ 0x0D, { "DEC  C", 0, 4, &DEC_C } },
		{ 0x15, { "DEC  D", 0, 4, &DEC_D } },
		{ 0x1D, { "DEC  E", 0, 4, &DEC_E } },
		{ 0x25, { "DEC  H", 0, 4, &DEC_H } },
		{ 0x2D, { "DEC  L", 0, 4, &DEC_L } },
		{ 0x35, { "DEC  (HL)", 0, 12, &DEC_aHL } },

		#pragma endregion

		#pragma region 16-bit Arithmetic

		// ADD HL,n
		{ 0x09, { "ADD  HL,BC", 0, 8, &ADD_HL_BC } },
		{ 0x19, { "ADD  HL,DE", 0, 8, &ADD_HL_DE } },
		{ 0x29, { "ADD  HL,HL", 0, 8, &ADD_HL_HL } },
		{ 0x39, { "ADD  HL,SP", 0, 8, &ADD_HL_SP } },

		// ADD SP,n
		{ 0xE8, { "ADD  SP,$%02X", 1, 16, &ADD_SP_n } },

		// INC nn
		{ 0x03, { "INC  BC", 0, 8, &INC_BC } },
		{ 0x13, { "INC  DE", 0, 8, &INC_DE } },
		{ 0x23, { "INC  HL", 0, 8, &INC_HL } },
		{ 0x33, { "INC  SP", 0, 8, &INC_SP } },

		// DEC nn
		{ 0x0B, { "DEC  BC", 0, 8, &DEC_BC } },
		{ 0x1B, { "DEC  DE", 0, 8, &DEC_DE } },
		{ 0x2B, { "DEC  HL", 0, 8, &DEC_HL } },
		{ 0x3B, { "DEC  SP", 0, 8, &DEC_SP } },

		#pragma endregion

		#pragma region Miscellaneous

		// SWAP n (See Prefix CB opcodes)
		//{ 0xCB 37, { "SWAP A", 0, 8, &SWAP_A } },
		//{ 0xCB 30, { "SWAP B", 0, 8, &SWAP_B } },
		//{ 0xCB 31, { "SWAP C", 0, 8, &SWAP_C } },
		//{ 0xCB 32, { "SWAP D", 0, 8, &SWAP_D } },
		//{ 0xCB 33, { "SWAP E", 0, 8, &SWAP_E } },
		//{ 0xCB 34, { "SWAP H", 0, 8, &SWAP_H } },
		//{ 0xCB 35, { "SWAP L", 0, 8, &SWAP_L } },
		//{ 0xCB 36, { "SWAP (HL)", 0, 16, &SWAP_aHL } },

		// Decimal adjust (Register A)
		{ 0x27, { "DAA", 0, 4, &DAA } },

		// Complement (Register A)
		{ 0x2F, { "CPL", 0, 4, &CPL } },

		// Complement carry flag
		{ 0x3F, { "CCF", 0, 4, &CCF } },

		// Set carry flag
		{ 0x37, { "SCF", 0, 4, &SCF } },

		// NOP
		{ 0x00, { "NOP", 0, 4, &NOP } },

		// HALT
		{ 0x76, { "HALT", 0, 4, &HALT } },

		// STOP
		{ 0x10, { "STOP", 1, 4, &STOP } }, // technically 10 00, but second byte is ignored

		// Disable/Enable Interrupts
		{ 0xF3, { "DI", 0, 4, &DI } },
		{ 0xFB, { "EI", 0, 4, &EI } },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (Register A)
		{ 0x07, { "RLCA", 0, 4, &RLCA } }, // NOTE TO SELF: this rotates A and sets the carry flag to the old bit 7 (bit 0 is set to bit 7, c is also set to bit 7)

		// Rotate left through carry (Register A)
		{ 0x17, { "RLA", 0, 4, &RLA } }, // NOTE TO SELF: this rotates A plus the carry flag (bit 0 is set to c, c is set to bit 7)

		// Rotate right with carry (Register A)
		{ 0x0F, { "RRCA", 0, 4, &RRCA } },

		// Rotate right through carry (Register A)
		{ 0x1F, { "RRA", 0, 4, &RRA } },

		// Rotate left with carry (RLC n) (See Prefix CB opcodes)
		//{ 0xCB 07, { "RLC  A", 0, 8, &RLC_A } },
		//{ 0xCB 00, { "RLC  B", 0, 8, &RLC_B } },
		//{ 0xCB 01, { "RLC  C", 0, 8, &RLC_C } },
		//{ 0xCB 02, { "RLC  D", 0, 8, &RLC_D } },
		//{ 0xCB 03, { "RLC  E", 0, 8, &RLC_E } },
		//{ 0xCB 04, { "RLC  H", 0, 8, &RLC_H } },
		//{ 0xCB 05, { "RLC  L", 0, 8, &RLC_L } },
		//{ 0xCB 06, { "RLC  (HL)", 0, 16, &RLC_aHL } },

		// Rotate left through carry (RL n) (See Prefix CB opcodes)
		//{ 0xCB 17, { "RL   A", 0, 8, &RL_A } },
		//{ 0xCB 10, { "RL   B", 0, 8, &RL_B } },
		//{ 0xCB 11, { "RL   C", 0, 8, &RL_C } },
		//{ 0xCB 12, { "RL   D", 0, 8, &RL_D } },
		//{ 0xCB 13, { "RL   E", 0, 8, &RL_E } },
		//{ 0xCB 14, { "RL   H", 0, 8, &RL_H } },
		//{ 0xCB 15, { "RL   L", 0, 8, &RL_L } },
		//{ 0xCB 16, { "RL   (HL)", 0, 16, &RL_aHL } },

		// Rotate right with carry (RRC n) (See Prefix CB opcodes)
		//{ 0xCB 0F, { "RRC  A", 0, 8, &RRC_A } },
		//{ 0xCB 08, { "RRC  B", 0, 8, &RRC_B } },
		//{ 0xCB 09, { "RRC  C", 0, 8, &RRC_C } },
		//{ 0xCB 0A, { "RRC  D", 0, 8, &RRC_D } },
		//{ 0xCB 0B, { "RRC  E", 0, 8, &RRC_E } },
		//{ 0xCB 0C, { "RRC  H", 0, 8, &RRC_H } },
		//{ 0xCB 0D, { "RRC  L", 0, 8, &RRC_L } },
		//{ 0xCB 0E, { "RRC  (HL)", 0, 16, &RRC_aHL },

		// Rotate right through carry (RR n) (See Prefix CB opcodes)
		//{ 0xCB 1F, { "RR   A", 0, 8, &RR_A } },
		//{ 0xCB 18, { "RR   B", 0, 8, &RR_B } },
		//{ 0xCB 19, { "RR   C", 0, 8, &RR_C } },
		//{ 0xCB 1A, { "RR   D", 0, 8, &RR_D } },
		//{ 0xCB 1B, { "RR   E", 0, 8, &RR_E } },
		//{ 0xCB 1C, { "RR   H", 0, 8, &RR_H } },
		//{ 0xCB 1D, { "RR   L", 0, 8, &RR_L } },
		//{ 0xCB 1E, { "RR   (HL)", 0, 16, &RR_aHL } },

		// Shift left into carry (SLA n) (See Prefix CB opcodes)
		//{ 0xCB 27, { "SLA  A", 0, 8, &SLA_A } },
		//{ 0xCB 20, { "SLA  B", 0, 8, &SLA_B } },
		//{ 0xCB 21, { "SLA  C", 0, 8, &SLA_C } },
		//{ 0xCB 22, { "SLA  D", 0, 8, &SLA_D } },
		//{ 0xCB 23, { "SLA  E", 0, 8, &SLA_E } },
		//{ 0xCB 24, { "SLA  H", 0, 8, &SLA_H } },
		//{ 0xCB 25, { "SLA  L", 0, 8, &SLA_L } },
		//{ 0xCB 26, { "SLA  (HL)", 0, 16, &SLA_aHL } },

		// Shift right into carry (SRA n) (See Prefix CB opcodes)
		//{ 0xCB 2F, { "SRA  A", 0, 8, &SRA_A } },
		//{ 0xCB 28, { "SRA  B", 0, 8, &SRA_B } },
		//{ 0xCB 29, { "SRA  C", 0, 8, &SRA_C } },
		//{ 0xCB 2A, { "SRA  D", 0, 8, &SRA_D } },
		//{ 0xCB 2B, { "SRA  E", 0, 8, &SRA_E } },
		//{ 0xCB 2C, { "SRA  H", 0, 8, &SRA_H } },
		//{ 0xCB 2D, { "SRA  L", 0, 8, &SRA_L } },
		//{ 0xCB 2E, { "SRA  (HL)", 0, 16, &SRA_aHL } },

		// Shift right into carry (SRL n) (See Prefix CB opcodes)
		//{ 0xCB 3F, { "SRL  A", 0, 8, &SRL_A } },
		//{ 0xCB 38, { "SRL  B", 0, 8, &SRL_B } },
		//{ 0xCB 39, { "SRL  C", 0, 8, &SRL_C } },
		//{ 0xCB 3A, { "SRL  D", 0, 8, &SRL_D } },
		//{ 0xCB 3B, { "SRL  E", 0, 8, &SRL_E } },
		//{ 0xCB 3C, { "SRL  H", 0, 8, &SRL_H } },
		//{ 0xCB 3D, { "SRL  L", 0, 8, &SRL_L } },
		//{ 0xCB 3E, { "SRL  (HL)", 0, 16, &SRL_aHL } },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r) (See Prefix CB opcodes)
		//{ 0xCB 47, { "BIT  b,A", 0, 8, &BIT_n_A } },
		//{ 0xCB 40, { "BIT  b,B", 0, 8, &BIT_n_B } },
		//{ 0xCB 41, { "BIT  b,C", 0, 8, &BIT_n_C } },
		//{ 0xCB 42, { "BIT  b,D", 0, 8, &BIT_n_D } },
		//{ 0xCB 43, { "BIT  b,E", 0, 8, &BIT_n_E } },
		//{ 0xCB 44, { "BIT  b,H", 0, 8, &BIT_n_H } },
		//{ 0xCB 45, { "BIT  b,L", 0, 8, &BIT_n_L } },
		//{ 0xCB 46, { "BIT  b,(HL)", 0, 16, &BIT_n_aHL } },

		// Set Bit (SET b,r) (See Prefix CB opcodes)
		//{ 0xCB C7, { "SET  b,A", 0, 8, &SET_n_A } },
		//{ 0xCB C0, { "SET  b,B", 0, 8, &SET_n_B } },
		//{ 0xCB C1, { "SET  b,C", 0, 8, &SET_n_C } },
		//{ 0xCB C2, { "SET  b,D", 0, 8, &SET_n_D } },
		//{ 0xCB C3, { "SET  b,E", 0, 8, &SET_n_E } },
		//{ 0xCB C4, { "SET  b,H", 0, 8, &SET_n_H } },
		//{ 0xCB C5, { "SET  b,L", 0, 8, &SET_n_L } },
		//{ 0xCB C6, { "SET  b,(HL)", 0, 16, &SET_n_aHL } },

		// Reset (clear) Bit (RES b,r) (See Prefix CB opcodes)
		//{ 0xCB 87, { "RES  b,A", 0, 8, &RES_n_A } },
		//{ 0xCB 80, { "RES  b,B", 0, 8, &RES_n_B } },
		//{ 0xCB 81, { "RES  b,C", 0, 8, &RES_n_C } },
		//{ 0xCB 82, { "RES  b,D", 0, 8, &RES_n_D } },
		//{ 0xCB 83, { "RES  b,E", 0, 8, &RES_n_E } },
		//{ 0xCB 84, { "RES  b,H", 0, 8, &RES_n_H } },
		//{ 0xCB 85, { "RES  b,L", 0, 8, &RES_n_L } },
		//{ 0xCB 86, { "RES  b,(HL)", 0, 16, &RES_n_aHL } },

		#pragma endregion

		#pragma region Jumps

		// JP nn
		{ 0xC3, { "JP   $%04X", 2, 12, &JP_nn } },

		// JP cc,nn
		{ 0xC2, { "JP   NZ,$%04X", 2, 12, &JP_NZ_nn } },
		{ 0xCA, { "JP   Z,$%04X", 2, 12, &JP_Z_nn } },
		{ 0xD2, { "JP   NC,$%04X", 2, 12, &JP_NC_nn } },
		{ 0xDA, { "JP   C,$%04X", 2, 12, &JP_C_nn } },

		// JP (HL)
		{ 0xE9, { "JP   (HL)", 0, 4, &JP_aHL } },

		// JR n (relative jump)
		{ 0x18, { "JR   $%04X", 1, 8, &JR_n } },

		// JR cc,n
		{ 0x20, { "JR   NZ,$%04X", 1, 8, &JR_NZ_n } },
		{ 0x28, { "JR   Z,$%04X", 1, 8, &JR_Z_n } },
		{ 0x30, { "JR   NC,$%04X", 1, 8, &JR_NC_n } },
		{ 0x38, { "JR   C,$%04X", 1, 8, &JR_C_n } },

		#pragma endregion

		#pragma region Calls

		// CALL nn
		{ 0xCD, { "CALL $%04X", 2, 12, &CALL_nn } },

		// CALL cc,nn
		{ 0xC4, { "CALL NZ,$%04X", 2, 12, &CALL_NZ_nn } },
		{ 0xCC, { "CALL Z,$%04X", 2, 12, &CALL_Z_nn } },
		{ 0xD4, { "CALL NC,$%04X", 2, 12, &CALL_NC_nn } },
		{ 0xDC, { "CALL C,$%04X", 2, 12, &CALL_C_nn } },

		#pragma endregion

		#pragma region Restarts

		// RST n
		{ 0xC7, { "RST  $00", 0, 32, &RST_00 } },
		{ 0xCF, { "RST  $08", 0, 32, &RST_08 } },
		{ 0xD7, { "RST  $10", 0, 32, &RST_10 } },
		{ 0xDF, { "RST  $18", 0, 32, &RST_18 } },
		{ 0xE7, { "RST  $20", 0, 32, &RST_20 } },
		{ 0xEF, { "RST  $28", 0, 32, &RST_28 } },
		{ 0xF7, { "RST  $30", 0, 32, &RST_30 } },
		{ 0xFF, { "RST  $38", 0, 32, &RST_38 } },

		#pragma endregion

		#pragma region Returns

		// RET
		{ 0xC9, { "RET", 0, 8, &RET } },

		// RET cc
		{ 0xC0, { "RET  NZ", 0, 8, &RET_NZ } },
		{ 0xC8, { "RET  Z", 0, 8, &RET_Z } },
		{ 0xD0, { "RET  NC", 0, 8, &RET_NC } },
		{ 0xD8, { "RET  C", 0, 8, &RET_C } },

		// RETI
		{ 0xD9, { "RETI", 0, 8, &RETI } },

		#pragma endregion
	};

	const map<uint8_t, Instruction> CPU::sOpcodeDisassembly_PrefixCB
	{
		#pragma region Swap

		// SWAP n (See Prefix CB opcodes)
		{ 0x37, { "SWAP A", 0, 8, &SWAP_A } },
		{ 0x30, { "SWAP B", 0, 8, &SWAP_B } },
		{ 0x31, { "SWAP C", 0, 8, &SWAP_C } },
		{ 0x32, { "SWAP D", 0, 8, &SWAP_D } },
		{ 0x33, { "SWAP E", 0, 8, &SWAP_E } },
		{ 0x34, { "SWAP H", 0, 8, &SWAP_H } },
		{ 0x35, { "SWAP L", 0, 8, &SWAP_L } },
		{ 0x36, { "SWAP (HL)", 0, 16, &SWAP_aHL } },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (RLC n)
		{ 0x07, { "RLC  A", 1, 8, &RLC_A } },
		{ 0x00, { "RLC  B", 1, 8, &RLC_B } },
		{ 0x01, { "RLC  C", 1, 8, &RLC_C } },
		{ 0x02, { "RLC  D", 1, 8, &RLC_D } },
		{ 0x03, { "RLC  E", 1, 8, &RLC_E } },
		{ 0x04, { "RLC  H", 1, 8, &RLC_H } },
		{ 0x05, { "RLC  L", 1, 8, &RLC_L } },
		{ 0x06, { "RLC  (HL)", 1, 16, &RLC_aHL } },

		// Rotate left through carry (RL n)
		{ 0x17, { "RL   A", 1, 8, &RL_A } },
		{ 0x10, { "RL   B", 1, 8, &RL_B } },
		{ 0x11, { "RL   C", 1, 8, &RL_C } },
		{ 0x12, { "RL   D", 1, 8, &RL_D } },
		{ 0x13, { "RL   E", 1, 8, &RL_E } },
		{ 0x14, { "RL   H", 1, 8, &RL_H } },
		{ 0x15, { "RL   L", 1, 8, &RL_L } },
		{ 0x16, { "RL   (HL)", 1, 16, &RL_aHL } },

		// Rotate right with carry (RRC n)
		{ 0x0F, { "RRC  A", 1, 8, &RRC_A } },
		{ 0x08, { "RRC  B", 1, 8, &RRC_B } },
		{ 0x09, { "RRC  C", 1, 8, &RRC_C } },
		{ 0x0A, { "RRC  D", 1, 8, &RRC_D } },
		{ 0x0B, { "RRC  E", 1, 8, &RRC_E } },
		{ 0x0C, { "RRC  H", 1, 8, &RRC_H } },
		{ 0x0D, { "RRC  L", 1, 8, &RRC_L } },
		{ 0x0E, { "RRC  (HL)", 1, 16, &RRC_aHL } },

		// Rotate right through carry (RR n)
		{ 0x1F, { "RR   A", 1, 8, &RR_A } },
		{ 0x18, { "RR   B", 1, 8, &RR_B } },
		{ 0x19, { "RR   C", 1, 8, &RR_C } },
		{ 0x1A, { "RR   D", 1, 8, &RR_D } },
		{ 0x1B, { "RR   E", 1, 8, &RR_E } },
		{ 0x1C, { "RR   H", 1, 8, &RR_H } },
		{ 0x1D, { "RR   L", 1, 8, &RR_L } },
		{ 0x1E, { "RR   (HL)", 1, 16, &RR_aHL } },

		// Shif left into carry (SLA n)
		{ 0x27, { "SLA  A", 1, 8, &SLA_A } },
		{ 0x20, { "SLA  B", 1, 8, &SLA_B } },
		{ 0x21, { "SLA  C", 1, 8, &SLA_C } },
		{ 0x22, { "SLA  D", 1, 8, &SLA_D } },
		{ 0x23, { "SLA  E", 1, 8, &SLA_E } },
		{ 0x24, { "SLA  H", 1, 8, &SLA_H } },
		{ 0x25, { "SLA  L", 1, 8, &SLA_L } },
		{ 0x26, { "SLA  (HL)", 1, 16, &SLA_aHL } },

		// Shif right into carry (SRA n)
		{ 0x2F, { "SRA  A", 1, 8, &SRA_A } },
		{ 0x28, { "SRA  B", 1, 8, &SRA_B } },
		{ 0x29, { "SRA  C", 1, 8, &SRA_C } },
		{ 0x2A, { "SRA  D", 1, 8, &SRA_D } },
		{ 0x2B, { "SRA  E", 1, 8, &SRA_E } },
		{ 0x2C, { "SRA  H", 1, 8, &SRA_H } },
		{ 0x2D, { "SRA  L", 1, 8, &SRA_L } },
		{ 0x2E, { "SRA  (HL)", 1, 16, &SRA_aHL } },

		// Shift right into carry (SRL n)
		{ 0x3F, { "SRL  A", 1, 8, &SRL_A } },
		{ 0x38, { "SRL  B", 1, 8, &SRL_B } },
		{ 0x39, { "SRL  C", 1, 8, &SRL_C } },
		{ 0x3A, { "SRL  D", 1, 8, &SRL_D } },
		{ 0x3B, { "SRL  E", 1, 8, &SRL_E } },
		{ 0x3C, { "SRL  H", 1, 8, &SRL_H } },
		{ 0x3D, { "SRL  L", 1, 8, &SRL_L } },
		{ 0x3E, { "SRL  (HL)", 1, 16, &SRL_aHL } },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r)
		{ 0x47, { "BIT  0,A", 1, 8, &BIT_0_A } },
		{ 0x40, { "BIT  0,B", 1, 8, &BIT_0_B } },
		{ 0x41, { "BIT  0,C", 1, 8, &BIT_0_C } },
		{ 0x42, { "BIT  0,D", 1, 8, &BIT_0_D } },
		{ 0x43, { "BIT  0,E", 1, 8, &BIT_0_E } },
		{ 0x44, { "BIT  0,H", 1, 8, &BIT_0_H } },
		{ 0x45, { "BIT  0,L", 1, 8, &BIT_0_L } },
		{ 0x46, { "BIT  0,(HL)", 1, 16, &BIT_0_aHL } },
		{ 0x4F, { "BIT  1,A", 1, 8, &BIT_1_A } },
		{ 0x48, { "BIT  1,B", 1, 8, &BIT_1_B } },
		{ 0x49, { "BIT  1,C", 1, 8, &BIT_1_C } },
		{ 0x4A, { "BIT  1,D", 1, 8, &BIT_1_D } },
		{ 0x4B, { "BIT  1,E", 1, 8, &BIT_1_E } },
		{ 0x4C, { "BIT  1,H", 1, 8, &BIT_1_H } },
		{ 0x4D, { "BIT  1,L", 1, 8, &BIT_1_L } },
		{ 0x4E, { "BIT  1,(HL)", 1, 16, &BIT_1_aHL } },
		{ 0x57, { "BIT  2,A", 1, 8, &BIT_2_A } },
		{ 0x50, { "BIT  2,B", 1, 8, &BIT_2_B } },
		{ 0x51, { "BIT  2,C", 1, 8, &BIT_2_C } },
		{ 0x52, { "BIT  2,D", 1, 8, &BIT_2_D } },
		{ 0x53, { "BIT  2,E", 1, 8, &BIT_2_E } },
		{ 0x54, { "BIT  2,H", 1, 8, &BIT_2_H } },
		{ 0x55, { "BIT  2,L", 1, 8, &BIT_2_L } },
		{ 0x56, { "BIT  2,(HL)", 1, 16, &BIT_2_aHL } },
		{ 0x5F, { "BIT  3,A", 1, 8, &BIT_3_A } },
		{ 0x58, { "BIT  3,B", 1, 8, &BIT_3_B } },
		{ 0x59, { "BIT  3,C", 1, 8, &BIT_3_C } },
		{ 0x5A, { "BIT  3,D", 1, 8, &BIT_3_D } },
		{ 0x5B, { "BIT  3,E", 1, 8, &BIT_3_E } },
		{ 0x5C, { "BIT  3,H", 1, 8, &BIT_3_H } },
		{ 0x5D, { "BIT  3,L", 1, 8, &BIT_3_L } },
		{ 0x5E, { "BIT  3,(HL)", 1, 16, &BIT_3_aHL } },
		{ 0x67, { "BIT  4,A", 1, 8, &BIT_4_A } },
		{ 0x60, { "BIT  4,B", 1, 8, &BIT_4_B } },
		{ 0x61, { "BIT  4,C", 1, 8, &BIT_4_C } },
		{ 0x62, { "BIT  4,D", 1, 8, &BIT_4_D } },
		{ 0x63, { "BIT  4,E", 1, 8, &BIT_4_E } },
		{ 0x64, { "BIT  4,H", 1, 8, &BIT_4_H } },
		{ 0x65, { "BIT  4,L", 1, 8, &BIT_4_L } },
		{ 0x66, { "BIT  4,(HL)", 1, 16, &BIT_4_aHL } },
		{ 0x6F, { "BIT  5,A", 1, 8, &BIT_5_A } },
		{ 0x68, { "BIT  5,B", 1, 8, &BIT_5_B } },
		{ 0x69, { "BIT  5,C", 1, 8, &BIT_5_C } },
		{ 0x6A, { "BIT  5,D", 1, 8, &BIT_5_D } },
		{ 0x6B, { "BIT  5,E", 1, 8, &BIT_5_E } },
		{ 0x6C, { "BIT  5,H", 1, 8, &BIT_5_H } },
		{ 0x6D, { "BIT  5,L", 1, 8, &BIT_5_L } },
		{ 0x6E, { "BIT  5,(HL)", 1, 16, &BIT_5_aHL } },
		{ 0x77, { "BIT  6,A", 1, 8, &BIT_6_A } },
		{ 0x70, { "BIT  6,B", 1, 8, &BIT_6_B } },
		{ 0x71, { "BIT  6,C", 1, 8, &BIT_6_C } },
		{ 0x72, { "BIT  6,D", 1, 8, &BIT_6_D } },
		{ 0x73, { "BIT  6,E", 1, 8, &BIT_6_E } },
		{ 0x74, { "BIT  6,H", 1, 8, &BIT_6_H } },
		{ 0x75, { "BIT  6,L", 1, 8, &BIT_6_L } },
		{ 0x76, { "BIT  6,(HL)", 1, 16, &BIT_6_aHL } },
		{ 0x7F, { "BIT  7,A", 1, 8, &BIT_7_A } },
		{ 0x78, { "BIT  7,B", 1, 8, &BIT_7_B } },
		{ 0x79, { "BIT  7,C", 1, 8, &BIT_7_C } },
		{ 0x7A, { "BIT  7,D", 1, 8, &BIT_7_D } },
		{ 0x7B, { "BIT  7,E", 1, 8, &BIT_7_E } },
		{ 0x7C, { "BIT  7,H", 1, 8, &BIT_7_H } },
		{ 0x7D, { "BIT  7,L", 1, 8, &BIT_7_L } },
		{ 0x7E, { "BIT  7,(HL)", 1, 16, &BIT_7_aHL } },

		// Set Bit (SET b,r)
		{ 0xC7, { "SET  0,A", 1, 8, &SET_0_A } },
		{ 0xC0, { "SET  0,B", 1, 8, &SET_0_B } },
		{ 0xC1, { "SET  0,C", 1, 8, &SET_0_C } },
		{ 0xC2, { "SET  0,D", 1, 8, &SET_0_D } },
		{ 0xC3, { "SET  0,E", 1, 8, &SET_0_E } },
		{ 0xC4, { "SET  0,H", 1, 8, &SET_0_H } },
		{ 0xC5, { "SET  0,L", 1, 8, &SET_0_L } },
		{ 0xC6, { "SET  0,(HL)", 1, 16, &SET_0_aHL } },
		{ 0xCF, { "SET  1,A", 1, 8, &SET_1_A } },
		{ 0xC8, { "SET  1,B", 1, 8, &SET_1_B } },
		{ 0xC9, { "SET  1,C", 1, 8, &SET_1_C } },
		{ 0xCA, { "SET  1,D", 1, 8, &SET_1_D } },
		{ 0xCB, { "SET  1,E", 1, 8, &SET_1_E } },
		{ 0xCC, { "SET  1,H", 1, 8, &SET_1_H } },
		{ 0xCD, { "SET  1,L", 1, 8, &SET_1_L } },
		{ 0xCE, { "SET  1,(HL)", 1, 16, &SET_1_aHL } },
		{ 0xD7, { "SET  2,A", 1, 8, &SET_2_A } },
		{ 0xD0, { "SET  2,B", 1, 8, &SET_2_B } },
		{ 0xD1, { "SET  2,C", 1, 8, &SET_2_C } },
		{ 0xD2, { "SET  2,D", 1, 8, &SET_2_D } },
		{ 0xD3, { "SET  2,E", 1, 8, &SET_2_E } },
		{ 0xD4, { "SET  2,H", 1, 8, &SET_2_H } },
		{ 0xD5, { "SET  2,L", 1, 8, &SET_2_L } },
		{ 0xD6, { "SET  2,(HL)", 1, 16, &SET_2_aHL } },
		{ 0xDF, { "SET  3,A", 1, 8, &SET_3_A } },
		{ 0xD8, { "SET  3,B", 1, 8, &SET_3_B } },
		{ 0xD9, { "SET  3,C", 1, 8, &SET_3_C } },
		{ 0xDA, { "SET  3,D", 1, 8, &SET_3_D } },
		{ 0xDB, { "SET  3,E", 1, 8, &SET_3_E } },
		{ 0xDC, { "SET  3,H", 1, 8, &SET_3_H } },
		{ 0xDD, { "SET  3,L", 1, 8, &SET_3_L } },
		{ 0xDE, { "SET  3,(HL)", 1, 16, &SET_3_aHL } },
		{ 0xE7, { "SET  4,A", 1, 8, &SET_4_A } },
		{ 0xE0, { "SET  4,B", 1, 8, &SET_4_B } },
		{ 0xE1, { "SET  4,C", 1, 8, &SET_4_C } },
		{ 0xE2, { "SET  4,D", 1, 8, &SET_4_D } },
		{ 0xE3, { "SET  4,E", 1, 8, &SET_4_E } },
		{ 0xE4, { "SET  4,H", 1, 8, &SET_4_H } },
		{ 0xE5, { "SET  4,L", 1, 8, &SET_4_L } },
		{ 0xE6, { "SET  4,(HL)", 1, 16, &SET_4_aHL } },
		{ 0xEF, { "SET  5,A", 1, 8, &SET_5_A } },
		{ 0xE8, { "SET  5,B", 1, 8, &SET_5_B } },
		{ 0xE9, { "SET  5,C", 1, 8, &SET_5_C } },
		{ 0xEA, { "SET  5,D", 1, 8, &SET_5_D } },
		{ 0xEB, { "SET  5,E", 1, 8, &SET_5_E } },
		{ 0xEC, { "SET  5,H", 1, 8, &SET_5_H } },
		{ 0xED, { "SET  5,L", 1, 8, &SET_5_L } },
		{ 0xEE, { "SET  5,(HL)", 1, 16, &SET_5_aHL } },
		{ 0xF7, { "SET  6,A", 1, 8, &SET_6_A } },
		{ 0xF0, { "SET  6,B", 1, 8, &SET_6_B } },
		{ 0xF1, { "SET  6,C", 1, 8, &SET_6_C } },
		{ 0xF2, { "SET  6,D", 1, 8, &SET_6_D } },
		{ 0xF3, { "SET  6,E", 1, 8, &SET_6_E } },
		{ 0xF4, { "SET  6,H", 1, 8, &SET_6_H } },
		{ 0xF5, { "SET  6,L", 1, 8, &SET_6_L } },
		{ 0xF6, { "SET  6,(HL)", 1, 16, &SET_6_aHL } },
		{ 0xFF, { "SET  7,A", 1, 8, &SET_7_A } },
		{ 0xF8, { "SET  7,B", 1, 8, &SET_7_B } },
		{ 0xF9, { "SET  7,C", 1, 8, &SET_7_C } },
		{ 0xFA, { "SET  7,D", 1, 8, &SET_7_D } },
		{ 0xFB, { "SET  7,E", 1, 8, &SET_7_E } },
		{ 0xFC, { "SET  7,H", 1, 8, &SET_7_H } },
		{ 0xFD, { "SET  7,L", 1, 8, &SET_7_L } },
		{ 0xFE, { "SET  7,(HL)", 1, 16, &SET_7_aHL } },

		// Reset (Clear) Bit (RES b,r)
		{ 0x87, { "RES  0,A", 1, 8, &RES_0_A } },
		{ 0x80, { "RES  0,B", 1, 8, &RES_0_B } },
		{ 0x81, { "RES  0,C", 1, 8, &RES_0_C } },
		{ 0x82, { "RES  0,D", 1, 8, &RES_0_D } },
		{ 0x83, { "RES  0,E", 1, 8, &RES_0_E } },
		{ 0x84, { "RES  0,H", 1, 8, &RES_0_H } },
		{ 0x85, { "RES  0,L", 1, 8, &RES_0_L } },
		{ 0x86, { "RES  0,(HL)", 1, 16, &RES_0_aHL } },
		{ 0x8F, { "RES  1,A", 1, 8, &RES_1_A } },
		{ 0x88, { "RES  1,B", 1, 8, &RES_1_B } },
		{ 0x89, { "RES  1,C", 1, 8, &RES_1_C } },
		{ 0x8A, { "RES  1,D", 1, 8, &RES_1_D } },
		{ 0x8B, { "RES  1,E", 1, 8, &RES_1_E } },
		{ 0x8C, { "RES  1,H", 1, 8, &RES_1_H } },
		{ 0x8D, { "RES  1,L", 1, 8, &RES_1_L } },
		{ 0x8E, { "RES  1,(HL)", 1, 16, &RES_1_aHL } },
		{ 0x97, { "RES  2,A", 1, 8, &RES_2_A } },
		{ 0x90, { "RES  2,B", 1, 8, &RES_2_B } },
		{ 0x91, { "RES  2,C", 1, 8, &RES_2_C } },
		{ 0x92, { "RES  2,D", 1, 8, &RES_2_D } },
		{ 0x93, { "RES  2,E", 1, 8, &RES_2_E } },
		{ 0x94, { "RES  2,H", 1, 8, &RES_2_H } },
		{ 0x95, { "RES  2,L", 1, 8, &RES_2_L } },
		{ 0x96, { "RES  2,(HL)", 1, 16, &RES_2_aHL } },
		{ 0x9F, { "RES  3,A", 1, 8, &RES_3_A } },
		{ 0x98, { "RES  3,B", 1, 8, &RES_3_B } },
		{ 0x99, { "RES  3,C", 1, 8, &RES_3_C } },
		{ 0x9A, { "RES  3,D", 1, 8, &RES_3_D } },
		{ 0x9B, { "RES  3,E", 1, 8, &RES_3_E } },
		{ 0x9C, { "RES  3,H", 1, 8, &RES_3_H } },
		{ 0x9D, { "RES  3,L", 1, 8, &RES_3_L } },
		{ 0x9E, { "RES  3,(HL)", 1, 16, &RES_3_aHL } },
		{ 0xA7, { "RES  4,A", 1, 8, &RES_4_A } },
		{ 0xA0, { "RES  4,B", 1, 8, &RES_4_B } },
		{ 0xA1, { "RES  4,C", 1, 8, &RES_4_C } },
		{ 0xA2, { "RES  4,D", 1, 8, &RES_4_D } },
		{ 0xA3, { "RES  4,E", 1, 8, &RES_4_E } },
		{ 0xA4, { "RES  4,H", 1, 8, &RES_4_H } },
		{ 0xA5, { "RES  4,L", 1, 8, &RES_4_L } },
		{ 0xA6, { "RES  4,(HL)", 1, 16, &RES_4_aHL } },
		{ 0xAF, { "RES  5,A", 1, 8, &RES_5_A } },
		{ 0xA8, { "RES  5,B", 1, 8, &RES_5_B } },
		{ 0xA9, { "RES  5,C", 1, 8, &RES_5_C } },
		{ 0xAA, { "RES  5,D", 1, 8, &RES_5_D } },
		{ 0xAB, { "RES  5,E", 1, 8, &RES_5_E } },
		{ 0xAC, { "RES  5,H", 1, 8, &RES_5_H } },
		{ 0xAD, { "RES  5,L", 1, 8, &RES_5_L } },
		{ 0xAE, { "RES  5,(HL)", 1, 16, &RES_5_aHL } },
		{ 0xB7, { "RES  6,A", 1, 8, &RES_6_A } },
		{ 0xB0, { "RES  6,B", 1, 8, &RES_6_B } },
		{ 0xB1, { "RES  6,C", 1, 8, &RES_6_C } },
		{ 0xB2, { "RES  6,D", 1, 8, &RES_6_D } },
		{ 0xB3, { "RES  6,E", 1, 8, &RES_6_E } },
		{ 0xB4, { "RES  6,H", 1, 8, &RES_6_H } },
		{ 0xB5, { "RES  6,L", 1, 8, &RES_6_L } },
		{ 0xB6, { "RES  6,(HL)", 1, 16, &RES_6_aHL } },
		{ 0xBF, { "RES  7,A", 1, 8, &RES_7_A } },
		{ 0xB8, { "RES  7,B", 1, 8, &RES_7_B } },
		{ 0xB9, { "RES  7,C", 1, 8, &RES_7_C } },
		{ 0xBA, { "RES  7,D", 1, 8, &RES_7_D } },
		{ 0xBB, { "RES  7,E", 1, 8, &RES_7_E } },
		{ 0xBC, { "RES  7,H", 1, 8, &RES_7_H } },
		{ 0xBD, { "RES  7,L", 1, 8, &RES_7_L } },
		{ 0xBE, { "RES  7,(HL)", 1, 16, &RES_7_aHL } }

		#pragma endregion
	};

	CPU::CPU(MemoryMap& memory) :
		mMemory(memory), mInterruptsEnabled(false), mHalted(false), mEnableInterruptsAfterNextInstruction(false), mDisableInterruptsAfterNextInstruction(false)
	{
	}

	void CPU::StepCPU()
	{
		if (mHalted)
		{
			return;
		}

		uint8_t opcode = 0x00;
		uint16_t pc = mRegisters.PC;
		try
		{
			bool disableInterrupts = false, enableInterrupts = false;
			if (mDisableInterruptsAfterNextInstruction)
			{
				disableInterrupts = true;
				mDisableInterruptsAfterNextInstruction = false;
			}
			if (mEnableInterruptsAfterNextInstruction)
			{
				enableInterrupts = true;
				mEnableInterruptsAfterNextInstruction = false;
			}

			// gather instruction information
			opcode = mMemory.ReadByte(mRegisters.PC++);
			Instruction instruction = opcode != 0xCB ? sOpcodeDisassembly.at(opcode) : sOpcodeDisassembly_PrefixCB.at(opcode);
			uint16_t operand = 0x0000;
			if (instruction.OperandLength == 1)
			{
				operand = mMemory.ReadByte(mRegisters.PC);
				mRegisters.PC += 1;
			}
			else if (instruction.OperandLength == 2)
			{
				operand = mMemory.ReadWord(mRegisters.PC);
				mRegisters.PC += 2;
			}

			// execute instruction
			invoke(instruction.Function, this, operand);
			// increment clock cycles

			if (disableInterrupts)
			{
				mInterruptsEnabled = false;
			}
			if (enableInterrupts)
			{
				mInterruptsEnabled = true;
			}
		}
		catch (exception& ex)
		{
			char message[100];
			sprintf_s(message, sizeof(message), "Error executing instruction 0x%02X at memory location 0x%04X:\n%s", opcode, pc, ex.what());
			throw exception(message);
		}
	}

	void CPU::Reset()
	{
		mRegisters.Reset();
		mMemory.Reset();
	}

	Registers& CPU::GetRegisters()
	{
		return mRegisters;
	}

	const Registers& CPU::GetRegisters() const
	{
		return mRegisters;
	}

	MemoryMap& CPU::GetMemoryMap()
	{
		return mMemory;
	}

	const MemoryMap& CPU::GetMemoryMap() const
	{
		return mMemory;
	}

	int32_t CPU::GetOperandLength(uint8_t opcode)
	{
		if (opcode == 0xCB)
		{
			return 1;
		}

		map<uint8_t, Instruction>::const_iterator it = sOpcodeDisassembly.find(opcode);
		if (it == sOpcodeDisassembly.end())
		{
			throw exception("Opcode not found!");
		}

		return it->second.OperandLength;
	}

	string CPU::GetDisassembly(uint8_t opcode, uint16_t operand)
	{
		map<uint8_t, Instruction>::const_iterator it;

		if (opcode == 0xCB)
		{
			it = sOpcodeDisassembly_PrefixCB.find(static_cast<uint8_t>(operand));
			if (it == sOpcodeDisassembly_PrefixCB.end())
			{
				throw exception("Opcode not found!");
			}
		}
		else
		{
			it = sOpcodeDisassembly.find(opcode);
			if (it == sOpcodeDisassembly.end())
			{
				throw exception("Opcode not found!");
			}
		}

		char str[20];
		sprintf_s(str, sizeof(str), it->second.Disassebly, operand);
		return str;
	}

	void CPU::PushWordToStack(uint16_t value)
	{
		mRegisters.SP -= 2;
		mMemory.WriteWord(mRegisters.SP, value);
	}

	uint16_t CPU::PopWordFromStack()
	{
		uint16_t value = mMemory.ReadWord(mRegisters.SP);
		mRegisters.SP += 2;
		return value;
	}

	void CPU::UnimplementedInstruction(uint16_t)
	{
		throw exception("Unimplemented instruction!");
	}

	#pragma region 8-Bit Loads

	/**
	 * \brief Load one byte immediate value into register B
	 */
	void CPU::LD_B_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.B = n;
	}

	/**
	 * \brief Load one byte immediate value into register C
	 */
	void CPU::LD_C_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.C = n;
	}

	/**
	 * \brief Load one byte immediate value into register D
	 */
	void CPU::LD_D_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.D = n;
	}

	/**
	 * \brief Load one byte immediate value into register E
	 */
	void CPU::LD_E_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.E = n;
	}

	/**
	 * \brief Load one byte immediate value into register H
	 */
	void CPU::LD_H_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.H = n;
	}

	/**
	 * \brief Load one byte immediate value into register L
	 */
	void CPU::LD_L_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.L = n;
	}

	/**
	 * \brief Put A into register A
	 */
	void CPU::LD_A_A(uint16_t)
	{
		mRegisters.A = mRegisters.A;
	}

	/**
	 * \brief Put B into register A
	 */
	void CPU::LD_A_B(uint16_t)
	{
		mRegisters.A = mRegisters.B;
	}

	/**
	 * \brief Put C into register A
	 */
	void CPU::LD_A_C(uint16_t)
	{
		mRegisters.A = mRegisters.C;
	}

	/**
	 * \brief Put D into register A
	 */
	void CPU::LD_A_D(uint16_t)
	{
		mRegisters.A = mRegisters.D;
	}

	/**
	 * \brief Put E into register A
	 */
	void CPU::LD_A_E(uint16_t)
	{
		mRegisters.A = mRegisters.E;
	}

	/**
	 * \brief Put H into register A
	 */
	void CPU::LD_A_H(uint16_t)
	{
		mRegisters.A = mRegisters.H;
	}

	/**
	 * \brief Put L into register A
	 */
	void CPU::LD_A_L(uint16_t)
	{
		mRegisters.A = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register A
	 */
	void CPU::LD_A_aHL(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register B
	 */
	void CPU::LD_B_B(uint16_t)
	{
		mRegisters.B = mRegisters.B;
	}

	/**
	 * \brief Put C into register B
	 */
	void CPU::LD_B_C(uint16_t)
	{
		mRegisters.B = mRegisters.C;
	}

	/**
	 * \brief Put D into register B
	 */
	void CPU::LD_B_D(uint16_t)
	{
		mRegisters.B = mRegisters.D;
	}

	/**
	 * \brief Put E into register B
	 */
	void CPU::LD_B_E(uint16_t)
	{
		mRegisters.B = mRegisters.E;
	}

	/**
	 * \brief Put H into register B
	 */
	void CPU::LD_B_H(uint16_t)
	{
		mRegisters.B = mRegisters.H;
	}

	/**
	 * \brief Put L into register B
	 */
	void CPU::LD_B_L(uint16_t)
	{
		mRegisters.B = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register B
	 */
	void CPU::LD_B_aHL(uint16_t)
	{
		mRegisters.B = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register C
	 */
	void CPU::LD_C_B(uint16_t)
	{
		mRegisters.C = mRegisters.B;
	}

	/**
	 * \brief Put C into register C
	 */
	void CPU::LD_C_C(uint16_t)
	{
		mRegisters.C = mRegisters.C;
	}

	/**
	 * \brief Put D into register C
	 */
	void CPU::LD_C_D(uint16_t)
	{
		mRegisters.C = mRegisters.D;
	}

	/**
	 * \brief Put E into register C
	 */
	void CPU::LD_C_E(uint16_t)
	{
		mRegisters.C = mRegisters.E;
	}

	/**
	 * \brief Put H into register C
	 */
	void CPU::LD_C_H(uint16_t)
	{
		mRegisters.C = mRegisters.H;
	}

	/**
	 * \brief Put L into register C
	 */
	void CPU::LD_C_L(uint16_t)
	{
		mRegisters.C = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register C
	 */
	void CPU::LD_C_aHL(uint16_t)
	{
		mRegisters.C = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register D
	 */
	void CPU::LD_D_B(uint16_t)
	{
		mRegisters.D = mRegisters.B;
	}

	/**
	 * \brief Put C into register D
	 */
	void CPU::LD_D_C(uint16_t)
	{
		mRegisters.D = mRegisters.C;
	}

	/**
	 * \brief Put D into register D
	 */
	void CPU::LD_D_D(uint16_t)
	{
		mRegisters.D = mRegisters.D;
	}

	/**
	 * \brief Put E into register D
	 */
	void CPU::LD_D_E(uint16_t)
	{
		mRegisters.D = mRegisters.E;
	}

	/**
	 * \brief Put H into register D
	 */
	void CPU::LD_D_H(uint16_t)
	{
		mRegisters.D = mRegisters.H;
	}

	/**
	 * \brief Put L into register D
	 */
	void CPU::LD_D_L(uint16_t)
	{
		mRegisters.D = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register D
	 */
	void CPU::LD_D_aHL(uint16_t)
	{
		mRegisters.D = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register E
	 */
	void CPU::LD_E_B(uint16_t)
	{
		mRegisters.E = mRegisters.B;
	}

	/**
	 * \brief Put C into register E
	 */
	void CPU::LD_E_C(uint16_t)
	{
		mRegisters.E = mRegisters.C;
	}

	/**
	 * \brief Put D into register E
	 */
	void CPU::LD_E_D(uint16_t)
	{
		mRegisters.E = mRegisters.D;
	}

	/**
	 * \brief Put E into register E
	 */
	void CPU::LD_E_E(uint16_t)
	{
		mRegisters.E = mRegisters.E;
	}

	/**
	 * \brief Put H into register E
	 */
	void CPU::LD_E_H(uint16_t)
	{
		mRegisters.E = mRegisters.H;
	}

	/**
	 * \brief Put L into register E
	 */
	void CPU::LD_E_L(uint16_t)
	{
		mRegisters.E = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register E
	 */
	void CPU::LD_E_aHL(uint16_t)
	{
		mRegisters.E = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register H
	 */
	void CPU::LD_H_B(uint16_t)
	{
		mRegisters.H = mRegisters.B;
	}

	/**
	 * \brief Put C into register H
	 */
	void CPU::LD_H_C(uint16_t)
	{
		mRegisters.H = mRegisters.C;
	}

	/**
	 * \brief Put D into register H
	 */
	void CPU::LD_H_D(uint16_t)
	{
		mRegisters.H = mRegisters.D;
	}

	/**
	 * \brief Put E into register H
	 */
	void CPU::LD_H_E(uint16_t)
	{
		mRegisters.H = mRegisters.E;
	}

	/**
	 * \brief Put H into register H
	 */
	void CPU::LD_H_H(uint16_t)
	{
		mRegisters.H = mRegisters.H;
	}

	/**
	 * \brief Put L into register H
	 */
	void CPU::LD_H_L(uint16_t)
	{
		mRegisters.H = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register H
	 */
	void CPU::LD_H_aHL(uint16_t)
	{
		mRegisters.H = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into register L
	 */
	void CPU::LD_L_B(uint16_t)
	{
		mRegisters.L = mRegisters.B;
	}

	/**
	 * \brief Put C into register L
	 */
	void CPU::LD_L_C(uint16_t)
	{
		mRegisters.L = mRegisters.C;
	}

	/**
	 * \brief Put D into register L
	 */
	void CPU::LD_L_D(uint16_t)
	{
		mRegisters.L = mRegisters.D;
	}

	/**
	 * \brief Put E into register L
	 */
	void CPU::LD_L_E(uint16_t)
	{
		mRegisters.L = mRegisters.E;
	}

	/**
	 * \brief Put H into register L
	 */
	void CPU::LD_L_H(uint16_t)
	{
		mRegisters.L = mRegisters.H;
	}

	/**
	 * \brief Put L into register L
	 */
	void CPU::LD_L_L(uint16_t)
	{
		mRegisters.L = mRegisters.L;
	}

	/**
	 * \brief Put value at memory location HL into register L
	 */
	void CPU::LD_L_aHL(uint16_t)
	{
		mRegisters.L = mMemory.ReadByte(mRegisters.HL);
	}

	/**
	 * \brief Put B into memory location HL
	 */
	void CPU::LD_aHL_B(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.B);
	}

	/**
	 * \brief Put C into memory location HL
	 */
	void CPU::LD_aHL_C(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.C);
	}

	/**
	 * \brief Put D into memory location HL
	 */
	void CPU::LD_aHL_D(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.D);
	}

	/**
	 * \brief Put E into memory location HL
	 */
	void CPU::LD_aHL_E(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.E);
	}

	/**
	 * \brief Put H into memory location HL
	 */
	void CPU::LD_aHL_H(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.H);
	}

	/**
	 * \brief Put L into memory location HL
	 */
	void CPU::LD_aHL_L(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.L);
	}

	/**
	 * \brief Put one byte immediate value into memory location HL
	 */
	void CPU::LD_aHL_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mMemory.WriteByte(mRegisters.HL, n);
	}

	/**
	 * \brief Put value at memory location BC into register A
	 */
	void CPU::LD_A_aBC(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(mRegisters.BC);
	}

	/**
	 * \brief Put value at memory location DE into register A
	 */
	void CPU::LD_A_aDE(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(mRegisters.DE);
	}

	/**
	 * \brief Put value at two-byte immediate memory location into register A
	 */
	void CPU::LD_A_ann(uint16_t operand)
	{
		mRegisters.A = mMemory.ReadByte(operand);
	}

	/**
	 * \brief Put one byte immediate value into register A
	 */
	void CPU::LD_A_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.A = n;
	}

	/**
	 * \brief Put A into register B
	 */
	void CPU::LD_B_A(uint16_t)
	{
		mRegisters.B = mRegisters.A;
	}

	/**
	 * \brief Put A into register C
	 */
	void CPU::LD_C_A(uint16_t)
	{
		mRegisters.C = mRegisters.A;
	}

	/**
	 * \brief Put A into register D
	 */
	void CPU::LD_D_A(uint16_t)
	{
		mRegisters.D = mRegisters.A;
	}

	/**
	 * \brief Put A into register E
	 */
	void CPU::LD_E_A(uint16_t)
	{
		mRegisters.E = mRegisters.A;
	}

	/**
	 * \brief Put A into register H
	 */
	void CPU::LD_H_A(uint16_t)
	{
		mRegisters.H = mRegisters.A;
	}

	/**
	 * \brief Put A into register L
	 */
	void CPU::LD_L_A(uint16_t)
	{
		mRegisters.L = mRegisters.A;
	}

	/**
	 * \brief Put A into memory location BC
	 */
	void CPU::LD_aBC_A(uint16_t)
	{
		mMemory.WriteByte(mRegisters.BC, mRegisters.A);
	}

	/**
	* \brief Put A into memory location DE
	*/
	void CPU::LD_aDE_A(uint16_t)
	{
		mMemory.WriteByte(mRegisters.DE, mRegisters.A);
	}

	/**
	 * \brief Put A into memory location HL
	 */
	void CPU::LD_aHL_A(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL, mRegisters.A);
	}

	/**
	 * \brief Put A into two-byte immediate memory location
	 */
	void CPU::LD_ann_A(uint16_t operand)
	{
		mMemory.WriteByte(operand, mRegisters.A);
	}

	/**
	 * \brief Put value at memory location 0xFF00 + register C into register A
	 */
	void CPU::LD_A_aC(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(0xFF00 + mRegisters.C);
	}

	/**
	 * \brief Put A into memory location 0xFF00 + register C
	 */
	void CPU::LD_aC_A(uint16_t)
	{
		mMemory.WriteByte(0xFF00 + mRegisters.C, mRegisters.A);
	}

	/**
	 * \brief Put value at memory location HL into register A and decrement HL
	 */
	void CPU::LDD_A_aHL(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(mRegisters.HL--);
	}

	/**
	 * \brief Put A into memory location HL and decrement HL
	 */
	void CPU::LDD_aHL_A(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL--, mRegisters.A);
	}

	/**
	 * \brief Put value at memory location HL into register A and increment HL
	 */
	void CPU::LDI_A_aHL(uint16_t)
	{
		mRegisters.A = mMemory.ReadByte(mRegisters.HL++);
	}

	/**
	 * \brief Put A into memory location HL and increment HL
	 */
	void CPU::LDI_aHL_A(uint16_t)
	{
		mMemory.WriteByte(mRegisters.HL++, mRegisters.A);
	}

	/**
	 * \brief Put A into memory location 0xFF00 + a one byte immediate value
	 */
	void CPU::LD_an_A(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mMemory.WriteByte(0xFF00 + n, mRegisters.A);
	}

	/**
	 * \brief Put value at memory location 0xFF00 + a one byte immediate value into register A
	 */
	void CPU::LD_A_an(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand);
		mRegisters.A = mMemory.ReadByte(0xFF00 + n);
	}

	#pragma endregion

	#pragma region 16-Bit Loads

	/**
	 * \brief Put two byte immediate value into register BC
	 */
	void CPU::LD_BC_nn(uint16_t operand)
	{
		mRegisters.BC = operand;
	}

	/**
	 * \brief Put two byte immediate value into register DE
	 */
	void CPU::LD_DE_nn(uint16_t operand)
	{
		mRegisters.DE = operand;
	}

	/**
	 * \brief Put two byte immediate value into register HL
	 */
	void CPU::LD_HL_nn(uint16_t operand)
	{
		mRegisters.HL = operand;
	}

	/**
	 * \brief Put two byte immediate value into the stack pointer
	 */
	void CPU::LD_SP_nn(uint16_t operand)
	{
		mRegisters.SP = operand;
	}

	/**
	 * \brief Put HL into the stack pointer
	 */
	void CPU::LD_SP_HL(uint16_t operand)
	{
		mRegisters.SP = operand;
	}

	/**
	 * \brief Put SP + one byte signed immediate value into register HL.
	 */
	void CPU::LD_HL_SP_n(uint16_t operand)
	{
		int8_t n = static_cast<int8_t>(operand & 0xFF);

		mRegisters.ResetZeroFlag();
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag((mRegisters.HL & 0xF) + (operand & 0xF) > 0xF);
		mRegisters.AssignCarryFlag((mRegisters.HL & 0xFF) + (operand & 0xFF) > 0xFF);

		mRegisters.HL = mRegisters.HL + n;
	}

	/**
	 * \brief Put the stack pointer at the two byte immediate address
	 */
	void CPU::LD_ann_SP(uint16_t operand)
	{
		mMemory.WriteWord(operand, mRegisters.SP);
	}

	/**
	 * \brief Push register AF onto the stack and decrement the stack pointer.
	 */
	void CPU::PUSH_AF(uint16_t)
	{
		PushWordToStack(mRegisters.AF);
	}

	/**
	 * \brief Push register BC onto the stack and decrement the stack pointer.
	 */
	void CPU::PUSH_BC(uint16_t)
	{
		PushWordToStack(mRegisters.BC);
	}

	/**
	 * \brief Push register DE onto the stack and decrement the stack pointer.
	 */
	void CPU::PUSH_DE(uint16_t)
	{
		PushWordToStack(mRegisters.DE);
	}

	/**
	 * \brief Push register HL onto the stack and decrement the stack pointer.
	 */
	void CPU::PUSH_HL(uint16_t)
	{
		PushWordToStack(mRegisters.HL);
	}

	/**
	 * \brief Pop two bytes off the stack into register AF and increment the stack pointer.
	 */
	void CPU::POP_AF(uint16_t)
	{
		mRegisters.AF = PopWordFromStack();
	}

	/**
	 * \brief Pop two bytes off the stack into register BC and increment the stack pointer.
	 */
	void CPU::POP_BC(uint16_t)
	{
		mRegisters.BC = PopWordFromStack();
	}

	/**
	 * \brief Pop two bytes off the stack into register DE and increment the stack pointer.
	 */
	void CPU::POP_DE(uint16_t)
	{
		mRegisters.DE = PopWordFromStack();
	}

	/**
	 * \brief Pop two bytes off the stack into register HL and increment the stack pointer.
	 */
	void CPU::POP_HL(uint16_t)
	{
		mRegisters.HL = PopWordFromStack();
	}

	#pragma endregion

	#pragma region 8-Bit ALU

	/**
	 * \brief Add A into A
	 */
	void CPU::ADD_A_A(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.A;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.A & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.A & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add B into A
	 */
	void CPU::ADD_A_B(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.B;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.B & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.B & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add C into A
	 */
	void CPU::ADD_A_C(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.C;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.C & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.C & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add D into A
	 */
	void CPU::ADD_A_D(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.D;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.D & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.D & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add E into A
	 */
	void CPU::ADD_A_E(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.E;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.E & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.E & 0xFF) > 0xFF;

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);

		mRegisters.A = result;
	}

	/**
	 * \brief Add H into A
	 */
	void CPU::ADD_A_H(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.H;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.H & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.H & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add L into A
	 */
	void CPU::ADD_A_L(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.L;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.L & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.L & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add the value at address HL into A
	 */
	void CPU::ADD_A_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A + value;
		bool halfCarry = (mRegisters.A & 0xF) + (value & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (value & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add a one byte immediate value into A
	 */
	void CPU::ADD_A_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A + n;
		bool halfCarry = (mRegisters.A & 0xF) + (n & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (n & 0xFF) > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add A with carry into A
	 */
	void CPU::ADC_A_A(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.A + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.A & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.A & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add B with carry into A
	 */
	void CPU::ADC_A_B(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.B + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.B & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.B & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add C with carry into A
	 */
	void CPU::ADC_A_C(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.C + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.C & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.C & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add D with carry into A
	 */
	void CPU::ADC_A_D(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.D + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.D & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.D & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add E with carry into A
	 */
	void CPU::ADC_A_E(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.E + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.E & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.E & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add H with carry into A
	 */
	void CPU::ADC_A_H(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.H + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.H & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.H & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add L with carry into A
	 */
	void CPU::ADC_A_L(uint16_t)
	{
		uint8_t result = mRegisters.A + mRegisters.L + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.L & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.L & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add the value at address HL with carry into A
	 */
	void CPU::ADC_A_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A + value + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (value & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (value & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add a one byte immediate value with carry into A
	 */
	void CPU::ADC_A_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A + n + mRegisters.GetCarryFlag() ? 1 : 0;
		bool halfCarry = (mRegisters.A & 0xF) + (n & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (n & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract A from A
	 */
	void CPU::SUB_A(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.A;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.A & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.A & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract B from A
	 */
	void CPU::SUB_B(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.B;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.B & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.B & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract C from A
	 */
	void CPU::SUB_C(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.C;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.C & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.C & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract D from A
	 */
	void CPU::SUB_D(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.D;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.D & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.D & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract E from A
	 */
	void CPU::SUB_E(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.E;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.E & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.E & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract H from A
	 */
	void CPU::SUB_H(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.H;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.H & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.H & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract L from A
	 */
	void CPU::SUB_L(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.L;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.L & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.L & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract the value at address HL from A
	 */
	void CPU::SUB_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A - value;
		bool halfCarry = (mRegisters.A & 0xF) < (value & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (value & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract a one byte immediate value from A
	 */
	void CPU::SUB_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A - n;
		bool halfCarry = (mRegisters.A & 0xF) < (n & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (n & 0xFF);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract A with carry from A
	 */
	void CPU::SBC_A_A(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.A + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.A & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.A & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract B with carry from A
	 */
	void CPU::SBC_A_B(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.B + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.B & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.B & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract C with carry from A
	 */
	void CPU::SBC_A_C(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.C + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.C & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.C & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract D with carry from A
	 */
	void CPU::SBC_A_D(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.D + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.D & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.D & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract E with carry from A
	 */
	void CPU::SBC_A_E(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.E + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.E & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.E & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract H with carry from A
	 */
	void CPU::SBC_A_H(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.H + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.H & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.H & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract L with carry from A
	 */
	void CPU::SBC_A_L(uint16_t)
	{
		uint8_t result = mRegisters.A - (mRegisters.L + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((mRegisters.L & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((mRegisters.L & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract the value at address HL with carry from A
	 */
	void CPU::SBC_A_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A - (value + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((value & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((value & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Subtract a one byte immediate value with carry from A
	 */
	void CPU::SBC_A_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A - (n + mRegisters.GetCarryFlag() ? 1 : 0);
		bool halfCarry = (mRegisters.A & 0xF) < ((n & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0);
		bool fullCarry = (mRegisters.A & 0xFF) < ((n & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Logically AND A with A
	 */
	void CPU::AND_A(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.A;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND B with A
	 */
	void CPU::AND_B(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.B;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND C with A
	 */
	void CPU::AND_C(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.C;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND D with A
	 */
	void CPU::AND_D(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.D;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND E with A
	 */
	void CPU::AND_E(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.E;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND H with A
	 */
	void CPU::AND_H(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.H;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND L with A
	 */
	void CPU::AND_L(uint16_t)
	{
		uint8_t result = mRegisters.A & mRegisters.L;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND the value at address HL with A
	 */
	void CPU::AND_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A & value;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically AND a one byte immediate value with A
	 */
	void CPU::AND_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A & n;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR A with A
	 */
	void CPU::OR_A(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.A;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR B with A
	 */
	void CPU::OR_B(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.B;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR C with A
	 */
	void CPU::OR_C(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.C;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR D with A
	 */
	void CPU::OR_D(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.D;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR E with A
	 */
	void CPU::OR_E(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.E;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR H with A
	 */
	void CPU::OR_H(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.H;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR L with A
	 */
	void CPU::OR_L(uint16_t)
	{
		uint8_t result = mRegisters.A | mRegisters.L;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR the value at address HL with A
	 */
	void CPU::OR_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A | value;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically OR a one byte immediate value with A
	 */
	void CPU::OR_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A | n;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR A with A
	 */
	void CPU::XOR_A(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.A;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR B with A
	 */
	void CPU::XOR_B(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.B;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR C with A
	 */
	void CPU::XOR_C(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.C;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR D with A
	 */
	void CPU::XOR_D(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.D;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR E with A
	 */
	void CPU::XOR_E(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.E;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR H with A
	 */
	void CPU::XOR_H(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.H;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR L with A
	 */
	void CPU::XOR_L(uint16_t)
	{
		uint8_t result = mRegisters.A ^ mRegisters.L;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR the value at address HL with A
	 */
	void CPU::XOR_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A ^ value;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Logically exclusive OR a one byte immediate value with A
	 */
	void CPU::XOR_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint8_t result = mRegisters.A ^ n;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Compare A to A
	 */
	void CPU::CP_A(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.A;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.A & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.A & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare B to A
	 */
	void CPU::CP_B(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.B;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.B & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.B & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare C to A
	 */
	void CPU::CP_C(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.C;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.C & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.C & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare D to A
	 */
	void CPU::CP_D(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.D;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.D & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.D & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare E to A
	 */
	void CPU::CP_E(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.E;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.E & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.E & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare H to A
	 */
	void CPU::CP_H(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.H;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.H & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.H & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare L to A
	 */
	void CPU::CP_L(uint16_t)
	{
		uint8_t result = mRegisters.A - mRegisters.L;
		bool halfCarry = (mRegisters.A & 0xF) < (mRegisters.L & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (mRegisters.L & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare the value at address HL to A
	 */
	void CPU::CP_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A - value;
		bool halfCarry = (mRegisters.A & 0xF) < (value & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (value & 0xFF);

		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Compare a one byte immediate value to A
	 */
	void CPU::CP_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		bool zero = mRegisters.A == n;
		bool halfCarry = (mRegisters.A & 0xF) < (n & 0xF);
		bool fullCarry = (mRegisters.A & 0xFF) < (n & 0xFF);

		mRegisters.AssignZeroFlag(zero);
		mRegisters.SetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register A
	 */
	void CPU::INC_A(uint16_t)
	{
		uint8_t result = mRegisters.A + 1;
		bool halfCarry = (mRegisters.A & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + 1 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register B
	 */
	void CPU::INC_B(uint16_t)
	{
		uint8_t result = mRegisters.B + 1;
		bool halfCarry = (mRegisters.B & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.B & 0xFF) + 1 > 0xFF;

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register C
	 */
	void CPU::INC_C(uint16_t)
	{
		uint8_t result = mRegisters.C + 1;
		bool halfCarry = (mRegisters.C & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.C & 0xFF) + 1 > 0xFF;

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register D
	 */
	void CPU::INC_D(uint16_t)
	{
		uint8_t result = mRegisters.D + 1;
		bool halfCarry = (mRegisters.D & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.D & 0xFF) + 1 > 0xFF;

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register E
	 */
	void CPU::INC_E(uint16_t)
	{
		uint8_t result = mRegisters.E + 1;
		bool halfCarry = (mRegisters.E & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.E & 0xFF) + 1 > 0xFF;

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register H
	 */
	void CPU::INC_H(uint16_t)
	{
		uint8_t result = mRegisters.H + 1;
		bool halfCarry = (mRegisters.H & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) + 1 > 0xFF;

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register L
	 */
	void CPU::INC_L(uint16_t)
	{
		uint8_t result = mRegisters.L + 1;
		bool halfCarry = (mRegisters.L & 0xF) + 1 > 0xF;
		bool fullCarry = (mRegisters.L & 0xFF) + 1 > 0xFF;

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment the value at address HL
	 */
	void CPU::INC_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A + value;
		bool halfCarry = (mRegisters.A & 0xF) + (value & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) + (value & 0xFF) > 0xFF;

		mMemory.WriteByte(mRegisters.HL, result);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register A
	 */
	void CPU::DEC_A(uint16_t)
	{
		uint8_t result = mRegisters.A - 1;
		bool halfCarry = (mRegisters.A & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) - 1 > 0xFF;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register B
	 */
	void CPU::DEC_B(uint16_t)
	{
		uint8_t result = mRegisters.B - 1;
		bool halfCarry = (mRegisters.B & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.B & 0xFF) - 1 > 0xFF;

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register C
	 */
	void CPU::DEC_C(uint16_t)
	{
		uint8_t result = mRegisters.C - 1;
		bool halfCarry = (mRegisters.C & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.C & 0xFF) - 1 > 0xFF;

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register D
	 */
	void CPU::DEC_D(uint16_t)
	{
		uint8_t result = mRegisters.D - 1;
		bool halfCarry = (mRegisters.D & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.D & 0xFF) - 1 > 0xFF;

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register E
	 */
	void CPU::DEC_E(uint16_t)
	{
		uint8_t result = mRegisters.E - 1;
		bool halfCarry = (mRegisters.E & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.E & 0xFF) - 1 > 0xFF;

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register H
	 */
	void CPU::DEC_H(uint16_t)
	{
		uint8_t result = mRegisters.H - 1;
		bool halfCarry = (mRegisters.H & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) - 1 > 0xFF;

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement register L
	 */
	void CPU::DEC_L(uint16_t)
	{
		uint8_t result = mRegisters.L - 1;
		bool halfCarry = (mRegisters.L & 0xF) - 1 > 0xF;
		bool fullCarry = (mRegisters.L & 0xFF) - 1 > 0xFF;

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Decrement the value at address HL
	 */
	void CPU::DEC_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = mRegisters.A - value;
		bool halfCarry = (mRegisters.A & 0xF) - (value & 0xF) > 0xF;
		bool fullCarry = (mRegisters.A & 0xFF) - (value & 0xFF) > 0xFF;

		mMemory.WriteByte(mRegisters.HL, result);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	#pragma endregion

	#pragma region 16-Bit Arithmetic

	/**
	 * \brief Add BC into HL
	 */
	void CPU::ADD_HL_BC(uint16_t)
	{
		uint16_t result = mRegisters.HL + mRegisters.BC;
		bool halfCarry = (mRegisters.H & 0xF) + (mRegisters.B & 0xF) > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) + (mRegisters.B & 0xFF) > 0xFF;

		mRegisters.HL = result;
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add DE into HL
	 */
	void CPU::ADD_HL_DE(uint16_t)
	{
		uint16_t result = mRegisters.HL + mRegisters.DE;
		bool halfCarry = (mRegisters.H & 0xF) + (mRegisters.D & 0xF) > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) + (mRegisters.D & 0xFF) > 0xFF;

		mRegisters.HL = result;
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add HL into HL
	 */
	void CPU::ADD_HL_HL(uint16_t)
	{
		uint16_t result = mRegisters.HL + mRegisters.HL;
		bool halfCarry = (mRegisters.H & 0xF) + (mRegisters.H & 0xF) > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) + (mRegisters.H & 0xFF) > 0xFF;

		mRegisters.HL = result;
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add SP into HL
	 */
	void CPU::ADD_HL_SP(uint16_t)
	{
		uint16_t result = mRegisters.HL + mRegisters.SP;
		bool halfCarry = (mRegisters.H & 0xF) + ((mRegisters.SP & 0xF00) >> 8) > 0xF;
		bool fullCarry = (mRegisters.H & 0xFF) + ((mRegisters.SP & 0xFF00) >> 8) > 0xFF;

		mRegisters.HL = result;
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Add a two byte immediate value into SP
	 */
	void CPU::ADD_SP_n(uint16_t operand)
	{
		uint8_t n = static_cast<uint8_t>(operand & 0xFF);
		uint16_t result = mRegisters.SP + n;
		bool halfCarry = ((mRegisters.SP & 0xF00) >> 8) + (n & 0xF) > 0xF;
		bool fullCarry = ((mRegisters.SP & 0xFF00) >> 8) + (n & 0xFF) > 0xFF;

		mRegisters.SP = result;
		mRegisters.ResetZeroFlag();
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag(halfCarry);
		mRegisters.AssignCarryFlag(fullCarry);
	}

	/**
	 * \brief Increment register BC
	 */
	void CPU::INC_BC(uint16_t)
	{
		mRegisters.BC = mRegisters.BC + 1;
	}

	/**
	 * \brief Increment register DE
	 */
	void CPU::INC_DE(uint16_t)
	{
		mRegisters.DE = mRegisters.DE + 1;
	}

	/**
	 * \brief Increment register HL
	 */
	void CPU::INC_HL(uint16_t)
	{
		mRegisters.HL = mRegisters.HL + 1;
	}

	/**
	 * \brief Increment register SP
	 */
	void CPU::INC_SP(uint16_t)
	{
		mRegisters.SP = mRegisters.SP + 1;
	}

	/**
	 * \brief Decrement register BC
	 */
	void CPU::DEC_BC(uint16_t)
	{
		mRegisters.BC = mRegisters.BC + 1;
	}

	/**
	 * \brief Decrement register DE
	 */
	void CPU::DEC_DE(uint16_t)
	{
		mRegisters.DE = mRegisters.DE + 1;
	}

	/**
	 * \brief Decrement register HL
	 */
	void CPU::DEC_HL(uint16_t)
	{
		mRegisters.HL = mRegisters.HL + 1;
	}

	/**
	 * \brief Decrement register SP
	 */
	void CPU::DEC_SP(uint16_t)
	{
		mRegisters.SP = mRegisters.SP + 1;
	}

	#pragma endregion

	#pragma region Miscellaneous

	/**
	 * \brief Swap upper & lower nibles of A
	 */
	void CPU::SWAP_A(uint16_t)
	{
		uint8_t result = ((mRegisters.A & 0xF0) >> 4) | ((mRegisters.A & 0x0F) << 4);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of B
	 */
	void CPU::SWAP_B(uint16_t)
	{
		uint8_t result = ((mRegisters.B & 0xF0) >> 4) | ((mRegisters.B & 0x0F) << 4);

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of C
	 */
	void CPU::SWAP_C(uint16_t)
	{
		uint8_t result = ((mRegisters.C & 0xF0) >> 4) | ((mRegisters.C & 0x0F) << 4);

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of D
	 */
	void CPU::SWAP_D(uint16_t)
	{
		uint8_t result = ((mRegisters.D & 0xF0) >> 4) | ((mRegisters.D & 0x0F) << 4);

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of E
	 */
	void CPU::SWAP_E(uint16_t)
	{
		uint8_t result = ((mRegisters.E & 0xF0) >> 4) | ((mRegisters.E & 0x0F) << 4);

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of H
	 */
	void CPU::SWAP_H(uint16_t)
	{
		uint8_t result = ((mRegisters.H & 0xF0) >> 4) | ((mRegisters.H & 0x0F) << 4);

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of L
	 */
	void CPU::SWAP_L(uint16_t)
	{
		uint8_t result = ((mRegisters.L & 0xF0) >> 4) | ((mRegisters.L & 0x0F) << 4);

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Swap upper & lower nibles of the value at address HL
	 */
	void CPU::SWAP_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint8_t result = ((value & 0xF0) >> 4) | ((value & 0x0F) << 4);

		mMemory.WriteByte(mRegisters.HL, result);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.ResetCarryFlag();
	}

	/**
	 * \brief Decimal adjust register A (Make BCD)
	 * \remarks Based on http://z80-heaven.wikidot.com/instructions-set:daa
	 */
	void CPU::DAA(uint16_t)
	{
		uint8_t value = mRegisters.A;

		if ((value & 0x0F) > 9 || mRegisters.GetHalfCarryFlag())
		{
			value += 0x06;
		}

		if (((value & 0xF0) >> 4) > 9 || mRegisters.GetCarryFlag())
		{
			value += 0x60;
			mRegisters.SetCarryFlag();
		}
		else
		{
			mRegisters.ResetCarryFlag();
		}

		mRegisters.A = value;
		mRegisters.AssignZeroFlag(value == 0);
		mRegisters.ResetHalfCarryFlag();
	}

	/**
	 * \brief Complement register A (flip bits)
	 */
	void CPU::CPL(uint16_t)
	{
		mRegisters.A = ~mRegisters.A;
		mRegisters.SetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Complement carry flag
	 */
	void CPU::CCF(uint16_t)
	{
		mRegisters.AssignCarryFlag(!mRegisters.GetCarryFlag());
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
	}

	/**
	 * \brief Set carry flag
	 */
	void CPU::SCF(uint16_t)
	{
		mRegisters.SetCarryFlag();
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
	}

	/**
	 * \brief Perform no operation
	 */
	void CPU::NOP(uint16_t)
	{
	}

	/**
	 * \brief Power down CPU until an interrupt occurs
	 */
	void CPU::HALT(uint16_t)
	{
		mHalted = true;
	}

	/**
	 * \brief Halt CPU & display until button pressed
	 */
	void CPU::STOP(uint16_t)
	{
		// TODO figure out what to do here
	}

	/**
	 * \brief Disable interrupts (after next instruction)
	 */
	void CPU::DI(uint16_t)
	{
		mDisableInterruptsAfterNextInstruction = true;
	}

	/**
	 * \brief Enable interrupts (after next instruction)
	 */
	void CPU::EI(uint16_t)
	{
		mEnableInterruptsAfterNextInstruction = true;
	}

	#pragma endregion

	#pragma region Rotates & Shift

	/**
	 * \brief Rotate A left
	 */
	void CPU::RLCA(uint16_t)
	{
		uint16_t result = mRegisters.A << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.A = result & 0xFF;
		mRegisters.ResetZeroFlag(); // ???
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate A left through carry
	 */
	void CPU::RLA(uint16_t)
	{
		uint16_t result = mRegisters.A << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.A = result & 0xFF;
		mRegisters.ResetZeroFlag(); // ???
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate A right
	 */
	void CPU::RRCA(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		uint8_t result = (mRegisters.A >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.A = result;
		mRegisters.ResetZeroFlag(); // ???
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate A right with carry
	 */
	void CPU::RRA(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		uint8_t result = (mRegisters.A >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.A = result;
		mRegisters.ResetZeroFlag(); // ???
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate A left
	 */
	void CPU::RLC_A(uint16_t)
	{
		uint16_t result = mRegisters.A << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.A = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate B left
	 */
	void CPU::RLC_B(uint16_t)
	{
		uint16_t result = mRegisters.B << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.B = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate C left
	 */
	void CPU::RLC_C(uint16_t)
	{
		uint16_t result = mRegisters.C << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.C = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate D left
	 */
	void CPU::RLC_D(uint16_t)
	{
		uint16_t result = mRegisters.D << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.D = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate E left
	 */
	void CPU::RLC_E(uint16_t)
	{
		uint16_t result = mRegisters.E << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.E = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate H left
	 */
	void CPU::RLC_H(uint16_t)
	{
		uint16_t result = mRegisters.H << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.H = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate L left
	 */
	void CPU::RLC_L(uint16_t)
	{
		uint16_t result = mRegisters.L << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mRegisters.L = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate the value at address HL left
	 */
	void CPU::RLC_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint16_t result = value << 1;
		bool carry = result > 0xFF;
		result += carry ? 1 : 0;

		mMemory.WriteByte(mRegisters.HL, result & 0xFF);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate A left through carry
	 */
	void CPU::RL_A(uint16_t)
	{
		uint16_t result = mRegisters.A << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.A = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate B left through carry
	 */
	void CPU::RL_B(uint16_t)
	{
		uint16_t result = mRegisters.B << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.B = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate C left through carry
	 */
	void CPU::RL_C(uint16_t)
	{
		uint16_t result = mRegisters.C << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.C = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate D left through carry
	 */
	void CPU::RL_D(uint16_t)
	{
		uint16_t result = mRegisters.D << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.D = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate E left through carry
	 */
	void CPU::RL_E(uint16_t)
	{
		uint16_t result = mRegisters.E << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.E = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate H left through carry
	 */
	void CPU::RL_H(uint16_t)
	{
		uint16_t result = mRegisters.H << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.H = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate L left through carry
	 */
	void CPU::RL_L(uint16_t)
	{
		uint16_t result = mRegisters.L << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mRegisters.L = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate the value at address HL left through carry
	 */
	void CPU::RL_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint16_t result = value << 1;
		result += mRegisters.GetCarryFlag() ? 1 : 0;
		bool carry = result > 0xFF;

		mMemory.WriteByte(mRegisters.HL, result & 0xFF);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Rotate A right
	 */
	void CPU::RRC_A(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		uint8_t result = (mRegisters.A >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate B right
	 */
	void CPU::RRC_B(uint16_t)
	{
		bool carry = (mRegisters.B & 0x1) != 0;
		uint8_t result = (mRegisters.B >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate C right
	 */
	void CPU::RRC_C(uint16_t)
	{
		bool carry = (mRegisters.C & 0x1) != 0;
		uint8_t result = (mRegisters.C >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate D right
	 */
	void CPU::RRC_D(uint16_t)
	{
		bool carry = (mRegisters.D & 0x1) != 0;
		uint8_t result = (mRegisters.D >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate E right
	 */
	void CPU::RRC_E(uint16_t)
	{
		bool carry = (mRegisters.E & 0x1) != 0;
		uint8_t result = (mRegisters.E >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate H right
	 */
	void CPU::RRC_H(uint16_t)
	{
		bool carry = (mRegisters.H & 0x1) != 0;
		uint8_t result = (mRegisters.H >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate L right
	 */
	void CPU::RRC_L(uint16_t)
	{
		bool carry = (mRegisters.L & 0x1) != 0;
		uint8_t result = (mRegisters.L >> 1) + (carry ? 0x80 : 0x00);

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate the value at address HL right
	 */
	void CPU::RRC_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		bool carry = (value & 0x1) != 0;
		uint8_t result = (value >> 1) + (carry ? 0x80 : 0x00);

		mMemory.WriteByte(mRegisters.HL, result);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate A right with carry
	 */
	void CPU::RR_A(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		uint8_t result = (mRegisters.A >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate B right with carry
	 */
	void CPU::RR_B(uint16_t)
	{
		bool carry = (mRegisters.B & 0x1) != 0;
		uint8_t result = (mRegisters.B >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate C right with carry
	 */
	void CPU::RR_C(uint16_t)
	{
		bool carry = (mRegisters.C & 0x1) != 0;
		uint8_t result = (mRegisters.C >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate D right with carry
	 */
	void CPU::RR_D(uint16_t)
	{
		bool carry = (mRegisters.D & 0x1) != 0;
		uint8_t result = (mRegisters.D >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate E right with carry
	 */
	void CPU::RR_E(uint16_t)
	{
		bool carry = (mRegisters.E & 0x1) != 0;
		uint8_t result = (mRegisters.E >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate H right with carry
	 */
	void CPU::RR_H(uint16_t)
	{
		bool carry = (mRegisters.H & 0x1) != 0;
		uint8_t result = (mRegisters.H >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate L right with carry
	 */
	void CPU::RR_L(uint16_t)
	{
		bool carry = (mRegisters.L & 0x1) != 0;
		uint8_t result = (mRegisters.L >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Rotate the value at address HL right with carry
	 */
	void CPU::RR_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		bool carry = (value & 0x1) != 0;
		uint8_t result = (value >> 1) + (mRegisters.GetCarryFlag() ? 0x80 : 0x00);

		mMemory.WriteByte(mRegisters.HL, result);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift A left (into carry)
	 */
	void CPU::SLA_A(uint16_t)
	{
		uint16_t result = mRegisters.A << 1;
		bool carry = result > 0xFF;

		mRegisters.A = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift B left (into carry)
	 */
	void CPU::SLA_B(uint16_t)
	{
		uint16_t result = mRegisters.B << 1;
		bool carry = result > 0xFF;

		mRegisters.B = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift C left (into carry)
	 */
	void CPU::SLA_C(uint16_t)
	{
		uint16_t result = mRegisters.C << 1;
		bool carry = result > 0xFF;

		mRegisters.C = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift D left (into carry)
	 */
	void CPU::SLA_D(uint16_t)
	{
		uint16_t result = mRegisters.D << 1;
		bool carry = result > 0xFF;

		mRegisters.D = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift E left (into carry)
	 */
	void CPU::SLA_E(uint16_t)
	{
		uint16_t result = mRegisters.E << 1;
		bool carry = result > 0xFF;

		mRegisters.E = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift H left (into carry)
	 */
	void CPU::SLA_H(uint16_t)
	{
		uint16_t result = mRegisters.H << 1;
		bool carry = result > 0xFF;

		mRegisters.H = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift L left (into carry)
	 */
	void CPU::SLA_L(uint16_t)
	{
		uint16_t result = mRegisters.L << 1;
		bool carry = result > 0xFF;

		mRegisters.L = result & 0xFF;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift the value at address HL left (into carry)
	 */
	void CPU::SLA_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		uint16_t result = value << 1;
		bool carry = result > 0xFF;

		mMemory.WriteByte(mRegisters.HL, result & 0xFF);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 7 always goes into C
	}

	/**
	 * \brief Shift A right arithmetically (into carry)
	 */
	void CPU::SRA_A(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		bool negative = (mRegisters.A & 0x80) != 0;
		uint8_t result = (mRegisters.A >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift B right arithmetically (into carry)
	 */
	void CPU::SRA_B(uint16_t)
	{
		bool carry = (mRegisters.B & 0x1) != 0;
		bool negative = (mRegisters.B & 0x80) != 0;
		uint8_t result = (mRegisters.B >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift C right arithmetically (into carry)
	 */
	void CPU::SRA_C(uint16_t)
	{
		bool carry = (mRegisters.C & 0x1) != 0;
		bool negative = (mRegisters.C & 0x80) != 0;
		uint8_t result = (mRegisters.C >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift D right arithmetically (into carry)
	 */
	void CPU::SRA_D(uint16_t)
	{
		bool carry = (mRegisters.D & 0x1) != 0;
		bool negative = (mRegisters.D & 0x80) != 0;
		uint8_t result = (mRegisters.D >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift E right arithmetically (into carry)
	 */
	void CPU::SRA_E(uint16_t)
	{
		bool carry = (mRegisters.E & 0x1) != 0;
		bool negative = (mRegisters.E & 0x80) != 0;
		uint8_t result = (mRegisters.E >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift H right arithmetically (into carry)
	 */
	void CPU::SRA_H(uint16_t)
	{
		bool carry = (mRegisters.H & 0x1) != 0;
		bool negative = (mRegisters.H & 0x80) != 0;
		uint8_t result = (mRegisters.H >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift L right arithmetically (into carry)
	 */
	void CPU::SRA_L(uint16_t)
	{
		bool carry = (mRegisters.L & 0x1) != 0;
		bool negative = (mRegisters.L & 0x80) != 0;
		uint8_t result = (mRegisters.L >> 1) | (negative ? 0x80 : 0x00);

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift the value at address HL right arithmetically (into carry)
	 */
	void CPU::SRA_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		bool carry = (value & 0x1) != 0;
		bool negative = (value & 0x80) != 0;
		uint8_t result = (value >> 1) | (negative ? 0x80 : 0x00);

		mMemory.WriteByte(mRegisters.HL, result & 0xFF);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift A right logically (into carry)
	 */
	void CPU::SRL_A(uint16_t)
	{
		bool carry = (mRegisters.A & 0x1) != 0;
		uint8_t result = (mRegisters.A >> 1) & 0x7F;

		mRegisters.A = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift B right logically (into carry)
	 */
	void CPU::SRL_B(uint16_t)
	{
		bool carry = (mRegisters.B & 0x1) != 0;
		uint8_t result = (mRegisters.B >> 1) & 0x7F;

		mRegisters.B = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift C right logically (into carry)
	 */
	void CPU::SRL_C(uint16_t)
	{
		bool carry = (mRegisters.C & 0x1) != 0;
		uint8_t result = (mRegisters.C >> 1) & 0x7F;

		mRegisters.C = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift D right logically (into carry)
	 */
	void CPU::SRL_D(uint16_t)
	{
		bool carry = (mRegisters.D & 0x1) != 0;
		uint8_t result = (mRegisters.D >> 1) & 0x7F;

		mRegisters.D = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift E right logically (into carry)
	 */
	void CPU::SRL_E(uint16_t)
	{
		bool carry = (mRegisters.E & 0x1) != 0;
		uint8_t result = (mRegisters.E >> 1) & 0x7F;

		mRegisters.E = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift H right logically (into carry)
	 */
	void CPU::SRL_H(uint16_t)
	{
		bool carry = (mRegisters.H & 0x1) != 0;
		uint8_t result = (mRegisters.H >> 1) & 0x7F;

		mRegisters.H = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift L right logically (into carry)
	 */
	void CPU::SRL_L(uint16_t)
	{
		bool carry = (mRegisters.L & 0x1) != 0;
		uint8_t result = (mRegisters.L >> 1) & 0x7F;

		mRegisters.L = result;
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	/**
	 * \brief Shift the value at address HL right logically (into carry)
	 */
	void CPU::SRL_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		bool carry = (value & 0x1) != 0;
		uint8_t result = (value >> 1) & 0x7F;

		mMemory.WriteByte(mRegisters.HL, result & 0xFF);
		mRegisters.AssignZeroFlag(result == 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.ResetHalfCarryFlag();
		mRegisters.AssignCarryFlag(carry); // bit 0 always goes into C
	}

	#pragma endregion

	#pragma region Bit Opcodes

	/**
	 * \brief Test bit 0 in register A
	 */
	void CPU::BIT_0_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register A
	 */
	void CPU::BIT_1_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register A
	 */
	void CPU::BIT_2_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register A
	 */
	void CPU::BIT_3_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register A
	 */
	void CPU::BIT_4_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register A
	 */
	void CPU::BIT_5_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register A
	 */
	void CPU::BIT_6_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register A
	 */
	void CPU::BIT_7_A(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.A & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register B
	 */
	void CPU::BIT_0_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register B
	 */
	void CPU::BIT_1_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register B
	 */
	void CPU::BIT_2_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register B
	 */
	void CPU::BIT_3_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register B
	 */
	void CPU::BIT_4_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register B
	 */
	void CPU::BIT_5_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register B
	 */
	void CPU::BIT_6_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register B
	 */
	void CPU::BIT_7_B(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.B & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register C
	 */
	void CPU::BIT_0_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register C
	 */
	void CPU::BIT_1_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register C
	 */
	void CPU::BIT_2_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register C
	 */
	void CPU::BIT_3_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register C
	 */
	void CPU::BIT_4_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register C
	 */
	void CPU::BIT_5_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register C
	 */
	void CPU::BIT_6_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register C
	 */
	void CPU::BIT_7_C(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.C & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register D
	 */
	void CPU::BIT_0_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register D
	 */
	void CPU::BIT_1_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register D
	 */
	void CPU::BIT_2_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register D
	 */
	void CPU::BIT_3_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register D
	 */
	void CPU::BIT_4_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register D
	 */
	void CPU::BIT_5_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register D
	 */
	void CPU::BIT_6_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register D
	 */
	void CPU::BIT_7_D(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.D & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register E
	 */
	void CPU::BIT_0_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register E
	 */
	void CPU::BIT_1_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register E
	 */
	void CPU::BIT_2_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register E
	 */
	void CPU::BIT_3_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register E
	 */
	void CPU::BIT_4_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register E
	 */
	void CPU::BIT_5_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register E
	 */
	void CPU::BIT_6_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register E
	 */
	void CPU::BIT_7_E(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.E & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register H
	 */
	void CPU::BIT_0_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register H
	 */
	void CPU::BIT_1_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register H
	 */
	void CPU::BIT_2_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register H
	 */
	void CPU::BIT_3_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register H
	 */
	void CPU::BIT_4_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register H
	 */
	void CPU::BIT_5_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register H
	 */
	void CPU::BIT_6_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register H
	 */
	void CPU::BIT_7_H(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.H & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in register L
	 */
	void CPU::BIT_0_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in register L
	 */
	void CPU::BIT_1_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in register L
	 */
	void CPU::BIT_2_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in register L
	 */
	void CPU::BIT_3_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in register L
	 */
	void CPU::BIT_4_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in register L
	 */
	void CPU::BIT_5_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in register L
	 */
	void CPU::BIT_6_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in register L
	 */
	void CPU::BIT_7_L(uint16_t)
	{
		mRegisters.AssignZeroFlag((mRegisters.L & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 0 in the value at memory location HL
	 */
	void CPU::BIT_0_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00000001) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 1 in the value at memory location HL
	 */
	void CPU::BIT_1_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00000010) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 2 in the value at memory location HL
	 */
	void CPU::BIT_2_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00000100) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 3 in the value at memory location HL
	 */
	void CPU::BIT_3_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00001000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 4 in the value at memory location HL
	 */
	void CPU::BIT_4_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00010000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 5 in the value at memory location HL
	 */
	void CPU::BIT_5_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b00100000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 6 in the value at memory location HL
	 */
	void CPU::BIT_6_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b01000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Test bit 7 in the value at memory location HL
	 */
	void CPU::BIT_7_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		mRegisters.AssignZeroFlag((value & 0b10000000) != 0);
		mRegisters.ResetSubtractFlag();
		mRegisters.SetHalfCarryFlag();
	}

	/**
	 * \brief Set bit 0 in register A
	 */
	void CPU::SET_0_A(uint16_t)
	{
		mRegisters.A |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register A
	 */
	void CPU::SET_1_A(uint16_t)
	{
		mRegisters.A |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register A
	 */
	void CPU::SET_2_A(uint16_t)
	{
		mRegisters.A |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register A
	 */
	void CPU::SET_3_A(uint16_t)
	{
		mRegisters.A |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register A
	 */
	void CPU::SET_4_A(uint16_t)
	{
		mRegisters.A |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register A
	 */
	void CPU::SET_5_A(uint16_t)
	{
		mRegisters.A |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register A
	 */
	void CPU::SET_6_A(uint16_t)
	{
		mRegisters.A |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register A
	 */
	void CPU::SET_7_A(uint16_t)
	{
		mRegisters.A |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register B
	 */
	void CPU::SET_0_B(uint16_t)
	{
		mRegisters.B |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register B
	 */
	void CPU::SET_1_B(uint16_t)
	{
		mRegisters.B |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register B
	 */
	void CPU::SET_2_B(uint16_t)
	{
		mRegisters.B |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register B
	 */
	void CPU::SET_3_B(uint16_t)
	{
		mRegisters.B |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register B
	 */
	void CPU::SET_4_B(uint16_t)
	{
		mRegisters.B |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register B
	 */
	void CPU::SET_5_B(uint16_t)
	{
		mRegisters.B |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register B
	 */
	void CPU::SET_6_B(uint16_t)
	{
		mRegisters.B |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register B
	 */
	void CPU::SET_7_B(uint16_t)
	{
		mRegisters.B |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register C
	 */
	void CPU::SET_0_C(uint16_t)
	{
		mRegisters.C |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register C
	 */
	void CPU::SET_1_C(uint16_t)
	{
		mRegisters.C |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register C
	 */
	void CPU::SET_2_C(uint16_t)
	{
		mRegisters.C |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register C
	 */
	void CPU::SET_3_C(uint16_t)
	{
		mRegisters.C |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register C
	 */
	void CPU::SET_4_C(uint16_t)
	{
		mRegisters.C |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register C
	 */
	void CPU::SET_5_C(uint16_t)
	{
		mRegisters.C |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register C
	 */
	void CPU::SET_6_C(uint16_t)
	{
		mRegisters.C |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register C
	 */
	void CPU::SET_7_C(uint16_t)
	{
		mRegisters.C |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register D
	 */
	void CPU::SET_0_D(uint16_t)
	{
		mRegisters.D |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register D
	 */
	void CPU::SET_1_D(uint16_t)
	{
		mRegisters.D |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register D
	 */
	void CPU::SET_2_D(uint16_t)
	{
		mRegisters.D |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register D
	 */
	void CPU::SET_3_D(uint16_t)
	{
		mRegisters.D |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register D
	 */
	void CPU::SET_4_D(uint16_t)
	{
		mRegisters.D |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register D
	 */
	void CPU::SET_5_D(uint16_t)
	{
		mRegisters.D |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register D
	 */
	void CPU::SET_6_D(uint16_t)
	{
		mRegisters.D |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register D
	 */
	void CPU::SET_7_D(uint16_t)
	{
		mRegisters.D |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register E
	 */
	void CPU::SET_0_E(uint16_t)
	{
		mRegisters.E |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register E
	 */
	void CPU::SET_1_E(uint16_t)
	{
		mRegisters.E |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register E
	 */
	void CPU::SET_2_E(uint16_t)
	{
		mRegisters.E |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register E
	 */
	void CPU::SET_3_E(uint16_t)
	{
		mRegisters.E |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register E
	 */
	void CPU::SET_4_E(uint16_t)
	{
		mRegisters.E |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register E
	 */
	void CPU::SET_5_E(uint16_t)
	{
		mRegisters.E |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register E
	 */
	void CPU::SET_6_E(uint16_t)
	{
		mRegisters.E |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register E
	 */
	void CPU::SET_7_E(uint16_t)
	{
		mRegisters.E |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register H
	 */
	void CPU::SET_0_H(uint16_t)
	{
		mRegisters.H |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register H
	 */
	void CPU::SET_1_H(uint16_t)
	{
		mRegisters.H |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register H
	 */
	void CPU::SET_2_H(uint16_t)
	{
		mRegisters.H |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register H
	 */
	void CPU::SET_3_H(uint16_t)
	{
		mRegisters.H |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register H
	 */
	void CPU::SET_4_H(uint16_t)
	{
		mRegisters.H |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register H
	 */
	void CPU::SET_5_H(uint16_t)
	{
		mRegisters.H |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register H
	 */
	void CPU::SET_6_H(uint16_t)
	{
		mRegisters.H |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register H
	 */
	void CPU::SET_7_H(uint16_t)
	{
		mRegisters.H |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in register L
	 */
	void CPU::SET_0_L(uint16_t)
	{
		mRegisters.L |= 0b00000001;
	}

	/**
	 * \brief Set bit 1 in register L
	 */
	void CPU::SET_1_L(uint16_t)
	{
		mRegisters.L |= 0b00000010;
	}

	/**
	 * \brief Set bit 2 in register L
	 */
	void CPU::SET_2_L(uint16_t)
	{
		mRegisters.L |= 0b00000100;
	}

	/**
	 * \brief Set bit 3 in register L
	 */
	void CPU::SET_3_L(uint16_t)
	{
		mRegisters.L |= 0b00001000;
	}

	/**
	 * \brief Set bit 4 in register L
	 */
	void CPU::SET_4_L(uint16_t)
	{
		mRegisters.L |= 0b00010000;
	}

	/**
	 * \brief Set bit 5 in register L
	 */
	void CPU::SET_5_L(uint16_t)
	{
		mRegisters.L |= 0b00100000;
	}

	/**
	 * \brief Set bit 6 in register L
	 */
	void CPU::SET_6_L(uint16_t)
	{
		mRegisters.L |= 0b01000000;
	}

	/**
	 * \brief Set bit 7 in register L
	 */
	void CPU::SET_7_L(uint16_t)
	{
		mRegisters.L |= 0b10000000;
	}

	/**
	 * \brief Set bit 0 in the value at address HL
	 */
	void CPU::SET_0_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00000001;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 1 in the value at address HL
	 */
	void CPU::SET_1_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00000010;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 2 in the value at address HL
	 */
	void CPU::SET_2_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00000100;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 3 in the value at address HL
	 */
	void CPU::SET_3_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00001000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 4 in the value at address HL
	 */
	void CPU::SET_4_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00010000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 5 in the value at address HL
	 */
	void CPU::SET_5_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b00100000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 6 in the value at address HL
	 */
	void CPU::SET_6_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b01000000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Set bit 7 in the value at address HL
	 */
	void CPU::SET_7_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value |= 0b10000000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 0 in register A
	 */
	void CPU::RES_0_A(uint16_t)
	{
		mRegisters.A &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register A
	 */
	void CPU::RES_1_A(uint16_t)
	{
		mRegisters.A &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register A
	 */
	void CPU::RES_2_A(uint16_t)
	{
		mRegisters.A &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register A
	 */
	void CPU::RES_3_A(uint16_t)
	{
		mRegisters.A &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register A
	 */
	void CPU::RES_4_A(uint16_t)
	{
		mRegisters.A &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register A
	 */
	void CPU::RES_5_A(uint16_t)
	{
		mRegisters.A &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register A
	 */
	void CPU::RES_6_A(uint16_t)
	{
		mRegisters.A &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register A
	 */
	void CPU::RES_7_A(uint16_t)
	{
		mRegisters.A &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register B
	 */
	void CPU::RES_0_B(uint16_t)
	{
		mRegisters.B &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register B
	 */
	void CPU::RES_1_B(uint16_t)
	{
		mRegisters.B &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register B
	 */
	void CPU::RES_2_B(uint16_t)
	{
		mRegisters.B &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register B
	 */
	void CPU::RES_3_B(uint16_t)
	{
		mRegisters.B &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register B
	 */
	void CPU::RES_4_B(uint16_t)
	{
		mRegisters.B &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register B
	 */
	void CPU::RES_5_B(uint16_t)
	{
		mRegisters.B &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register B
	 */
	void CPU::RES_6_B(uint16_t)
	{
		mRegisters.B &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register B
	 */
	void CPU::RES_7_B(uint16_t)
	{
		mRegisters.B &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register C
	 */
	void CPU::RES_0_C(uint16_t)
	{
		mRegisters.C &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register C
	 */
	void CPU::RES_1_C(uint16_t)
	{
		mRegisters.C &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register C
	 */
	void CPU::RES_2_C(uint16_t)
	{
		mRegisters.C &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register C
	 */
	void CPU::RES_3_C(uint16_t)
	{
		mRegisters.C &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register C
	 */
	void CPU::RES_4_C(uint16_t)
	{
		mRegisters.C &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register C
	 */
	void CPU::RES_5_C(uint16_t)
	{
		mRegisters.C &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register C
	 */
	void CPU::RES_6_C(uint16_t)
	{
		mRegisters.C &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register C
	 */
	void CPU::RES_7_C(uint16_t)
	{
		mRegisters.C &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register D
	 */
	void CPU::RES_0_D(uint16_t)
	{
		mRegisters.D &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register D
	 */
	void CPU::RES_1_D(uint16_t)
	{
		mRegisters.D &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register D
	 */
	void CPU::RES_2_D(uint16_t)
	{
		mRegisters.D &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register D
	 */
	void CPU::RES_3_D(uint16_t)
	{
		mRegisters.D &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register D
	 */
	void CPU::RES_4_D(uint16_t)
	{
		mRegisters.D &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register D
	 */
	void CPU::RES_5_D(uint16_t)
	{
		mRegisters.D &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register D
	 */
	void CPU::RES_6_D(uint16_t)
	{
		mRegisters.D &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register D
	 */
	void CPU::RES_7_D(uint16_t)
	{
		mRegisters.D &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register E
	 */
	void CPU::RES_0_E(uint16_t)
	{
		mRegisters.E &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register E
	 */
	void CPU::RES_1_E(uint16_t)
	{
		mRegisters.E &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register E
	 */
	void CPU::RES_2_E(uint16_t)
	{
		mRegisters.E &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register E
	 */
	void CPU::RES_3_E(uint16_t)
	{
		mRegisters.E &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register E
	 */
	void CPU::RES_4_E(uint16_t)
	{
		mRegisters.E &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register E
	 */
	void CPU::RES_5_E(uint16_t)
	{
		mRegisters.E &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register E
	 */
	void CPU::RES_6_E(uint16_t)
	{
		mRegisters.E &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register E
	 */
	void CPU::RES_7_E(uint16_t)
	{
		mRegisters.E &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register H
	 */
	void CPU::RES_0_H(uint16_t)
	{
		mRegisters.H &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register H
	 */
	void CPU::RES_1_H(uint16_t)
	{
		mRegisters.H &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register H
	 */
	void CPU::RES_2_H(uint16_t)
	{
		mRegisters.H &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register H
	 */
	void CPU::RES_3_H(uint16_t)
	{
		mRegisters.H &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register H
	 */
	void CPU::RES_4_H(uint16_t)
	{
		mRegisters.H &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register H
	 */
	void CPU::RES_5_H(uint16_t)
	{
		mRegisters.H &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register H
	 */
	void CPU::RES_6_H(uint16_t)
	{
		mRegisters.H &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register H
	 */
	void CPU::RES_7_H(uint16_t)
	{
		mRegisters.H &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in register L
	 */
	void CPU::RES_0_L(uint16_t)
	{
		mRegisters.L &= ~0b00000001;
	}

	/**
	 * \brief Reset (clear) bit 1 in register L
	 */
	void CPU::RES_1_L(uint16_t)
	{
		mRegisters.L &= ~0b00000010;
	}

	/**
	 * \brief Reset (clear) bit 2 in register L
	 */
	void CPU::RES_2_L(uint16_t)
	{
		mRegisters.L &= ~0b00000100;
	}

	/**
	 * \brief Reset (clear) bit 3 in register L
	 */
	void CPU::RES_3_L(uint16_t)
	{
		mRegisters.L &= ~0b00001000;
	}

	/**
	 * \brief Reset (clear) bit 4 in register L
	 */
	void CPU::RES_4_L(uint16_t)
	{
		mRegisters.L &= ~0b00010000;
	}

	/**
	 * \brief Reset (clear) bit 5 in register L
	 */
	void CPU::RES_5_L(uint16_t)
	{
		mRegisters.L &= ~0b00100000;
	}

	/**
	 * \brief Reset (clear) bit 6 in register L
	 */
	void CPU::RES_6_L(uint16_t)
	{
		mRegisters.L &= ~0b01000000;
	}

	/**
	 * \brief Reset (clear) bit 7 in register L
	 */
	void CPU::RES_7_L(uint16_t)
	{
		mRegisters.L &= ~0b10000000;
	}

	/**
	 * \brief Reset (clear) bit 0 in the value at address HL
	 */
	void CPU::RES_0_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00000001;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 1 in the value at address HL
	 */
	void CPU::RES_1_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00000010;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 2 in the value at address HL
	 */
	void CPU::RES_2_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00000100;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 3 in the value at address HL
	 */
	void CPU::RES_3_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00001000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 4 in the value at address HL
	 */
	void CPU::RES_4_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00010000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 5 in the value at address HL
	 */
	void CPU::RES_5_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b00100000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 6 in the value at address HL
	 */
	void CPU::RES_6_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b01000000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	/**
	 * \brief Reset (clear) bit 7 in the value at address HL
	 */
	void CPU::RES_7_aHL(uint16_t)
	{
		uint8_t value = mMemory.ReadByte(mRegisters.HL);
		value &= ~0b10000000;
		mMemory.WriteByte(mRegisters.HL, value);
	}

	#pragma endregion

	#pragma region Jumps

	/**
	 * \brief Jump to two byte immediate address
	 */
	void CPU::JP_nn(uint16_t operand)
	{
		mRegisters.PC = operand;
	}

	/**
	 * \brief Jump to two byte immediate address if the zero flag is not set
	 */
	void CPU::JP_NZ_nn(uint16_t operand)
	{
		if (!mRegisters.GetZeroFlag())
		{
			mRegisters.PC = operand;
		}
	}

	/**
	 * \brief Jump to two byte immediate address if the zero flag is set
	 */
	void CPU::JP_Z_nn(uint16_t operand)
	{
		if (mRegisters.GetZeroFlag())
		{
			mRegisters.PC = operand;
		}
	}

	/**
	 * \brief Jump to two byte immediate address if the carry flag is not set
	 */
	void CPU::JP_NC_nn(uint16_t operand)
	{
		if (!mRegisters.GetCarryFlag())
		{
			mRegisters.PC = operand;
		}
	}

	/**
	 * \brief Jump to two byte immediate address if the carry flag is set
	 */
	void CPU::JP_C_nn(uint16_t operand)
	{
		if (mRegisters.GetCarryFlag())
		{
			mRegisters.PC = operand;
		}
	}

	/**
	 * \brief Jump to address contained in HL
	 */
	void CPU::JP_aHL(uint16_t)
	{
		mRegisters.PC = mRegisters.HL;
	}

	/**
	 * \brief Add one byte immediate to current address and jump to it
	 */
	void CPU::JR_n(uint16_t operand)
	{
		int8_t offset = static_cast<int8_t>(operand & 0xFF);
		mRegisters.PC += offset;
	}

	/**
	 * \brief Add one byte immediate to current address and jump to it if the zero flag is not set
	 */
	void CPU::JR_NZ_n(uint16_t operand)
	{
		if (!mRegisters.GetZeroFlag())
		{
			int8_t offset = static_cast<int8_t>(operand & 0xFF);
			mRegisters.PC += offset;
		}
	}

	/**
	 * \brief Add one byte immediate to current address and jump to it if the zero flag is set
	 */
	void CPU::JR_Z_n(uint16_t operand)
	{
		if (mRegisters.GetZeroFlag())
		{
			int8_t offset = static_cast<int8_t>(operand & 0xFF);
			mRegisters.PC += offset;
		}
	}

	/**
	 * \brief Add one byte immediate to current address and jump to it if the carry flag is not set
	 */
	void CPU::JR_NC_n(uint16_t operand)
	{
		if (!mRegisters.GetCarryFlag())
		{
			int8_t offset = static_cast<int8_t>(operand & 0xFF);
			mRegisters.PC += offset;
		}
	}

	/**
	 * \brief Add one byte immediate to current address and jump to it if the carry flag is set
	 */
	void CPU::JR_C_n(uint16_t operand)
	{
		if (mRegisters.GetCarryFlag())
		{
			int8_t offset = static_cast<int8_t>(operand & 0xFF);
			mRegisters.PC += offset;
		}
	}

	#pragma endregion

	#pragma region Calls

	/**
	 * \brief Push address of next instruction onto stack and then jump to the two byte immediate value
	 */
	void CPU::CALL_nn(uint16_t operand)
	{
		// PC has already been incremented when execution is happening
		PushWordToStack(mRegisters.PC);
		mRegisters.PC = operand;
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to the two byte immediate value if the zero flag is not set
	 */
	void CPU::CALL_NZ_nn(uint16_t operand)
	{
		if (!mRegisters.GetZeroFlag())
		{
			CALL_nn(operand);
		}
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to the two byte immediate value if the zero flag is set
	 */
	void CPU::CALL_Z_nn(uint16_t operand)
	{
		if (mRegisters.GetZeroFlag())
		{
			CALL_nn(operand);
		}
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to the two byte immediate value if the carry flag is not set
	 */
	void CPU::CALL_NC_nn(uint16_t operand)
	{
		if (!mRegisters.GetCarryFlag())
		{
			CALL_nn(operand);
		}
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to the two byte immediate value if the carry flag is set
	 */
	void CPU::CALL_C_nn(uint16_t operand)
	{
		if (mRegisters.GetCarryFlag())
		{
			CALL_nn(operand);
		}
	}

	#pragma endregion

	#pragma region Restarts

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0000
	 */
	void CPU::RST_00(uint16_t)
	{
		CALL_nn(0x0000);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0008
	 */
	void CPU::RST_08(uint16_t)
	{
		CALL_nn(0x0008);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0010
	 */
	void CPU::RST_10(uint16_t)
	{
		CALL_nn(0x0010);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0018
	 */
	void CPU::RST_18(uint16_t)
	{
		CALL_nn(0x0018);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0020
	 */
	void CPU::RST_20(uint16_t)
	{
		CALL_nn(0x0020);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0028
	 */
	void CPU::RST_28(uint16_t)
	{
		CALL_nn(0x0028);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0030
	 */
	void CPU::RST_30(uint16_t)
	{
		CALL_nn(0x0030);
	}

	/**
	 * \brief Push address of next instruction onto stack and then jump to address 0x0038
	 */
	void CPU::RST_38(uint16_t)
	{
		CALL_nn(0x0038);
	}

	#pragma endregion

	#pragma region Returns

	/**
	 * \brief Pop two bytes from stack & jump to that address
	 */
	void CPU::RET(uint16_t)
	{
		uint16_t address = PopWordFromStack();
		mRegisters.PC = address;
	}

	/**
	 * \brief Pop two bytes from stack & jump to that address if the zero flag is not set
	 */
	void CPU::RET_NZ(uint16_t operand)
	{
		if (!mRegisters.GetZeroFlag())
		{
			RET(operand);
		}
	}

	/**
	 * \brief Pop two bytes from stack & jump to that address if the zero flag is set
	 */
	void CPU::RET_Z(uint16_t operand)
	{
		if (mRegisters.GetZeroFlag())
		{
			RET(operand);
		}
	}

	/**
	 * \brief Pop two bytes from stack & jump to that address if the carry flag is not set
	 */
	void CPU::RET_NC(uint16_t operand)
	{
		if (!mRegisters.GetCarryFlag())
		{
			RET(operand);
		}
	}

	/**
	 * \brief Pop two bytes from stack & jump to that address if the carry flag is set
	 */
	void CPU::RET_C(uint16_t operand)
	{
		if (mRegisters.GetCarryFlag())
		{
			RET(operand);
		}
	}

	/**
	 * \brief Pop two bytes from stack & jump to that address then enable interrupts
	 */
	void CPU::RETI(uint16_t operand)
	{
		RET(operand);
		EI(operand);
	}

	#pragma endregion
}
