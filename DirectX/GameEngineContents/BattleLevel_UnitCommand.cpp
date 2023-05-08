#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
void BattleLevel::UnitCommand_Item()
{
	// юс╫ц
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Wait()
{
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Attack()
{
	TargetUnit = AttackableUnits.front();
	ChangeState(BattleState::Battle);
	return;

	//std::list<AttackCommand> AttackDetail = UnitCommand::Attack(SelectUnit, AttackableUnits.front());
	//SelectUnit->SetUnitData(Unit(AttackDetail.back().SubjectUnit));
	//AttackableUnits.front()->SetUnitData(Unit(AttackDetail.back().TargetUnit));
	//SelectUnit->SetIsTurnEnd(true);

	//if (SelectUnit->GetIsDie())
	//{
	//	bool IsAliveUnit = false;
	//	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	//	{
	//		if (false == _Unit->GetIsDie())
	//		{
	//			IsAliveUnit = true;
	//		}
	//	}
	//	if (false == IsAliveUnit)
	//	{
	//		ChangeState(BattleState::GameOver);
	//		return;
	//	}
	//}
	//if (AttackableUnits.front()->GetIsDie())
	//{
	//	AttackableUnits.front()->Off();
	//}

	//ChangeState(BattleState::Select);
	//return;
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
