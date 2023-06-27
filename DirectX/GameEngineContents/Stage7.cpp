#include "PrecompileHeader.h"
#include "Stage7.h"

Stage7::Stage7()
{
	StartPos.push_back({ 3, 9 });
	StartPos.push_back({ 2, 11 });
	StartPos.push_back({ 1, 12 });
	StartPos.push_back({ 4, 11 });
	StartPos.push_back({ 1, 10 });
	StartPos.push_back({ 3, 10 });
	StartPos.push_back({ 2, 9 });
	StartPos.push_back({ 5, 10 });
	StartPos.push_back({ 2, 8 });
	StartPos.push_back({ 1, 9 });
	StartPos.push_back({ 3, 12 });
	StartPos.push_back({ 2, 12 });
}

Stage7::~Stage7()
{
}

void Stage7::StageSetting()
{
	SetStage(7);
	ClearTarget = BattleClearTarget::AllKill;
	ClearTargetText = "¸ñÇ¥:Àû Àü¸ê";
	OpeningEventInit();
	ClearEventInit();

	NewPlayerUnit(UnitIdentityCode::Rath, 1, { 2, 8 }, { ItemCode::ShortBow, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Matthew, 1, { 1, 9 }, { ItemCode::IronSword });
	NewPlayerUnit(UnitIdentityCode::Lucius, 1, { 3, 12 }, { ItemCode::Lightning });
	NewPlayerUnit(UnitIdentityCode::Ninian, 1, { 2, 12 }, { ItemCode::Vulnerary });


	NewEnemyUnit(UnitIdentityCode::DarkMage, 1, { 5, 8 }, { ItemCode::Flux });


}

void Stage7::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage7::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage8");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage8");
	};
}

