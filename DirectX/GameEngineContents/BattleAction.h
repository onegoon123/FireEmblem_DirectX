#pragma once

// Ό³Έν :
class BattleAction
{
public:
	// constrcuter destructer
	BattleAction();
	~BattleAction();

	// delete Function
	BattleAction(const BattleAction& _Other) = delete;
	BattleAction(BattleAction&& _Other) noexcept = delete;
	BattleAction& operator=(const BattleAction& _Other) = delete;
	BattleAction& operator=(BattleAction&& _Other) noexcept = delete;

protected:

private:

};

