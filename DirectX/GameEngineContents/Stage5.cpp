#include "PrecompileHeader.h"
#include "Stage5.h"

Stage5::Stage5()
{
}

Stage5::~Stage5()
{
}

void Stage5::StageSetting()
{
	SetStage(5);

	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 5 }, { ItemCode::IronAxe });

}

