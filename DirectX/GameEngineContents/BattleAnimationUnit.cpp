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
	IsDie = false;
	IdentityValue = _IdentityValue;

	if (CurAnimation != nullptr)
	{
		// 이전 애니메이션이 있다면 Off
		CurAnimation->Off();
	}

	if (IdentityValue == UnitIdentityCode::Sain || IdentityValue == UnitIdentityCode::Kent)
	{
		if (UnitValue->GetUnitData().GetWeaponTypeValue() == WeaponType::Sword)
		{
			IdentityValue = static_cast<UnitIdentityCode>(static_cast<int>(IdentityValue) + 1);
		}
	}
	if (IdentityValue == UnitIdentityCode::GeneralWallace)
	{
		if (UnitValue->GetUnitData().GetWeaponTypeValue() == WeaponType::Axe)
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
	CurAnimation->SetOpacity(1);
	CurAnimation->SetBrightness(0);
	CurAnimation->ChangeAnimation("Idle");
	EffectAnimation->ChangeAnimation("Idle");
	EffectAnimation->GetTransform()->SetLocalScale({ -960,640, 1 });
}

void BattleAnimationUnit::Attack()
{
	CurAnimation->ChangeAnimation("Attack");
	GetTransform()->SetLocalPosition({ 0, 0, -1 });
}

void BattleAnimationUnit::Critical()
{
	CurAnimation->ChangeAnimation("Critical");
	GetTransform()->SetLocalPosition({ 0, 0, -1 });
}

void BattleAnimationUnit::Dodge()
{
	CurAnimation->ChangeAnimation("Dodge");
	GameEngineSound::Play("Dodge.wav");
}

void BattleAnimationUnit::HitEffect(const std::string_view& _Name)
{
	EffectAnimation->ChangeAnimation(_Name);
}

void BattleAnimationUnit::Die()
{
	IsDie = true;
	Timer = 0;
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
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Effect_Miss.png").GetFullPath(), 4, 5);
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Effect_Fire.png").GetFullPath(), 5, 7);
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Effect_Heal.png").GetFullPath(), 5, 9);

	}

	std::function<void()> SetBright0 = [this] {
		CurAnimation->SetBrightness(0);
	};
	std::function<void()> SetBright1 = [this] {
		CurAnimation->SetBrightness(1);
	};

	EffectAnimation = CreateComponent<SpriteRenderer>(RenderOrder::Effect);
	EffectAnimation->GetTransform()->SetLocalScale({ -960,640, 1 });
	EffectAnimation->GetTransform()->SetWorldPosition({ 0,0, -2});
	EffectAnimation->CreateAnimation({ "Idle", "Effect_Hit.png", 8, 8 });

	EffectAnimation->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "Effect_Hit.png", .Start = 0, .End = 8, .Loop = false, .FrameTime = {.04f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f} });
	EffectAnimation->SetAnimationStartEvent("Hit", 1, SetBright1);
	EffectAnimation->SetAnimationStartEvent("Hit", 5, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Effect_Hit.png", .Start = 9, .End = 17, .Loop = false, .FrameTime = {.06f, .04f, .04f, .03f, .03f, .03f, .03f, .03f, .03f} });
	EffectAnimation->SetAnimationStartEvent("Critical", 10, SetBright1);
	EffectAnimation->SetAnimationStartEvent("Critical", 14, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Effect_Miss.png", .Start = 0, .End = 18, .Loop = false,
		.FrameTime = { .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .03f, .5f, .03f, } });
	EffectAnimation->SetAnimationStartEvent("Dodge", 1, [this] {
		EffectAnimation->GetTransform()->SetWorldScale({960, 640, 1});
		});
	EffectAnimation->SetAnimationStartEvent("Dodge", 18, [this] {
		EffectAnimation->GetTransform()->SetLocalScale({ -960,640, 1 });
		});
	EffectAnimation->CreateAnimation({ .AnimationName = "FireHit", .SpriteName = "Effect_Fire.png", .Start = 0, .End = 19, .FrameInter = 0.05f, .Loop = false, });
	EffectAnimation->SetAnimationStartEvent("FireHit", 16, SetBright1);
	EffectAnimation->SetAnimationStartEvent("FireHit", 18, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "FireCritical", .SpriteName = "Effect_Fire.png", .FrameInter = 0.05f, .Loop = false,
		.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}
		});
	EffectAnimation->SetAnimationStartEvent("FireCritical", 21, SetBright1);
	EffectAnimation->SetAnimationStartEvent("FireCritical", 25, SetBright0);

	EffectAnimation->CreateAnimation({ .AnimationName = "FireDodge", .SpriteName = "Effect_Fire.png", .Start = 0, .End = 19, .FrameInter = 0.05f, .Loop = false, });
	EffectAnimation->SetAnimationStartEvent("FireDodge", 14, std::bind(&BattleAnimationUnit::Dodge, this));

	EffectAnimation->CreateAnimation({ .AnimationName = "Heal", .SpriteName = "Effect_Heal.png", .Start = 0, .End = 40, .FrameInter = 0.05f });
	EffectAnimation->SetAnimationStartEvent("Heal", 10, SetBright1);
	EffectAnimation->SetAnimationStartEvent("Heal", 20, SetBright0);

	EffectAnimation->ChangeAnimation("Idle");
}

void BattleAnimationUnit::Update(float _DeltaTime)
{
	if (true == EffectAnimation->IsAnimationEnd())
	{
		EffectAnimation->ChangeAnimation("Idle");
	}

	if (false == IsDie) { return; }

	Timer += _DeltaTime;
	CurAnimation->SetOpacity(1 - Timer);
	CurAnimation->SetBrightness(1 - Timer);
	if (1 < Timer)
	{
		CurAnimation->SetBrightness(0);
		CurAnimation->SetOpacity(0);
		IsDie = false;
	}
}


std::shared_ptr<SpriteRenderer> BattleAnimationUnit::CreateAnimation(UnitIdentityCode _UnitIdentity)
{
	std::shared_ptr<SpriteRenderer> NewAnim;
	NewAnim = CreateComponent<SpriteRenderer>(RenderOrder::Unit);
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
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lyn.png", .Start = 0, .End = 24, .Loop = false, .FrameTime = {.2f, .08f, .08f, .2f, .04f, .04f, .08f, .08f, .08f, .6f, .04f, .08f, .06f , .06f, .06f, .08f, .08f ,.08f, .08f ,.08f, .08f ,.08f, .08f ,.08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 2, []
			{
				GameEngineSound::Play("DrawWeapon.wav");
			});
		NewAnim->SetAnimationStartEvent("Attack", 6, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 10, []
			{
				GameEngineSound::Play("WindNoise.wav");
			});
		NewAnim->SetAnimationStartEvent("Attack", 19, []
			{
				GameEngineSound::Play("Sheath.wav");
			});
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lyn.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 43, 45, 43, 46, 43, 47, 48, 49, 50, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24  }
			, .FrameTime = {.2f, .06f, .06f, .06f, .24f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f,.06f, .24f, .06f,.06f, .06f, .2f, .06f, 0.5f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f} });
		NewAnim->SetAnimationStartEvent("Critical", 2, []
			{
				GameEngineSound::Play("Sheath.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 26, []
			{
				GameEngineSound::Play("DrawWeapon.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 42, []
			{
				GameEngineSound::Play("Slash1.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 45, []
			{
				GameEngineSound::Play("Slash2.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 46, [this]
			{
				GameEngineSound::Play("Slash4.wav");
				GameEngineSound::Play("Crash.wav");
				Level->HitEvent();
			});
		NewAnim->SetAnimationStartEvent("Critical", 49, []
			{
				GameEngineSound::Play("WindNoise.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 19, []
			{
				GameEngineSound::Play("Sheath.wav");
			});
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lyn.png", .Loop = false, .FrameIndex = {51, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::BladeLordLyn:
	{
		if (nullptr == GameEngineSprite::Find("Battle_BladeLyn.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_BladeLyn.png").GetFullPath(), 6, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_BladeLyn.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_BladeLyn.png", .Start = 0, .End = 36, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .05f, .08f, .08f, .1f, .05f, .08f, .1f, .05f, .1f, .02f, .6f, .05f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 15, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 36, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_BladeLyn.png", .Loop = false,
			.FrameIndex = {37, 38, 39, 40, 41, 42, 43, 44, 45, 44, 46, 47, 48, 47, 49, 47, 49, 47, 49, 47, 48, 47, 50, 47, 51, 47, 52, 47, 53, 47, 54, 55, 56, 70, 47, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 0}
			, .FrameTime = { .08f, .08f, .08f, .08f, .05f, .08f, .08f, .08f, .04f, .04f, .04f, .2f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .2f, .04f, .1f, .04f, .1f, .04f, .1f, .04f, .2f, .04f, .04f, .25f, .01f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 70, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 0, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_BladeLyn.png", .Loop = false, .FrameIndex = {68, 69, 68, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Sain:
	{
		if (nullptr == GameEngineSprite::Find("Battle_SainLance.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_SainLance.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_SainLance.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_SainLance.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_SainLance.png", .Loop = false,
			.FrameIndex = {0, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_SainLance.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });

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
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_SainSword.png", .Loop = false,
			.FrameIndex = {0, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_SainSword.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::Kent:
	{
		if (nullptr == GameEngineSprite::Find("Battle_KentLance.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_KentLance.png").GetFullPath(), 5, 7);
		}

		NewAnim->CreateAnimation({ "Idle", "Battle_KentLance.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_KentLance.png", .Start = 0, .End = 17, .Loop = false, .FrameTime = {.2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_KentLance.png", .Loop = false,
			.FrameIndex = {0, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_KentLance.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });

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
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_KentSword.png", .Loop = false,
			.FrameIndex = {0, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			.FrameTime = {.05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .15f, .04f, .2f, .08f, .08f, .08f, .04f, .6f, .04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f,} });
		NewAnim->SetAnimationStartEvent("Critical", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_KentSword.png", .Loop = false, .FrameIndex = {30, 31, 30, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });

		break;
	}
	case UnitIdentityCode::Florina:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Florina.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Florina.png").GetFullPath(), 6, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Florina.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Florina.png", .Start = 0, .End = 32, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .04f, .08f, .08f, .5f, .04f, .08f, .04f, .08f, .08f, .4f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 13, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 32, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Florina.png", .Loop = false,
			.FrameIndex = {34,  35, 36, 37, 38, 35, 36, 37, 38, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}
			, .FrameTime = {.08f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .04f, .08f, .08f, .5f, .04f, .08f, .04f, .08f, .08f, .4f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 13, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 32, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Florina.png", .Loop = false, .FrameIndex = {41, 42, 43, 42, 41, 0}, .FrameTime = {.02f, .02f, .6f, .05f, .05f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Wil:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Wil.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Wil.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Wil.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Wil.png", .Start = 0, .End = 17, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, 0.04f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .3f, .04f, .04f, .6f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 15, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Wil.png", .Start = 18, .End = 32, .Loop = false,
			.FrameTime = { .16f, .16f, .3f, .08f, .05f, .05f, .05f, .05f, .08f, .08f, .3f, .04f, .6f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 30, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 32, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Wil.png", .Loop = false, .FrameIndex = {33, 34, 33, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Dorcas:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Dorcas.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Dorcas.png").GetFullPath(), 5, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Dorcas.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Dorcas.png", .Start = 0, .End = 14, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .05f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 6, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 14, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Dorcas.png", .Loop = false,
			.FrameIndex = {0, 17, 18, 19, 20, 21, 22, 23, 24, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
			.FrameTime = { .08f, .08f, .1f, .1f, .1f, .06f, .06f, .06f, .06f, .1f, .04f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 6, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 14, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Dorcas.png", .Loop = false, .FrameIndex = {34, 35, 34, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::WarriorDorcas:
	{
		if (nullptr == GameEngineSprite::Find("Battle_WarriorDorcas.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_WarriorDorcas.png").GetFullPath(), 5, 11);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_WarriorDorcas.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_WarriorDorcas.png", .Start = 0, .End = 13, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .05f, .05f, .6f, .08f, .06f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 6, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 13, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_WarriorDorcas.png",.Start = 13, .End = 39, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .6f, .08f, .08f, .06f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f } });
		NewAnim->SetAnimationStartEvent("Critical", 25, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 39, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_WarriorDorcas.png", .Loop = false, .FrameIndex = {14, 0}, .FrameTime = {.7f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Serra:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Serra.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Serra.png").GetFullPath(), 3, 3);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Serra.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Serra.png", .Start = 0, .End = 6, .Loop = false, 
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, 2.0f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 1, std::bind(&BattleAnimationLevel::HealEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 6, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Serra.png", .Loop = false, .FrameIndex = {7, 8, 7, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Erk:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Erk.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Erk.png").GetFullPath(), 5, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Erk.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Erk.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->CreateAnimation({ .AnimationName = "AttackLoop", .SpriteName = "Battle_Erk.png", .Start = 12, .End = 15, .FrameInter = 0.06f, .Loop = true, });
		NewAnim->CreateAnimation({ .AnimationName = "AttackEnd", .SpriteName = "Battle_Erk.png", .Start = 16, .End = 24, .FrameInter = 0.06f, .Loop = false, });

		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));
		NewAnim->SetAnimationStartEvent("AttackEnd", 23, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Erk.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Erk.png", .Loop = false, .FrameIndex = {37, 38, 37, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Rath:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Rath.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Rath.png").GetFullPath(), 5, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Rath.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Rath.png", .Start = 0, .End = 21, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, 0.2f, .04f, .6f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 15, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 21, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Rath.png", .Start = 0, .End = 21, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, 0.2f, .04f, .6f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Critical", 15, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 21, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Rath.png", .Loop = false, .FrameIndex = {0, 22, 0}, .FrameTime = {.1f, .6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Matthew:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Matthew.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Matthew.png").GetFullPath(), 5, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Matthew.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Matthew.png", .Start = 0, .End = 22, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .05f, .6f, .08f, .08f, .05f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 6, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 22, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Matthew.png", .Loop = false,
			.FrameIndex = {0, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 30, 31, 34, 30, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}, 
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .05f, .08f, .05f, .08f, .08f, .05f, .05f, .6f, .08f, .08f, .05f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 34, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 22, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Matthew.png", .Loop = false, .FrameIndex = {35, 36, 35, 0}, .FrameTime = {.08f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::AssassinMatthew:
	{
		if (nullptr == GameEngineSprite::Find("Battle_AssassinMatthew.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_AssassinMatthew.png").GetFullPath(), 6, 14);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_AssassinMatthew.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_AssassinMatthew.png", .Start = 0, .End = 34, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .05f, .05f, .05f, .04f, .04f, .04f, .04f, .08f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 16, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 34, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_AssassinMatthew.png", .Loop = false,
			.FrameIndex = {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 49,  51, 49, 51, 49, 51, 49, 51, 49, 52, 49, 54, 55, 56, 57,  58, 49, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77},
			.FrameTime = { .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .2f, .06f, .06f, .2f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .2f, .06f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 59, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 77, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_AssassinMatthew.png", .Loop = false, .FrameIndex = {78, 79, 78, 0}, .FrameTime = {.08f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Ninian:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Ninian.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Ninian.png").GetFullPath(), 6, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Ninian.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Heal", .SpriteName = "Battle_Ninian.png", .Start = 0, .End = 45, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Ninian.png", .Loop = false, .FrameIndex = {46, 47, 46, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Lucius:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Lucius.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Lucius.png").GetFullPath(), 4, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Lucius.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lucius.png", .Start = 0, .End = 16, .Loop = false, 
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .05f, .6f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 12, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 16, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lucius.png", .Start = 0, .End = 16, .Loop = false,
			.FrameTime = {.08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .05f, .6f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 12, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 16, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lucius.png", .Loop = false, .FrameIndex = {17, 18, 17, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Wallace:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Wallace.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Wallace.png").GetFullPath(), 5, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Wallace.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Wallace.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Wallace.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Critical", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Wallace.png", .Loop = false, .FrameIndex = {1, 0}, .FrameTime = {.1f, 1.0f} });
		break;
	}
	case UnitIdentityCode::GeneralWallace:
	{
		if (nullptr == GameEngineSprite::Find("Battle_GeneralWallace.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_GeneralWallace.png").GetFullPath(), 5, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_GeneralWallace.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_GeneralWallace.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_GeneralWallace.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_GeneralWallace.png", .Loop = false, .FrameIndex = {1, 2, 1, 0}, .FrameTime = {.08f, .7f, .08f, 1.0f} });
		break;
	}
	case UnitIdentityCode::GeneralWallaceAxe:
	{
		if (nullptr == GameEngineSprite::Find("Battle_GeneralWallace.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_GeneralWallace.png").GetFullPath(), 5, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_GeneralWallace.png", 29, 29 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_GeneralWallace.png", .Start = 29, .End = 56, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 39, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 56, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_GeneralWallace.png", .Start = 29, .End = 56, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 39, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 56, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_GeneralWallace.png", .Loop = false, .FrameIndex = {30, 31, 30, 29}, .FrameTime = {.08f, .7f, .08f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Brigand:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyBrigand.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyBrigand.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyBrigand.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
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
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 11, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemySoldier.png", .Loop = false,
			.FrameIndex = {12, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
			.FrameTime = {  .3f, .04f, .04f, .1f, .06f, .6f, .04f, .04f, .06f, .06f, .06f, .06f, .06f,} });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 11, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemySoldier.png", .Loop = false, .FrameIndex = {15, 16, 15, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
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
		NewAnim->SetAnimationStartEvent("Attack", 19, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 34, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false,
			.FrameIndex = {35, 36, 35, 37, 35, 36, 35,			38, 39, 40, 41, 42, 43, 44, 45, 46, 47,  48, 49, 50, 51, 52, 53, 54, 55, 56, 57,   58, 59, 60, 61, 62, 63, 64, 65, 66, 67,   68, 69, 70, 71, 72, 73, 74, 75, 76, 77,  78, 79,  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
			.FrameTime = { .1f, .1f, .1f, .1f, .1f, .1f, .1f,	.04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f,  .02f, .02f, .02f, .02f, .02f, .02f, .04f, .04f, .04f, .04f,   .04f, .6f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, } });
		NewAnim->SetAnimationStartEvent("Critical", 79, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 33, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false, .FrameIndex = {81, 82, 81, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
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
		NewAnim->SetAnimationStartEvent("Attack", 15, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 17, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyArcher.png", .Start = 18, .End = 32, .Loop = false,
			.FrameTime = { .16f, .16f, .3f, .08f, .05f, .05f, .05f, .05f, .08f, .08f, .3f, .04f, .6f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 30, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 32, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyArcher.png", .Loop = false, .FrameIndex = {33, 34, 33, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Knight:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyKnight.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyKnight.png").GetFullPath(), 5, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyKnight.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyKnight.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyKnight.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Critical", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyKnight.png", .Loop = false, .FrameIndex = {1, 0}, .FrameTime = {.1f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Mage:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyMage.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyMage.png").GetFullPath(), 5, 8);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyMage.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyMage.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->CreateAnimation({ .AnimationName = "AttackLoop", .SpriteName = "Battle_EnemyMage.png", .Start = 12, .End = 15, .FrameInter = 0.06f, .Loop = true, });
		NewAnim->CreateAnimation({ .AnimationName = "AttackEnd", .SpriteName = "Battle_EnemyMage.png", .Start = 16, .End = 24, .FrameInter = 0.06f, .Loop = false, });

		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));
		NewAnim->SetAnimationStartEvent("AttackEnd", 23, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyMage.png", .Start = 0, .End = 11, .FrameInter = 0.06f, .Loop = false, });
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 11, std::bind(&BattleAnimationUnit::AttackLoop, this, 0.8f));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyMage.png", .Loop = false, .FrameIndex = {37, 38, 37, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Batta:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Batta.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Batta.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Batta.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Batta.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Batta.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Batta.png", .Loop = false, .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Zugu:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Zugu.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Zugu.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Zugu.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Zugu.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Zugu.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Zugu.png", .Loop = false, .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Glass:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyMercenary.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyMercenary.png").GetFullPath(), 7, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyMercenary.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyMercenary.png", .Start = 0, .End = 34, .Loop = false,
			.FrameTime = { .1f, .1f, .15f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .6f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, .05f, } });
		NewAnim->SetAnimationStartEvent("Attack", 19, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 34, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false,
			.FrameIndex = {35, 36, 35, 37, 35, 36, 35,			38, 39, 40, 41, 42, 43, 44, 45, 46, 47,  48, 49, 50, 51, 52, 53, 54, 55, 56, 57,   58, 59, 60, 61, 62, 63, 64, 65, 66, 67,   68, 69, 70, 71, 72, 73, 74, 75, 76, 77,  78, 79,  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
			.FrameTime = { .1f, .1f, .1f, .1f, .1f, .1f, .1f,	.04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f,   .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f, .02f,  .02f, .02f, .02f, .02f, .02f, .02f, .04f, .04f, .04f, .04f,   .04f, .6f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, .04f, } });
		NewAnim->SetAnimationStartEvent("Critical", 79, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 33, std::bind(&BattleAnimationUnit::AttackEnd, this));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyMercenary.png", .Loop = false, .FrameIndex = {81, 82, 81, 0}, .FrameTime = {.1f, .6f, .04f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Migal:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyBrigand.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyBrigand.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyBrigand.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyBrigand.png", .Loop = false, .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Carjiga:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Carjiga.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Carjiga.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Carjiga.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Carjiga.png", .Start = 0, .End = 19, .Loop = false,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Carjiga.png", .Start = 0, .End = 19, .Loop = false,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .6f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 4, std::bind(&GameEngineSound::Play, "Jump.wav"));
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, [this] {
			GameEngineSound::Play("Landing.wav");
			AttackEnd();
			});
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Carjiga.png", .Loop = false, .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Bool:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Bool.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Bool.png").GetFullPath(), 5, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Bool.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Bool.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Bool.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Critical", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Bool.png", .Loop = false, .FrameIndex = {1, 0}, .FrameTime = {.1f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Yogi:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Yogi.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Yogi.png").GetFullPath(), 5, 5);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Yogi.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Yogi.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Attack", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Yogi.png", .Loop = false,
			.FrameIndex = {0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .6f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f} });
		NewAnim->SetAnimationStartEvent("Critical", 7, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Yogi.png", .Loop = false, .FrameIndex = {1, 0}, .FrameTime = {.1f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Eagler:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Eagler.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Eagler.png").GetFullPath(), 5, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Eagler.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Eagler.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Eagler.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Eagler.png", .Loop = false, .FrameIndex = {1, 2, 1, 0}, .FrameTime = {.08f, .7f, .08f, 1.0f} });
		break;
	}
	case UnitIdentityCode::Lundgren:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Lundgren.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Lundgren.png").GetFullPath(), 5, 12);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Lundgren.png", 0, 0 });

		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lundgren.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Attack", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lundgren.png", .Start = 0, .End = 28, .Loop = false,
			.FrameTime = { .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, .08f, } });
		NewAnim->SetAnimationStartEvent("Critical", 10, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 28, std::bind(&BattleAnimationUnit::AttackEnd, this));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lundgren.png", .Loop = false, .FrameIndex = {1, 2, 1, 0}, .FrameTime = {.08f, .7f, .08f, 1.0f} });
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
	GetTransform()->SetLocalPosition({ 0, 0, 0 });
	CurAnimation->ChangeAnimation("Idle");
	Level->TurnEnd();
}
