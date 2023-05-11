#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
#include "UnitCommandUI.h"
#include "AttackUI.h"
#include "ItemUI.h"
#include "Item.h"
void BattleLevel::UnitCommand_Item()
{
	UI_UnitCommand->Off();
	UI_Item->On(SelectUnit);
}

void BattleLevel::UnitCommand_Wait()
{
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Attack()
{
	UI_UnitCommand->Off();
	UI_Attack->On(SelectUnit, AttackableUnits);
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
	UI_Attack->Off();
	UI_Item->Off();
	UI_UnitCommand->On();
}

void BattleLevel::UnitCommand_TargetAttack(std::shared_ptr<BattleUnit> _Target)
{
	TargetUnit = _Target;
	ChangeState(BattleState::Battle);
	return;
}

void BattleLevel::UnitCommand_ItemUse(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	UnitCommand::Wait(SelectUnit);
	UI_Item->Off();
	SelectUnit->SetIsTurnEnd(true);
	SelectUnit->GetUnitData().UseItem(_ItemIter);
	ChangeState(BattleState::Select);
}
