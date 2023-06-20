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

	void On();

protected:
	void Start() override;
	
private:
	std::vector<std::shared_ptr<class DialogueBox>> CommandBoxs;
	std::list<UnitCommand>* CommandList = nullptr;
};

