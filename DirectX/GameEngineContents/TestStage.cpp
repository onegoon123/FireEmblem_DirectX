#include "PrecompileHeader.h"
#include "TestStage.h"

TestStage::TestStage()
{
	StartPos.push_back({ 3, 3 });
	StartPos.push_back({ 2, 4 });
	StartPos.push_back({ 3, 5 });
	StartPos.push_back({ 2, 2 });
	StartPos.push_back({ 1, 3 });
	StartPos.push_back({ 3, 1 });

	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
}

TestStage::~TestStage()
{
}

void TestStage::StageSetting()
{
	SetStage(5);
	ClearTarget = BattleClearTarget::AllKill;
	ClearTargetText = "목표:적 전멸";

	NewPlayerUnit(UnitIdentityCode::Lyn, 99, { 3, 3 }, { ItemCode::IronSword, ItemCode::ManiKatti, ItemCode::Vulnerary, ItemCode::MasterSeal })->GetUnitData().AddExp(80);
	NewPlayerUnit(UnitIdentityCode::Kent, 1, { 2, 4 }, { ItemCode::IronSword, ItemCode::IronLance, ItemCode::Vulnerary })->GetUnitData().AddExp(80);
	NewPlayerUnit(UnitIdentityCode::Sain, 1, { 3, 5 }, { ItemCode::IronLance });
	NewPlayerUnit(UnitIdentityCode::Florina, 1, { 2, 2 }, { ItemCode::SlimLance, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Wil, 2, { 1, 3 }, { ItemCode::IronBow });
	NewPlayerUnit(UnitIdentityCode::Dorcas, 3, { 3, 1 }, { ItemCode::HandAxe, ItemCode::MasterSeal });

	// 세라, 에르크 (중립)
	NewPlayerUnit(UnitIdentityCode::Serra, 1, { 4, 3 }, { ItemCode::Heal,ItemCode::Heal, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Erk, 1, { 4, 2 }, { ItemCode::Fire });

	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 3, 9 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 7, 5 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 2, { 8, 7 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 11, 9 }, { ItemCode::IronAxe, ItemCode::IronSword });

	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 10, 9 }, { ItemCode::IronAxe, ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 14, 7 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 2, { 12, 2 }, { ItemCode::IronSword });

	NewEnemyUnit(UnitIdentityCode::Carjiga, 1, { 14, 0 }, { ItemCode::IronAxe });
	OpeningEventInit();
	ClearEventInit();
}

void TestStage::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void TestStage::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage6");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage6");
	};
}
