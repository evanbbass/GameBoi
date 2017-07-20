#include "pch.h"
#include "Timer.h"
#include "CPU.h"

using namespace std;

namespace GameBoi
{
	// frequency in Hz
	const int32_t Timer::TimerFrequencyMap[4] =
	{
		4096,
		262144,
		65536,
		16384
	};

	const int32_t Timer::DividerFrequency = 16382;

	Timer::Timer(MemoryMap& memory) :
		mMemory(memory),
		mTimerCounter(0), mDividerCounter(0), mCurrentFrequency(TimerFrequencyMap[0]),
		mDivider(0), mTimer(0), mTimerModulator(0), mTimerController(0)
	{
	}

	void Timer::StepTimer(int32_t cpuCycles)
	{
		StepDivider(cpuCycles);
		CheckFrequencyChange();

		if (IsEnabled())
		{
			mTimerCounter += cpuCycles;

			int32_t rate = CPU::CPUClockSpeed / mCurrentFrequency;
			if (mTimerCounter >= rate)
			{
				// reset counter
				mTimerCounter -= rate;

				if (mTimer == 0xFF)
				{
					mMemory.SetTimerInterruptFlag();
					mTimer = mTimerModulator;
				}
				else
				{
					mTimer++;
				}
			}
		}
	}

	void Timer::StepDivider(int32_t cpuCycles)
	{
		mDividerCounter += cpuCycles;
		const int32_t frequency = CPU::CPUClockSpeed / DividerFrequency;

		if (mDividerCounter >= frequency)
		{
			mDividerCounter -= frequency;
			mDivider++;
		}
	}

	void Timer::CheckFrequencyChange()
	{
		int32_t newFrequency = GetTimerFrequency();
		if (newFrequency != mCurrentFrequency)
		{
			mTimerCounter = 0;
			mCurrentFrequency = newFrequency;
		}
	}

	bool Timer::IsEnabled() const
	{
		return Utilities::TestBit(mTimerController, TimerEnabledBit);
	}

	int32_t Timer::GetTimerFrequency() const
	{
		return TimerFrequencyMap[mTimerController & TimerFrequencyMask];
	}

	uint8_t Timer::GetDivider() const
	{
		return mDivider;
	}

	uint8_t Timer::GetTimer() const
	{
		return mTimer;
	}

	uint8_t Timer::GetTimerModulator() const
	{
		return mTimerModulator;
	}

	uint8_t Timer::GetTimerController() const
	{
		return mTimerController;
	}

	void Timer::SetDivider(uint8_t)
	{
		// Writing to the divider always sets it to 0
		mDivider = 0;
	}

	void Timer::SetTimer(uint8_t value)
	{
		mTimer = value;
	}

	void Timer::SetTimerModulator(uint8_t value)
	{
		mTimerModulator = value;
	}

	void Timer::SetTimerController(uint8_t value)
	{
		mTimerController = value;
	}
}
