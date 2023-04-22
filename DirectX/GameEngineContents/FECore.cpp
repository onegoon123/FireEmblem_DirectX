#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "TitleLevel.h"
#include "BattleLevel.h"

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
	GameEngineCore::CreateLevel<BattleLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void FECore::GameEnd()
{

}
