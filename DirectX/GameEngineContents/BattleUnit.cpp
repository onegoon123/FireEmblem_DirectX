#include "PrecompileHeader.h"
#include "BattleUnit.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Stat.h"
#include "Weapon.h"
BattleUnit::BattleUnit() 
{
}

BattleUnit::~BattleUnit() 
{
}

void BattleUnit::SetIsTurnEnd(bool _Value)
{
	UnitData.IsTurnEnd = _Value;

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

bool BattleUnit::GetIsTurnEnd()
{
	return UnitData.IsTurnEnd;
}


void BattleUnit::SetUnitCode(int _Code)
{
	UnitData.UnitCode = _Code;
	
	if (2 <= UnitData.UnitCode)
	{
		SetName("적");
		ImageName = "Map_EnemyBrigandTest.png";
		SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
		UnitData.UnitStat.SetStat_Brigand();
	}
	else
	{
		SetName("플레이어");
		ImageName = "Map_LynTest.png";
		UnitData.UnitStat.SetStat_Lyn();
	}

	UnitData.UnitStat.EquipWeapon.Damage = 5;	// 공격력
	UnitData.UnitStat.EquipWeapon.Hit = 90;		// 명중률
	UnitData.UnitStat.EquipWeapon.Critical = 5;	// 치명타
	UnitData.UnitStat.EquipWeapon.Weight = 5;		// 무게
	UnitData.UnitStat.EquipWeapon.Range = 1;		// 사거리
	UnitData.UnitStat.EquipWeapon.Uses = 30;		// 내구도

	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;
}

int BattleUnit::GetUnitCode()
{
	return UnitData.UnitCode;
}

int BattleUnit::GetMoveStat()
{
	return UnitData.UnitStat.Movement;
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

