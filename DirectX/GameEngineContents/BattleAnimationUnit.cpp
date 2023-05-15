#include "PrecompileHeader.h"
#include "BattleAnimationUnit.h"
#include "BattleUnit.h"
#include "SpriteRenderer.h"
BattleAnimationUnit::BattleAnimationUnit()
{
	Animations = std::map<BattleClass, BattleAnimation>();
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

	if (CurAnimation.Renderer != nullptr)
	{
		// 이전 애니메이션이 있다면 Off
		CurAnimation.Renderer->Off();
	}

	// 클래스 값에 따른 애니메이션을 찾는다
	std::map<BattleClass, BattleAnimation>::iterator AnimationIter;
	AnimationIter = Animations.find(ClassValue);
	if (AnimationIter == Animations.end())
	{
		// 해당 애니메이션이 없다면 생성
		CurAnimation = CreateAnimation(ClassValue);
		Animations.emplace(std::pair<BattleClass, BattleAnimation>(ClassValue, CurAnimation));
	}
	else
	{
		CurAnimation = AnimationIter->second;
	}

	CurAnimation.Renderer->On();
	CurAnimation.Renderer->ChangeAnimation("Idle");
}

void BattleAnimationUnit::SetAttack()
{
	CurAnimation.Renderer->ChangeAnimation("Attack");
}

void BattleAnimationUnit::SetCritical()
{
	CurAnimation.Renderer->ChangeAnimation("Critical");
}

void BattleAnimationUnit::SetDodge()
{
	CurAnimation.Renderer->ChangeAnimation("Dodge");
}

void BattleAnimationUnit::Update(float _DeltaTime)
{
	if (true == CurAnimation.Renderer->IsAnimationEnd())
	{
		CurAnimation.Renderer->ChangeAnimation("Idle");
	}
}

BattleAnimation BattleAnimationUnit::CreateAnimation(BattleClass _ClassValue)
{
	BattleAnimation NewAnim;
	NewAnim.Renderer = CreateComponent<SpriteRenderer>();
	NewAnim.Renderer->GetTransform()->SetLocalScale({ 768, 512 });
	NewAnim.Renderer->GetTransform()->SetLocalPosition({ 0, 64 });

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
		NewAnim.Renderer->CreateAnimation({ "Idle", "Battle_Lyn.png", 0, 0 });
		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lyn.png", .Start = 0, .End = 24, .FrameTime = {.3f, .06f, .06f,.3f, .04f, .04f, .2f, .06f, .06f, .25f, .03f, .08f, .08f , .08f, .08f, .08f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f} });
		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lyn.png",
			.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29}
			, .FrameTime = {.5f, .1f, .1f, .1f, .1f, .05f, .1f, .1f, .1f} });

		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_Lyn.png", .FrameIndex = {51, 0}, .FrameTime = {.4f, 1.0f} });
		NewAnim.AttackTime = 2.5f;
		NewAnim.AttackEffectTime = 1.18f;
		NewAnim.CriticalTime = 2.5f;
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
	case BattleClass::Brigand:
	{
		if (nullptr == GameEngineSprite::Find("Battle_EnemyBrigand.png"))
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_EnemyBrigand.png").GetFullPath(), 5, 7);
		}
		NewAnim.Renderer->CreateAnimation({ "Idle", "Battle_EnemyBrigand.png", 0, 0 });
		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, .5f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, .06f, } });
		//NewAnim->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "Battle_EnemyBrigand.png", .Start = 0, .End = 19, .FrameTime = {} });
		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_EnemyBrigand.png",
			.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29}
			, .FrameTime = {.5f, .1f, .1f, .1f, .1f, .05f, .1f, .1f, .1f} });
		NewAnim.Renderer->CreateAnimation({ .AnimationName = "Dodge", .SpriteName = "Battle_EnemyBrigand.png", .FrameIndex = {2, 0}, .FrameTime = {.4f, 1.0f} });
		NewAnim.AttackTime = 2.1f;
		NewAnim.AttackEffectTime = 0.78f;
		break;
	}
	case BattleClass::Soldier:
	case BattleClass::Mercenary:
	default:
		break;
	}

	float AttackT = 0;
	for (float t : { .3f, .06f, .06f, .06f, .03f, .06f, .06f, .06f, .06f, .03f, })
	{
		AttackT += t;
	}
	AttackT;

	return NewAnim;



}