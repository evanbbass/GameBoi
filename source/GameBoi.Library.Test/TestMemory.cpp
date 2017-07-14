#include "pch.h"
#include "CppUnitTest.h"
#include "MemoryMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace GameBoi;

namespace GameBoiLibraryTest
{		
	TEST_CLASS(TestMemory)
	{
	public:
		
		TEST_METHOD(TestCartridgeIndexOperator)
		{
			Cartridge cart;

			uint8_t zero = 0;
			uint16_t bank0Index = 0x1234;
			uint16_t bank1Index = 0x5678;
			uint16_t outOfRangeIndex = 0x9ABC;

			Assert::AreEqual(zero, cart.ReadByte(bank0Index));
			Assert::AreEqual(zero, cart.ReadByte(bank1Index));
			Assert::ExpectException<exception>([&cart, outOfRangeIndex] { cart.ReadByte(outOfRangeIndex); });

			uint8_t value = 0xFA;
			cart.WriteByte(bank0Index, value);
			cart.WriteByte(bank1Index, value);

			Assert::AreEqual(value, cart.ReadByte(bank0Index));
			Assert::AreEqual(value, cart.ReadByte(bank1Index));

			const Cartridge& constCart = cart;
			uint8_t value2 = 0xBC;
			cart.WriteByte(bank0Index, value2);
			cart.WriteByte(bank1Index, value2);

			Assert::AreEqual(value2, constCart.ReadByte(bank0Index));
			Assert::AreEqual(value2, constCart.ReadByte(bank1Index));

			cart.Reset();
			Assert::AreEqual(zero, cart.ReadByte(bank0Index));
			Assert::AreEqual(zero, cart.ReadByte(bank1Index));
		}

		TEST_METHOD(TestMemoryReadWriteByte)
		{
			MemoryMap mem;

			uint8_t zero = 0;

			uint16_t cartridgeIndex = 0x1234;
			uint16_t vramIndex = 0x8500;
			uint16_t sramIndex = 0xA600;
			uint16_t wramIndex = 0xC800;
			uint16_t wramEchoIndex = 0xE100;
			uint16_t oamIndex = 0xFE80;
			uint16_t unusable0Index = 0xFEF0;
			uint16_t ioIndex = 0xFF30;
			uint16_t unusable1Index = 0xFF70;
			uint16_t internalRamIndex = 0xFFF0;

			Assert::AreEqual(zero, mem.ReadByte(cartridgeIndex));
			Assert::AreEqual(zero, mem.ReadByte(vramIndex));
			Assert::AreEqual(zero, mem.ReadByte(sramIndex));
			Assert::AreEqual(zero, mem.ReadByte(wramIndex));
			Assert::AreEqual(zero, mem.ReadByte(wramEchoIndex));
			Assert::AreEqual(zero, mem.ReadByte(oamIndex));
			Assert::ExpectException<exception>([&mem, unusable0Index] { mem.ReadByte(unusable0Index); });
			Assert::AreEqual(zero, mem.ReadByte(ioIndex));
			Assert::ExpectException<exception>([&mem, unusable1Index] { mem.ReadByte(unusable1Index); });
			Assert::AreEqual(zero, mem.ReadByte(internalRamIndex));

			uint8_t value = 0xCD;

			mem.WriteByte(cartridgeIndex, value);
			mem.WriteByte(vramIndex, value);
			mem.WriteByte(sramIndex, value);
			mem.WriteByte(wramIndex, value);
			mem.WriteByte(wramEchoIndex, value);
			mem.WriteByte(oamIndex, value);
			Assert::ExpectException<exception>([&mem, unusable0Index, value] { mem.WriteByte(unusable0Index, value); });
			mem.WriteByte(ioIndex, value);
			Assert::ExpectException<exception>([&mem, unusable1Index, value] { mem.WriteByte(unusable1Index, value); });
			mem.WriteByte(internalRamIndex, value);

			Assert::AreEqual(value, mem.ReadByte(cartridgeIndex));
			Assert::AreEqual(value, mem.ReadByte(vramIndex));
			Assert::AreEqual(value, mem.ReadByte(sramIndex));
			Assert::AreEqual(value, mem.ReadByte(wramIndex));
			Assert::AreEqual(value, mem.ReadByte(wramEchoIndex));
			Assert::AreEqual(value, mem.ReadByte(oamIndex));
			Assert::AreEqual(value, mem.ReadByte(ioIndex));
			Assert::AreEqual(value, mem.ReadByte(internalRamIndex));

			const MemoryMap& constMem = mem;
			Assert::AreEqual(value, constMem.ReadByte(cartridgeIndex));
			Assert::AreEqual(value, constMem.ReadByte(vramIndex));
			Assert::AreEqual(value, constMem.ReadByte(sramIndex));
			Assert::AreEqual(value, constMem.ReadByte(wramIndex));
			Assert::AreEqual(value, constMem.ReadByte(wramEchoIndex));
			Assert::AreEqual(value, constMem.ReadByte(oamIndex));
			Assert::AreEqual(value, constMem.ReadByte(ioIndex));
			Assert::AreEqual(value, constMem.ReadByte(internalRamIndex));

			mem.Reset();
			Assert::AreEqual(zero, mem.ReadByte(vramIndex));
			Assert::AreEqual(zero, mem.ReadByte(sramIndex));
			Assert::AreEqual(zero, mem.ReadByte(wramIndex));
			Assert::AreEqual(zero, mem.ReadByte(wramEchoIndex));
			Assert::AreEqual(zero, mem.ReadByte(oamIndex));
			Assert::AreEqual(zero, mem.ReadByte(ioIndex));
			Assert::AreEqual(zero, mem.ReadByte(internalRamIndex));
		}

		TEST_METHOD(TestMemoryReadWriteWord)
		{
			MemoryMap mem;

			uint16_t zero = 0;

			uint16_t cartridgeIndex = 0x1234;
			uint16_t vramIndex = 0x8500;
			uint16_t sramIndex = 0xA600;
			uint16_t wramIndex = 0xC800;
			uint16_t wramEchoIndex = 0xE100;
			uint16_t oamIndex = 0xFE80;
			uint16_t ioIndex = 0xFF30;
			uint16_t internalRamIndex = 0xFFF0;

			Assert::IsTrue(zero == mem.ReadWord(cartridgeIndex));
			Assert::IsTrue(zero == mem.ReadWord(vramIndex));
			Assert::IsTrue(zero == mem.ReadWord(sramIndex));
			Assert::IsTrue(zero == mem.ReadWord(wramIndex));
			Assert::IsTrue(zero == mem.ReadWord(wramEchoIndex));
			Assert::IsTrue(zero == mem.ReadWord(oamIndex));
			Assert::IsTrue(zero == mem.ReadWord(ioIndex));
			Assert::IsTrue(zero == mem.ReadWord(internalRamIndex));

			uint16_t value = 0xABCD;
			uint8_t value_h = (value & 0xFF00) >> 8;
			uint8_t value_l = (value & 0x00FF);

			mem.WriteWord(cartridgeIndex, value);
			mem.WriteWord(vramIndex, value);
			mem.WriteWord(sramIndex, value);
			mem.WriteWord(wramIndex, value);
			mem.WriteWord(wramEchoIndex, value);
			mem.WriteWord(oamIndex, value);
			mem.WriteWord(ioIndex, value);
			mem.WriteWord(internalRamIndex, value);

			//Assert::IsTrue(value == mem.ReadWord(cartridgeIndex));
			Assert::IsTrue(value == mem.ReadWord(vramIndex));
			Assert::IsTrue(value == mem.ReadWord(sramIndex));
			Assert::IsTrue(value == mem.ReadWord(wramIndex));
			Assert::IsTrue(value == mem.ReadWord(wramEchoIndex));
			Assert::IsTrue(value == mem.ReadWord(oamIndex));
			Assert::IsTrue(value == mem.ReadWord(ioIndex));
			Assert::IsTrue(value == mem.ReadWord(internalRamIndex));

			Assert::AreEqual(value_l, mem.ReadByte(cartridgeIndex));
			Assert::AreEqual(value_h, mem.ReadByte(cartridgeIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(vramIndex));
			Assert::AreEqual(value_h, mem.ReadByte(vramIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(sramIndex));
			Assert::AreEqual(value_h, mem.ReadByte(sramIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(wramIndex));
			Assert::AreEqual(value_h, mem.ReadByte(wramIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(wramEchoIndex));
			Assert::AreEqual(value_h, mem.ReadByte(wramEchoIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(oamIndex));
			Assert::AreEqual(value_h, mem.ReadByte(oamIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(ioIndex));
			Assert::AreEqual(value_h, mem.ReadByte(ioIndex + 1));
			Assert::AreEqual(value_l, mem.ReadByte(internalRamIndex));
			Assert::AreEqual(value_h, mem.ReadByte(internalRamIndex + 1));

			const MemoryMap& constMem = mem;
			Assert::IsTrue(value == constMem.ReadWord(cartridgeIndex));
			Assert::IsTrue(value == constMem.ReadWord(vramIndex));
			Assert::IsTrue(value == constMem.ReadWord(sramIndex));
			Assert::IsTrue(value == constMem.ReadWord(wramIndex));
			Assert::IsTrue(value == constMem.ReadWord(wramEchoIndex));
			Assert::IsTrue(value == constMem.ReadWord(oamIndex));
			Assert::IsTrue(value == constMem.ReadWord(ioIndex));
			Assert::IsTrue(value == constMem.ReadWord(internalRamIndex));

			mem.Reset();
			Assert::IsTrue(zero == mem.ReadWord(vramIndex));
			Assert::IsTrue(zero == mem.ReadWord(sramIndex));
			Assert::IsTrue(zero == mem.ReadWord(wramIndex));
			Assert::IsTrue(zero == mem.ReadWord(wramEchoIndex));
			Assert::IsTrue(zero == mem.ReadWord(oamIndex));
			Assert::IsTrue(zero == mem.ReadWord(ioIndex));
			Assert::IsTrue(zero == mem.ReadWord(internalRamIndex));
		}

		TEST_METHOD(TestMemoryWorkingRAMEcho)
		{
			MemoryMap mem;

			uint16_t wramIndex = 0xC100;
			uint16_t wramEchoIndex = wramIndex + 0x2000;

			uint8_t value1 = 0xAB;
			mem.WriteByte(wramIndex, value1);
			Assert::AreEqual(value1, mem.ReadByte(wramIndex));
			Assert::AreEqual(value1, mem.ReadByte(wramEchoIndex));

			uint8_t value2 = 0xCD;
			mem.WriteByte(wramEchoIndex, value2);
			Assert::AreEqual(value2, mem.ReadByte(wramIndex));
			Assert::AreEqual(value2, mem.ReadByte(wramEchoIndex));
		}
	};
}