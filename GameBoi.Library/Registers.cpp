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

	inline bool Registers::GetZeroFlag() const
	{
		return Flags & ZERO_FLAG;
	}

	inline void Registers::SetZeroFlag()
	{
		Flags |= ZERO_FLAG;
	}

	inline void Registers::ClearZeroFlag()
	{
		Flags &= ~ZERO_FLAG;
	}

	inline bool Registers::GetSubtractFlag() const
	{
		return Flags & SUBTRACT_FLAG;
	}

	inline void Registers::SetSubtractFlag()
	{
		Flags |= SUBTRACT_FLAG;
	}

	inline void Registers::ClearSubtractFlag()
	{
		Flags &= ~SUBTRACT_FLAG;
	}

	inline bool Registers::GetHalfCarryFlag() const
	{
		return Flags & HALF_CARRY_FLAG;
	}

	inline void Registers::SetHalfCarryFlag()
	{
		Flags |= HALF_CARRY_FLAG;
	}

	inline void Registers::ClearHalfCarryFlag()
	{
		Flags &= ~HALF_CARRY_FLAG;
	}

	inline bool Registers::GetCarryFlag() const
	{
		return Flags & CARRY_FLAG;
	}

	inline void Registers::SetCarryFlag()
	{
		Flags |= CARRY_FLAG;
	}

	inline void Registers::ClearCarryFlag()
	{
		Flags &= ~CARRY_FLAG;
	}
}