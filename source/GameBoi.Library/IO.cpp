#include "pch.h"
#include "IO.h"

namespace GameBoi
{
	IO::IO(MemoryMap& memory) :
		mMemory(memory), mTimer(memory), mKeypad(memory)
	{
	}

	uint8_t IO::ReadByte(uint16_t address) const
	{
		switch (address)
		{
			// timer registers
			case Timer::DividerAddress:
				return mTimer.GetDivider();
			case Timer::TimerAddress:
				return mTimer.GetTimer();
			case Timer::TimerModulatorAddress:
				return mTimer.GetTimerModulator();
			case Timer::TimerControllerAddress:
				return mTimer.GetTimerController();

			// Keypad registers
			case Keypad::KeypadRegisterAddress:
				return mKeypad.GetKeypadRegister();

			default:
				return 0;
		}
	}

	void IO::WriteByte(uint16_t address, uint8_t value)
	{
		switch (address)
		{
			// timer registers
			case Timer::DividerAddress:
				// Writing to the divider always sets it to 0
				mTimer.SetDivider(0);
			case Timer::TimerAddress:
				mTimer.SetTimer(value);
			case Timer::TimerModulatorAddress:
				mTimer.SetTimerModulator(value);
			case Timer::TimerControllerAddress:
				mTimer.SetTimerController(value);

			// Keypad registers
			case Keypad::KeypadRegisterAddress:
				mKeypad.SetKeypadRegister(value);

			default:
				break;
		}
	}

	Timer& IO::GetTimer()
	{
		return mTimer;
	}

	const Timer& IO::GetTimer() const
	{
		return mTimer;
	}

	Keypad& IO::GetKeypad()
	{
		return mKeypad;
	}

	const Keypad& IO::GetKeypad() const
	{
		return mKeypad;
	}
}
