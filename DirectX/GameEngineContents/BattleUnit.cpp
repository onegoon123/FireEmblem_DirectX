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

void BattleUnit::SetUnitCode(int _Code)
{
	UnitCode = _Code;
	UnitStat.SetStat_Lyn();
	SetName("¸°");

	if (2 <= UnitCode)
	{
		SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", "Map_EnemyBrigandTest.png");
	}
}

void BattleUnit::Start()
{
	SpriteRender = CreateComponent<GameEngineRenderer>();
	SpriteRender->SetPipeLine("2DTexture");
	SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", "Map_LynTest.png");
	SpriteRender->GetTransform()->SetWorldScale({ 128,128 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
}

