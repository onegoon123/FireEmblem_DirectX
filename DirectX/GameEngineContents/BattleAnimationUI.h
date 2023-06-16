#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Unit.h"
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

	void SetClassChange();
	void SetDefault();
	void SetFadeWhite();
	void SetFadeWait(float _Timer);
	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);
	
	void SetData(Unit& _Unit1, Unit& _Unit2, bool _Unit1Attackable, bool _Unit2Attackable);
	void SetDamage(Unit& _Unit);

	void SetEXP(int _Before, int _Get, Unit& _UnitData);
	void LevelUpStart(Unit& _UnitData);
	bool IsTurnEnd();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class BattleAnimationLevel* CurLevel = nullptr;
	GameEngineTimeEvent* TimeEvent = nullptr;
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

	std::shared_ptr<class EXPBar> EXPUI = nullptr;
	std::shared_ptr<class LevelUpUI> LevelUI = nullptr;

	Unit PlayerData;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	float WaitTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
	bool IsLevelUp = false;

	void EndExpUI();
};

