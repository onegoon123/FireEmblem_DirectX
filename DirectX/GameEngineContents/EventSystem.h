#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class EventSystem : public GameEngineActor
{
public:
	// constrcuter destructer
	EventSystem();
	~EventSystem();

	// delete Function
	EventSystem(const EventSystem& _Other) = delete;
	EventSystem(EventSystem&& _Other) noexcept = delete;
	EventSystem& operator=(const EventSystem& _Other) = delete;
	EventSystem& operator=(EventSystem&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineUIRenderer> Background = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Portrait1 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Portrait2 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Portrait3 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Portrait4 = nullptr;

	void PushEvent(std::function<void()> _Function, bool _ButtonCheck = false, float _Timer = 0.0f)
	{
		EventData NewEvent;
		NewEvent.Function = _Function;
		NewEvent.ButtonCheck = _ButtonCheck;
		NewEvent.Timer = _Timer;
	}
	void EventStart();
	bool GetIsEnd() { return IsEnd; }
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	struct EventData
	{
		std::function<void()> Function;
		bool ButtonCheck = false;
		float Timer = 0.0f;
	};
	std::vector<EventData> Events;
	size_t EventIndex = 0;
	
	bool IsEnd = false;
};

