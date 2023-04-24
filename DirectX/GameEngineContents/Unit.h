#pragma once
#include "Stat.h"
class Unit
{
	friend class BattleUnit;
	friend class UnitCommand;
public:
	// constrcuter destructer
	Unit();
	~Unit();

	Unit(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = _Other.UnitStat;
		CurrentHP = _Other.CurrentHP;
		UnitStat.EquipWeapon.SetWeaponStat(_Other.UnitStat.EquipWeapon.GetWeaponeStat());
		IsTurnEnd = _Other.IsTurnEnd;
	}

private:
	static int UnitNum;

	int UnitCode = 0;
	Stat UnitStat;
	int CurrentHP = 0;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	bool IsTurnEnd = false;
};

