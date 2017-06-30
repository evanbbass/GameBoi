#include "pch.h"
#include "MemoryMapManaged.h"

using namespace std;
using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	MemoryMapManaged::MemoryMapManaged() :
		mMemoryMap(new MemoryMap())
	{
	}

	MemoryMapManaged::MemoryMapManaged(GameBoi::MemoryMap& unmanagedMemoryMap) :
		mMemoryMap(&unmanagedMemoryMap)
	{
	}

	MemoryMap& MemoryMapManaged::Unmanaged::get()
	{
		return *mMemoryMap;
	}

	void MemoryMapManaged::Reset()
	{
		mMemoryMap->Reset();
	}

	Byte MemoryMapManaged::ReadByte(UInt16 address)
	{
		try
		{
			return mMemoryMap->ReadByte(address);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	UInt16 MemoryMapManaged::ReadWord(UInt16 address)
	{
		try
		{
			return mMemoryMap->ReadWord(address);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void MemoryMapManaged::WriteByte(UInt16 address, Byte value)
	{
		try
		{
			mMemoryMap->WriteByte(address, value);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void MemoryMapManaged::WriteWord(UInt16 address, UInt16 value)
	{
		try
		{
			mMemoryMap->WriteWord(address, value);
		}
		catch (exception& ex)
		{
			throw gcnew Exception(gcnew String(ex.what()));
		}
	}

	void MemoryMapManaged::LoadCartridgeFromFile(String^ fileName)
	{
		mMemoryMap->LoadCartridgeFromFile(msclr::interop::marshal_as<std::string>(fileName));
	}

	CartridgeManaged^ MemoryMapManaged::Cartridge::get()
	{
		return gcnew CartridgeManaged(mMemoryMap->GetCartridge());
	}
}
