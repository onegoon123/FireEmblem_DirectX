#include "PrecompileHeader.h"
#include "BattleAnimationUnit.h"
#include "BattleUnit.h"
#include "SpriteRenderer.h"
#include "BattleAnimationLevel.h"
BattleAnimationUnit::BattleAnimationUnit()
{
	Animations = std::map<BattleClass, std::shared_ptr<SpriteRenderer>>();
}

BattleAnimationUnit::~BattleAnimationUnit()
{
}

void BattleAnimationUnit::SetAnimation(std::shared_ptr<BattleUnit> _Unit)
{
	SetAnimation(_Unit->GetUnitData().GetClassValue());
}

void BattleAnimationUnit::SetAnimation(BattleClass _ClassValue)
{
	ClassValue = _ClassValue;

	if (CurAnimation != nullptr)
	{
		// 이전 애니메이션이 있다면 Off
		CurAnimation->Off();
	}

	// 클래스 값에 따른 애니메이션을 찾는다
	std::map<BattleClass, std::shared_ptr<SpriteRenderer>>::iterator AnimationIter;
	AnimationIter = Animations.find(ClassValue);
	if (AnimationIter == Animations.end())
	{
		// 해당 애니메이션이 없다면 생성
		CurAnimation = CreateAnimation(ClassValue);
		Animations.emplace(std::pair<BattleClass, std::shared_ptr<SpriteRenderer>>(ClassValue, CurAnimation));
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

void BattleAnimationUnit::Damage()
{
	EffectAnimation->ChangeAnimation("Hit");
}

void BattleAnimationUnit::CriticalDamage()
{
	EffectAnimation->ChangeAnimation("Critical");
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
	EffectAnimation->ChangeAnimation("Idle");
}

void BattleAnimationUnit::Update(float _DeltaTime)
{
	if (true == CurAnimation->IsAnimationEnd())
	{
		CurAnimation->ChangeAnimation("Idle");
	}

	if (true == EffectAnimation->IsAnimationEnd())
	{
		EffectAnimation->ChangeAnimation("Idle");
	}
}

std::shared_ptr<SpriteRenderer> BattleAnimationUnit::CreateAnimation(BattleClass _ClassValue)
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







	switch (_ClassValue)
	{
	case BattleClass::Lord:
	{
		if (nullptr == GameEngineSprite::Find("Battle_Lyn.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Lyn.png").GetFullPath(), 6, 9);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_Lyn.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lyn.png", .Start = 0, .End = 24, .FrameTime = {.2f, .04f, .04f, .2f, .03f, .03f, .04f, .04f, .04f, .2f, .03f, .04f, .06f , .06f, .06f, .06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f} });
		NewAnim->SetAnimationStartEvent("Attack", 5, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 24, std::bind(&BattleAnimationLevel::TurnEnd, Level));
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lyn.png",
			.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 43, 45, 43, 46, 43, 47, 48, 49, 50, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24  }
			, .FrameTime = {.2f, .06f, .06f, .06f, .24f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f,.06f, .24f, .06f,.06f, .06f, .06f, .06f, 1.0f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f} });
		NewAnim->SetAnimationStartEvent("Critical", 46, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 24, std::bind(&BattleAnimationLevel::TurnEnd, Level));

		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lyn.png", .FrameIndex = {51, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	case BattleClass::BladeLord:
	case BattleClass::Cavalier:
	case BattleClass::PegasusKnight:
	case BattleClass::Archer:
	case BattleClass::Fighter:
	case BattleClass::Warrior:
	case BattleClass::Cleric:
	case BattleClass::Mage:
	case BattleClass::Nomad:
	case BattleClass::Thief:
	case BattleClass::Assassin:
	case BattleClass::Dancer:
	case BattleClass::Monk:
	case BattleClass::Knight:
	case BattleClass::General:
	case BattleClass::Soldier:
	case BattleClass::Mercenary:
	case BattleClass::Brigand:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyBrigand.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyBrigand.png").GetFullPath(), 5, 7);
		}
		NewAnim->CreateAnimation({ "Idle", "Battle_EnemyBrigand.png", 0, 0 });
		NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19,
			.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .5f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Attack", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Attack", 19, std::bind(&BattleAnimationLevel::TurnEnd, Level));
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19,
				.FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .5f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		NewAnim->SetAnimationStartEvent("Critical", 9, std::bind(&BattleAnimationLevel::HitEvent, Level));
		NewAnim->SetAnimationStartEvent("Critical", 19, std::bind(&BattleAnimationLevel::TurnEnd, Level));
		NewAnim->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyBrigand.png", .FrameIndex = {2, 0}, .FrameTime = {.6f, 1.0f} });
		break;
	}
	default:
		break;
	}

	return NewAnim;



}