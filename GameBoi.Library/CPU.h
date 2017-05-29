#pragma once
#include "MemoryMap.h"
#include "Registers.h"

namespace GameBoi
{
	class CPU
	{
	public:
		CPU();
		explicit CPU(const std::string& cartFileName);
		~CPU() = default;

		void Reset();
		void LoadCartridge(const std::string& cartFileName);

	private:
		Registers mRegisters;
		MemoryMap mMemory;
	};
}