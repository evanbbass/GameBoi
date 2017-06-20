#include "pch.h"
#include "CartridgeManaged.h"

using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	CartridgeManaged::CartridgeManaged() :
		mCartridge(new Cartridge())
	{
	}

	CartridgeManaged::CartridgeManaged(String^ filename) :
		mCartridge(new Cartridge(msclr::interop::marshal_as<std::string>(filename)))
	{
	}

	CartridgeManaged::CartridgeManaged(Cartridge& unmanagedCartridge) :
		mCartridge(&unmanagedCartridge)
	{
	}

	Cartridge& CartridgeManaged::GetUnmanaged()
	{
		return *mCartridge;
	}

	void CartridgeManaged::ReadFromFile(String^ filename)
	{
		mCartridge->ReadFromFile(msclr::interop::marshal_as<std::string>(filename));
	}

	void CartridgeManaged::Reset()
	{
		mCartridge->Reset();
	}

	Byte CartridgeManaged::ReadByte(UInt16 address)
	{
		return mCartridge->ReadByte(address);
	}

	UInt16 CartridgeManaged::ReadWord(UInt16 address)
	{
		return mCartridge->ReadWord(address);
	}

	void CartridgeManaged::WriteByte(UInt16 address, Byte value)
	{
		mCartridge->WriteByte(address, value);
	}

	void CartridgeManaged::WriteWord(UInt16 address, UInt16 value)
	{
		mCartridge->WriteWord(address, value);
	}

	void CartridgeManaged::SetSwitchableBankIndex(uint32_t index)
	{
		mCartridge->SetSwitchableBankIndex(index);
	}

	String^ CartridgeManaged::GetGameTitle()
	{
		return gcnew String(mCartridge->GetGameTitle().c_str());
	}

	Cartridge::CartridgeType CartridgeManaged::GetCartrideType()
	{
		return mCartridge->GetCartrideType();
	}

	bool CartridgeManaged::GetColorSupport()
	{
		return mCartridge->GetColorSupport();
	}

	bool CartridgeManaged::GetSuperSupport()
	{
		return mCartridge->GetSuperSupport();
	}

	String^ CartridgeManaged::DisassembleRom(UInt16 startAddress, UInt16 length)
	{
		return gcnew String(mCartridge->DisassembleRom(startAddress, length).c_str());
	}

	void CartridgeManaged::DisassebleRomToFile(String^ filename, UInt16 startAddress, UInt16 length)
	{
		mCartridge->DisassebleRomToFile(msclr::interop::marshal_as<std::string>(filename), startAddress, length);
	}
}