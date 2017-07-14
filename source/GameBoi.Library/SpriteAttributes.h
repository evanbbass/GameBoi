#pragma once

#include <cstdint>
#include "Utilities.h"

namespace GameBoi
{
	struct SpriteAttributes
	{
		SpriteAttributes() :
			PositionY(0), PositionX(0), TileNumber(0), Attributes(0)
		{
		}

		uint8_t PositionY;		// Vertical position on the screen, minus 16
		uint8_t PositionX;		// Horizontal position on the screen, minus 8
		uint8_t TileNumber;		// Selects a tile from memory (0x8000-0x8FFF)
		uint8_t Attributes;		// Holds various flags

		bool IsAboveBackground() const { return !Utilities::TestBit(Attributes, 7); }
		bool FlipY() const { return Utilities::TestBit(Attributes, 6); }
		bool FlipX() const { return Utilities::TestBit(Attributes, 5); }
		uint8_t GetPalletNumber() const { return Utilities::TestBit(Attributes, 4) ? 1 : 0; }
		// bits 3-0 are for Color Game Boy only
	};
}
