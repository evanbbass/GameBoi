#include "pch.h"
#include "CPU.h"
#include <iostream>

using namespace std;

namespace GameBoi
{
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
