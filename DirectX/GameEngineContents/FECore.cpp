#include "FECore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"

FECore::FECore()
{
}

FECore::~FECore()
{
}

void FECore::GameStart()
{
	new int();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void FECore::GameEnd()
{

}