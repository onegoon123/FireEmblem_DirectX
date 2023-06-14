#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage7 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage7();
	~Stage7();

	// delete Function
	Stage7(const Stage7& _Other) = delete;
	Stage7(Stage7&& _Other) noexcept = delete;
	Stage7& operator=(const Stage7& _Other) = delete;
	Stage7& operator=(Stage7&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:
	void OpeningEventInit();
	void ClearEventInit();
};

