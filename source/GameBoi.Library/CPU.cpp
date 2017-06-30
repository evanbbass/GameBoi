#include "pch.h"
#include "CPU.h"

using namespace std;

namespace GameBoi
{
	const uint16_t CPU::sInterruptEnabledAddress = 0xFFFF;
	const uint16_t CPU::sInterruptFlagAddress = 0xFF0F;
	const uint16_t CPU::sDividerAddress = 0xFF04;
	const uint16_t CPU::sTimerAddress = 0xFF05;
	const uint16_t CPU::sTimerModulatorAddress = 0xFF06;
	const uint16_t CPU::sTimerControllerAddress = 0xFF07;
	const uint8_t CPU::sVBlankInterruptFlag = 0b00000001;
	const uint8_t CPU::sLCDInterruptFlag = 0b00000010;
	const uint8_t CPU::sTimerInterruptFlag = 0b00000100;
	const uint8_t CPU::sJoypadInterruptFlag = 0b00001000;
	const uint16_t CPU::sVBlankISRAddress = 0x0040;
	const uint16_t CPU::sLCDISRAddress = 0x0048;
	const uint16_t CPU::sTimerISRAddress = 0x0050;
	const uint16_t CPU::sJoypadISRAddress = 0x0060;

	CPU::CPU(MemoryMap& memory) :
		mMemory(memory), mInterruptMasterEnabled(false), mHalted(false), mEnableInterruptsAfterNextInstruction(false), mDisableInterruptsAfterNextInstruction(false)
	{
	}

	void CPU::StepCPU()
	{
		if (mInterruptMasterEnabled)
		{
			HandleInterrupts();
		}

		if (mHalted)
		{
			return;
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
				sOpcodeDisassembly.at(opcode) :
				sOpcodeDisassembly_PrefixCB.at(mMemory.ReadByte(mRegisters.PC++));
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
			// increment clock cycles

			if (disableInterrupts)
			{
				mInterruptMasterEnabled = false;
			}
			if (enableInterrupts)
			{
				mInterruptMasterEnabled = true;
			}
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
		return mMemory.ReadByte(sInterruptEnabledAddress);
	}

	uint8_t CPU::GetInterruptFlagRegister() const
	{
		return mMemory.ReadByte(sInterruptFlagAddress);
	}

	void CPU::HandleInterrupts()
	{
		uint8_t interruptsEnabled = GetInterruptEnabledRegister();
		uint8_t interruptsFlag = GetInterruptFlagRegister();
		uint8_t interrupts = interruptsEnabled & interruptsFlag;

		if (interrupts != 0)
		{
			if ((interrupts & 0xF0) != 0)
			{
				throw exception("Invalid interrupt flag detected!");
			}

			mInterruptMasterEnabled = false;
			PushWordToStack(mRegisters.PC);

			if ((interrupts & sVBlankInterruptFlag) != 0)
			{
				mRegisters.PC = sVBlankISRAddress;
				ResetVBlankInterruptFlag();
			}
			else if ((interrupts & sLCDInterruptFlag) != 0)
			{
				mRegisters.PC = sLCDISRAddress;
				ResetLCDInterruptFlag();
			}
			else if ((interrupts & sTimerInterruptFlag) != 0)
			{
				mRegisters.PC = sTimerISRAddress;
				ResetTimerInterruptFlag();
			}
			else if ((interrupts & sJoypadInterruptFlag) != 0)
			{
				mRegisters.PC = sJoypadISRAddress;
				ResetJoypadInterruptFlag();
			}

			mHalted = false;
		}
	}

	void CPU::SetVBlankInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts |= sVBlankInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::SetLCDInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts |= sLCDInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::SetTimerInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts |= sTimerInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::SetJoypadInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts |= sJoypadInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::ResetVBlankInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts &= ~sVBlankInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::ResetLCDInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts &= ~sLCDInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::ResetTimerInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts &= ~sTimerInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}

	void CPU::ResetJoypadInterruptFlag()
	{
		uint8_t interrupts = GetInterruptFlagRegister();
		interrupts &= ~sJoypadInterruptFlag;
		mMemory.WriteByte(sInterruptFlagAddress, interrupts);
	}
}
