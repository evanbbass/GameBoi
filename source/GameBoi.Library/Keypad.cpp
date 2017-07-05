#include "pch.h"
#include "Keypad.h"
#include "Utilities.h"
#include "MemoryMap.h"

// IMPORTANT NOTE
// A value of 0 indicates a button is pressed. A value of 1 indicates it is not.

namespace GameBoi
{
	Keypad::Keypad(MemoryMap& memory) :
		mMemory(memory),
		mButtonModeSelected(false), mDirectionModeSelected(false),
		mButtonRegister((1 << ButtonBit) | 0x0F), mDirectionRegister((1 << DirectionBit) | 0x0F)
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
			return 0x0F;
		}
	}

	void Keypad::SetKeypadRegister(uint8_t value)
	{
		mButtonModeSelected = Utilities::TestBit(value, ButtonBit);
		mDirectionModeSelected = Utilities::TestBit(value, DirectionBit);
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
		bool wasPressed = GetButtonAPressed();
		mButtonRegister = pressed ?
			Utilities::ResetBit(mButtonRegister, ButtonABit) :
			Utilities::SetBit(mButtonRegister, ButtonABit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetButtonBPressed(bool pressed)
	{
		bool wasPressed = GetButtonBPressed();
		mButtonRegister = pressed ?
			Utilities::ResetBit(mButtonRegister, ButtonBBit) :
			Utilities::SetBit(mButtonRegister, ButtonBBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetButtonStartPressed(bool pressed)
	{
		bool wasPressed = GetButtonStartPressed();
		mButtonRegister = pressed ?
			Utilities::ResetBit(mButtonRegister, ButtonStartBit) :
			Utilities::SetBit(mButtonRegister, ButtonStartBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetButtonSelectPressed(bool pressed)
	{
		bool wasPressed = GetButtonSelectPressed();
		mButtonRegister = pressed ?
			Utilities::ResetBit(mButtonRegister, ButtonSelectBit) :
			Utilities::SetBit(mButtonRegister, ButtonSelectBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetDirectionRightPressed(bool pressed)
	{
		bool wasPressed = GetDirectionRightPressed();
		mDirectionRegister = pressed ?
			Utilities::ResetBit(mDirectionRegister, DirectionRightBit) :
			Utilities::SetBit(mDirectionRegister, DirectionRightBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetDirectionLeftPressed(bool pressed)
	{
		bool wasPressed = GetDirectionLeftPressed();
		mDirectionRegister = pressed ?
			Utilities::ResetBit(mDirectionRegister, DirectionLeftBit) :
			Utilities::SetBit(mDirectionRegister, DirectionLeftBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetDirectionUpPressed(bool pressed)
	{
		bool wasPressed = GetDirectionUpPressed();
		mDirectionRegister = pressed ?
			Utilities::ResetBit(mDirectionRegister, DirectionUpBit) :
			Utilities::SetBit(mDirectionRegister, DirectionUpBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}

	void Keypad::SetDirectionDownPressed(bool pressed)
	{
		bool wasPressed = GetDirectionDownPressed();
		mDirectionRegister = pressed ?
			Utilities::ResetBit(mDirectionRegister, DirectionDownBit) :
			Utilities::SetBit(mDirectionRegister, DirectionDownBit);

		if (pressed && !wasPressed && mButtonModeSelected)
		{
			mMemory.SetKeypadInterruptFlag();
		}
	}
}
