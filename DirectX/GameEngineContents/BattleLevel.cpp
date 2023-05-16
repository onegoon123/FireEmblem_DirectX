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
#include "FieldCommandUI.h"
#include "PhaseUI.h"
#include "UICursor.h"
#include "AttackUI.h"
#include "ItemUI.h"

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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 448, 288, -554.0f });
	// 맵을 생성
	MainMap = CreateActor<BattleMap>();

	Tiles = CreateActor<TileRender>();
	Tiles->Create(MainMap->MapScaleInt2);

	Arrows = CreateActor<ArrowRender>();
	Arrows->Create(MainMap->MapScaleInt2);

	MainCursor = CreateActor<MapCursor>();
	MainCursor->SetMapPos({ 0,0 });



	//NewActor = CreateActor<BattleUnit>();
	//NewActor->SetUnitCode(UnitIdentityCode::Dorcas);
	//NewActor->SetMapPos({ 5, 4 });
	//NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	//NewActor->NewItem(ItemCode::IronAxe);
	//NewActor->NewItem(ItemCode::Vulnerary);
	//PlayerUnits.push_back(NewActor);

	//NewActor = CreateActor<BattleUnit>();
	//NewActor->SetUnitCode(UnitIdentityCode::Wallace);
	//NewActor->SetMapPos({ 6, 5 });
	//NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	//NewActor->NewItem(ItemCode::KillerLance);
	//PlayerUnits.push_back(NewActor);

	//NewActor = CreateActor<BattleUnit>();
	//NewActor->SetUnitCode(UnitIdentityCode::Kent);
	//NewActor->SetMapPos({ 3, 5 });
	//NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	//NewActor->NewItem(ItemCode::KillerLance);
	//PlayerUnits.push_back(NewActor);

	std::shared_ptr<BattleUnit> NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->SetMapPos({ 4, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::KillingSword);
	NewActor->NewItem(ItemCode::Vulnerary);
	NewActor->NewItem(ItemCode::Vulnerary);
	NewActor->GetUnitData().LevelUp(99);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 5, 5 });
	//NewActor->GetUnitData().LevelUp(99);
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 6 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 4 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
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

	UI_Select = CreateActor<SelectUI>();
	//UI_Select->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_Select->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_UnitCommand = CreateActor<UnitCommandUI>();
	//UI_UnitCommand->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_UnitCommand->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_Attack = CreateActor<AttackUI>();
	//UI_Attack->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_Attack->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_Item = CreateActor<ItemUI>();
	//UI_Attack->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_Item->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_FieldCommand = CreateActor<FieldCommandUI>();
	//UI_FieldCommand->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_FieldCommand->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_Phase = CreateActor<PhaseUI>();
	//UI_Phase->GetTransform()->SetParent(GetMainCamera()->GetTransform());
	UI_Phase->GetTransform()->SetLocalPosition({ 448, 288, 0 });

	UI_Cursor = CreateActor<UICursor>();

	//UI_Window = CreateActor<UIWindow>();
	//UI_Window->GetTransform()->SetParent(&UITransform);
	//UI_Window->GetTransform()->SetLocalPosition(float4::Zero);
	//UI_Window->Setting();

	UI_UnitCommand->Setting(this);
	UI_FieldCommand->Setting(this);
	UI_Attack->Setting(this);
	UI_Item->Setting(this);

	CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

