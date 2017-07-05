[Back to Home](../../README.md)

[Next to Week 2](Week2.md)

## 5/23/2017
Using the [Game Boy Hardware Documentation](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf), I set up the initial classes for the Game Boy's memory. Initially everything was done in one monolithic Memory class, with each segment (Cartridge ROM, Video RAM, Switchable RAM, etc.) contained within its own byte array:

```c++
uint8_t Cartridge[0x8000]; // 0x0000 - 0x8000
uint8_t VideoRAM[0x2000]; // 0x8000 - 0x9FFF
uint8_t SwitchableRAM[0x2000]; // 0xA000 - 0xBFFF
uint8_t WorkingRAM[0x2000]; // 0xC000 - 0xDFFF
uint8_t WorkingRAMShadow[0x1E00]; // 0xE000 - 0xFDFF
uint8_t Graphics[0xA0]; // 0xFE00 - 0xFE9F
uint8_t Unusable[0x60]; // 0xFEA0 - 0xFEFF
uint8_t IO[0x80]; // 0xFF00 - 0xFF7F
uint8_t ZeroPageRAM[0x80]; // 0xFF80 - 0xFFFF
```

To enable easier access to specific bytes within the memory, I added an indexing operator, which would get the byte from the correct memory segment:

```c++
uint8_t& operator[](uint16_t address)
{
	if (address < 0x8000)
	{
		return Cartridge[address];
	}
	else if (address < 0xA000)
	{
		return VideoRAM[address - 0x8000];
	}
	else if (address < 0xC000)
	{
		return SwitchableRAM[address - 0xA000];
	}
	else if (address < 0xE000)
	{
		return WorkingRAM[address - 0xC000];
	}
	else if (address < 0xFE00)
	{
		return WorkingRAM[address - 0xE000];
	}
	else if (address < 0xFEA0)
	{
		return Graphics[address - 0xFE00];
	}
	else if (address < 0xFF00)
	{
		throw std::exception("Unusable memory!");
	}
	else if (address < 0xFF80)
	{
		return IO[address - 0xFEA0];
	}
	else if (address < 0x10000)
	{
		return ZeroPageRAM[address - 0xFF80];
	}
	else
	{
		throw std::exception("address out of range!");
	}
}
```

While this works for individual bytes, some instructions require words. In addition, the syntax could likely get confusing, so I also added Read and Write functions for both bytes and words (words will do bit-shifting of byte reads/writes):

```c++
uint8_t Memory::ReadByte(uint16_t address) const
{
	return (*this)[address];
}
uint16_t Memory::ReadWord(uint16_t address) const
{
	return ((*this)[address + 1] << 8) | (*this)[address];
}
void Memory::WriteByte(uint16_t address, uint8_t value)
{
	(*this)[address] = value;
}
void Memory::WriteWord(uint16_t address, uint16_t value)
{
	(*this)[address] = value & 0x00FF;
	(*this)[address + 1] = (value & 0xFF00) >> 8;
}
```

With all that done, I realized I could extract the Cartridge into its own class. In the future I might do that with additional segments (in particular the graphics-related segments).

In addition, I set up the primary registers using unions as described in [CTurt's article about his Game Boy emulator](http://cturt.github.io/cinoop.html).

## 5/24/2017
Today I added VS Unit Tests to make sure the hardware emulation behaves as expected without needing to read in ROMs. I also added methods to the Registers struct to access, set, and clear specific flags.

## 5/25/2017
More refactoring today. The first thing I did was I switched the Cartridge from being a fixed two ROM banks to being a vector of ROM banks, with an index indicating which bank will be accessed from the upper 16k of addresses.

```c++
std::vector<std::array<uint8_t, BANK_SIZE>> mBanks;
uint32_t mSwitchableBankIndex;
//...
if (address < BANK_SIZE)
{
	return mBanks[0][address];
}
else if (address < (BANK_SIZE * 2))
{
	return mBanks[mSwitchableBankIndex][address - BANK_SIZE];
}
```

This makes future support for map swapping easier, although full support will be much later on (I need to get the basics working first). 

As you can see from the sample, another thing I did was switch from C-style arrays to C++ std::arrays.

The biggest thing I did though was parsing the ROM files. The header information for the cartridge is located from 0x100 to 0x14F. Of particular note are the Game Title from 0x134 to 0x142, Color Game Boy support flag at 0x143, Super Game Boy support flag at 0x146, Cartridge type at 0x147, ROM type at 0x148, and RAM type at 0x149. There are also checksums at 0x14D and 0x14E-0x14F that I might add support for later on.
