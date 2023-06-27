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
	if (nullptr != Renderer)
	{
		Renderer->Death();
		Renderer = nullptr;
	}
	if (nullptr != FrontRenderer)
	{
		FrontRenderer->Death();
		FrontRenderer = nullptr;
	}
}

void BattleUnit::Select()
{
	GetTransform()->SetLocalPositiveScaleX();
	Renderer->Off();
	FrontRenderer->On();
	FrontRenderer->ChangeAnimation("Select");
}

void BattleUnit::SetIdle()
{
	GetTransform()->SetLocalPositiveScaleX();
	Renderer->ChangeAnimation("Idle");
	Renderer->On();
	FrontRenderer->Off();
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

static int EnemyNum = static_cast<int>(UnitIdentityCode::Brigand);
void BattleUnit::SetUnitCode(UnitIdentityCode _Code)
{
	UnitData.IdentityCode = _Code;
	UnitData.UnitCode = static_cast<int>(_Code);
	UnitData.UnitStat.SetIdentity(_Code);
	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;
	
	SetUnitAnimation(_Code);
}

void BattleUnit::ClassChange(BattleClass _Value)
{
	UnitData.ClassChange(_Value);
	SetUnitAnimation(UnitData.IdentityCode);
}

void BattleUnit::LoadUnitData(Unit _Value)
{
	UnitData = _Value;
	bool IsShortWalk = false;
	WalkSoundName = "Walk_Foot.wav";
	switch (UnitData.GetIdentityCode())
	{
	case UnitIdentityCode::Lyn:
		SetName("린");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_Lyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::BladeLordLyn:
		SetName("린");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_BladeLyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Sain:
		SetName("세인");
		UnitData.SetName("Sain");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Horse.wav";
		break;
	case UnitIdentityCode::Kent:
		SetName("켄트");
		UnitData.SetName("Kent");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Horse.wav";
		break;
	case UnitIdentityCode::Florina:
		SetName("플로리나");
		UnitData.SetName("Florina");
		MapSpriteName = "Map_Florina.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Pegasus.wav";
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
	case UnitIdentityCode::WarriorDorcas:
		SetName("돌카스");
		UnitData.SetName("Dorcas");
		MapSpriteName = "Map_WarriorDorcas.png";
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
	case UnitIdentityCode::AssassinMatthew:
		SetName("메튜");
		UnitData.SetName("Matthew");
		MapSpriteName = "Map_AssassinMatthew.png";
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
	case UnitIdentityCode::GeneralWallace:
		SetName("월레스");
		UnitData.SetName("Wallace");
		MapSpriteName = "Map_GeneralWallace.png";
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
	case UnitIdentityCode::Archer:
		UnitData.UnitCode = EnemyNum++;
		SetName("궁병");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyArcher.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Knight:
		UnitData.UnitCode = EnemyNum++;
		SetName("기사");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyKnight.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Mage:
		UnitData.UnitCode = EnemyNum++;
		SetName("메이지");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyMage.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::DarkMage:
		UnitData.UnitCode = EnemyNum++;
		SetName("다크메이지");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyMage.png";
		UnitData.IsPlayer = false;
		break;
	default:
		break;
	}

	if (Renderer != nullptr)
	{
		Renderer->Death();
		Renderer = nullptr;
		FrontRenderer->Death();
		FrontRenderer = nullptr;
	}
	Renderer = CreateComponent<SpriteRenderer>(RenderOrder::Unit);
	Renderer->SetLocalScale({ 192,192 });
	FrontRenderer = CreateComponent<SpriteRenderer>(RenderOrder::SelectUnit);
	FrontRenderer->SetLocalScale({ 192,192 });
	FrontRenderer->Off();

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
	FrontRenderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.3f, 0.1f, 0.3f, 0.1f} });
	if (true == IsShortWalk)
	{
		FrontRenderer->CreateAnimation({ .AnimationName = "Left", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {6, 7, 8, 7} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Down", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {9, 10, 11, 10} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Up", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {12, 13, 14, 13} });
	}
	else
	{
		FrontRenderer->CreateAnimation({ "Left", MapSpriteName, 6, 9, 0.2f, true, false });
		FrontRenderer->CreateAnimation({ "Down", MapSpriteName, 10, 13, 0.2f, true, false });
		FrontRenderer->CreateAnimation({ "Up", MapSpriteName, 14, 17, 0.2f, true, false });
	}

	Renderer->ChangeAnimation("Idle");
	FrontRenderer->ChangeAnimation("Select");
}

bool BattleUnit::IsAttackable(int _Distance)
{
	if (nullptr == UnitData.CurWeapon)
	{
		return false;
	}
	if (UnitData.GetWeaponTypeValue() == WeaponType::Bow)
	{
		if (_Distance == 1)
		{
			return false;
		}
		if (_Distance <= UnitData.CurWeapon->GetRange())
		{
			return true;
		}
		return false;
	}
	

	return _Distance <= UnitData.CurWeapon->GetRange();
}

bool BattleUnit::IsAttackable(std::shared_ptr<BattleUnit> _Other)
{
	return IsAttackable(GetMapPos().GetDistance(_Other->GetMapPos()));
}

bool BattleUnit::IsAttackable(int2 _Other)
{
	return IsAttackable(GetMapPos().GetDistance(_Other));
}


void BattleUnit::Start()
{
	

	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
	MapUnit::Update(_DeltaTime);
}

void BattleUnit::SetMoveDir(int2 _Dir)
{
	Renderer->Off();
	FrontRenderer->On();

	if (_Dir == int2::Right)
	{
		FrontRenderer->ChangeAnimation("Left", false);
		GetTransform()->SetLocalNegativeScaleX();
		return;
	}

	GetTransform()->SetLocalPositiveScaleX();

	if (_Dir == int2::Left)
	{
		FrontRenderer->ChangeAnimation("Left", false);
		return;
	}
	if (_Dir == int2::Down)
	{
		FrontRenderer->ChangeAnimation("Down", false);
		return;
	}
	if (_Dir == int2::Up)
	{
		FrontRenderer->ChangeAnimation("Up", false);
		return;
	}
}

void BattleUnit::MoveStart()
{
	if (false == IsEventMove)
	{
		if (SoundDealy == true)
		{
			SoundDealy = false;
			return;
		}
		SoundDealy = true;
	}
	if (WalkSoundName != "")
	{
		if (GetName() == "플로리나")
		{
			GameEngineSound::Play(WalkSoundName);
			return;
		}
		GameEngineSound::Play(WalkSoundName);
	} 
}

void BattleUnit::MoveEnd()
{
	if (true == IsEventMove)
	{
		SetIdle();
	}
}

void BattleUnit::SetUnitAnimation(UnitIdentityCode _Value)
{
	bool IsShortWalk = false;
	WalkSoundName = "Walk_Foot.wav";
	switch (_Value)
	{
	case UnitIdentityCode::Lyn:
		SetName("린");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_Lyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::BladeLordLyn:
		SetName("린");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_BladeLyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Sain:
		SetName("세인");
		UnitData.SetName("Sain");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Horse.wav";
		break;
	case UnitIdentityCode::Kent:
		SetName("켄트");
		UnitData.SetName("Kent");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Horse.wav";
		break;
	case UnitIdentityCode::Florina:
		SetName("플로리나");
		UnitData.SetName("Florina");
		MapSpriteName = "Map_Florina.png";
		UnitData.IsPlayer = true;
		WalkSoundName = "Walk_Pegasus.wav";
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
	case UnitIdentityCode::WarriorDorcas:
		SetName("돌카스");
		UnitData.SetName("Dorcas");
		MapSpriteName = "Map_WarriorDorcas.png";
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
	case UnitIdentityCode::AssassinMatthew:
		SetName("메튜");
		UnitData.SetName("Matthew");
		MapSpriteName = "Map_AssassinMatthew.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Ninian:
		SetName("니니안");
		UnitData.SetName("Ninian");
		MapSpriteName = "Map_Ninian.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Lucius:
		SetName("루세아");
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
	case UnitIdentityCode::GeneralWallace:
		SetName("월레스");
		UnitData.SetName("Wallace");
		MapSpriteName = "Map_GeneralWallace.png";
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
	case UnitIdentityCode::Archer:
		UnitData.UnitCode = EnemyNum++;
		SetName("궁병");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyArcher.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Knight:
		UnitData.UnitCode = EnemyNum++;
		SetName("기사");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyKnight.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Mage:
		UnitData.UnitCode = EnemyNum++;
		SetName("메이지");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyMage.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::DarkMage:
		UnitData.UnitCode = EnemyNum++;
		SetName("다크메이지");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyMage.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Batta:
		UnitData.UnitCode = EnemyNum++;
		SetName("바타");
		UnitData.SetName("Batta");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Zugu:
		UnitData.UnitCode = EnemyNum++;
		SetName("주그");
		UnitData.SetName("Zugu");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Glass:
		UnitData.UnitCode = EnemyNum++;
		SetName("글라스");
		UnitData.SetName("Glass");
		MapSpriteName = "Map_EnemyMercenary.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Migal:
		UnitData.UnitCode = EnemyNum++;
		SetName("미갈");
		UnitData.SetName("Migal");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Carjiga:
		UnitData.UnitCode = EnemyNum++;
		SetName("카지가");
		UnitData.SetName("Carjiga");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Bool:
		UnitData.UnitCode = EnemyNum++;
		SetName("불");
		UnitData.SetName("Bool");
		MapSpriteName = "Map_EnemyKnight.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Yogi:
		UnitData.UnitCode = EnemyNum++;
		SetName("요기");
		UnitData.SetName("Yogi");
		MapSpriteName = "Map_EnemyKnight.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Eagler:
		UnitData.UnitCode = EnemyNum++;
		SetName("애글러");
		UnitData.SetName("Eagler");
		MapSpriteName = "Map_EnemyGeneral.png";
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Lundgren:
		UnitData.UnitCode = EnemyNum++;
		SetName("루드그렌");
		UnitData.SetName("Lundgren");
		MapSpriteName = "Map_EnemyGeneral.png";
		UnitData.IsPlayer = false;
		break;
	default:
		break;
	}

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

	if (Renderer != nullptr)
	{
		Renderer->Death();
		Renderer = nullptr;
		FrontRenderer->Death();
		FrontRenderer = nullptr;
	}
	Renderer = CreateComponent<SpriteRenderer>(RenderOrder::Unit);
	Renderer->SetLocalScale({ 192,192 });
	FrontRenderer = CreateComponent<SpriteRenderer>(RenderOrder::SelectUnit);
	FrontRenderer->SetLocalScale({ 192,192 });
	FrontRenderer->Off();

	Renderer->CreateAnimation({ .AnimationName = "Idle",.SpriteName = MapSpriteName, .FrameIndex = {0, 1, 2, 1}, .FrameTime = {0.5f, 0.1f, 0.5f, 0.1f} });
	if (true == UnitData.IsPlayer)
	{
		Renderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.3f, 0.1f, 0.3f, 0.1f} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.3f, 0.1f, 0.3f, 0.1f} });
	}
	else
	{
		Renderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.15f, 0.05f, 0.15f, 0.05f} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Select",.SpriteName = MapSpriteName, .FrameIndex = {3, 4, 5, 4}, .FrameTime = {0.15f, 0.05f, 0.15f, 0.05f} });
	}
	if (true == IsShortWalk)
	{
		FrontRenderer->CreateAnimation({ .AnimationName = "Left", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {6, 7, 8, 7} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Down", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {9, 10, 11, 10} });
		FrontRenderer->CreateAnimation({ .AnimationName = "Up", .SpriteName = MapSpriteName, .FrameInter = 0.2f, .FrameIndex = {12, 13, 14, 13} });
	}
	else
	{
		FrontRenderer->CreateAnimation({ "Left", MapSpriteName, 6, 9, 0.2f, true, false });
		FrontRenderer->CreateAnimation({ "Down", MapSpriteName, 10, 13, 0.2f, true, false });
		FrontRenderer->CreateAnimation({ "Up", MapSpriteName, 14, 17, 0.2f, true, false });
	}

	Renderer->ChangeAnimation("Idle");
	FrontRenderer->ChangeAnimation("Select");
}

