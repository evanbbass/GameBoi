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
		uint8_t mROMBank0[0x4000];
		uint8_t mSwitchableROMBank[0x4000];
	};
}