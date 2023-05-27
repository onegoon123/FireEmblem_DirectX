#include "PrecompileHeader.h"
#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::StageSetting()
{
	SetStage(1);

	std::shared_ptr<BattleUnit> NewActor;

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 4 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::ManiKatti);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Kent);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 5 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::ManiKatti);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Dorcas);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 5, 5 });
	NewActor->NewItem(ItemCode::HandAxe);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->NewItem(ItemCode::HandAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 3 });
	PushEnemyUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Soldier);
	NewActor->NewItem(ItemCode::SilverLance);
	NewActor->NewItem(ItemCode::SilverLance);
	NewActor->NewItem(ItemCode::SilverLance);
	NewActor->NewItem(ItemCode::SilverLance);
	NewActor->NewItem(ItemCode::SilverLance);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 2, 4 });
	PushEnemyUnit(NewActor);

}

