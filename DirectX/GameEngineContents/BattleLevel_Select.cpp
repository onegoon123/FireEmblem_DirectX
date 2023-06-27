#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleMap.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "SpriteRenderer.h"
#include "UnitCommand.h"
#include "FERandom.h"
#include "BattleLevelUI.h"
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{
	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsUp("LeftClick") || GameEngineInput::IsUp("RightClick"))
	{
		IsMouseOn = true;
		MainCursor->SetSoundPlay(false);
		return;
	}

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


	int2 CursorPos = MainCursor->WorldPos;
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		CameraMove(MoveValue);
		MainCursor->MoveCursorPosLerp(MoveValue);
		CursorDirCheck();	// 커서의 방향(정중앙 기준) 체크
		CursorUnitSelect();
		BattleUI->SetTerrain(GetTerrain(MainCursor->WorldPos));
	}
}

void BattleLevel::CursorUnitSelect()
{
	// 커서가 이동한 곳에 아군 유닛이 있는가?
	SelectUnit = nullptr;
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->WorldPos == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// 유닛 정보 UI로 띄우기
			MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색
			SetTile();
			MainCursor->Select();
			return;
		}
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->WorldPos == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// 유닛 정보 UI로 띄우기
			MoveSearchForEnemy();	// 이동범위 탐색, 자동으로 공격범위도 탐색
			SetTile();
			return;
		}
	}
	Tiles->Clear();
	BattleUI->UnitUIOff();
	MainCursor->Idle();
}

void BattleLevel::CursorAndArrowMove()
{

	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsUp("LeftClick") || GameEngineInput::IsUp("RightClick"))
	{
		IsMouseOn = true;
		MainCursor->SetSoundPlay(false);
		return;
	}

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


	int2 CursorPos = MainCursor->WorldPos;
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
	{
		// 이동할 곳이 맵 밖이 아니라면
		if (false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		CameraMove(MoveValue);
		MainCursor->MoveCursorPosLerp(MoveValue);
		AddArrow(MainCursor->WorldPos);
	}
}

void BattleLevel::CursorMoveMouse()
{
	if (
		GameEngineInput::IsDown("Up") ||
		GameEngineInput::IsDown("Down") ||
		GameEngineInput::IsDown("Left") ||
		GameEngineInput::IsDown("Right")
		)
	{
		IsMouseOn = false;
		MainCursor->SetSoundPlay(true);
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->WorldPos;
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f) + CameraUnit->GetMapPos();
	if (true == IsMapOut(MouseMapPos))
	{
		return;
	}
	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;

		CameraMove(MovePos.Normalize());
		MainCursor->MoveCursorPosLerp(MovePos.Normalize());

		CursorDirCheck();
		CursorUnitSelect();
		BattleUI->SetTerrain(GetTerrain(MainCursor->WorldPos));
	}


}

void BattleLevel::CursorAndArrowMoveMouse()
{
	if (
		GameEngineInput::IsDown("Up") ||
		GameEngineInput::IsDown("Down") ||
		GameEngineInput::IsDown("Left") ||
		GameEngineInput::IsDown("Right")
		)
	{
		IsMouseOn = false;
		MainCursor->SetSoundPlay(true);
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->WorldPos;
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f) + CameraUnit->GetMapPos();
	if (true == IsMapOut(MouseMapPos))
	{
		return;
	}
	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;
		CameraMove(MovePos.Normalize());
		MainCursor->MoveCursorPosLerp(MovePos.Normalize());
		CursorDirCheck();
		AddArrow(MainCursor->WorldPos);
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

	BattleUI->SetCursorDir(CursorDir);
}

void BattleLevel::UnitSelect()
{
	// 확인버튼 입력시에만
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick")) {

		if (true == IsMapOut(MainCursor->WorldPos)) { return; }

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
				GameEngineSound::Play("UnitSelect.wav");
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
				SelectUnit->GetRenderer()->SetLerp({ 1.0f, 0.0f, 0.5f }, 0.3f);
			}
			else
			{
				SelectUnit->GetRenderer()->OffLerp();
			}
			EnemyTileCheck();
			MoveSearchForEnemy();
			SetTile();
		}
		return;
	}

	// L버튼(A 키)를 누르면 아군유닛을 자동으로 찾아주는 기능
	if (GameEngineInput::IsDown("ButtonL"))
	{
		if (true == MainCursor->GetIsMove()) { return; }
		GameEngineSound::Play("Cancel.wav");
		if (nullptr == SelectUnit)
		{
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (_Unit->GetIsDie()) { continue; }
				if (_Unit->GetIsTurnEnd()) { continue; }

				SelectUnit = _Unit;
				MainCursor->SetCursorPos(SelectUnit->GetMapPos());
				CameraSetPos();
				CursorDirCheck();
				SetUI_UnitData();
				MoveSearch();
				SetTile();
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
						MainCursor->SetCursorPos(SelectUnit->GetMapPos());
						CameraSetPos();
						CursorDirCheck();
						SetUI_UnitData();
						MoveSearch();
						SetTile();
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }

						SelectUnit = _Unit;
						MainCursor->SetCursorPos(SelectUnit->GetMapPos());
						CameraSetPos();
						CursorDirCheck();
						SetUI_UnitData();
						MoveSearch();
						SetTile();
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
		SetTile();
		return;

	}
	// 선택한 유닛의 정보를 표시하는 기능
	if (GameEngineInput::IsDown("ButtonR") || GameEngineInput::IsDown("MiddleClick"))
	{
		if (nullptr == SelectUnit) { return; }
		GameEngineSound::Play("UnitSelect.wav");
		ChangeState(BattleState::Information);
		return;
	}


	// 시간석
	if (GameEngineInput::IsDown("ButtonX"))
	{
		ChangeState(BattleState::TimeStone);
		return;

	}
}

void BattleLevel::SetUI_UnitData()
{
	BattleUI->SetUnitData(SelectUnit);
}

