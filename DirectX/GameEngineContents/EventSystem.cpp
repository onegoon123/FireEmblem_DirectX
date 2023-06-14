#include "PrecompileHeader.h"
#include "EventSystem.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
EventSystem::EventSystem()
{
	Events.reserve(100);
}

EventSystem::~EventSystem()
{
}

void EventSystem::EventStart()
{
	if (Events.size() == 0)
	{
		
		IsEnd = true;
		return;
	}
	EventIndex = 0;
	Reset();
	Events[0].Function();
	On();
}

void EventSystem::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	Foreground->ColorOptionValue.MulColor.a = 1;
	Foreground->On();
}

void EventSystem::SetFadeOut(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	Foreground->ColorOptionValue.MulColor.a = 0;
	Foreground->On();
}

void EventSystem::Start()
{
	Background = CreateComponent<GameEngineUIRenderer>(0);
	Background->GetTransform()->SetLocalScale({ 960, 640 });
	Background->Off();

	Foreground = CreateComponent<GameEngineUIRenderer>(2);
	Foreground->GetTransform()->SetLocalScale({ 960, 640 });
	Foreground->SetTexture("Black.png");
	Foreground->Off();

	Portrait1 = CreateComponent<GameEngineUIRenderer>(1);
	Portrait1->GetTransform()->SetLocalPosition({ 0, -160 });
	Portrait1->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait1->Off();

	Portrait2 = CreateComponent<GameEngineUIRenderer>(1);
	Portrait2->GetTransform()->SetLocalPosition({ 284, -160 }); // 오른쪽 구석
	Portrait2->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait2->Off();

	Portrait3 = CreateComponent<GameEngineUIRenderer>(1);
	Portrait3->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait3->Off();

	Portrait4 = CreateComponent<GameEngineUIRenderer>(1);
	Portrait4->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait4->Off();

	Dialogue = GetLevel()->CreateActor<DialogueSystem>();
	Dialogue->GetTransform()->SetParent(GetTransform());
	Dialogue->Off();

	Off();
}

void EventSystem::Update(float _DeltaTime)
{
	
	if (true == IsEnd) { return; }
	FadeUpdate(_DeltaTime);

	if (GameEngineInput::IsDown("Start"))
	{
		if (nullptr != SkipFunction)
		{
			SkipFunction();
		}
		IsEnd = true;
	}

	EventData& CurEvent = Events[EventIndex];

	CurEvent.Timer -= _DeltaTime;
	if (CurEvent.Timer < 0)
	{
		if (true == CurEvent.ButtonCheck && false == GameEngineInput::IsDown("ButtonA") && false == GameEngineInput::IsDown("LeftClick"))
		{
			return;
		}
		++EventIndex;
		if (Events.size() <= EventIndex)
		{
			IsEnd = true;
			return;
		}
		if (nullptr == Events[EventIndex].Function) { return; }
		Events[EventIndex].Function();
	}
}

void EventSystem::FadeUpdate(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeIn = false;
			Foreground->ColorOptionValue.MulColor.a = 0;
			return;
		}
		Foreground->ColorOptionValue.MulColor.a = FadeTimer;
	}

	if (true == IsFadeOut)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeOut = false;
			Foreground->ColorOptionValue.MulColor.a = 1;
			return;
		}
		Foreground->ColorOptionValue.MulColor.a = FadeTimer;
	}
}

void EventSystem::Reset()
{
	Background->GetTransform()->SetLocalScale({ 960, 640 });
	Background->Off();

	Foreground->GetTransform()->SetLocalScale({ 960, 640 });
	Foreground->SetTexture("Black.png");
	Foreground->Off();

	Portrait1->GetTransform()->SetLocalPosition({ 0, -160 });
	Portrait1->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait1->Off();

	Portrait2->GetTransform()->SetLocalPosition({ 284, -160 }); // 오른쪽 구석
	Portrait2->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait2->Off();

	Portrait3->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait3->Off();

	Portrait4->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait4->Off();

	Dialogue->GetTransform()->SetParent(GetTransform());
	Dialogue->Off();

	FadeTimer = 0;
	IsFadeIn = false;
	IsFadeOut = false;
	IsEnd = false;
}

