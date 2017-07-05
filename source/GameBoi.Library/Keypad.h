#pragma once

namespace GameBoi
{
	class MemoryMap;

	class Keypad final
	{
	public:
		explicit Keypad(MemoryMap& memory);

		uint8_t GetKeypadRegister() const;
		void SetKeypadRegister(uint8_t value);

		bool GetButtonAPressed() const;
		bool GetButtonBPressed() const;
		bool GetButtonStartPressed() const;
		bool GetButtonSelectPressed() const;
		bool GetDirectionRightPressed() const;
		bool GetDirectionLeftPressed() const;
		bool GetDirectionUpPressed() const;
		bool GetDirectionDownPressed() const;

		void SetButtonAPressed(bool pressed);
		void SetButtonBPressed(bool pressed);
		void SetButtonStartPressed(bool pressed);
		void SetButtonSelectPressed(bool pressed);
		void SetDirectionRightPressed(bool pressed);
		void SetDirectionLeftPressed(bool pressed);
		void SetDirectionUpPressed(bool pressed);
		void SetDirectionDownPressed(bool pressed);

		static const uint16_t KeypadRegisterAddress = 0xFF00;
		static const uint8_t ButtonABit = 0;
		static const uint8_t ButtonBBit = 1;
		static const uint8_t ButtonStartBit = 2;
		static const uint8_t ButtonSelectBit = 3;
		static const uint8_t DirectionRightBit = 0;
		static const uint8_t DirectionLeftBit = 1;
		static const uint8_t DirectionUpBit = 2;
		static const uint8_t DirectionDownBit = 3;
		static const uint8_t ButtonBit = 4;
		static const uint8_t DirectionBit = 5;

	private:
		MemoryMap& mMemory;
		bool mButtonModeSelected;
		bool mDirectionModeSelected;
		uint8_t mButtonRegister;
		uint8_t mDirectionRegister;

	};
}
