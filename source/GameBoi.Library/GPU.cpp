#include "pch.h"
#include "GPU.h"
#include "MemoryMap.h"
#include "Utilities.h"

using namespace std;

namespace GameBoi
{
	GPU::GPU(MemoryMap& memory) :
		mMemory(memory), mScanlineCounter(0)
	{
	}

	void GPU::StepGPU(int32_t cpuCycles)
	{
		if (!IsEnabled())
		{
			// while the LCD is disabled, reset the scanline and set the mode to VBlank
			mScanlineCounter = 0;
			mMemory.WriteByte(CurrentScanlineAddress, 0);
			SetLCDStatus(LCDStatus::VBlank);
		}
		else
		{
			mScanlineCounter += cpuCycles;

			if (mScanlineCounter >= CPUCyclesPerScanline)
			{
				// reset the counter
				mScanlineCounter -= CPUCyclesPerScanline;

				HandleHBlank();
			}

			UpdateLCDStatus();
			CheckCoincidenceFlag();
		}
	}

	bool GPU::IsEnabled() const
	{
		// TODO make 7 a constant
		return Utilities::TestBit(mMemory.ReadByte(LCDControlRegisterAddress), 7);
	}

	uint8_t GPU::GetCurrentScanline() const
	{
		return mMemory.ReadByte(CurrentScanlineAddress);
	}

	uint8_t GPU::GetLCDStatusRegister() const
	{
		return mMemory.ReadByte(LCDStatusRegisterAddress);
	}

	GPU::LCDStatus GPU::GetLCDStatus() const
	{
		return static_cast<LCDStatus>(GetLCDStatusRegister() & 0b11);
	}

	uint8_t GPU::GetLCDControlRegister() const
	{
		return mMemory.ReadByte(LCDControlRegisterAddress);
	}

	uint8_t GPU::GetCoincidenceRegister() const
	{
		return mMemory.ReadByte(CoincidenceRegisterAddress);
	}

	void GPU::DrawScanLine()
	{
		// TODO graphics! my fave!
	}

	void GPU::HandleHBlank()
	{
		// increment the current scanline
		uint8_t currentScanline = GetCurrentScanline() + 1;

		if (currentScanline == ScreenHeight)
		{
			// scanlines 144 through 153 are the VBlank period
			mMemory.SetVBlankInterruptFlag();
		}
		else if (currentScanline > MaxScanlines)
		{
			// if scanline is over 153, reset it
			currentScanline = 0;
		}

		// TODO technically this isn't allowed
		mMemory.WriteByte(CurrentScanlineAddress, currentScanline);

		// between 0 and 143, draw the scanline
		if (currentScanline < ScreenHeight)
		{
			DrawScanLine();
		}
	}

	void GPU::UpdateLCDStatus()
	{
		LCDStatus lastStatus = GetLCDStatus();
		bool requestInterrupt = false;
		if (GetCurrentScanline() >= 144)
		{
			SetLCDStatus(LCDStatus::VBlank);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), VBlankInterruptBit);
		}
		else if (mScanlineCounter < OAMStatusCutoff)
		{
			SetLCDStatus(LCDStatus::OAM);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), OAMInterruptBit);
		}
		else if (mScanlineCounter < VRAMStatusCutoff)
		{
			SetLCDStatus(LCDStatus::VRAM);
		}
		else
		{
			SetLCDStatus(LCDStatus::HBlank);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), HBlankInterruptBit);
		}

		// Handle interrupts
		if (requestInterrupt && lastStatus != GetLCDStatus())
		{
			mMemory.SetLCDInterruptFlag();
		}
	}

	void GPU::CheckCoincidenceFlag()
	{
		if (GetCurrentScanline() == GetCoincidenceRegister())
		{
			uint8_t newStatus = Utilities::SetBit(GetLCDStatusRegister(), CoincidenceBit);
			mMemory.WriteByte(LCDStatusRegisterAddress, newStatus);

			if (Utilities::TestBit(GetLCDStatusRegister(), CoincidenceInterruptBit))
			{
				mMemory.SetLCDInterruptFlag();
			}
		}
		else
		{
			uint8_t newStatus = Utilities::ResetBit(GetLCDStatusRegister(), CoincidenceBit);
			mMemory.WriteByte(LCDStatusRegisterAddress, newStatus);
		}
	}

	void GPU::SetLCDStatus(LCDStatus status)
	{
		uint8_t statusReg = (GetLCDStatusRegister() & 0b11111100) | static_cast<uint8_t>(status);
		mMemory.WriteByte(LCDStatusRegisterAddress, statusReg);
	}
}
