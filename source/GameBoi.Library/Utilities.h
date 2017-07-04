#pragma once
#include <cstdint>

class Utilities abstract final
{
public:
	static uint8_t SetBit(uint8_t value, uint8_t bit)
	{
		return value | (1 << bit);
	}

	static uint8_t ResetBit(uint8_t value, uint8_t bit)
	{
		return value & ~(1 << bit);
	}

	static bool TestBit(uint8_t value, uint8_t bit)
	{
		return (value | (1 << bit)) != 0;
	}
};