#pragma once
#include "BattleLevel.h"
// Ό³Έν :
class Stage8 : public BattleLevel
{
public:
	// constrcuter destructer
	Stage8();
	~Stage8();

	// delete Function
	Stage8(const Stage8& _Other) = delete;
	Stage8(Stage8&& _Other) noexcept = delete;
	Stage8& operator=(const Stage8& _Other) = delete;
	Stage8& operator=(Stage8&& _Other) noexcept = delete;

protected:
	void StageSetting() override;
private:

};

