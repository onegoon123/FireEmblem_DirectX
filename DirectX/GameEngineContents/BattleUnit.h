#pragma once
#include "MapUnit.h"
// Ό³Έν :
class GameEngineRender;
class BattleUnit : public MapUnit
{
public:
	// constrcuter destructer
	BattleUnit();
	~BattleUnit();

	// delete Function
	BattleUnit(const BattleUnit& _Other) = delete;
	BattleUnit(BattleUnit&& _Other) noexcept = delete;
	BattleUnit& operator=(const BattleUnit& _Other) = delete;
	BattleUnit& operator=(BattleUnit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineRenderer> SpriteRender = nullptr;
};

