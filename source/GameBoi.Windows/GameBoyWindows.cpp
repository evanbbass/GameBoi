#include "pch.h"
#include "GameBoyWindows.h"

using namespace GameBoi;

namespace GameBoiWindows
{
	GameBoyWindows::GameBoyWindows(const std::string& cartridgeName) :
		mWindow(sf::VideoMode(GPU::ScreenWidth * 3, GPU::ScreenHeight * 3), "GameBoi"), mShowFPS(false)
	{
		mFont.loadFromFile("Calibri.ttf");
		mFPS.setFont(mFont);
		mFPS.setCharacterSize(12);
		mFPS.setFillColor(sf::Color::White);
		mFPS.setOutlineColor(sf::Color::Black);
		mFPS.setOutlineThickness(1.0f);

		mGameBoy.LoadCartridge(cartridgeName);
		std::string windowTitle = "GameBoi - ";
		windowTitle += mGameBoy.GetMemoryMap().GetCartridge().GetGameTitle();
		mWindow.setTitle(windowTitle);

		mWindow.setFramerateLimit(60);
		mView.reset(sf::FloatRect(0.0f, 0.0f, static_cast<float>(GPU::ScreenWidth), static_cast<float>(GPU::ScreenHeight)));
		mView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		mWindow.setView(mView);

		mTexture.create(GPU::ScreenWidth, GPU::ScreenHeight);
		mLCDScreen.setTexture(mTexture);
	}

	void GameBoyWindows::Run()
	{
		while (mWindow.isOpen())
		{
			sf::Event e;
			while (mWindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed || (mWindow.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				{
					mWindow.close();
				}
			}

			mWindow.clear(sf::Color::Black);

			// update gameboy
			int32_t cpuCycles = 0;
			const int32_t maxCycles = CPU::CPUClockSpeed / 60;
			while (cpuCycles < maxCycles)
			{
				try
				{
					cpuCycles += mGameBoy.Update();
				}
				catch (const std::exception& ex)
				{
					if (MessageBoxA(mWindow.getSystemHandle(), ex.what(), "Error!", MB_OK) == IDOK)
					{
						mWindow.close();
					}
				}
			}
			HandleKeyPress();

			// draw
			Display& gbDisplay = mGameBoy.GetMemoryMap().GetIO().GetGPU().GetDisplay();
			mDisplay.UpdatePixels(gbDisplay);
			mTexture.update(mDisplay.GetPixels());
			mWindow.draw(mLCDScreen);

			if (mShowFPS)
			{
				DrawFPS();
			}

			mWindow.display();
		}

		mGameBoy.WriteSaveFile();
	}

	void GameBoyWindows::HandleKeyPress()
	{
		if (!mWindow.hasFocus())
		{
			return;
		}

		Keypad& keypad = mGameBoy.GetMemoryMap().GetIO().GetKeypad();

		keypad.SetButtonAPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
		keypad.SetButtonBPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::X));
		keypad.SetButtonStartPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
		keypad.SetButtonSelectPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

		keypad.SetDirectionUpPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
		keypad.SetDirectionDownPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
		keypad.SetDirectionLeftPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		keypad.SetDirectionRightPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			mShowFPS = !mShowFPS;
		}
	}

	void GameBoyWindows::DrawFPS()
	{
		static sf::Clock clock;
		static float lastTime = 0.0f;
	
		float currentTime = clock.getElapsedTime().asSeconds();
		if (currentTime >= 0.5f)
		{
			float fps = 1.0f / (currentTime - lastTime);
			clock.restart();
			lastTime = 0;
			mFPS.setString(std::to_string(fps));
		}
		else
		{
			lastTime = currentTime;
		}
	
		mWindow.draw(mFPS);
	}
}
