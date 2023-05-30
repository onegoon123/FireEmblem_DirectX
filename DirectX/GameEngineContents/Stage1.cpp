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

	// 린
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->GetUnitData().LevelUp();
	NewActor->SetMapPos({ 2, 1 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::Vulnerary);
	NewActor->NewItem(ItemCode::Vulnerary);
	PushPlayerUnit(NewActor);

	// 켄트
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Kent);
	NewActor->SetMapPos({ 0, 2 });
	NewActor->NewItem(ItemCode::IronSword);
	NewActor->NewItem(ItemCode::IronLance);
	NewActor->NewItem(ItemCode::Vulnerary);
	PushPlayerUnit(NewActor);

	// 세인
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Sain);
	NewActor->SetMapPos({ 0, 4 });
	NewActor->NewItem(ItemCode::IronLance);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Florina);
	NewActor->SetMapPos({ 0, 4 });
	NewActor->NewItem(ItemCode::IronLance);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Erk);
	NewActor->SetMapPos({ 0, 5 });
	NewActor->NewItem(ItemCode::IronLance);
	PushPlayerUnit(NewActor);

	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Matthew);
	NewActor->SetMapPos({ 1, 5 });
	NewActor->NewItem(ItemCode::KillingSword);
	PushPlayerUnit(NewActor);

	// 산적
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 4, 3 });
	PushEnemyUnit(NewActor);

	// 산적
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 0 });
	PushEnemyUnit(NewActor);

	// 산적
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 13, 4 });
	NewActor->GetUnitData().LevelUp();
	PushEnemyUnit(NewActor);

	// 산적
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 12, 8 });
	NewActor->GetUnitData().LevelUp();
	PushEnemyUnit(NewActor);

	// 주그
	NewActor = CreateActor<BattleUnit>(RenderOrder::Unit);
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewItem(ItemCode::IronAxe);
	NewActor->SetMapPos({ 13, 8 });
	NewActor->GetUnitData().LevelUp(3);
	PushEnemyUnit(NewActor);
}

