#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <deque>
#include <queue>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "BattleMap.h"
#include "UnitCommand.h"
bool BattleLevel::UnitMoveAnim()
{
	if (false == SelectUnit->GetIsMove())
	{
		if (ArrowPos.size() <= ++MoveIndex)
		{
			return true;
		}
		SelectUnit->SetMapPosLerp(ArrowPos[MoveIndex]);
	}


	return false;
}


int DirX[] = { 0, -1, 0, 1 };
int DirY[] = { 1, 0, -1, 0 };
int BowDirX[] = { 0, 2, 0, -2, 1, 1, -1, -1 };
int BowDirY[] = { 2, 0, -2, 0, 1, -1, 1, -1 };
struct SearchData
{
	int2 Pos;
	int MoveStat;
};
struct CalData
{
	int2 Pos = int2();
	int MoveStat = 0;
	std::vector<int2> History = std::vector<int2>();
};

void BattleLevel::MoveSearch()
{

	std::queue<SearchData> Queue;
	SearchData StartData = { SelectUnit->GetMapPos(), SelectUnit->GetMoveStat() };
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();
	Queue.push(StartData);

	for (int i = 0; i < IsMove.size(); i++)
	{
		IsMove[i].assign(IsMove[i].size(), false);
	}
	IsMove[StartData.Pos.y][StartData.Pos.x] = true;
	while (false == Queue.empty())
	{
		SearchData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			SearchData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}

			bool Check = false;
			for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
			{
				if (true == _Unit->GetIsDie()) { continue; }
				if (NextMove.Pos == _Unit->GetMapPos())
				{
					Check = true;
					break;
				}
			}
			if (true == Check)
			{
				continue;
			}

			if (ClassValue == BattleClass::PegasusKnight)
			{
				NextMove.MoveStat -= GetTerrainCostFly(NextMove.Pos);
			}
			else
			{
				NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			}

			if (NextMove.MoveStat < 0)
			{
				continue;
			}


			IsMove[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}


	if (SelectUnit->GetUnitData().GetWeaponTypeValue() == WeaponType::Bow)
	{
		AttackSearchBow();
		return;
	}
	AttackSearch();
}

void BattleLevel::AttackSearch()
{
	std::queue<SearchData> Queue;
	for (int i = 0; i < IsAttack.size(); i++)
	{
		IsAttack[i].assign(IsAttack[i].size(), false);
	}
	for (int y = 0; y < MainMap->MapScaleInt2.y; y++)
	{
		for (int x = 0; x < MainMap->MapScaleInt2.x; x++)
		{
			if (true == IsMove[y][x])
			{
				Queue.push(SearchData(int2(x, y), SelectUnit->GetRangeStat()));
			}
		}
	}

	while (false == Queue.empty())
	{
		SearchData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			SearchData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (true == IsMove[NextMove.Pos.y][NextMove.Pos.x])
			{
				continue;
			}
			if (true == IsAttack[NextMove.Pos.y][NextMove.Pos.x])
			{
				continue;
			}
			if (--NextMove.MoveStat < 0)
			{
				continue;
			}

			IsAttack[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}

}

void BattleLevel::AttackSearchBow()
{
	std::queue<SearchData> Queue;
	for (int i = 0; i < IsAttack.size(); i++)
	{
		IsAttack[i].assign(IsAttack[i].size(), false);
	}
	for (int y = 0; y < MainMap->MapScaleInt2.y; y++)
	{
		for (int x = 0; x < MainMap->MapScaleInt2.x; x++)
		{
			if (true == IsMove[y][x])
			{
				Queue.push(SearchData(int2(x, y), SelectUnit->GetRangeStat() - 1));
			}
		}
	}

	while (false == Queue.empty())
	{
		SearchData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 8; i++)
		{
			SearchData NextMove = CurrentData;
			NextMove.Pos += int2(BowDirX[i], BowDirY[i]);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (true == IsMove[NextMove.Pos.y][NextMove.Pos.x])
			{
				continue;
			}
			if (true == IsAttack[NextMove.Pos.y][NextMove.Pos.x])
			{
				continue;
			}
			if (--NextMove.MoveStat < 0)
			{
				continue;
			}

			IsAttack[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}

}

void BattleLevel::MoveSearchForEnemy()
{

	std::queue<SearchData> Queue;
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();

	SearchData StartData = { SelectUnit->GetMapPos(), SelectUnit->GetMoveStat() };
	Queue.push(StartData);

	for (int i = 0; i < IsMove.size(); i++)
	{
		IsMove[i].assign(IsMove[i].size(), false);
	}
	IsMove[StartData.Pos.y][StartData.Pos.x] = true;
	while (false == Queue.empty())
	{
		SearchData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			SearchData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}

			bool Check = false;
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (true == _Unit->GetUnitData().GetIsDie()) { continue; }
				if (NextMove.Pos == _Unit->GetMapPos())
				{
					Check = true;
					break;
				}
			}
			if (true == Check)
			{
				continue;
			}


			if (ClassValue == BattleClass::PegasusKnight)
			{
				NextMove.MoveStat -= GetTerrainCostFly(NextMove.Pos);
			}
			else
			{
				NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			}
			if (NextMove.MoveStat < 0)
			{
				continue;
			}




			IsMove[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}

	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }
		int2 Pos = _Unit->GetMapPos();
		IsMove[Pos.y][Pos.x] = false;
	}

	if (SelectUnit->GetUnitData().GetClassValue() == BattleClass::Archer)
	{
		AttackSearchBow();
		return;
	}
	AttackSearchForEnemy();
}

void BattleLevel::TargetSearchForEnemy()
{
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();

	int2 StartPos = SelectUnit->GetMapPos();
	std::vector<int2> Targets;
	Targets.reserve(PlayerUnits.size());

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		Targets.push_back(_Unit->GetMapPos());
	}

	std::vector<CalData> MoveData;
	MoveData.resize(PlayerUnits.size());
	for (int i = 0; i < MoveData.size(); i++)
	{
		MoveData[i].MoveStat = 99;
	}

	for (int UnitIndex = 0; UnitIndex < PlayerUnits.size(); UnitIndex++)
	{
		int2 TargetPos = Targets[UnitIndex];

		MainCursor->SetCursorPos(TargetPos);


		std::vector<std::vector<bool>> Moved;
		Moved.resize(IsMove.size());
		for (int i = 0; i < IsMove.size(); i++)
		{
			Moved[i].resize(IsMove[i].size());
		}




		CalData NewData = CalData();
		NewData.Pos = StartPos;
		NewData.MoveStat = 0;

		std::deque<CalData> Queue;
		Queue.push_back(NewData);
		
		while (false == Queue.empty())
		{
			CalData CurrentData = Queue.front();
			Queue.pop_front();
			for (int i = 0; i < 4; i++)
			{
				CalData NextMove = CurrentData;
				NextMove.Pos += int2(DirX[i], DirY[i]);
				NextMove.History.push_back(CurrentData.Pos);

				if (true == IsMapOut(NextMove.Pos))
				{
					continue;
				}
				if (true == Moved[NextMove.Pos.y][NextMove.Pos.x])
				{
					continue;
				}
				if (NextMove.Pos == TargetPos)
				{
					if (NextMove.MoveStat < MoveData[UnitIndex].MoveStat)
					{
						NextMove.History.push_back(TargetPos);
						MoveData[UnitIndex] = NextMove;
						break;
					}
					continue;
				}

				if (ClassValue == BattleClass::PegasusKnight)
				{
					NextMove.MoveStat += GetTerrainCostFly(NextMove.Pos);
				}
				else
				{
					NextMove.MoveStat += GetTerrainCostFoot(NextMove.Pos);
				}
				if (99 <= NextMove.MoveStat)
				{
					continue;
				}

				Moved[NextMove.Pos.y][NextMove.Pos.x] = true;
				std::deque<CalData>::const_iterator QueIter = Queue.begin();
				while (true)
				{
					if (QueIter == Queue.end())
					{
						Queue.push_back(NextMove);
						break;
					}
					if (NextMove.Pos.GetDistance(TargetPos) - NextMove.MoveStat > (*QueIter).Pos.GetDistance(TargetPos) - (*QueIter).MoveStat)
					{
						Queue.insert(QueIter, NextMove);
						break;
					}
					QueIter++;
				}
			}
		}
	}

	std::list<std::shared_ptr<BattleUnit>>::iterator UnitIter = PlayerUnits.begin();

	std::vector<int2> ResultMove;
	
	int Min = 9999;
	for (int i = 0; UnitIter != PlayerUnits.end(); UnitIter++)
	{
		if (true == (*UnitIter)->GetIsDie()) { 
			i++;
			continue; 
		}
		int MoveSize = MoveData[i].MoveStat;
		if (MoveSize < Min)
		{
			Min = MoveSize;
			ResultMove = MoveData[i].History;
		}
		i++;
	}

	int Size = (int)ResultMove.size() < SelectUnit->GetMoveStat() ? (int)ResultMove.size() : SelectUnit->GetMoveStat();
	int MoveStat = SelectUnit->GetMoveStat();
	ArrowPos.resize(Size);
	if (0 == ArrowPos.size())
	{
		return;
	}
	ArrowPos[0] = ResultMove[0];
	for (int i = 1; i < Size; i++)
	{
		if (ClassValue == BattleClass::PegasusKnight)
		{
			MoveStat -= GetTerrainCostFly(ResultMove[i]);
		}
		else
		{
			MoveStat -= GetTerrainCostFoot(ResultMove[i]);
		}
		if (MoveStat < 0)
		{
			ArrowPos.resize(i);
			break;
		}
		ArrowPos[i] = ResultMove[i];
	}
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		std::vector<int2>::iterator ArrowIter = ArrowPos.begin();
		for (; ArrowIter != ArrowPos.end(); ArrowIter++)
		{
			if (*ArrowIter == _Unit->GetMapPos())
			{
				ArrowPos.erase(ArrowIter);
				break;;
			}
		}
		if (0 == ArrowPos.size())
		{
			return;
		}
	}
	bool Check = true;
	while (true == Check)
	{
		Check = false;
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode())
			{
				continue;
			}
			std::vector<int2>::reverse_iterator ArrowIter = ArrowPos.rbegin();
			if (_Unit->GetMapPos() == ArrowPos.back())
			{
				Check = true;
				ArrowPos.resize(ArrowPos.size() - 1);
				break;
			}
		}
		if (0 == ArrowPos.size())
		{
			return;
		}
	}
}

void BattleLevel::AttackSearchForEnemy()
{
	std::queue<SearchData> Queue;
	for (int i = 0; i < IsAttack.size(); i++)
	{
		IsAttack[i].assign(IsAttack[i].size(), false);
	}
	for (int y = 0; y < MainMap->MapScaleInt2.y; y++)
	{
		for (int x = 0; x < MainMap->MapScaleInt2.x; x++)
		{
			if (true == IsMove[y][x])
			{
				Queue.push(SearchData(int2(x, y), SelectUnit->GetRangeStat()));
			}
		}
	}

	while (false == Queue.empty())
	{
		SearchData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			SearchData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (--NextMove.MoveStat < 0)
			{
				continue;
			}

			IsAttack[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}


}

void BattleLevel::SetTile()
{
	Tiles->Clear();
	if (SelectUnit == nullptr) { return; }
	if (SelectUnit->GetUnitData().GetClassValue() == BattleClass::Cleric || SelectUnit->GetUnitData().GetClassValue() == BattleClass::Dancer)
	{
		Tiles->SetTileMove(IsMove);	// 이동 및 공격 범위를 타일로 표시
		Tiles->SetTileHeal(IsAttack);	// 이동 및 공격 범위를 타일로 표시
	}
	else
	{
		Tiles->SetTile(IsMove, IsAttack);	// 이동 및 공격 범위를 타일로 표시
	}
}

void BattleLevel::AddArrow(int2 _TargetPos)
{

	// 맵 밖으로 벗어난 경우
	if (true == IsMapOut(_TargetPos))
	{
		return;
	}

	// 이동 불가능한 지역인 경우
	if (false == IsMove[_TargetPos.y][_TargetPos.x])
	{
		IsArrowOut = true;
		return;
	}

	// 선택한 유닛의 위치로 돌아간다면
	if (SelectUnit->GetMapPos() == _TargetPos)
	{
		// 화살표 초기화
		ArrowPos.clear();
		Arrows->Clear();
		IsArrowOut = false;
		ArrowPos.push_back(SelectUnit->GetMapPos());
		return;
	}

	for (int i = 0; i < ArrowPos.size(); i++)
	{
		// 이동한 곳에 화살표가 이미 있었다면
		if (ArrowPos[i] == _TargetPos)
		{
			ArrowPos.resize(i + 1);
			Arrows->SetArrow(ArrowPos);
			IsArrowOut = false;
			return;
		}
	}

	// 화살표가 이동력을 초과한 경우
	if (SelectUnit->GetMoveStat() < ArrowPos.size())
	{
		// 다시 계산
		MoveCalculation();
		IsArrowOut = false;
		return;
	}


	if (2 <= _TargetPos.GetDistance(ArrowPos.back()))
	{
		//ArrowPos.clear();	
		MoveCalculation();
		IsArrowOut = false;
		return;
	}

	ArrowPos.push_back(_TargetPos);
	Arrows->SetArrow(ArrowPos);
}

void BattleLevel::MoveCalculation()
{


	int2 StartPos = SelectUnit->GetMapPos();
	int2 TargetPos = MainCursor->WorldPos;
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();
	if (true == IsMapOut(TargetPos))
	{
		return;
	}
	if (false == IsMove[TargetPos.y][TargetPos.x])
	{
		return;
	}
	if (StartPos == TargetPos)
	{
		Arrows->Clear();
		return;
	}

	CalData NewData = CalData();
	NewData.Pos = StartPos;
	NewData.MoveStat = SelectUnit->GetMoveStat();

	std::queue<CalData> Queue;
	Queue.push(NewData);

	while (false == Queue.empty())
	{
		CalData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			CalData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			NextMove.History.push_back(CurrentData.Pos);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (false == IsMove[NextMove.Pos.y][NextMove.Pos.x])
			{
				continue;
			}
			if (NextMove.Pos == TargetPos)
			{
				NextMove.History.push_back(TargetPos);
				Arrows->SetArrow(NextMove.History);
				ArrowPos = NextMove.History;
				return;
			}

			if (ClassValue == BattleClass::PegasusKnight)
			{
				NextMove.MoveStat -= GetTerrainCostFly(NextMove.Pos);
			}
			else
			{
				NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			}
			if (NextMove.MoveStat < 0)
			{
				continue;
			}

			Queue.push(NextMove);
		}
	}
}

void BattleLevel::EnemyFindTarget()
{
	// 공격가능한 유닛들
	std::vector<std::shared_ptr<BattleUnit>> Targets;
	Targets.reserve(PlayerUnits.size());

	for (std::shared_ptr<BattleUnit> _Player : PlayerUnits)
	{
		if (true == _Player->GetIsDie()) { continue; }
		int2 PlayerPos = _Player->GetMapPos();
		if (true == IsAttack[PlayerPos.y][PlayerPos.x])
		{
			Targets.push_back(_Player);
		}
	}

	if (Targets.size() == 0)
	{
		TargetUnit = nullptr;
		return;
	}
	if (Targets.size() == 1)
	{
		TargetUnit = Targets.front();
		return;
	}

	int TargetPriority = -99;	// 타겟의 우선도

	// 타겟 우선도에 의한 결정
	for (int i = 0; i < Targets.size(); i++)
	{
		int Priority = 0;
		int BeforeTargetHP = Targets[i]->GetUnitData().GetHP();
		AttackCommand AttackData = UnitCommand::AttackSimulation(SelectUnit, Targets[i]);

		if (AttackData.TargetUnit.GetIsDie() == true)
		{
			// 적을 사망시키면 우선도 상승
			Priority += 2;
		}
		if (AttackData.SubjectUnit.GetIsDie() == false)
		{
			// 내가 안죽으면 우선도 상승
			Priority += 1;
		}
		if (BeforeTargetHP == AttackData.TargetUnit.GetHP())
		{
			// 대미지를 넣지 못하면 우선도 하락
			Priority -= 1;
		}
		if (AttackData.TargetUnit.GetClassValue() == BattleClass::Cleric)
		{
			// 타겟이 힐러라면 우선도 상승
			Priority += 1;
		}
		if (Targets[i]->GetUnitData().GetRangeStat() < SelectUnit->GetUnitData().GetRangeStat())
		{
			// 상대보다 공격 사거리가 길면 우선도 상승
			Priority += 1;
		}

		if (TargetPriority < Priority)
		{
			TargetUnit = Targets[i];
			TargetPriority = Priority;
		}
	}


}

void BattleLevel::MoveCalculationForEnemyAttack()
{
	int2 StartPos = SelectUnit->GetMapPos();
	int2 TargetPos = MainCursor->WorldPos;
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();

	if (true == IsMapOut(TargetPos))
	{
		return;
	}
	if (SelectUnit->IsAttackable(StartPos.GetDistance(TargetPos)))
	{
		ArrowPos.clear();
		return;
	}


	CalData NewData = CalData();
	NewData.Pos = StartPos;
	NewData.MoveStat = SelectUnit->GetMoveStat();

	std::queue<CalData> Queue;
	Queue.push(NewData);

	while (false == Queue.empty())
	{
		CalData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			CalData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			NextMove.History.push_back(CurrentData.Pos);

			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (false == IsMove[NextMove.Pos.y][NextMove.Pos.x])
			{
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if (true == _Unit->GetIsDie()) { continue; }
					if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }
					if (NextMove.Pos == _Unit->GetMapPos())
					{
						Queue.push(NextMove);
						break;
					}
				}
				continue;
			}

			if (ClassValue == BattleClass::PegasusKnight)
			{
				NextMove.MoveStat -= GetTerrainCostFly(NextMove.Pos);
			}
			else
			{
				NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			}
			if (NextMove.MoveStat < 0)
			{
				continue;
			}
			if (SelectUnit->IsAttackable(NextMove.Pos.GetDistance(TargetPos)))
			{
				ArrowPos = NextMove.History;
				ArrowPos.push_back(NextMove.Pos);
				return;
			}
			Queue.push(NextMove);
			continue;
		}
	}
}

void BattleLevel::MoveCalculationForEnemy()
{
	int2 StartPos = SelectUnit->GetMapPos();
	int2 TargetPos = MainCursor->WorldPos;
	BattleClass ClassValue = SelectUnit->GetUnitData().GetClassValue();

	if (true == IsMapOut(TargetPos))
	{
		return;
	}

	CalData NewData = CalData();
	NewData.Pos = StartPos;
	NewData.MoveStat = SelectUnit->GetMoveStat();

	std::queue<CalData> Queue;
	Queue.push(NewData);

	while (false == Queue.empty())
	{
		CalData CurrentData = Queue.front();
		Queue.pop();

		for (int i = 0; i < 4; i++)
		{
			CalData NextMove = CurrentData;
			NextMove.Pos += int2(DirX[i], DirY[i]);
			NextMove.History.push_back(CurrentData.Pos);
			if (true == IsMapOut(NextMove.Pos))
			{
				continue;
			}
			if (false == IsMove[NextMove.Pos.y][NextMove.Pos.x])
			{
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if (true == _Unit->GetIsDie()) { continue; }
					if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }
					if (NextMove.Pos == _Unit->GetMapPos())
					{
						Queue.push(NextMove);
						break;
					}
				}
				continue;
			}
			if (ClassValue == BattleClass::PegasusKnight)
			{
				NextMove.MoveStat -= GetTerrainCostFly(NextMove.Pos);
			}
			else
			{
				NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			}
			if (NextMove.MoveStat < 0)
			{
				continue;
			}
			if (NextMove.Pos == TargetPos)
			{
				NextMove.History.push_back(TargetPos);
				ArrowPos = NextMove.History;
				return;
			}
			Queue.push(NextMove);
			continue;
		}
	}
}

void BattleLevel::EnemyTileCheck()
{
	std::shared_ptr<BattleUnit> BeforeUnit = SelectUnit;
	Tiles->EnemyTileClear();
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (false == _Unit->GetIsCheckTile() && false == IsEnemyRangeCheck) { continue; }
		if (true == _Unit->GetIsDie()) { continue; }
		SelectUnit = _Unit;
		MoveSearchForEnemy();
		Tiles->SetEnemyTile(IsAttack);
	}
	SelectUnit = BeforeUnit;
}


void BattleLevel::UnitMove()
{
	if (true == IsMapOut(MainCursor->WorldPos)) { return; }
	if (true == IsMove[MainCursor->WorldPos.y][MainCursor->WorldPos.x])
	{
		for (std::shared_ptr<BattleUnit> _Actor : PlayerUnits)
		{
			// 나 자신, 죽은 유닛을 제외한 유닛들 중
			if (true == _Actor->GetIsDie()) { continue; }
			if (_Actor->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }

			// 이동할 위치에 있는 유닛이 있다면 종료
			if (_Actor->GetMapPos() == MainCursor->WorldPos)
			{
				return;
			}
		}
		// 이동이 가능하다면 MoveWait State로 전환
		ChangeState(BattleState::MoveWait);
	}
}

bool BattleLevel::IsMapOut(int2 _Pos)
{
	if (_Pos.x < 0)
	{
		return true;
	}
	if (MainMap->MapScaleInt2.x <= _Pos.x)
	{
		return true;
	}
	if (MainMap->MapScaleInt2.y <= _Pos.y)
	{
		return true;
	}
	if (_Pos.y < 0)
	{
		return true;
	}
	return false;
}

Terrain BattleLevel::GetTerrain(int2 _Pos)
{
	return MainMap->TerrainData[_Pos.y][_Pos.x];
}

int BattleLevel::GetTerrainCostFoot(int2 _Pos)
{
	Terrain TerrainData = MainMap->TerrainData[_Pos.y][_Pos.x];
	return BattleMap::GetTerrainCostFoot(TerrainData);
}
int BattleLevel::GetTerrainCostFly(int2 _Pos)
{
	Terrain TerrainData = MainMap->TerrainData[_Pos.y][_Pos.x];
	return BattleMap::GetTerrainCostFly(TerrainData);
}
int BattleLevel::GetTerrainDodge(int2 _Pos)
{
	Terrain TerrainData = MainMap->TerrainData[_Pos.y][_Pos.x];
	return BattleMap::GetTerrainDodge(TerrainData);
}

int BattleLevel::GetTerrainDef(int2 _Pos)
{
	Terrain TerrainData = MainMap->TerrainData[_Pos.y][_Pos.x];
	return BattleMap::GetTerrainDef(TerrainData);
}
