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
#include "BattleLevelUI.h"

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
	NewActor->SetUnitCode(UnitIdentityCode::Sain);
	NewActor->GetUnitData().LevelUp(200);
	NewActor->SetMapPos({ 3, 5 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::IronLance);
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp(99);
	NewActor->SetMapPos({ 5, 4 });
	NewActor->NewItem(ItemCode::ManiKatti);
	NewActor->NewItem(ItemCode::IronLance);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->NewItem(ItemCode::Fire);
	NewActor->NewItem(ItemCode::IronBow);
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Mage);
	NewActor->NewItem(ItemCode::IronBow);
	NewActor->NewItem(ItemCode::Fire);
	NewActor->GetUnitData().LevelUp(99);
	NewActor->SetMapPos({ 6, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Soldier);
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::IronLance);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 10, 4 });
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

	BattleUI = CreateActor<BattleLevelUI>();

	CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

