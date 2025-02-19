#pragma once

#include <cstdint>
#include "Utilities.h"

namespace GameBoi
{
	struct LCDControl
	{
		LCDControl() :
			mRegister(0x91)
		{
		}

		uint8_t GetRegister() const
		{
			return mRegister;
		}

		void SetRegister(uint8_t value)
		{
			mRegister = value;
		}

		static constexpr uint16_t LCDControlRegisterAddress = 0xFF40;

		bool LCDEnabled() const;
		bool WindowEnabled() const;
		bool SpriteEnabled() const;
		bool BackgroundEnabled() const;

		bool TileIdentifiersAreUnsigned() const;

		uint8_t GetSpriteWidth() const;
		uint8_t GetSpriteHeight() const;

		uint16_t GetWindowTileMapDisplayAddress() const;
		uint16_t GetWindowTileDataAddress() const;
		uint16_t GetBackgroundTileMapDisplayAddress() const;

	private:
		uint8_t mRegister;
	};
}
