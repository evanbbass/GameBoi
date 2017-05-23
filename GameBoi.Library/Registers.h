#pragma once
#include <cstdint>

#pragma warning(push)
#pragma warning(disable : 4201)
struct Registers
{
	union
	{
		struct
		{
			uint8_t F;
			uint8_t A;
		};
		uint16_t AF;
	};

	union
	{
		struct
		{
			uint8_t C;
			uint8_t B;
		};
		uint16_t BC;
	};

	union
	{
		struct
		{
			uint8_t E;
			uint8_t D;
		};
		uint16_t DE;
	};

	union
	{
		struct
		{
			uint8_t L;
			uint8_t H;
		};
		uint16_t HL;
	};

	uint16_t SP;
	uint16_t PC;
};
#pragma warning(pop)
