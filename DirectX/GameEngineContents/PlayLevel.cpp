#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "BattleActor.h"
#include <GameEngineCore/GameEngineCamera.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<BattleActor> NewPlayer = CreateActor<BattleActor>("Player");


}