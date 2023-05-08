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
	void SetIsDie(bool _Value)
	{
		UnitData.IsDie = _Value;
	}
	bool GetIsDie()
	{
		return UnitData.IsDie;
	}
	bool GetIsPlayer()
	{
		return UnitData.IsPlayer;
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
		if (false == UnitData.IsDie)
		{
			On();
		}
		else
		{
			Off();
		}
		SetIsTurnEnd(GetIsTurnEnd());
	}

	void SetTerrain(Terrain _TerrainData, int _TerrainDodge, int _TerrainDeffence)
	{
		UnitData.TerrainData = _TerrainData;
		UnitData.TerrainDodge = _TerrainDodge;
		UnitData.TerrainDeffence = _TerrainDeffence;
	}

	Unit& GetUnitData()
	{
		return UnitData;
	}

	void NewWeapon(ItemCode _Code)
	{
		UnitData.NewItem(_Code);
	}

	std::shared_ptr<class SpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

	std::string ToString() const
	{
		std::string Str;
		Str += "¿Ã∏ß : " + std::string(GetName()) + '\n';
		Str += UnitData.ToString();
		return Str;
	}

	bool GetIsCheckTile() { return IsCheckTile; }
	void SetIsCheckTile(bool _Value) { IsCheckTile = _Value; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class SpriteRenderer> Renderer = nullptr;
	std::string_view ImageName = "";
private:
	Unit UnitData;

	bool IsCheckTile = false;
};

