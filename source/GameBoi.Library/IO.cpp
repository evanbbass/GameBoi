#include "pch.h"
#include "IO.h"
#include "MemoryMap.h"

namespace GameBoi
{
	IO::IO(MemoryMap& memory) :
		mMemory(memory), mGPU(memory), mTimer(memory), mKeypad(memory), mInterruptFlags(0)
	{
	}

	uint8_t IO::ReadByte(uint16_t address) const
	{
		switch (address)
		{
			case MemoryMap::InterruptFlagAddress:
				return mInterruptFlags;

			// Keypad registers
			case Keypad::KeypadRegisterAddress:
				return mKeypad.GetKeypadRegister();

			// timer registers
			case Timer::DividerAddress:
				return mTimer.GetDivider();
			case Timer::TimerAddress:
				return mTimer.GetTimer();
			case Timer::TimerModulatorAddress:
				return mTimer.GetTimerModulator();
			case Timer::TimerControllerAddress:
				return mTimer.GetTimerController();

			// GPU registers
			case LCDControl::LCDControlRegisterAddress:
				return mGPU.GetLCDControlRegister();
			case GPU::LCDStatusRegisterAddress:
				return mGPU.GetLCDStatusRegister();
			case GPU::ScrollYAddress:
				return mGPU.GetScrollY();
			case GPU::ScrollXAddress:
				return mGPU.GetScrollX();
			case GPU::CurrentScanlineAddress:
				return mGPU.GetCurrentScanline();
			case GPU::CoincidenceRegisterAddress:
				return mGPU.GetCoincidenceRegister();
			case GPU::DMAAddress:
				return 0xFF;
			case GPU::BackgroundPalletAddress:
				return mGPU.GetBackgroundPallet();
			case GPU::SpritePallet0Address:
				return mGPU.GetSpritePallet0();
			case GPU::SpritePallet1Address:
				return mGPU.GetSpritePallet1();
			case GPU::WindowYAddress:
				return mGPU.GetWindowY();
			case GPU::WindowXAddress:
				return mGPU.GetWindowX();

			default:
				return 0xFF;
		}
	}

	void IO::WriteByte(uint16_t address, uint8_t value)
	{
		switch (address)
		{
			case MemoryMap::InterruptFlagAddress:
				mInterruptFlags = value;
				break;

			// timer registers
			case Timer::DividerAddress:
				mTimer.SetDivider(value);
				break;
			case Timer::TimerAddress:
				mTimer.SetTimer(value);
				break;
			case Timer::TimerModulatorAddress:
				mTimer.SetTimerModulator(value);
				break;
			case Timer::TimerControllerAddress:
				mTimer.SetTimerController(value);
				break;

			// Keypad registers
			case Keypad::KeypadRegisterAddress:
				mKeypad.SetKeypadRegister(value);
				break;

			// GPU registers
			case LCDControl::LCDControlRegisterAddress:
				mGPU.SetLCDControlRegister(value);
				break;
			case GPU::LCDStatusRegisterAddress:
				mGPU.SetLCDStatusRegister(value);
				break;
			case GPU::ScrollYAddress:
				mGPU.SetScrollY(value);
				break;
			case GPU::ScrollXAddress:
				mGPU.SetScrollX(value);
				break;
			case GPU::CurrentScanlineAddress:
				// writing to the current scanline resets it
				mGPU.SetCurrentScanline(0);
				break;
			case GPU::CoincidenceRegisterAddress:
				mGPU.SetCoincidenceRegister(value);
				break;
			case GPU::DMAAddress:
				mMemory.DMATransfer(value);
				break;
			case GPU::BackgroundPalletAddress:
				mGPU.SetBackgroundPallet(value);
				break;
			case GPU::SpritePallet0Address:
				mGPU.SetSpritePallet0(value);
				break;
			case GPU::SpritePallet1Address:
				mGPU.SetSpritePallet1(value);
				break;
			case GPU::WindowYAddress:
				mGPU.SetWindowY(value);
				break;
			case GPU::WindowXAddress:
				mGPU.SetWindowX(value);
				break;

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

	GPU& IO::GetGPU()
	{
		return mGPU;
	}

	const GPU& IO::GetGPU() const
	{
		return mGPU;
	}
}
