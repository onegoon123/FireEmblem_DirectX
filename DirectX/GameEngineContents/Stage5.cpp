#include "PrecompileHeader.h"
#include "Stage5.h"

Stage5::Stage5()
{
	StartPos.push_back({ 3, 3 });
	StartPos.push_back({ 2, 4 });
	StartPos.push_back({ 3, 5 });
	StartPos.push_back({ 2, 2 });
	StartPos.push_back({ 1, 3 });
	StartPos.push_back({ 3, 1 });

	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
}

Stage5::~Stage5()
{
}

void Stage5::StageSetting()
{
	SetStage(5);

	// 세라, 에르크 (중립)
	NewPlayerUnit(UnitIdentityCode::Serra, 1, { 6, 3 }, { ItemCode::Heal,ItemCode::Heal, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Erk, 1, { 7, 3 }, { ItemCode::Fire });

	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 3, 9 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 7, 5 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 2, { 8, 7 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 11, 9 }, { ItemCode::IronAxe, ItemCode::IronSword });

	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 11, 9 }, { ItemCode::IronAxe, ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 14, 7 }, { ItemCode::IronBow});
	NewEnemyUnit(UnitIdentityCode::Mercenary, 2, { 12, 2 }, { ItemCode::IronSword });
	// 바그
	NewEnemyUnit(UnitIdentityCode::Brigand, 10, { 14, 0 }, { ItemCode::IronAxe });
}

