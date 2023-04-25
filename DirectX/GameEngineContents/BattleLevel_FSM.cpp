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
void BattleLevel::ChangeState(BattleState _State)
{

	(this->*StateEnd)();

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
		//StateUpdate = &BattleLevel::Update;
		//StateEnd = &BattleLevel::End;
		//Start();
		break;
	}

}

void BattleLevel::PlayerPhaseStart()
{
	for (std::shared_ptr<BattleUnit> _Actor : EnemyActors)
	{
		if (true == _Actor->GetIsDie()) { continue; }
		_Actor->SetIsTurnEnd(false);
	}

	MainCursor->On();


	//
	//UnitCommand::Attack(PlayerActors.front(), EnemyActors.front());
	ChangeState(BattleState::Select);
}

void BattleLevel::PlayerPhaseUpdate(float _DeltaTime)
{
}

void BattleLevel::PlayerPhaseEnd()
{
}

void BattleLevel::SelectStart()
{
	bool IsTurnEnd = true;	// 턴이 끝났는가?
	for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
	{
		if (true == _Actor->GetIsDie()) { continue; }

		if (false == _Actor->GetIsTurnEnd())
		{
			// 아직 턴이 안끝난 유닛이 있다
			IsTurnEnd = false;
			break;
		}
	}
	if (true == IsTurnEnd)
	{
		ChangeState(BattleState::EnemyPhase);
		return;
	}

	MainCursor->On();
	UI_Select->UIOn();
	CursorDirCheck();
}

void BattleLevel::SelectUpdate(float _DeltaTime)
{
	CursorMove();

	if (GameEngineInput::IsDown("OK"))
	{

		for (std::shared_ptr<BattleUnit> CurActor : PlayerActors)
		{
			if (true == CurActor->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == CurActor->GetMapPos())
			{
				if (true == CurActor->GetIsTurnEnd())
				{
					// 턴이 종료된 유닛
					break;
				}
				SelectUnit = CurActor;
				ChangeState(BattleState::Move);
				return;
			}
		}

		ChangeState(BattleState::FieldCommand);
		return;
	}
}

void BattleLevel::SelectEnd()
{
	UI_Select->UIOff();
}

void BattleLevel::MoveStart()
{

	if (nullptr == SelectUnit)
	{
		MsgAssert("Actor가 선택되지 않은 채 State가 변경되었습니다.");
	}
	BeforePos = SelectUnit->GetMapPos();
	ArrowPos.clear();
	ArrowPos.push_back(SelectUnit->GetMapPos());	// 엑터 위치에서부터 화살표 시작
	MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색

	Tiles->SetTile(IsMove);
	Tiles->SetTileAttack(IsAttack);
	AddArrow(MainCursor->GetMapPos());

	MainCursor->On();
}

void BattleLevel::MoveUpdate(float _DeltaTime)
{
	CursorAndArrowMove();
	if (GameEngineInput::IsDown("OK"))
	{
		UnitMove();
		return;
	}
	if (GameEngineInput::IsDown("Cancel"))
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


	for (std::shared_ptr<BattleUnit> _Enemy : EnemyActors)
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
	if (GameEngineInput::IsDown("OK"))
	{
		// 현재 임시로 대기 명령을 내리는 것으로 인식
		UnitCommand::Wait(SelectUnit);
		SelectUnit->SetIsTurnEnd(true);
		ChangeState(BattleState::Select);
	}
	if (GameEngineInput::IsDown("Cancel"))
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
	if (GameEngineInput::IsDown("OK"))
	{
		ChangeState(BattleState::EnemyPhase);
		return;
	}
	if (GameEngineInput::IsDown("Cancel"))
	{
		ChangeState(BattleState::PlayerPhase);
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
	for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
	{
		if (true == _Actor->GetIsDie()) { continue; }
		_Actor->SetIsTurnEnd(false);
	}
	MainCursor->Off();
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

	for (std::shared_ptr<BattleUnit> _Enemy : EnemyActors)
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

	for (std::shared_ptr<BattleUnit> _Player : PlayerActors)
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
				for (std::shared_ptr<BattleUnit> _Player : PlayerActors)
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
		SelectUnit->UnitData = Unit(AttackDetail.back().SubjectUnit);
		TargetUnit->UnitData = Unit(AttackDetail.back().TargetUnit);

		if (SelectUnit->GetIsDie())
		{
			SelectUnit = nullptr;
		}
		if (TargetUnit->GetIsDie())
		{
			TargetUnit = nullptr;

			bool IsAliveUnit = false;
			for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
			{
				if (false == _Actor->GetIsDie())
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
	}
	else
	{
		UnitCommand::Wait(SelectUnit);
	}
	ChangeState(BattleState::EnemySelect);
}

void BattleLevel::EnemyBattleUpdate(float _DeltaTime)
{
}

void BattleLevel::EnemyBattleEnd()
{
	if (nullptr != SelectUnit)
	{
		SelectUnit->SetIsTurnEnd(true);
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
				for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeSubjectUnit;
						_Actor->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Actor : EnemyActors)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeSubjectUnit;
						_Actor->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
				{
					if ((*RIter).BeforeTargetUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeTargetUnit;
					}
				}
				for (std::shared_ptr<BattleUnit> _Actor : EnemyActors)
				{
					if ((*RIter).BeforeTargetUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeTargetUnit;
					}
				}
			}
				break;
			case CommandType::Item:
				break;
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeSubjectUnit;
						_Actor->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Actor : EnemyActors)
				{
					if ((*RIter).BeforeSubjectUnit.UnitCode == _Actor->GetUnitCode())
					{
						_Actor->UnitData = (*RIter).BeforeSubjectUnit;
						_Actor->SetMapPos((*RIter).BeforeSubjectUnitPos);
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
