#pragma once

#include "Cartridge.h"

namespace GameBoiManaged
{
	public ref class CartridgeManaged
	{
	public:
		CartridgeManaged();
		explicit CartridgeManaged(System::String^ filename);
		CartridgeManaged(GameBoi::Cartridge& unmanagedCartridge);

		property GameBoi::Cartridge& Unmanaged { GameBoi::Cartridge& get(); }

		void ReadFromFile(System::String^ filename);
		void Reset();

		System::Byte ReadByte(System::UInt16 address);
		System::UInt16  ReadWord(System::UInt16  address);
		void WriteByte(System::UInt16  address, System::Byte value);
		void WriteWord(System::UInt16  address, System::UInt16  value);

		void SetSwitchableBankIndex(uint32_t index);

		property System::String^ GameTitle { System::String^ get(); }
		property GameBoi::Cartridge::CartridgeType CartrideType { GameBoi::Cartridge::CartridgeType get(); }
		property bool ColorSupport { bool get(); }
		property bool SuperSupport { bool get(); }

		System::String^ DisassembleRom(System::UInt16 startAddress, System::UInt16 length);
		void DisassebleRomToFile(System::String^ filename, System::UInt16 startAddress, System::UInt16 length);

	private:
		GameBoi::Cartridge* mCartridge;
	};
}