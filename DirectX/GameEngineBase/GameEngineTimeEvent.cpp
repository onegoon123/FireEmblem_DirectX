#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{
}

GameEngineTimeEvent::~GameEngineTimeEvent()
{
}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void()> _Event, bool _Loop /*= false*/)
{
	// 기본 생성자가 있으면
	// 그냥 자기가 내부에서 기본생성자 가지고 만들어주는 것.
	TimeEvent& NewEvent = Event.emplace_back();
	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	for (size_t i = 0; i < Event.size(); i++)
	{
		Event[i].CurTime -= _DeltaTime;

		if (Event[i].CurTime < 0.0f)
		{
			Event[i].Event();
			if (true == Event[i].Loop)
			{
				Event[i].CurTime = Event[i].Time;
			}
		}
	}
}