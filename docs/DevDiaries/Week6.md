[Back to Home](../../README.md)

[Back to Week 5](Week5.md)

[Next to Week 7](Week7.md)

## 7/05/2017
This week was a LOT of refactoring, as well as a whole bunch of new features. I had to make up time for last week while still being busy with other commitments. While I didn't quite make up the time, I still made good progress. After this week, all that's left before I can fully run a game (probably just Tetris for now) is graphics.

One thing I did early on was move the interrupts from the CPU class to the MemoryMap class. This puts them closer to where they actually are, as well as giving easier access to them from other scripts which don't necessarily need a reference to the CPU but may already have a reference to the MemoryMap.

I also wanted to clean up the CPU.cpp file, so I separated all of the CPU Instruction related functionality into CPU.Instructions.cpp, which left CPU.cpp much slimmed down. I wasn't sure if this would work at first, but the world hasn't ended yet so I assume it did.

----

### Timers
On to the big new stuff: first, the Timer. I wasn't sure how the timer was supposed to work at first, so I had to do a lot of research. The [new source](http://www.codeslinger.co.uk/pages/projects/gameboy/timers.html) I found that I mentioned previously helped immensely in that regard.

I decided to use the method used in the example provided by the above link, where the timer is stepped relative to the CPU. That is, since the CPU runs at 4194304Hz, we can divide that by the Timer frequency to determine how many CPU cycles there are per step of the timer. To support this, the StepCPU method was refactored to return the number of cycles it took to execute the instruction.
For example, if the timer is set to 4096Hz, the timer will step once every 4194304 / 4096 = 1024 CPU clock cycles.

```c++
int32_t CPU::StepCPU();

void Timer::StepTimer(int32_t cpuCycles)
{
	StepDivider(cpuCycles);
	CheckFrequencyChange();

	if (IsEnabled())
	{
		mTimerCounter += cpuCycles;

		int32_t rate = CPU::CPUClockSpeed / mCurrentFrequency;
		if (mTimerCounter >= rate)
		{
			// reset counter
			mTimerCounter -= rate;

			uint8_t timer = mMemory.ReadByte(TimerAddress);
			if (timer == 0xFF)
			{
				mMemory.SetTimerInterruptFlag();
				mMemory.WriteByte(TimerAddress, GetTimerModulator());
			}
			else
			{
				mMemory.WriteByte(TimerAddress, timer + 1);
			}
		}
	}
}

// main loop
{
	int32_t cpuCycles = cpu.StepCPU();
	timer.StepTimer(cpuCycles);
}
```

One difference between my implementation and codeslinger's is that I deal with overflow of the timers. When mTimerCounter goes over the timer modulator, he resets the counter to 0 (actually he sets it to the modulator since he counts down), while I subtract out the modulator to keep any overflow in an attempt to keep it properly in sync with the CPU.

In my first pass at the timers and other hardware, I had them all reading and writing to the MemoryMap object. Later, I refactored this so each piece of IO hardware has its own registers, and added an IO class which houses all of these objects and deals with attempts to read or write to them properly. This has a side effect of fixing a problem I had with the first pass of the divider (and some other hardware) code:

```c++
// first pass
void Timer::StepDivider(int32_t cpuCycles)
{
	mDividerCounter += cpuCycles;
	const int32_t frequency = CPU::CPUClockSpeed / DividerFrequency;

	if (mDividerCounter >= frequency)
	{
		mDividerCounter -= frequency;
		// Technically attempting to write to this address resets it to 0,
		// but we need to be able to set it from here
		mMemory.WriteByte(DividerAddress, GetDivider() + 1);
	}
}

// new version
void Timer::StepDivider(int32_t cpuCycles)
{
	mDividerCounter += cpuCycles;
	const int32_t frequency = CPU::CPUClockSpeed / DividerFrequency;

	if (mDividerCounter >= frequency)
	{
		mDividerCounter -= frequency;
		// now the Timer class has direct access
		mDivider++;
	}
}

// and now writing to the divider can reset it to zero
void IO::WriteByte(uint16_t address, uint8_t value)
{
	switch (address)
	{
		// timer registers
		case Timer::DividerAddress:
			// Writing to the divider always sets it to 0
			mTimer.SetDivider(0);
	}
}
```

### GPU
Next up was the first pass at the GPU. This came from the [LCD section](http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html) of the website I've been referencing. Note that no graphics have been done yet, this is just the hardware setup. This ended up being very similar to the timer:

```c++
void GPU::StepGPU(int32_t cpuCycles)
{
	if (!IsEnabled())
	{
		// while the LCD is disabled, reset the scanline and set the mode to VBlank
		mScanlineCounter = 0;
		mMemory.WriteByte(CurrentScanlineAddress, 0);
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
		CheckCoincidenceFlag();
	}
}
```

Initially this function was kind of a mess, but I refactored out the three methods you see there. There wasn't anything particularly significant about this that wasn't covered in the Timer section, so I won't go into to much detail. If you're interested, the full source can be viewed on the [repository](https://github.com/evanbbass/GameBoi/blob/6b3181a2e0ee6f2f7e5aa99bc2de571b0f42c908/source/GameBoi.Library/GPU.cpp).

### Input
The last major hardware feature added was the inputs. While this wasn't much code, it does seem to be needlessly complicated. Rather than mapping the 8 possible inputs to its own bit in the register, they are all mapped to the lower 4 bits while bits 4 and 5 signify which group the program wants to read:
```
Taken from pandocs
Bit 7 - Not used
Bit 6 - Not used
Bit 5 - P15 Select Button Keys (0=Select)
Bit 4 - P14 Select Direction Keys (0=Select)
Bit 3 - P13 Input Down or Start (0=Pressed) (Read Only)
Bit 2 - P12 Input Up or Select (0=Pressed) (Read Only)
Bit 1 - P11 Input Left or Button B (0=Pressed) (Read Only)
Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)
```

But after looking at some of the other examples, I came up with a pretty simple implementation:
```c++
uint8_t Keypad::GetKeypadRegister() const
{
	if (mDirectionModeSelected)
	{
		return mDirectionRegister;
	}
	else if (mButtonModeSelected)
	{
		return mButtonRegister;
	}
	else
	{
		// If neither state was selected, treat all buttons as not pressed
		return 0x0F;
	}
}

void Keypad::SetKeypadRegister(uint8_t value)
{
	mButtonModeSelected = Utilities::TestBit(value, ButtonBit);
	mDirectionModeSelected = Utilities::TestBit(value, DirectionBit);
}
```

Then for each button, set the bit in the correct register (and trigger interrupts if necessary):
```c++
void Keypad::SetButtonAPressed(bool pressed)
{
	mButtonRegister = pressed ?
		Utilities::ResetBit(mButtonRegister, ButtonABit) :
		Utilities::SetBit(mButtonRegister, ButtonABit);

	if (pressed && mButtonModeSelected)
	{
		mMemory.SetKeypadInterruptFlag();
	}
}
```

----
### IAddressable interface
One more thing I'd like to note before getting to the fun stuff: Since so much hardware has the Read/Write functionality, I decided to make an interface that they could all inherit from:

```c++
class IAddressable abstract
{
public:
	virtual ~IAddressable() = default;

	virtual uint8_t ReadByte(uint16_t address) const = 0;
	virtual void WriteByte(uint16_t address, uint8_t value) = 0;

	uint16_t ReadWord(uint16_t address) const
	{
		return (ReadByte(address + 1) << 8) | ReadByte(address);
	}

	void WriteWord(uint16_t address, uint16_t value)
	{
		WriteByte(address, value & 0x00FF);
		WriteByte(address + 1, (value & 0xFF00) >> 8);
	}
};
```

### Rendering
While I don't have graphics fully implemented, I decided to go ahead and try to get a window up and running. I decided to use [SMFL](https://www.sfml-dev.org) as it is very simple to use (what would normally be 500 lines of OpenGL or DirectX code can be done in about 10 with SFML).

I got a game loop up and running within 30 minutes:

```C++
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
	int32_t cpuCycles = 0;
	const int32_t maxCycles = CPU::CPUClockSpeed / 60;
	while (cpuCycles < maxCycles)
	{
		cpuCycles += gb.Update();
	}
	HandleKeyPress(keypad);

	// draw

	window.display();
}
```

Key presses were very simple to add, and I tested them and they work properly:
```c++
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
```

I used the same approach used by [codeslinger](http://www.codeslinger.co.uk/pages/projects/gameboy/beginning.html), where all 1/60th of a second worth of instructions are executed each frame. I might change this later, but for now it's a good regulator.

Obviously it's just a black screen for now, but it works! (Well, I haven't tested actually running a game yet, but it shows a window!)
