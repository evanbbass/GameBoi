#include "pch.h"
#include "CppUnitTest.h"
#include "MemoryMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace GameBoi;

namespace GameBoiLibraryTest
{
	TEST_CLASS(TestGraphics)
	{
	public:

		TEST_METHOD(TestGraphicsPallet)
		{
			Pallet pallet;
			uint8_t value = 0b11100100; // pallet is 11, 10, 01, 00
			pallet.SetPallet(value);
			Assert::AreEqual(value, pallet.GetPallet());

			Display::Color color0 = pallet.GetPalletColor(0b00);
			Display::Color color1 = pallet.GetPalletColor(0b01);
			Display::Color color2 = pallet.GetPalletColor(0b10);
			Display::Color color3 = pallet.GetPalletColor(0b11);

			Assert::AreEqual(static_cast<uint8_t>(Display::Color::White), static_cast<uint8_t>(color0));
			Assert::AreEqual(static_cast<uint8_t>(Display::Color::LightGray), static_cast<uint8_t>(color1));
			Assert::AreEqual(static_cast<uint8_t>(Display::Color::DarkGray), static_cast<uint8_t>(color2));
			Assert::AreEqual(static_cast<uint8_t>(Display::Color::Black), static_cast<uint8_t>(color3));
		}
	};
}