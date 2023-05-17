#pragma once
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "UnitCommand.h"
// Ό³Έν :
class SpriteRenderer;
class BattleAnimationUnit;
class BattleAnimationLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BattleAnimationLevel();
	~BattleAnimationLevel();

	// delete Function
	BattleAnimationLevel(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel(BattleAnimationLevel&& _Other) noexcept = delete;
	BattleAnimationLevel& operator=(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel& operator=(BattleAnimationLevel&& _Other) noexcept = delete;

	static void SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data);

	void HitEvent();
	void TurnEnd();

	GameEngineTimeEvent TimeEvent;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
private:
	static std::shared_ptr<BattleUnit> SubjectUnit;
	static std::shared_ptr<BattleUnit> TargetUnit;
	static std::list<AttackCommand> BattleData;
	static std::list<AttackCommand>::iterator BattleIter;

	std::shared_ptr<SpriteRenderer> BackgroundRender;
	std::shared_ptr<SpriteRenderer> TerrainLeft;
	std::shared_ptr<SpriteRenderer> TerrainRight;
	std::shared_ptr<BattleAnimationUnit> SubjectAnimation;
	std::shared_ptr<BattleAnimationUnit> TargetAnimation;
	std::shared_ptr<BattleAnimationUnit> LeftUnit;
	std::shared_ptr<BattleAnimationUnit> RightUnit;
	std::shared_ptr<SpriteRenderer> UIRender;

	void Test();
	void End();
};

