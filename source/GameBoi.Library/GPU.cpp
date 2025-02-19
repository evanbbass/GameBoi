#include "pch.h"
#include "GPU.h"
#include "MemoryMap.h"
#include "Utilities.h"

// TODO I go lazy and stopped getting rid of magic numbers, probably should fix that
namespace
{
	constexpr uint8_t CoincidenceBit = 2;
	constexpr uint8_t HBlankInterruptBit = 3;
	constexpr uint8_t VBlankInterruptBit = 4;
	constexpr uint8_t OAMInterruptBit = 5;
	constexpr uint8_t CoincidenceInterruptBit = 6;

	constexpr int32_t CPUCyclesPerScanline = 456;
	constexpr int32_t OAMStatusCutoff = 80;
	constexpr int32_t VRAMStatusCutoff = OAMStatusCutoff + 172;

    constexpr int32_t InvisibleScanlines = 8;
	constexpr int32_t MaxScanlines = GameBoi::GPU::ScreenHeight + InvisibleScanlines; // 144 visible scanlines and 8 invisible ones
}


namespace GameBoi
{
	GPU::GPU(MemoryMap& memory) :
		mMemory(memory), mDisplay(), mScanlineCounter(0), mCurrentScanline(0), mLCDStatusRegister(0), mCoincidenceRegister(0),
		mScrollY(0), mScrollX(0), mWindowY(0), mWindowX(0)
	{
		mBackgroundPallet.SetPallet(0xFC);
		mSpritePallet0.SetPallet(0xFF);
		mSpritePallet1.SetPallet(0xFF);
	}

	void GPU::StepGPU(int32_t cpuCycles)
	{
		if (!mLCDControl.LCDEnabled())
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

	void GPU::DrawScanLine()
	{
		if (mLCDControl.BackgroundEnabled())
		{
			RenderTiles();
		}

		if (mLCDControl.SpriteEnabled())
		{
			RenderSprites();
		}
	}

	void GPU::RenderTiles()
	{
		uint8_t scrollY = mScrollY;
		uint8_t scrollX = mScrollX;
		uint8_t windowY = mWindowY;
		uint8_t windowX = mWindowX - 7;

		bool isWindowRow = mLCDControl.WindowEnabled() && windowY <= mCurrentScanline;

		// which tile data are we using?
		uint16_t tileData = mLCDControl.GetWindowTileDataAddress();

		uint16_t backgroundMemory = isWindowRow ?
			mLCDControl.GetWindowTileMapDisplayAddress() :
			mLCDControl.GetBackgroundTileMapDisplayAddress();

		uint8_t yPos = isWindowRow ? mCurrentScanline - windowY : scrollY + mCurrentScanline;

		uint16_t tileRow = (yPos >> 3) << 5;

		// for each column in the current row of pixels
		for (uint8_t pixel = 0; pixel < ScreenWidth; ++pixel)
		{
			bool isWindowCol = mLCDControl.WindowEnabled() && pixel >= windowX;

			uint8_t xPos = pixel;

			if (isWindowRow)
			{
				if (isWindowCol)
				{
					xPos = pixel - windowX;
				}
			}
			else
			{
				xPos += scrollX;
			}

			uint16_t tileCol = (xPos >> 3);

			uint8_t tileNum = mMemory.ReadByte(backgroundMemory + tileRow + tileCol);

			uint16_t tileLocation = tileData +
				((mLCDControl.TileIdentifiersAreUnsigned() ? tileNum : reinterpret_cast<int8_t&>(tileNum) + 128) << 4);

			// line is the current y position in the tile (y position mod the height of the tile, 8), times 2 bytes per tile
			uint8_t line = (yPos % 8) << 1;
			uint8_t data1 = mMemory.ReadByte(tileLocation + line);
			uint8_t data2 = mMemory.ReadByte(tileLocation + line + 1);

			// color bit is the current x position in the tile, measured from the left
			uint8_t colorBit = 7 - (xPos % 8);

			// get the color (before the pallet) from the two bytes
			// TODO possibly comment this more to explain
			uint8_t colorNumber = (Utilities::GetBit(data2, colorBit) << 1) | Utilities::GetBit(data1, colorBit);

			// get the actual color to draw from the pallet
			Display::Color color = mBackgroundPallet.GetPalletColor(colorNumber);

			// draw the pixel
			mDisplay.SetPixel(mCurrentScanline, pixel, color);
		}
	}

	void GPU::RenderSprites()
	{
		ObjectAttributeMemory& oam = mMemory.GetOAM();

		for (uint8_t sprite = 0; sprite < 40; sprite++)
		{
			SpriteAttributes& attributes = oam[sprite];
			uint8_t yPos = attributes.PositionY - 16;
			uint8_t xPos = attributes.PositionX - 8;

			uint8_t ysize = mLCDControl.GetSpriteHeight();

			// if the current scanline intersects the sprite, draw the appropriate line from the sprite
			if ((mCurrentScanline >= yPos) && (mCurrentScanline < (yPos + ysize)))
			{
				uint8_t line = mCurrentScanline - yPos;

				if (attributes.FlipY())
				{
					line = ysize - line;
				}

				line <<= 1;

				// get sprite pixel data. Sprites are 16 bytes, so offset by tile number * 16, then offset by the line number
				uint8_t data1 = mMemory.ReadByte((MemoryMap::VRAM_START + (attributes.TileNumber << 4)) + line);
				uint8_t data2 = mMemory.ReadByte((MemoryMap::VRAM_START + (attributes.TileNumber << 4)) + line + 1);

				// loop through each column of the sprite and set the corresponding pixels for the current row
				for (uint8_t tilePixel = 0; tilePixel < 8; ++tilePixel)
				{
					uint8_t colorBit = attributes.FlipX() ? 7 - tilePixel : tilePixel;
					uint8_t colorNumber = (Utilities::GetBit(data2, colorBit) << 1) | Utilities::GetBit(data1, colorBit);

					if (colorNumber == 0)
					{
					// white is transparent for sprites
						continue;
					}

					Display::Color col = attributes.GetPalletNumber() == 1 ?
						mSpritePallet1.GetPalletColor(colorNumber) :
						mSpritePallet0.GetPalletColor(colorNumber);

					uint8_t xPix = 7 - tilePixel;

					uint8_t pixel = xPos + xPix;

					// make sure sprite is in bounds (y bounds are already checked)
					if (pixel < 0 || pixel >= ScreenWidth)
					{
						continue;
					}

					// check if pixel is hidden behind background
					if (attributes.IsAboveBackground() || mDisplay.GetPixel(mCurrentScanline, pixel) == Display::Color::White)
					{
						mDisplay.SetPixel(mCurrentScanline, pixel, col);
					}
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
