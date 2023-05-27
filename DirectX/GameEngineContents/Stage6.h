#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage6 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage6();
	~Stage6();

	// delete Function
	Stage6(const Stage6& _Other) = delete;
	Stage6(Stage6&& _Other) noexcept = delete;
	Stage6& operator=(const Stage6& _Other) = delete;
	Stage6& operator=(Stage6&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:

};

