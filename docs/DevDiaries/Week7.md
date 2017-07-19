[Back to Home](../../README.md)

[Back to Week 6](Week6.md)

[Next to Week 8](Week8.md)

## 7/12/2017
This week's dev diary was posted late because there wasn't much to show due to bugs.

As planned, I finished the GPU functionality, and I hooked everything up to an SFML window with a full game loop, but after some testing, I found that the rendering functions were never getting called anyway, so nothing was ever being written to the LCD screen.

Unfortunately I didn't have much time left for this week so I only got some preliminary debugging done, which means I didn't have anything to show other than a blank screen with the promise that the emulator is running in the background.

I'll breifly go over some of the code I wrote this week, but for the really interesting stuff I'd suggest going over to [next week's diary](Week8.md).

----

### LCD Screen
First, I needed a class to actually write the pixels to, and that SFML could later read the pixels from. Unlike other emulators that immediately translate Game Boy pixel values into RGB colors, I decided to abstract that into simply a 2D array of colors (white, light gray, dark gray, or black) which could be interpreted later using whatever framework necessary (even though I knew I would be using SFML).

```c++
class Display final
{
public:
	enum class Color : uint8_t
	{
		White = 0b00,
		LightGray = 0b01,
		DarkGray = 0b10,
		Black = 0b11
	};

	Color GetPixel(int32_t row, int32_t column) const
	{
		return mDisplay[row][column];
	}

	void SetPixel(int32_t row, int32_t column, Color value)
	{
		mDisplay[row][column] = value;
	}

private:
	std::array<std::array<Color, 160>, 144> mDisplay;
};
```

On the flip side, I added a class dedicated to interfacing between that `Display` class and SFML.

```c++
class SFMLDisplay final
{
public:
	SFMLDisplay()
	{
		mPixels.fill(0x00);
	}

	void UpdatePixels(const GameBoi::Display& display)
	{
		for (int col = 0; col < GameBoi::GPU::ScreenWidth; ++col)
		{
			for (int row = 0; row < GameBoi::GPU::ScreenHeight; ++row)
			{
				uint8_t value = static_cast<uint8_t>(display.GetPixel(row, col));

				sf::Color color = Helpers::InterpolateColors(sf::Color::White, sf::Color::Black, value / 3.0f);

				mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4    ] = color.r;
				mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 1] = color.g;
				mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 2] = color.b;
				mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 3] = color.a;
			}
		}
	}

	const uint8_t* GetPixels() const
	{
		return mPixels.data();
	}

private:
	std::array<uint8_t, GameBoi::GPU::ScreenWidth * GameBoi::GPU::ScreenHeight * 4> mPixels;
};
```

Then, in the main loop, I update the pixel data and pass it into an SFML texture.

```c++
void GameBoyWindows::Run()
{
	while (mWindow.isOpen())
	{
		// update code

		// draw
		Display& gbDisplay = mGameBoy.GetMemoryMap().GetIO().GetGPU().GetDisplay();
		mDisplay.UpdatePixels(gbDisplay);
		mTexture.update(mDisplay.GetPixels());
		mWindow.draw(mLCDScreen);
	}
}
```

### Other Abstractions
Once I started working primarily in the IO area, I noticed that there were a great many fields that contained bitmasked attributes. To help with code cleanliness, I started to abstract those fields into their own classes.

One example is the sprite attributes in the Object Attribute Memory (OAM). The OAM contains attributes for 40 sprites, with each attributes field being made up of 4 bytes. To that end, I refactored the OAM field in the memory map into its own class, which was simply an array of `SpriteAttributes` objects.

```c++
class ObjectAttributeMemory : public IAddressable
{
public:
	uint8_t ReadByte(uint16_t address) const override;
	void WriteByte(uint16_t address, uint8_t value) override;

	SpriteAttributes& operator[](int32_t index);
	const SpriteAttributes& operator[](int32_t index) const;

private:
	std::array<SpriteAttributes, 40> mSpriteAttributes;
};

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
```

Another abstraction I made was the `Pallet`s in the GPU. The Pallets determine what bit values map to which actual colors. For example, a pallet value of `0b11100100` would map 00 to white, 11 to black, etc. as normal. However a value of `0b00011011` would reverse that. (An example of this would be in Mario games when Mario blinks while invincible).

```c++
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
```

----

That's really it for this week. The bulk of the work was writing the `DrawTiles()` and `DrawSprites()` functions in the GPU, but those are heavily inspired from [the codeslinger blog](http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html) and therefore aren't particularly exciting.
