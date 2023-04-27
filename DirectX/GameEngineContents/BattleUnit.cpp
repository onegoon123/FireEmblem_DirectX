#include "PrecompileHeader.h"
#include "BattleUnit.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Stat.h"
#include "Weapon.h"
#include "UnitRenderer.h"
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
		SpriteRender->SetGrayScale(true);
		//SpriteRender->SetPipeLine("2DTextureGray");
		//SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	}
	else
	{
		SpriteRender->SetGrayScale(false);
		//SpriteRender->SetPipeLine("2DTexture");
		//SpriteRender->GetShaderResHelper().SetTexture("DiffuseTex", ImageName);
	}
}

bool BattleUnit::GetIsTurnEnd()
{
	return UnitData.IsTurnEnd;
}


void BattleUnit::SetUnitCode(int _Code)
{
	SetUnitCode(static_cast<UnitIdentityCode>(_Code));
}

void BattleUnit::SetUnitCode(UnitIdentityCode _Code)
{
	UnitData.UnitCode = static_cast<int>(_Code);
	UnitData.UnitStat.SetIdentity(_Code);
	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;

	switch (_Code)
	{
	case UnitIdentityCode::Lyn:
		SetName("¸°");
		ImageName = "Map_LynTest.png";
		break;
	case UnitIdentityCode::Sain:
		break;
	case UnitIdentityCode::Kent:
		break;
	case UnitIdentityCode::Florina:
		break;
	case UnitIdentityCode::Wil:
		break;
	case UnitIdentityCode::Dorcas:
		break;
	case UnitIdentityCode::Serra:
		break;
	case UnitIdentityCode::Erk:
		break;
	case UnitIdentityCode::Rath:
		break;
	case UnitIdentityCode::Matthew:
		break;
	case UnitIdentityCode::Ninian:
		break;
	case UnitIdentityCode::Lucius:
		break;
	case UnitIdentityCode::Wallace:
		break;
	case UnitIdentityCode::Brigand:
		SetName("»êÀû");
		ImageName = "Map_EnemyBrigandTest.png";
		break;
	case UnitIdentityCode::Soldier:
		break;
	case UnitIdentityCode::Mercenary:
		break;
	case UnitIdentityCode::Archer:
		break;
	case UnitIdentityCode::Knight:
		break;
	case UnitIdentityCode::Mage:
		break;
	default:
		break;
	}
	SpriteRender->SetTexture(ImageName);
}

void BattleUnit::Start()
{
	SpriteRender = CreateComponent<UnitRenderer>();
	ImageName = "Map_LynTest.png";
	SpriteRender->SetTexture(ImageName);
	SpriteRender->GetTransform()->SetWorldScale({ 128,128 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
}

