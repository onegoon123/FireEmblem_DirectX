#include "PrecompileHeader.h"
#include "Stage0.h"

Stage0::Stage0() 
{
	StartPos.push_back({ 13, 2 });
	StartPos.push_back({ 13, 4 });
	StartPos.push_back({ 14, 3 });
	StartPos.push_back({ 13, 0 });
	StartPos.push_back({ 13, 1 });
	StartPos.push_back({ 14, 1 });
	StartPos.push_back({ 14, 2 });
	StartPos.push_back({ 12, 2 });
	StartPos.push_back({ 13, 3 });
	StartPos.push_back({ 14, 4 });
}

Stage0::~Stage0() 
{
}

void Stage0::StageSetting()
{
	SetStage(0);

	// 린
	NewPlayerUnit(UnitIdentityCode::Lyn, 1, { 13, 2 }, { ItemCode::IronSword, ItemCode::Vulnerary, ItemCode::Vulnerary });

	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 2, 3 }, { ItemCode::IronAxe});
	// 바타
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 3, 7 }, { ItemCode::IronAxe});

}

