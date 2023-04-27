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
		Renderer->SetGrayScale(true);
	}
	else
	{
		Renderer->SetGrayScale(false);
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

static int EnemyNum = 0;
void BattleUnit::SetUnitCode(UnitIdentityCode _Code)
{
	UnitData.UnitCode = static_cast<int>(_Code);
	UnitData.UnitStat.SetIdentity(_Code);
	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;

	switch (_Code)
	{
	case UnitIdentityCode::Lyn:
		SetName("��");
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
		UnitData.UnitCode += EnemyNum++;
		SetName("����");
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
	Renderer->SetTexture(ImageName);
}

void BattleUnit::Start()
{
	Renderer = CreateComponent<UnitRenderer>();
	ImageName = "Map_LynTest.png";
	Renderer->SetTexture(ImageName);
	Renderer->SetWorldScale({ 128,128 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
}

