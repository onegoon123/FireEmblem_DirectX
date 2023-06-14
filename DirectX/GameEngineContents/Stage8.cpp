#include "PrecompileHeader.h"
#include "Stage8.h"

Stage8::Stage8()
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

Stage8::~Stage8()
{
}

void Stage8::StageSetting()
{
	SetStage(8);


	OpeningEventInit();
	ClearEventInit();
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

