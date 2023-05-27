#include "PrecompileHeader.h"
#include "Stage10.h"

Stage10::Stage10()
{
}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);
	std::shared_ptr<BattleUnit> NewActor;

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 10 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::ManiKatti);
	PushPlayerUnit(NewActor);


	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->NewItem(ItemCode::HandAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 10, 10 });
	PushEnemyUnit(NewActor);


}

