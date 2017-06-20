#pragma once

#include "GameBoy.h"
#include "CPUManaged.h"
#include "MemoryMapManaged.h"

namespace GameBoiManaged
{
	public ref class GameBoyManaged
	{
	public:
		GameBoyManaged();
		explicit GameBoyManaged(System::String^ filename);
		~GameBoyManaged();

		property GameBoi::GameBoy& Unmanaged { GameBoi::GameBoy& get(); }

		void LoadCartridge(System::String^ filename);
		void Reset();

		property CPUManaged^ CPU { CPUManaged^ get(); }
		property MemoryMapManaged^ MemoryMap { MemoryMapManaged^ get(); }

	private:
		GameBoi::GameBoy* mGameBoy;
	};
}
