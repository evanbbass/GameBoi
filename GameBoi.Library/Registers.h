#pragma once
#include <cstdint>

#pragma warning(push)
#pragma warning(disable : 4201)
namespace GameBoi
{
	struct Registers
	{
		Registers();
		~Registers() = default;

		union
		{
			struct
			{
				uint8_t F;
				uint8_t A;
			};
			struct
			{
				uint8_t Flags;
				uint8_t Accumulator;
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

		void Reset();

		bool GetZeroFlag() const;
		void SetZeroFlag();
		void ResetZeroFlag();
		void AssignZeroFlag(bool value);

		bool GetSubtractFlag() const;
		void SetSubtractFlag();
		void ResetSubtractFlag();
		void AssignSubtractFlag(bool value);

		bool GetHalfCarryFlag() const;
		void SetHalfCarryFlag();
		void ResetHalfCarryFlag();
		void AssignHalfCarryFlag(bool value);

		bool GetCarryFlag() const;
		void SetCarryFlag();
		void ResetCarryFlag();
		void AssignCarryFlag(bool value);

	private:
		static const uint8_t ZERO_FLAG = 0b10000000;
		static const uint8_t SUBTRACT_FLAG = 0b01000000;
		static const uint8_t HALF_CARRY_FLAG = 0b00100000;
		static const uint8_t CARRY_FLAG = 0b00010000;
	};
}
#pragma warning(pop)
