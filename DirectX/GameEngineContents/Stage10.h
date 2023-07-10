#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage10 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage10();
	~Stage10();

	// delete Function
	Stage10(const Stage10& _Other) = delete;
	Stage10(Stage10&& _Other) noexcept = delete;
	Stage10& operator=(const Stage10& _Other) = delete;
	Stage10& operator=(Stage10&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:
	void OpeningEventInit();
	void ClearEventInit();

	GameEngineSoundPlayer EventBgmPlayer;
};

