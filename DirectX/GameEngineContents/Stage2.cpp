#include "PrecompileHeader.h"
#include "Stage2.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::StageSetting()
{
	SetStage(2);
	std::shared_ptr<BattleUnit> NewActor;

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 4 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::ManiKatti);
	PushPlayerUnit(NewActor);


	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->NewItem(ItemCode::HandAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 7, 3 });
	PushEnemyUnit(NewActor);


}

