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

	bool GetIsLerp()
	{
		return IsLerp;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int MaxHP = 0;
	int HP = 0;

	int TargetHP = 0;
	const float Time = 0.05f;
	float Timer = 0;
	bool IsLerp = false;

	std::vector<std::shared_ptr<class GameEngineUIRenderer>> Renders;
};

