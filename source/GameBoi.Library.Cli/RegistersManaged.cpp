#include "pch.h"
#include "RegistersManaged.h"

using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	RegistersManaged::RegistersManaged() :
		mRegisters(new Registers())
	{
	}

	RegistersManaged::RegistersManaged(Registers& unmanagedRegisters) :
		mRegisters(&unmanagedRegisters)
	{
	}

	Registers& RegistersManaged::GetUnmanaged()
	{
		return *mRegisters;
	}

	Byte RegistersManaged::A::get()
	{
		return mRegisters->A;
	}

	void RegistersManaged::A::set(Byte value)
	{
		mRegisters->A = value;
	}

	Byte RegistersManaged::F::get()
	{
		return mRegisters->F;
	}

	void RegistersManaged::F::set(Byte value)
	{
		mRegisters->F = value;
	}

	UInt16 RegistersManaged::AF::get()
	{
		return mRegisters->AF;
	}

	void RegistersManaged::AF::set(UInt16 value)
	{
		mRegisters->AF = value;
	}

	Byte RegistersManaged::B::get()
	{
		return mRegisters->B;
	}

	void RegistersManaged::B::set(Byte value)
	{
		mRegisters->B = value;
	}

	Byte RegistersManaged::C::get()
	{
		return mRegisters->C;
	}

	void RegistersManaged::C::set(Byte value)
	{
		mRegisters->C = value;
	}

	UInt16 RegistersManaged::BC::get()
	{
		return mRegisters->BC;
	}

	void RegistersManaged::BC::set(UInt16 value)
	{
		mRegisters->BC = value;
	}

	Byte RegistersManaged::D::get()
	{
		return mRegisters->D;
	}

	void RegistersManaged::D::set(Byte value)
	{
		mRegisters->D = value;
	}

	Byte RegistersManaged::E::get()
	{
		return mRegisters->E;
	}

	void RegistersManaged::E::set(Byte value)
	{
		mRegisters->E = value;
	}

	UInt16 RegistersManaged::DE::get()
	{
		return mRegisters->DE;
	}

	void RegistersManaged::DE::set(UInt16 value)
	{
		mRegisters->DE = value;
	}

	Byte RegistersManaged::H::get()
	{
		return mRegisters->H;
	}

	void RegistersManaged::H::set(Byte value)
	{
		mRegisters->H = value;
	}

	Byte RegistersManaged::L::get()
	{
		return mRegisters->L;
	}

	void RegistersManaged::L::set(Byte value)
	{
		mRegisters->L = value;
	}

	UInt16 RegistersManaged::HL::get()
	{
		return mRegisters->HL;
	}

	void RegistersManaged::HL::set(UInt16 value)
	{
		mRegisters->HL = value;
	}

	UInt16 RegistersManaged::SP::get()
	{
		return mRegisters->SP;
	}

	void RegistersManaged::SP::set(UInt16 value)
	{
		mRegisters->SP = value;
	}

	UInt16 RegistersManaged::PC::get()
	{
		return mRegisters->PC;
	}

	void RegistersManaged::PC::set(UInt16 value)
	{
		mRegisters->PC = value;
	}

	void RegistersManaged::Reset()
	{
		mRegisters->Reset();
	}

	bool RegistersManaged::ZeroFlag::get()
	{
		return mRegisters->GetZeroFlag();
	}

	void RegistersManaged::ZeroFlag::set(bool value)
	{
		mRegisters->AssignZeroFlag(value);
	}

	void RegistersManaged::SetZeroFlag()
	{
		mRegisters->SetZeroFlag();
	}

	void RegistersManaged::ResetZeroFlag()
	{
		mRegisters->ResetZeroFlag();
	}

	bool RegistersManaged::SubtractFlag::get()
	{
		return mRegisters->GetSubtractFlag();
	}

	void RegistersManaged::SubtractFlag::set(bool value)
	{
		mRegisters->AssignSubtractFlag(value);
	}

	void RegistersManaged::SetSubtractFlag()
	{
		mRegisters->SetSubtractFlag();
	}

	void RegistersManaged::ResetSubtractFlag()
	{
		mRegisters->ResetSubtractFlag();
	}

	bool RegistersManaged::HalfCarryFlag::get()
	{
		return mRegisters->GetHalfCarryFlag();
	}

	void RegistersManaged::HalfCarryFlag::set(bool value)
	{
		mRegisters->AssignHalfCarryFlag(value);
	}

	void RegistersManaged::SetHalfCarryFlag()
	{
		mRegisters->SetHalfCarryFlag();
	}

	void RegistersManaged::ResetHalfCarryFlag()
	{
		mRegisters->ResetHalfCarryFlag();
	}

	bool RegistersManaged::CarryFlag::get()
	{
		return mRegisters->GetCarryFlag();
	}

	void RegistersManaged::CarryFlag::set(bool value)
	{
		mRegisters->AssignCarryFlag(value);
	}

	void RegistersManaged::SetCarryFlag()
	{
		mRegisters->SetCarryFlag();
	}

	void RegistersManaged::ResetCarryFlag()
	{
		mRegisters->ResetCarryFlag();
	}
}
