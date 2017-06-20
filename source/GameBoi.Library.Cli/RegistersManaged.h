#pragma once

#include "Registers.h"

namespace GameBoiManaged
{
	public ref class RegistersManaged
	{
	public:
		RegistersManaged();
		RegistersManaged(GameBoi::Registers& unmanagedRegisters);

		property GameBoi::Registers& Unmanaged { GameBoi::Registers& get(); }

		property System::Byte A { System::Byte get(); void set(System::Byte value); }
		property System::Byte F { System::Byte get(); void set(System::Byte value); }
		property System::UInt16 AF { System::UInt16 get(); void set(System::UInt16 value); }
		property System::Byte B { System::Byte get(); void set(System::Byte value); }
		property System::Byte C { System::Byte get(); void set(System::Byte value); }
		property System::UInt16 BC { System::UInt16 get(); void set(System::UInt16 value); }
		property System::Byte D { System::Byte get(); void set(System::Byte value); }
		property System::Byte E { System::Byte get(); void set(System::Byte value); }
		property System::UInt16 DE { System::UInt16 get(); void set(System::UInt16 value); }
		property System::Byte H { System::Byte get(); void set(System::Byte value); }
		property System::Byte L { System::Byte get(); void set(System::Byte value); }
		property System::UInt16 HL { System::UInt16 get(); void set(System::UInt16 value); }
		property System::UInt16 SP { System::UInt16 get(); void set(System::UInt16 value); }
		property System::UInt16 PC { System::UInt16 get(); void set(System::UInt16 value); }

		void Reset();

		property bool ZeroFlag { bool get(); void set(bool value); }
		void SetZeroFlag();
		void ResetZeroFlag();

		property bool SubtractFlag { bool get(); void set(bool value); }
		void SetSubtractFlag();
		void ResetSubtractFlag();

		property bool HalfCarryFlag { bool get(); void set(bool value); }
		void SetHalfCarryFlag();
		void ResetHalfCarryFlag();

		property bool CarryFlag { bool get(); void set(bool value); }
		void SetCarryFlag();
		void ResetCarryFlag();

	private:
		GameBoi::Registers* mRegisters;
	};
}
