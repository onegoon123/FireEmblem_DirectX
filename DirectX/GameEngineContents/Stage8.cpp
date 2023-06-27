#include "PrecompileHeader.h"
#include "Stage8.h"

Stage8::Stage8()
{
	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 3, 14 });
	StartPos.push_back({ 4, 15 });
	StartPos.push_back({ 3, 16 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 16 });
	StartPos.push_back({ 2, 14 });
	StartPos.push_back({ 0, 15 });
	StartPos.push_back({ 2, 16 });
	StartPos.push_back({ 1, 13 });
	StartPos.push_back({ 3, 17 });
	StartPos.push_back({ 3, 15 });
}

Stage8::~Stage8()
{
}

void Stage8::StageSetting()
{
	SetStage(8);
	OpeningEventInit();
	ClearEventInit();

	NewEnemyUnit(UnitIdentityCode::DarkMage, 1, { 13, 14 }, { ItemCode::Flux })->SetDetectionRange(5);
	NewEnemyUnit(UnitIdentityCode::Mage, 1, { 13, 13 }, { ItemCode::Fire })->SetDetectionRange(5);
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 4, 6 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 9, 9 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 11, 7 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Soldier, 3, { 7, 4 }, { ItemCode::IronLance});
	NewEnemyUnit(UnitIdentityCode::Soldier, 3, { 8, 4 }, { ItemCode::IronLance});
	NewEnemyUnit(UnitIdentityCode::Brigand, 3, { 7, 2 }, { ItemCode::IronAxe});
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 8, 2 }, { ItemCode::IronSword});

	NewEnemyUnit(UnitIdentityCode::Soldier, 3, { 11, 3 }, { ItemCode::IronLance})->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 11, 1 }, { ItemCode::IronSword})->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::Brigand, 3, { 13, 3 }, { ItemCode::IronAxe})->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::Brigand, 3, { 13, 1 }, { ItemCode::IronAxe})->SetDetectionRange(8);

	// ¿ä±â
	NewEnemyUnit(UnitIdentityCode::Yogi, 1, { 12, 2 }, { ItemCode::SilverLance})->SetDetectionRange(1);

}

void Stage8::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage8::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage9");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage9");
	};
}

