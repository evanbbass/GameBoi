#include "pch.h"
#include "Keypad.h"
#include "Utilities.h"
#include "MemoryMap.h"

// IMPORTANT NOTE
// A value of 0 indicates a button is pressed. A value of 1 indicates it is not.

namespace
{
	constexpr uint8_t ButtonABit = 0;
	constexpr uint8_t ButtonBBit = 1;
	constexpr uint8_t ButtonSelectBit = 2;
	constexpr uint8_t ButtonStartBit = 3;
	constexpr uint8_t DirectionRightBit = 0;
	constexpr uint8_t DirectionLeftBit = 1;
	constexpr uint8_t DirectionUpBit = 2;
	constexpr uint8_t DirectionDownBit = 3;
	constexpr uint8_t DirectionBit = 4;
	constexpr uint8_t ButtonBit = 5;
}

namespace GameBoi
{
	Keypad::Keypad(MemoryMap& memory) :
		mMemory(memory),
		mButtonModeSelected(false), mDirectionModeSelected(false),
		mButtonRegister(~(1 << ButtonBit) & 0xFF), mDirectionRegister(~(1 << DirectionBit) & 0xFF)
	{
	}

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
			return 0xFF;
		}
	}

	void Keypad::SetKeypadRegister(uint8_t value)
	{
		// 0 = select
		mButtonModeSelected = !Utilities::TestBit(value, ButtonBit);
		mDirectionModeSelected = !Utilities::TestBit(value, DirectionBit);
	}

	bool Keypad::GetButtonAPressed() const
	{
		return !Utilities::TestBit(mButtonRegister, ButtonABit);
	}

	bool Keypad::GetButtonBPressed() const
	{
		return !Utilities::TestBit(mButtonRegister, ButtonBBit);
	}

	bool Keypad::GetButtonStartPressed() const
	{
		return !Utilities::TestBit(mButtonRegister, ButtonStartBit);
	}

	bool Keypad::GetButtonSelectPressed() const
	{
		return !Utilities::TestBit(mButtonRegister, ButtonSelectBit);
	}

	bool Keypad::GetDirectionRightPressed() const
	{
		return !Utilities::TestBit(mDirectionRegister, DirectionRightBit);
	}

	bool Keypad::GetDirectionLeftPressed() const
	{
		return !Utilities::TestBit(mDirectionRegister, DirectionLeftBit);
	}

	bool Keypad::GetDirectionUpPressed() const
	{
		return !Utilities::TestBit(mDirectionRegister, DirectionUpBit);
	}

	bool Keypad::GetDirectionDownPressed() const
	{
		return !Utilities::TestBit(mDirectionRegister, DirectionDownBit);
	}

	void Keypad::SetButtonAPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetButtonAPressed();
			
			mButtonRegister = Utilities::ResetBit(mButtonRegister, ButtonABit);

			if (!wasPressed && mButtonModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mButtonRegister = Utilities::SetBit(mButtonRegister, ButtonABit);
		}
	}

	void Keypad::SetButtonBPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetButtonBPressed();

			mButtonRegister = Utilities::ResetBit(mButtonRegister, ButtonBBit);

			if (!wasPressed && mButtonModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mButtonRegister = Utilities::SetBit(mButtonRegister, ButtonBBit);
		}
	}

	void Keypad::SetButtonStartPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetButtonStartPressed();

			mButtonRegister = Utilities::ResetBit(mButtonRegister, ButtonStartBit);

			if (!wasPressed && mButtonModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mButtonRegister = Utilities::SetBit(mButtonRegister, ButtonStartBit);
		}
	}

	void Keypad::SetButtonSelectPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetButtonSelectPressed();

			mButtonRegister = Utilities::ResetBit(mButtonRegister, ButtonSelectBit);

			if (!wasPressed && mButtonModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mButtonRegister = Utilities::SetBit(mButtonRegister, ButtonSelectBit);
		}
	}

	void Keypad::SetDirectionRightPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetDirectionRightPressed();

			mDirectionRegister = Utilities::ResetBit(mDirectionRegister, DirectionRightBit);

			if (!wasPressed && mDirectionModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mDirectionRegister = Utilities::SetBit(mDirectionRegister, DirectionRightBit);
		}
	}

	void Keypad::SetDirectionLeftPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetDirectionLeftPressed();

			mDirectionRegister = Utilities::ResetBit(mDirectionRegister, DirectionLeftBit);

			if (!wasPressed && mDirectionModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mDirectionRegister = Utilities::SetBit(mDirectionRegister, DirectionLeftBit);
		}
	}

	void Keypad::SetDirectionUpPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetDirectionUpPressed();

			mDirectionRegister = Utilities::ResetBit(mDirectionRegister, DirectionUpBit);

			if (!wasPressed && mDirectionModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mDirectionRegister = Utilities::SetBit(mDirectionRegister, DirectionUpBit);
		}
	}

	void Keypad::SetDirectionDownPressed(bool pressed)
	{
		if (pressed)
		{
			bool wasPressed = GetDirectionDownPressed();

			mDirectionRegister = Utilities::ResetBit(mDirectionRegister, DirectionDownBit);

			if (!wasPressed && mDirectionModeSelected)
			{
				mMemory.SetKeypadInterruptFlag();
			}
		}
		else
		{
			mDirectionRegister = Utilities::SetBit(mDirectionRegister, DirectionDownBit);
		}
	}
}
