#pragma once
#include <cstdint>

class Utilities abstract final
{
public:
	static uint8_t SetBit(uint8_t value, uint8_t bit)
	{
		return value | (1 << bit);
	}

	static uint16_t SetBit(uint16_t value, uint8_t bit)
	{
		return value | (1 << bit);
	}

	static uint8_t ResetBit(uint8_t value, uint8_t bit)
	{
		return value & ~(1 << bit);
	}

	static uint16_t ResetBit(uint16_t value, uint8_t bit)
	{
		return value & ~(1 << bit);
	}

	static bool TestBit(uint8_t value, uint8_t bit)
	{
		return (value & (1 << bit)) != 0;
	}

	static bool TestBit(uint16_t value, uint8_t bit)
	{
		return (value & (1 << bit)) != 0;
	}

	static uint8_t GetBit(uint8_t value, uint8_t bit)
	{
		return (value & (1 << bit)) >> bit;
	}

	static uint16_t GetBit(uint16_t value, uint8_t bit)
	{
		return (value & (1 << bit)) >> bit;
	}
};