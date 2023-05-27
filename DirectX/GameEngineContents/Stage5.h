#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage5 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage5();
	~Stage5();

	// delete Function
	Stage5(const Stage5& _Other) = delete;
	Stage5(Stage5&& _Other) noexcept = delete;
	Stage5& operator=(const Stage5& _Other) = delete;
	Stage5& operator=(Stage5&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:

};

