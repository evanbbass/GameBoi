#include "pch.h"
#include "CPUManaged.h"

using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	CPUManaged::CPUManaged(MemoryMapManaged^ memoryMap) :
		mCPU(new CPU(memoryMap->GetUnmanaged()))
	{
	}

	CPUManaged::CPUManaged(CPU& unmanagedCPU) :
		mCPU(&unmanagedCPU)
	{
	}

	CPU& CPUManaged::GetUnmanaged()
	{
		return *mCPU;
	}

	void CPUManaged::StepCPU()
	{
		mCPU->StepCPU();
	}

	void CPUManaged::Reset()
	{
		mCPU->Reset();
	}

	RegistersManaged^ CPUManaged::GetRegisters()
	{
		return gcnew RegistersManaged(mCPU->GetRegisters());
	}

	MemoryMapManaged^ CPUManaged::GetMemoryMap()
	{
		return gcnew MemoryMapManaged(mCPU->GetMemoryMap());
	}

	Int32 CPUManaged::GetOperandLength(Byte opcode)
	{
		return CPU::GetOperandLength(opcode);
	}

	System::String ^ CPUManaged::GetDisassembly(System::Byte opcode)
	{
		return gcnew String(CPU::GetDisassembly(opcode).c_str());
	}

	String^ CPUManaged::GetDisassembly(Byte opcode, UInt16 operand)
	{
		return gcnew String(CPU::GetDisassembly(opcode, operand).c_str());
	}
}
