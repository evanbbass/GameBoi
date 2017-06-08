#include "pch.h"
#include "Registers.h"

namespace GameBoi
{
	Registers::Registers() :
		AF(0), BC(0), DE(0), HL(0), SP(0xFFFE), PC(0x100)
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
		return Flags & ZERO_FLAG;
	}

	void Registers::SetZeroFlag()
	{
		Flags |= ZERO_FLAG;
	}

	void Registers::ResetZeroFlag()
	{
		Flags &= ~ZERO_FLAG;
	}

	void Registers::AssignZeroFlag(bool value)
	{
		Flags = value ? Flags | ZERO_FLAG : Flags & ~ZERO_FLAG;
	}

	bool Registers::GetSubtractFlag() const
	{
		return Flags & SUBTRACT_FLAG;
	}

	void Registers::SetSubtractFlag()
	{
		Flags |= SUBTRACT_FLAG;
	}

	void Registers::ResetSubtractFlag()
	{
		Flags &= ~SUBTRACT_FLAG;
	}

	void Registers::AssignSubtractFlag(bool value)
	{
		Flags = value ? Flags | SUBTRACT_FLAG : Flags & ~SUBTRACT_FLAG;
	}

	bool Registers::GetHalfCarryFlag() const
	{
		return Flags & HALF_CARRY_FLAG;
	}

	void Registers::SetHalfCarryFlag()
	{
		Flags |= HALF_CARRY_FLAG;
	}

	void Registers::ResetHalfCarryFlag()
	{
		Flags &= ~HALF_CARRY_FLAG;
	}

	void Registers::AssignHalfCarryFlag(bool value)
	{
		Flags = value ? Flags | HALF_CARRY_FLAG : Flags & ~HALF_CARRY_FLAG;
	}

	bool Registers::GetCarryFlag() const
	{
		return Flags & CARRY_FLAG;
	}

	void Registers::SetCarryFlag()
	{
		Flags |= CARRY_FLAG;
	}

	void Registers::ResetCarryFlag()
	{
		Flags &= ~CARRY_FLAG;
	}

	void Registers::AssignCarryFlag(bool value)
	{
		Flags = value ? Flags | CARRY_FLAG : Flags & ~CARRY_FLAG;
	}
}