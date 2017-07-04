#pragma once

namespace GameBoi
{
	class MemoryMap;

	class GPU final
	{
	public:
		enum class LCDStatus : uint8_t
		{
			HBlank = 0b00, // H-Blank
			VBlank = 0b01, // V-Blank
			OAM = 0b10, // Searching Sprite Attributes
			VRAM = 0b11 // Transferring Data to LCD Driver
		};

		explicit GPU(MemoryMap& memory);

		/// <summary>
		/// Steps the GPU. This is done relative to the number of CPU clock cycles since the
		/// last step to keep the GPU in sync with the CPU.
		/// 
		/// Specifically, it takes the GPU 456 CPU clock cycles to draw each scanline. So we set 
		/// mScanlineCounter to 0 and add <paramref name="cpuCycles" />
		/// until mScanlineCounter hits 456, then increment the current scanline.
		/// </summary>
		/// <param name="cpuCycles">Number of CPU clock cycles since the last step.</param>
		void StepGPU(int32_t cpuCycles);

		bool IsEnabled() const;
		uint8_t GetCurrentScanline() const;
		uint8_t GetLCDStatusRegister() const;
		LCDStatus GetLCDStatus() const;
		uint8_t GetLCDControlRegister() const;
		uint8_t GetCoincidenceRegister() const;

		static const uint16_t CurrentScanlineAddress = 0xFF44;
		static const uint16_t LCDStatusRegisterAddress = 0xFF41;
		static const uint16_t LCDControlRegisterAddress = 0xFF40;
		static const uint16_t CoincidenceRegisterAddress = 0xFF45;
		static const uint8_t CoincidenceBit = 2;
		static const uint8_t HBlankInterruptBit = 3;
		static const uint8_t VBlankInterruptBit = 4;
		static const uint8_t OAMInterruptBit = 5;
		static const uint8_t CoincidenceInterruptBit = 6;

		static const int32_t CPUCyclesPerScanline = 456;
		static const int32_t OAMStatusCutoff = 80;
		static const int32_t VRAMStatusCutoff = OAMStatusCutoff + 172;

		static const int32_t ScreenWidth = 160;
		static const int32_t ScreenHeight = 144;
		static const int32_t MaxScanlines = 153; // 144 visible scanlines and 8 invisible ones

	private:
		MemoryMap& mMemory;
		int32_t mScanlineCounter;

		void DrawScanLine();
		void HandleHBlank();
		void UpdateLCDStatus();
		void CheckCoincidenceFlag();
		void SetLCDStatus(LCDStatus status);
	};
}
