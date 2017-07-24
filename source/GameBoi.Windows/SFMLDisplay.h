#pragma once
#include <array>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "GPU.h"
#include "Display.h"
#include "Helpers.h"

namespace GameBoiWindows
{
	class SFMLDisplay final
	{
	public:
		SFMLDisplay() :
			mBlackColor(sf::Color::Black), mWhiteColor(sf::Color::White)
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

					sf::Color color = Helpers::InterpolateColors(mWhiteColor, mBlackColor, value / 3.0f);

					mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4    ] = color.r;
					mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 1] = color.g;
					mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 2] = color.b;
					mPixels[(col + GameBoi::GPU::ScreenWidth * row) * 4 + 3] = color.a;
				}
			}
		}

		const sf::Color& GetBlackColor() const
		{
			return mBlackColor;
		}

		void SetBlackColor(const sf::Color& color)
		{
			mBlackColor = color;
		}

		const sf::Color& GetWhiteColor() const
		{
			return mWhiteColor;
		}

		void SetWhiteColor(const sf::Color& color)
		{
			mWhiteColor = color;
		}

		const uint8_t* GetPixels() const
		{
			return mPixels.data();
		}

	private:
		std::array<uint8_t, GameBoi::GPU::ScreenWidth * GameBoi::GPU::ScreenHeight * 4> mPixels;
		sf::Color mBlackColor;
		sf::Color mWhiteColor;
	};
}
