#include "pch.h"
#include "CPUManaged.h"

using namespace std;
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
		try
		{
			mCPU->StepCPU();
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
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
		return mCPU->GetInterruptMasterEnabled();
	}

	Byte CPUManaged::InterruptEnabledRegister::get()
	{
		return mCPU->GetInterruptEnabledRegister();
	}

	Byte CPUManaged::InterruptFlagRegister::get()
	{
		return mCPU->GetInterruptFlagRegister();
	}

	Int32 CPUManaged::GetOperandLength(Byte opcode)
	{
		try
		{
			return CPU::GetOperandLength(opcode);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	String^ CPUManaged::GetDisassembly(Byte opcode)
	{
		try
		{
			return gcnew String(CPU::GetDisassembly(opcode).c_str());
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	String^ CPUManaged::GetDisassembly(Byte opcode, UInt16 operand)
	{
		try
		{
			return gcnew String(CPU::GetDisassembly(opcode, operand).c_str());
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}
}
