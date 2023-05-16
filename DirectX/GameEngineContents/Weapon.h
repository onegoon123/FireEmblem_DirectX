#pragma once

#include "Item.h"
#include "ContentsEnum.h"
enum class WeaponType
{
	None,
	Sword,		// 검
	LanceReaver,
	Lance,		// 창
	AxeReaver,
	Axe,		// 도끼
	SwordReaver,
	Bow,		// 활
	AnimaTome,	// 속성마법
	DarkTome,	// 흑마법
	LightTome,	// 빛마법
};


// 설명 :
class Weapon : public Item
{
	//friend class Stat;
public:
	// constrcuter destructer
	Weapon();
	Weapon(ItemCode _Code);
	~Weapon();

	Weapon(const Weapon& _Other)
	{
		SetName(_Other.GetName());
		Damage = _Other.Damage;
		Hit = _Other.Hit;
		Critical = _Other.Critical;
		Weight = _Other.Weight;
		Range = _Other.Range;
		Uses = _Other.Uses;
		WeaponTypeValue = _Other.WeaponTypeValue;
		ValidArmour = _Other.ValidArmour;
		ValidHorse = _Other.ValidHorse;
		IsReaver = _Other.IsReaver;
	}

	Weapon operator=(const Weapon& _Other)
	{
		return Weapon(_Other);
	}

	static std::shared_ptr<Weapon> CreateWeapon(ItemCode _Code);

	// 무기의 상성을 체크하는 함수 (반환값이 1 : 유리, 0 : 일반, -1 : 불리)
	static int GetWeaponeTriangle(std::shared_ptr<Weapon> _SubjectWeapon, std::shared_ptr<Weapon> _TargetWeapon);

	// 해당 클래스가 이 무기를 사용 가능한가?
	bool IsUseWeapon(BattleClass _Class);

	WeaponType GetWeaponTypeValue()
	{
		return WeaponTypeValue;
	}

	int GetDamage() 
	{
		return Damage;
	}

	int GetHit()
	{
		return Hit;
	}

	int GetCritical()
	{
		return Critical;
	}

	int GetWeight()
	{
		return Weight;
	}

	int GetRange()
	{
		return Range;
	}

	bool GetValidArmour()
	{
		return ValidArmour;
	}

	bool GetValidHorse()
	{
		return ValidHorse;
	}

	bool GetIsReaver()
	{
		return IsReaver;
	}

protected:

private:
	WeaponType WeaponTypeValue = WeaponType::None;

	int Damage = 0;		// 공격력
	int Hit = 0;		// 명중률
	int Critical = 0;	// 치명타
	int Weight = 0;		// 무게
	int Range = 0;		// 사거리
	//int Uses = 0;		// 내구도

	bool ValidArmour = false;
	bool ValidHorse = false;
	bool IsReaver = false;

	void SetWeapon_SlimSword();
	void SetWeapon_IronSword();
	void SetWeapon_SteelSword();
	void SetWeapon_Lancereaver();
	void SetWeapon_Armourslayer();
	void SetWeapon_KillingSword();
	void SetWeapon_ManiKatti();

	void SetWeapon_SlimLance();
	void SetWeapon_IronLance();
	void SetWeapon_SteelLance();
	void SetWeapon_SilverLance();
	void SetWeapon_KillerLance();
	void SetWeapon_Axereaver();
	void SetWeapon_Horseslayer();

	void SetWeapon_HandAxe();
	void SetWeapon_IronAxe();
	void SetWeapon_Swordreaver();
	void SetWeapon_Hammer();

	void SetWeapon_ShortBow();
	void SetWeapon_IronBow();
	void SetWeapon_Ballista();


	void SetWeapon_Fire();
	void SetWeapon_Flux();
	void SetWeapon_Lightning();


};

