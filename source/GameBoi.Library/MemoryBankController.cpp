#include "pch.h"
#include "MemoryBankController.h"
#include "Utilities.h"

using namespace std;

namespace GameBoi
{
	MemoryBankController::MemoryBankController() :
		mRomBankIndex(0), mRamBankIndex(0), mRamEnabled(false)
	{
	}

	unique_ptr<MemoryBankController> MemoryBankController::CreateMBC(Cartridge::CartridgeType type)
	{
		switch (type)
		{
			case Cartridge::CartridgeType::ROM_MBC1:
			case Cartridge::CartridgeType::ROM_MBC1_RAM:
			case Cartridge::CartridgeType::ROM_MBC1_RAM_BATTERY:
				return make_unique<MBC1>();

			case Cartridge::CartridgeType::ROM_MBC2:
			case Cartridge::CartridgeType::ROM_MBC2_BATTERY:
				return make_unique<MBC2>();

			case Cartridge::CartridgeType::ROM_MBC3_TIMER_BATTERY:
			case Cartridge::CartridgeType::ROM_MBC3_TIMER_RAM_BATTERY:
			case Cartridge::CartridgeType::ROM_MBC3:
			case Cartridge::CartridgeType::ROM_MBC3_RAM:
			case Cartridge::CartridgeType::ROM_MBC3_RAM_BATTERY:
				return make_unique<MBC3>();

			case Cartridge::CartridgeType::ROM_MBC4:
			case Cartridge::CartridgeType::ROM_MBC4_RAM:
			case Cartridge::CartridgeType::ROM_MBC4_RAM_BATTERY:

			case Cartridge::CartridgeType::ROM_MBC5:
			case Cartridge::CartridgeType::ROM_MBC5_RAM:
			case Cartridge::CartridgeType::ROM_MBC5_RAM_BATTERY:
			case Cartridge::CartridgeType::ROM_MBC5_RUMBLE:
			case Cartridge::CartridgeType::ROM_MBC5_RUMBLE_RAM:
			case Cartridge::CartridgeType::ROM_MBC5_RUMBLE_RAM_BATTERY:

			default:
				return nullptr;
		}
	}

	#pragma region MBC1

	MBC1::MBC1() :
		mRamModeSelected(false)
	{
	}

	void MBC1::WriteByte(uint16_t address, uint8_t value)
	{
		if (address < 0x2000)
		{
			EnableRAM(value);
		}
		else if (address < 0x4000)
		{
			SelectROMBankLow(value);
		}
		else if (address < 0x6000)
		{
			if (mRamModeSelected)
			{
				SelectRAMBank(value);
			}
			else
			{
				SelectROMBankHigh(value);
			}
		}
		else if (address < 0x8000)
		{
			SelectMode(value);
		}
	}

	int32_t MBC1::GetROMBankIndex() const
	{
		return mRamModeSelected ? 1 : mRomBankIndex;
	}

	int32_t MBC1::GetRAMBankIndex() const
	{
		return mRamModeSelected ? mRamBankIndex : 0;
	}

	void MBC1::SelectROMBankLow(uint8_t value)
	{
		// ROM Bank Number
		uint8_t bankLowerBits = value & 0b11111; // lower 5 bits change
		if (bankLowerBits == 0)
		{
			// For MBC1, this has the side effect of blocking 0x20, 0x40, and 0x60 as well
			bankLowerBits = 1;
		}

		uint8_t bankUpperBits = mRomBankIndex & 0b11100000; // upper 3 bits stay the same

		mRomBankIndex = (bankUpperBits | bankLowerBits);
	}

	void MBC1::SelectROMBankHigh(uint8_t value)
	{
		// ROM Bank Number
		uint8_t bankLowerBits = mRomBankIndex & 0b11111; // lower 5 bits stay the same
		uint8_t bankUpperBits = (value & 0b11) << 5; // upper 3 bits change
		mRomBankIndex = bankUpperBits | bankLowerBits;
	}

	void MBC1::SelectRAMBank(uint8_t value)
	{
		// 2-bit register
		mRamBankIndex = value & 0b11;
	}

	void MBC1::SelectMode(uint8_t value)
	{
		mRamModeSelected = (value & 0b1) == 0b1;
	}

	#pragma endregion

	#pragma region MBC2

	MBC2::MBC2()
	{
	}

	void MBC2::WriteByte(uint16_t address, uint8_t value)
	{
		if (address < 0x2000)
		{
			if (Utilities::TestBit(address, 9))
			{
				EnableRAM(value);
			}
		}
		else if (address < 0x4000)
		{
			SelectROMBank(value);
		}
		else if (address >= 0xA000 && address < 0xA1FF)
		{
			// MBC2 RAM is 512x4 bits
			mRAM[address - 0xA000] = value & 0b1111;
		}
	}

	uint8_t MBC2::ReadByte(uint16_t address)
	{
		return mRAM[address - 0xA000];
	}

	void MBC2::SelectROMBank(uint8_t value)
	{
		mRomBankIndex = value & 0b1111;

		if (mRomBankIndex == 0)
		{
			mRomBankIndex = 1;
		}
	}

	#pragma endregion

	#pragma region MBC3

	MBC3::MBC3()
	{
	}

	void MBC3::WriteByte(uint16_t address, uint8_t value)
	{
		if (address < 0x2000)
		{
			EnableRAM(value);
		}
		else if (address < 0x4000)
		{
			SelectROMBank(value);
		}
		else if (address < 0x6000)
		{
			
		}
		else if (address < 0x8000)
		{
			
		}
	}

	void MBC3::SelectROMBank(uint8_t value)
	{
		mRomBankIndex = value & 0b1111111;

		if (mRomBankIndex == 0)
		{
			mRomBankIndex++;
		}
	}

	void MBC3::SelectRAMBank(uint8_t value)
	{
		value;
	}

	#pragma endregion
}
