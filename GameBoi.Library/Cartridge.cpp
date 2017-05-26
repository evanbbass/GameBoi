#include "pch.h"
#include "Cartridge.h"
#include <fstream>

using namespace std;

namespace GameBoi
{
	const map<int32_t, int32_t> RomSizeMap =
	{
		{ 0x00, 2 },
		{ 0x01, 4 },
		{ 0x02, 8 },
		{ 0x03, 16 },
		{ 0x04, 32 },
		{ 0x05, 64 },
		{ 0x06, 128 },
		{ 0x52, 72 },
		{ 0x53, 80 },
		{ 0x54, 96 }
	};

	Cartridge::Cartridge() :
	    mSwitchableBankIndex(1)
	{
		Reset();
	}

	Cartridge::Cartridge(const string& filename) :
		mSwitchableBankIndex(1)
	{
		ReadFromFile(filename);
	}

	void Cartridge::ReadFromFile(const string& filename)
	{
		ifstream rom(filename, ios::in | ios::binary | ios::ate);
		if (!rom)
		{
			throw exception("Input file not valid.");
		}
		streamoff fileSize = rom.tellg();

		// read title of game
		{
			rom.seekg(0x134);
			// title goes from byte 0x134 to byte 0x142, inclusive
			const uint8_t gameNameSize = 0x142 - 0x134 + 1;
			char gameName[gameNameSize + 1] { 0 };
			rom.read(gameName, gameNameSize);
			mGameTitle = gameName;
		}

		// read color game boy flag
		{
			rom.seekg(0x143);
			uint8_t colorSupport;
			rom.read(reinterpret_cast<char*>(&colorSupport), 1);
			mColorSupport = colorSupport == 0x80;
		}

		// read super game boy flag
		{
			rom.seekg(0x146);
			uint8_t superSupport;
			rom.read(reinterpret_cast<char*>(&superSupport), 1);
			mSuperSupport = superSupport == 0x03;
		}

		// read cartridge type
		{
			rom.seekg(0x147);
			rom.read(reinterpret_cast<char*>(&mCartType), 1);
		}

		// read rom size and load rom
		{
			// find the number of rom banks
			rom.seekg(0x148);
			uint8_t romSizeKey;
			rom.read(reinterpret_cast<char*>(&romSizeKey), 1);
			int32_t numRomBanks = RomSizeMap.at(romSizeKey);

			// check the file size against the number of rom banks
			if (fileSize != BANK_SIZE * numRomBanks)
			{
				throw exception("File size mismatch!");
			}

			// read the rom banks into memory
			rom.seekg(0, ios::beg);
			mBanks.resize(numRomBanks);
			for (array<uint8_t, BANK_SIZE>& bank : mBanks)
			{
				rom.read(reinterpret_cast<char*>(bank.data()), BANK_SIZE);
			}
		}

		// read ram size
		{
			rom.seekg(0x149);
			uint8_t ramSizeKey;
			rom.read(reinterpret_cast<char*>(&ramSizeKey), 1);
			// don't know what to do with this yet...
			ramSizeKey = ramSizeKey;
		}
	}

	void Cartridge::Reset()
	{
		// default to 2 banks
		mBanks.resize(2);
		for (array<uint8_t, BANK_SIZE>& bank : mBanks)
		{
			bank.fill(0);
		}
	}

	uint8_t& Cartridge::operator[](uint16_t address)
	{
		if (address < BANK_SIZE)
		{
			return mBanks[0][address];
		}
		else if (address < (BANK_SIZE * 2))
		{
			return mBanks[mSwitchableBankIndex][address - BANK_SIZE];
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

	void Cartridge::SetSwitchableBankIndex(uint32_t index)
	{
		if (index < 1 || index > mBanks.size())
		{
			throw exception("Index not valid.");
		}

		mSwitchableBankIndex = index;
	}
}
