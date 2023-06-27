#include "PrecompileHeader.h"
#include "Stage10.h"
#include "FEData.h"
Stage10::Stage10()
{
	StartPos.push_back({ 4, 15 });
	StartPos.push_back({ 5, 14 });
	StartPos.push_back({ 6, 15 });
	StartPos.push_back({ 5, 16 });
	StartPos.push_back({ 3, 15 });
	StartPos.push_back({ 3, 16 });
	StartPos.push_back({ 4, 14 });
	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 4, 16 });
	StartPos.push_back({ 5, 13 });
	StartPos.push_back({ 5, 17 });
	StartPos.push_back({ 5, 15 });
}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);

	OpeningEventInit();
	ClearEventInit();

	NewEnemyUnit(UnitIdentityCode::Soldier, 1, { 14, 14 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::Mage, 1, { 15, 15 }, { ItemCode::Fire });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 16, 13 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 14, 9 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::DarkMage, 1, { 15, 3 }, { ItemCode::Flux });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 9, 7 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 8, 8 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 7, 4 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 4, 7 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Knight, 1, { 2, 0 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::Lundgren, 1, { 2, 1 }, { ItemCode::SilverLance });
}

void Stage10::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage10::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("TitleLevel");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("TitleLevel");
	};
}
