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

void BattleUnit::SetIsTurnEnd(bool _Value)
{
	IsTurnEnd = _Value;

	if (_Value == true)
	{
		SpriteRender->SetPipeLine("2DTextureGray");
		SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	}
	else
	{
		SpriteRender->SetPipeLine("2DTexture");
		SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	}
}


void BattleUnit::SetUnitCode(int _Code)
{
	UnitCode = _Code;
	UnitStat.SetStat_Lyn();
	SetName("¸°");

	if (2 <= UnitCode)
	{
		ImageName = "Map_EnemyBrigandTest.png";
		SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	}
	else
	{
		ImageName = "Map_LynTest.png";
	}
}

void BattleUnit::Start()
{
	SpriteRender = CreateComponent<GameEngineRenderer>();
	SpriteRender->SetPipeLine("2DTexture");
	ImageName = "Map_LynTest.png";
	SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	SpriteRender->GetTransform()->SetWorldScale({ 128,128 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
}

