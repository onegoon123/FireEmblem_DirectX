#include "PrecompileHeader.h"
#include "Stage2.h"

Stage2::Stage2()
{
	StartPos.push_back({ 0, 6 });
	StartPos.push_back({ 1, 4 });
	StartPos.push_back({ 1, 6 });

	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
}

Stage2::~Stage2()
{
}

void Stage2::StageSetting()
{
	SetStage(2);
	ClearTarget = BattleClearTarget::Conquer;
	ConquerPos = { 11, 8 };
	ClearTargetText = "목표:옥좌 제압";

	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 9 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 11, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 13, 1 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 11, 6 }, { ItemCode::IronAxe });
	// 글라스
	NewEnemyUnit(UnitIdentityCode::Glass, 1, { 11, 8 }, { ItemCode::IronSword, ItemCode::Vulnerary });

	OpeningEventInit();
	ClearEventInit();
}

void Stage2::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage2::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		FindPlayerUnit(UnitIdentityCode::Lyn)->NewItem(ItemCode::ManiKatti);
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage3");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage3");
	};
}
