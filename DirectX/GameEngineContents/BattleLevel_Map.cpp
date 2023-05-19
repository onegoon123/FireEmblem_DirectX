#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <queue>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "BattleMap.h"

bool BattleLevel::UnitMoveAnim()
{
	if (false == SelectUnit->GetIsMove())
	{
		if (ArrowPos.size() == ++MoveIndex)
		{
			return true;
		}
		SelectUnit->SetMapPosLerp(ArrowPos[MoveIndex]);
	}

	
	return false;
}


int DirX[] = { 0, 1, 0, -1 };
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


			NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			if (NextMove.MoveStat < 0)
			{
				continue;
			}


			IsMove[NextMove.Pos.y][NextMove.Pos.x] = true;

			Queue.push(NextMove);
		}
	}


	if (SelectUnit->GetUnitData().GetCurWeapon()->GetWeaponTypeValue() == WeaponType::Bow)
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

	
			NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
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

	// 일단 임시
	if (false /*SelectUnit->GetClass() == 1*/)
	{
		AttackSearchForEnemy();
		return;
	}
	AttackSearchForEnemy();
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
	int2 TargetPos = MainCursor->GetMapPos();

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

			NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
			if (NextMove.MoveStat < 0)
			{
				continue;
			}

			Queue.push(NextMove);
		}
	}
}

void BattleLevel::MoveCalculationForEnemyAttack()
{
	int2 StartPos = SelectUnit->GetMapPos();
	int2 TargetPos = MainCursor->GetMapPos();

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
			NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
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
	int2 TargetPos = MainCursor->GetMapPos();

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
			NextMove.MoveStat -= GetTerrainCostFoot(NextMove.Pos);
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
	if (true == IsMapOut(MainCursor->GetMapPos())) { return; }
	if (true == IsMove[MainCursor->GetMapPos().y][MainCursor->GetMapPos().x])
	{
		for (std::shared_ptr<BattleUnit> _Actor : PlayerUnits)
		{
			// 나 자신, 죽은 유닛을 제외한 유닛들 중
			if (true == _Actor->GetIsDie()) { continue; }
			if (_Actor->GetUnitCode() == SelectUnit->GetUnitCode()) {continue;}

			// 이동할 위치에 있는 유닛이 있다면 종료
			if (_Actor->GetMapPos() == MainCursor->GetMapPos())
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

int BattleLevel::GetTerrainCostFoot(int2 _Pos)
{
	Terrain TerrainData = MainMap->TerrainData[_Pos.y][_Pos.x];
	return BattleMap::GetTerrainCostFoot(TerrainData);
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
