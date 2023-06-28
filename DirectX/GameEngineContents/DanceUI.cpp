#include "PrecompileHeader.h"
#include "DanceUI.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "MapCursor.h"
#include "NumberActor.h"
#include "DoubleIconActor.h"
#include "UIButtonSystem.h"
#include "TextRenderer.h"
DanceUI::DanceUI()
{
}

DanceUI::~DanceUI()
{
}

void DanceUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_Map = _Level->GetMapCursor();
	DanceFunction = std::bind(&BattleLevel::UnitCommand_TargetDance, _Level, std::placeholders::_1);
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);

}

void DanceUI::On(std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	GameEngineActor::On();

	TargetUnits = _TargetUnits;

	IsOnFrame = true;
	TargetSelectStart();
}

void DanceUI::Start()
{
	GameEngineActor::Off();
}

void DanceUI::Update(float _DeltaTime)
{
	TargetSelectUpdate(_DeltaTime);
}


void DanceUI::TargetSelectStart()
{
	TargetIter = TargetUnits.begin();
	Cursor_Map->On();

	SetTarget();
}

void DanceUI::TargetSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		GameEngineSound::Play("CommandSelect.wav");
		DanceFunction(TargetUnit);
		Off();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineSound::Play("Cancel.wav");
		CancelFunction();
		return;
	}
	if (Cursor_Map->GetIsMove()) { return; }


	if (GameEngineInput::IsDown("Up") || GameEngineInput::IsDown("Left"))
	{
		GameEngineSound::Play("CommandMove.wav");
		if (TargetIter == TargetUnits.begin())
		{
			TargetIter = TargetUnits.end();
		}
		TargetIter--;
		SetTarget();
		return;
	}
	if (GameEngineInput::IsDown("Down") || GameEngineInput::IsDown("Right") || GameEngineInput::IsUp("MiddleClick"))
	{
		GameEngineSound::Play("CommandMove.wav");
		TargetIter++;
		if (TargetIter == TargetUnits.end())
		{
			TargetIter = TargetUnits.begin();
		}
		SetTarget();
		return;
	}
}

void DanceUI::TargetSelectEnd()
{
}

void DanceUI::SetTarget()
{
	TargetUnit = *TargetIter;
	Cursor_Map->SetCursorPos(TargetUnit->GetMapPos());
}
