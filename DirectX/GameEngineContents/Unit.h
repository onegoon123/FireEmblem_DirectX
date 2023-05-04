#pragma once
#include "Stat.h"
#include "Weapon.h"
#include "ContentsEnum.h"
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
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
	}
	void operator=(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
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

	int UnitCode = 0;
	int CurrentHP = 0;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	bool IsTurnEnd = false;
	bool IsDie = false;
	bool IsPlayer = false;
	Stat UnitStat;

	void NewItem(ItemCode _Code);
	

private:

	std::list<std::shared_ptr<Item>> Items = std::list<std::shared_ptr<Item>>();
	
};

