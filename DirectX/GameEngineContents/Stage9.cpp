#include "PrecompileHeader.h"
#include "Stage9.h"

Stage9::Stage9()
{
	// юс╫ц
	StartPos.push_back({ 3, 3 });
	StartPos.push_back({ 2, 4 });
	StartPos.push_back({ 3, 5 });
	StartPos.push_back({ 2, 2 });
	StartPos.push_back({ 1, 3 });
	StartPos.push_back({ 3, 1 });
	StartPos.push_back({ 4, 1 });
	StartPos.push_back({ 5, 1 });
	StartPos.push_back({ 7, 1 });
	StartPos.push_back({ 7, 1 });
	StartPos.push_back({ 7, 1 });
	StartPos.push_back({ 7, 1 });
	StartPos.push_back({ 7, 1 });
}

Stage9::~Stage9()
{
}

void Stage9::StageSetting()
{
	SetStage(9);
	OpeningEventInit();
	ClearEventInit();
}

void Stage9::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage9::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage10");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage10");
	};
}
