#pragma once

#include <array>
#include "IAddressable.h"
#include "SpriteAttributes.h"

namespace GameBoi
{
	class ObjectAttributeMemory : public IAddressable
	{
	public:
		uint8_t ReadByte(uint16_t address) const override;
		void WriteByte(uint16_t address, uint8_t value) override;

		SpriteAttributes& operator[](int32_t index);
		const SpriteAttributes& operator[](int32_t index) const;

	private:
		std::array<SpriteAttributes, 40> mSpriteAttributes;
	};
}
