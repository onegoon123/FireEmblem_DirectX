#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
// Ό³Έν :
class SpriteRenderer;
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

protected:
	void Start() override;
	void Update(float _DeltaTiime) override;

private:

	std::shared_ptr<SpriteRenderer> Renderer;
	float Timer = 0;

};

