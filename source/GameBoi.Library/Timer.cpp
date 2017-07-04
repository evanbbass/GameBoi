#include "pch.h"
#include "Timer.h"
#include "MemoryMap.h"
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
		mMemory(memory), mTimerCounter(0), mDividerCounter(0), mCurrentFrequency(TimerFrequencyMap[0])
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

				uint8_t timer = mMemory.ReadByte(TimerAddress);
				if (timer == 0xFF)
				{
					mMemory.SetTimerInterruptFlag();
					mMemory.WriteByte(TimerAddress, GetTimerModulator());
				}
				else
				{
					mMemory.WriteByte(TimerAddress, timer + 1);
				}
			}
		}
	}

	bool Timer::IsEnabled() const
	{
		return (GetTimerController() & TimerEnabledBit) != 0;
	}

	uint8_t Timer::GetDivider() const
	{
		return mMemory.ReadByte(DividerAddress);
	}

	uint8_t Timer::GetTimer() const
	{
		return mMemory.ReadByte(TimerAddress);
	}

	uint8_t Timer::GetTimerModulator() const
	{
		return mMemory.ReadByte(TimerModulatorAddress);
	}

	uint8_t Timer::GetTimerController() const
	{
		return mMemory.ReadByte(TimerControllerAddress);
	}

	int32_t Timer::GetTimerFrequency() const
	{
		return TimerFrequencyMap[GetTimerController() & TimerFrequencyBits];
	}

	void Timer::StepDivider(int32_t cpuCycles)
	{
		mDividerCounter += cpuCycles;
		const int32_t frequency = CPU::CPUClockSpeed / DividerFrequency;

		if (mDividerCounter >= frequency)
		{
			mDividerCounter -= frequency;
			// TODO technically this isn't allowed
			mMemory.WriteByte(DividerAddress, GetDivider() + 1);
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
}
