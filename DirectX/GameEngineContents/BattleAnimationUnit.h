#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class SpriteRenderer;
struct BattleAnimation
{
	std::shared_ptr<SpriteRenderer> Renderer = nullptr;
	float AttackTime = 0.0f;
	float AttackEffectTime = 0.0f;
	float CriticalTime = 0.0f;
	float CriticalEffectTime = 0.0f;
	float DodgeTime = 0.0f;
};

// Ό³Έν :
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

	void SetAttack();
	void SetCritical();
	void SetDodge();

	float GetAttackTime() { return CurAnimation.AttackTime; }
	float GetAttackEffectTime() { return CurAnimation.AttackEffectTime; }
	float GetCriticalTime() { return CurAnimation.CriticalTime; }
	float GetCriticalEffectTime() { return CurAnimation.CriticalEffectTime; }

protected:
	void Update(float _DeltaTime) override;
	
private:
	BattleClass ClassValue = BattleClass::Lord;

	BattleAnimation CurAnimation;
	std::map<BattleClass, BattleAnimation> Animations;

	BattleAnimation CreateAnimation(BattleClass _ClassValue);
};

