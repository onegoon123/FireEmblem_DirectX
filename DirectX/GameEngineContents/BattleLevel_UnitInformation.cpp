#include "PrecompileHeader.h"
#include "BattleLevel.h"

void BattleLevel::UnitInformation_Cancel()
{
	ChangeState(BattleState::Select);
}
