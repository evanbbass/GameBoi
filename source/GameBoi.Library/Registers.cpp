#include "pch.h"
#include "Registers.h"
#include "Utilities.h"

namespace GameBoi
{
	Registers::Registers() :
		AF(0x01B0), BC(0x0013), DE(0x00D8), HL(0x014D), SP(0xFFFE), PC(0x100)
	{
	}

	void Registers::Reset()
	{
		AF = 0;
		BC = 0;
		DE = 0;
		HL = 0;
		SP = 0xFFFE;
		PC = 0x100;
	}

	bool Registers::GetZeroFlag() const
	{
		return Utilities::TestBit(Flags, ZeroBit);
	}

	void Registers::SetZeroFlag()
	{
		Flags = Utilities::SetBit(Flags, ZeroBit);
	}

	void Registers::ResetZeroFlag()
	{
		Flags = Utilities::ResetBit(Flags, ZeroBit);
	}

	void Registers::AssignZeroFlag(bool value)
	{
		Flags = value ? Utilities::SetBit(Flags, ZeroBit) : Utilities::ResetBit(Flags, ZeroBit);
	}

	bool Registers::GetSubtractFlag() const
	{
		return Utilities::TestBit(Flags, SubtractBit);
	}

	void Registers::SetSubtractFlag()
	{
		Flags = Utilities::SetBit(Flags, SubtractBit);
	}

	void Registers::ResetSubtractFlag()
	{
		Flags = Utilities::ResetBit(Flags, SubtractBit);
	}

	void Registers::AssignSubtractFlag(bool value)
	{
		Flags = value ? Utilities::SetBit(Flags, SubtractBit) : Utilities::ResetBit(Flags, SubtractBit);
	}

	bool Registers::GetHalfCarryFlag() const
	{
		return Utilities::TestBit(Flags, HalfCarryBit);
	}

	void Registers::SetHalfCarryFlag()
	{
		Flags = Utilities::SetBit(Flags, HalfCarryBit);
	}

	void Registers::ResetHalfCarryFlag()
	{
		Flags = Utilities::ResetBit(Flags, HalfCarryBit);
	}

	void Registers::AssignHalfCarryFlag(bool value)
	{
		Flags = value ? Utilities::SetBit(Flags, HalfCarryBit) : Utilities::ResetBit(Flags, HalfCarryBit);
	}

	bool Registers::GetCarryFlag() const
	{
		return Utilities::TestBit(Flags, CarryBit);
	}

	void Registers::SetCarryFlag()
	{
		Flags = Utilities::SetBit(Flags, CarryBit);
	}

	void Registers::ResetCarryFlag()
	{
		Flags = Utilities::ResetBit(Flags, CarryBit);
	}

	void Registers::AssignCarryFlag(bool value)
	{
		Flags = value ? Utilities::SetBit(Flags, CarryBit) : Utilities::ResetBit(Flags, CarryBit);
	}
}
