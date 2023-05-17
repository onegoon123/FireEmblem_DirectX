#include "PrecompileHeader.h"
#include "BattleAnimationUnit.h"
#include "BattleUnit.h"
#include "SpriteRenderer.h"
#include "BattleAnimationLevel.h"
BattleAnimationUnit::BattleAnimationUnit()
{
	Animations = std::map<UnitIdentityCode, std::shared_ptr<SpriteRenderer>>();
}

BattleAnimationUnit::~BattleAnimationUnit()
{
}

void BattleAnimationUnit::SetAnimation(std::shared_ptr<BattleUnit> _Unit)
{
	UnitValue = _Unit;
	SetAnimation(_Unit->GetUnitData().GetIdentityCode());
}

void BattleAnimationUnit::SetAnimation(UnitIdentityCode _IdentityValue)
{
	IdentityValue = _IdentityValue;

	if (CurAnimation != nullptr)
	{
		// 이전 애니메이션이 있다면 Off
		CurAnimation->Off();
	}

	if (IdentityValue == UnitIdentityCode::Sain || IdentityValue == UnitIdentityCode::Kent)
	{
		if (UnitValue->GetUnitData().GetCurWeapon()->GetWeaponTypeValue() == WeaponType::Sword)
		{
 			IdentityValue = static_cast<UnitIdentityCode>(static_cast<int>(IdentityValue) + 1);
		}
	}

	// 클래스 값에 따른 애니메이션을 찾는다
	std::map<UnitIdentityCode, std::shared_ptr<SpriteRenderer>>::iterator AnimationIter;
	AnimationIter = Animations.find(IdentityValue);
	if (AnimationIter == Animations.end())
	{
		// 해당 애니메이션이 없다면 생성
		CurAnimation = CreateAnimation(IdentityValue);
		Animations.emplace(std::pair<UnitIdentityCode, std::shared_ptr<SpriteRenderer>>(IdentityValue, CurAnimation));
	}
	else
	{
		CurAnimation = AnimationIter->second;
	}

	CurAnimation->On();
	CurAnimation->ChangeAnimation("Idle");
}

void BattleAnimationUnit::Attack()
{
	CurAnimation->ChangeAnimation("Attack");
}

void BattleAnimationUnit::Critical()
{
	CurAnimation->ChangeAnimation("Critical");
}

void BattleAnimationUnit::Dodge()
{
	CurAnimation->ChangeAnimation("Dodge");
}

void BattleAnimationUnit::HitEffect(const std::string_view& _Name)
{
	EffectAnimation->ChangeAnimation(_Name);
}


void BattleAnimationUnit::Start()
{
	Level = dynamic_cast<BattleAnimationLevel*>(GetLevel());
	if (Level == nullptr)
	{
		MsgAssert("BattleAnimationUnit은 BattleAnimationLevel에서만 생성 가능합니다");
		return;
	}

	if (nullptr == GameEngineSprite::Find("Effect_Hit.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("Effect");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Effect_Hit.png").GetFullPath(), 3, 9);

		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Effect_Fire.png").GetFullPath(), 5, 7);

	}

	std::function<void()> SetBright0 = [this] {
		CurAnimation->SetBrightness(0);
	};
	std::function<void()> SetBright1 = [this] {
		CurAnimation->SetBrightness(1);
	};

	EffectAnimation = CreateComponent<SpriteRenderer>();
	EffectAnimation->GetTransform()->SetLocalScale({ 960,640 });
	EffectAnimation->GetTransform()->SetLocalNegativeScaleX();
	EffectAnimation->CreateAnimation({ "Idle", "Effect_Hit.png", 8, 8 });

	EffectAnimation->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "Effect_Hit.png", .Start = 0, .End = 8, .Loop = false, .FrameTime = {.04f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f} });
	EffectAnimation->SetAnimationStartEvent("Hit", 0, SetBright1);
	EffectAnimation->SetAnimationStartEvent("Hit", 5, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Effect_Hit.png", .Start = 9, .End = 17, .Loop = false, .FrameTime = {.06f, .04f, .04f, .03f, .03f, .03f, .03f, .03f, .03f} });
	EffectAnimation->SetAnimationStartEvent("Critical", 9, SetBright1);
	EffectAnimation->SetAnimationStartEvent("Critical", 14, SetBright0);

	EffectAnimation->CreateAnimation({ "Dodge", "Effect_Hit.png", 8, 8 });
	EffectAnimation->SetAnimationStartEvent("Dodge", 8, std::bind(&BattleAnimationUnit::Dodge, this));

	EffectAnimation->CreateAnimation({ .AnimationName = "FireHit", .SpriteName = "Effect_Fire.png", .Start = 0, .End = 19, .FrameInter = 0.05f, .Loop = false,});
	EffectAnimation->SetAnimationStartEvent("FireHit", 16, SetBright1);
	EffectAnimation->SetAnimationStartEvent("FireHit", 18, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "FireCritical", .SpriteName = "Effect_Fire.png", .FrameInter = 0.05f, .Loop = false, 
		.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}
		});
	EffectAnimation->SetAnimationStartEvent("FireCritical", 21, SetBright1);
	EffectAnimation->SetAnimationStartEvent("FireCritical", 25, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "FireDodge", .SpriteName = "Effect_Fire.png", .Start = 0, .End = 19, .FrameInter = 0.05f, .Loop = false, });
	EffectAnimation->SetAnimationStartEvent("FireDodge", 14, std::bind(&BattleAnimationUnit::Dodge, this));

	EffectAnimation->ChangeAnimation("Idle");
}

void BattleAnimationUnit::Update(float _DeltaTime)
{
	if (true == EffectAnimation->IsAnimationEnd())
	{
		EffectAnimation->ChangeAnimation("Idle");
	}
}


std::shared_ptr<SpriteRenderer> BattleAnimationUnit::CreateAnimation(UnitIdentityCode _UnitIdentity)
{
	std::shared_ptr<SpriteRenderer> NewAnim;
	NewAnim = CreateComponent<SpriteRenderer>();
	NewAnim->GetTransform()->SetLocalScale({ 768, 512 });
	NewAnim->GetTransform()->SetLocalPosition({ 0, 64 });

	//std::string_view AnimationName = "";
	//std::string_view SpriteName = "";
	//size_t Start = static_cast<size_t>(-1);
	//size_t End = static_cast<size_t>(-1);
	//float FrameInter = 0.1f;
	//bool Loop = true;
	//bool ScaleToTexture = false;
	//std::vector<size_t> FrameIndex = std::vector<size_t>();
	//std::vector<float> FrameTime = std::vector<float>();

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Character");
	Dir.Move("Battle");




	switch (_UnitIdentity)
	{
	case UnitIdentityCode::Lyn:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Lyn.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Lyn.png").GetFullPath(), 6, 9);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Lyn.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lyn.png", .Start = 0, .End = 24, .Loop = false, .FrameTime = {.2f, .04f, .04f, .2f, .03f, .03f, .04f, .04f, .04f, .6f, .03f, .04f, .06f , .06f, .06f, .06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f} });
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lyn.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 43, 45, 43, 46, 43, 47, 48, 49, 50, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24  }
			, .FrameTime = {.2f, .06f, .06f, .06f, .24f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f,.06f, .24f, .06f,.06f, .06f, .06f, .06f, 1.0f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f} });
		NewAnim->SetAnimationStartEvent("Critical", 46, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lyn.png", .Loop = false, .FrameIndex = {51, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::BladeLoadLyn:
	case UnitIdentityCode::Sain:
	{
		if (nullptr == GameEngineSprite::Find("Battle_SainLance.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_SainLance.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_SainLance.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_SainLance.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_SainLance.png", .Loop = false,
			.FrameIndex = {17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_SainLance.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::SainSword:
	{
		if (nullptr == GameEngineSprite::Find("Battle_SainSword.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_SainSword.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_SainSword.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_SainSword.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_SainSword.png", .Loop = false,
			.FrameIndex = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_SainSword.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::Kent:
	{
		if (nullptr == GameEngineSprite::Find("Battle_KentLance.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_KentLance.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_KentLance.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "Battle_KentLance.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Hit", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Hit", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_KentLance.png", .Loop = false,
			.FrameIndex = {17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_KentLance.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::KentSword:
	{
		if (nullptr == GameEngineSprite::Find("Battle_KentSword.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_KentSword.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_KentSword.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_KentSword.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_KentSword.png", .Loop = false,
			.FrameIndex = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_KentSword.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::Florina:
	case UnitIdentityCode::Wil:
	case UnitIdentityCode::Dorcas:
	case UnitIdentityCode::WarriorDorcas:
	case UnitIdentityCode::Serra:
	case UnitIdentityCode::Erk:
	case UnitIdentityCode::Rath:
	case UnitIdentityCode::Matthew:
	case UnitIdentityCode::AssassinMatthew:
	case UnitIdentityCode::Ninian:
	case UnitIdentityCode::Lucius:
	case UnitIdentityCode::Wallace:
	case UnitIdentityCode::GeneralWallace:
	case UnitIdentityCode::Brigand:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyBrigand.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyBrigand.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyBrigand.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, std::bind(&BattleAnimationUnit::AttackEnd, this));
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyBrigand.png", .Loop = false, .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Soldier:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemySoldier.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemySoldier.png").GetFullPath(), 4, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemySoldier.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemySoldier.png", .Start = 0, .End = 11, .Loop = false,
			.FrameTime = { .3f, .04f, .1f, .06f, .6f, .04f, .04f, .06f, .06f, .06f, .06f, .06f,} });
		NewAnim->SetAnimationStartEvent("Attack", 3, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 11, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemySoldier.png", .Loop = false,
			.FrameIndex = {12, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
			.FrameTime = {  .3f, .04f, .04f, .1f, .06f, .6f, .04f, .04f, .06f, .06f, .06f, .06f, .06f,} });
		NewAnim->SetAnimationStartEvent("Critical", 3, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 11, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemySoldier.png", .Loop = false, .FrameIndex = {15, 16, 15, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Mercenary:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyMercenary.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyMercenary.png").GetFullPath(), 7, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyMercenary.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyMercenary.png", .Start = 0, .End = 34, .Loop = false,
			.FrameTime = { .1f, .1f, .15f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .6f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, } });
		NewAnim->SetAnimationStartEvent("Attack", 18, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 34, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false,
			.FrameIndex = {35, 36, 35, 37, 35, 36, 35,			38, 39, 40, 41, 42, 43, 44, 45, 46, 47,  48, 49, 50, 51, 52, 53, 54, 55, 56, 57,   58, 59, 60, 61, 62, 63, 64, 65, 66, 67,   68, 69, 70, 71, 72, 73, 74, 75, 76, 77,  78, 79,  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
			.FrameTime = { .1f, .1f, .1f, .1f, .1f, .1f, .1f,	.04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f,  .02f, .02f, .02f, .02f, .02f, .02f, .04f, .04f, .04f, .04f,   .04f, .6f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, } });
		NewAnim->SetAnimationStartEvent("Critical", 78, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 33, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false, .FrameIndex = {81, 82, 81, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Archer:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyArcher.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyArcher.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyArcher.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyArcher.png", .Start = 0, .End = 17, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, 0.04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .3f, .04f, .04f, .6f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 14, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyArcher.png", .Start = 18, .End = 32, .Loop = false,
			.FrameTime = { .16f, .16f, .3f, .08f, .05f, .05f, .05f, .05f, .08f, .08f, .3f, .04f, .6f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 29, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 32, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyArcher.png", .Loop = false, .FrameIndex = {33, 34, 33, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Knight:
	case UnitIdentityCode::Mage:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyMage.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyMage.png").GetFullPath(), 5, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyMage.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyMage.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false,});
		NewAnim->CreateAnimation({ .AnimationName = "AttackLoop", .SpriteName = "Battle_EnemyMage.png", .Start = 12, .End = 15, .FrameInter = 0.06f, .Loop = true, });
		NewAnim->CreateAnimation({ .AnimationName = "AttackEnd", .SpriteName = "Battle_EnemyMage.png", .Start = 16, .End = 24, .FrameInter = 0.06f, .Loop = false, });

		NewAnim->SetAnimationStartEvent("Attack", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));
		NewAnim->SetAnimationStartEvent("AttackEnd", 23, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyMage.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->SetAnimationStartEvent("Critical", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyMage.png", .Loop = false, .FrameIndex = {33, 34, 33, 0}, .FrameTime = {.04f, .6f, .04f, 1.0f} });
		break;
	}
	
	default:
		break;
	}

	return NewAnim;

}

void BattleAnimationUnit::AttackLoop(float _Timer)
{
	CurAnimation->ChangeAnimation("AttackLoop");
	Level->TimeEvent.AddEvent(_Timer, std::bind(&BattleAnimationUnit::AttackLoopEnd, this));
}

void BattleAnimationUnit::AttackLoopEnd()
{
	CurAnimation->ChangeAnimation("AttackEnd");
}

void BattleAnimationUnit::AttackEnd()
{
	CurAnimation->ChangeAnimation("Idle");
	Level->TurnEnd();
}
