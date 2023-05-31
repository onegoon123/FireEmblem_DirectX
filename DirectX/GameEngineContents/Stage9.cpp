#include "PrecompileHeader.h"
#include "Stage9.h"

Stage9::Stage9()
{
}

Stage9::~Stage9()
{
}

void Stage9::StageSetting()
{
	SetStage(9);
	std::shared_ptr<BattleUnit> NewActor;

	
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 9, 9 }, { ItemCode::IronAxe });


}

