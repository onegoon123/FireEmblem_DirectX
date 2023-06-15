#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
#include "Item.h"
#include "BattleLevelUI.h"
#include "MapCursor.h"
void BattleLevel::UnitCommand_Item()
{
	BattleUI->ItemOn(SelectUnit);
}

void BattleLevel::UnitCommand_Wait()
{
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Attack()
{
	BattleUI->AttackOn(SelectUnit, AttackableUnits);
}

void BattleLevel::UnitCommand_Heal()
{
	BattleUI->HealOn(SelectUnit, CloseUnits);
}

void BattleLevel::UnitCommand_Exchange()
{
	BattleUI->ExchangeOn(SelectUnit, CloseUnits);
}
void BattleLevel::UnitCommand_ExchangeEnd(std::shared_ptr<BattleUnit> _Target)
{
	UnitCommand::Wait(SelectUnit);
	MainCursor->SetMapPos(SelectUnit->GetMapPos());
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}
void BattleLevel::UnitCommand_Cancel()
{
	//BattleUI->AllOff();
	SelectUnit->SetMapPos(BeforePos);
	ChangeState(BattleState::Move);
}

void BattleLevel::UnitCommand_CommandCancel()
{
	BattleUI->UnitCommandOn();
}

void BattleLevel::UnitCommand_TargetAttack(std::shared_ptr<BattleUnit> _Target)
{
	TargetUnit = _Target;
	ChangeState(BattleState::Battle);
	return;
}
void BattleLevel::UnitCommand_TargetHeal(std::shared_ptr<BattleUnit> _Target, std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	TargetUnit = _Target;
	UseItem = _ItemIter;
	ChangeState(BattleState::Heal);
	return;
}
void BattleLevel::UnitCommand_ItemUse(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	ItemCode _ItemCode = (*_ItemIter)->GetItemCode();
	UseItem = _ItemIter;
	ChangeState(BattleState::Potion);
}

void BattleLevel::UnitCommand_Conquer()
{
	ChangeState(BattleState::Clear);
}