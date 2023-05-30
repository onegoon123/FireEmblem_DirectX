#include "PrecompileHeader.h"
#include "Stage10.h"
#include "FEData.h"
Stage10::Stage10()
{
}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);

	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 3, 15 });
	StartPos.push_back({ 2, 14 });
	StartPos.push_back({ 1, 16 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });

	LoadPlayerUnits(FEData::GetPlayerUnits());

	std::shared_ptr<BattleUnit> NewActor;

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 3, 5 });
	PushEnemyUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 5, 5 });
	PushEnemyUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 12, 15 });
	PushEnemyUnit(NewActor);
}

