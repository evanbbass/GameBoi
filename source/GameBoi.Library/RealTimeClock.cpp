#include "pch.h"
#include "RealTimeClock.h"
#include "Utilities.h"

using namespace std;

namespace GameBoi
{
	RealTimeClock::RealTimeClock() :
		mSeconds(0), mMinutes(0), mHours(0), mDays(0), mReadyToLatch(false)
	{
	}

	void RealTimeClock::LatchClockData(uint8_t value)
	{
		// writing 0 followed by 1 latches the current time to the RTC registers
		if (!mReadyToLatch && !Utilities::TestBit(value, 0))
		{
			mReadyToLatch = true;
		}
		else
		{
			if (mReadyToLatch && Utilities::TestBit(value, 0))
			{
				Latch();
			}

			mReadyToLatch = false;
		}
	}

	bool RealTimeClock::IsActive() const
	{
		return !Utilities::TestBit(mDays, 14);
	}

	bool RealTimeClock::DayCounterCarry() const
	{
		return Utilities::TestBit(mDays, 15);
	}

	void RealTimeClock::Latch()
	{
		// write time to registers
	}
}
