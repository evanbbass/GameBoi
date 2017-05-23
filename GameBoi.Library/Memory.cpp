#include "pch.h"
#include "Memory.h"

namespace GameBoi
{
	Memory::Memory()
	{
		Reset();
	}

	void Memory::Reset()
	{
		mCart.Reset();
		memset(mVideoRAM, 0, sizeof(mVideoRAM));
		memset(mSwitchableRAM, 0, sizeof(mSwitchableRAM));
		memset(mWorkingRAM, 0, sizeof(mWorkingRAM));
		memset(mWorkingRAMEcho, 0, sizeof(mWorkingRAMEcho));
		memset(mOAM, 0, sizeof(mOAM));
		memset(UNUSABLE0, 0, sizeof(UNUSABLE0));
		memset(mIO, 0, sizeof(mIO));
		memset(UNUSABLE1, 0, sizeof(UNUSABLE1));
		memset(mInternalRAM, 0, sizeof(mInternalRAM));
	}

	uint8_t& Memory::operator[](uint16_t address)
	{
		if (address < CARTRIDGE_END)
		{
			return mCart[address];
		}
		else if (address < VRAM_END)
		{
			return mVideoRAM[address - VRAM_START];
		}
		else if (address < SRAM_END)
		{
			return mSwitchableRAM[address - SRAM_START];
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
			return mOAM[address - OAM_START];
		}
		else if (address < UNUSABLE0_END)
		{
			throw std::exception("Unusable memory!");
		}
		else if (address < IO_END)
		{
			return mIO[address - IO_START];
		}
		else if (address < UNUSABLE1_END)
		{
			throw std::exception("Unusable memory!");
		}
		else if (address < INTERNAL_RAM_END)
		{
			return mInternalRAM[address - INTERNAL_RAM_START];
		}
		else
		{
			throw std::exception("Address out of range!");
		}
	}

	uint8_t Memory::operator[](uint16_t address) const
	{
		return const_cast<Memory&>(*this)[address];
	}

	uint8_t Memory::ReadByte(uint16_t address) const
	{
		return (*this)[address];
	}

	uint16_t Memory::ReadWord(uint16_t address) const
	{
		return ((*this)[address + 1] << 8) | (*this)[address];
	}

	void Memory::WriteByte(uint16_t address, uint8_t value)
	{
		(*this)[address] = value;
	}

	void Memory::WriteWord(uint16_t address, uint16_t value)
	{
		(*this)[address] = value & 0x00FF;
		(*this)[address + 1] = (value & 0xFF00) >> 8;
	}
}
