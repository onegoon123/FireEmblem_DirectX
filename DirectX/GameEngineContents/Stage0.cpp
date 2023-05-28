#include "PrecompileHeader.h"
#include "Stage0.h"

Stage0::Stage0() 
{
}

Stage0::~Stage0() 
{
}

void Stage0::StageSetting()
{
	SetStage(0);

	std::shared_ptr<BattleUnit> NewActor;

	// 린
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->SetMapPos({ 13, 2 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::Vulnerary);
	NewActor->NewItem(ItemCode::Vulnerary);
	PushPlayerUnit(NewActor);

	// 산적
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 2, 3 });
	PushEnemyUnit(NewActor);

	// 바타
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->GetUnitData().LevelUp();
	NewActor->SetMapPos({ 3, 7 });
	PushEnemyUnit(NewActor);

}

