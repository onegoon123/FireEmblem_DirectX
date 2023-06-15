#pragma once
#include "Weapon.h"
#include "ContentsEnum.h"
// 메인 스탯
// 레벨업시 성장할 능력치들
struct MainStat
{
	union
	{
		struct
		{
			int HP;				// 체력
			int Strength;		// 힘
			int Magic;			// 마력
			int Dexterity;		// 기술
			int Speed;			// 속도
			int Defense;		// 수비
			int Resistance;		// 마방
			int Luck;			// 행운
			int Constitution;	// 체격
		};
		int Array[9];
	};

	MainStat()
	{
		Array[0] = 0;
		HP = 0;
		Strength = 0;
		Magic = 0;
		Dexterity = 0;
		Speed = 0;
		Defense = 0;
		Resistance = 0;
		Luck = 0;
		Constitution = 0;
	}
	MainStat operator-(MainStat& _Other)
	{
		MainStat ReturnStat;
		ReturnStat.HP = HP - _Other.HP;
		ReturnStat.Strength = Strength - _Other.Strength;
		ReturnStat.Magic = Magic - _Other.Magic;
		ReturnStat.Dexterity = Dexterity - _Other.Dexterity;
		ReturnStat.Speed = Speed - _Other.Speed;
		ReturnStat.Defense = Defense - _Other.Defense;
		ReturnStat.Resistance = Resistance - _Other.Resistance;
		ReturnStat.Luck = Luck - _Other.Luck;
		ReturnStat.Constitution = Constitution - _Other.Constitution;
		return ReturnStat;
	}
	void operator+=(MainStat& _Other)
	{
		HP += _Other.HP;
		Strength += _Other.Strength;
		Magic += _Other.Magic;
		Dexterity +=  _Other.Dexterity;
		Speed += _Other.Speed;
		Defense += _Other.Defense;
		Resistance += _Other.Resistance;
		Luck += _Other.Luck;
		Constitution +=  _Other.Constitution;
	}

public:
	int GetAttackStat(WeaponType _Value) const;

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
		MainStatValue = _Other.MainStatValue;
		MaximumStat = _Other.MaximumStat;
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
	MainStat MainStatValue;
	MainStat MaximumStat;

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



	MainStat ClassChange_BladeLord();
	MainStat ClassChange_Warrior();
	MainStat ClassChange_Assassin();
	MainStat ClassChange_General();

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


	void SetStat_Brigand();
	void SetStat_Soldier();
	void SetStat_Mercenary();
	void SetStat_Archer();
	void SetStat_Knight();
	void SetStat_Mage();

	void SetStat_Batta();
	void SetStat_Zugu();
	void SetStat_Glass();
	void SetStat_Migal();
	void SetStat_Carjiga();

};
