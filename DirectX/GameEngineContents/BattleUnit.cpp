#include "PrecompileHeader.h"
#include "BattleUnit.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Stat.h"
#include "Weapon.h"
#include "SpriteRenderer.h"
BattleUnit::BattleUnit()
{
	MoveSpeed = 15.0f;
}

BattleUnit::~BattleUnit()
{
}

void BattleUnit::Select()
{
	GetTransform()->SetLocalPositiveScaleX();
	Renderer->ChangeAnimation("Select");
}

void BattleUnit::SetIdle()
{
	GetTransform()->SetLocalPositiveScaleX();
	Renderer->ChangeAnimation("Idle");
}

void BattleUnit::SetIsTurnEnd(bool _Value)
{
	UnitData.IsTurnEnd = _Value;

	if (_Value == true)
	{
		Renderer->SetSaturation(0);
	}
	else
	{
		Renderer->SetSaturation(1);
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

static int EnemyNum = 13;
void BattleUnit::SetUnitCode(UnitIdentityCode _Code)
{
	UnitData.UnitCode = static_cast<int>(_Code);
	UnitData.UnitStat.SetIdentity(_Code);
	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;
	bool IsShortWalk = false;
	switch (_Code)
	{
	case UnitIdentityCode::Lyn:
		SetName("린");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_Lyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Sain:
		SetName("세인");
		UnitData.SetName("Sain");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Kent:
		SetName("켄트");
		UnitData.SetName("Kent");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Florina:
		SetName("플로리나");
		UnitData.SetName("Florina");
		MapSpriteName = "Map_Florina.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Wil:
		SetName("윌");
		UnitData.SetName("Wil");
		MapSpriteName = "Map_Wil.png";
		IsShortWalk = true;
		UnitData.IsPlayer = true;
		break;
		break;
	case UnitIdentityCode::Dorcas:
		SetName("돌카스");
		UnitData.SetName("Dorcas");
		MapSpriteName = "Map_Dorcas.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Serra:
		SetName("세라");
		UnitData.SetName("Serra");
		MapSpriteName = "Map_Serra.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Erk:
		SetName("에릭");
		UnitData.SetName("Erk");
		MapSpriteName = "Map_Erk.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Rath:
		SetName("라스");
		UnitData.SetName("Rath");
		MapSpriteName = "Map_Rath.png";
		IsShortWalk = true;
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Matthew:
		SetName("메튜");
		UnitData.SetName("Matthew");
		MapSpriteName = "Map_Matthew.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Ninian:
		SetName("니니안");
		UnitData.SetName("Ninian");
		MapSpriteName = "Map_Ninian.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Lucius:
		SetName("루시우스");
		UnitData.SetName("Lucius");
		MapSpriteName = "Map_Lucius.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Wallace:
		SetName("월레스");
		UnitData.SetName("Wallace");
		MapSpriteName = "Map_Wallace.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Brigand:
		UnitData.UnitCode = EnemyNum++;
		SetName("산적");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Soldier:
		UnitData.UnitCode = EnemyNum++;
		SetName("병사");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemySoldier.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Mercenary:
		UnitData.UnitCode = EnemyNum++;
		SetName("용병");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyMercenary.png";
		UnitData.IsPlayer = false;
		break;
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

	//std::string_view AnimationName = "";
	//std::string_view SpriteName = "";
	//size_t Start = static_cast<size_t>(-1);
	//size_t End = static_cast<size_t>(-1);
	//float FrameInter = 0.1f;
	//bool Loop = true;
	//bool ScaleToTexture = false;
	if (nullptr == GameEngineSprite::Find(MapSpriteName))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Character");
		Dir.Move("Map");
		if (true == IsShortWalk)
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName(MapSpriteName).GetFullPath(), 3, 5);
		}
		else
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName(MapSpriteName).GetFullPath(), 3, 6);
		}
		
	}


	Renderer->CreateAnimation({ .AnimationName = "Idle",.SpriteName = MapSpriteName, .FrameIndex = {0, 1, 2, 1}, .FrameTime = {0.5f, 0.1f, 0.5f, 0.1f} });
	Renderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.3f, 0.1f, 0.3f, 0.1f} });
	if (true == IsShortWalk)
	{
		Renderer->CreateAnimation({ .AnimationName = "Left", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {6, 7, 8, 7} });
		Renderer->CreateAnimation({ .AnimationName = "Down", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {9, 10, 11, 10} });
		Renderer->CreateAnimation({ .AnimationName = "Up", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {12, 13, 14, 13} });
	}
	else
	{
		Renderer->CreateAnimation({ "Left", MapSpriteName, 6, 9, 0.2f, true, false });
		Renderer->CreateAnimation({ "Down", MapSpriteName, 10, 13, 0.2f, true, false });
		Renderer->CreateAnimation({ "Up", MapSpriteName, 14, 17, 0.2f, true, false });
	}

	Renderer->ChangeAnimation("Idle");
}


void BattleUnit::Start()
{
	Renderer = CreateComponent<SpriteRenderer>();
	Renderer->SetLocalScale({ 192,192 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
	MapUnit::Update(_DeltaTime);
}

void BattleUnit::SetMoveDir(int2 _Dir)
{
	if (_Dir == int2::Right)
	{
		Renderer->ChangeAnimation("Left");
		GetTransform()->SetLocalNegativeScaleX();
		return;
	}

	GetTransform()->SetLocalPositiveScaleX();

	if (_Dir == int2::Left)
	{
		Renderer->ChangeAnimation("Left");
		return;
	}
	if (_Dir == int2::Down)
	{
		Renderer->ChangeAnimation("Down");
		return;
	}
	if (_Dir == int2::Up)
	{
		Renderer->ChangeAnimation("Up");
		return;
	}
}

