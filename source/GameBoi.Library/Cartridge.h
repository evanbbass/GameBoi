#pragma once
#include <array>
#include <map>
#include <vector>
#include "IAddressable.h"

namespace GameBoi
{
	class Cartridge final : public IAddressable
	{
	public:
		static const size_t ROM_BANK_SIZE = 0x4000;
		static const size_t RAM_BANK_SIZE = 0x2000;

		enum class CartridgeType : uint8_t
		{
			ROM_ONLY = 0x00,
			ROM_MBC1 = 0x01,
			ROM_MBC1_RAM = 0x02,
			ROM_MBC1_RAM_BATTERY = 0x03,
			ROM_MBC2 = 0x05,
			ROM_MBC2_BATTERY = 0x06,
			ROM_RAM = 0x08,
			ROM_RAM_BATTERY = 0x09,
			ROM_MMM01 = 0x0B,
			ROM_MMM01_RAM = 0x0C,
			ROM_MMM01_RAM_BATTERY = 0x0D,
			ROM_MBC3_TIMER_BATTERY = 0x0F,
			ROM_MBC3_TIMER_RAM_BATTERY = 0x10,
			ROM_MBC3 = 0x11,
			ROM_MBC3_RAM = 0x12,
			ROM_MBC3_RAM_BATTERY = 0x13,
			ROM_MBC4 = 0x15,
			ROM_MBC4_RAM = 0x16,
			ROM_MBC4_RAM_BATTERY = 0x17,
			ROM_MBC5 = 0x19,
			ROM_MBC5_RAM = 0x1A,
			ROM_MBC5_RAM_BATTERY = 0x1B,
			ROM_MBC5_RUMBLE = 0x1C,
			ROM_MBC5_RUMBLE_RAM = 0x1D,
			ROM_MBC5_RUMBLE_RAM_BATTERY = 0x1E,
			Bandai_TAMA5 = 0xFD,
			Pocket_Camera = 0x1F,
			Hudson_HuC_3 = 0xFE,
			Hudson_HuC_1 = 0xFF
		};

	public:
		Cartridge();
		explicit Cartridge(const std::string& filename);

		void ReadFromFile(const std::string& filename);
		void WriteSaveFile() const;
		void Reset();

		uint8_t ReadByte(uint16_t address) const override;
		void WriteByte(uint16_t address, uint8_t value) override;

		const std::string& GetGameTitle() const;
		CartridgeType GetCartrideType() const;
		bool GetColorSupport() const;
		bool GetSuperSupport() const;

		bool IsMBC1() const;
		bool IsMBC2() const;
		bool IsMBC3() const;
		bool IsMBC4() const;
		bool IsMBC5() const;
		bool HasRAM() const;
		bool HasBattery() const;
		bool HasTimer() const;
		bool HasRumble() const;

		std::string DisassembleRom(uint16_t startAddress, uint16_t length) const;
		void DisassebleRomToFile(const std::string& filename, uint16_t startAddress, uint16_t length) const;

	private:
		uint8_t ReadByteRom(uint16_t address) const;
		uint8_t ReadByteRam(uint16_t address) const;
		void HandleBankSwitching(uint16_t address, uint8_t value);
		void HandleRomBankSwitchingLo(uint8_t value);
		void HandleRomBankSwitchingHi(uint8_t value);
		void HandleRamBankSwitching(uint8_t value);

		std::string mFileName;

		// Cartridge ROM has 32k of address space and can have multiple 16kB ROM banks
		std::vector<std::array<uint8_t, ROM_BANK_SIZE>> mRomBanks;
		uint8_t mSwitchableRomBankIndex;
		// Cartridge may also have multiple 8kB RAM banks
		std::vector<std::array<uint8_t, RAM_BANK_SIZE>> mRamBanks;
		uint8_t mSwitchableRamBankIndex;
		bool mRamEnabled;
		bool mRamModeSelected;
		bool mRtcModeSelected;

		std::string mGameTitle;
		CartridgeType mCartType;
		bool mColorSupport;
		bool mSuperSupport;

		static const std::map<int32_t, int32_t> RomSizeMap;
		static const std::map<int32_t, int32_t> RamSizeMap;
	};
}
