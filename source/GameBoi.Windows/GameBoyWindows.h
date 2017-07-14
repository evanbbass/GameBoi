#pragma once
#include "GameBoy.h"
#include <SFML/Graphics.hpp>
#include "SFMLDisplay.h"

namespace GameBoiWindows
{
	class GameBoyWindows
	{
	public:
		explicit GameBoyWindows(const std::string& cartridgeName);

		void Run();

	private:
		GameBoi::GameBoy mGameBoy;

		SFMLDisplay mDisplay;

		sf::RenderWindow mWindow;
		sf::View mView;
		sf::Texture mTexture;
		sf::Sprite mLCDScreen;
		sf::Text mFPS;

		void HandleKeyPress();
		void DrawFPS();

		sf::Font mFont;
	};
}
