#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UnitCommand.h"

class TimeStoneUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TimeStoneUI();
	~TimeStoneUI();

	// delete Function
	TimeStoneUI(const TimeStoneUI& _Other) = delete;
	TimeStoneUI(TimeStoneUI&& _Other) noexcept = delete;
	TimeStoneUI& operator=(const TimeStoneUI& _Other) = delete;
	TimeStoneUI& operator=(TimeStoneUI&& _Other) noexcept = delete;

	void Setting(class BattleLevel* _Level);
	void On(bool _IsGameOver = false);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BattleLevel* CurLevel = nullptr;
	std::function<void()> Rewind = nullptr;
	std::function<void()> Play = nullptr;
	std::function<void()> Select = nullptr;
	std::function<void()> Cancel = nullptr;

	std::vector<std::shared_ptr<class TimeCommand>> CommandRenders;
	std::vector<UnitCommand> CommandList;

	float4 MoveTarget;
	int CurrentCursor = 0;
	Faction CurFaction = Faction::None;

	const float WaitTime = 0.1f;
	float Timer = 0.0f;
	const float PreesTime = 0.4f;
	bool PressOK = false;
	bool IsGameOver = false;
	void CommandMoveUp();
	void CommandMoveDown();
	void CommandSetting();
};

