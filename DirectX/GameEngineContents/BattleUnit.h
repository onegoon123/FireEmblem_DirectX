#pragma once
#include "MapUnit.h"
#include "Unit.h"
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

	void SetIsTurnEnd(bool _Value);
	bool GetIsTurnEnd() { return IsTurnEnd; }

	void SetUnitCode(int _Code);
	int GetUnitCode() { return UnitCode; }

	int GetMoveStat() { return UnitStat.Movement; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class GameEngineRenderer> SpriteRender = nullptr;
	std::string_view ImageName = "";
private:
	int UnitCode = 0;
	Stat UnitStat;
	bool IsTurnEnd = false;
};

