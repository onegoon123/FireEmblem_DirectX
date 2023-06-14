#include "PrecompileHeader.h"
#include "Stage10.h"
#include "FEData.h"
Stage10::Stage10()
{
	// юс╫ц
	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 3, 15 });
	StartPos.push_back({ 2, 14 });
	StartPos.push_back({ 1, 16 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });
	StartPos.push_back({ 1, 15 });


}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);

	OpeningEventInit();
	ClearEventInit();
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
