#pragma once
#include <string>

// 유닛 클래스
// 배틀 시 화면에 나타날 플레이어, 적, 기타 오브젝트의 부모 클래스
class Unit
{
public:
	// constructer destructer
	Unit();
	~Unit();

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) = delete;

protected:

private:
	int IdentityCode = 0;
	std::string UnitName = "";
	//Stat UnitStat;
};

// 메인 스탯
// 레벨업시 성장할 능력치들
class MainStat
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

enum class BattleClass
{
	Lord,		// 로드
	BladeLord,	// 블레이드 로드 *
	Cavalier,	// 소셜나이트
	Paladin,	// 팔라딘 * 
	PegasusKnight,// 페가수스 나이트
	Archer,		// 아쳐
	Fighter,	// 전사
	Warrior,	// 워리어 *
	Cleric,		// 시스터
	Bishop,		// 비숍 *
	Mage,		// 마도사
	Nomad,		// 유목민
	Thief,		// 도적
	Assassin,	// 어쌔신 *
	Dancer,		// 무희
	Monk,		// 승려
	Knight,		// 아머나이트
	Brigand,	// 산적
	Soldier,	// 군인
};

// 스탯 클래스
// 유닛이 지닐 스탯을 관리하는 클래스
class Stat
{
private:
	int Level;			// 레벨
	BattleClass ClassValue;
	MainStat MainStatValue;
	int Experience;				// 경험치
	int GrowthRates_HP;			// 체력 성장률
	int GrowthRates_Strength;	// 힘   성장률
	int GrowthRates_Magic;		// 마력 성장률
	int GrowthRates_Dexterity;	// 기술 성장률
	int GrowthRates_Speed;		// 속도 성장률
	int GrowthRates_Defense;	// 수비 성장률
	int GrowthRates_Resistance;	// 마방 성장률
	int GrowthRates_Luck;		// 행운 성장률

public:
	// 기초 스텟 지정
	void SetIdentity(int _IdentityCode);
	// 경험치 증가 (레벨업 시 true)
	bool AddExperience(int _Experience);
	// 레벨 업 (경험치 증가 후 직접 실행, 증가한 능력치를 반환)
	MainStat LevelUp();


private:
	void SetStat_Lyn();
	void SetStat_Sain();
	void SetStat_Kent();
	void SetStat_Fiora();
	void SetStat_Wil();
	void SetStat_Dorcas();
	void SetStat_Serra();
	void SetStat_Erk();
	void SetStat_Rath();
	void SetStat_Matthew();
	void SetStat_Ninian();
	void SetStat_Lucius();
	void SetStat_Wallace();
};