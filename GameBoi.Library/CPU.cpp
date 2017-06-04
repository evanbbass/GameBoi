#include "pch.h"
#include "CPU.h"
#include <iostream>

using namespace std;

namespace GameBoi
{
	const map<uint8_t, char*> CPU::sOpcodeDisassembly
	{
		#pragma region 8-bit Loads

		// LD nn,n
		{ 0x06, "LD B,$%02X" }, // e.g. LD B,$AB
		{ 0x0E, "LD C,$%02X" }, // e.g. LD C,$AB
		{ 0x16, "LD D,$%02X" }, // e.g. LD D,$AB
		{ 0x1E, "LD E,$%02X" }, // e.g. LD E,$AB
		{ 0x26, "LD H,$%02X" }, // e.g. LD H,$AB
		{ 0x2E, "LD L,$%02X" }, // e.g. LD L,$AB

		// LD r1,r2
		{ 0x7F, "LD A,A" },
		{ 0x78, "LD A,B" },
		{ 0x79, "LD A,C" },
		{ 0x7A, "LD A,D" },
		{ 0x7B, "LD A,E" },
		{ 0x7C, "LD A,H" },
		{ 0x7D, "LD A,L" },
		{ 0x7E, "LD A,(HL)" },
		{ 0x40, "LD B,B" },
		{ 0x41, "LD B,C" },
		{ 0x42, "LD B,D" },
		{ 0x43, "LD B,E" },
		{ 0x44, "LD B,H" },
		{ 0x45, "LD B,L" },
		{ 0x46, "LD B,(HL)" },
		{ 0x48, "LD C,B" },
		{ 0x49, "LD C,C" },
		{ 0x4A, "LD C,D" },
		{ 0x4B, "LD C,E" },
		{ 0x4C, "LD C,H" },
		{ 0x4D, "LD C,L" },
		{ 0x4E, "LD C,(HL)" },
		{ 0x50, "LD D,B" },
		{ 0x51, "LD D,C" },
		{ 0x52, "LD D,D" },
		{ 0x53, "LD D,E" },
		{ 0x54, "LD D,H" },
		{ 0x55, "LD D,L" },
		{ 0x56, "LD D,(HL)" },
		{ 0x58, "LD E,B" },
		{ 0x59, "LD E,C" },
		{ 0x5A, "LD E,D" },
		{ 0x5B, "LD E,E" },
		{ 0x5C, "LD E,H" },
		{ 0x5D, "LD E,L" },
		{ 0x5E, "LD E,(HL)" },
		{ 0x60, "LD H,B" },
		{ 0x61, "LD H,C" },
		{ 0x62, "LD H,D" },
		{ 0x63, "LD H,E" },
		{ 0x64, "LD H,H" },
		{ 0x65, "LD H,L" },
		{ 0x66, "LD H,(HL)" },
		{ 0x68, "LD L,B" },
		{ 0x69, "LD L,C" },
		{ 0x6A, "LD L,D" },
		{ 0x6B, "LD L,E" },
		{ 0x6C, "LD L,H" },
		{ 0x6D, "LD L,L" },
		{ 0x6E, "LD L,(HL)" },
		{ 0x70, "LD (HL),B" },
		{ 0x71, "LD (HL),C" },
		{ 0x72, "LD (HL),D" },
		{ 0x73, "LD (HL),E" },
		{ 0x74, "LD (HL),H" },
		{ 0x75, "LD (HL),L" },
		{ 0x36, "LD (HL),$%02X" }, // e.g. LD (HL),$BC

		// LD A,n
		//{ 0x7F, "LD A,A" },
		//{ 0x78, "LD A,B" },
		//{ 0x79, "LD A,C" },
		//{ 0x7A, "LD A,D" },
		//{ 0x7B, "LD A,E" },
		//{ 0x7C, "LD A,H" },
		//{ 0x7D, "LD A,L" },
		{ 0x0A, "LD A,(BC)" },
		{ 0x1A, "LD A,(DE)" },
		//{ 0x7E, "LD A,(HL)" },
		{ 0xFA, "LD A,($%04X)" }, // e.g. LD A,($1234)
		{ 0x3E, "LD A,$%02X" }, // e.g. LD A,$AB

		// LD n,A
		//{ 0x7F, "LD A,A" },
		{ 0x47, "LD B,A" },
		{ 0x4F, "LD C,A" },
		{ 0x57, "LD D,A" },
		{ 0x5F, "LD E,A" },
		{ 0x67, "LD H,A" },
		{ 0x6F, "LD L,A" },
		{ 0x02, "LD (BC),A" },
		{ 0x12, "LD (DE),A" },
		{ 0x77, "LD (HL),A" },
		{ 0xEA, "LD ($%04X),A" }, // e.g. LD ($1234),A

		// LD A,($FF00+C) and reverse
		{ 0xF2, "LD A,(C)" }, // also LD A,($FF00+C)
		{ 0xE2, "LD (C),A" },

		// LD A,(HL-) and variations
		{ 0x3A, "LD A,(HL-)" }, // also LD A,(HLD) or LDD A,(HL)
		{ 0x32, "LD (HL-),A" }, // also LD (HLD),A or LDD (HL),A
		{ 0x2A, "LD A,(HL+)" }, // also LD A,(HLI) or LDI A,(HL)
		{ 0x22, "LD (HL+),A" }, // also LD (HLI),A or LDI (HL),A

		// LDH (n),A and reverse
		{ 0xE0, "LD A,($%02X)" },
		{ 0xF0, "LD ($%02X),A" },

		#pragma endregion

		#pragma region 16-bit loads

		// LD n,nn
		{ 0x01, "LD BC,$%04X" },
		{ 0x11, "LD DE,$%04X" },
		{ 0x21, "LD HL,$%04X" },
		{ 0x31, "LD SP,$%04X" },

		// LD, SP,HL
		{ 0xF9, "LD SP,HL" },

		// LD HL,SP+n
		{ 0xF8, "LD HL,SP+$%02X" }, // also LDHL SP,n

		// LD (nn),SP
		{ 0x08, "LD ($%04X),SP" },

		// PUSH nn
		{ 0xF5, "PUSH AF" },
		{ 0xC5, "PUSH BC" },
		{ 0xD5, "PUSH DE" },
		{ 0xE5, "PUSH HL" },

		// POP nn
		{ 0xF1, "POP AF" },
		{ 0xC1, "POP BC" },
		{ 0xD1, "POP DE" },
		{ 0xE1, "POP HL" },

		#pragma endregion

		#pragma region 8-bit ALU

		// ADD A,n
		{ 0x87, "ADD A,A" },
		{ 0x80, "ADD A,B" },
		{ 0x81, "ADD A,C" },
		{ 0x82, "ADD A,D" },
		{ 0x83, "ADD A,E" },
		{ 0x84, "ADD A,H" },
		{ 0x85, "ADD A,L" },
		{ 0x86, "ADD A,(HL)" },
		{ 0xC6, "ADD A,$%02X" },

		// ADC A,n
		{ 0x8F, "ADC A,A" },
		{ 0x88, "ADC A,B" },
		{ 0x89, "ADC A,C" },
		{ 0x8A, "ADC A,D" },
		{ 0x8B, "ADC A,E" },
		{ 0x8C, "ADC A,H" },
		{ 0x8D, "ADC A,L" },
		{ 0x8E, "ADC A,(HL)" },
		{ 0xCE, "ADC A,$%02X" },

		// SUB A,n
		{ 0x97, "SUB A,A" },
		{ 0x90, "SUB A,B" },
		{ 0x91, "SUB A,C" },
		{ 0x92, "SUB A,D" },
		{ 0x93, "SUB A,E" },
		{ 0x94, "SUB A,H" },
		{ 0x95, "SUB A,L" },
		{ 0x96, "SUB A,(HL)" },
		{ 0xD6, "SUB A,$%02X" },

		// SBC A,n
		{ 0x9F, "SBC A,A" },
		{ 0x98, "SBC A,B" },
		{ 0x99, "SBC A,C" },
		{ 0x9A, "SBC A,D" },
		{ 0x9B, "SBC A,E" },
		{ 0x9C, "SBC A,H" },
		{ 0x9D, "SBC A,L" },
		{ 0x9E, "SBC A,(HL)" },
		{ 0xDE, "SBC A,$%02X" }, // ?? Manual seems confused about this one

		// AND n
		{ 0xA7, "AND A" },
		{ 0xA0, "AND B" },
		{ 0xA1, "AND C" },
		{ 0xA2, "AND D" },
		{ 0xA3, "AND E" },
		{ 0xA4, "AND H" },
		{ 0xA5, "AND L" },
		{ 0xA6, "AND (HL)" },
		{ 0xE6, "AND $%02X" },

		// OR n
		{ 0xB7, "OR A" },
		{ 0xB0, "OR B" },
		{ 0xB1, "OR C" },
		{ 0xB2, "OR D" },
		{ 0xB3, "OR E" },
		{ 0xB4, "OR H" },
		{ 0xB5, "OR L" },
		{ 0xB6, "OR (HL)" },
		{ 0xF6, "OR $%02X" },

		// XOR n
		{ 0xAF, "XOR A" },
		{ 0xA8, "XOR B" },
		{ 0xA9, "XOR C" },
		{ 0xAA, "XOR D" },
		{ 0xAB, "XOR E" },
		{ 0xAC, "XOR H" },
		{ 0xAD, "XOR L" },
		{ 0xAE, "XOR (HL)" },
		{ 0xEE, "XOR $%02X" },

		// CP n
		{ 0xBF, "CP A" },
		{ 0xB8, "CP B" },
		{ 0xB9, "CP C" },
		{ 0xBA, "CP D" },
		{ 0xBB, "CP E" },
		{ 0xBC, "CP H" },
		{ 0xBD, "CP L" },
		{ 0xBE, "CP (HL)" },
		{ 0xFE, "CP $%02X" },

		// INC n
		{ 0x3C, "INC A" },
		{ 0x04, "INC B" },
		{ 0x0C, "INC C" },
		{ 0x14, "INC D" },
		{ 0x1C, "INC E" },
		{ 0x24, "INC H" },
		{ 0x2C, "INC L" },
		{ 0x34, "INC (HL)" },

		// DEC n
		{ 0x3D, "DEC A" },
		{ 0x05, "DEC B" },
		{ 0x0D, "DEC C" },
		{ 0x15, "DEC D" },
		{ 0x1D, "DEC E" },
		{ 0x25, "DEC H" },
		{ 0x2D, "DEC L" },
		{ 0x35, "DEC (HL)" },

		#pragma endregion

		#pragma region 16-bit Arithmetic

		// ADD HL,n
		{ 0x09, "ADD HL,BC" },
		{ 0x19, "ADD HL,DE" },
		{ 0x29, "ADD HL,HL" },
		{ 0x39, "ADD HL,SP" },

		// ADD SP,n
		{ 0xE8, "ADD SP,$%04X" },

		// INC nn
		{ 0x03, "INC BC" },
		{ 0x13, "INC DE" },
		{ 0x23, "INC HL" },
		{ 0x33, "INC SP" },

		// DEC nn
		{ 0x0B, "DEC BC" },
		{ 0x1B, "DEC DE" },
		{ 0x2B, "DEC HL" },
		{ 0x3B, "DEC SP" },

		#pragma endregion

		#pragma region Miscellaneous

		// SWAP n (See Prefix CB opcodes)
		//{ 0xCB 37, "SWAP A" },
		//{ 0xCB 30, "SWAP B" },
		//{ 0xCB 31, "SWAP C" },
		//{ 0xCB 32, "SWAP D" },
		//{ 0xCB 33, "SWAP E" },
		//{ 0xCB 34, "SWAP H" },
		//{ 0xCB 35, "SWAP L" },
		//{ 0xCB 36, "SWAP (HL)" },

		// Decimal adjust (Register A)
		{ 0x27, "DAA" },

		// Complement (Register A)
		{ 0x2F, "CPL" },

		// Complement carry flag
		{ 0x3F, "CCF" },

		// Set carry flag
		{ 0x37, "SCF" },

		// NOP
		{ 0x00, "NOP" },

		// HALT
		{ 0x76, "HALT" },

		// STOP
		{ 0x10, "STOP" }, // technically 10 00

		// Disable/Enable Interrupts
		{ 0xF3, "DI" },
		{ 0xFB, "EI" },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (Register A)
		{ 0x07, "RLCA" }, // NOTE TO SELF: this rotates A and sets the carry flag to the old bit 7 (bit 0 is set to bit 7, c is also set to bit 7)

		// Rotate left through carry (Register A)
		{ 0x17, "RLA" }, // NOTE TO SELF: this rotates A plus the carry flag (bit 0 is set to c, c is set to bit 7)

		// Rotate right with carry (Register A)
		{ 0x0F, "RRCA" },

		// Rotate right through carry (Register A)
		{ 0x1F, "RRA" },

		// Rotate left with carry (RLC n) (See Prefix CB opcodes)
		//{ 0xCB 07, "RLC A" },
		//{ 0xCB 00, "RLC B" },
		//{ 0xCB 01, "RLC C" },
		//{ 0xCB 02, "RLC D" },
		//{ 0xCB 03, "RLC E" },
		//{ 0xCB 04, "RLC H" },
		//{ 0xCB 05, "RLC L" },
		//{ 0xCB 06, "RLC (HL)" },

		// Rotate left through carry (RL n) (See Prefix CB opcodes)
		//{ 0xCB 17, "RL A" },
		//{ 0xCB 10, "RL B" },
		//{ 0xCB 11, "RL C" },
		//{ 0xCB 12, "RL D" },
		//{ 0xCB 13, "RL E" },
		//{ 0xCB 14, "RL H" },
		//{ 0xCB 15, "RL L" },
		//{ 0xCB 16, "RL (HL)" },

		// Rotate right with carry (RRC n) (See Prefix CB opcodes)
		//{ 0xCB 0F, "RRC A" },
		//{ 0xCB 08, "RRC B" },
		//{ 0xCB 09, "RRC C" },
		//{ 0xCB 0A, "RRC D" },
		//{ 0xCB 0B, "RRC E" },
		//{ 0xCB 0C, "RRC H" },
		//{ 0xCB 0D, "RRC L" },
		//{ 0xCB 0E, "RRC (HL)" },

		// Rotate right through carry (RR n) (See Prefix CB opcodes)
		//{ 0xCB 1F, "RR A" },
		//{ 0xCB 18, "RR B" },
		//{ 0xCB 19, "RR C" },
		//{ 0xCB 1A, "RR D" },
		//{ 0xCB 1B, "RR E" },
		//{ 0xCB 1C, "RR H" },
		//{ 0xCB 1D, "RR L" },
		//{ 0xCB 1E, "RR (HL)" },

		// Shift left into carry (SLA n) (See Prefix CB opcodes)
		//{ 0xCB 27, "SLA A" },
		//{ 0xCB 20, "SLA B" },
		//{ 0xCB 21, "SLA C" },
		//{ 0xCB 22, "SLA D" },
		//{ 0xCB 23, "SLA E" },
		//{ 0xCB 24, "SLA H" },
		//{ 0xCB 25, "SLA L" },
		//{ 0xCB 26, "SLA (HL)" },

		// Shift right into carry (SRA n) (See Prefix CB opcodes)
		//{ 0xCB 2F, "SRA A" },
		//{ 0xCB 28, "SRA B" },
		//{ 0xCB 29, "SRA C" },
		//{ 0xCB 2A, "SRA D" },
		//{ 0xCB 2B, "SRA E" },
		//{ 0xCB 2C, "SRA H" },
		//{ 0xCB 2D, "SRA L" },
		//{ 0xCB 2E, "SRA (HL)" },

		// Shift right into carry (SRL n) (See Prefix CB opcodes)
		//{ 0xCB 3F, "SRL A" },
		//{ 0xCB 38, "SRL B" },
		//{ 0xCB 39, "SRL C" },
		//{ 0xCB 3A, "SRL D" },
		//{ 0xCB 3B, "SRL E" },
		//{ 0xCB 3C, "SRL H" },
		//{ 0xCB 3D, "SRL L" },
		//{ 0xCB 3E, "SRL (HL)" },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r) (See Prefix CB opcodes)
		//{ 0xCB 47, "BIT b,A" },
		//{ 0xCB 40, "BIT b,B" },
		//{ 0xCB 41, "BIT b,C" },
		//{ 0xCB 42, "BIT b,D" },
		//{ 0xCB 43, "BIT b,E" },
		//{ 0xCB 44, "BIT b,H" },
		//{ 0xCB 45, "BIT b,L" },
		//{ 0xCB 46, "BIT b,(HL)" },

		// Set Bit (SET b,r) (See Prefix CB opcodes)
		//{ 0xCB C7, "SET b,A" },
		//{ 0xCB C0, "SET b,B" },
		//{ 0xCB C1, "SET b,C" },
		//{ 0xCB C2, "SET b,D" },
		//{ 0xCB C3, "SET b,E" },
		//{ 0xCB C4, "SET b,H" },
		//{ 0xCB C5, "SET b,L" },
		//{ 0xCB C6, "SET b,(HL)" },

		// Reset (clear) Bit (RES b,r) (See Prefix CB opcodes)
		//{ 0xCB 87, "RES b,A" },
		//{ 0xCB 80, "RES b,B" },
		//{ 0xCB 81, "RES b,C" },
		//{ 0xCB 82, "RES b,D" },
		//{ 0xCB 83, "RES b,E" },
		//{ 0xCB 84, "RES b,H" },
		//{ 0xCB 85, "RES b,L" },
		//{ 0xCB 86, "RES b,(HL)" },

		#pragma endregion

		#pragma region Jumps

		// JP nn
		{ 0xC3, "JP $%04X" },

		// JP cc,nn
		{ 0xC2, "JP NZ,$%04X" },
		{ 0xCA, "JP Z,$%04X" },
		{ 0xD2, "JP NC,$%04X" },
		{ 0xDA, "JP C,$%04X" },

		// JP (HL)
		{ 0xE9, "JP (HL)" },

		// JR n (relative jump)
		{ 0x18, "JR $%02X" },

		// JR cc,n
		{ 0x20, "JP NZ,$%02X" },
		{ 0x28, "JP Z,$%02X" },
		{ 0x30, "JP NC,$%02X" },
		{ 0x38, "JP C,$%02X" },

		#pragma endregion

		#pragma region Calls

		// CALL nn
		{ 0xCD, "CALL $%04X" },

		// CALL cc,nn
		{ 0xC4, "CALL NZ,$%04X" },
		{ 0xCC, "CALL Z,$%04X" },
		{ 0xD4, "CALL NC,$%04X" },
		{ 0xDC, "CALL C,$%04X" },

		#pragma endregion

		#pragma region Restarts

		// RST n
		{ 0xC7, "RST 00H" },
		{ 0xCF, "RST 08H" },
		{ 0xD7, "RST 10H" },
		{ 0xDF, "RST 18H" },
		{ 0xE7, "RST 20H" },
		{ 0xEF, "RST 28H" },
		{ 0xF7, "RST 30H" },
		{ 0xFF, "RST 38H" },

		#pragma endregion

		#pragma region Returns

		// RET
		{ 0xC9, "RET" },

		// RET cc
		{ 0xC0, "RET NZ" },
		{ 0xC8, "RET Z" },
		{ 0xD0, "RET NC" },
		{ 0xD8, "RET C" },

		// RETI
		{ 0xD9, "RETI" },

		#pragma endregion
	};

	const map<uint8_t, char*> CPU::sOpcodeDisassembly_PrefixCB
	{
		#pragma region Swap

		// SWAP n (See Prefix CB opcodes)
		{ 0x37, "SWAP A" },
		{ 0x30, "SWAP B" },
		{ 0x31, "SWAP C" },
		{ 0x32, "SWAP D" },
		{ 0x33, "SWAP E" },
		{ 0x34, "SWAP H" },
		{ 0x35, "SWAP L" },
		{ 0x36, "SWAP (HL)" },

		#pragma endregion

		#pragma region Rotates & Shifts

		// Rotate left with carry (RLC n)
		{ 0x07, "RLC A" },
		{ 0x00, "RLC B" },
		{ 0x01, "RLC C" },
		{ 0x02, "RLC D" },
		{ 0x03, "RLC E" },
		{ 0x04, "RLC H" },
		{ 0x05, "RLC L" },
		{ 0x06, "RLC (HL)" },

		// Rotate left through carry (RL n)
		{ 0x17, "RL A" },
		{ 0x10, "RL B" },
		{ 0x11, "RL C" },
		{ 0x12, "RL D" },
		{ 0x13, "RL E" },
		{ 0x14, "RL H" },
		{ 0x15, "RL L" },
		{ 0x16, "RL (HL)" },

		// Rotate right with carry (RRC n)
		{ 0x0F, "RRC A" },
		{ 0x08, "RRC B" },
		{ 0x09, "RRC C" },
		{ 0x0A, "RRC D" },
		{ 0x0B, "RRC E" },
		{ 0x0C, "RRC H" },
		{ 0x0D, "RRC L" },
		{ 0x0E, "RRC (HL)" },

		// Rotate right through carry (RR n)
		{ 0x1F, "RR A" },
		{ 0x18, "RR B" },
		{ 0x19, "RR C" },
		{ 0x1A, "RR D" },
		{ 0x1B, "RR E" },
		{ 0x1C, "RR H" },
		{ 0x1D, "RR L" },
		{ 0x1E, "RR (HL)" },

		// Shif left into carry (SLA n)
		{ 0x27, "SLA A" },
		{ 0x20, "SLA B" },
		{ 0x21, "SLA C" },
		{ 0x22, "SLA D" },
		{ 0x23, "SLA E" },
		{ 0x24, "SLA H" },
		{ 0x25, "SLA L" },
		{ 0x26, "SLA (HL)" },

		// Shif right into carry (SRA n)
		{ 0x2F, "SRA A" },
		{ 0x28, "SRA B" },
		{ 0x29, "SRA C" },
		{ 0x2A, "SRA D" },
		{ 0x2B, "SRA E" },
		{ 0x2C, "SRA H" },
		{ 0x2D, "SRA L" },
		{ 0x2E, "SRA (HL)" },

		// Shift right into carry (SRL n)
		{ 0x3F, "SRL A" },
		{ 0x38, "SRL B" },
		{ 0x39, "SRL C" },
		{ 0x3A, "SRL D" },
		{ 0x3B, "SRL E" },
		{ 0x3C, "SRL H" },
		{ 0x3D, "SRL L" },
		{ 0x3E, "SRL (HL)" },

		#pragma endregion

		#pragma region Bit Opcodes

		// Test Bit (BIT b,r)
		{ 0x47, "BIT 0,A" },
		{ 0x40, "BIT 0,B" },
		{ 0x41, "BIT 0,C" },
		{ 0x42, "BIT 0,D" },
		{ 0x43, "BIT 0,E" },
		{ 0x44, "BIT 0,H" },
		{ 0x45, "BIT 0,L" },
		{ 0x46, "BIT 0,(HL)" },
		{ 0x4F, "BIT 1,A" },
		{ 0x48, "BIT 1,B" },
		{ 0x49, "BIT 1,C" },
		{ 0x4A, "BIT 1,D" },
		{ 0x4B, "BIT 1,E" },
		{ 0x4C, "BIT 1,H" },
		{ 0x4D, "BIT 1,L" },
		{ 0x4E, "BIT 1,(HL)" },
		{ 0x57, "BIT 2,A" },
		{ 0x50, "BIT 2,B" },
		{ 0x51, "BIT 2,C" },
		{ 0x52, "BIT 2,D" },
		{ 0x53, "BIT 2,E" },
		{ 0x54, "BIT 2,H" },
		{ 0x55, "BIT 2,L" },
		{ 0x56, "BIT 2,(HL)" },
		{ 0x5F, "BIT 3,A" },
		{ 0x58, "BIT 3,B" },
		{ 0x59, "BIT 3,C" },
		{ 0x5A, "BIT 3,D" },
		{ 0x5B, "BIT 3,E" },
		{ 0x5C, "BIT 3,H" },
		{ 0x5D, "BIT 3,L" },
		{ 0x5E, "BIT 3,(HL)" },
		{ 0x67, "BIT 4,A" },
		{ 0x60, "BIT 4,B" },
		{ 0x61, "BIT 4,C" },
		{ 0x62, "BIT 4,D" },
		{ 0x63, "BIT 4,E" },
		{ 0x64, "BIT 4,H" },
		{ 0x65, "BIT 4,L" },
		{ 0x66, "BIT 4,(HL)" },
		{ 0x6F, "BIT 5,A" },
		{ 0x68, "BIT 5,B" },
		{ 0x69, "BIT 5,C" },
		{ 0x6A, "BIT 5,D" },
		{ 0x6B, "BIT 5,E" },
		{ 0x6C, "BIT 5,H" },
		{ 0x6D, "BIT 5,L" },
		{ 0x6E, "BIT 5,(HL)" },
		{ 0x77, "BIT 6,A" },
		{ 0x70, "BIT 6,B" },
		{ 0x71, "BIT 6,C" },
		{ 0x72, "BIT 6,D" },
		{ 0x73, "BIT 6,E" },
		{ 0x74, "BIT 6,H" },
		{ 0x75, "BIT 6,L" },
		{ 0x76, "BIT 6,(HL)" },
		{ 0x7F, "BIT 7,A" },
		{ 0x78, "BIT 7,B" },
		{ 0x79, "BIT 7,C" },
		{ 0x7A, "BIT 7,D" },
		{ 0x7B, "BIT 7,E" },
		{ 0x7C, "BIT 7,H" },
		{ 0x7D, "BIT 7,L" },
		{ 0x7E, "BIT 7,(HL)" },

		// Set Bit (SET b,r)
		{ 0xC7, "SET 0,A" },
		{ 0xC0, "SET 0,B" },
		{ 0xC1, "SET 0,C" },
		{ 0xC2, "SET 0,D" },
		{ 0xC3, "SET 0,E" },
		{ 0xC4, "SET 0,H" },
		{ 0xC5, "SET 0,L" },
		{ 0xC6, "SET 0,(HL)" },
		{ 0xCF, "SET 1,A" },
		{ 0xC8, "SET 1,B" },
		{ 0xC9, "SET 1,C" },
		{ 0xCA, "SET 1,D" },
		{ 0xCB, "SET 1,E" },
		{ 0xCC, "SET 1,H" },
		{ 0xCD, "SET 1,L" },
		{ 0xCE, "SET 1,(HL)" },
		{ 0xD7, "SET 2,A" },
		{ 0xD0, "SET 2,B" },
		{ 0xD1, "SET 2,C" },
		{ 0xD2, "SET 2,D" },
		{ 0xD3, "SET 2,E" },
		{ 0xD4, "SET 2,H" },
		{ 0xD5, "SET 2,L" },
		{ 0xD6, "SET 2,(HL)" },
		{ 0xDF, "SET 3,A" },
		{ 0xD8, "SET 3,B" },
		{ 0xD9, "SET 3,C" },
		{ 0xDA, "SET 3,D" },
		{ 0xDB, "SET 3,E" },
		{ 0xDC, "SET 3,H" },
		{ 0xDD, "SET 3,L" },
		{ 0xDE, "SET 3,(HL)" },
		{ 0xE7, "SET 4,A" },
		{ 0xE0, "SET 4,B" },
		{ 0xE1, "SET 4,C" },
		{ 0xE2, "SET 4,D" },
		{ 0xE3, "SET 4,E" },
		{ 0xE4, "SET 4,H" },
		{ 0xE5, "SET 4,L" },
		{ 0xE6, "SET 4,(HL)" },
		{ 0xEF, "SET 5,A" },
		{ 0xE8, "SET 5,B" },
		{ 0xE9, "SET 5,C" },
		{ 0xEA, "SET 5,D" },
		{ 0xEB, "SET 5,E" },
		{ 0xEC, "SET 5,H" },
		{ 0xED, "SET 5,L" },
		{ 0xEE, "SET 5,(HL)" },
		{ 0xF7, "SET 6,A" },
		{ 0xF0, "SET 6,B" },
		{ 0xF1, "SET 6,C" },
		{ 0xF2, "SET 6,D" },
		{ 0xF3, "SET 6,E" },
		{ 0xF4, "SET 6,H" },
		{ 0xF5, "SET 6,L" },
		{ 0xF6, "SET 6,(HL)" },
		{ 0xFF, "SET 7,A" },
		{ 0xF8, "SET 7,B" },
		{ 0xF9, "SET 7,C" },
		{ 0xFA, "SET 7,D" },
		{ 0xFB, "SET 7,E" },
		{ 0xFC, "SET 7,H" },
		{ 0xFD, "SET 7,L" },
		{ 0xFE, "SET 7,(HL)" },

		// Reset (Clear) Bit (RES b,r)
		{ 0x87, "RES 0,A" },
		{ 0x80, "RES 0,B" },
		{ 0x81, "RES 0,C" },
		{ 0x82, "RES 0,D" },
		{ 0x83, "RES 0,E" },
		{ 0x84, "RES 0,H" },
		{ 0x85, "RES 0,L" },
		{ 0x86, "RES 0,(HL)" },
		{ 0x8F, "RES 1,A" },
		{ 0x88, "RES 1,B" },
		{ 0x89, "RES 1,C" },
		{ 0x8A, "RES 1,D" },
		{ 0x8B, "RES 1,E" },
		{ 0x8C, "RES 1,H" },
		{ 0x8D, "RES 1,L" },
		{ 0x8E, "RES 1,(HL)" },
		{ 0x97, "RES 2,A" },
		{ 0x90, "RES 2,B" },
		{ 0x91, "RES 2,C" },
		{ 0x92, "RES 2,D" },
		{ 0x93, "RES 2,E" },
		{ 0x94, "RES 2,H" },
		{ 0x95, "RES 2,L" },
		{ 0x96, "RES 2,(HL)" },
		{ 0x9F, "RES 3,A" },
		{ 0x98, "RES 3,B" },
		{ 0x99, "RES 3,C" },
		{ 0x9A, "RES 3,D" },
		{ 0x9B, "RES 3,E" },
		{ 0x9C, "RES 3,H" },
		{ 0x9D, "RES 3,L" },
		{ 0x9E, "RES 3,(HL)" },
		{ 0xA7, "RES 4,A" },
		{ 0xA0, "RES 4,B" },
		{ 0xA1, "RES 4,C" },
		{ 0xA2, "RES 4,D" },
		{ 0xA3, "RES 4,E" },
		{ 0xA4, "RES 4,H" },
		{ 0xA5, "RES 4,L" },
		{ 0xA6, "RES 4,(HL)" },
		{ 0xAF, "RES 5,A" },
		{ 0xA8, "RES 5,B" },
		{ 0xA9, "RES 5,C" },
		{ 0xAA, "RES 5,D" },
		{ 0xAB, "RES 5,E" },
		{ 0xAC, "RES 5,H" },
		{ 0xAD, "RES 5,L" },
		{ 0xAE, "RES 5,(HL)" },
		{ 0xB7, "RES 6,A" },
		{ 0xB0, "RES 6,B" },
		{ 0xB1, "RES 6,C" },
		{ 0xB2, "RES 6,D" },
		{ 0xB3, "RES 6,E" },
		{ 0xB4, "RES 6,H" },
		{ 0xB5, "RES 6,L" },
		{ 0xB6, "RES 6,(HL)" },
		{ 0xBF, "RES 7,A" },
		{ 0xB8, "RES 7,B" },
		{ 0xB9, "RES 7,C" },
		{ 0xBA, "RES 7,D" },
		{ 0xBB, "RES 7,E" },
		{ 0xBC, "RES 7,H" },
		{ 0xBD, "RES 7,L" },
		{ 0xBE, "RES 7,(HL)" },

		#pragma endregion
	};

	CPU::CPU(MemoryMap& memory) :
		mMemory(memory)
	{
	}

	void CPU::StepCPU()
	{
		//uint8_t opcode = mMemory.ReadByte(mRegisters.PC++);
		//uint16_t operand = true ? 0 : true ? mMemory.ReadByte(mRegisters.PC) : mMemory.ReadWord(mRegisters.PC);
		//mRegisters.PC += 0;
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

	string CPU::GetDisassembly(uint8_t opcode, uint16_t operand)
	{
		map<uint8_t, char*>::const_iterator it;

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
		sprintf_s(str, sizeof(str), it->second, operand);
		return str;
	}

	void CPU::LD_B_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD B," << hex << value << endl;
#endif

		mRegisters.B = value;
	}

	void CPU::LD_C_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD C," << hex << value << endl;
#endif

		mRegisters.C = value;
	}

	void CPU::LD_D_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD D," << hex << value << endl;
#endif

		mRegisters.D = value;
	}

	void CPU::LD_E_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD E," << hex << value << endl;
#endif

		mRegisters.E = value;
	}

	void CPU::LD_H_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD H," << hex << value << endl;
#endif

		mRegisters.H = value;
	}

	void CPU::LD_L_n(uint8_t value)
	{
#ifdef _DEBUG
		cout << "LD L," << hex << value << endl;
#endif

		mRegisters.L = value;
	}
}
