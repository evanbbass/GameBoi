#include "pch.h"
#include "GameBoyManaged.h"

using namespace System;
using namespace GameBoi;

namespace GameBoiManaged
{
	GameBoyManaged::GameBoyManaged() :
		mGameBoy(new GameBoy())
	{
	}

	GameBoyManaged::GameBoyManaged(String^ filename) :
		mGameBoy(new GameBoy(msclr::interop::marshal_as<std::string>(filename)))
	{
	}

	GameBoyManaged::~GameBoyManaged()
	{
		delete mGameBoy;
	}

	GameBoy& GameBoyManaged::Unmanaged::get()
	{
		return *mGameBoy;
	}

	void GameBoyManaged::LoadCartridge(String^ filename)
	{
		mGameBoy->LoadCartridge(msclr::interop::marshal_as<std::string>(filename));
	}

	void GameBoyManaged::Reset()
	{
		mGameBoy->Reset();
	}

	CPUManaged^ GameBoyManaged::CPU::get()
	{
		return gcnew CPUManaged(mGameBoy->GetCPU());
	}

	MemoryMapManaged^ GameBoyManaged::MemoryMap::get()
	{
		return gcnew MemoryMapManaged(mGameBoy->GetMemoryMap());
	}
}