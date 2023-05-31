#include "PrecompileHeader.h"
#include "Stage0.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
Stage0::Stage0() 
{
	StartPos.push_back({ 13, 2 });
	StartPos.push_back({ 13, 4 });
	StartPos.push_back({ 14, 3 });
	StartPos.push_back({ 13, 0 });
	StartPos.push_back({ 13, 1 });
	StartPos.push_back({ 14, 1 });
	StartPos.push_back({ 14, 2 });
	StartPos.push_back({ 12, 2 });
	StartPos.push_back({ 13, 3 });
	StartPos.push_back({ 14, 4 });
}

Stage0::~Stage0() 
{
}

void Stage0::StageSetting()
{
	SetStage(0);
	ClearTarget = BattleClearTarget::Conquer;
	ConquerPos = { 3, 7 };

	// 린
	Unit_Lyn = NewPlayerUnit(UnitIdentityCode::Lyn, 1, { 14, 0 }, { ItemCode::IronSword, ItemCode::Vulnerary, ItemCode::Vulnerary });

	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 2, 3 }, { ItemCode::IronAxe});
	// 바타
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 3, 7 }, { ItemCode::IronAxe})->SetDetectionRange(1);

	
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->SetTexture("EventBackground_House.png");
		OpeningEvent->Portrait1->SetTexture("Portrait_Lyn.png");
		OpeningEvent->Portrait1->Off();
		OpeningEvent->SetFadeIn(1.0f);
		OpeningEvent->Dialogue->SetFadeIn(1.0f);
		}
	, true, 1.0f);


	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait1->Off();
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->SetMoveSpeed(5.0f);
		Unit_Lyn->IsEventMove = true;
		Unit_Lyn->MoveMapPosLerp(int2::Up * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Left * 1);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Right * 1);
		}
	, false, 0.2f);
	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Down * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(0.5f);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->On();
		OpeningEvent->Portrait1->On();
		OpeningEvent->SetFadeIn(.5f);
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(1.0f);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(0.2f);
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait1->Off();
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->SetMoveSpeed(5.0f);
		Unit_Lyn->MoveMapPosLerp(int2::Up * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Left * 1);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->IsEventMove = false;
		Unit_Lyn->SetMoveSpeed(15.0f);
		}
	, false, .0f);
}

