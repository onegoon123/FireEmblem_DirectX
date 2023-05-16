#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class SpriteRenderer;
class BattleUnit;
class BattleAnimationLevel;

// Ό³Έν :
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

	void Attack();
	void Critical();
	void Dodge();
	void Damage();
	void CriticalDamage();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	BattleAnimationLevel* Level = nullptr;
	std::weak_ptr<BattleAnimationUnit> EnemyUnit;

	BattleClass ClassValue = BattleClass::Lord;
	std::shared_ptr<SpriteRenderer> CurAnimation;
	std::map<BattleClass, std::shared_ptr<SpriteRenderer>> Animations;
	std::shared_ptr<SpriteRenderer> EffectAnimation = nullptr;

	std::shared_ptr<SpriteRenderer> CreateAnimation(BattleClass _ClassValue);

};

