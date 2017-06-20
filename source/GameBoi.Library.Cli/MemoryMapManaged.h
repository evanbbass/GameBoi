#pragma once

#include "CartridgeManaged.h"
#include "MemoryMap.h"

namespace GameBoiManaged
{
	public ref class MemoryMapManaged
	{
	public:
		MemoryMapManaged();
		MemoryMapManaged(GameBoi::MemoryMap& unmanagedMemoryMap);

		GameBoi::MemoryMap& GetUnmanaged();

		void Reset();

		System::Byte ReadByte(System::UInt16 address);
		System::UInt16 ReadWord(System::UInt16 address);
		void WriteByte(System::UInt16 address, System::Byte value);
		void WriteWord(System::UInt16 address, System::UInt16 value);

		void LoadCartridgeFromFile(System::String^ fileName);
		CartridgeManaged^ GetCartridge();

	private:
		GameBoi::MemoryMap* mMemoryMap;
	};
}