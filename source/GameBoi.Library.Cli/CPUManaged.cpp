#include "pch.h"
#include "CPUManaged.h"

using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	CPUManaged::CPUManaged(MemoryMapManaged^ memoryMap) :
		mCPU(new CPU(memoryMap->Unmanaged))
	{
	}

	CPUManaged::CPUManaged(CPU& unmanagedCPU) :
		mCPU(&unmanagedCPU)
	{
	}

	CPU& CPUManaged::Unmanaged::get()
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

	RegistersManaged^ CPUManaged::Registers::get()
	{
		return gcnew RegistersManaged(mCPU->GetRegisters());
	}

	MemoryMapManaged^ CPUManaged::MemoryMap::get()
	{
		return gcnew MemoryMapManaged(mCPU->GetMemoryMap());
	}

	bool CPUManaged::InterruptMasterEnabled::get()
	{
		return mCPU->InterruptMasterEnabled();
	}

	Int32 CPUManaged::GetOperandLength(Byte opcode)
	{
		return CPU::GetOperandLength(opcode);
	}

	String^ CPUManaged::GetDisassembly(Byte opcode)
	{
		return gcnew String(CPU::GetDisassembly(opcode).c_str());
	}

	String^ CPUManaged::GetDisassembly(Byte opcode, UInt16 operand)
	{
		return gcnew String(CPU::GetDisassembly(opcode, operand).c_str());
	}
}
