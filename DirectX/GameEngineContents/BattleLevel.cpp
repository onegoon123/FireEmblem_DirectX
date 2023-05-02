#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BattleMap.h"
#include "MapCursor.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "ArrowRender.h"
#include "ContentsEnum.h"
#include "SelectUI.h"
#include "UnitCommandUI.h"
BattleLevel::BattleLevel()
{
	StateUpdate = &BattleLevel::PlayerPhaseUpdate;
	StateEnd = &BattleLevel::PlayerPhaseEnd;

	ArrowPos.reserve(8);
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetWorldPosition({ 448, 288, -554.0f });
	// 맵을 생성
	MainMap = CreateActor<BattleMap>();

	Tiles = CreateActor<TileRender>();
	Tiles->Create(MainMap->MapScaleInt2);

	Arrows = CreateActor<ArrowRender>();
	Arrows->Create(MainMap->MapScaleInt2);

	MainCursor = CreateActor<MapCursor>();
	MainCursor->SetMapPos({ 0,0 });

	std::shared_ptr<BattleUnit> NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->SetMapPos({ 4, 5 });
	NewActor->NewWeapon(ItemCode::IronSword);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Wallace);
	NewActor->SetMapPos({ 3, 2 });
	NewActor->NewWeapon(ItemCode::IronSword);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 8, 8 });
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 8 });
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 5 });
	EnemyUnits.push_back(NewActor);

	IsMove.resize(MainMap->MapScaleInt2.y);
	for (int i = 0; i < IsMove.size(); i++)
	{
		IsMove[i].resize(MainMap->MapScaleInt2.x);
	}
	IsAttack.resize(MainMap->MapScaleInt2.y);
	for (int i = 0; i < IsAttack.size(); i++)
	{
		IsAttack[i].resize(MainMap->MapScaleInt2.x);
	}

	// UI 생성
	UI_Select = CreateActor<SelectUI>();
	UI_UnitCommand = CreateActor<UnitCommandUI>();
	UI_UnitCommand->Off();
	UI_Select->GetTransform()->SetWorldPosition({448, 288});

	CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::Update(float _DeltaTime)
{
	(this->*StateUpdate)(_DeltaTime);
}

