#include "pch.h"
#include "GameBoy.h"

using namespace std;

namespace GameBoi
{
	GameBoy::GameBoy() :
		mCPU(mMemory), mTimer(mMemory.GetIO().GetTimer()), mGPU(mMemory.GetIO().GetGPU())
	{
	}

	GameBoy::GameBoy(const string& cartridgeFileName) :
		mCPU(mMemory), mTimer(mMemory.GetIO().GetTimer()), mGPU(mMemory.GetIO().GetGPU())
	{
		LoadCartridge(cartridgeFileName);
	}

	void GameBoy::LoadCartridge(const string& fileName)
	{
		mMemory.LoadCartridgeFromFile(fileName);
	}

	void GameBoy::Reset()
	{
		mCPU.Reset();
	}

	int32_t GameBoy::Update()
	{
		int32_t cpuCycles = mCPU.StepCPU();
		mGPU.StepGPU(cpuCycles);
		mTimer.StepTimer(cpuCycles);
		return cpuCycles;
	}

	CPU& GameBoy::GetCPU()
	{
		return mCPU;
	}

	const CPU& GameBoy::GetCPU() const
	{
		return mCPU;
	}

	MemoryMap& GameBoy::GetMemoryMap()
	{
		return mMemory;
	}

	const MemoryMap& GameBoy::GetMemoryMap() const
	{
		return mMemory;
	}
}
