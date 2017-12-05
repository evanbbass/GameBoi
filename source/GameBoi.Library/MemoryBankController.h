#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include "Cartridge.h"

namespace GameBoi
{
	class MemoryBankController abstract
	{
	public:
		MemoryBankController();
		virtual ~MemoryBankController() = default;

		static std::unique_ptr<MemoryBankController> CreateMBC(Cartridge::CartridgeType type);

		virtual void WriteByte(uint16_t address, uint8_t value) = 0;

		virtual int32_t GetROMBankIndex() const { return mRomBankIndex; }
		virtual int32_t GetRAMBankIndex() const { return mRomBankIndex; }
		bool RAMIsEnabled() const { return mRamEnabled; }

	protected:
		void EnableRAM(uint8_t value) { mRamEnabled = (value & 0x0F) == 0x0A; }

		int32_t mRomBankIndex;
		int32_t mRamBankIndex;
		bool mRamEnabled;

		const static uint8_t RAMEnabledValue = 0x0A;
	};

	class MBC1 final : public MemoryBankController
	{
	public:
		MBC1();

		void WriteByte(uint16_t address, uint8_t value) override;

		int32_t GetROMBankIndex() const override;
		int32_t GetRAMBankIndex() const override;

	private:
		void SelectROMBankLow(uint8_t value);
		void SelectROMBankHigh(uint8_t value);
		void SelectRAMBank(uint8_t value);
		void SelectMode(uint8_t value);

		bool mRamModeSelected;
	};

	class MBC2 final : public MemoryBankController
	{
	public:
		MBC2();

		void WriteByte(uint16_t address, uint8_t value) override;
		uint8_t ReadByte(uint16_t address);

	private:
		void SelectROMBank(uint8_t value);

		// MBC2 has 512x4 bits of RAM on-chip
		std::array<uint8_t, 0x200> mRAM;
	};

	class MBC3 final : public MemoryBankController
	{
	public:
		MBC3();

		void WriteByte(uint16_t address, uint8_t value) override;

	private:
		void SelectROMBank(uint8_t value);
		void SelectRAMBank(uint8_t value);
	};
}
