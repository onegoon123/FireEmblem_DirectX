#pragma once

#include "Item.h"

enum class WeaponType
{
	Sword,		// 검
	Lance,		// 창
	Axe,		// 도끼
	Bow,		// 활
	Stave,		// 지팡이
	AnimaTome,	// 속성마법
	LightTome,	// 빛마법
};

// 설명 :
class Weapon : public Item
{
	friend class Stat;
public:
	// constrcuter destructer
	Weapon();
	~Weapon();

	Weapon(const Weapon& _Other)
	{
		Damage = _Other.Damage;
		Hit = _Other.Hit;
		Critical = _Other.Critical;
		Weight = _Other.Weight;
		Range = _Other.Range;
		Uses = _Other.Uses;
	}
	Weapon operator=(const Weapon& _Other)
	{
		Weapon NewWeapon(_Other);
		//NewWeapon.Damage = _Other.Damage;
		//NewWeapon.Hit = _Other.Hit;
		//NewWeapon.Critical = _Other.Critical;
		//NewWeapon.Weight = _Other.Weight;
		//NewWeapon.Range = _Other.Range;
		//NewWeapon.Uses = _Other.Uses;

		return NewWeapon;
	}

	void SetWeaponStat(Weapon _Other)
	{
		Damage = _Other.Damage;
		Hit = _Other.Hit;
		Critical = _Other.Critical;
		Weight = _Other.Weight;
		Range = _Other.Range;
		Uses = _Other.Uses;
	}

	Weapon GetWeaponeStat() const
	{
		return *this;
	}

	int Damage = 0;		// 공격력
	int Hit = 0;		// 명중률
	int Critical = 0;	// 치명타
	int Weight = 0;		// 무게
	int Range = 0;		// 사거리
	int Uses = 0;		// 내구도
protected:

private:
};

