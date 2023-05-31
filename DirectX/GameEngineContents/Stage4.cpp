#include "PrecompileHeader.h"
#include "Stage4.h"

Stage4::Stage4()
{
}

Stage4::~Stage4()
{
}

void Stage4::StageSetting()
{
	SetStage(4);
	std::shared_ptr<BattleUnit> NewActor;

	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 4 }, { ItemCode::IronAxe });
}

