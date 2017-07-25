#include "pch.h"
#include "GameBoyWindows.h"

using namespace std;
using namespace sf;
using namespace GameBoi;

namespace GameBoiWindows
{
	GameBoyWindows::GameBoyWindows(const string& cartridgeName) :
		mWindow(VideoMode(GPU::ScreenWidth * 3, GPU::ScreenHeight * 3), "GameBoi"), mShowFPS(false)
	{
		mFont.loadFromFile("Calibri.ttf");
		mFPS.setFont(mFont);
		mFPS.setCharacterSize(12);
		mFPS.setFillColor(Color::White);
		mFPS.setOutlineColor(Color::Black);
		mFPS.setOutlineThickness(1.0f);

		mGameBoy.LoadCartridge(cartridgeName);

		mWindow.setFramerateLimit(60);
		mView.reset(FloatRect(0.0f, 0.0f, static_cast<float>(GPU::ScreenWidth), static_cast<float>(GPU::ScreenHeight)));
		mView.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		mWindow.setView(mView);

		mTexture.create(GPU::ScreenWidth, GPU::ScreenHeight);
		mLCDScreen.setTexture(mTexture);
	}

	void GameBoyWindows::Run()
	{
		while (mWindow.isOpen())
		{
			Event e;
			while (mWindow.pollEvent(e))
			{
				if (e.type == Event::Closed || (mWindow.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)))
				{
					mWindow.close();
				}
			}

			mWindow.clear(Color::Black);

			// update gameboy
			int32_t cpuCycles = 0;
			const int32_t maxCycles = CPU::CPUClockSpeed / 60;
			while (cpuCycles < maxCycles)
			{
				try
				{
					cpuCycles += mGameBoy.Update();
				}
				catch (exception& ex)
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

		keypad.SetButtonAPressed(Keyboard::isKeyPressed(Keyboard::Z));
		keypad.SetButtonBPressed(Keyboard::isKeyPressed(Keyboard::X));
		keypad.SetButtonStartPressed(Keyboard::isKeyPressed(Keyboard::Return));
		keypad.SetButtonSelectPressed(Keyboard::isKeyPressed(Keyboard::Space));

		keypad.SetDirectionUpPressed(Keyboard::isKeyPressed(Keyboard::Up));
		keypad.SetDirectionDownPressed(Keyboard::isKeyPressed(Keyboard::Down));
		keypad.SetDirectionLeftPressed(Keyboard::isKeyPressed(Keyboard::Left));
		keypad.SetDirectionRightPressed(Keyboard::isKeyPressed(Keyboard::Right));

		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			mShowFPS = !mShowFPS;
		}
	}

	void GameBoyWindows::DrawFPS()
	{
		static Clock clock;
		static float lastTime = 0.0f;
	
		float currentTime = clock.getElapsedTime().asSeconds();
		if (currentTime >= 0.5f)
		{
			float fps = 1.0f / (currentTime - lastTime);
			clock.restart();
			lastTime = 0;
			mFPS.setString(to_string(fps));
		}
		else
		{
			lastTime = currentTime;
		}
	
		mWindow.draw(mFPS);
	}
}
