#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "FERandom.h"
#include "BattleAnimationLevel.h"
#include "SpriteRenderer.h"
#include "BattleUnit.h"
#include "BattleMap.h"
#include "MapCursor.h"
#include "TileRender.h"
#include "ArrowRender.h"
#include "UnitCommand.h"
#include "SelectUI.h"
#include "UnitCommandUI.h"
#include "PhaseUI.h"
#include "FieldCommandUI.h"
#include "DebugWindow.h" // 임시
void BattleLevel::ChangeState(BattleState _State)
{

	if (CurState != BattleState::None)
	{
		StateEnd();
	}
	CurState = _State;

	switch (_State)
	{
	case BattleLevel::BattleState::PlayerPhase:
		StateUpdate = std::bind(&BattleLevel::PlayerPhaseUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::PlayerPhaseEnd, this);
		PlayerPhaseStart();
		break;
	case BattleLevel::BattleState::Select:
		StateUpdate = std::bind(&BattleLevel::SelectUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::SelectEnd, this);
		SelectStart();
		break;
	case BattleLevel::BattleState::Move:
		StateUpdate = std::bind(&BattleLevel::MoveUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::MoveEnd, this);
		MoveStart();
		break;
	case BattleLevel::BattleState::MoveWait:
		StateUpdate = std::bind(&BattleLevel::MoveWaitUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::MoveWaitEnd, this);
		MoveWaitStart();
		break;
	case BattleLevel::BattleState::UnitCommand:
		StateUpdate = std::bind(&BattleLevel::UnitCommandUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::UnitCommandEnd, this);
		UnitCommandStart();
		break;
	case BattleLevel::BattleState::FieldCommand:
		StateUpdate = std::bind(&BattleLevel::FieldCommandUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::FieldCommandEnd, this);
		FieldCommandStart();
		break;
	case BattleLevel::BattleState::Battle:
		StateUpdate = std::bind(&BattleLevel::BattleUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::BattleEnd, this);
		BattleStart();
		break;
	case BattleLevel::BattleState::EnemyPhase:
		StateUpdate = std::bind(&BattleLevel::EnemyPhaseUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyPhaseEnd, this);
		EnemyPhaseStart();
		break;
	case BattleLevel::BattleState::EnemySelect:
		StateUpdate = std::bind(&BattleLevel::EnemySelectUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemySelectEnd, this);
		EnemySelectStart();
		break;
	case BattleLevel::BattleState::EnemyMove:
		StateUpdate = std::bind(&BattleLevel::EnemyMoveUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyMoveEnd, this);
		EnemyMoveStart();
		break;
	case BattleLevel::BattleState::EnemyBattle:
		StateUpdate = std::bind(&BattleLevel::EnemyBattleUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyBattleEnd, this);
		EnemyBattleStart();
		break;
	case BattleLevel::BattleState::GameOver:
		StateUpdate = std::bind(&BattleLevel::GameOverUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::GameOverEnd, this);
		GameOverStart();
		break;
	case BattleLevel::BattleState::TimeStone:
		StateUpdate = std::bind(&BattleLevel::TimeStoneUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::TimeStoneEnd, this);
		TimeStoneStart();
		break;
	default:
	{
		MsgAssert("아직 지정하지 않은 State 입니다");
		break;
	}
	}

}

void BattleLevel::PlayerPhaseStart()
{
	UnitCommand::PhaseStart(Faction::Player);
	// 모든 적 유닛 턴 복구
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
		_Unit->SetIdle();
	}

	// 지형에 따른 체력회복
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		switch (_Unit->GetUnitData().GetTerrainData())
		{
		case Terrain::Fort:
			_Unit->GetUnitData().RecoverPersent(0.2f);
			break;
		case Terrain::Gate:
			_Unit->GetUnitData().RecoverPersent(0.1f);
			break;
		default:
			break;
		}
	}
	MainCursor->Off();
	UI_Phase->PhaseOn(Faction::Player);
}

void BattleLevel::PlayerPhaseUpdate(float _DeltaTime)
{
	if (true == UI_Phase->PhaseUIEnd())
	{
		ChangeState(BattleState::Select);
	}
}

void BattleLevel::PlayerPhaseEnd()
{
	// 플레이어 리스트 중 가장 앞에있는 유닛을 선택
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		SelectUnit = _Unit;
		MainCursor->SetMapPos(SelectUnit->GetMapPos());
		break;
	}

}

void BattleLevel::SelectStart()
{
	// Select 상태가 시작될때 마다 모든 유닛의 행동이 끝났는지 체크
	bool IsTurnEnd = true;	// 턴이 끝났는가?
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }

		if (false == _Unit->GetIsTurnEnd())
		{
			// 아직 턴이 안끝난 유닛이 있다
			IsTurnEnd = false;
			break;
		}
	}
	// 모든 유닛의 턴이 끝났다면
	if (true == IsTurnEnd)
	{
		ChangeState(BattleState::EnemyPhase);	// 적 턴으로
		return;
	}

	// 선택 유닛 초기화
	//SelectUnit = nullptr;

	// Select State시 필요한 UI
	MainCursor->On();
	UI_Select->On();
	CursorDirCheck();
	// 선택된 유닛이 있다면 유닛 데이터 지정
	if (nullptr != SelectUnit)
	{
		CursorUnitSelect();
	}
	// 적 타일 체크
	EnemyTileCheck();
}

void BattleLevel::SelectUpdate(float _DeltaTime)
{
	if (true == IsMouseOn)
	{
		CursorMoveMouse();
	}
	else
	{
		CursorMove();	// 커서 이동
	}
	UnitSelect();	// 유닛 선택 동작들 처리

}

void BattleLevel::SelectEnd()
{
	// Select State 종료시 끄는 UI
	UI_Select->Off();
}

void BattleLevel::MoveStart()
{

	if (nullptr == SelectUnit)
	{
		MsgAssert("유닛 선택되지 않은 채 MoveState로 변경되었습니다.");
	}

	BeforePos = SelectUnit->GetMapPos();	// 이동 전 위치

	// 선택한 유닛이 없을때 기준 적 타일 체크
	SelectUnit->SetIsDie(true);
	EnemyTileCheck();
	SelectUnit->SetIsDie(false);

	MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색
	Tiles->SetTile(IsMove, IsAttack);	// 이동 및 공격 범위를 타일로 표시
	// 이동 화살표 초기화
	ArrowPos.clear();
	ArrowPos.push_back(SelectUnit->GetMapPos());	// 엑터 위치에서부터 화살표 시작
	AddArrow(ArrowPos.front());

	// Move State시 필요한 UI
	MainCursor->On();

	// 유닛 선택 애니메이션
	SelectUnit->Select();
}

void BattleLevel::MoveUpdate(float _DeltaTime)
{

	if (true == IsMouseOn)
	{
		CursorAndArrowMoveMouse();
	}
	else
	{
		CursorAndArrowMove();	// 커서 이동 및 화살표 추가
	}

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		// A버튼 (Z키) 입력시 유닛을 커서 위치로 이동
		UnitMove();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		// 커서를 선택한 유닛위치로 돌려놓은 후 Select State로 변경
		MainCursor->SetMapPos(SelectUnit->GetMapPos());
		ChangeState(BattleState::Select);
		return;
	}
	if (GameEngineInput::IsDown("RightClick"))
	{
		// Select State로 변경
		ChangeState(BattleState::Select);
		return;
	}
}

void BattleLevel::MoveEnd()
{
	// Move State 종료시 화살표와 이동타일을 제거
	Arrows->Clear();
	Tiles->Clear();
	SelectUnit->SetIdle();

}

void BattleLevel::MoveWaitStart()
{
	// MoveWait State가 시작시 값을 초기화
	MainCursor->Off();
	MoveIndex = 0;
	SelectUnit->SetBeforeMapPos();
	SelectUnit->SetMapPosLerp(ArrowPos[0]);
}

void BattleLevel::MoveWaitUpdate(float _DeltaTime)
{
	if (true == UnitMoveAnim())
	{
		// 이동 종료
		ChangeState(BattleState::UnitCommand);
	}
}

void BattleLevel::MoveWaitEnd()
{
	// 정확한 위치로 다시 지정
	SelectUnit->SetMapPos(MainCursor->GetMapPos());
	Terrain TerrainData = MainMap->TerrainData[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x];
	SelectUnit->SetTerrain(TerrainData);
}

void BattleLevel::UnitCommandStart()
{
	// 이동한 위치 기준으로 적 타일 체크
	EnemyTileCheck();

	// IsMove를 현재 위치만 true로 변경
	for (int y = 0; y < IsMove.size(); y++)
	{
		for (int x = 0; x < IsMove[y].size(); x++)
		{
			IsMove[y][x] = false;
		}
	}
	IsMove[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x] = true;

	// 클래스에 따라 현재 위치에서 공격 할 수 있는 범위 표시
	if (false/*SelectUnit->GetClass() == 1*/)
	{
		AttackSearchBow();
	}
	else
	{
		AttackSearch();
	}
	Tiles->SetTileAttack(IsAttack);

	bool IsAttackable = false;
	bool IsCloseUnit = false;

	// 공격 범위 이내에 적이 있는지 판단
	AttackableUnits.clear();
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		int2 EnemyPos = _Unit->GetMapPos();
		if (true == IsAttack[EnemyPos.y][EnemyPos.x])
		{
			// 공격 범위 내의 적을 발견 시 리스트 저장
			AttackableUnits.push_back(_Unit);
		}
	}

	// 공격 가능한 적이 있을때
	if (1 <= AttackableUnits.size())
	{
		IsAttackable = true;
	}

	// 근처에 아군 유닛이 있는지 판단
	CloseUnits.clear();
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }

		int2 UnitPos = SelectUnit->GetMapPos();
		int2 _UnitPos = _Unit->GetMapPos();

		if (_UnitPos == UnitPos + int2::Up)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Down)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Left)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Right)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
	}

	// 근처에 아군 유닛이 있을때
	if (1 <= CloseUnits.size())
	{
		IsCloseUnit = true;
	}


	// 커맨드 UI 켜기
	UI_UnitCommand->On();
	UI_UnitCommand->SetCommand(IsAttackable, IsCloseUnit);
	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";
	if (true == IsAttackable) 
	{
		Window->Text += "공격\n";
	}
	Window->Text += "소지품\n";

	if (true == IsCloseUnit)
	{
		Window->Text += "교환\n";
	}
	Window->Text += "대기\n";
}

void BattleLevel::UnitCommandUpdate(float _DeltaTime)
{

}

void BattleLevel::UnitCommandEnd()
{
	UI_UnitCommand->Off();
	Tiles->Clear();
	SelectUnit->SetIdle();
}

void BattleLevel::FieldCommandStart()
{
	//UI_UnitCommand->SetCommand(false, false);
	UI_FieldCommand->On();
	MainCursor->Off();

	// 커맨드 UI 켜기
	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "시간석\n부대\n설정\n중단\n종료";
}

void BattleLevel::FieldCommandUpdate(float _DeltaTime)
{
}

void BattleLevel::FieldCommandEnd()
{
	UI_FieldCommand->Off();
	MainCursor->On();
}

void BattleLevel::BattleStart()
{

	std::list<AttackCommand> AttackDetail = UnitCommand::Attack(SelectUnit, TargetUnit);
	BattleAnimationLevel::SetBattleData(SelectUnit, TargetUnit, AttackDetail);
	SelectUnit->SetUnitData(Unit(AttackDetail.back().SubjectUnit));
	TargetUnit->SetUnitData(Unit(AttackDetail.back().TargetUnit));

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);

	return;
}

void BattleLevel::BattleUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer)
	{
		GameEngineCore::ChangeLevel("BattleAnimationLevel");
		CloseUpTimer = 0;

		SelectUnit->SetIsTurnEnd(true);
		if (SelectUnit->GetIsDie())
		{
			SelectUnit->Off();
			SelectUnit = nullptr;

			bool IsAliveUnit = false;
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (false == _Unit->GetIsDie())
				{
					IsAliveUnit = true;
				}
			}
			if (false == IsAliveUnit)
			{
				ChangeState(BattleState::TimeStone);
				return;
			}
		}
		ChangeState(BattleState::Select);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(GetMainCamera()->GetTransform()->GetWorldPosition(), TargetUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}

void BattleLevel::BattleEnd()
{
	GetMainCamera()->GetTransform()->SetWorldPosition({ 448, 288, -554.0f });
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	MainMap->GetRenderer()->SetIsBlur(false);

	if (TargetUnit->GetIsDie())
	{
		TargetUnit->Off();
		TargetUnit = nullptr;
	}
}

void BattleLevel::EnemyPhaseStart()
{
	UnitCommand::PhaseStart(Faction::Enemy);

	IsSkip = false;

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
		_Unit->SetIdle();
	}
	MainCursor->Off();
	Tiles->EnemyTileClear();

	// 지형에 따른 체력회복
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		switch (_Unit->GetUnitData().GetTerrainData())
		{
		case Terrain::Fort:
			_Unit->GetUnitData().RecoverPersent(0.2f);
			break;
		case Terrain::Gate:
			_Unit->GetUnitData().RecoverPersent(0.1f);
			break;
		default:
			break;
		}
	}

	UI_Phase->PhaseOn(Faction::Enemy);
}

void BattleLevel::EnemyPhaseUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Start"))
	{
		IsSkip = true;
	}
	if (true == IsSkip)
	{
		UI_Phase->PhaseOff();
		ChangeState(BattleState::EnemySelect);
		return;
	}
	if (true == UI_Phase->PhaseUIEnd())
	{
		ChangeState(BattleState::EnemySelect);
	}
}

void BattleLevel::EnemyPhaseEnd()
{
}

void BattleLevel::EnemySelectStart()
{

	for (std::shared_ptr<BattleUnit> _Enemy : EnemyUnits)
	{
		if (true == _Enemy->GetIsDie()) { continue; }
		if (false == _Enemy->GetIsTurnEnd())
		{
			SelectUnit = _Enemy;
			ChangeState(BattleState::EnemyMove);

			return;
		}
	}

	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::EnemySelectUpdate(float _DeltaTime)
{
}

void BattleLevel::EnemySelectEnd()
{
}

void BattleLevel::EnemyMoveStart()
{
	int2 EnemyPos = SelectUnit->GetMapPos();
	SelectUnit->SetBeforeMapPos();
	int Min = 9999;

	MoveSearchForEnemy();

	TargetUnit = nullptr;

	for (std::shared_ptr<BattleUnit> _Player : PlayerUnits)
	{
		if (true == _Player->GetIsDie()) { continue; }
		int2 PlayerPos = _Player->GetMapPos();
		if (true == IsAttack[PlayerPos.y][PlayerPos.x])
		{
			TargetUnit = _Player;
			break;
		}
	}

	if (TargetUnit == nullptr)
	{
		// 공격범위 내의 적이 없음
		// 최대한 적과 가까워질 방법을 찾는다

		int2 MovePos = SelectUnit->GetMapPos();
		int MinDistance = 99;
		for (int y = 0; y < IsMove.size(); y++)
		{
			for (int x = 0; x < IsMove[y].size(); x++)
			{
				if (false == IsMove[y][x])
				{
					continue;
				}
				int2 Pos = { x, y };
				for (std::shared_ptr<BattleUnit> _Player : PlayerUnits)
				{
					if (true == _Player->GetIsDie()) { continue; }
					int Distance = Pos.GetDistance(_Player->GetMapPos());
					if (Distance < MinDistance)
					{
						MovePos = Pos;
						MinDistance = Distance;
					}
				}
			}
		}
		MainCursor->SetMapPos(MovePos);
		MoveCalculationForEnemy();
		MoveIndex = 0;
		return;
	}

	// 공격범위내 적 포착
	MainCursor->SetMapPos(TargetUnit->GetMapPos());
	ArrowPos.clear();
	MoveCalculationForEnemy();

	int2 MovePos = ArrowPos.back();
	MainCursor->SetMapPos(MovePos);

	MoveIndex = 0;
}

void BattleLevel::EnemyMoveUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Start"))
	{
		IsSkip = true;
	}
	if (true == IsSkip)
	{
		ChangeState(BattleState::EnemyBattle);
		return;
	}
	if (true == UnitMoveAnim())
	{
		ChangeState(BattleState::EnemyBattle);
	}
}

void BattleLevel::EnemyMoveEnd()
{
	SelectUnit->SetMapPos(ArrowPos.back());
	Terrain TerrainData = MainMap->TerrainData[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x];
	SelectUnit->SetTerrain(TerrainData);
	SelectUnit->SetIdle();
}

void BattleLevel::EnemyBattleStart()
{
	if (nullptr != TargetUnit)
	{
		std::list<AttackCommand> AttackDetail = UnitCommand::Attack(SelectUnit, TargetUnit);
		BattleAnimationLevel::SetBattleData(SelectUnit, TargetUnit, AttackDetail);
		SelectUnit->SetUnitData(Unit(AttackDetail.back().SubjectUnit));
		TargetUnit->SetUnitData(Unit(AttackDetail.back().TargetUnit));
	}
	else
	{
		UnitCommand::Wait(SelectUnit);
		ChangeState(BattleState::EnemySelect);
		return;
	}
	//ChangeState(BattleState::EnemySelect);
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);
}

void BattleLevel::EnemyBattleUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer || true == IsSkip)
	{
		if (false == IsSkip)
		{
			GameEngineCore::ChangeLevel("BattleAnimationLevel");
		}
		CloseUpTimer = 0;
		if (TargetUnit->GetIsDie())
		{
			TargetUnit->Off();
			TargetUnit = nullptr;

			bool IsAliveUnit = false;
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (false == _Unit->GetIsDie())
				{
					IsAliveUnit = true;
				}
			}
			if (false == IsAliveUnit)
			{
				ChangeState(BattleState::TimeStone);
				return;
			}
		}
		ChangeState(BattleState::EnemySelect);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(GetMainCamera()->GetTransform()->GetWorldPosition(), TargetUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}

void BattleLevel::EnemyBattleEnd()
{
	GetMainCamera()->GetTransform()->SetWorldPosition({ 448, 288, -554.0f });
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	MainMap->GetRenderer()->SetIsBlur(false);
	SelectUnit->SetIsTurnEnd(true);
	if (SelectUnit->GetIsDie())
	{
		SelectUnit->Off();
		SelectUnit = nullptr;
	}

}

static std::list<UnitCommand> Command;
static std::list<UnitCommand>::reverse_iterator RIter;
static std::list<UnitCommand>::reverse_iterator RIterEnd;

void BattleLevel::GameOverStart()
{
	Command = UnitCommand::GetCommandList();
	RIter = Command.rbegin();
	RIterEnd = Command.rend();
}
void BattleLevel::GameOverUpdate(float _DeltaTime)
{
	static float Timer = 0;
	Timer += _DeltaTime;

	if (1.0f < Timer)
	{
		Timer = 0;


		if (RIter != RIterEnd)
		{
			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
					}
				}
			}
			break;
			case CommandType::Item:
				break;
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
			}
			break;
			default:
				break;
			}
			FERandom::AddRandomCount(-(*RIter).RandomNum);
			int randc = FERandom::GetRandomCount();
			RIter++;
		}
		else
		{
			UnitCommand::ResetCommandList();
			ChangeState(BattleState::PlayerPhase);
			return;
		}
	}
}

void BattleLevel::GameOverEnd()
{
}

float EffectTimer = 0;
float MapEffectTimer = 0;
int RewindNum = 0;
enum TimeStoneState
{
	EffectIn,
	EffectOut,
	Control
};
TimeStoneState CurTimeStoneState = EffectIn;

void BattleLevel::TimeStoneStart()
{
	EffectTimer = 0;
	MapEffectTimer = 0;
	CurTimeStoneState = EffectIn;
	RewindNum = 0;

	Tiles->Clear();
	MainCursor->Off();
	Command = UnitCommand::GetCommandList();
	RIter = Command.rbegin();
	RIterEnd = Command.rend();

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);

}

void BattleLevel::TimeStoneUpdate(float _DeltaTime)
{
	EffectTimer += _DeltaTime;
	MapEffectTimer += _DeltaTime * 2;

	if (MapEffectTimer < 0.7f) {
		MainMap->GetRenderer()->SetLerp({ 0.3f, 0.0f, 0.6f }, MapEffectTimer);
		MainMap->GetRenderer()->SetBlurLevel(MapEffectTimer);
	}

	switch (CurTimeStoneState)
	{
	case EffectIn:
	{
		if (0.05 < EffectTimer)
		{
			CurTimeStoneState = EffectOut;
			return;
		}
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(EffectTimer * 200);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, EffectTimer * 200);
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(EffectTimer * 200);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, EffectTimer * 200);
		}

		break;
	}
	case EffectOut:
	{
		if (1.0f < EffectTimer)
		{
			CurTimeStoneState = Control;
			return;
		}
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(10.f - EffectTimer * 10);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, 1.f - EffectTimer);
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(10.f - EffectTimer * 10);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, 1.f - EffectTimer);
		}
		break;
	}
	case Control:
	{
		if (GameEngineInput::IsDown("Up") || GameEngineInput::IsUp("MiddleClick"))
		{
			if (RIter == RIterEnd) {
				return;
			}
			if (RewindNum + 1 == Command.size())
			{
				return;
			}
			RewindNum++;
			FERandom::AddRandomCount(-(*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						//Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeSubjectItems);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
						//Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeTargetItems);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeTargetItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						//Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeSubjectItems);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
						//Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeTargetItems);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeTargetItems);
					}
				}
				break;
			}
			case CommandType::Item:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeSubjectItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).BeforeSubjectItems);
					}
				}
				break;
			}
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}

				break;
			}
			case CommandType::EnemyPhaseStart:
			{
				static std::list<UnitCommand>::reverse_iterator NewRIter;
				NewRIter = RIter;
				//NewRIter++;
				while (NewRIter != RIterEnd)
				{
					if ((*NewRIter).TypeValue == CommandType::PlayerPhaseStart)
					{
						break;
					}

					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if ((*NewRIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitCode())
						{
							_Unit->SetIsTurnEnd(true);
							break;
						}
					}
					NewRIter++;
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			{
				static std::list<UnitCommand>::reverse_iterator NewRIter;
				NewRIter = RIter;

				//NewRIter++;
				while (NewRIter != RIterEnd)
				{
					if ((*NewRIter).TypeValue == CommandType::EnemyPhaseStart)
					{

						break;
					}

					for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
					{
						if ((*NewRIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitCode())
						{
							_Unit->SetIsTurnEnd(true);
							break;
						}
					}
					NewRIter++;
				}
				break;
			}

			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				RIter;
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}
			
			RIter++;
			

			return;
		}
		if (GameEngineInput::IsDown("Down"))
		{
			if (RIter == Command.rbegin()) { 
				return; 
			}
			RIter--;
			RewindNum--;
			FERandom::AddRandomCount((*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterSubjectItems);

					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterTargetItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterSubjectItems);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterTargetItems);
					}
				}
				break;
			}
			case CommandType::Item:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterSubjectItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						Item::LoadItemDataList(_Unit->GetUnitData().GetItems(), (*RIter).AfterSubjectItems);
					}
				}
				break;
			}
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			case CommandType::EnemyPhaseStart:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				break;
			}
			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}

			return;
		}
		break;
	}
	default:
		break;
	}


	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		for (int i = 0; i < RewindNum; i++)
		{
			UnitCommand::PopCommandList();
		}
		ChangeState(BattleState::Select);
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		while (RIter != Command.rbegin()) {
			RIter--;
			RewindNum--;
			FERandom::AddRandomCount((*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
					}
				}
				break;
			}
			case CommandType::Item:
				break;
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			case CommandType::EnemyPhaseStart:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				break;
			}
			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}
		}
		ChangeState(BattleState::Select);
		return;
	}
	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 테스트 코드 미작동");
		}
		Window->Text = "";
		size_t i = Command.size();
		for (UnitCommand _Command : Command)
		{
			Window->Text += _Command.Record;
			if (RewindNum == --i)
			{
			Window->Text += " <";
			}
			Window->Text += '\n';
		}
	}
}

void BattleLevel::TimeStoneEnd()
{
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
		_Unit->GetRenderer()->OffLerp();
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
		_Unit->GetRenderer()->OffLerp();
	}
	MainMap->GetRenderer()->OffLerp();
	MainMap->GetRenderer()->SetIsBlur(false);
}
