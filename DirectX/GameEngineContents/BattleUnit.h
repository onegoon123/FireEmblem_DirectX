#pragma once
#include "MapUnit.h"
#include "Stat.h"
#include "Unit.h"
#include "ContentsEnum.h"
class BattleUnit : public MapUnit
{
public:

	BattleUnit();
	~BattleUnit();

	BattleUnit(const BattleUnit& _Other) = delete;
	BattleUnit(BattleUnit&& _Other) noexcept = delete;
	BattleUnit& operator=(const BattleUnit& _Other) = delete;
	BattleUnit& operator=(BattleUnit&& _Other) noexcept = delete;

	void SetIsTurnEnd(bool _Value);
	bool GetIsTurnEnd();
	bool GetIsDie()
	{
		return UnitData.IsDie;
	}
	void SetUnitCode(int _Code);
	void SetUnitCode(UnitIdentityCode _Code);
	int GetUnitCode()
	{
		return UnitData.UnitCode;
	}
	int GetMoveStat()
	{
		return UnitData.UnitStat.Movement;
	}

	void SetUnitData(Unit _Value)
	{
		UnitData = _Value;
	}

	const Unit& GetUnitData()
	{
		return UnitData;
	}

	void NewWeapon(ItemCode _Code)
	{
		UnitData.NewItem(_Code);
	}

	std::shared_ptr<class UnitRenderer> GetRenderer()
	{
		return Renderer;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class UnitRenderer> Renderer = nullptr;
	std::string_view ImageName = "";
private:
	Unit UnitData;
};

