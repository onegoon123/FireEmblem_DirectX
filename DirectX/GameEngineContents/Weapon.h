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

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

protected:

private:
	int Damage = 0;		// 공격력
	int Hit = 0;		// 명중률
	int Critical = 0;	// 치명타
	int Weight = 0;		// 무게
	int Range = 0;		// 사거리
	int Uses = 0;		// 내구도
};

