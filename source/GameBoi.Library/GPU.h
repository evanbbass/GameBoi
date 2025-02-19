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

        Display& GetDisplay() { return mDisplay; }
        const Display& GetDisplay() const { return mDisplay; }

        uint8_t GetCurrentScanline() const { return mCurrentScanline; }
        uint8_t GetLCDStatusRegister() const { return mLCDStatusRegister; }
        uint8_t GetLCDControlRegister() const { return mLCDControl.GetRegister(); }
        uint8_t GetCoincidenceRegister() const { return mCoincidenceRegister; }

        uint8_t GetScrollY() const { return mScrollY; }
        uint8_t GetScrollX() const { return mScrollX; }
        uint8_t GetWindowY() const { return mWindowY; }
        uint8_t GetWindowX() const { return mWindowX; }

		uint8_t GetBackgroundPallet() const { return mBackgroundPallet.GetPallet(); }
        uint8_t GetSpritePallet0() const { return mSpritePallet0.GetPallet(); }
        uint8_t GetSpritePallet1() const { return mSpritePallet1.GetPallet(); }

        void SetCurrentScanline(uint8_t value) { mCurrentScanline = value; }
        void SetLCDStatusRegister(uint8_t value) { mLCDStatusRegister = value; }
        void SetLCDControlRegister(uint8_t value) { mLCDControl.SetRegister(value); }
        void SetCoincidenceRegister(uint8_t value) { mCoincidenceRegister = value; }

        void SetScrollY(uint8_t value) { mScrollY = value; }
        void SetScrollX(uint8_t value) { mScrollX = value; }
        void SetWindowY(uint8_t value) { mWindowY = value; }
        void SetWindowX(uint8_t value) { mWindowX = value; }

        void SetBackgroundPallet(uint8_t value) { mBackgroundPallet.SetPallet(value); }
        void SetSpritePallet0(uint8_t value) { mSpritePallet0.SetPallet(value); }
        void SetSpritePallet1(uint8_t value) { mSpritePallet1.SetPallet(value); }

        LCDStatus GetLCDStatus() const { return static_cast<LCDStatus>(mLCDStatusRegister & 0b11); }

		static constexpr uint16_t CurrentScanlineAddress = 0xFF44;
		static constexpr uint16_t LCDStatusRegisterAddress = 0xFF41;
		static constexpr uint16_t CoincidenceRegisterAddress = 0xFF45;

		static constexpr uint16_t DMAAddress = 0xFF46;

		static constexpr uint16_t ScrollYAddress = 0xFF42;
		static constexpr uint16_t ScrollXAddress = 0xFF43;
		static constexpr uint16_t WindowYAddress = 0xFF4A;
		static constexpr uint16_t WindowXAddress = 0xFF4B;

		static constexpr uint16_t BackgroundPalletAddress = 0xFF47;
		static constexpr uint16_t SpritePallet0Address = 0xFF48;
		static constexpr uint16_t SpritePallet1Address = 0xFF49;

		static constexpr int32_t ScreenWidth = 160;
		static constexpr int32_t ScreenHeight = 144;

	private:
		MemoryMap& mMemory;
		Display mDisplay;
		int32_t mScanlineCounter;
		uint8_t mCurrentScanline;
		uint8_t mLCDStatusRegister;
		LCDControl mLCDControl;
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
