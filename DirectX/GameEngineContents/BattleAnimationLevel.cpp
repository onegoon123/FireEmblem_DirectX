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

	SubjectAnimation->SetAnimation(SubjectUnit->GetUnitData().GetClassValue());
	TargetAnimation->SetAnimation(TargetUnit->GetUnitData().GetClassValue());

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
			SubjectAnimation->SetCritical();
			float time = SubjectAnimation->GetCriticalTime();
			TimeEvent.AddEvent(SubjectAnimation->GetCriticalTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
		else
		{
			TargetAnimation->SetCritical();
			TimeEvent.AddEvent(TargetAnimation->GetCriticalTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
	}
	else if (Command.IsHit)
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->SetAttack();
			TimeEvent.AddEvent(SubjectAnimation->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
		else
		{
			TargetAnimation->SetAttack();
			TimeEvent.AddEvent(TargetAnimation->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
	}
	else
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->SetAttack();
			TimeEvent.AddEvent(SubjectAnimation->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
			TimeEvent.AddEvent(SubjectAnimation->GetAttackEffectTime(), std::bind(&BattleAnimationUnit::SetDodge, TargetAnimation));
		}
		else
		{
			TargetAnimation->SetAttack();
			SubjectAnimation->SetDodge();
			TimeEvent.AddEvent(TargetAnimation->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
			TimeEvent.AddEvent(TargetAnimation->GetAttackEffectTime(), std::bind(&BattleAnimationUnit::SetDodge, SubjectAnimation));
		}
	}
	
	BattleIter++;
}

void BattleAnimationLevel::End()
{
	GameEngineCore::ChangeLevel("BattleLevel");
}
