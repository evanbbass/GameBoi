#pragma once

namespace GameBoi
{
	class RealTimeClock final
	{
	public:
		RealTimeClock();

		void LatchClockData(uint8_t value);
		bool IsActive() const;
		bool DayCounterCarry() const;

	private:
		uint8_t mSeconds;
		uint8_t mMinutes;
		uint8_t mHours;
		uint16_t mDays;
		bool mReadyToLatch;

		void Latch();

		const static uint16_t DaysMask = 0b0000000111111111;
	};
}
