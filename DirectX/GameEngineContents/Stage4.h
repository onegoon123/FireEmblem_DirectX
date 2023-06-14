#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage4 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage4();
	~Stage4();

	// delete Function
	Stage4(const Stage4& _Other) = delete;
	Stage4(Stage4&& _Other) noexcept = delete;
	Stage4& operator=(const Stage4& _Other) = delete;
	Stage4& operator=(Stage4&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:
	void OpeningEventInit();
	void ClearEventInit();
};

