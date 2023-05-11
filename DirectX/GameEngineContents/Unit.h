#pragma once
#include "Stat.h"
#include "Weapon.h"
#include "ContentsEnum.h"
#include "BattleMap.h"
class Unit : public GameEngineNameObject
{
public:

	Unit();
	~Unit();
	Unit(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainData = _Other.TerrainData;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
		Items = _Other.Items;
		Weapons = _Other.Weapons;
	}
	void operator=(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainData = _Other.TerrainData;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
		Items = _Other.Items;
		Weapons = _Other.Weapons;
	}
	std::string ToString() const
	{
		std::string Str;
		Str += "체력 : " + std::to_string(CurrentHP) + " / " + std::to_string(UnitStat.MainStatValue.HP) + '\n';
		Str += "공격력 : " + std::to_string(UnitStat.GetAttackPoint());
		return Str;
	}

	void LevelUp()
	{
		MainStat UpStat = UnitStat.LevelUp();
		if (1 <= UpStat.HP)
		{
			CurrentHP += UpStat.HP;
		}
	}
	void LevelUp(int _Value)
	{
		for (int i = 0; i < _Value; i++)
		{
			MainStat UpStat = UnitStat.LevelUp();
			if (1 <= UpStat.HP)
			{
				CurrentHP += UpStat.HP;
			}
		}
	}

	void Recover(int _Value)
	{
		CurrentHP += _Value;
		if (UnitStat.MainStatValue.HP < CurrentHP)
		{
			CurrentHP = UnitStat.MainStatValue.HP;
		}
	}

	void RecoverPersent(float _Value)
	{
		Recover(static_cast<int>(std::roundf(UnitStat.MainStatValue.HP * _Value)));
	}

	int GetRangeStat();
	const std::list<std::shared_ptr<Weapon>>& GetWeapons()
	{
		return Weapons;
	}
	std::list<std::shared_ptr<Item>>& GetItems()
	{
		return Items;
	}
	void EquipWeapon(std::shared_ptr<Weapon> _Weapon);
	void UseItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	void DropItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);

	int UnitCode = -1;
	int CurrentHP = 0;
	Terrain TerrainData = Terrain::None;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	bool IsTurnEnd = false;
	bool IsDie = false;
	bool IsPlayer = false;
	Stat UnitStat;

	void NewItem(ItemCode _Code);
	

private:

	std::list<std::shared_ptr<Item>> Items = std::list<std::shared_ptr<Item>>();
	std::list<std::shared_ptr<Weapon>> Weapons = std::list<std::shared_ptr<Weapon>>();
	
};

