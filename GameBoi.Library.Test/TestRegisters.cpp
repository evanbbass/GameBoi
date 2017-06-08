#include "pch.h"
#include "CppUnitTest.h"
#include "Registers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace GameBoi;

namespace GameBoiLibraryTest
{
	TEST_CLASS(TestRegisters)
	{
	public:

		TEST_METHOD(TestRegistersUnions)
		{
			Registers reg;

			uint8_t zeroByte = 0;
			uint16_t zeroWord = 0;

			// test registers are initialized to zero
			Assert::IsTrue(zeroByte == reg.A);
			Assert::IsTrue(zeroByte == reg.Accumulator);
			Assert::IsTrue(zeroByte == reg.F);
			Assert::IsTrue(zeroByte == reg.Flags);
			Assert::IsTrue(zeroWord == reg.AF);
			Assert::IsTrue(zeroByte == reg.B);
			Assert::IsTrue(zeroByte == reg.C);
			Assert::IsTrue(zeroWord == reg.BC);
			Assert::IsTrue(zeroByte == reg.D);
			Assert::IsTrue(zeroByte == reg.E);
			Assert::IsTrue(zeroWord == reg.DE);
			Assert::IsTrue(zeroByte == reg.H);
			Assert::IsTrue(zeroByte == reg.L);
			Assert::IsTrue(zeroWord == reg.HL);

			// test setting the full 16-bit register also sets the 8-bit registers
			uint16_t value = 0xABCD;
			uint8_t value_h = (value & 0xFF00) >> 8;
			uint8_t value_l = (value & 0x00FF);

			reg.AF = value;
			Assert::IsTrue(value_h == reg.A);
			Assert::IsTrue(value_h == reg.Accumulator);
			Assert::IsTrue(value_l == reg.F);
			Assert::IsTrue(value_l == reg.Flags);

			reg.BC = value;
			Assert::IsTrue(value_h == reg.B);
			Assert::IsTrue(value_l == reg.C);

			reg.DE = value;
			Assert::IsTrue(value_h == reg.D);
			Assert::IsTrue(value_l == reg.E);

			reg.HL = value;
			Assert::IsTrue(value_h == reg.H);
			Assert::IsTrue(value_l == reg.L);

			// test setting the 8-bit registers also affects the 16-bit registers
			uint8_t value2_h = 0x12;
			uint8_t value2_l = 0x34;
			uint16_t value2 = (value2_h << 8) | value2_l;

			reg.A = value2_h;
			reg.F = value2_l;
			Assert::IsTrue(value2_h == reg.Accumulator);
			Assert::IsTrue(value2_l == reg.Flags);
			Assert::IsTrue(value2 == reg.AF);

			reg.B = value2_h;
			reg.C = value2_l;
			Assert::IsTrue(value2 == reg.BC);

			reg.D = value2_h;
			reg.E = value2_l;
			Assert::IsTrue(value2 == reg.DE);

			reg.H = value2_h;
			reg.L = value2_l;
			Assert::IsTrue(value2 == reg.HL);
		}

		TEST_METHOD(TestRegistersFlags)
		{
			Registers reg;
			static const uint8_t ZERO_FLAG = 0b10000000;
			static const uint8_t SUBTRACT_FLAG = 0b01000000;
			static const uint8_t HALF_CARRY_FLAG = 0b00100000;
			static const uint8_t CARRY_FLAG = 0b00010000;

			// values should initialize to 0 (false)
			Assert::IsFalse(reg.GetZeroFlag());
			Assert::IsFalse(reg.GetSubtractFlag());
			Assert::IsFalse(reg.GetHalfCarryFlag());
			Assert::IsFalse(reg.GetCarryFlag());

			// test setting flags
			reg.SetZeroFlag();
			Assert::IsTrue(reg.GetZeroFlag());
			Assert::IsTrue(ZERO_FLAG == (ZERO_FLAG & reg.Flags));

			reg.SetSubtractFlag();
			Assert::IsTrue(reg.GetSubtractFlag());
			Assert::IsTrue(SUBTRACT_FLAG == (SUBTRACT_FLAG & reg.Flags));

			reg.SetHalfCarryFlag();
			Assert::IsTrue(reg.GetHalfCarryFlag());
			Assert::IsTrue(HALF_CARRY_FLAG == (HALF_CARRY_FLAG & reg.Flags));

			reg.SetCarryFlag();
			Assert::IsTrue(reg.GetCarryFlag());
			Assert::IsTrue(CARRY_FLAG == (CARRY_FLAG & reg.Flags));

			// test resetting flags
			reg.ResetZeroFlag();
			Assert::IsFalse(reg.GetZeroFlag());
			Assert::IsFalse(ZERO_FLAG == (ZERO_FLAG & reg.Flags));

			reg.ResetSubtractFlag();
			Assert::IsFalse(reg.GetSubtractFlag());
			Assert::IsFalse(SUBTRACT_FLAG == (SUBTRACT_FLAG & reg.Flags));

			reg.ResetHalfCarryFlag();
			Assert::IsFalse(reg.GetHalfCarryFlag());
			Assert::IsFalse(HALF_CARRY_FLAG == (HALF_CARRY_FLAG & reg.Flags));

			reg.ResetCarryFlag();
			Assert::IsFalse(reg.GetCarryFlag());
			Assert::IsFalse(CARRY_FLAG == (CARRY_FLAG & reg.Flags));

			// test assigning flags
			reg.AssignZeroFlag(true);
			Assert::IsTrue(reg.GetZeroFlag());
			Assert::IsTrue(ZERO_FLAG ==( ZERO_FLAG & reg.Flags));

			reg.AssignSubtractFlag(true);
			Assert::IsTrue(reg.GetSubtractFlag());
			Assert::IsTrue(SUBTRACT_FLAG == (SUBTRACT_FLAG & reg.Flags));

			reg.AssignHalfCarryFlag(true);
			Assert::IsTrue(reg.GetHalfCarryFlag());
			Assert::IsTrue(HALF_CARRY_FLAG == (HALF_CARRY_FLAG & reg.Flags));

			reg.AssignCarryFlag(true);
			Assert::IsTrue(reg.GetCarryFlag());
			Assert::IsTrue(CARRY_FLAG == (CARRY_FLAG & reg.Flags));
		}
	};
}