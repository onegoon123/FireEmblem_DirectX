#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage3 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage3();
	~Stage3();

	// delete Function
	Stage3(const Stage3& _Other) = delete;
	Stage3(Stage3&& _Other) noexcept = delete;
	Stage3& operator=(const Stage3& _Other) = delete;
	Stage3& operator=(Stage3&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:
	void OpeningEventInit();
	void ClearEventInit();
};

