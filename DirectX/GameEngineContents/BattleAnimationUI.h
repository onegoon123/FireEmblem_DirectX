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
	
	void SetData(class Unit& _Unit1, Unit& _Unit2);
	void SetDamage(Unit& _Unit);

	bool IsTurnEnd();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> UIRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> FadeRenderer = nullptr;

	std::shared_ptr<class BattleHPBar> PlayerHPBar = nullptr;
	std::shared_ptr<BattleHPBar> EnemyHPBar = nullptr;

	std::shared_ptr<class NumberActor> Number_PlayerHP = nullptr;
	std::shared_ptr<NumberActor> Number_PlayerDamage = nullptr;
	std::shared_ptr<NumberActor> Number_PlayerHit = nullptr;
	std::shared_ptr<NumberActor> Number_PlayerCritical = nullptr;

	std::shared_ptr<NumberActor> Number_EnemyHP = nullptr;
	std::shared_ptr<NumberActor> Number_EnemyDamage = nullptr;
	std::shared_ptr<NumberActor> Number_EnemyHit = nullptr;
	std::shared_ptr<NumberActor> Number_EnemyCritical = nullptr;

	std::shared_ptr<GameEngineUIRenderer> PlayerWeaponIcon = nullptr;
	std::shared_ptr<GameEngineUIRenderer> EnemyWeaponIcon = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PlayerTriangle = nullptr;
	std::shared_ptr<GameEngineUIRenderer> EnemyTriangle = nullptr;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

