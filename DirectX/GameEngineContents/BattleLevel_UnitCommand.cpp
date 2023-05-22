#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
#include "Item.h"
#include "BattleLevelUI.h"
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

void BattleLevel::UnitCommand_Exchange()
{
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Cancel()
{
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

void BattleLevel::UnitCommand_ItemUse(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	ItemCode _ItemCode = (*_ItemIter)->GetItemCode();
	BattleUI->AllOff();
	UnitCommand::ItemUse(SelectUnit, _ItemIter);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}
