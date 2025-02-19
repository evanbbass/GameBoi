#pragma once
#include "Cartridge.h"
#include "IAddressable.h"
#include "IO.h"
#include "SpriteAttributes.h"
#include "ObjectAttributeMemory.h"

namespace GameBoi
{
	// Interrupt Enable Register
	// -------------------------- - FFFF
	// Internal (High) RAM
	// -------------------------- - FF80
	// I/O ports
	// -------------------------- - FF00
	// Empty but unusable for I/O
	// -------------------------- - FEA0
	// Sprite Attribute Memory (OAM)
	// -------------------------- - FE00
	// Echo of 8kB Internal RAM
	// -------------------------- - E000
	// 8kB Internal (Working) RAM
	// -------------------------- - C000 --
	// 8kB Switchable RAM bank            |= on Cartridge, if any
	// -------------------------- - A000 --
	// 8kB Video RAM
	// -------------------------- - 8000 --
	// 16kB Switchable ROM bank           |
	// -------------------------- - 4000  |= 32kB Cartridge
	// 16kB ROM bank #0                   |
	// -------------------------- - 0000 --

	class MemoryMap final : public IAddressable
	{
		friend class CPU;

	public:
		MemoryMap();

		void Reset();

		uint8_t ReadByte(uint16_t address) const override;
		void WriteByte(uint16_t address, uint8_t value) override;

		void LoadCartridgeFromFile(const std::string& fileName);
		Cartridge& GetCartridge();
		const Cartridge& GetCartridge() const;
		ObjectAttributeMemory& GetOAM();
		const ObjectAttributeMemory& GetOAM() const;
		IO& GetIO();
		const IO& GetIO() const;

		uint8_t GetInterruptEnabledRegister() const;
		uint8_t GetInterruptFlagRegister() const;
		void SetVBlankInterruptFlag();
		void SetLCDInterruptFlag();
		void SetTimerInterruptFlag();
		void SetKeypadInterruptFlag();

		/// <summary>
		/// Handles Direct Memory Access, which copies data from <paramref name="value" /> << 8
		/// to the Sprite (Object) Attribute Memory (OAM).
		/// 
		/// e.g. If 0x56 is passed in, memory from 0x5600 through 0x569F will be copied to
		/// 0xFE00 through 0xFE9F.
		/// </summary>
		void DMATransfer(uint8_t value);

		static constexpr uint16_t InterruptEnabledAddress	= 0xFFFF;
		static constexpr uint16_t InterruptFlagAddress		= 0xFF0F;
		static constexpr uint8_t  VBlankInterruptBit		= 0;
		static constexpr uint8_t  LCDInterruptBit			= 1;
		static constexpr uint8_t  TimerInterruptBit			= 2;
		static constexpr uint8_t  KeypadInterruptBit		= 4;
		static constexpr uint16_t VBlankISRAddress			= 0x0040;
		static constexpr uint16_t LCDISRAddress				= 0x0048;
		static constexpr uint16_t TimerISRAddress			= 0x0050;
		static constexpr uint16_t KeypadISRAddress			= 0x0060;

		static constexpr uint16_t BIOS_START				= 0x0000;
		static constexpr uint16_t CARTRIDGE_START			= 0x0000;
		static constexpr uint16_t VRAM_START				= 0x8000;
		static constexpr uint16_t SRAM_START				= 0xA000;
		static constexpr uint16_t WRAM_START				= 0xC000;
		static constexpr uint16_t WRAM_ECHO_START			= 0xE000;
		static constexpr uint16_t OAM_START					= 0xFE00;
		static constexpr uint16_t UNUSABLE_START			= 0xFEA0;
		static constexpr uint16_t IO_START					= 0xFF00;
		static constexpr uint16_t INTERNAL_RAM_START		= 0xFF80;
		static constexpr uint16_t INTERRUPT_ENABLE_START	= 0xFFFF;

		static constexpr uint16_t BIOS_END					= 0x0100;
		static constexpr uint16_t CARTRIDGE_END				= VRAM_START;
		static constexpr uint16_t VRAM_END					= SRAM_START;
		static constexpr uint16_t SRAM_END					= WRAM_START;
		static constexpr uint16_t WRAM_END					= WRAM_ECHO_START;
		static constexpr uint16_t WRAM_ECHO_END				= OAM_START;
		static constexpr uint16_t OAM_END					= UNUSABLE_START;
		static constexpr uint16_t UNUSABLE_END				= IO_START;
		static constexpr uint16_t IO_END					= INTERNAL_RAM_START;
		static constexpr uint16_t INTERNAL_RAM_END			= INTERRUPT_ENABLE_START;

		static constexpr uint16_t BIOS_SIZE					= BIOS_END - BIOS_START;
		static constexpr uint16_t CARTRIDGE_SIZE			= CARTRIDGE_END - CARTRIDGE_START;
		static constexpr uint16_t VRAM_SIZE					= VRAM_END - VRAM_START;
		static constexpr uint16_t SRAM_SIZE					= SRAM_END - SRAM_START;
		static constexpr uint16_t WRAM_SIZE					= WRAM_END - WRAM_START;
		static constexpr uint16_t WRAM_ECHO_SIZE			= WRAM_ECHO_END - WRAM_ECHO_START;
		static constexpr uint16_t OAM_SIZE					= OAM_END - OAM_START;
		static constexpr uint16_t UNUSABLE_SIZE				= UNUSABLE_END - UNUSABLE_START;
		static constexpr uint16_t IO_SIZE					= IO_END - IO_START;
		static constexpr uint16_t INTERNAL_RAM_SIZE			= INTERNAL_RAM_END - INTERNAL_RAM_START;

	private:
		bool mIsInBIOS;											// 0x0000 - 0x0100 if in BIOS

		void ResetVBlankInterruptFlag();
		void ResetLCDInterruptFlag();
		void ResetTimerInterruptFlag();
		void ResetKeypadInterruptFlag();

		Cartridge mCart;										// 0x0000 - 0x7FFF
		std::array<uint8_t, VRAM_SIZE> mVideoRAM;				// 0x8000 - 0x9FFF
																// 0xA000 - 0xBFFF (Located on cartridge)
		std::array<uint8_t, WRAM_SIZE> mWorkingRAM;				// 0xC000 - 0xDFFF
																// 0xE000 - 0xFDFF (Echos WRAM, so no need to include again)
		ObjectAttributeMemory mOAM;								// 0xFE00 - 0xFE9F
																// 0xFEA0 - 0xFEFF (Unusable addresses)
		IO mIO;													// 0xFF00 - 0xFF7F
		std::array<uint8_t, INTERNAL_RAM_SIZE> mInternalRAM;	// 0xFF80 - 0xFFFE
		uint8_t mInterruptEnableRegister;						// 0xFFFF
	};
}
