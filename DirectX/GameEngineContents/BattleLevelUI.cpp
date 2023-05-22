#include "PrecompileHeader.h"
#include "BattleLevelUI.h"
#include "BattleLevel.h"

#include "SelectUI.h"
#include "UnitCommandUI.h"
#include "FieldCommandUI.h"
#include "PhaseUI.h"
#include "AttackUI.h"
#include "ItemUI.h"
#include "UICursor.h"

BattleLevelUI::BattleLevelUI()
{
}

BattleLevelUI::~BattleLevelUI()
{
}

void BattleLevelUI::AllOff()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();
}

void BattleLevelUI::SelectOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Select->On();
}

void BattleLevelUI::SetUnitData(std::shared_ptr<BattleUnit> _Unit)
{
	UI_Select->SetUnitData(_Unit);
}

void BattleLevelUI::UnitUIOff()
{
	UI_Select->UnitUIOff();
}

void BattleLevelUI::SetCursorDir(UIDir _Dir)
{
	UI_Select->SetCursorDir(_Dir);
}

void BattleLevelUI::UnitCommandOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_UnitCommand->On();
}

void BattleLevelUI::UnitCommandSet(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_UnitCommand->On();
	UI_UnitCommand->SetCommand(_IsAttackable, _IsCloseUnit, _IsItem);
}

void BattleLevelUI::FieldCommandOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_FieldCommand->On();
}

void BattleLevelUI::AttackOn(std::shared_ptr<class BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Attack->On(_SelectUnit, _TargetUnits);
}

void BattleLevelUI::ItemOn(std::shared_ptr<BattleUnit> _SelectUnit)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Item->On(_SelectUnit);
}

void BattleLevelUI::PhaseOn(Faction _Faction)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Phase->PhaseOn(_Faction);
}

bool BattleLevelUI::IsPhaseEnd()
{
	return UI_Phase->PhaseUIEnd();
}


void BattleLevelUI::Start()
{
	BattleLevel* CurLevel = dynamic_cast<BattleLevel*>(GetLevel());
	if (nullptr == CurLevel)
	{
		MsgAssert("BattleLevelUI는 BattleLevel에서만 생성할 수 있습니다.");
	}
	UI_Select = CurLevel->CreateActor<SelectUI>();
	UI_UnitCommand = CurLevel->CreateActor<UnitCommandUI>();
	UI_Attack = CurLevel->CreateActor<AttackUI>();
	UI_Item = CurLevel->CreateActor<ItemUI>();
	UI_FieldCommand = CurLevel->CreateActor<FieldCommandUI>();
	UI_Phase = CurLevel->CreateActor<PhaseUI>();

	UI_Cursor = CurLevel->CreateActor<UICursor>();

	UI_UnitCommand->Setting(CurLevel, UI_Cursor);
	UI_Attack->Setting(CurLevel, UI_Cursor);
	UI_Item->Setting(CurLevel, UI_Cursor);
	UI_FieldCommand->Setting(CurLevel, UI_Cursor);
}

