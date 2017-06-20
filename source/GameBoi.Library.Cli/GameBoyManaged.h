#pragma once

#include "GameBoy.h"

namespace GameBoiManaged
{
	public ref class GameBoyManaged
	{
	public:
		GameBoyManaged();
		explicit GameBoyManaged(System::String^ filename);
		~GameBoyManaged();

		GameBoi::GameBoy& GetUnmanaged();

		void LoadCartridge(System::String^ filename);
		void Reset();

	private:
		GameBoi::GameBoy* mGameBoy;
	};
}
