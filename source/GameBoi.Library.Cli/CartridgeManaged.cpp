#include "pch.h"
#include "CartridgeManaged.h"

using namespace std;
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

	Cartridge& CartridgeManaged::Unmanaged::get()
	{
		return *mCartridge;
	}

	void CartridgeManaged::ReadFromFile(String^ filename)
	{
		try
		{
			mCartridge->ReadFromFile(msclr::interop::marshal_as<std::string>(filename));
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void CartridgeManaged::Reset()
	{
		mCartridge->Reset();
	}

	Byte CartridgeManaged::ReadByte(UInt16 address)
	{
		try
		{
			return mCartridge->ReadByte(address);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	UInt16 CartridgeManaged::ReadWord(UInt16 address)
	{
		try
		{
			return mCartridge->ReadWord(address);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void CartridgeManaged::WriteByte(UInt16 address, Byte value)
	{
		try
		{
			mCartridge->WriteByte(address, value);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void CartridgeManaged::WriteWord(UInt16 address, UInt16 value)
	{
		try
		{
			mCartridge->WriteWord(address, value);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	String^ CartridgeManaged::GameTitle::get()
	{
		return gcnew String(mCartridge->GetGameTitle().c_str());
	}

	CartridgeTypeManaged CartridgeManaged::CartrideType::get()
	{
		return static_cast<CartridgeTypeManaged>(mCartridge->GetCartrideType());
	}

	bool CartridgeManaged::ColorSupport::get()
	{
		return mCartridge->GetColorSupport();
	}

	bool CartridgeManaged::SuperSupport::get()
	{
		return mCartridge->GetSuperSupport();
	}

	String^ CartridgeManaged::DisassembleRom(UInt16 startAddress, UInt16 length)
	{
		try
		{
			return gcnew String(mCartridge->DisassembleRom(startAddress, length).c_str());
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void CartridgeManaged::DisassebleRomToFile(String^ filename, UInt16 startAddress, UInt16 length)
	{
		try
		{
			mCartridge->DisassebleRomToFile(msclr::interop::marshal_as<std::string>(filename), startAddress, length);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}
}