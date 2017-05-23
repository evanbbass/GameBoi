#include "pch.h"
#include "Cartridge.h"

using namespace std;

namespace GameBoi
{
	Cartridge::Cartridge()
	{
		Reset();
	}

	void Cartridge::Reset()
	{
		memset(mROMBank0, 0, sizeof(mROMBank0));
		memset(mSwitchableROMBank, 0, sizeof(mSwitchableROMBank));
	}

	uint8_t& Cartridge::operator[](uint16_t address)
	{
		if (address < 0x4000)
		{
			return mROMBank0[address];
		}
		else if (address < 0x8000)
		{
			return mSwitchableROMBank[address - 0x4000];
		}
		else
		{
			throw exception("Address out of Cartridge range.");
		}
	}

	uint8_t Cartridge::operator[](uint16_t address) const
	{
		return const_cast<Cartridge&>(*this)[address];
	}
}