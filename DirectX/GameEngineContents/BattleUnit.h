#pragma once
#include "MapUnit.h"
#include "Stat.h"
#include "Unit.h"
// Ό³Έν :
class GameEngineRender;
class BattleUnit : public MapUnit
{
	friend class UnitCommand;
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
	bool GetIsTurnEnd();

	void SetUnitCode(int _Code);
	int GetUnitCode();

	int GetMoveStat();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class GameEngineRenderer> SpriteRender = nullptr;
	std::string_view ImageName = "";
private:
	Unit UnitData;
};

