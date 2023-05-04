#include "PrecompileHeader.h"	
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BattleAnimationLevel.h"
#include "SpriteRenderer.h"

std::shared_ptr<BattleUnit> BattleAnimationLevel::SubjectUnit = nullptr;
std::shared_ptr<BattleUnit> BattleAnimationLevel::TargetUnit = nullptr;
std::list<AttackCommand> BattleAnimationLevel::BattleData = std::list<AttackCommand>();

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

	UnitLeft = NewActor->CreateComponent<SpriteRenderer>();
	UnitLeft->SetTexture("TestBattleBrigand.png");
	UnitLeft->SetWorldScale({ 768, 512 });
	UnitLeft->GetTransform()->SetWorldPosition({ 0, 64 });

	UnitRight = NewActor->CreateComponent<SpriteRenderer>();
	UnitRight->SetTexture("TestBattleLyn.png");
	UnitRight->SetWorldScale({ 768, 512 });
	UnitRight->GetTransform()->SetWorldPosition({ 0, 64 });

	UIRender = NewActor->CreateComponent<SpriteRenderer>();
	UIRender->SetTexture("BattleUI.png");
	UIRender->SetWorldScale({ 1024, 640 });
}

void BattleAnimationLevel::Update(float _DeltaTime)
{
	Timer += _DeltaTime;
	if (2.0f < Timer)
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}
}

void BattleAnimationLevel::LevelChangeStart()
{
	Timer = 0;
}
