#pragma once
#include "CPU.h"

namespace GameBoi
{
	class GameBoy
	{
	public:
		GameBoy();
		~GameBoy() = default;

		void LoadCartridge(const std::string& fileName);
		void Reset();

		CPU& GetCPU();
		const CPU& GetCPU() const;
		MemoryMap& GetMemoryMap();
		const MemoryMap& GetMemoryMap() const;

	private:
		CPU mCPU;
		MemoryMap mMemory;
	};
}
