#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BattleHPBar : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleHPBar();
	~BattleHPBar();

	// delete Function
	BattleHPBar(const BattleHPBar& _Other) = delete;
	BattleHPBar(BattleHPBar&& _Other) noexcept = delete;
	BattleHPBar& operator=(const BattleHPBar& _Other) = delete;
	BattleHPBar& operator=(BattleHPBar&& _Other) noexcept = delete;

	void SetMaxHP(int _Value);
	void SetCurrentHP(int _Value);

	void SetHPAnimation(int _Value);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int MaxHP = 0;
	int CurrentHP = 0;
	float Timer = 0;
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> Renders;
};

