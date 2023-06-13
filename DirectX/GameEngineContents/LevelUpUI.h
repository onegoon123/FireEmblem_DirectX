#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include "Unit.h"
// Ό³Έν :
class LevelUpUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelUpUI();
	~LevelUpUI();

	// delete Function
	LevelUpUI(const LevelUpUI& _Other) = delete;
	LevelUpUI(LevelUpUI&& _Other) noexcept = delete;
	LevelUpUI& operator=(const LevelUpUI& _Other) = delete;
	LevelUpUI& operator=(LevelUpUI&& _Other) noexcept = delete;

	void LevelUpStart(Unit& _UnitData);

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	class BattleAnimationLevel* CurLevel = nullptr;
	GameEngineFSM FSM;
	GameEngineTimeEvent TimeEvent;
	std::shared_ptr<class GameEngineUIRenderer> LevelUpImage = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UIBack = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UIRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UIPortraitRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UITextRender = nullptr;

	std::shared_ptr<class NumberActor> Number_Level = nullptr;
	std::vector< std::shared_ptr<NumberActor>> Number_Stats;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> UpStatBacks;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> UpStatArrows;

	MainStat UpStat;
	int Count = -1;
	float Timer = 0;
};

