#include "pch.h"
#include "ObjectAttributeMemory.h"
#include "MemoryMap.h"

using namespace std;

namespace GameBoi
{
	uint8_t ObjectAttributeMemory::ReadByte(uint16_t address) const
	{
		int32_t index = (address - MemoryMap::OAM_START) / sizeof(SpriteAttributes);
		int32_t offset = (address - MemoryMap::OAM_START) % sizeof(SpriteAttributes);
		switch (offset)
		{
			case 0:
				return mSpriteAttributes[index].PositionY;
			case 1:
				return mSpriteAttributes[index].PositionX;
			case 2:
				return mSpriteAttributes[index].TileNumber;
			case 3:
				return mSpriteAttributes[index].Attributes;
			default:
				return 0;
		}
	}

	void ObjectAttributeMemory::WriteByte(uint16_t address, uint8_t value)
	{
		int32_t index = (address - MemoryMap::OAM_START) / sizeof(SpriteAttributes);
		int32_t offset = (address - MemoryMap::OAM_START) % sizeof(SpriteAttributes);
		switch (offset)
		{
			case 0:
				mSpriteAttributes[index].PositionY = value;
				break;
			case 1:
				mSpriteAttributes[index].PositionX = value;
				break;
			case 2:
				mSpriteAttributes[index].TileNumber = value;
				break;
			case 3:
				mSpriteAttributes[index].Attributes = value;
				break;
			default:
				break;
		}
	}

	SpriteAttributes& ObjectAttributeMemory::operator[](int32_t index)
	{
		if (index < 0 || index >= static_cast<int32_t>(mSpriteAttributes.size()))
		{
			throw exception("Index out of range!");
		}

		return mSpriteAttributes[index];
	}

	const SpriteAttributes& ObjectAttributeMemory::operator[](int32_t index) const
	{
		if (index < 0 || index >= static_cast<int32_t>(mSpriteAttributes.size()))
		{
			throw exception("Index out of range!");
		}

		return mSpriteAttributes[index];
	}
}
