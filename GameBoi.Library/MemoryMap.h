#pragma once
#include "Cartridge.h"

namespace GameBoi
{
	// Interrupt Enable Register
	// -------------------------- - FFFF
	// Internal RAM
	// -------------------------- - FF80
	// Empty but unusable for I / O
	// -------------------------- - FF4C
	// I / O ports
	// -------------------------- - FF00
	// Empty but unusable for I / O
	// -------------------------- - FEA0
	// Sprite Attrib MemoryMap(OAM)
	// -------------------------- - FE00
	// Echo of 8kB Internal RAM
	// -------------------------- - E000
	// 8kB Internal RAM
	// -------------------------- - C000
	// 8kB switchable RAM bank
	// -------------------------- - A000
	// 8kB Video RAM
	// -------------------------- - 8000 --
	// 16kB switchable ROM bank           |
	// -------------------------- - 4000  |= 32kB Cartridge
	// 16kB ROM bank #0                   |
	// -------------------------- - 0000 --

	class MemoryMap
	{
	private:
		const static uint16_t CARTRIDGE_START = 0x0000;
		const static uint16_t VRAM_START = 0x8000;
		const static uint16_t SRAM_START = 0xA000;
		const static uint16_t WRAM_START = 0xC000;
		const static uint16_t WRAM_ECHO_START = 0xE000;
		const static uint16_t OAM_START = 0xFE00;
		const static uint16_t UNUSABLE0_START = 0xFEA0;
		const static uint16_t IO_START = 0xFF00;
		const static uint16_t UNUSABLE1_START = 0xFF4C;
		const static uint16_t INTERNAL_RAM_START = 0xFF80;

		const static uint16_t CARTRIDGE_END = VRAM_START;
		const static uint16_t VRAM_END = SRAM_START;
		const static uint16_t SRAM_END = WRAM_START;
		const static uint16_t WRAM_END = WRAM_ECHO_START;
		const static uint16_t WRAM_ECHO_END = OAM_START;
		const static uint16_t OAM_END = UNUSABLE0_START;
		const static uint16_t UNUSABLE0_END = IO_START;
		const static uint16_t IO_END = UNUSABLE1_START;
		const static uint16_t UNUSABLE1_END = INTERNAL_RAM_START;
		const static uint32_t INTERNAL_RAM_END = 0x10000; // end of addressable space

		const static uint16_t BIOS_SIZE = 0x100;
		const static uint16_t CARTRIDGE_SIZE = CARTRIDGE_END - CARTRIDGE_START;
		const static uint16_t VRAM_SIZE = VRAM_END - VRAM_START;
		const static uint16_t SRAM_SIZE = SRAM_END - SRAM_START;
		const static uint16_t WRAM_SIZE = WRAM_END - WRAM_START;
		const static uint16_t WRAM_ECHO_SIZE = WRAM_ECHO_END - WRAM_ECHO_START;
		const static uint16_t OAM_SIZE = OAM_END - OAM_START;
		const static uint16_t UNUSABLE0_SIZE = UNUSABLE0_END - UNUSABLE0_START;
		const static uint16_t IO_SIZE = IO_END - IO_START;
		const static uint16_t UNUSABLE1_SIZE = UNUSABLE1_END - UNUSABLE1_START;
		const static uint16_t INTERNAL_RAM_SIZE = INTERNAL_RAM_END - INTERNAL_RAM_START;

	public:
		MemoryMap();

		void Reset();

		uint8_t ReadByte(uint16_t address) const;
		uint16_t ReadWord(uint16_t address) const;
		void WriteByte(uint16_t address, uint8_t value);
		void WriteWord(uint16_t address, uint16_t value);

		void LoadCartridgeFromFile(const std::string& fileName);
		Cartridge& GetCartridge();
		const Cartridge& GetCartridge() const;

	private:
		bool mIsInBIOS;
		const static std::array<uint8_t, BIOS_SIZE> sBIOS;		// 0x0000 - 0x0100 if in BIOS

		Cartridge mCart;										// 0x0000 - 0x7FFF
		std::array<uint8_t, VRAM_SIZE> mVideoRAM;				// 0x8000 - 0x9FFF
		std::array<uint8_t, SRAM_SIZE> mSwitchableRAM;			// 0xA000 - 0xBFFF
		std::array<uint8_t, WRAM_SIZE> mWorkingRAM;				// 0xC000 - 0xDFFF
		//std::array<uint8_t, WRAM_ECHO_SIZE> mWorkingRAMEcho;	// 0xE000 - 0xFDFF
		std::array<uint8_t, OAM_SIZE> mOAM;						// 0xFE00 - 0xFE9F
		//std::array<uint8_t, UNUSABLE0_SIZE> UNUSABLE0;		// 0xFEA0 - 0xFEFF
		std::array<uint8_t, IO_SIZE> mIO;						// 0xFF00 - 0xFF4B
		//std::array<uint8_t, UNUSABLE1_SIZE> UNUSABLE1;		// 0xFF4C - 0xFF7F
		std::array<uint8_t, INTERNAL_RAM_SIZE> mInternalRAM;	// 0xFF80 - 0xFFFF
	};
}
