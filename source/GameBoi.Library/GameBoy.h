#pragma once
#include "CPU.h"
#include "Timer.h"
#include "GPU.h"

namespace GameBoi
{
	class GameBoy
	{
	public:
		GameBoy();
		explicit GameBoy(const std::string& cartridgeFileName);
		~GameBoy() = default;

		void LoadCartridge(const std::string& fileName);
		void Reset();
		void Update();

		CPU& GetCPU();
		const CPU& GetCPU() const;
		MemoryMap& GetMemoryMap();
		const MemoryMap& GetMemoryMap() const;

	private:
		CPU mCPU;
		GPU mGPU;
		MemoryMap mMemory;
		Timer mTimer;
	};
}
