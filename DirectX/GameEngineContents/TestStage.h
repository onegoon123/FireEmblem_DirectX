#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class TestStage : public BattleLevel
{
public:
	// constrcuter destructer
	TestStage();
	~TestStage();

	// delete Function
	TestStage(const TestStage& _Other) = delete;
	TestStage(TestStage&& _Other) noexcept = delete;
	TestStage& operator=(const TestStage& _Other) = delete;
	TestStage& operator=(TestStage&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:
	void OpeningEventInit();
	void ClearEventInit();
};

