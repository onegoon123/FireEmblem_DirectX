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
#include "PhaseUI.h"

BattleLevel::BattleLevel()
{
	StateUpdate = std::bind(&BattleLevel::PlayerPhaseUpdate, this, std::placeholders::_1);
	StateEnd = std::bind(&BattleLevel::PlayerPhaseEnd, this);

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
	NewActor->NewWeapon(ItemCode::ManiKatti);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Dorcas);
	NewActor->SetMapPos({ 5, 4 });
	NewActor->NewWeapon(ItemCode::IronAxe);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Wallace);
	NewActor->SetMapPos({ 6, 5 });
	NewActor->NewWeapon(ItemCode::IronLance);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Kent);
	NewActor->SetMapPos({ 3, 5 });
	NewActor->NewWeapon(ItemCode::IronLance);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->GetUnitData().LevelUp(10);
	NewActor->NewWeapon(ItemCode::SteelSword); 
	NewActor->SetMapPos({ 8, 5 });
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->GetUnitData().LevelUp(10);
	NewActor->NewWeapon(ItemCode::SteelSword);
	NewActor->SetMapPos({ 9, 6 });
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 4 });
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
	UI_Select->GetTransform()->SetWorldPosition({448, 288});
	UI_Select->UIOff();

	UI_UnitCommand = CreateActor<UnitCommandUI>();
	UI_UnitCommand->GetTransform()->SetWorldPosition({ 448, 288 });
	UI_UnitCommand->Setting(this);
	UI_UnitCommand->Off();

	UI_Phase = CreateActor<PhaseUI>();
	UI_Phase->GetTransform()->SetWorldPosition({ 448, 288 });

	CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

