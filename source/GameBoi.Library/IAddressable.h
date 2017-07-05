#pragma once

namespace GameBoi
{
	class IAddressable abstract
	{
	public:
		virtual ~IAddressable() = default;

		virtual uint8_t ReadByte(uint16_t address) const = 0;
		virtual void WriteByte(uint16_t address, uint8_t value) = 0;

		uint16_t ReadWord(uint16_t address) const
		{
			return (ReadByte(address + 1) << 8) | ReadByte(address);
		}

		void WriteWord(uint16_t address, uint16_t value)
		{
			WriteByte(address, value & 0x00FF);
			WriteByte(address + 1, (value & 0xFF00) >> 8);
		}
	};
}
