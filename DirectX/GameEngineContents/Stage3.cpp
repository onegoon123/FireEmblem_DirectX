#include "PrecompileHeader.h"
#include "Stage3.h"

Stage3::Stage3()
{
	StartPos.push_back({ 1, 1 });
	StartPos.push_back({ 2, 0 });
	StartPos.push_back({ 4, 1 });
	StartPos.push_back({ 2, 2 });
}

Stage3::~Stage3()
{
}

void Stage3::StageSetting()
{
	SetStage(3);

	// 플로리나
	NewPlayerUnit(UnitIdentityCode::Florina, 1, { 2, 2 }, { ItemCode::SlimLance, ItemCode::Vulnerary });

	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 8, 2 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 5, 5 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 5, 5 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 13, 1 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 8, 5 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 14, 4 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 11, 6 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 12, 7 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 11, 9 }, { ItemCode::IronSword });

	// 미갈
	NewEnemyUnit(UnitIdentityCode::Brigand, 8, { 13, 9 }, { ItemCode::IronAxe });

}

