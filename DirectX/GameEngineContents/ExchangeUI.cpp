#include "PrecompileHeader.h"
#include "ExchangeUI.h"
#include "MapCursor.h"
#include "BattleLevel.h"
ExchangeUI::ExchangeUI()
{
}

ExchangeUI::~ExchangeUI()
{
}

void ExchangeUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_UI = _Cursor;
	Cursor_Map = _Level->GetMapCursor();
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);
}

void ExchangeUI::On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	LeftUnit = _SelectUnit;
	TargetUnits = _TargetUnits;
	TargetIter = TargetUnits.begin();
	Cursor_Map->SetMapPos((*TargetIter)->GetMapPos());

	TargetSelectStart();
}

void ExchangeUI::Start()
{
}

void ExchangeUI::Update(float _DeltaTime)
{
	if (true == IsUnitSelect)
	{
		ExchangeUpdate(_DeltaTime);
	}
	else
	{
		TargetSelectUpdate(_DeltaTime);
	}
}

void ExchangeUI::TargetSelectStart()
{
	IsUnitSelect = false;

	TargetIter = TargetUnits.begin();
	Cursor_Map->On();
}

void ExchangeUI::TargetSelectUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonB"))
	{
		CancelFunction();
		Cursor_Map->Off();
		return;
	}
}

void ExchangeUI::TargetSelectEnd()
{
}

void ExchangeUI::ExchangeStart()
{
}

void ExchangeUI::ExchangeUpdate(float _DeltaTime)
{
}
