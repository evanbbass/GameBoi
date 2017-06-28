#pragma once

namespace GameBoiManaged
{
	public enum class CartridgeTypeManaged : System::Byte
	{
		ROM_ONLY = 0x00,
		ROM_MBC1 = 0x01,
		ROM_MBC1_RAM = 0x02,
		ROM_MBC1_RAM_BATT = 0x03,
		ROM_MBC2 = 0x05,
		ROM_MBC2_BATTERY = 0x06,
		ROM_RAM = 0x08,
		ROM_RAM_BATTERY = 0x09,
		ROM_MMM01 = 0x0B,
		ROM_MMM01_SRAM = 0x0C,
		ROM_MMM01_SRAM_BATT = 0x0D,
		ROM_MBC3_TIMER_BATT = 0x0F,
		ROM_MBC3_TIMER_RAM_BATT = 0x10,
		ROM_MBC3 = 0x11,
		ROM_MBC3_RAM = 0x12,
		ROM_MBC3_RAM_BATT = 0x13,
		ROM_MBC5 = 0x19,
		ROM_MBC5_RAM = 0x1A,
		ROM_MBC5_RAM_BATT = 0x1B,
		ROM_MBC5_RUMBLE = 0x1C,
		ROM_MBC5_RUMBLE_SRAM = 0x1D,
		ROM_MBC5_RUMBLE_SRAM_BATT = 0x1E,
		Bandai_TAMA5 = 0xFD,
		Pocket_Camera = 0x1F,
		Hudson_HuC_3 = 0xFE,
		Hudson_HuC_1 = 0xFF
	};
}