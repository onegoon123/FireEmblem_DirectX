#include "PrecompileHeader.h"
#include "BattleUnit.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

BattleUnit::BattleUnit() 
{
}

BattleUnit::~BattleUnit() 
{
}

void BattleUnit::Start()
{
	SpriteRender = CreateComponent<GameEngineRenderer>();
	SpriteRender->SetPipeLine("2DTexture");
	SpriteRender->GetTransform()->SetWorldScale({ 104,104 });

	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PlayerMoveForward"))
	{
		MoveMapPos(int2::Up);
	}
	if (true == GameEngineInput::IsDown("PlayerMoveBack"))
	{
		MoveMapPos(int2::Down);
	}
	if (true == GameEngineInput::IsDown("PlayerMoveRight"))
	{
		MoveMapPos(int2::Right);
	}
	if (true == GameEngineInput::IsDown("PlayerMoveLeft"))
	{
		MoveMapPos(int2::Left);
		
	}
}

