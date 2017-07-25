#include "pch.h"
#include "Cartridge.h"
#include "CPU.h"
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace GameBoi
{
	const map<int32_t, int32_t> Cartridge::RomSizeMap =
	{
		{ 0x00, 2 },
		{ 0x01, 4 },
		{ 0x02, 8 },
		{ 0x03, 16 },
		{ 0x04, 32 },
		{ 0x05, 64 },
		{ 0x06, 128 },
		{ 0x07, 256 },
		{ 0x08, 512 },
		{ 0x52, 72 },
		{ 0x53, 80 },
		{ 0x54, 96 }
	};

	const map<int32_t, int32_t> Cartridge::RamSizeMap =
	{
		{ 0x00, 0 },
		{ 0x01, 2 },
		{ 0x02, 8 },
		{ 0x03, 32 }, // 4 banks of 8kB
		{ 0x04, 128 }, // 16 banks of 8kB
		{ 0x05, 64 } // 8 banks of 8kB
	};

	Cartridge::Cartridge() :
		mSwitchableRomBankIndex(1), mSwitchableRamBankIndex(0), mRamEnabled(false), mRamModeSelected(false)
	{
		Reset();
	}

	Cartridge::Cartridge(const string& filename) :
		mSwitchableRomBankIndex(1), mSwitchableRamBankIndex(0), mRamEnabled(false), mRamModeSelected(false)
	{
		ReadFromFile(filename);
	}

	void Cartridge::ReadFromFile(const string& filename)
	{
		mFileName = filename;

		//if (mFileName.substr(mFileName.find_last_of("."), mFileName.size()) != ".gb")
		//{
		//	throw exception("Invalid file extension specified");
		//}

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
			// 0x80 is color support, 0xC0 is color only
			mColorSupport = colorSupport == 0x80 || colorSupport == 0xC0;
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
			if (static_cast<size_t>(fileSize) != ROM_BANK_SIZE * numRomBanks)
			{
				throw exception("File size mismatch!");
			}

			// read the rom banks into memory
			rom.seekg(0, ios::beg);
			mRomBanks.resize(numRomBanks);
			for (array<uint8_t, ROM_BANK_SIZE>& bank : mRomBanks)
			{
				rom.read(reinterpret_cast<char*>(bank.data()), ROM_BANK_SIZE);
			}
		}

		// read ram size
		{
			rom.seekg(0x149);
			uint8_t ramSizeKey;
			rom.read(reinterpret_cast<char*>(&ramSizeKey), 1);
			int32_t numRamBanks = RamSizeMap.at(ramSizeKey);

			// read the rom banks into memory
			mRamBanks.resize(numRamBanks);

			string saveFileName = mFileName.substr(0, mFileName.find_last_of(".")) + ".sav";
			ifstream saveFile(saveFileName, ios::in | ios::binary | ios::ate);
			streamoff saveSize = saveFile.tellg();

			if (HasBattery() && saveFile.good())
			{
				// TODO apparently this isn't right but I can't find any sources on how it should work
				// check the file size against the number of rom banks
				if (static_cast<size_t>(saveSize) != RAM_BANK_SIZE * numRamBanks)
				{
					throw exception("Save file size mismatch!");
				}

				saveFile.seekg(ios::beg);
				for (array<uint8_t, RAM_BANK_SIZE>& bank : mRamBanks)
				{
					saveFile.read(reinterpret_cast<char*>(bank.data()), RAM_BANK_SIZE);
				}
			}
			else
			{
				for (array<uint8_t, RAM_BANK_SIZE>& bank : mRamBanks)
				{
					bank.fill(0);
				}
			}
		}
	}

	void Cartridge::WriteSaveFile() const
	{
		string saveFileName = mFileName.substr(0, mFileName.find_last_of(".")) + ".sav";
		ofstream saveFile(saveFileName, ios::out | ios::binary);

		if (HasBattery() && mRamBanks.size() > 0 && saveFile.good())
		{
			for (const array<uint8_t, RAM_BANK_SIZE>& bank : mRamBanks)
			{
				saveFile.write(reinterpret_cast<const char*>(bank.data()), RAM_BANK_SIZE);
			}
		}
	}

	void Cartridge::Reset()
	{
		// default to 2 banks
		mRomBanks.resize(2);
		for (array<uint8_t, ROM_BANK_SIZE>& bank : mRomBanks)
		{
			bank.fill(0);
		}
		mRamBanks.clear();
	}

	uint8_t Cartridge::ReadByte(uint16_t address) const
	{
		if (address < (ROM_BANK_SIZE * 2))
		{
			return ReadByteRom(address);
		}
		else if (address >= MemoryMap::SRAM_START && address < MemoryMap::SRAM_END)
		{
			if (!mRamEnabled || mRamBanks.size() == 0)
			{
				return 0;
			}

			return mRamBanks[mSwitchableRamBankIndex][address - MemoryMap::SRAM_START];
		}
		else
		{
			throw exception("Address out of Cartridge range.");
		}
	}

	void Cartridge::WriteByte(uint16_t address, uint8_t value)
	{
		if (address < (ROM_BANK_SIZE * 2))
		{
			HandleBankSwitching(address, value);
		}
		else if (address >= MemoryMap::SRAM_START && address < MemoryMap::SRAM_END)
		{
			if (!mRamEnabled || mRamBanks.size() == 0)
			{
				return;
			}

			mRamBanks[mSwitchableRamBankIndex][address - MemoryMap::SRAM_START] = value;
		}
		else
		{
			throw exception("Address out of Cartridge range.");
		}
	}

	uint8_t Cartridge::ReadByteRom(uint16_t address) const
	{
		if (address < ROM_BANK_SIZE)
		{
			return mRomBanks[0][address];
		}
		else if (address < (ROM_BANK_SIZE * 2))
		{
			return mRomBanks[mSwitchableRomBankIndex][address - ROM_BANK_SIZE];
		}
		else
		{
			throw exception("Address out of ROM range.");
		}
	}

	uint8_t Cartridge::ReadByteRam(uint16_t address) const
	{
		return mRamBanks[mSwitchableRamBankIndex][address];
	}

	void Cartridge::HandleBankSwitching(uint16_t address, uint8_t value)
	{
		if (address < 0x2000)
		{
			// RAM Enable
			if (!IsMBC2() || !Utilities::TestBit(address, 9))
			{
				mRamEnabled = ((value & 0x0F) == 0x0A);
			}
		}
		else if (address < 0x4000)
		{
			HandleRomBankSwitchingLo(value);
		}
		else if (address < 0x6000)
		{
			if (mRamModeSelected)
			{
				HandleRamBankSwitching(value);
			}
			else
			{
				HandleRomBankSwitchingHi(value);
			}
		}
		else if (address < 0x8000)
		{
			if (IsMBC1())
			{
				mRamModeSelected = value != 0;

				if (mRamModeSelected)
				{
					mSwitchableRomBankIndex &= 0b00011111;
				}
				else
				{
					mSwitchableRamBankIndex = 0;
				}
			}
			else if (IsMBC3())
			{
				
			}
		}
	}

	void Cartridge::HandleRomBankSwitchingLo(uint8_t value)
	{
		if (IsMBC1())
		{
			// ROM Bank Number
			uint8_t bankLowerBits = value & 0b00011111; // lower 5 bits change
			if (bankLowerBits == 0)
			{
				// For MBC1, this has the side effect of blocking 0x20, 0x40, and 0x60 as well
				bankLowerBits = 1;
			}

			uint8_t bankUpperBits = mSwitchableRomBankIndex & 0b11100000; // upper 3 bits stay the same

			mSwitchableRomBankIndex = (bankUpperBits | bankLowerBits);
		}
		else if (IsMBC2())
		{
			mSwitchableRomBankIndex = value & 0x0F;
			if (mSwitchableRomBankIndex == 0)
			{
				mSwitchableRomBankIndex += 1;
			}
		}
		else if (IsMBC3())
		{
			// TODO
		}
	}

	void Cartridge::HandleRomBankSwitchingHi(uint8_t value)
	{
		// Note: This isn't used for MBC2
		if (IsMBC1())
		{
			// ROM Bank Number
			uint8_t bankLowerBits = mSwitchableRomBankIndex & 0b00011111; // lower 5 bits stay the same
			uint8_t bankUpperBits = (value & 0b11) << 5; // upper 3 bits change
			mSwitchableRomBankIndex = bankUpperBits | bankLowerBits;
		}
		else if (IsMBC3())
		{
			// TODO
		}
	}

	void Cartridge::HandleRamBankSwitching(uint8_t value)
	{
		// Note: This isn't used for MBC2
		if (IsMBC1())
		{
			mSwitchableRamBankIndex = value & 0b11;
		}
		else if (IsMBC3())
		{
			// TODO
		}
	}

	const string& Cartridge::GetGameTitle() const
	{
		return mGameTitle;
	}

	Cartridge::CartridgeType Cartridge::GetCartrideType() const
	{
		return mCartType;
	}

	bool Cartridge::GetColorSupport() const
	{
		return mColorSupport;
	}

	bool Cartridge::GetSuperSupport() const
	{
		return mSuperSupport;
	}

	bool Cartridge::IsMBC1() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC1:
			case CartridgeType::ROM_MBC1_RAM:
			case CartridgeType::ROM_MBC1_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::IsMBC2() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC2:
			case CartridgeType::ROM_MBC2_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::IsMBC3() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC3_TIMER_BATTERY:
			case CartridgeType::ROM_MBC3_TIMER_RAM_BATTERY:
			case CartridgeType::ROM_MBC3:
			case CartridgeType::ROM_MBC3_RAM:
			case CartridgeType::ROM_MBC3_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::IsMBC4() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC4:
			case CartridgeType::ROM_MBC4_RAM:
			case CartridgeType::ROM_MBC4_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::IsMBC5() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC5:
			case CartridgeType::ROM_MBC5_RAM:
			case CartridgeType::ROM_MBC5_RAM_BATTERY:
			case CartridgeType::ROM_MBC5_RUMBLE:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::HasRAM() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC1_RAM:
			case CartridgeType::ROM_MBC1_RAM_BATTERY:
			case CartridgeType::ROM_RAM:
			case CartridgeType::ROM_RAM_BATTERY:
			case CartridgeType::ROM_MMM01_RAM:
			case CartridgeType::ROM_MMM01_RAM_BATTERY:
			case CartridgeType::ROM_MBC3_TIMER_RAM_BATTERY:
			case CartridgeType::ROM_MBC3_RAM:
			case CartridgeType::ROM_MBC3_RAM_BATTERY:
			case CartridgeType::ROM_MBC4_RAM:
			case CartridgeType::ROM_MBC4_RAM_BATTERY:
			case CartridgeType::ROM_MBC5_RAM:
			case CartridgeType::ROM_MBC5_RAM_BATTERY:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM_BATTERY:
			case CartridgeType::Hudson_HuC_1:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::HasTimer() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC3_TIMER_BATTERY:
			case CartridgeType::ROM_MBC3_TIMER_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::HasRumble() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC5_RUMBLE:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM_BATTERY:
				return true;
			default:
				return false;
		}
	}

	bool Cartridge::HasBattery() const
	{
		switch (mCartType)
		{
			case CartridgeType::ROM_MBC1_RAM_BATTERY:
			case CartridgeType::ROM_MBC2_BATTERY:
			case CartridgeType::ROM_RAM_BATTERY:
			case CartridgeType::ROM_MMM01_RAM_BATTERY:
			case CartridgeType::ROM_MBC3_TIMER_BATTERY:
			case CartridgeType::ROM_MBC3_TIMER_RAM_BATTERY:
			case CartridgeType::ROM_MBC3_RAM_BATTERY:
			case CartridgeType::ROM_MBC4_RAM_BATTERY:
			case CartridgeType::ROM_MBC5_RAM_BATTERY:
			case CartridgeType::ROM_MBC5_RUMBLE_RAM_BATTERY:
			case CartridgeType::Hudson_HuC_1:
				return true;
			default:
				return false;
		}
	}

	string Cartridge::DisassembleRom(uint16_t startAddress, uint16_t length) const
	{
		stringstream disassembly;
		disassembly << hex << uppercase << setfill('0');

		uint16_t programCounter = startAddress;
		uint16_t endAddress = programCounter + length;

		while (programCounter < endAddress)
		{
			disassembly << "0x" << setw(4) << programCounter << ": ";

			uint8_t opcode = ReadByte(programCounter++);
			int32_t operandLength = -1;
			disassembly << setw(2) << static_cast<int>(opcode) << " ";

			try
			{
				operandLength = CPU::GetOperandLength(opcode);
			}
			catch (...)
			{
				disassembly << "       " << "Undefined opcode";
			}

			if (operandLength == 0)
			{
				string dis = CPU::GetDisassembly(opcode);
				disassembly << "       " << dis;
			}
			else if (operandLength == 1)
			{
				uint8_t operand = ReadByte(programCounter++);
				string dis = CPU::GetDisassembly(opcode, operand);
				disassembly << setw(2) << static_cast<int>(operand) << "     " << dis;
			}
			else if (operandLength == 2)
			{
				uint16_t operand = ReadWord(programCounter);
				programCounter += 2;
				uint8_t operand_l = (operand & 0x00FF);
				uint8_t operand_h = (operand & 0xFF00) >> 8;
				string dis = CPU::GetDisassembly(opcode, operand);
				disassembly << setw(2) << static_cast<int>(operand_l) << " " << setw(2) << static_cast<int>(operand_h) << "  " << dis;
			}

			disassembly << endl;
		}

		return disassembly.str();
	}

	void Cartridge::DisassebleRomToFile(const string& filename, uint16_t startAddress, uint16_t length) const
	{
		ofstream file(filename);

		if (file.good())
		{
			file << DisassembleRom(startAddress, length);
		}
	}
}
