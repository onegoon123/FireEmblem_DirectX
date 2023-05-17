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
	void SetAnimation(UnitIdentityCode _IdentityValue);

	void Attack();
	void Critical();
	void Dodge();
	void HitEffect(const std::string_view& _Name);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	BattleAnimationLevel* Level = nullptr;
	std::shared_ptr<BattleUnit> UnitValue = nullptr;

	std::weak_ptr<BattleAnimationUnit> EnemyUnit;

	UnitIdentityCode IdentityValue = UnitIdentityCode::Lyn;
	std::shared_ptr<SpriteRenderer> CurAnimation;
	std::map<UnitIdentityCode, std::shared_ptr<SpriteRenderer>> Animations;
	std::shared_ptr<SpriteRenderer> EffectAnimation = nullptr;

	std::shared_ptr<SpriteRenderer> CreateAnimation(UnitIdentityCode _UnitIdentity);

	void AttackLoop(float _Timer);
	void AttackLoopEnd();
	void AttackEnd();
};

