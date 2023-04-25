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
#include "SelectUI.h"
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{

	if (
		PreesTime < GameEngineInput::GetPressTime("UpMove") ||
		PreesTime < GameEngineInput::GetPressTime("DownMove") ||
		PreesTime < GameEngineInput::GetPressTime("LeftMove") ||
		PreesTime < GameEngineInput::GetPressTime("RightMove")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("UpMove") &&
		GameEngineInput::IsFree("DownMove") &&
		GameEngineInput::IsFree("LeftMove") &&
		GameEngineInput::IsFree("RightMove")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("UpMove") || (GameEngineInput::IsPress("UpMove") && PressOK))
	{

		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("DownMove") || (GameEngineInput::IsPress("DownMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("LeftMove") || (GameEngineInput::IsPress("LeftMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("RightMove") || (GameEngineInput::IsPress("RightMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		MainCursor->MoveMapPosLerp(MoveValue);
		CursorDirCheck();	// 커서의 방향(정중앙 기준) 체크
	}
}

void BattleLevel::CursorAndArrowMove()
{

	if (
		PreesTime < GameEngineInput::GetPressTime("UpMove") ||
		PreesTime < GameEngineInput::GetPressTime("DownMove") ||
		PreesTime < GameEngineInput::GetPressTime("LeftMove") ||
		PreesTime < GameEngineInput::GetPressTime("RightMove")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("UpMove") &&
		GameEngineInput::IsFree("DownMove") &&
		GameEngineInput::IsFree("LeftMove") &&
		GameEngineInput::IsFree("RightMove")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("UpMove") || (GameEngineInput::IsPress("UpMove") && PressOK))
	{

		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("DownMove") || (GameEngineInput::IsPress("DownMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("LeftMove") || (GameEngineInput::IsPress("LeftMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("RightMove") || (GameEngineInput::IsPress("RightMove") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		MainCursor->MoveMapPosLerp(MoveValue);
		AddArrow(MainCursor->GetMapPos());
	}
}

void BattleLevel::CursorDirCheck()
{
	float4 CursorPos = MainCursor->EndPos;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	UIDir CursorDir = UIDir::None;

	if (CursorPos.ix() < ScreenSize.hix())
	{
		// 왼쪽
		if (CursorPos.iy() > ScreenSize.hiy())
		{
			// 위
			CursorDir = UIDir::LeftUp;
		}
		else
		{
			// 아래
			CursorDir = UIDir::LeftDown;
		}
	}
	else
	{
		// 오른쪽
		if (CursorPos.iy() > ScreenSize.hiy())
		{
			// 위
			CursorDir = UIDir::RightUp;
		}
		else
		{
			// 아래
			CursorDir = UIDir::RightDown;
		}
	}

	UI_Select->SetCursorDir(CursorDir);
}

bool BattleLevel::UnitMoveAnim()
{


	if (1 <= MoveTimer)
	{
		if (ArrowPos.size() == ++MoveIndex)
		{
			return true;
		}
		MoveStartPos = SelectUnit->GetTransform()->GetWorldPosition();
		float4 _ArrowPos = ArrowPos[MoveIndex];
		MoveEndPos = _ArrowPos * TileScale;
		MoveTimer = 0;
	}

	SelectUnit->GetTransform()->SetLocalPosition(float4::LerpClamp(MoveStartPos, MoveEndPos, MoveTimer));
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
			for (std::shared_ptr<BattleUnit> _Unit : EnemyActors)
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


	if (false/*SelectUnit->GetClass() == 1*/)
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
				Queue.push(SearchData(int2(x, y), 1/*SelectUnit->GetRangeStat()*/));
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
				Queue.push(SearchData(int2(x, y), 1/* SelectUnit->GetRangeStat() / 2)*/));
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
			for (std::shared_ptr<BattleUnit> _Unit : PlayerActors)
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
			Check = false;
			for (std::shared_ptr<BattleUnit> _Actor : EnemyActors)
			{
				if (true == _Actor->GetIsDie()) { continue; }
				if (NextMove.Pos == _Actor->GetMapPos())
				{
					Check = true;
					break;
				}
			}
			if (true == Check)
			{
				//Queue.push(NextMove);
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
				Queue.push(SearchData(int2(x, y), 1/*SelectUnit->GetRangeStat()*/));
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
				if (NextMove.Pos == TargetPos)
				{
					ArrowPos = NextMove.History;
					return;
				}
				continue;
			}
			if (NextMove.Pos == TargetPos)
			{
				//NextMove.History.push_back(TargetPos);
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

void BattleLevel::UnitMove()
{
	if (true == IsMove[MainCursor->GetMapPos().y][MainCursor->GetMapPos().x])
	{
		for (std::shared_ptr<BattleUnit> _Actor : PlayerActors)
		{
			if (true == _Actor->GetIsDie()) { continue; }
			if (_Actor->GetMapPos() == MainCursor->GetMapPos())
			{
				// 임시) 클래스 번호가 다르면 다른 유닛이므로 이동이 불가능함
				if (_Actor->GetUnitCode() != SelectUnit->GetUnitCode())
				{
					return;
				}
			}
		}
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
	switch (TerrainData)
	{
	case Terrain::Plain:
		return 1;
	case Terrain::None:
		return 99;
	case Terrain::Forest:
		return 2;
	case Terrain::Cliff:
		return 99;
	case Terrain::Mountain:
		return 4;
	case Terrain::Peak:
		return 99;
	case Terrain::Door:
		return 99;
	case Terrain::Gate:
		return 1;
	case Terrain::House:
		return 1;
	case Terrain::Sea:
		return 99;
	case Terrain::River:
		return 5;
	case Terrain::Bridge:
		return 1;
	case Terrain::Wall:
		return 99;
	default:
		return 99;
	}
}


