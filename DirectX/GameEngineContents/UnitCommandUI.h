#pragma once
#include <GameEngineCore/GameEngineActor.h>
class UnitCommandUI : public GameEngineActor
{
public:
	// constructer destructer
	UnitCommandUI();
	~UnitCommandUI();

	// delete Function
	UnitCommandUI(const UnitCommandUI& _Other) = delete;
	UnitCommandUI(UnitCommandUI&& _Other) = delete;
	UnitCommandUI& operator=(const UnitCommandUI& _Other) = delete;
	UnitCommandUI& operator=(UnitCommandUI&& _Other) = delete;

protected:

private:

};

