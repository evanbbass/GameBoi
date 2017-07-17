#include "pch.h"
#include "CPU.h"
#include "Utilities.h"

using namespace std;

namespace GameBoi
{
	CPU::CPU(MemoryMap& memory) :
		mMemory(memory), mInterruptMasterEnabled(true), mHalted(false), mEnableInterruptsAfterNextInstruction(false), mDisableInterruptsAfterNextInstruction(false)
	{
	}

	int32_t CPU::StepCPU()
	{
		if (mInterruptMasterEnabled)
		{
			HandleInterrupts();
		}

		if (mHalted)
		{
			return 0;
		}

		uint8_t opcode = 0x00;
		uint16_t pc = mRegisters.PC;
		try
		{
			bool disableInterrupts = false, enableInterrupts = false;
			if (mDisableInterruptsAfterNextInstruction)
			{
				disableInterrupts = true;
				mDisableInterruptsAfterNextInstruction = false;
			}
			if (mEnableInterruptsAfterNextInstruction)
			{
				enableInterrupts = true;
				mEnableInterruptsAfterNextInstruction = false;
			}

			// gather instruction information
			opcode = mMemory.ReadByte(mRegisters.PC++);

			// if opcode is 0xCB, it is prefix-CB and we need to read another byte
			// TODO unify this with the DisassembleRom() method in Cartridge class
			Instruction instruction = opcode != 0xCB ?
				OpcodeInstructionMap.at(opcode) :
				OpcodeInstructionMap_PrefixCB.at(mMemory.ReadByte(mRegisters.PC++));
			uint16_t operand = 0x0000;
			if (instruction.OperandLength == 1)
			{
				operand = mMemory.ReadByte(mRegisters.PC);
				mRegisters.PC += 1;
			}
			else if (instruction.OperandLength == 2)
			{
				operand = mMemory.ReadWord(mRegisters.PC);
				mRegisters.PC += 2;
			}

			// execute instruction
			invoke(instruction.Function, this, operand);

			if (disableInterrupts)
			{
				mInterruptMasterEnabled = false;
			}
			if (enableInterrupts)
			{
				mInterruptMasterEnabled = true;
			}

			return instruction.Cycles;
		}
		catch (exception& ex)
		{
			char message[100];
			sprintf_s(message, sizeof(message), "Error executing instruction 0x%02X at memory location 0x%04X:\n%s", opcode, pc, ex.what());
			throw exception(message);
		}
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

	bool CPU::GetInterruptMasterEnabled() const
	{
		return mInterruptMasterEnabled;
	}

	uint8_t CPU::GetInterruptEnabledRegister() const
	{
		return mMemory.GetInterruptEnabledRegister();
	}

	uint8_t CPU::GetInterruptFlagRegister() const
	{
		return mMemory.GetInterruptFlagRegister();
	}

	void CPU::HandleInterrupts()
	{
		uint8_t interruptsEnabled = GetInterruptEnabledRegister();
		uint8_t interruptsFlag = GetInterruptFlagRegister();
		uint8_t interrupts = interruptsEnabled & interruptsFlag;

		if (interrupts != 0)
		{
			mInterruptMasterEnabled = false;
			PushWordToStack(mRegisters.PC);

			if (Utilities::TestBit(interrupts, MemoryMap::VBlankInterruptBit))
			{
				mRegisters.PC = MemoryMap::VBlankISRAddress;
				mMemory.ResetVBlankInterruptFlag();
			}
			else if (Utilities::TestBit(interrupts, MemoryMap::LCDInterruptBit))
			{
				mRegisters.PC = MemoryMap::LCDISRAddress;
				mMemory.ResetLCDInterruptFlag();
			}
			else if (Utilities::TestBit(interrupts, MemoryMap::TimerInterruptBit))
			{
				mRegisters.PC = MemoryMap::TimerISRAddress;
				mMemory.ResetTimerInterruptFlag();
			}
			else if (Utilities::TestBit(interrupts, MemoryMap::KeypadInterruptBit))
			{
				mRegisters.PC = MemoryMap::KeypadISRAddress;
				mMemory.ResetKeypadInterruptFlag();
			}

			mHalted = false;
		}
	}
}
