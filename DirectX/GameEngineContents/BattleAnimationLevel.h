#pragma once
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "UnitCommand.h"
// Ό³Έν :
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

	static void SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data, const std::string_view& _Level);

	void HitEvent();
	void HealEvent();
	void TurnEnd();

	void BattleEnd();

	GameEngineTimeEvent TimeEvent;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	static std::string_view ReturnLevelStr;
	static std::shared_ptr<class BattleUnit> SubjectUnit;
	static std::shared_ptr<BattleUnit> TargetUnit;
	static std::list<AttackCommand> BattleData;
	static std::list<AttackCommand>::iterator BattleIter;

	std::shared_ptr<class SpriteRenderer> BackgroundRender;
	std::shared_ptr<SpriteRenderer> TerrainLeft;
	std::shared_ptr<SpriteRenderer> TerrainRight;
	std::shared_ptr<class BattleAnimationUnit> SubjectAnimation;
	std::shared_ptr<BattleAnimationUnit> TargetAnimation;
	std::shared_ptr<BattleAnimationUnit> LeftUnit;
	std::shared_ptr<BattleAnimationUnit> RightUnit;
	std::shared_ptr<class BattleAnimationUI> UI;

	bool IsTurnEnd = false;

	void PlayAttack();
	void End();
};

