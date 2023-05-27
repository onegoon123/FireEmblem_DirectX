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
	std::shared_ptr<BattleUnit> NewActor;

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 1, 5 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::ManiKatti);
	PushPlayerUnit(NewActor);


	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->NewItem(ItemCode::HandAxe);
	NewActor->GetUnitData().LevelUp(0);
	NewActor->SetMapPos({ 7, 5 });
	PushEnemyUnit(NewActor);


}

