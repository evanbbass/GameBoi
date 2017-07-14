#pragma once
#include <SFML/Graphics/Color.hpp>

namespace GameBoiWindows
{
	class Helpers abstract final
	{
	public:
		static sf::Color InterpolateColors(const sf::Color& color1, const sf::Color& color2, float interpolationValue)
		{
			sf::Color newColor;
			newColor.r = static_cast<uint8_t>(color1.r + (color2.r - color1.r) * interpolationValue);
			newColor.g = static_cast<uint8_t>(color1.g + (color2.g - color1.g) * interpolationValue);
			newColor.b = static_cast<uint8_t>(color1.b + (color2.b - color1.b) * interpolationValue);
			newColor.a = 255;
			return newColor;
		}
	};
}
