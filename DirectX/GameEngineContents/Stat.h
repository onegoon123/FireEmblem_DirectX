#pragma once
#include "Weapon.h"
#include "ContentsEnum.h"
// 메인 스탯
// 레벨업시 성장할 능력치들
struct MainStat
{
	int HP = 0;				// 체력
	int Strength = 0;		// 힘
	int Magic = 0;			// 마력
	int Dexterity = 0;		// 기술
	int Speed = 0;			// 속도
	int Defense = 0;		// 수비
	int Resistance = 0;		// 마방
	int Luck = 0;			// 행운
	int Constitution = 0;	// 체격
};


// 스탯 클래스
// 유닛이 지닐 스탯을 관리하는 클래스
class Stat
{

public:
	Stat();
	~Stat();
	Stat(const Stat& _Other)
	{
		ClassValue = _Other.ClassValue;
		EquipWeapon = _Other.EquipWeapon;
		MainStatValue = _Other.MainStatValue;
		Level = _Other.Level;			// 레벨
		Movement = _Other.Movement;				// 이동력
		Experience = _Other.Experience;			// 경험치
		GrowthRates_HP = _Other.GrowthRates_HP;			// 체력 성장률
		GrowthRates_Strength = _Other.GrowthRates_Strength;	// 힘   성장률
		GrowthRates_Magic = _Other.GrowthRates_Magic;		// 마력 성장률
		GrowthRates_Dexterity = _Other.GrowthRates_Dexterity;	// 기술 성장률
		GrowthRates_Speed = _Other.GrowthRates_Speed;		// 속도 성장률
		GrowthRates_Defense = _Other.GrowthRates_Defense;	// 수비 성장률
		GrowthRates_Resistance = _Other.GrowthRates_Resistance;	// 마방 성장률
		GrowthRates_Luck = _Other.GrowthRates_Luck;		// 행운 성장률
	}

	BattleClass ClassValue = BattleClass::Lord;
	std::shared_ptr<Weapon> EquipWeapon = nullptr;		// 장비한 무기
	MainStat MainStatValue;
	int Level = 0;			// 레벨
	int Movement = 0;				// 이동력
	int Experience = 0;			// 경험치
	int GrowthRates_HP = 0;			// 체력 성장률
	int GrowthRates_Strength = 0;	// 힘   성장률
	int GrowthRates_Magic = 0;		// 마력 성장률
	int GrowthRates_Dexterity = 0;	// 기술 성장률
	int GrowthRates_Speed = 0;		// 속도 성장률
	int GrowthRates_Defense = 0;	// 수비 성장률
	int GrowthRates_Resistance = 0;	// 마방 성장률
	int GrowthRates_Luck = 0;		// 행운 성장률


	// 기초 스텟 지정
	void SetIdentity(int _IdentityCode);
	void SetIdentity(UnitIdentityCode _IdentityCode);
	// 경험치 증가 (레벨업 시 true)
	bool AddExperience(int _Experience);
	// 레벨 업 (경험치 증가 후 직접 실행, 증가한 능력치를 반환)
	MainStat LevelUp();

	int GetAttackPoint() const;
	int GetAttackPoint(BattleClass _TargetClass) const;
	int GetAttackPoint(const class Unit& _Other) const;
	int GetMagicAttackPoint() const;
	int GetHitPoint() const;
	int GetHitPoint(const class Unit& _Other) const;
	int GetCriticalPoint() const;
	int GetCriticalPoint(const class Unit& _Other) const;
	int GetAttackSpeedPoint() const;
	int GetDodgePoint() const;
	int GetCriticalDodgePoint() const;
	bool IsDoubleAttack(const class Unit& _Other) const;


private:
	void SetStat_Lyn();
	void SetStat_Sain();
	void SetStat_Kent();
	void SetStat_Florina();
	void SetStat_Wil();
	void SetStat_Dorcas();
	void SetStat_Serra();
	void SetStat_Erk();
	void SetStat_Rath();
	void SetStat_Matthew();
	void SetStat_Ninian();
	void SetStat_Lucius();
	void SetStat_Wallace();

	void ClassChange_BladeLord();
	void ClassChange_Warrior();
	void ClassChange_Assassin();
	void ClassChange_General();

	void SetStat_Brigand();
	void SetStat_Soldier();
	void SetStat_Mercenary();
	void SetStat_Archer();
	void SetStat_Knight();
	void SetStat_Mage();

};
