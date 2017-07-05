// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "GameBoy.h"

using namespace std;
using namespace GameBoi;
using namespace sf;

void HandleKeyPress(Keypad& keypad);

int main(int argc, char* argv[])
{
	GameBoy gb;
	if (argc > 1)
	{
		gb.LoadCartridge(argv[1]);
	}

	Keypad& keypad = gb.GetMemoryMap().GetIO().GetKeypad();

	RenderWindow window(VideoMode(GPU::ScreenWidth * 5, GPU::ScreenHeight * 5), "GameBoi", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear(Color::Black);

		// update gameboy
		//int32_t cpuCycles = 0;
		//const int32_t maxCycles = CPU::CPUClockSpeed / 60;
		//while (cpuCycles < maxCycles)
		//{
		//	cpuCycles += gb.Update();
		//}
		HandleKeyPress(keypad);

		// draw

		window.display();
	}

	return 0;
}

void HandleKeyPress(Keypad& keypad)
{
	keypad.SetButtonAPressed(Keyboard::isKeyPressed(Keyboard::Z));
	keypad.SetButtonBPressed(Keyboard::isKeyPressed(Keyboard::X));
	keypad.SetButtonStartPressed(Keyboard::isKeyPressed(Keyboard::Return));
	keypad.SetButtonSelectPressed(Keyboard::isKeyPressed(Keyboard::Space));

	keypad.SetDirectionUpPressed(Keyboard::isKeyPressed(Keyboard::Up));
	keypad.SetDirectionDownPressed(Keyboard::isKeyPressed(Keyboard::Down));
	keypad.SetDirectionLeftPressed(Keyboard::isKeyPressed(Keyboard::Left));
	keypad.SetDirectionRightPressed(Keyboard::isKeyPressed(Keyboard::Right));
}
