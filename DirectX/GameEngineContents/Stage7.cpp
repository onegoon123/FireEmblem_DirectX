#include "PrecompileHeader.h"
#include "Stage7.h"

Stage7::Stage7()
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
}

Stage7::~Stage7()
{
}

void Stage7::StageSetting()
{
	SetStage(7);
	OpeningEventInit();
	ClearEventInit();
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

