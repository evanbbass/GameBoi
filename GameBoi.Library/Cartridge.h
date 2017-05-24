#pragma once

namespace GameBoi
{
	class Cartridge
	{
	public:
		Cartridge();

		void Reset();

		uint8_t& operator[](uint16_t address);
		uint8_t operator[](uint16_t address) const;

	private:
		// Cartridge has 32k of address space and can have multiple 16kB ROM banks
		// Bank 0 is always loaded in the lower 16k
		uint8_t mROMBank0[0x4000];
		// Other banks can be swapped in to the upper 16k
		uint8_t mSwitchableROMBank[0x4000];
	};
}