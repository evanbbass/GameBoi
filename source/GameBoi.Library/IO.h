#pragma once
#include "Keypad.h"
#include "IAddressable.h"
#include "Timer.h"
#include "GPU.h"

namespace GameBoi
{
	class MemoryMap;

	class IO final : public IAddressable
	{
	public:
		explicit IO(MemoryMap& parent);

		uint8_t ReadByte(uint16_t address) const override;
		void WriteByte(uint16_t address, uint8_t value) override;

		Timer& GetTimer();
		const Timer& GetTimer() const;
		Keypad& GetKeypad();
		const Keypad& GetKeypad() const;
		GPU& GetGPU();
		const GPU& GetGPU() const;

	private:
		MemoryMap& mMemory;
		GPU mGPU;
		Timer mTimer;
		Keypad mKeypad;
		uint8_t mInterruptFlags;
	};
}
