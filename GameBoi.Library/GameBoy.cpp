#include "pch.h"
#include "GameBoy.h"

using namespace std;

namespace GameBoi
{
	GameBoy::GameBoy(): mCPU(mMemory)
	{
	}

	void GameBoy::LoadCartridge(const string& fileName)
	{
		mMemory.LoadCartridgeFromFile(fileName);
	}

	void GameBoy::Reset()
	{
		mCPU.Reset();
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
