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

		property GameBoi::CPU& Unmanaged { GameBoi::CPU& get(); }

		void StepCPU();

		void Reset();

		property RegistersManaged^ Registers { RegistersManaged^ get(); }
		property MemoryMapManaged^ MemoryMap { MemoryMapManaged^ get(); }

		property bool InterruptMasterEnabled { bool get(); }

		static System::Int32 GetOperandLength(System::Byte opcode);
		static System::String^ GetDisassembly(System::Byte opcode);
		static System::String^ GetDisassembly(System::Byte opcode, System::UInt16 operand);

	private:
		GameBoi::CPU* mCPU;
	};
}
