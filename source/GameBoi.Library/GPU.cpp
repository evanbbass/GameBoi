#include "pch.h"
#include "GPU.h"
#include "MemoryMap.h"
#include "Utilities.h"

using namespace std;

// TODO I go lazy and stopped getting rid of magic numbers, probably should fix that

namespace GameBoi
{
	GPU::GPU(MemoryMap& memory) :
		mMemory(memory), mScanlineCounter(0), mCurrentScanline(0), mLCDStatusRegister(0), mCoincidenceRegister(0),
		mScrollY(0), mScrollX(0), mWindowY(0), mWindowX(0)
	{
	}

	void GPU::StepGPU(int32_t cpuCycles)
	{
		if (!mLCDControlRegister.LCDEnabled())
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
		return mLCDControlRegister.GetRegister();
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
		mLCDControlRegister.SetRegister(value);
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

	void GPU::DrawScanLine()
	{
		if (mLCDControlRegister.BackgroundEnabled())
		{
			RenderTiles();
		}

		if (mLCDControlRegister.SpriteEnabled())
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

		bool usingWindow = mLCDControlRegister.WindowEnabled() && windowY <= mCurrentScanline;

		// which tile data are we using?
		uint16_t tileData = mLCDControlRegister.GetWindowTileDataAddress();

		uint16_t backgroundMemory = usingWindow ?
			mLCDControlRegister.GetWindowTileMapDisplayAddress() :
			mLCDControlRegister.GetBackgroundTileMapDisplayAddress();

		uint8_t yPos = usingWindow ? mCurrentScanline - windowY : scrollY + mCurrentScanline;

		uint16_t tileRow = (yPos >> 3) << 5;

		// for each column in the current row of pixels
		for (uint8_t pixel = 0; pixel < ScreenWidth; ++pixel)
		{
			uint8_t xPos = pixel + scrollX;

			if (usingWindow)
			{
				if (pixel >= windowX)
				{
					xPos = pixel - windowX;
				}
			}

			uint16_t tileCol = (xPos >> 3);

			uint8_t tileNum = mMemory.ReadByte(backgroundMemory + tileRow + tileCol);

			uint16_t tileLocation = tileData + ((mLCDControlRegister.TileIdentifiersAreUnsigned() ? tileNum : reinterpret_cast<int8_t&>(tileNum) + 128) << 4);

			// line is the current y position in the tile (y position mod the height of the tile, 8), times 2 bytes per tile
			uint8_t line = (yPos % 8) << 1;
			uint8_t data1 = mMemory.ReadByte(tileLocation + line);
			uint8_t data2 = mMemory.ReadByte(tileLocation + line + 1);

			// color bit is the current x position in the tile, measured from the left
			uint8_t colourBit = 7 - (xPos % 8);

			// get the color (before the pallet) from the two bytes
			// TODO possibly comment this more to explain
			uint8_t colorNumber = (Utilities::GetBit(data2, colourBit) << 1) | Utilities::GetBit(data1, colourBit);

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

			uint8_t ysize = mLCDControlRegister.GetSpriteHeight();

			// if the current scanline intersects the sprite, draw the appropriate line from the sprite
			if ((mCurrentScanline >= yPos) && (mCurrentScanline < (yPos + ysize)))
			{
				uint8_t line = mCurrentScanline - yPos;

				if (attributes.FlipY())
				{
					line = ysize - line;
				}

				line <<= 1;

				uint8_t data1 = mMemory.ReadByte((0x8000 + (attributes.TileNumber << 4)) + line);
				uint8_t data2 = mMemory.ReadByte((0x8000 + (attributes.TileNumber << 4)) + line + 1);

				// loop through each column of the sprite and set the corresponding pixels for the current row
				for (uint8_t tilePixel = 0; tilePixel < 8; ++tilePixel)
				{
					uint8_t colourbit = attributes.FlipX() ? 7 - tilePixel : tilePixel;
					uint8_t colourNum = (Utilities::GetBit(data2, colourbit) << 1) | Utilities::GetBit(data1, colourbit);

					Display::Color col = attributes.GetPalletNumber() == 1 ?
						mSpritePallet1.GetPalletColor(colourNum) :
						mSpritePallet0.GetPalletColor(colourNum);

					// white is transparent for sprites
					if (col == Display::Color::White)
					{
						continue;
					}

					uint8_t xPix = 7 - tilePixel;

					uint8_t pixel = xPos + xPix;

					// check if pixel is hidden behind background
					if (attributes.IsAboveBackground() && mDisplay.GetPixel(mCurrentScanline, pixel) == Display::Color::White)
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
