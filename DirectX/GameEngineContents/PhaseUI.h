#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
// Ό³Έν :
class GameEngineUIRenderer;
class PhaseUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PhaseUI();
	~PhaseUI();

	// delete Function
	PhaseUI(const PhaseUI& _Other) = delete;
	PhaseUI(PhaseUI&& _Other) noexcept = delete;
	PhaseUI& operator=(const PhaseUI& _Other) = delete;
	PhaseUI& operator=(PhaseUI&& _Other) noexcept = delete;

	void PhaseOn(Faction _Faction);
	bool PhaseUIEnd();
	void PhaseOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class PhaseState
	{
		Start,
		Wait,
		Disapear,
		End
	};
	PhaseState CurState = PhaseState::Start;

	std::shared_ptr<GameEngineUIRenderer> Renderer;
	float Timer = 0;
	bool IsEnd = false;

	void StartUpdate(float _DeltaTime);
	void WaitUpdate(float _DeltaTime);
	void DisapearUpdate(float _DeltaTime);
	void EndUpdate(float _DeltaTime);
};

