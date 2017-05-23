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
	// Sprite Attrib Memory(OAM)
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

	#define CARTRIDGE_START 0x0000
	#define VRAM_START 0x8000
	#define SRAM_START 0xA000
	#define WRAM_START 0xC000
	#define WRAM_ECHO_START 0xE000
	#define OAM_START 0xFE00
	#define UNUSABLE0_START 0xFEA0
	#define IO_START 0xFF00
	#define UNUSABLE1_START 0xFF4C
	#define INTERNAL_RAM_START 0xFF80

	#define CARTRIDGE_END VRAM_START
	#define VRAM_END SRAM_START
	#define SRAM_END WRAM_START
	#define WRAM_END WRAM_ECHO_START
	#define WRAM_ECHO_END OAM_START
	#define OAM_END UNUSABLE0_START
	#define UNUSABLE0_END IO_START
	#define IO_END UNUSABLE1_START
	#define UNUSABLE1_END INTERNAL_RAM_START
	#define INTERNAL_RAM_END 0x10000

	#define VRAM_SIZE (VRAM_END - CARTRIDGE_END)
	#define SRAM_SIZE (SRAM_END - VRAM_END)
	#define WRAM_SIZE (WRAM_END - SRAM_END)
	#define WRAM_ECHO_SIZE (WRAM_ECHO_END - WRAM_END)
	#define OAM_SIZE (OAM_END - WRAM_ECHO_END)
	#define UNUSABLE0_SIZE (UNUSABLE0_END - OAM_END)
	#define IO_SIZE (IO_END - UNUSABLE0_END)
	#define UNUSABLE1_SIZE (UNUSABLE1_END - IO_END)
	#define INTERNAL_RAM_SIZE (INTERNAL_RAM_END - UNUSABLE1_END)

	class Memory
	{
	public:
		Memory();

		void Reset();

		uint8_t& operator[](uint16_t address);
		uint8_t operator[](uint16_t address) const;

		uint8_t ReadByte(uint16_t address) const;
		uint16_t ReadWord(uint16_t address) const;
		void WriteByte(uint16_t address, uint8_t value);
		void WriteWord(uint16_t address, uint16_t value);

	private:
		Cartridge mCart;							// 0x0000 - 0x7FFF
		uint8_t mVideoRAM[VRAM_SIZE];				// 0x8000 - 0x9FFF
		uint8_t mSwitchableRAM[SRAM_SIZE];			// 0xA000 - 0xBFFF
		uint8_t mWorkingRAM[WRAM_SIZE];				// 0xC000 - 0xDFFF
		uint8_t mWorkingRAMEcho[WRAM_ECHO_SIZE];	// 0xE000 - 0xFDFF
		uint8_t mOAM[OAM_SIZE];						// 0xFE00 - 0xFE9F
		uint8_t UNUSABLE0[UNUSABLE0_SIZE];			// 0xFEA0 - 0xFEFF
		uint8_t mIO[IO_SIZE];						// 0xFF00 - 0xFF4B
		uint8_t UNUSABLE1[UNUSABLE1_SIZE];			// 0xFF4C - 0xFF7F
		uint8_t mInternalRAM[INTERNAL_RAM_SIZE];	// 0xFF80 - 0xFFFF
	};
}
