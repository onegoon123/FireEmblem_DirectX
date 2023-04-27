#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleMap.h"
#include "SelectUI.h"
#include "BattleUnit.h"

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

		// 커서가 이동한 곳에 아군 유닛이 있는가?
		SelectUnit = nullptr;
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			if (_Unit->GetIsDie()) { continue; }
			if (MoveValue == _Unit->GetMapPos())
			{
				SelectUnit = _Unit;
			}
		}
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
	if (GameEngineInput::IsDown("OK")) {

		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			if (true == _Unit->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == _Unit->GetMapPos())
			{
				if (true == _Unit->GetIsTurnEnd())
				{
					// 턴이 종료된 유닛
					break;
				}
				SelectUnit = _Unit;
				ChangeState(BattleState::Move);
				return;
			}
		}

		ChangeState(BattleState::FieldCommand);
		return;
	}

	if (GameEngineInput::IsDown("Next"))
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
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }
						SelectUnit = _Unit;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						return;
					}
					return;
				}
			}
		}


	}
}
