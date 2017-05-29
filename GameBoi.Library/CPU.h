#pragma once
#include "MemoryMap.h"
#include "Registers.h"

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

	private:
		Registers mRegisters;
		MemoryMap& mMemory;

		#pragma region  8-Bit Loads
		void LD_B_n(uint8_t value);
		void LD_C_n(uint8_t value);
		void LD_D_n(uint8_t value);
		void LD_E_n(uint8_t value);
		void LD_H_n(uint8_t value);
		void LD_L_n(uint8_t value);
		#pragma endregion
	};
}