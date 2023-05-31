#include "PrecompileHeader.h"
#include "EventSystem.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
EventSystem::EventSystem() 
{
}

EventSystem::~EventSystem() 
{
}

void EventSystem::EventStart()
{
	EventIndex = 0;
	Events[0].Function();
	On();
}

void EventSystem::Start()
{
	Background = CreateComponent<GameEngineUIRenderer>();
	Background->GetTransform()->SetLocalScale({ 960, 640 });
	Background->Off();

	Portrait1 = CreateComponent<GameEngineUIRenderer>();
	Portrait1->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait1->Off();
	
	Portrait2 = CreateComponent<GameEngineUIRenderer>();
	Portrait2->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait2->Off();

	Portrait3 = CreateComponent<GameEngineUIRenderer>();
	Portrait3->GetTransform()->SetLocalScale({ 384, 320 });
	Portrait3->Off();
	Off();
}

void EventSystem::Update(float _DeltaTime)
{
	EventData& CurEvent = Events[EventIndex];
	if (true == CurEvent.ButtonCheck)
	{
		if (true == GameEngineInput::IsDown("ButtonA"))
		{
			Events[++EventIndex].Function();
		}
		return;
	}

	CurEvent.Timer -= _DeltaTime;
	if (CurEvent.Timer < 0)
	{
		Events[++EventIndex].Function();
	}
}

