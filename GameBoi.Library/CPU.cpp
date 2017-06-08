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
		{ 0x87, { "ADD  A,A", 0, 4, &UnimplementedInstruction } },
		{ 0x80, { "ADD  A,B", 0, 4, &UnimplementedInstruction } },
		{ 0x81, { "ADD  A,C", 0, 4, &UnimplementedInstruction } },
		{ 0x82, { "ADD  A,D", 0, 4, &UnimplementedInstruction } },
		{ 0x83, { "ADD  A,E", 0, 4, &UnimplementedInstruction } },
		{ 0x84, { "ADD  A,H", 0, 4, &UnimplementedInstruction } },
		{ 0x85, { "ADD  A,L", 0, 4, &UnimplementedInstruction } },
		{ 0x86, { "ADD  A,(HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xC6, { "ADD  A,$%02X", 1, 8, &UnimplementedInstruction } },

		// ADC A,n
		{ 0x8F, { "ADC  A,A", 0, 4, &UnimplementedInstruction } },
		{ 0x88, { "ADC  A,B", 0, 4, &UnimplementedInstruction } },
		{ 0x89, { "ADC  A,C", 0, 4, &UnimplementedInstruction } },
		{ 0x8A, { "ADC  A,D", 0, 4, &UnimplementedInstruction } },
		{ 0x8B, { "ADC  A,E", 0, 4, &UnimplementedInstruction } },
		{ 0x8C, { "ADC  A,H", 0, 4, &UnimplementedInstruction } },
		{ 0x8D, { "ADC  A,L", 0, 4, &UnimplementedInstruction } },
		{ 0x8E, { "ADC  A,(HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xCE, { "ADC  A,$%02X", 1, 8, &UnimplementedInstruction } },

		// SUB n
		{ 0x97, { "SUB  A", 0, 4, &UnimplementedInstruction } },
		{ 0x90, { "SUB  B", 0, 4, &UnimplementedInstruction } },
		{ 0x91, { "SUB  C", 0, 4, &UnimplementedInstruction } },
		{ 0x92, { "SUB  D", 0, 4, &UnimplementedInstruction } },
		{ 0x93, { "SUB  E", 0, 4, &UnimplementedInstruction } },
		{ 0x94, { "SUB  H", 0, 4, &UnimplementedInstruction } },
		{ 0x95, { "SUB  L", 0, 4, &UnimplementedInstruction } },
		{ 0x96, { "SUB  (HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xD6, { "SUB  $%02X", 1, 8, &UnimplementedInstruction } },

		// SBC A,n
		{ 0x9F, { "SBC  A,A", 0, 4, &UnimplementedInstruction } },
		{ 0x98, { "SBC  A,B", 0, 4, &UnimplementedInstruction } },
		{ 0x99, { "SBC  A,C", 0, 4, &UnimplementedInstruction } },
		{ 0x9A, { "SBC  A,D", 0, 4, &UnimplementedInstruction } },
		{ 0x9B, { "SBC  A,E", 0, 4, &UnimplementedInstruction } },
		{ 0x9C, { "SBC  A,H", 0, 4, &UnimplementedInstruction } },
		{ 0x9D, { "SBC  A,L", 0, 4, &UnimplementedInstruction } },
		{ 0x9E, { "SBC  A,(HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xDE, { "SBC  A,$%02X", 1, 8, &UnimplementedInstruction } }, // ?? Manual seems confused about this one

		// AND n
		{ 0xA7, { "AND  A", 0, 4, &UnimplementedInstruction } },
		{ 0xA0, { "AND  B", 0, 4, &UnimplementedInstruction } },
		{ 0xA1, { "AND  C", 0, 4, &UnimplementedInstruction } },
		{ 0xA2, { "AND  D", 0, 4, &UnimplementedInstruction } },
		{ 0xA3, { "AND  E", 0, 4, &UnimplementedInstruction } },
		{ 0xA4, { "AND  H", 0, 4, &UnimplementedInstruction } },
		{ 0xA5, { "AND  L", 0, 4, &UnimplementedInstruction } },
		{ 0xA6, { "AND  (HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xE6, { "AND  $%02X", 1, 8, &UnimplementedInstruction } },

		// OR n
		{ 0xB7, { "OR   A", 0, 4, &UnimplementedInstruction } },
		{ 0xB0, { "OR   B", 0, 4, &UnimplementedInstruction } },
		{ 0xB1, { "OR   C", 0, 4, &UnimplementedInstruction } },
		{ 0xB2, { "OR   D", 0, 4, &UnimplementedInstruction } },
		{ 0xB3, { "OR   E", 0, 4, &UnimplementedInstruction } },
		{ 0xB4, { "OR   H", 0, 4, &UnimplementedInstruction } },
		{ 0xB5, { "OR   L", 0, 4, &UnimplementedInstruction } },
		{ 0xB6, { "OR   (HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xF6, { "OR   $%02X", 1, 8, &UnimplementedInstruction } },

		// XOR n
		{ 0xAF, { "XOR  A", 0, 4, &UnimplementedInstruction } },
		{ 0xA8, { "XOR  B", 0, 4, &UnimplementedInstruction } },
		{ 0xA9, { "XOR  C", 0, 4, &UnimplementedInstruction } },
		{ 0xAA, { "XOR  D", 0, 4, &UnimplementedInstruction } },
		{ 0xAB, { "XOR  E", 0, 4, &UnimplementedInstruction } },
		{ 0xAC, { "XOR  H", 0, 4, &UnimplementedInstruction } },
		{ 0xAD, { "XOR  L", 0, 4, &UnimplementedInstruction } },
		{ 0xAE, { "XOR  (HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xEE, { "XOR  $%02X", 1, 8, &UnimplementedInstruction } },

		// CP n
		{ 0xBF, { "CP   A", 0, 4, &UnimplementedInstruction } },
		{ 0xB8, { "CP   B", 0, 4, &UnimplementedInstruction } },
		{ 0xB9, { "CP   C", 0, 4, &UnimplementedInstruction } },
		{ 0xBA, { "CP   D", 0, 4, &UnimplementedInstruction } },
		{ 0xBB, { "CP   E", 0, 4, &UnimplementedInstruction } },
		{ 0xBC, { "CP   H", 0, 4, &UnimplementedInstruction } },
		{ 0xBD, { "CP   L", 0, 4, &UnimplementedInstruction } },
		{ 0xBE, { "CP   (HL)", 0, 8, &UnimplementedInstruction } },
		{ 0xFE, { "CP   $%02X", 1, 8, &UnimplementedInstruction } },

		// INC n
		{ 0x3C, { "INC  A", 0, 4, &UnimplementedInstruction } },
		{ 0x04, { "INC  B", 0, 4, &UnimplementedInstruction } },
		{ 0x0C, { "INC  C", 0, 4, &UnimplementedInstruction } },
		{ 0x14, { "INC  D", 0, 4, &UnimplementedInstruction } },
		{ 0x1C, { "INC  E", 0, 4, &UnimplementedInstruction } },
		{ 0x24, { "INC  H", 0, 4, &UnimplementedInstruction } },
		{ 0x2C, { "INC  L", 0, 4, &UnimplementedInstruction } },
		{ 0x34, { "INC  (HL)", 0, 12, &UnimplementedInstruction } },

		// DEC n
		{ 0x3D, { "DEC  A", 0, 4, &UnimplementedInstruction } },
		{ 0x05, { "DEC  B", 0, 4, &UnimplementedInstruction } },
		{ 0x0D, { "DEC  C", 0, 4, &UnimplementedInstruction } },
		{ 0x15, { "DEC  D", 0, 4, &UnimplementedInstruction } },
		{ 0x1D, { "DEC  E", 0, 4, &UnimplementedInstruction } },
		{ 0x25, { "DEC  H", 0, 4, &UnimplementedInstruction } },
		{ 0x2D, { "DEC  L", 0, 4, &UnimplementedInstruction } },
		{ 0x35, { "DEC  (HL)", 0, 12, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region 16-bit Arithmetic

		// ADD HL,n
		{ 0x09, { "ADD  HL,BC", 0, 8, &UnimplementedInstruction } },
		{ 0x19, { "ADD  HL,DE", 0, 8, &UnimplementedInstruction } },
		{ 0x29, { "ADD  HL,HL", 0, 8, &UnimplementedInstruction } },
		{ 0x39, { "ADD  HL,SP", 0, 8, &UnimplementedInstruction } },

		// ADD SP,n
		{ 0xE8, { "ADD  SP,$%02X", 1, 16, &UnimplementedInstruction } },

		// INC nn
		{ 0x03, { "INC  BC", 0, 8, &UnimplementedInstruction } },
		{ 0x13, { "INC  DE", 0, 8, &UnimplementedInstruction } },
		{ 0x23, { "INC  HL", 0, 8, &UnimplementedInstruction } },
		{ 0x33, { "INC  SP", 0, 8, &UnimplementedInstruction } },

		// DEC nn
		{ 0x0B, { "DEC  BC", 0, 8, &UnimplementedInstruction } },
		{ 0x1B, { "DEC  DE", 0, 8, &UnimplementedInstruction } },
		{ 0x2B, { "DEC  HL", 0, 8, &UnimplementedInstruction } },
		{ 0x3B, { "DEC  SP", 0, 8, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Miscellaneous

		// SWAP n (See Prefix CB opcodes)
		//{ 0xCB 37, { "SWAP A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 30, { "SWAP B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 31, { "SWAP C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 32, { "SWAP D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 33, { "SWAP E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 34, { "SWAP H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 35, { "SWAP L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 36, { "SWAP (HL)", 0, 16, &UnimplementedInstruction } },

		// Decimal adjust (Register A)
		{ 0x27, { "DAA", 0, 4, &UnimplementedInstruction } },

		// Complement (Register A)
		{ 0x2F, { "CPL", 0, 4, &UnimplementedInstruction } },

		// Complement carry flag
		{ 0x3F, { "CCF", 0, 4, &UnimplementedInstruction } },

		// Set carry flag
		{ 0x37, { "SCF", 0, 4, &UnimplementedInstruction } },

		// NOP
		{ 0x00, { "NOP", 0, 4, &NOP } },

		// HALT
		{ 0x76, { "HALT", 0, 4, &UnimplementedInstruction } },

		// STOP
		{ 0x10, { "STOP", 1, 4, &UnimplementedInstruction } }, // technically 10 00, but second byte is ignored

		// Disable/Enable Interrupts
		{ 0xF3, { "DI", 0, 4, &UnimplementedInstruction } },
		{ 0xFB, { "EI", 0, 4, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (Register A)
		{ 0x07, { "RLCA", 0, 4, &UnimplementedInstruction } }, // NOTE TO SELF: this rotates A and sets the carry flag to the old bit 7 (bit 0 is set to bit 7, c is also set to bit 7)

		// Rotate left through carry (Register A)
		{ 0x17, { "RLA", 0, 4, &UnimplementedInstruction } }, // NOTE TO SELF: this rotates A plus the carry flag (bit 0 is set to c, c is set to bit 7)

		// Rotate right with carry (Register A)
		{ 0x0F, { "RRCA", 0, 4, &UnimplementedInstruction } },

		// Rotate right through carry (Register A)
		{ 0x1F, { "RRA", 0, 4, &UnimplementedInstruction } },

		// Rotate left with carry (RLC n) (See Prefix CB opcodes)
		//{ 0xCB 07, { "RLC  A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 00, { "RLC  B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 01, { "RLC  C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 02, { "RLC  D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 03, { "RLC  E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 04, { "RLC  H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 05, { "RLC  L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 06, { "RLC  (HL)", 0, 16, &UnimplementedInstruction } },

		// Rotate left through carry (RL n) (See Prefix CB opcodes)
		//{ 0xCB 17, { "RL   A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 10, { "RL   B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 11, { "RL   C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 12, { "RL   D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 13, { "RL   E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 14, { "RL   H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 15, { "RL   L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 16, { "RL   (HL)", 0, 16, &UnimplementedInstruction } },

		// Rotate right with carry (RRC n) (See Prefix CB opcodes)
		//{ 0xCB 0F, { "RRC  A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 08, { "RRC  B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 09, { "RRC  C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 0A, { "RRC  D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 0B, { "RRC  E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 0C, { "RRC  H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 0D, { "RRC  L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 0E, { "RRC  (HL)", 0, 16, &UnimplementedInstruction },

		// Rotate right through carry (RR n) (See Prefix CB opcodes)
		//{ 0xCB 1F, { "RR   A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 18, { "RR   B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 19, { "RR   C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 1A, { "RR   D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 1B, { "RR   E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 1C, { "RR   H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 1D, { "RR   L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 1E, { "RR   (HL)", 0, 16 } },

		// Shift left into carry (SLA n) (See Prefix CB opcodes)
		//{ 0xCB 27, { "SLA  A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 20, { "SLA  B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 21, { "SLA  C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 22, { "SLA  D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 23, { "SLA  E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 24, { "SLA  H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 25, { "SLA  L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 26, { "SLA  (HL)", 0, 16, &UnimplementedInstruction } },

		// Shift right into carry (SRA n) (See Prefix CB opcodes)
		//{ 0xCB 2F, { "SRA  A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 28, { "SRA  B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 29, { "SRA  C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 2A, { "SRA  D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 2B, { "SRA  E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 2C, { "SRA  H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 2D, { "SRA  L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 2E, { "SRA  (HL)", 0, 16, &UnimplementedInstruction } },

		// Shift right into carry (SRL n) (See Prefix CB opcodes)
		//{ 0xCB 3F, { "SRL  A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 38, { "SRL  B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 39, { "SRL  C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 3A, { "SRL  D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 3B, { "SRL  E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 3C, { "SRL  H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 3D, { "SRL  L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 3E, { "SRL  (HL)", 0, 16, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r) (See Prefix CB opcodes)
		//{ 0xCB 47, { "BIT  b,A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 40, { "BIT  b,B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 41, { "BIT  b,C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 42, { "BIT  b,D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 43, { "BIT  b,E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 44, { "BIT  b,H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 45, { "BIT  b,L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 46, { "BIT  b,(HL)", 0, 16, &UnimplementedInstruction } },

		// Set Bit (SET b,r) (See Prefix CB opcodes)
		//{ 0xCB C7, { "SET  b,A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C0, { "SET  b,B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C1, { "SET  b,C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C2, { "SET  b,D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C3, { "SET  b,E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C4, { "SET  b,H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C5, { "SET  b,L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB C6, { "SET  b,(HL)", 0, 16, &UnimplementedInstruction } },

		// Reset (clear) Bit (RES b,r) (See Prefix CB opcodes)
		//{ 0xCB 87, { "RES  b,A", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 80, { "RES  b,B", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 81, { "RES  b,C", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 82, { "RES  b,D", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 83, { "RES  b,E", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 84, { "RES  b,H", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 85, { "RES  b,L", 0, 8, &UnimplementedInstruction } },
		//{ 0xCB 86, { "RES  b,(HL)", 0, 16, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Jumps

		// JP nn
		{ 0xC3, { "JP   $%04X", 2, 12, &UnimplementedInstruction } },

		// JP cc,nn
		{ 0xC2, { "JP   NZ,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xCA, { "JP   Z,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xD2, { "JP   NC,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xDA, { "JP   C,$%04X", 2, 12, &UnimplementedInstruction } },

		// JP (HL)
		{ 0xE9, { "JP   (HL)", 0, 4, &UnimplementedInstruction } },

		// JR n (relative jump)
		{ 0x18, { "JR   $%02X", 1, 8, &UnimplementedInstruction } },

		// JR cc,n
		{ 0x20, { "JR   NZ,$%02X", 1, 8, &UnimplementedInstruction } },
		{ 0x28, { "JR   Z,$%02X", 1, 8, &UnimplementedInstruction } },
		{ 0x30, { "JR   NC,$%02X", 1, 8, &UnimplementedInstruction } },
		{ 0x38, { "JR   C,$%02X", 1, 8, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Calls

		// CALL nn
		{ 0xCD, { "CALL $%04X", 2, 12, &UnimplementedInstruction } },

		// CALL cc,nn
		{ 0xC4, { "CALL NZ,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xCC, { "CALL Z,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xD4, { "CALL NC,$%04X", 2, 12, &UnimplementedInstruction } },
		{ 0xDC, { "CALL C,$%04X", 2, 12, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Restarts

		// RST n
		{ 0xC7, { "RST  $00", 0, 32, &UnimplementedInstruction } },
		{ 0xCF, { "RST  $08", 0, 32, &UnimplementedInstruction } },
		{ 0xD7, { "RST  $10", 0, 32, &UnimplementedInstruction } },
		{ 0xDF, { "RST  $18", 0, 32, &UnimplementedInstruction } },
		{ 0xE7, { "RST  $20", 0, 32, &UnimplementedInstruction } },
		{ 0xEF, { "RST  $28", 0, 32, &UnimplementedInstruction } },
		{ 0xF7, { "RST  $30", 0, 32, &UnimplementedInstruction } },
		{ 0xFF, { "RST  $38", 0, 32, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Returns

		// RET
		{ 0xC9, { "RET", 0, 8, &UnimplementedInstruction } },

		// RET cc
		{ 0xC0, { "RET  NZ", 0, 8, &UnimplementedInstruction } },
		{ 0xC8, { "RET  Z", 0, 8, &UnimplementedInstruction } },
		{ 0xD0, { "RET  NC", 0, 8, &UnimplementedInstruction } },
		{ 0xD8, { "RET  C", 0, 8, &UnimplementedInstruction } },

		// RETI
		{ 0xD9, { "RETI", 0, 8, &UnimplementedInstruction } },

		#pragma endregion
	};

	const map<uint8_t, Instruction> CPU::sOpcodeDisassembly_PrefixCB
	{
		#pragma region Swap

		// SWAP n (See Prefix CB opcodes)
		{ 0x37, { "SWAP A", 0, 8, &UnimplementedInstruction } },
		{ 0x30, { "SWAP B", 0, 8, &UnimplementedInstruction } },
		{ 0x31, { "SWAP C", 0, 8, &UnimplementedInstruction } },
		{ 0x32, { "SWAP D", 0, 8, &UnimplementedInstruction } },
		{ 0x33, { "SWAP E", 0, 8, &UnimplementedInstruction } },
		{ 0x34, { "SWAP H", 0, 8, &UnimplementedInstruction } },
		{ 0x35, { "SWAP L", 0, 8, &UnimplementedInstruction } },
		{ 0x36, { "SWAP (HL)", 0, 16, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (RLC n)
		{ 0x07, { "RLC  A", 1, 8, &UnimplementedInstruction } },
		{ 0x00, { "RLC  B", 1, 8, &UnimplementedInstruction } },
		{ 0x01, { "RLC  C", 1, 8, &UnimplementedInstruction } },
		{ 0x02, { "RLC  D", 1, 8, &UnimplementedInstruction } },
		{ 0x03, { "RLC  E", 1, 8, &UnimplementedInstruction } },
		{ 0x04, { "RLC  H", 1, 8, &UnimplementedInstruction } },
		{ 0x05, { "RLC  L", 1, 8, &UnimplementedInstruction } },
		{ 0x06, { "RLC  (HL)", 1, 16, &UnimplementedInstruction } },

		// Rotate left through carry (RL n)
		{ 0x17, { "RL   A", 1, 8, &UnimplementedInstruction } },
		{ 0x10, { "RL   B", 1, 8, &UnimplementedInstruction } },
		{ 0x11, { "RL   C", 1, 8, &UnimplementedInstruction } },
		{ 0x12, { "RL   D", 1, 8, &UnimplementedInstruction } },
		{ 0x13, { "RL   E", 1, 8, &UnimplementedInstruction } },
		{ 0x14, { "RL   H", 1, 8, &UnimplementedInstruction } },
		{ 0x15, { "RL   L", 1, 8, &UnimplementedInstruction } },
		{ 0x16, { "RL   (HL)", 1, 16, &UnimplementedInstruction } },

		// Rotate right with carry (RRC n)
		{ 0x0F, { "RRC  A", 1, 8, &UnimplementedInstruction } },
		{ 0x08, { "RRC  B", 1, 8, &UnimplementedInstruction } },
		{ 0x09, { "RRC  C", 1, 8, &UnimplementedInstruction } },
		{ 0x0A, { "RRC  D", 1, 8, &UnimplementedInstruction } },
		{ 0x0B, { "RRC  E", 1, 8, &UnimplementedInstruction } },
		{ 0x0C, { "RRC  H", 1, 8, &UnimplementedInstruction } },
		{ 0x0D, { "RRC  L", 1, 8, &UnimplementedInstruction } },
		{ 0x0E, { "RRC  (HL)", 1, 16, &UnimplementedInstruction } },

		// Rotate right through carry (RR n)
		{ 0x1F, { "RR   A", 1, 8, &UnimplementedInstruction } },
		{ 0x18, { "RR   B", 1, 8, &UnimplementedInstruction } },
		{ 0x19, { "RR   C", 1, 8, &UnimplementedInstruction } },
		{ 0x1A, { "RR   D", 1, 8, &UnimplementedInstruction } },
		{ 0x1B, { "RR   E", 1, 8, &UnimplementedInstruction } },
		{ 0x1C, { "RR   H", 1, 8, &UnimplementedInstruction } },
		{ 0x1D, { "RR   L", 1, 8, &UnimplementedInstruction } },
		{ 0x1E, { "RR   (HL)", 1, 16, &UnimplementedInstruction } },

		// Shif left into carry (SLA n)
		{ 0x27, { "SLA  A", 1, 8, &UnimplementedInstruction } },
		{ 0x20, { "SLA  B", 1, 8, &UnimplementedInstruction } },
		{ 0x21, { "SLA  C", 1, 8, &UnimplementedInstruction } },
		{ 0x22, { "SLA  D", 1, 8, &UnimplementedInstruction } },
		{ 0x23, { "SLA  E", 1, 8, &UnimplementedInstruction } },
		{ 0x24, { "SLA  H", 1, 8, &UnimplementedInstruction } },
		{ 0x25, { "SLA  L", 1, 8, &UnimplementedInstruction } },
		{ 0x26, { "SLA  (HL)", 1, 16, &UnimplementedInstruction } },

		// Shif right into carry (SRA n)
		{ 0x2F, { "SRA  A", 1, 8, &UnimplementedInstruction } },
		{ 0x28, { "SRA  B", 1, 8, &UnimplementedInstruction } },
		{ 0x29, { "SRA  C", 1, 8, &UnimplementedInstruction } },
		{ 0x2A, { "SRA  D", 1, 8, &UnimplementedInstruction } },
		{ 0x2B, { "SRA  E", 1, 8, &UnimplementedInstruction } },
		{ 0x2C, { "SRA  H", 1, 8, &UnimplementedInstruction } },
		{ 0x2D, { "SRA  L", 1, 8, &UnimplementedInstruction } },
		{ 0x2E, { "SRA  (HL)", 1, 16, &UnimplementedInstruction } },

		// Shift right into carry (SRL n)
		{ 0x3F, { "SRL  A", 1, 8, &UnimplementedInstruction } },
		{ 0x38, { "SRL  B", 1, 8, &UnimplementedInstruction } },
		{ 0x39, { "SRL  C", 1, 8, &UnimplementedInstruction } },
		{ 0x3A, { "SRL  D", 1, 8, &UnimplementedInstruction } },
		{ 0x3B, { "SRL  E", 1, 8, &UnimplementedInstruction } },
		{ 0x3C, { "SRL  H", 1, 8, &UnimplementedInstruction } },
		{ 0x3D, { "SRL  L", 1, 8, &UnimplementedInstruction } },
		{ 0x3E, { "SRL  (HL)", 1, 16, &UnimplementedInstruction } },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r)
		{ 0x47, { "BIT  0,A", 1, 8, &UnimplementedInstruction } },
		{ 0x40, { "BIT  0,B", 1, 8, &UnimplementedInstruction } },
		{ 0x41, { "BIT  0,C", 1, 8, &UnimplementedInstruction } },
		{ 0x42, { "BIT  0,D", 1, 8, &UnimplementedInstruction } },
		{ 0x43, { "BIT  0,E", 1, 8, &UnimplementedInstruction } },
		{ 0x44, { "BIT  0,H", 1, 8, &UnimplementedInstruction } },
		{ 0x45, { "BIT  0,L", 1, 8, &UnimplementedInstruction } },
		{ 0x46, { "BIT  0,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x4F, { "BIT  1,A", 1, 8, &UnimplementedInstruction } },
		{ 0x48, { "BIT  1,B", 1, 8, &UnimplementedInstruction } },
		{ 0x49, { "BIT  1,C", 1, 8, &UnimplementedInstruction } },
		{ 0x4A, { "BIT  1,D", 1, 8, &UnimplementedInstruction } },
		{ 0x4B, { "BIT  1,E", 1, 8, &UnimplementedInstruction } },
		{ 0x4C, { "BIT  1,H", 1, 8, &UnimplementedInstruction } },
		{ 0x4D, { "BIT  1,L", 1, 8, &UnimplementedInstruction } },
		{ 0x4E, { "BIT  1,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x57, { "BIT  2,A", 1, 8, &UnimplementedInstruction } },
		{ 0x50, { "BIT  2,B", 1, 8, &UnimplementedInstruction } },
		{ 0x51, { "BIT  2,C", 1, 8, &UnimplementedInstruction } },
		{ 0x52, { "BIT  2,D", 1, 8, &UnimplementedInstruction } },
		{ 0x53, { "BIT  2,E", 1, 8, &UnimplementedInstruction } },
		{ 0x54, { "BIT  2,H", 1, 8, &UnimplementedInstruction } },
		{ 0x55, { "BIT  2,L", 1, 8, &UnimplementedInstruction } },
		{ 0x56, { "BIT  2,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x5F, { "BIT  3,A", 1, 8, &UnimplementedInstruction } },
		{ 0x58, { "BIT  3,B", 1, 8, &UnimplementedInstruction } },
		{ 0x59, { "BIT  3,C", 1, 8, &UnimplementedInstruction } },
		{ 0x5A, { "BIT  3,D", 1, 8, &UnimplementedInstruction } },
		{ 0x5B, { "BIT  3,E", 1, 8, &UnimplementedInstruction } },
		{ 0x5C, { "BIT  3,H", 1, 8, &UnimplementedInstruction } },
		{ 0x5D, { "BIT  3,L", 1, 8, &UnimplementedInstruction } },
		{ 0x5E, { "BIT  3,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x67, { "BIT  4,A", 1, 8, &UnimplementedInstruction } },
		{ 0x60, { "BIT  4,B", 1, 8, &UnimplementedInstruction } },
		{ 0x61, { "BIT  4,C", 1, 8, &UnimplementedInstruction } },
		{ 0x62, { "BIT  4,D", 1, 8, &UnimplementedInstruction } },
		{ 0x63, { "BIT  4,E", 1, 8, &UnimplementedInstruction } },
		{ 0x64, { "BIT  4,H", 1, 8, &UnimplementedInstruction } },
		{ 0x65, { "BIT  4,L", 1, 8, &UnimplementedInstruction } },
		{ 0x66, { "BIT  4,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x6F, { "BIT  5,A", 1, 8, &UnimplementedInstruction } },
		{ 0x68, { "BIT  5,B", 1, 8, &UnimplementedInstruction } },
		{ 0x69, { "BIT  5,C", 1, 8, &UnimplementedInstruction } },
		{ 0x6A, { "BIT  5,D", 1, 8, &UnimplementedInstruction } },
		{ 0x6B, { "BIT  5,E", 1, 8, &UnimplementedInstruction } },
		{ 0x6C, { "BIT  5,H", 1, 8, &UnimplementedInstruction } },
		{ 0x6D, { "BIT  5,L", 1, 8, &UnimplementedInstruction } },
		{ 0x6E, { "BIT  5,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x77, { "BIT  6,A", 1, 8, &UnimplementedInstruction } },
		{ 0x70, { "BIT  6,B", 1, 8, &UnimplementedInstruction } },
		{ 0x71, { "BIT  6,C", 1, 8, &UnimplementedInstruction } },
		{ 0x72, { "BIT  6,D", 1, 8, &UnimplementedInstruction } },
		{ 0x73, { "BIT  6,E", 1, 8, &UnimplementedInstruction } },
		{ 0x74, { "BIT  6,H", 1, 8, &UnimplementedInstruction } },
		{ 0x75, { "BIT  6,L", 1, 8, &UnimplementedInstruction } },
		{ 0x76, { "BIT  6,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x7F, { "BIT  7,A", 1, 8, &UnimplementedInstruction } },
		{ 0x78, { "BIT  7,B", 1, 8, &UnimplementedInstruction } },
		{ 0x79, { "BIT  7,C", 1, 8, &UnimplementedInstruction } },
		{ 0x7A, { "BIT  7,D", 1, 8, &UnimplementedInstruction } },
		{ 0x7B, { "BIT  7,E", 1, 8, &UnimplementedInstruction } },
		{ 0x7C, { "BIT  7,H", 1, 8, &UnimplementedInstruction } },
		{ 0x7D, { "BIT  7,L", 1, 8, &UnimplementedInstruction } },
		{ 0x7E, { "BIT  7,(HL)", 1, 16, &UnimplementedInstruction } },

		// Set Bit (SET b,r)
		{ 0xC7, { "SET  0,A", 1, 8, &UnimplementedInstruction } },
		{ 0xC0, { "SET  0,B", 1, 8, &UnimplementedInstruction } },
		{ 0xC1, { "SET  0,C", 1, 8, &UnimplementedInstruction } },
		{ 0xC2, { "SET  0,D", 1, 8, &UnimplementedInstruction } },
		{ 0xC3, { "SET  0,E", 1, 8, &UnimplementedInstruction } },
		{ 0xC4, { "SET  0,H", 1, 8, &UnimplementedInstruction } },
		{ 0xC5, { "SET  0,L", 1, 8, &UnimplementedInstruction } },
		{ 0xC6, { "SET  0,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xCF, { "SET  1,A", 1, 8, &UnimplementedInstruction } },
		{ 0xC8, { "SET  1,B", 1, 8, &UnimplementedInstruction } },
		{ 0xC9, { "SET  1,C", 1, 8, &UnimplementedInstruction } },
		{ 0xCA, { "SET  1,D", 1, 8, &UnimplementedInstruction } },
		{ 0xCB, { "SET  1,E", 1, 8, &UnimplementedInstruction } },
		{ 0xCC, { "SET  1,H", 1, 8, &UnimplementedInstruction } },
		{ 0xCD, { "SET  1,L", 1, 8, &UnimplementedInstruction } },
		{ 0xCE, { "SET  1,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xD7, { "SET  2,A", 1, 8, &UnimplementedInstruction } },
		{ 0xD0, { "SET  2,B", 1, 8, &UnimplementedInstruction } },
		{ 0xD1, { "SET  2,C", 1, 8, &UnimplementedInstruction } },
		{ 0xD2, { "SET  2,D", 1, 8, &UnimplementedInstruction } },
		{ 0xD3, { "SET  2,E", 1, 8, &UnimplementedInstruction } },
		{ 0xD4, { "SET  2,H", 1, 8, &UnimplementedInstruction } },
		{ 0xD5, { "SET  2,L", 1, 8, &UnimplementedInstruction } },
		{ 0xD6, { "SET  2,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xDF, { "SET  3,A", 1, 8, &UnimplementedInstruction } },
		{ 0xD8, { "SET  3,B", 1, 8, &UnimplementedInstruction } },
		{ 0xD9, { "SET  3,C", 1, 8, &UnimplementedInstruction } },
		{ 0xDA, { "SET  3,D", 1, 8, &UnimplementedInstruction } },
		{ 0xDB, { "SET  3,E", 1, 8, &UnimplementedInstruction } },
		{ 0xDC, { "SET  3,H", 1, 8, &UnimplementedInstruction } },
		{ 0xDD, { "SET  3,L", 1, 8, &UnimplementedInstruction } },
		{ 0xDE, { "SET  3,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xE7, { "SET  4,A", 1, 8, &UnimplementedInstruction } },
		{ 0xE0, { "SET  4,B", 1, 8, &UnimplementedInstruction } },
		{ 0xE1, { "SET  4,C", 1, 8, &UnimplementedInstruction } },
		{ 0xE2, { "SET  4,D", 1, 8, &UnimplementedInstruction } },
		{ 0xE3, { "SET  4,E", 1, 8, &UnimplementedInstruction } },
		{ 0xE4, { "SET  4,H", 1, 8, &UnimplementedInstruction } },
		{ 0xE5, { "SET  4,L", 1, 8, &UnimplementedInstruction } },
		{ 0xE6, { "SET  4,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xEF, { "SET  5,A", 1, 8, &UnimplementedInstruction } },
		{ 0xE8, { "SET  5,B", 1, 8, &UnimplementedInstruction } },
		{ 0xE9, { "SET  5,C", 1, 8, &UnimplementedInstruction } },
		{ 0xEA, { "SET  5,D", 1, 8, &UnimplementedInstruction } },
		{ 0xEB, { "SET  5,E", 1, 8, &UnimplementedInstruction } },
		{ 0xEC, { "SET  5,H", 1, 8, &UnimplementedInstruction } },
		{ 0xED, { "SET  5,L", 1, 8, &UnimplementedInstruction } },
		{ 0xEE, { "SET  5,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xF7, { "SET  6,A", 1, 8, &UnimplementedInstruction } },
		{ 0xF0, { "SET  6,B", 1, 8, &UnimplementedInstruction } },
		{ 0xF1, { "SET  6,C", 1, 8, &UnimplementedInstruction } },
		{ 0xF2, { "SET  6,D", 1, 8, &UnimplementedInstruction } },
		{ 0xF3, { "SET  6,E", 1, 8, &UnimplementedInstruction } },
		{ 0xF4, { "SET  6,H", 1, 8, &UnimplementedInstruction } },
		{ 0xF5, { "SET  6,L", 1, 8, &UnimplementedInstruction } },
		{ 0xF6, { "SET  6,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xFF, { "SET  7,A", 1, 8, &UnimplementedInstruction } },
		{ 0xF8, { "SET  7,B", 1, 8, &UnimplementedInstruction } },
		{ 0xF9, { "SET  7,C", 1, 8, &UnimplementedInstruction } },
		{ 0xFA, { "SET  7,D", 1, 8, &UnimplementedInstruction } },
		{ 0xFB, { "SET  7,E", 1, 8, &UnimplementedInstruction } },
		{ 0xFC, { "SET  7,H", 1, 8, &UnimplementedInstruction } },
		{ 0xFD, { "SET  7,L", 1, 8, &UnimplementedInstruction } },
		{ 0xFE, { "SET  7,(HL)", 1, 16, &UnimplementedInstruction } },

		// Reset (Clear) Bit (RES b,r)
		{ 0x87, { "RES  0,A", 1, 8, &UnimplementedInstruction } },
		{ 0x80, { "RES  0,B", 1, 8, &UnimplementedInstruction } },
		{ 0x81, { "RES  0,C", 1, 8, &UnimplementedInstruction } },
		{ 0x82, { "RES  0,D", 1, 8, &UnimplementedInstruction } },
		{ 0x83, { "RES  0,E", 1, 8, &UnimplementedInstruction } },
		{ 0x84, { "RES  0,H", 1, 8, &UnimplementedInstruction } },
		{ 0x85, { "RES  0,L", 1, 8, &UnimplementedInstruction } },
		{ 0x86, { "RES  0,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x8F, { "RES  1,A", 1, 8, &UnimplementedInstruction } },
		{ 0x88, { "RES  1,B", 1, 8, &UnimplementedInstruction } },
		{ 0x89, { "RES  1,C", 1, 8, &UnimplementedInstruction } },
		{ 0x8A, { "RES  1,D", 1, 8, &UnimplementedInstruction } },
		{ 0x8B, { "RES  1,E", 1, 8, &UnimplementedInstruction } },
		{ 0x8C, { "RES  1,H", 1, 8, &UnimplementedInstruction } },
		{ 0x8D, { "RES  1,L", 1, 8, &UnimplementedInstruction } },
		{ 0x8E, { "RES  1,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x97, { "RES  2,A", 1, 8, &UnimplementedInstruction } },
		{ 0x90, { "RES  2,B", 1, 8, &UnimplementedInstruction } },
		{ 0x91, { "RES  2,C", 1, 8, &UnimplementedInstruction } },
		{ 0x92, { "RES  2,D", 1, 8, &UnimplementedInstruction } },
		{ 0x93, { "RES  2,E", 1, 8, &UnimplementedInstruction } },
		{ 0x94, { "RES  2,H", 1, 8, &UnimplementedInstruction } },
		{ 0x95, { "RES  2,L", 1, 8, &UnimplementedInstruction } },
		{ 0x96, { "RES  2,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0x9F, { "RES  3,A", 1, 8, &UnimplementedInstruction } },
		{ 0x98, { "RES  3,B", 1, 8, &UnimplementedInstruction } },
		{ 0x99, { "RES  3,C", 1, 8, &UnimplementedInstruction } },
		{ 0x9A, { "RES  3,D", 1, 8, &UnimplementedInstruction } },
		{ 0x9B, { "RES  3,E", 1, 8, &UnimplementedInstruction } },
		{ 0x9C, { "RES  3,H", 1, 8, &UnimplementedInstruction } },
		{ 0x9D, { "RES  3,L", 1, 8, &UnimplementedInstruction } },
		{ 0x9E, { "RES  3,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xA7, { "RES  4,A", 1, 8, &UnimplementedInstruction } },
		{ 0xA0, { "RES  4,B", 1, 8, &UnimplementedInstruction } },
		{ 0xA1, { "RES  4,C", 1, 8, &UnimplementedInstruction } },
		{ 0xA2, { "RES  4,D", 1, 8, &UnimplementedInstruction } },
		{ 0xA3, { "RES  4,E", 1, 8, &UnimplementedInstruction } },
		{ 0xA4, { "RES  4,H", 1, 8, &UnimplementedInstruction } },
		{ 0xA5, { "RES  4,L", 1, 8, &UnimplementedInstruction } },
		{ 0xA6, { "RES  4,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xAF, { "RES  5,A", 1, 8, &UnimplementedInstruction } },
		{ 0xA8, { "RES  5,B", 1, 8, &UnimplementedInstruction } },
		{ 0xA9, { "RES  5,C", 1, 8, &UnimplementedInstruction } },
		{ 0xAA, { "RES  5,D", 1, 8, &UnimplementedInstruction } },
		{ 0xAB, { "RES  5,E", 1, 8, &UnimplementedInstruction } },
		{ 0xAC, { "RES  5,H", 1, 8, &UnimplementedInstruction } },
		{ 0xAD, { "RES  5,L", 1, 8, &UnimplementedInstruction } },
		{ 0xAE, { "RES  5,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xB7, { "RES  6,A", 1, 8, &UnimplementedInstruction } },
		{ 0xB0, { "RES  6,B", 1, 8, &UnimplementedInstruction } },
		{ 0xB1, { "RES  6,C", 1, 8, &UnimplementedInstruction } },
		{ 0xB2, { "RES  6,D", 1, 8, &UnimplementedInstruction } },
		{ 0xB3, { "RES  6,E", 1, 8, &UnimplementedInstruction } },
		{ 0xB4, { "RES  6,H", 1, 8, &UnimplementedInstruction } },
		{ 0xB5, { "RES  6,L", 1, 8, &UnimplementedInstruction } },
		{ 0xB6, { "RES  6,(HL)", 1, 16, &UnimplementedInstruction } },
		{ 0xBF, { "RES  7,A", 1, 8, &UnimplementedInstruction } },
		{ 0xB8, { "RES  7,B", 1, 8, &UnimplementedInstruction } },
		{ 0xB9, { "RES  7,C", 1, 8, &UnimplementedInstruction } },
		{ 0xBA, { "RES  7,D", 1, 8, &UnimplementedInstruction } },
		{ 0xBB, { "RES  7,E", 1, 8, &UnimplementedInstruction } },
		{ 0xBC, { "RES  7,H", 1, 8, &UnimplementedInstruction } },
		{ 0xBD, { "RES  7,L", 1, 8, &UnimplementedInstruction } },
		{ 0xBE, { "RES  7,(HL)", 1, 16, &UnimplementedInstruction } }

		#pragma endregion
	};

	CPU::CPU(MemoryMap& memory) :
		mMemory(memory)
	{
	}

	void CPU::StepCPU()
	{
		uint8_t opcode = 0x00;
		try
		{
			opcode = mMemory.ReadByte(mRegisters.PC);
			Instruction instruction = opcode != 0xCB ? sOpcodeDisassembly.at(opcode) : sOpcodeDisassembly_PrefixCB.at(opcode);
			uint16_t operand = 0x0000;
			if (instruction.OperandLength == 1)
			{
				operand = mMemory.ReadByte(mRegisters.PC);
			}
			else if (instruction.OperandLength == 2)
			{
				operand = mMemory.ReadWord(mRegisters.PC);
			}

			invoke(instruction.Function, this, operand);
			mRegisters.PC += static_cast<uint16_t>(1 + instruction.OperandLength);
			// increment clock cycles
		}
		catch (exception& ex)
		{
			char message[100];
			sprintf_s(message, sizeof(message), "Error executing instruction 0x%02X at memory location 0x%04X:\n%s", opcode, mRegisters.PC, ex.what());
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
		mRegisters.HL = mRegisters.HL + n;

		mRegisters.ResetZeroFlag();
		mRegisters.ResetSubtractFlag();
		mRegisters.AssignHalfCarryFlag((mRegisters.HL & 0xFF) + (operand & 0xFF) > 0xFF);
		mRegisters.AssignCarryFlag((mRegisters.HL & 0xF) + (operand & 0xF) > 0xF);
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

	/**
	 * \brief Perform no operation
	 */
	void CPU::NOP(uint16_t)
	{
	}
}
