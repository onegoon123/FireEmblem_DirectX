#include "PrecompileHeader.h"
#include "BattleLevel.h"
void BattleLevel::FieldCommand_TimeStone()
{
	ChangeState(BattleState::TimeStone);
}

void BattleLevel::FieldCommand_ArmyUnit()
{
	return;
}

void BattleLevel::FieldCommand_Setting()
{
	return;
}

void BattleLevel::FieldCommand_Exit()
{
	ChangeState(BattleState::GameOver);
	return;
}

void BattleLevel::FieldCommand_PhaseEnd()
{
	ChangeState(BattleState::EnemyPhase);
}

void BattleLevel::FieldCommand_Cancel()
{
	ChangeState(BattleState::Select);
}
