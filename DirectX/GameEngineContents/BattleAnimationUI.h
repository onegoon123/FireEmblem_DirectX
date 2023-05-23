#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class BattleAnimationUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleAnimationUI();
	~BattleAnimationUI();

	// delete Function
	BattleAnimationUI(const BattleAnimationUI& _Other) = delete;
	BattleAnimationUI(BattleAnimationUI&& _Other) noexcept = delete;
	BattleAnimationUI& operator=(const BattleAnimationUI& _Other) = delete;
	BattleAnimationUI& operator=(BattleAnimationUI&& _Other) noexcept = delete;

	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);
		
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> UIRenderer = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> FadeRenderer = nullptr;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

