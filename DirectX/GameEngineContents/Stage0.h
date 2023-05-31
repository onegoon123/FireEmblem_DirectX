#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage0 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage0();
	~Stage0();

	// delete Function
	Stage0(const Stage0& _Other) = delete;
	Stage0(Stage0&& _Other) noexcept = delete;
	Stage0& operator=(const Stage0& _Other) = delete;
	Stage0& operator=(Stage0&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:

	std::shared_ptr<BattleUnit> Unit_Lyn = nullptr;
};

