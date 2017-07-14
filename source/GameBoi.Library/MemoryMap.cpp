#include "pch.h"
#include "MemoryMap.h"
#include "Utilities.h"

using namespace std;

namespace GameBoi
{
	const array<uint8_t, MemoryMap::BIOS_SIZE> MemoryMap::BIOS =
	{
		0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
		0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
		0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
		0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
		0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
		0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
		0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
		0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
		0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
		0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
		0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
		0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
		0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
		0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
		0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
		0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
	};

	MemoryMap::MemoryMap() :
		mIO(*this)
	{
		Reset();
	}

	void MemoryMap::Reset()
	{
		mIsInBIOS = false;
		mVideoRAM.fill(0);
		mWorkingRAM.fill(0);
		mInternalRAM.fill(0);
	}

	uint8_t MemoryMap::ReadByte(uint16_t address) const
	{
		if (mIsInBIOS && address < BIOS_SIZE)
		{
			return BIOS[address];
		}
		else if (address < CARTRIDGE_END)
		{
			return mCart.ReadByte(address);
		}
		else if (address < VRAM_END)
		{
			if (mIO.GetGPU().GetLCDStatus() != GPU::LCDStatus::VRAM)
			{
				return mVideoRAM[address - VRAM_START];
			}
			else
			{
				// when the LCD Controller is drawing the screen, do not allow access to VRAM
				return 0xFF;
			}
		}
		else if (address < SRAM_END)
		{
			return mCart.ReadByte(address);
		}
		else if (address < WRAM_END)
		{
			return mWorkingRAM[address - WRAM_START];
		}
		else if (address < WRAM_ECHO_END)
		{
			return mWorkingRAM[address - WRAM_ECHO_START];
		}
		else if (address < OAM_END)
		{
			GPU::LCDStatus status = mIO.GetGPU().GetLCDStatus();
			if (status != GPU::LCDStatus::OAM && status != GPU::LCDStatus::VRAM)
			{
				return mOAM.ReadByte(address);
			}
			else
			{
				return 0xFF;
			}
		}
		else if (address < UNUSABLE_END)
		{
			// Do nothing
			return 0;
		}
		else if (address < IO_END)
		{
			return mIO.ReadByte(address - IO_START);
		}
		else if (address < INTERNAL_RAM_END)
		{
			return mInternalRAM[address - INTERNAL_RAM_START];
		}
		else // if address == 0xFFFF
		{
			return mInterruptEnableRegister;
		}
	}

	void MemoryMap::WriteByte(uint16_t address, uint8_t value)
	{
		if (address < CARTRIDGE_END)
		{
			mCart.WriteByte(address, value);
		}
		else if (address < VRAM_END)
		{
			if (mIO.GetGPU().GetLCDStatus() != GPU::LCDStatus::VRAM)
			{
				mVideoRAM[address - VRAM_START] = value;
			}
		}
		else if (address < SRAM_END)
		{
			mCart.WriteByte(address, value);
		}
		else if (address < WRAM_END)
		{
			mWorkingRAM[address - WRAM_START] = value;
		}
		else if (address < WRAM_ECHO_END)
		{
			mWorkingRAM[address - WRAM_ECHO_START] = value;
		}
		else if (address < OAM_END)
		{
			GPU::LCDStatus status = mIO.GetGPU().GetLCDStatus();
			if (status != GPU::LCDStatus::OAM && status != GPU::LCDStatus::VRAM)
			{
				mOAM.WriteByte(address, value);
			}
		}
		else if (address < UNUSABLE_END)
		{
			// Do nothing
		}
		else if (address < IO_END)
		{
			mIO.WriteByte(address, value);
		}
		else if (address < INTERNAL_RAM_END)
		{
			mInternalRAM[address - INTERNAL_RAM_START] = value;
		}
		else // if address == 0xFFFF
		{
			mInterruptEnableRegister = value;
		}
	}

	void MemoryMap::LoadCartridgeFromFile(const string& fileName)
	{
		mCart.ReadFromFile(fileName);
	}

	Cartridge& MemoryMap::GetCartridge()
	{
		return mCart;
	}

	const Cartridge& MemoryMap::GetCartridge() const
	{
		return mCart;
	}

	ObjectAttributeMemory& MemoryMap::GetOAM()
	{
		return mOAM;
	}

	const ObjectAttributeMemory& MemoryMap::GetOAM() const
	{
		return mOAM;
	}

	IO& MemoryMap::GetIO()
	{
		return mIO;
	}

	const IO& MemoryMap::GetIO() const
	{
		return mIO;
	}

	uint8_t MemoryMap::GetInterruptEnabledRegister() const
	{
		return ReadByte(InterruptEnabledAddress);
	}

	uint8_t MemoryMap::GetInterruptFlagRegister() const
	{
		return ReadByte(InterruptFlagAddress);
	}

	void MemoryMap::SetVBlankInterruptFlag()
	{
		uint8_t interrupts = Utilities::SetBit(GetInterruptFlagRegister(), VBlankInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::SetLCDInterruptFlag()
	{
		uint8_t interrupts = Utilities::SetBit(GetInterruptFlagRegister(), LCDInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::SetTimerInterruptFlag()
	{
		uint8_t interrupts = Utilities::SetBit(GetInterruptFlagRegister(), TimerInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::SetKeypadInterruptFlag()
	{
		uint8_t interrupts = Utilities::SetBit(GetInterruptFlagRegister(), KeypadInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::DMATransfer(uint8_t value)
	{
		uint16_t address = value << 8;
		for (uint16_t i = 0; i < OAM_SIZE; ++i)
		{
			WriteByte(OAM_START + i, ReadByte(address + i));
		}
	}

	void MemoryMap::ResetVBlankInterruptFlag()
	{
		uint8_t interrupts = Utilities::ResetBit(GetInterruptFlagRegister(), VBlankInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::ResetLCDInterruptFlag()
	{
		uint8_t interrupts = Utilities::ResetBit(GetInterruptFlagRegister(), LCDInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::ResetTimerInterruptFlag()
	{
		uint8_t interrupts = Utilities::ResetBit(GetInterruptFlagRegister(), TimerInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}

	void MemoryMap::ResetKeypadInterruptFlag()
	{
		uint8_t interrupts = Utilities::ResetBit(GetInterruptFlagRegister(), KeypadInterruptBit);
		WriteByte(InterruptFlagAddress, interrupts);
	}
}
