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

	GameBoy& GameBoyManaged::GetUnmanaged()
	{
		return *mGameBoy;
	}

	void GameBoyManaged::LoadCartridge(String^ filename)
	{
		mGameBoy->LoadCartridge(msclr::interop::marshal_as<std::string>(filename));
	}

	Void GameBoyManaged::Reset()
	{
		mGameBoy->Reset();
	}
}