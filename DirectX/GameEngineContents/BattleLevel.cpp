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
#include "DebugWindow.h"
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


	// 카메라 세팅
	CameraUnit = CreateActor<MapUnit>();
	CameraUnit->SetMapPos(int2::Zero);
	MainCamera = GetMainCamera();
	MainCamera->SetProjectionType(CameraType::Orthogonal);
	MainCamera->GetTransform()->SetLocalPosition({ 448, 288, -554.0f });

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

	StageSetting();

	Tiles = CreateActor<TileRender>(RenderOrder::Tile);
	Tiles->Create(MainMap->MapScaleInt2);

	Arrows = CreateActor<ArrowRender>(RenderOrder::Unit);
	Arrows->Create(MainMap->MapScaleInt2);

	MainCursor = CreateActor<MapCursor>(RenderOrder::MapCursor);
	MainCursor->SetMapPos({ 0,0 });
	MainCursor->Setting(CameraUnit);

	BattleUI = CreateActor<BattleLevelUI>(RenderOrder::UI);
	InfoUI = CreateActor<UnitInformationUI>(RenderOrder::UI);

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

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Cursor = MainCursor;

	CurState = BattleState::None;
	ChangeState(BattleState::PlayerPhase);



}

void BattleLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();

	Tiles->Death();
	Tiles = nullptr;

	Arrows->Death();
	Arrows = nullptr;

	MainCursor->Death();
	MainCursor = nullptr;

	BattleUI->Death();
	BattleUI = nullptr;

	InfoUI->Death();
	InfoUI = nullptr;

	MainMap->Death();
	MainMap = nullptr;

	CameraUnit->Death();
	CameraUnit = nullptr;

	std::list<std::shared_ptr <BattleUnit>>::iterator UnitIter = PlayerUnits.begin();
	std::list<std::shared_ptr <BattleUnit>>::iterator UnitEnd = PlayerUnits.end();
	for (; UnitIter != UnitEnd; UnitIter++)
	{
		(*UnitIter)->Death();
		(*UnitIter) = nullptr;
	}
	PlayerUnits.clear();

	UnitIter = EnemyUnits.begin();
	UnitEnd = EnemyUnits.end();
	for (; UnitIter != UnitEnd; UnitIter++)
	{
		(*UnitIter)->Death();
		(*UnitIter) = nullptr;
	}
	EnemyUnits.clear();

	SelectUnit = nullptr;
	TargetUnit = nullptr;
	AttackableUnits.clear();
	CloseUnits.clear();
}

void BattleLevel::SetStage(int _StageNum)
{
	// 맵을 생성
	MainMap = CreateActor<BattleMap>(RenderOrder::Map);
	MainMap->SetMap(_StageNum);
}

void BattleLevel::PushPlayerUnit(std::shared_ptr<BattleUnit> _Unit)
{
	_Unit->SetTerrain(MainMap->TerrainData[_Unit->GetMapPos().y][_Unit->GetMapPos().x]);

	PlayerUnits.push_back(_Unit);
}

void BattleLevel::PushEnemyUnit(std::shared_ptr<BattleUnit> _Unit)
{
	_Unit->SetTerrain(MainMap->TerrainData[_Unit->GetMapPos().y][_Unit->GetMapPos().x]);

	EnemyUnits.push_back(_Unit);
}

void BattleLevel::CameraMove(int2 _Value)
{
	int2 CursorPos = MainCursor->WorldPos + _Value;
	int2 CursorScreenPos = CursorPos - CameraUnit->GetMapPos();
	int2 MoveValue = int2::Zero;
	if (CursorScreenPos.x < 2)
	{
		// 왼쪽으로 이동
		MoveValue += int2::Left;
	}
	else if (12 < CursorScreenPos.x)
	{
		// 오른쪽으로 이동
		MoveValue += int2::Right;
	}
	if (CursorScreenPos.y < 2)
	{
		// 아래로 이동
		MoveValue += int2::Down;
	}
	else if (7 < CursorScreenPos.y)
	{
		// 위로 이동
		MoveValue += int2::Up;
	}

	if (MoveValue == int2::Zero)
	{
		return;
	}

	int2 CameraPos = CameraUnit->GetMapPos() + MoveValue;

	if (CameraPos.x < 0 || MainMap->MapScaleInt2.x < CameraPos.x + 15)
	{
		MoveValue.x = 0;
	}
	if (CameraPos.y < 0 || MainMap->MapScaleInt2.y < CameraPos.y + 10)
	{
		MoveValue.y = 0;
	}

	CameraUnit->MoveMapPosLerp(MoveValue);

}

void BattleLevel::CameraSetPos()
{
	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = int2::Zero;

	bool Check = true;
	while (true == Check)
	{
		Check = false;
		if (CursorPos.x < 2)
		{
			Check = true;
			CursorPos.x += 1;
			MoveValue += int2::Left;
		}
		else if (12 < CursorPos.x)
		{
			Check = true;
			// 오른쪽으로 이동
			CursorPos.x -= 1;
			MoveValue += int2::Right;
		}
		if (CursorPos.y < 2)
		{
			Check = true;
			// 아래로 이동
			CursorPos.y += 1;
			MoveValue += int2::Down;
		}
		else if (7 < CursorPos.y)
		{
			Check = true;
			// 위로 이동
			CursorPos.y -= 1;
			MoveValue += int2::Up;
		}
	}

	int2 CameraPos = CameraUnit->GetMapPos() + MoveValue;

	if (CameraPos.x < 0)
	{
		CameraPos.x = 0;
	}
	else if (MainMap->MapScaleInt2.x < CameraPos.x + 15)
	{
		CameraPos.x = MainMap->MapScaleInt2.x - 15;
	}
	if (CameraPos.y < 0)
	{
		CameraPos.y = 0;
	}
	if (MainMap->MapScaleInt2.y < CameraPos.y + 10)
	{
		CameraPos.y = MainMap->MapScaleInt2.y - 10;
	}

	CameraUnit->SetMapPosLerp(CameraPos);
	MainCursor->SetCursorPos(MainCursor->WorldPos);
}

void BattleLevel::CameraUpdate(float _DeltaTime)
{
	if (true == CameraUnit->GetIsMove())
	{
		MainCamera->GetTransform()->SetLocalPosition(CameraUnit->GetTransform()->GetLocalPosition() + float4(448, 288, -554.0f));
		return;
	}
	MainCamera->GetTransform()->SetLocalPosition(CameraUnit->EndPos + float4(448, 288, -554.0f));
}
