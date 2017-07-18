#pragma once
#include "Pallet.h"
#include "LCDControl.h"

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

		Display& GetDisplay();
		const Display& GetDisplay() const;

		uint8_t GetCurrentScanline() const;
		uint8_t GetLCDStatusRegister() const;
		uint8_t GetLCDControlRegister() const;
		uint8_t GetCoincidenceRegister() const;

		uint8_t GetScrollY() const;
		uint8_t GetScrollX() const;
		uint8_t GetWindowY() const;
		uint8_t GetWindowX() const;

		uint8_t GetBackgroundPallet() const;
		uint8_t GetSpritePallet0() const;
		uint8_t GetSpritePallet1() const;

		void SetCurrentScanline(uint8_t value);
		void SetLCDStatusRegister(uint8_t value);
		void SetLCDControlRegister(uint8_t value);
		void SetCoincidenceRegister(uint8_t value);

		void SetScrollY(uint8_t value);
		void SetScrollX(uint8_t value);
		void SetWindowY(uint8_t value);
		void SetWindowX(uint8_t value);

		void SetBackgroundPallet(uint8_t value);
		void SetSpritePallet0(uint8_t value);
		void SetSpritePallet1(uint8_t value);

		LCDStatus GetLCDStatus() const;

		static const uint16_t CurrentScanlineAddress = 0xFF44;
		static const uint16_t LCDStatusRegisterAddress = 0xFF41;
		static const uint16_t CoincidenceRegisterAddress = 0xFF45;

		static const uint16_t DMAAddress = 0xFF46;

		static const uint16_t ScrollYAddress = 0xFF42;
		static const uint16_t ScrollXAddress = 0xFF43;
		static const uint16_t WindowYAddress = 0xFF4A;
		static const uint16_t WindowXAddress = 0xFF4B;

		static const uint16_t BackgroundPalletAddress = 0xFF47;
		static const uint16_t SpritePallet0Address = 0xFF48;
		static const uint16_t SpritePallet1Address = 0xFF49;

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
		Display mDisplay;
		int32_t mScanlineCounter;
		uint8_t mCurrentScanline;
		uint8_t mLCDStatusRegister;
		LCDControl mLCDControlRegister;
		uint8_t mCoincidenceRegister;
		uint8_t mScrollY;
		uint8_t mScrollX;
		uint8_t mWindowY;
		uint8_t mWindowX;
		Pallet mBackgroundPallet;
		Pallet mSpritePallet0;
		Pallet mSpritePallet1;

		void DrawScanLine();
		void RenderTiles();
		void RenderSprites();
		void DrawDebug();
		void HandleHBlank();
		void UpdateLCDStatus();
		void CheckCoincidence();
		void SetLCDStatus(LCDStatus status);
	};
}
