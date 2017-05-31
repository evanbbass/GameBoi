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
		{ 0xF2, "LD A,($FF00+C)" }, // also LD A,(C)
		{ 0xE2, "LD ($FF00+C),A" },

		// LD A,(HL-) and variations
		{ 0x3A, "LD A,(HL-)" }, // also LD A,(HLD) or LDD A,(HL)
		{ 0x32, "LD (HL-),A" }, // also LD (HLD),A or LDD (HL),A
		{ 0x2A, "LD A,(HL+)" }, // also LD A,(HLI) or LDI A,(HL)
		{ 0x22, "LD (HL+),A" }, // also LD (HLI),A or LDI (HL),A

		// LDH (n),A and reverse
		{ 0xE0, "LD A,($FF00+$%02X)" },
		{ 0xF0, "LD ($FF00+$%02X),A" },

		#pragma endregion

		#pragma region 16-bit loads

		// TODO

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
		map<uint8_t, char*>::const_iterator it = sOpcodeDisassembly.find(opcode);
		if (it == sOpcodeDisassembly.end())
		{
			throw exception("Opcode not found!");
		}

		char str[20];
		sprintf_s(str, sizeof(str), it->second, operand);
		return string(str);
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
