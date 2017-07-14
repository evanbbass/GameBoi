#pragma once
#include <array>

namespace GameBoi
{
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
}
