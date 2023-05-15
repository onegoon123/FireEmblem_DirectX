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

static float Timer = 0;
void BattleAnimationLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	std::shared_ptr<GameEngineActor> NewActor = CreateActor<GameEngineActor>();
	BackgroundRender = NewActor->CreateComponent<SpriteRenderer>();
	BackgroundRender->SetTexture("BattleBackground_Plains.png");
	BackgroundRender->SetWorldScale({ 960, 640 });

	TerrainLeft = NewActor->CreateComponent<SpriteRenderer>();
	TerrainLeft->SetTexture("Plain_Close.png");
	TerrainLeft->SetWorldScale({ 480, 160 });
	TerrainLeft->GetTransform()->SetWorldPosition({ -240, -112 });

	TerrainRight = NewActor->CreateComponent<SpriteRenderer>();
	TerrainRight->SetTexture("Plain_Close.png");
	TerrainRight->SetWorldScale({ -480, 160 });
	TerrainRight->GetTransform()->SetWorldPosition({ 240, -112 });

	UnitLeft = CreateActor<BattleAnimationUnit>();
	UnitRight = CreateActor<BattleAnimationUnit>();

	UIRender = NewActor->CreateComponent<SpriteRenderer>();
	UIRender->SetTexture("BattleUI.png");
	UIRender->SetWorldScale({ 1024, 640 });
}

void BattleAnimationLevel::Update(float _DeltaTime)
{
	TimeEvent.Update(_DeltaTime);

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsDown("Start") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
		return;
	}
	Timer += _DeltaTime;
	if (10.0f < Timer)
	{
		return;
		
	}
}

void BattleAnimationLevel::LevelChangeStart()
{
	IsPlayerSubject = SubjectUnit->GetIsPlayer();
	if (true == IsPlayerSubject)
	{
		UnitLeft->SetAnimation(SubjectUnit->GetUnitData().GetClassValue());
		UnitRight->SetAnimation(TargetUnit->GetUnitData().GetClassValue());
	}
	else
	{
		UnitLeft->SetAnimation(TargetUnit->GetUnitData().GetClassValue());
		UnitRight->SetAnimation(SubjectUnit->GetUnitData().GetClassValue());
	}
	UnitLeft->SetLeft();
	UnitRight->SetRight();

	Test();
}

void BattleAnimationLevel::Test()
{
	if (BattleIter == BattleData.end())
	{
		TimeEvent.AddEvent(0.5f, std::bind(&BattleAnimationLevel::End, this));
		return;
	}
	if (true == (*BattleIter).SubjectAttack)
	{
		if (true == IsPlayerSubject)
		{
			UnitLeft->SetAttack();
			TimeEvent.AddEvent(UnitLeft->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
		else
		{
			UnitRight->SetAttack();
			TimeEvent.AddEvent(UnitRight->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
	}
	else
	{
		if (true == IsPlayerSubject)
		{
			UnitRight->SetAttack();
			TimeEvent.AddEvent(UnitRight->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
		else
		{
			UnitLeft->SetAttack();
			TimeEvent.AddEvent(UnitLeft->GetAttackTime(), std::bind(&BattleAnimationLevel::Test, this));
		}
	}
	BattleIter++;
}

void BattleAnimationLevel::End()
{
	GameEngineCore::ChangeLevel("BattleLevel");
}
