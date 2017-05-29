#include "pch.h"
#include "CPU.h"

using namespace std;

namespace GameBoi
{
	CPU::CPU()
	{
	}

	CPU::CPU(const string& cartFileName)
	{
		LoadCartridge(cartFileName);
	}

	void CPU::Reset()
	{
		mRegisters.Reset();
		mMemory.Reset();
	}

	void CPU::LoadCartridge(const string& cartFileName)
	{
		Reset();
		mMemory.GetCartridge().ReadFromFile(cartFileName);
	}
}
