#include "pch.h"
#include "GPU.h"
#include "MemoryMap.h"
#include "Utilities.h"

using namespace std;

// TODO I go lazy and stopped getting rid of magic numbers, probably should fix that

namespace GameBoi
{
	GPU::GPU(MemoryMap& memory) :
		mMemory(memory), mScanlineCounter(0), mCurrentScanline(0), mLCDStatusRegister(0), mLCDControlRegister(0), mCoincidenceRegister(0),
		mScrollY(0), mScrollX(0), mWindowY(0), mWindowX(0)
	{
	}

	void GPU::StepGPU(int32_t cpuCycles)
	{
		if (!LCDEnabled())
		{
			// while the LCD is disabled, reset the scanline and set the mode to VBlank
			mScanlineCounter = 0;
			mCurrentScanline = 0;
			SetLCDStatus(LCDStatus::VBlank);
		}
		else
		{
			mScanlineCounter += cpuCycles;

			if (mScanlineCounter >= CPUCyclesPerScanline)
			{
				// reset the counter
				mScanlineCounter -= CPUCyclesPerScanline;

				HandleHBlank();
			}

			UpdateLCDStatus();
			CheckCoincidence();
		}
	}

	Display& GPU::GetDisplay()
	{
		return mDisplay;
	}

	const Display& GPU::GetDisplay() const
	{
		return mDisplay;
	}

	uint8_t GPU::GetCurrentScanline() const
	{
		return mCurrentScanline;
	}

	uint8_t GPU::GetLCDStatusRegister() const
	{
		return mLCDStatusRegister;
	}

	uint8_t GPU::GetLCDControlRegister() const
	{
		return mLCDControlRegister;
	}

	uint8_t GPU::GetCoincidenceRegister() const
	{
		return mCoincidenceRegister;
	}

	uint8_t GPU::GetScrollY() const
	{
		return mScrollY;
	}

	uint8_t GPU::GetScrollX() const
	{
		return mScrollX;
	}

	uint8_t GPU::GetWindowY() const
	{
		return mWindowY;
	}

	uint8_t GPU::GetWindowX() const
	{
		return mWindowX;
	}

	uint8_t GPU::GetBackgroundPallet() const
	{
		return mBackgroundPallet.GetPallet();
	}

	uint8_t GPU::GetSpritePallet0() const
	{
		return mSpritePallet0.GetPallet();
	}

	uint8_t GPU::GetSpritePallet1() const
	{
		return mSpritePallet1.GetPallet();
	}

	void GPU::SetScrollY(uint8_t value)
	{
		mScrollY = value;
	}

	void GPU::SetScrollX(uint8_t value)
	{
		mScrollX = value;
	}

	void GPU::SetWindowY(uint8_t value)
	{
		mWindowY = value;
	}

	void GPU::SetWindowX(uint8_t value)
	{
		mWindowX = value;
	}

	void GPU::SetCurrentScanline(uint8_t value)
	{
		mCurrentScanline = value;
	}

	void GPU::SetLCDStatusRegister(uint8_t value)
	{
		mLCDStatusRegister = value;
	}

	void GPU::SetLCDControlRegister(uint8_t value)
	{
		mLCDControlRegister = value;
	}

	void GPU::SetCoincidenceRegister(uint8_t value)
	{
		mCoincidenceRegister = value;
	}

	void GPU::SetBackgroundPallet(uint8_t value)
	{
		mBackgroundPallet.SetPallet(value);
	}

	void GPU::SetSpritePallet0(uint8_t value)
	{
		mSpritePallet0.SetPallet(value);
	}

	void GPU::SetSpritePallet1(uint8_t value)
	{
		mSpritePallet1.SetPallet(value);
	}

	GPU::LCDStatus GPU::GetLCDStatus() const
	{
		return static_cast<LCDStatus>(mLCDStatusRegister & 0b11);
	}

	bool GPU::LCDEnabled() const
	{
		return Utilities::TestBit(mLCDControlRegister, 7);
	}

	uint16_t GPU::GetWindowTileMapDisplayAddress() const
	{
		return Utilities::TestBit(mLCDControlRegister, 6) ? TileMapDisplay1Start : TileMapDisplay0Start;
	}

	bool GPU::WindowEnabled() const
	{
		return Utilities::TestBit(mLCDControlRegister, 5);
	}

	uint16_t GPU::GetWindowTileDataAddress() const
	{
		return Utilities::TestBit(mLCDControlRegister, 4) ? TileData1Start : TileData0Start;
	}

	bool GPU::TileIdentifiersAreUnsigned() const
	{
		return !Utilities::TestBit(mLCDControlRegister, 4);
	}

	uint16_t GPU::GetBackgroundTileMapDisplayAddress() const
	{
		return Utilities::TestBit(mLCDControlRegister, 3) ? TileMapDisplay1Start : TileMapDisplay0Start;
	}

	uint8_t GPU::GetSpriteWidth() const
	{
		return 8;
	}

	uint8_t GPU::GetSpriteHeight() const
	{
		return Utilities::TestBit(mLCDControlRegister, 2) ? 16 : 8;
	}

	bool GPU::SpriteEnabled() const
	{
		return Utilities::TestBit(mLCDControlRegister, 1);
	}

	bool GPU::BackgroundEnabled() const
	{
		return Utilities::TestBit(mLCDControlRegister, 0);
	}

	void GPU::DrawScanLine()
	{
		if (BackgroundEnabled())
		{
			RenderTiles();
		}

		if (SpriteEnabled())
		{
			RenderSprites();
		}

		if (!BackgroundEnabled() && !SpriteEnabled())
		{
			DrawDebug();
		}
	}

	void GPU::RenderTiles()
	{
		// TODO clean this up
		// The Game Boy has 32x32 tiles which are each 8x8 pixels, for a total of 256x256 pixels.
		// The LCD display is 160x144, with 153 total scanlines (9 invisible scanlines).

		// grab all the window information. Subtract 7 from window x because reasons
		uint8_t scrollX = mScrollX, scrollY = mScrollY;
		uint8_t windowX = mWindowX - 7, windowY = mWindowY;

		// get addresses for tile info
		bool drawingWindowTiles = WindowEnabled() && windowY <= mCurrentScanline;
		uint16_t tileDataAddress = GetWindowTileDataAddress();
		uint16_t tileMapAddress = drawingWindowTiles ? GetWindowTileMapDisplayAddress() : GetBackgroundTileMapDisplayAddress();

		// yPos is the y index of the current tile being drawn (out of 32)
		uint8_t yPos = drawingWindowTiles ? scrollY + mCurrentScanline : mCurrentScanline - windowY;
		// tileRow is the y index of the pixel within the tile beign drawn (out of 8)
		uint16_t tileRow = (yPos / 8) * 32;

		// go across each visible pixel in the row
		for (uint8_t pixelColumn = 0; pixelColumn < ScreenWidth; ++pixelColumn)
		{
			// x index of current tile
			uint8_t xPos = drawingWindowTiles && pixelColumn >= windowX ? pixelColumn - windowX : pixelColumn + scrollX;
			// x index of pixel within tile
			uint16_t tileCol = xPos / 8;

			uint16_t tileAddress = tileMapAddress + tileRow + tileCol;
			uint8_t tileNum = mMemory.ReadByte(tileAddress);

			uint16_t tileLocation = tileDataAddress;

			if (TileIdentifiersAreUnsigned())
			{
				// offset by the index of the tile (tileNum) times the size of a tile in memory (16 bytes)
				tileLocation += tileNum * 16;
			}
			else
			{
				tileLocation += (reinterpret_cast<int8_t&>(tileNum) + 128) * 16;
			}

			uint8_t line = (yPos % 8) * 2;
			uint8_t data1 = mMemory.ReadByte(tileLocation + line);
			uint8_t data2 = mMemory.ReadByte(tileLocation + line + 1);
			uint8_t colorBit = 7 - (xPos % 8);

			uint8_t colorVal = (Utilities::GetBit(data2, colorBit) << 1) | (Utilities::GetBit(data1, colorBit));
			Display::Color color = mBackgroundPallet.GetPalletColor(colorVal);
			mDisplay.SetPixel(mCurrentScanline, pixelColumn, color);
		}
	}

	void GPU::RenderSprites()
	{
		// TODO clean this up
		const ObjectAttributeMemory& oam = mMemory.GetOAM();

		// loop through the 40 sprites in OAM
		for (uint8_t spriteIndex = 0; spriteIndex < 40; ++spriteIndex)
		{
			const SpriteAttributes& attributes = oam[spriteIndex];
			uint8_t yPos = attributes.PositionY - 16;
			uint8_t xPos = attributes.PositionX - 8;
			uint8_t ySize = GetSpriteHeight();
			//uint8_t xSize = GetSpriteWidth();

			// check if the scanline covers the sprite
			if (mCurrentScanline < yPos || mCurrentScanline >= yPos + ySize)
			{
				continue;
			}

			uint8_t line = mCurrentScanline - yPos;

			if (attributes.FlipY())
			{
				line = ySize - line;
			}

			line *= 2;

			uint16_t dataAddress = 0x8000 + (attributes.TileNumber * 16) + line;
			uint8_t data1 = mMemory.ReadByte(dataAddress);
			uint8_t data2 = mMemory.ReadByte(dataAddress + 1);

			// read from right to left since pixel 0 is bit 7
			for (uint8_t tilePixel = 0; tilePixel < 8; ++tilePixel)
			{
				uint8_t colorBit = attributes.FlipX() ? 7 - tilePixel : tilePixel;
				uint8_t colorNum = (Utilities::GetBit(data2, colorBit) << 1) | Utilities::GetBit(data1, colorBit);

				Display::Color color = attributes.GetPalletNumber() == 0 ?
										   mSpritePallet0.GetPalletColor(colorNum) :
										   mSpritePallet1.GetPalletColor(colorNum);

				uint8_t xPix = 7 - tilePixel;
				uint8_t pixel = xPos + xPix;

				if (color != Display::Color::White)
				{
					mDisplay.SetPixel(mCurrentScanline, pixel, color);
				}
			}
		}
	}

	void GPU::DrawDebug()
	{
		for (uint8_t x = 0; x < ScreenWidth; ++x)
		{
			mDisplay.SetPixel(mCurrentScanline, x, static_cast<Display::Color>((x >> 2) % 4));
		}
	}

	void GPU::HandleHBlank()
	{
		// increment the current scanline
		mCurrentScanline++;

		if (mCurrentScanline == ScreenHeight)
		{
			// scanlines 144 through 153 are the VBlank period
			mMemory.SetVBlankInterruptFlag();
		}
		else if (mCurrentScanline > MaxScanlines)
		{
			// if scanline is over 153, reset it
			mCurrentScanline = 0;
		}

		// between 0 and 143, draw the scanline
		if (mCurrentScanline < ScreenHeight)
		{
			DrawScanLine();
		}
	}

	void GPU::UpdateLCDStatus()
	{
		LCDStatus lastStatus = GetLCDStatus();
		bool requestInterrupt = false;
		if (GetCurrentScanline() >= 144)
		{
			SetLCDStatus(LCDStatus::VBlank);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), VBlankInterruptBit);
		}
		else if (mScanlineCounter < OAMStatusCutoff)
		{
			SetLCDStatus(LCDStatus::OAM);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), OAMInterruptBit);
		}
		else if (mScanlineCounter < VRAMStatusCutoff)
		{
			SetLCDStatus(LCDStatus::VRAM);
		}
		else
		{
			SetLCDStatus(LCDStatus::HBlank);
			requestInterrupt = Utilities::TestBit(GetLCDStatusRegister(), HBlankInterruptBit);
		}

		// Handle interrupts if it was requested and the state changed
		if (requestInterrupt && lastStatus != GetLCDStatus())
		{
			mMemory.SetLCDInterruptFlag();
		}
	}

	void GPU::CheckCoincidence()
	{
		if (GetCurrentScanline() == GetCoincidenceRegister())
		{
			uint8_t newStatus = Utilities::SetBit(GetLCDStatusRegister(), CoincidenceBit);
			mLCDStatusRegister = newStatus;

			if (Utilities::TestBit(GetLCDStatusRegister(), CoincidenceInterruptBit))
			{
				mMemory.SetLCDInterruptFlag();
			}
		}
		else
		{
			uint8_t newStatus = Utilities::ResetBit(GetLCDStatusRegister(), CoincidenceBit);
			mLCDStatusRegister = newStatus;
		}
	}

	void GPU::SetLCDStatus(LCDStatus status)
	{
		uint8_t statusReg = (GetLCDStatusRegister() & 0b11111100) | static_cast<uint8_t>(status);
		mLCDStatusRegister = statusReg;
	}
}
