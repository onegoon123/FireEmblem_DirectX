#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
#include "UnitCommandUI.h"
#include "AttackUI.h"
#include "ItemUI.h"
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
