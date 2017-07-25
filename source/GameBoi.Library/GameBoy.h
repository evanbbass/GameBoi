#pragma once
#include "CPU.h"
#include "Timer.h"

namespace GameBoi
{
	class GPU;

	class GameBoy final
	{
	public:
		GameBoy();
		explicit GameBoy(const std::string& cartridgeFileName);
		~GameBoy() = default;

		void LoadCartridge(const std::string& fileName);
		void WriteSaveFile() const;
		void Reset();
		int32_t Update();

		CPU& GetCPU();
		const CPU& GetCPU() const;
		MemoryMap& GetMemoryMap();
		const MemoryMap& GetMemoryMap() const;

	private:
		CPU mCPU;
		MemoryMap mMemory;
		Timer& mTimer;
		GPU& mGPU;
	};
}
