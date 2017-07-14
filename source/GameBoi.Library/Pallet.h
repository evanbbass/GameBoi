#pragma once
#include <cstdint>
#include "Display.h"

namespace GameBoi
{
	class Pallet final
	{
	public:
		Pallet() : mPallet(0)
		{
		}

		uint8_t GetPallet() const { return mPallet; }
		void SetPallet(uint8_t value) { mPallet = value; }

		Display::Color GetPalletColor(uint8_t index) const
		{
			if (index >= 4)
			{
				return Display::Color::White;
			}

			uint8_t mask = 0b11 << (index * 2);
			uint8_t value = (mPallet & mask) >> (index * 2);
			return static_cast<Display::Color>(value);
		}

	private:
		uint8_t mPallet;
	};
}
