#pragma once

#include <cstdint>
#include "Utilities.h"

namespace GameBoi
{
	struct LCDControl
	{
		LCDControl() :
			mRegister(0)
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

		static const uint16_t LCDControlRegisterAddress = 0xFF40;

		bool LCDEnabled() const
		{
			return Utilities::TestBit(mRegister, 7);
		}

		uint16_t GetWindowTileMapDisplayAddress() const
		{
			return Utilities::TestBit(mRegister, 6) ? TileMapDisplay1Start : TileMapDisplay0Start;
		}

		bool WindowEnabled() const
		{
			return Utilities::TestBit(mRegister, 5);
		}

		uint16_t GetWindowTileDataAddress() const
		{
			return Utilities::TestBit(mRegister, 4) ? TileData1Start : TileData0Start;
		}

		bool TileIdentifiersAreUnsigned() const
		{
			return Utilities::TestBit(mRegister, 4);
		}

		uint16_t GetBackgroundTileMapDisplayAddress() const
		{
			return Utilities::TestBit(mRegister, 3) ? TileMapDisplay1Start : TileMapDisplay0Start;
		}

		uint8_t GetSpriteWidth() const
		{
			return 8;
		}

		uint8_t GetSpriteHeight() const
		{
			return Utilities::TestBit(mRegister, 2) ? 16 : 8;
		}

		bool SpriteEnabled() const
		{
			return Utilities::TestBit(mRegister, 1);
		}

		bool BackgroundEnabled() const
		{
			return Utilities::TestBit(mRegister, 0);
		}

	private:
		uint8_t mRegister;

		static const uint16_t TileMapDisplay0Start = 0x9800;
		static const uint16_t TileMapDisplay1Start = 0x9C00;
		static const uint16_t TileMapDisplaySize = 0x0400;
		static const uint16_t TileData0Start = 0x8800;
		static const uint16_t TileData1Start = 0x8000;
		static const uint16_t TileDataSize = 0x1000;
	};
}
