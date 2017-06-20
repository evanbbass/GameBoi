#pragma once

#include "CPU.h"
#include "MemoryMapManaged.h"
#include "RegistersManaged.h"

namespace GameBoiManaged
{
	public ref class CPUManaged
	{
	public:
		explicit CPUManaged(MemoryMapManaged^ memoryMap);
		CPUManaged(GameBoi::CPU& unmanagedCPU);

		GameBoi::CPU& GetUnmanaged();

		void StepCPU();

		void Reset();

		RegistersManaged^ GetRegisters();
		MemoryMapManaged^ GetMemoryMap();

		static System::Int32 GetOperandLength(System::Byte opcode);
		static System::String^ GetDisassembly(System::Byte opcode);
		static System::String^ GetDisassembly(System::Byte opcode, System::UInt16 operand);

	private:
		GameBoi::CPU* mCPU;
	};
}
