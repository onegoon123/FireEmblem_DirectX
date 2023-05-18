#include "PrecompileHeader.h"	
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BattleAnimationLevel.h"
#include "SpriteRenderer.h"
#include "BattleAnimationUnit.h"
std::shared_ptr<BattleUnit> BattleAnimationLevel::SubjectUnit = nullptr;
std::shared_ptr<BattleUnit> BattleAnimationLevel::TargetUnit = nullptr;
std::list<AttackCommand> BattleAnimationLevel::BattleData = std::list<AttackCommand>();
std::list<AttackCommand>::iterator BattleAnimationLevel::BattleIter = std::list<AttackCommand>::iterator();

BattleAnimationLevel::BattleAnimationLevel()
{
}

BattleAnimationLevel::~BattleAnimationLevel()
{
}

void BattleAnimationLevel::SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data)
{
	SubjectUnit = _SubjectUnit;
	TargetUnit = _TargetUnit;
	BattleData = _Data;
	BattleIter = BattleData.begin();
}

void BattleAnimationLevel::HitEvent()
{
	std::shared_ptr<BattleAnimationUnit> DamageUnit = nullptr;
	std::shared_ptr<BattleUnit> AttackUnit = nullptr;
	std::string EffectName = "";

	if (true == (*BattleIter).SubjectAttack)
	{
		DamageUnit = TargetAnimation;
		AttackUnit = SubjectUnit;
	}
	else
	{
		DamageUnit = SubjectAnimation;
		AttackUnit = TargetUnit;
	}

	if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Mage)
	{
		EffectName = "Fire";
		// 마법사, 어쌔신 경우 다른 이펙트
	}

	if ((*BattleIter).IsCritical)
	{
		EffectName += "Critical";
	}
	else if ((*BattleIter).IsHit)
	{
		EffectName += "Hit";
	}
	else
	{
		EffectName += "Dodge";
	}


	DamageUnit->HitEffect(EffectName);
}

void BattleAnimationLevel::TurnEnd()
{
	BattleIter++;
	Test();
}

void BattleAnimationLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });
	std::shared_ptr<GameEngineActor> NewActor = CreateActor<GameEngineActor>();
	BackgroundRender = NewActor->CreateComponent<SpriteRenderer>();
	BackgroundRender->SetTexture("BattleBackground_Plains.png");
	BackgroundRender->SetLocalScale({ 960, 640 });

	TerrainLeft = NewActor->CreateComponent<SpriteRenderer>();
	TerrainLeft->SetTexture("Plain_Close.png");
	TerrainLeft->SetLocalScale({ 480, 160 });
	TerrainLeft->GetTransform()->SetLocalPosition({ -240, -112 });

	TerrainRight = NewActor->CreateComponent<SpriteRenderer>();
	TerrainRight->SetTexture("Plain_Close.png");
	TerrainRight->SetLocalScale({ -480, 160 });
	TerrainRight->GetTransform()->SetLocalPosition({ 240, -112 });

	RightUnit = CreateActor<BattleAnimationUnit>();
	LeftUnit = CreateActor<BattleAnimationUnit>();
	LeftUnit->GetTransform()->SetLocalNegativeScaleX();

	UIRender = NewActor->CreateComponent<SpriteRenderer>();
	UIRender->SetTexture("BattleUI.png");
	UIRender->SetLocalScale({ 1024, 640 });
}

void BattleAnimationLevel::Update(float _DeltaTime)
{
	TimeEvent.Update(_DeltaTime);
	if (GameEngineInput::IsPress("Right"))
	{
		LeftUnit->GetTransform()->AddLocalPosition(float4::Right * 100 * _DeltaTime);
	}
	if (GameEngineInput::IsPress("Up"))
	{
		LeftUnit->GetTransform()->AddLocalPosition(float4::Forward * 100 * _DeltaTime);
	}
	if (GameEngineInput::IsPress("Down"))
	{
		LeftUnit->GetTransform()->AddLocalPosition(float4::Back * 100 * _DeltaTime);
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsDown("Start") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}
}

void BattleAnimationLevel::LevelChangeStart()
{
	if (SubjectUnit->GetIsPlayer())
	{
		SubjectAnimation = LeftUnit;
		TargetAnimation = RightUnit;
	}
	else
	{
		SubjectAnimation = RightUnit;
		TargetAnimation = LeftUnit;
	}

	SubjectAnimation->SetAnimation(SubjectUnit);
	TargetAnimation->SetAnimation(TargetUnit);

	TimeEvent.Clear();
	Test();
}

void BattleAnimationLevel::Test()
{
	if (BattleIter == BattleData.end())
	{
		TimeEvent.AddEvent(0.5f, std::bind(&BattleAnimationLevel::End, this));
		return;
	}

	AttackCommand& Command = (*BattleIter);

	if (Command.IsCritical)
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Critical();
		}
		else
		{
			TargetAnimation->Critical();
		}
	}
	else if (Command.IsHit)
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Attack();
		}
		else
		{
			TargetAnimation->Attack();
		}
	}
	else
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Attack();
		}
		else
		{
			TargetAnimation->Attack();
		}
	}

}

void BattleAnimationLevel::End()
{
	GameEngineCore::ChangeLevel("BattleLevel");
}
