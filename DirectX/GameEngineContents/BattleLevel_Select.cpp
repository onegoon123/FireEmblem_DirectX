#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleMap.h"
#include "SelectUI.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "SpriteRenderer.h"
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{
	if (
		PreesTime < GameEngineInput::GetPressTime("Up") ||
		PreesTime < GameEngineInput::GetPressTime("Down") ||
		PreesTime < GameEngineInput::GetPressTime("Left") ||
		PreesTime < GameEngineInput::GetPressTime("Right")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("Up") &&
		GameEngineInput::IsFree("Down") &&
		GameEngineInput::IsFree("Left") &&
		GameEngineInput::IsFree("Right")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
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

		// 커서가 이동한 곳에 아군 유닛이 있는가?
		SelectUnit = nullptr;
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			if (_Unit->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == _Unit->GetMapPos())
			{
				SelectUnit = _Unit;
				SetUI_UnitData();	// 유닛 정보 UI로 띄우기
				MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색
				Tiles->SetTile(IsMove, IsAttack);
				return;
			}
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			if (_Unit->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == _Unit->GetMapPos())
			{
				SelectUnit = _Unit;
				SetUI_UnitData();	// 유닛 정보 UI로 띄우기
				MoveSearchForEnemy();	// 이동범위 탐색, 자동으로 공격범위도 탐색
				Tiles->SetTile(IsMove, IsAttack);
				return;
			}
		}
		Tiles->Clear();
		UI_Select->UnitUIOff();
	}
}

void BattleLevel::CursorAndArrowMove()
{

	if (
		PreesTime < GameEngineInput::GetPressTime("Up") ||
		PreesTime < GameEngineInput::GetPressTime("Down") ||
		PreesTime < GameEngineInput::GetPressTime("Left") ||
		PreesTime < GameEngineInput::GetPressTime("Right")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("Up") &&
		GameEngineInput::IsFree("Down") &&
		GameEngineInput::IsFree("Left") &&
		GameEngineInput::IsFree("Right")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// 커서가 이동중이 아니며 이동할 곳이 맵 밖이 아니라면
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
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
	static float4 ScreenSize = GameEngineWindow::GetScreenSize() - float4(0, TileScale);
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

void BattleLevel::UnitSelect()
{
	// 확인버튼 입력시에만
	if (GameEngineInput::IsDown("ButtonA")) {

		// 선택한 곳에 유닛이 없다면
		if (nullptr == SelectUnit)
		{
			ChangeState(BattleState::FieldCommand);
			return;
		}

		// 선택한 유닛이 플레이어 유닛인가?
		if (true == SelectUnit->GetIsPlayer())
		{
			// 턴이 종료되지 않았다면
			if (false == SelectUnit->GetIsTurnEnd())
			{
				ChangeState(BattleState::Move);
				return;
			}
			else
			{
				ChangeState(BattleState::FieldCommand);
				return;
			}
		}
		else
		{
			// 적 유닛이라면 공격 범위 탐색
			SelectUnit->SetIsCheckTile(!SelectUnit->GetIsCheckTile());
			if (true == SelectUnit->GetIsCheckTile())
			{
				SelectUnit->GetRenderer()->SetLerp({1.0f, 0.0f, 0.5f}, 0.3f);
			}
			else
			{
				SelectUnit->GetRenderer()->OffLerp();
			}
			EnemyTileCheck();
			MoveSearchForEnemy();
			Tiles->SetTile(IsMove, IsAttack);
		}
		return;
	}

	// L버튼(A 키)를 누르면 아군유닛을 자동으로 찾아주는 기능
	if (GameEngineInput::IsDown("ButtonL"))
	{
		if (true == MainCursor->GetIsMove()) { return; }

		if (nullptr == SelectUnit)
		{
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (_Unit->GetIsDie()) { continue; }
				if (_Unit->GetIsTurnEnd()) { continue; }
				SelectUnit = _Unit;
				MainCursor->SetMapPos(SelectUnit->GetMapPos());
				CursorDirCheck();
				SetUI_UnitData();
				return;
			}
		}
		else
		{
			std::list<std::shared_ptr<BattleUnit>>::iterator Start = PlayerUnits.begin();
			std::list<std::shared_ptr<BattleUnit>>::iterator End = PlayerUnits.end();
			for (; Start != End; Start++)
			{
				if ((*Start)->GetUnitCode() == SelectUnit->GetUnitCode())
				{
					Start++;
					for (; Start != End; Start++)
					{
						if ((*Start)->GetIsDie()) { continue; }
						if ((*Start)->GetIsTurnEnd()) { continue; }
						if ((*Start)->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }

						SelectUnit = *Start;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						CursorDirCheck();
						SetUI_UnitData();
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }
						SelectUnit = _Unit;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						CursorDirCheck();
						SetUI_UnitData();
						return;
					}
					return;
				}
			}
		}


	}

	// Y버튼(C 키)를 누르면 모든 적의 공격 가능 범위를 표시
	if (GameEngineInput::IsDown("ButtonY"))
	{
		IsEnemyRangeCheck = !IsEnemyRangeCheck;
		EnemyTileCheck();
		

		// 선택한 유닛이 있다면
		if (nullptr == SelectUnit) { return; }

		if (true == SelectUnit->GetIsPlayer())
		{
			MoveSearch();
		}
		else
		{
			MoveSearchForEnemy();
		}
		Tiles->SetTile(IsMove, IsAttack);
		return;

	}
	// 선택한 유닛의 정보를 표시하는 기능
	if (GameEngineInput::IsDown("ButtonR"))
	{
		if (nullptr == SelectUnit) { return; }
		MsgTextBox(SelectUnit->ToString());
	}
}

void BattleLevel::SetUI_UnitData()
{
	UI_Select->SetUnitData(SelectUnit);
}

