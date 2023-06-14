#include "PrecompileHeader.h"
#include "Stage2.h"

Stage2::Stage2()
{
	StartPos.push_back({ 0, 6 });
	StartPos.push_back({ 1, 4 });
	StartPos.push_back({ 1, 6 });

	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
}

Stage2::~Stage2()
{
}

void Stage2::StageSetting()
{
	SetStage(2);

	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 9 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 11, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 13, 1 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 11, 6 }, { ItemCode::IronAxe });
	// 글라스
	NewEnemyUnit(UnitIdentityCode::Glass, 1, { 11, 8 }, { ItemCode::IronSword, ItemCode::Vulnerary });

}

