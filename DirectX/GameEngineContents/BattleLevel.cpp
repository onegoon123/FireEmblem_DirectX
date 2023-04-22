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
	StateUpdate = &BattleLevel::SelectUpdate;
	StateEnd = &BattleLevel::SelectEnd;

	ArrowPos.reserve(8);
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetWorldPosition({ 448, 288, -554.0f });
	// 맵을 생성
	MainMap = CreateActor<BattleMap>();

	Tiles = CreateActor<TileRender>();
	Tiles->Create(MainMap->MapScaleInt2);

	Arrows = CreateActor<ArrowRender>();
	Arrows->Create(MainMap->MapScaleInt2);

	// UI 생성
	UI_Select = CreateActor<SelectUI>();
	UI_UnitCommand = CreateActor<UnitCommandUI>();
	UI_UnitCommand->Off();

	MainCursor = CreateActor<MapCursor>();
	MainCursor->SetMapPos({ 0,0 });

	std::shared_ptr<BattleUnit> NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(0);
	NewActor->SetMapPos({ 3, 4 });
	//NewActor->SetClass(0);
	PlayerActors.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(1);
	NewActor->SetMapPos({ 4, 5 });
	//NewActor->SetRangeStat(2);
	PlayerActors.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(2);
	NewActor->SetMapPos({ 8, 8 });
	EnemyActors.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(3);
	NewActor->SetMapPos({ 10, 3 });
	EnemyActors.push_back(NewActor);

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


	CursorDirCheck();
}

void BattleLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	(this->*StateUpdate)(_DeltaTime);
}

