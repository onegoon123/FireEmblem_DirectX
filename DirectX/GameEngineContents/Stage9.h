#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage9 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage9();
	~Stage9();

	// delete Function
	Stage9(const Stage9& _Other) = delete;
	Stage9(Stage9&& _Other) noexcept = delete;
	Stage9& operator=(const Stage9& _Other) = delete;
	Stage9& operator=(Stage9&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:

};

