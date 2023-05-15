#include "PrecompileHeader.h"
#include "BattleAnimationUnit.h"
#include "BattleUnit.h"
#include "SpriteRenderer.h"
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

	CurAnimation->ChangeAnimation("Idle");
}

void BattleAnimationUnit::SetLeft()
{
	CurAnimation->GetTransform()->SetLocalNegativeScaleX();
}

void BattleAnimationUnit::SetRight()
{
	CurAnimation->GetTransform()->SetLocalPositiveScaleX();
}

void BattleAnimationUnit::SetAttack()
{
	CurAnimation->ChangeAnimation("Attack");
}

void BattleAnimationUnit::Update(float _DeltaTime)
{
	if (true == CurAnimation->IsAnimationEnd())
	{
		CurAnimation->ChangeAnimation("Idle");
	}
}

std::shared_ptr<SpriteRenderer> BattleAnimationUnit::CreateAnimation(BattleClass _ClassValue)
{
	std::shared_ptr<SpriteRenderer> NewAnim = CreateComponent<SpriteRenderer>();
	NewAnim->GetTransform()->SetWorldScale({ 768, 512 });
	NewAnim->GetTransform()->SetWorldPosition({ 0, 64 });

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

	if (nullptr == GameEngineSprite::Find("Battle_Lyn.png"))
	{
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Battle_Lyn.png").GetFullPath(), 6, 9);
	}
	NewAnim->CreateAnimation({ "Idle", "Battle_Lyn.png", 0, 0 });


	AttackTime = 2.72f;
	AttackEffectTime = 1.18f;

	NewAnim->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Battle_Lyn.png", .Start = 0, .End = 24, .FrameTime = {.5f, .06f, .06f,.5f, .03f, .03f, .2f, .06f, .06f, .25f, .03f, .08f, .08f , .08f, .08f, .08f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f ,.06f, .06f} });
	NewAnim->CreateAnimation({ .AnimationName = "Critical", .SpriteName = "Battle_Lyn.png",
		.FrameIndex = {0, 1, 2, 3, 25, 26, 27, 28, 29}
		, .FrameTime = {.5f, .1f, .1f, .1f, .1f, .05f, .1f, .1f, .1f} });

	return NewAnim;


	switch (_ClassValue)
	{
	case BattleClass::Lord:
	{
		break;
	}
	case BattleClass::BladeLord:
		break;
	case BattleClass::Cavalier:
		break;
	case BattleClass::PegasusKnight:
		break;
	case BattleClass::Archer:
		break;
	case BattleClass::Fighter:
		break;
	case BattleClass::Warrior:
		break;
	case BattleClass::Cleric:
		break;
	case BattleClass::Mage:
		break;
	case BattleClass::Nomad:
		break;
	case BattleClass::Thief:
		break;
	case BattleClass::Assassin:
		break;
	case BattleClass::Dancer:
		break;
	case BattleClass::Monk:
		break;
	case BattleClass::Knight:
		break;
	case BattleClass::General:
		break;
	case BattleClass::Brigand:
		break;
	case BattleClass::Soldier:
		break;
	case BattleClass::Mercenary:
		break;
	default:
		break;
	}
	return nullptr;
}

