#include "pch.h"
#include "MemoryMapManaged.h"

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

	MemoryMap& MemoryMapManaged::GetUnmanaged()
	{
		return *mMemoryMap;
	}

	void MemoryMapManaged::Reset()
	{
		mMemoryMap->Reset();
	}

	Byte MemoryMapManaged::ReadByte(UInt16 address)
	{
		return mMemoryMap->ReadByte(address);
	}

	UInt16 MemoryMapManaged::ReadWord(UInt16 address)
	{
		return mMemoryMap->ReadWord(address);
	}

	void MemoryMapManaged::WriteByte(UInt16 address, Byte value)
	{
		mMemoryMap->WriteByte(address, value);
	}

	void MemoryMapManaged::WriteWord(UInt16 address, UInt16 value)
	{
		mMemoryMap->WriteWord(address, value);
	}

	void MemoryMapManaged::LoadCartridgeFromFile(String^ fileName)
	{
		mMemoryMap->LoadCartridgeFromFile(msclr::interop::marshal_as<std::string>(fileName));
	}

	CartridgeManaged^ MemoryMapManaged::GetCartridge()
	{
		return gcnew CartridgeManaged(mMemoryMap->GetCartridge());
	}
}
