#include "PrecompileHeader.h"
#include "BattleLevel.h"

void BattleLevel::UnitInformation_Cancel()
{
	StateEnd();
	StateUpdate = std::bind(&BattleLevel::SelectUpdate, this, std::placeholders::_1);
	StateEnd = std::bind(&BattleLevel::SelectEnd, this);
	CurState = BattleState::Select;
	//ChangeState(BattleState::Select);
}
