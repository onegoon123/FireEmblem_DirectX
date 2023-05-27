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
#include "UnitInformationUI.h"
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
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 448, 288, -554.0f });


	// 리소스 로딩
	if (nullptr == GameEngineTexture::Find("PlayerCursor.png")) {
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		Dir.MoveParent();
		Dir.Move("Character");
		Dir.Move("BattleIcon");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		Dir.MoveParent();
		Dir.Move("Map");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		Dir.MoveParent();
		Dir.Move("Portrait");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	if (MainMap == nullptr)
	{
		// 맵을 생성
		MainMap = CreateActor<BattleMap>(RenderOrder::Map);
		MainMap->SetMap(0);

		Tiles = CreateActor<TileRender>(RenderOrder::Tile);
		Tiles->Create(MainMap->MapScaleInt2);

		Arrows = CreateActor<ArrowRender>(RenderOrder::Unit);
		Arrows->Create(MainMap->MapScaleInt2);

		MainCursor = CreateActor<MapCursor>(RenderOrder::MapCursor);
		MainCursor->SetMapPos({ 0,0 });

		BattleUI = CreateActor<BattleLevelUI>(RenderOrder::UI);
		InfoUI = CreateActor<UnitInformationUI>(RenderOrder::UI);

		std::shared_ptr<BattleUnit> NewActor;

		NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
		NewActor->SetUnitCode(UnitIdentityCode::Lyn);
		NewActor->GetUnitData().LevelUp(0);
		NewActor->SetMapPos({ 1, 4 });
		NewActor->NewItem(ItemCode::IronSword);
		NewActor->NewItem(ItemCode::ManiKatti);
		NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
		PlayerUnits.push_back(NewActor);

		NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
		NewActor->SetUnitCode(UnitIdentityCode::Kent);
		NewActor->GetUnitData().LevelUp(0);
		NewActor->SetMapPos({ 1, 5 });
		NewActor->NewItem(ItemCode::IronSword);
		NewActor->NewItem(ItemCode::ManiKatti);
		NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
		PlayerUnits.push_back(NewActor);

		NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
		NewActor->SetUnitCode(UnitIdentityCode::Dorcas);
		NewActor->GetUnitData().LevelUp(0);
		NewActor->SetMapPos({ 5, 5 });
		NewActor->NewItem(ItemCode::HandAxe);
		NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
		PlayerUnits.push_back(NewActor);

		NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
		NewActor->SetUnitCode(UnitIdentityCode::Brigand);
		NewActor->NewItem(ItemCode::IronAxe);
		NewActor->NewItem(ItemCode::HandAxe);
		NewActor->GetUnitData().LevelUp(0);
		NewActor->SetMapPos({ 1, 3 });
		NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
		EnemyUnits.push_back(NewActor);

		NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
		NewActor->SetUnitCode(UnitIdentityCode::Soldier);
		NewActor->NewItem(ItemCode::SilverLance);
		NewActor->NewItem(ItemCode::SilverLance);
		NewActor->NewItem(ItemCode::SilverLance);
		NewActor->NewItem(ItemCode::SilverLance);
		NewActor->NewItem(ItemCode::SilverLance);
		NewActor->GetUnitData().LevelUp(0);
		NewActor->SetMapPos({ 2, 4 });
		NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
		EnemyUnits.push_back(NewActor);
	}

	// 조건 초기화
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

	//CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);

}

void BattleLevel::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

void BattleLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();

	if (CurState == BattleState::BattleReturn || CurState == BattleState::EnemyBattleReturn)
	{
		return;
	}

}

void BattleLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();

	if (CurState == BattleState::BattleReturn || CurState == BattleState::EnemyBattleReturn)
	{
		return;
	}
}

