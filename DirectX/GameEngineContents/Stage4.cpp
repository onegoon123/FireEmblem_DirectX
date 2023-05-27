#include "PrecompileHeader.h"
#include "Stage4.h"

Stage4::Stage4()
{
}

Stage4::~Stage4()
{
}

void Stage4::StageSetting()
{
	SetStage(4);
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
	NewActor->SetMapPos({ 7, 4 });
	PushEnemyUnit(NewActor);


}

