#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

// Ό³Έν :
class SpriteRenderer;
class BattleUnit;
class BattleAnimationUnit : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleAnimationUnit();
	~BattleAnimationUnit();

	// delete Function
	BattleAnimationUnit(const BattleAnimationUnit& _Other) = delete;
	BattleAnimationUnit(BattleAnimationUnit&& _Other) noexcept = delete;
	BattleAnimationUnit& operator=(const BattleAnimationUnit& _Other) = delete;
	BattleAnimationUnit& operator=(BattleAnimationUnit&& _Other) noexcept = delete;

	void SetAnimation(std::shared_ptr<BattleUnit> _Unit);
	void SetAnimation(BattleClass _ClassValue);

	void SetLeft();
	void SetRight();

	void SetAttack();

	float GetAttackTime() { return AttackTime; }
	float GetAttackEffectTime() { return AttackEffectTime; }
	float GetCriticalTime() { return CriticalTime; }
	float GetCriticalEffectTime() { return CriticalEffectTime; }

protected:
	void Update(float _DeltaTime) override;
	
private:
	BattleClass ClassValue = BattleClass::Lord;

	std::map<BattleClass, std::shared_ptr<SpriteRenderer>> Animations;
	std::shared_ptr<SpriteRenderer> CurAnimation;
	float AttackTime = 0.0f;
	float AttackEffectTime = 0.0f;
	float CriticalTime = 0.0f;
	float CriticalEffectTime = 0.0f;
	float DodgeTime = 0.0f;
	std::shared_ptr<SpriteRenderer> CreateAnimation(BattleClass _ClassValue);
};

