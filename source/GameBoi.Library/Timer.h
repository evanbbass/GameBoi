#pragma once

namespace GameBoi
{
	class MemoryMap;

	class Timer final
	{
	public:
		explicit Timer(MemoryMap& memory);

		/// <summary>
		/// Steps the timer. This is done relative to the number of CPU clock cycles since the
		/// last step to keep the timer in sync with the CPU.
		/// 
		/// That is, the CPU runs at 4194304Hz. If the timer is set to 4096Hz mode, each timer
		/// step should occur every 4194304 / 4096 = 1024 CPU clock cycles. So we would set 
		/// mTimerCounter to 0 and add <paramref name="cpuCycles" />
		/// until mTimerCounter hits 1024, then step the timer.
		/// </summary>
		/// <param name="cpuCycles">Number of CPU clock cycles since the last step.</param>
		void StepTimer(int32_t cpuCycles);

		bool IsEnabled() const;
		int32_t GetTimerFrequency() const;

		uint8_t GetDivider() const;
		uint8_t GetTimer() const;
		uint8_t GetTimerModulator() const;
		uint8_t GetTimerController() const;
		void SetDivider(uint8_t value);
		void SetTimer(uint8_t value);
		void SetTimerModulator(uint8_t value);
		void SetTimerController(uint8_t value);

		static const uint16_t DividerAddress = 0xFF04;
		static const uint16_t TimerAddress = 0xFF05;
		static const uint16_t TimerModulatorAddress = 0xFF06;
		static const uint16_t TimerControllerAddress = 0xFF07;

	private:
		MemoryMap& mMemory;
		int32_t mTimerCounter;
		int32_t mDividerCounter;
		int32_t mCurrentFrequency;

		uint8_t mDivider;
		uint8_t mTimer;
		uint8_t mTimerModulator;
		uint8_t mTimerController;

		void StepDivider(int32_t cpuCycles);
		void CheckFrequencyChange();

		static const int32_t TimerFrequencyMap[4];
		static const int32_t DividerFrequency;
		static const uint8_t TimerEnabledBit = 2;
		static const uint8_t TimerFrequencyMask = 0b00000011;
	};
}
