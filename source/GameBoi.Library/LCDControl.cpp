#include "pch.h"
#include "LCDControl.h"

namespace
{
	constexpr uint16_t TileMapDisplay0Start = 0x9800;
	constexpr uint16_t TileMapDisplay1Start = 0x9C00;
	constexpr uint16_t TileMapDisplaySize = 0x0400;
	constexpr uint16_t TileData0Start = 0x8800;
	constexpr uint16_t TileData1Start = 0x8000;
	constexpr uint16_t TileDataSize = 0x1000;
}

namespace GameBoi
{
	bool LCDControl::LCDEnabled() const
	{
		return Utilities::TestBit(mRegister, 7);
	}

	bool LCDControl::WindowEnabled() const
	{
		return Utilities::TestBit(mRegister, 5);
	}

	bool LCDControl::SpriteEnabled() const
	{
		return Utilities::TestBit(mRegister, 1);
	}

	bool LCDControl::BackgroundEnabled() const
	{
		return Utilities::TestBit(mRegister, 0);
	}

	bool LCDControl::TileIdentifiersAreUnsigned() const
	{
		return Utilities::TestBit(mRegister, 4);
	}

	uint8_t LCDControl::GetSpriteWidth() const
	{
		return 8;
	}

	uint8_t LCDControl::GetSpriteHeight() const
	{
		return Utilities::TestBit(mRegister, 2) ? 16 : 8;
	}

	uint16_t LCDControl::GetWindowTileMapDisplayAddress() const
	{
		return Utilities::TestBit(mRegister, 6) ? TileMapDisplay1Start : TileMapDisplay0Start;
	}

	uint16_t LCDControl::GetWindowTileDataAddress() const
	{
		return Utilities::TestBit(mRegister, 4) ? TileData1Start : TileData0Start;
	}

	uint16_t LCDControl::GetBackgroundTileMapDisplayAddress() const
	{
		return Utilities::TestBit(mRegister, 3) ? TileMapDisplay1Start : TileMapDisplay0Start;
	}
}
