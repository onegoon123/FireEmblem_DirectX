#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "MapCursor.h"
#include "BattleUnit.h"
#include "ArrowRender.h"
#include "TileRender.h"
#include "SelectUI.h"
#include "UnitCommandUI.h"
#include "UnitCommand.h"
#include "FERandom.h"
#include <GameEngineCore/GameEngineCamera.h>
#include "SpriteRenderer.h"
#include "BattleMap.h"
void BattleLevel::ChangeState(BattleState _State)
{

	if (CurState != BattleState::None)
	{
		(this->*StateEnd)();
	}
	CurState = _State;

	switch (_State)
	{
	case BattleLevel::BattleState::PlayerPhase:
		StateUpdate = &BattleLevel::PlayerPhaseUpdate;
		StateEnd = &BattleLevel::PlayerPhaseEnd;
		PlayerPhaseStart();
		break;
	case BattleLevel::BattleState::Select:
		StateUpdate = &BattleLevel::SelectUpdate;
		StateEnd = &BattleLevel::SelectEnd;
		SelectStart();
		break;
	case BattleLevel::BattleState::Move:
		StateUpdate = &BattleLevel::MoveUpdate;
		StateEnd = &BattleLevel::MoveEnd;
		MoveStart();
		break;
	case BattleLevel::BattleState::MoveWait:
		StateUpdate = &BattleLevel::MoveWaitUpdate;
		StateEnd = &BattleLevel::MoveWaitEnd;
		MoveWaitStart();
		break;
	case BattleLevel::BattleState::UnitCommand:
		StateUpdate = &BattleLevel::UnitCommandUpdate;
		StateEnd = &BattleLevel::UnitCommandEnd;
		UnitCommandStart();
		break;
	case BattleLevel::BattleState::FieldCommand:
		StateUpdate = &BattleLevel::FieldCommandUpdate;
		StateEnd = &BattleLevel::FieldCommandEnd;
		FieldCommandStart();
		break;
	case BattleLevel::BattleState::Battle:
		StateUpdate = &BattleLevel::BattleUpdate;
		StateEnd = &BattleLevel::BattleEnd;
		BattleStart();
		break;
	case BattleLevel::BattleState::EnemyPhase:
		StateUpdate = &BattleLevel::EnemyPhaseUpdate;
		StateEnd = &BattleLevel::EnemyPhaseEnd;
		EnemyPhaseStart();
		break;
	case BattleLevel::BattleState::EnemySelect:
		StateUpdate = &BattleLevel::EnemySelectUpdate;
		StateEnd = &BattleLevel::EnemySelectEnd;
		EnemySelectStart();
		break;
	case BattleLevel::BattleState::EnemyMove:
		StateUpdate = &BattleLevel::EnemyMoveUpdate;
		StateEnd = &BattleLevel::EnemyMoveEnd;
		EnemyMoveStart();
		break;
	case BattleLevel::BattleState::EnemyBattle:
		StateUpdate = &BattleLevel::EnemyBattleUpdate;
		StateEnd = &BattleLevel::EnemyBattleEnd;
		EnemyBattleStart();
		break;
	case BattleLevel::BattleState::GameOver:
		StateUpdate = &BattleLevel::GameOverUpdate;
		StateEnd = &BattleLevel::GameOverEnd;
		GameOverStart();
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
	// 모든 적 유닛 턴 복구
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
	}

	ChangeState(BattleState::Select);
}

void BattleLevel::PlayerPhaseUpdate(float _DeltaTime)
{
}

void BattleLevel::PlayerPhaseEnd()
{
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		SelectUnit = _Unit;
		MainCursor->SetMapPos(SelectUnit->GetMapPos());
		UI_Select->UIOn();
		CursorDirCheck();
		SetUI_UnitData();
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

	// Select 상태시 필요한 UI 켜기
	MainCursor->On();
	UI_Select->UIOn();
	CursorDirCheck();
	if (nullptr != SelectUnit)
	{
		SetUI_UnitData();
	}
	EnemyTileCheck();
}

void BattleLevel::SelectUpdate(float _DeltaTime)
{
	CursorMove();	// 커서 이동
	UnitSelect();
}

void BattleLevel::SelectEnd()
{
	UI_Select->UIOff();
}

void BattleLevel::MoveStart()
{

	if (nullptr == SelectUnit)
	{
		MsgAssert("유닛 선택되지 않은 채 State가 변경되었습니다.");
	
	}
	BeforePos = SelectUnit->GetMapPos();

	SelectUnit->SetIsDie(true);
	EnemyTileCheck();
	SelectUnit->SetIsDie(false);

	ArrowPos.clear();
	ArrowPos.push_back(SelectUnit->GetMapPos());	// 엑터 위치에서부터 화살표 시작
	MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색

	Tiles->SetTile(IsMove, IsAttack);
	AddArrow(MainCursor->GetMapPos());

	MainCursor->On();
}

void BattleLevel::MoveUpdate(float _DeltaTime)
{
	CursorAndArrowMove();
	if (GameEngineInput::IsDown("ButtonA"))
	{
		UnitMove();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		ChangeState(BattleState::Select);
		//UnitMove();
		return;
	}
}

void BattleLevel::MoveEnd()
{
	Arrows->Clear();
	Tiles->Clear();
}

void BattleLevel::MoveWaitStart()
{
	MainCursor->Off();
	MoveTimer = 9999;
	MoveIndex = -1;
}

void BattleLevel::MoveWaitUpdate(float _DeltaTime)
{
	MoveTimer += _DeltaTime * MoveSpeed;
	if (true == UnitMoveAnim())
	{
		ChangeState(BattleState::UnitCommand);
	}
}

void BattleLevel::MoveWaitEnd()
{
	SelectUnit->SetMapPos(MainCursor->GetMapPos());
}

void BattleLevel::UnitCommandStart()
{
	EnemyTileCheck();
	UI_UnitCommand->On();

	for (int y = 0; y < IsMove.size(); y++)
	{
		for (int x = 0; x < IsMove[y].size(); x++)
		{
			IsMove[y][x] = false;
		}
	}
	IsMove[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x] = true;
	if (false/*SelectUnit->GetClass() == 1*/)
	{
		AttackSearchBow();
	}
	else
	{
		AttackSearch();
	}
	Tiles->SetTileAttack(IsAttack);


	for (std::shared_ptr<BattleUnit> _Enemy : EnemyUnits)
	{
		if (true == _Enemy->GetIsDie()) { continue; }
		int2 EnemyPos = _Enemy->GetMapPos();
		if (true == IsAttack[EnemyPos.y][EnemyPos.x])
		{
			// 공격 범위 내의 적을 발견
			int a = 0;
		}
	}
}

void BattleLevel::UnitCommandUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA"))
	{
		// 현재 임시로 대기 명령을 내리는 것으로 인식
		UnitCommand::Wait(SelectUnit);
		SelectUnit->SetIsTurnEnd(true);
		ChangeState(BattleState::Select);
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		SelectUnit->SetMapPos(BeforePos);
		ChangeState(BattleState::Move);
		return;
	}
}

void BattleLevel::UnitCommandEnd()
{
	UI_UnitCommand->Off();
	Tiles->Clear();
}

void BattleLevel::FieldCommandStart()
{
	UI_UnitCommand->On();
	MainCursor->Off();
}

void BattleLevel::FieldCommandUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA"))
	{
		ChangeState(BattleState::EnemyPhase);
		return;
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		ChangeState(BattleState::Select);
		return;
	}
}

void BattleLevel::FieldCommandEnd()
{
	UI_UnitCommand->Off();
	MainCursor->On();
}

void BattleLevel::BattleStart()
{
}

void BattleLevel::BattleUpdate(float _DeltaTime)
{
}

void BattleLevel::BattleEnd()
{
}

void BattleLevel::EnemyPhaseStart()
{
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
	}
	MainCursor->Off();
	Tiles->EnemyTileClear();
	ChangeState(BattleState::EnemySelect);
}

void BattleLevel::EnemyPhaseUpdate(float _DeltaTime)
{
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
		MoveTimer = 9999;
		MoveIndex = -1;
		return;
	}

	// 공격범위내 적 포착
	MainCursor->SetMapPos(TargetUnit->GetMapPos());
	ArrowPos.clear();
	MoveCalculationForEnemy();

	int2 MovePos = ArrowPos.back();
	MainCursor->SetMapPos(MovePos);

	MoveTimer = 9999;
	MoveIndex = -1;
}

void BattleLevel::EnemyMoveUpdate(float _DeltaTime)
{
	MoveTimer += _DeltaTime * MoveSpeed;
	if (true == UnitMoveAnim())
	{
		ChangeState(BattleState::EnemyBattle);
	}
}

void BattleLevel::EnemyMoveEnd()
{
	SelectUnit->SetMapPos(ArrowPos.back());
}

void BattleLevel::EnemyBattleStart()
{
	if (nullptr != TargetUnit)
	{
		std::list<AttackCommand> AttackDetail = UnitCommand::Attack(SelectUnit, TargetUnit);
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
	if (0.5f < CloseUpTimer)
	{
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
				ChangeState(BattleState::GameOver);
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
	int a = 0;
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
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Unit->GetUnitData().UnitCode)
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.UnitCode == _Unit->GetUnitData().UnitCode)
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Unit->GetUnitData().UnitCode)
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.UnitCode == _Unit->GetUnitData().UnitCode)
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
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Unit->GetUnitData().UnitCode)
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Unit->GetUnitData().UnitCode)
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
