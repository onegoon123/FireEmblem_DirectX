#include "PlayLevel.h"
#include "BattleActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Loading()
{
	std::shared_ptr<BattleActor> NewPlayer = CreateActor<BattleActor>("Player");
	GameEngineInput::CreateKey("A", 'a');
	GameEngineInput::CreateKey("B", 'b');

	GameEngineRandom::MainRandom.SetSeed(0);
}

void PlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("A"))
	{
		a = GameEngineRandom::MainRandom.RandomInt(0, 100);
		MsgTextBox(std::to_string(a));
	}
	if (GameEngineInput::IsDown("B"))
	{
		GameEngineRandom::MainRandom.SetSeed(0);
	}
}
