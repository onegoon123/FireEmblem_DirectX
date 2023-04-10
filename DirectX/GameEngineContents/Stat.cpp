#include "PrecompileHeader.h"
#include "Stat.h"
#include "FERandom.h"
void Stat::SetIdentity(int _IdentityCode)
{
}

const int NeedExperience = 100;		// 레벨업시 필요한 경험치
bool Stat::AddExperience(int _Experience)
{
	Experience += _Experience;

	// 경험치가 100을 넘기면
	if (NeedExperience <= Experience)
	{
		Experience -= NeedExperience;
		return true;	// 레벨업 필요 시 true를 리턴.
	}

	return false;
}

MainStat Stat::LevelUp()
{
	// 성장률 확률만큼 레벨업시 스텟 성장
	MainStat UpValue;
	if (FERandom::RandomInt() < GrowthRates_HP == true) { MainStatValue.HP++; UpValue.HP++; }
	if (FERandom::RandomInt() < GrowthRates_Strength == true) { MainStatValue.Strength++; UpValue.Strength++; }
	if (FERandom::RandomInt() < GrowthRates_Magic == true) { MainStatValue.Magic++; UpValue.Magic++; }
	if (FERandom::RandomInt() < GrowthRates_Dexterity == true) { MainStatValue.Dexterity++; UpValue.Dexterity++; }
	if (FERandom::RandomInt() < GrowthRates_Speed == true) { MainStatValue.Speed++; UpValue.Speed++; }
	if (FERandom::RandomInt() < GrowthRates_Luck == true) { MainStatValue.Luck++; UpValue.Luck++; }
	if (FERandom::RandomInt() < GrowthRates_Defense == true) { MainStatValue.Defense++; UpValue.Defense++; }
	if (FERandom::RandomInt() < GrowthRates_Resistance == true) { MainStatValue.Resistance++; UpValue.Resistance++; }

	return UpValue;
}

void Stat::SetStat_Lord()
{
	MainStatValue.HP = 16;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 4;
	MainStatValue.Dexterity = 7;
	MainStatValue.Speed = 9;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 2;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 5;
	ClassValue = BattleClass::Lord;
	Movement = 5;
	GrowthRates_HP = 90;
	GrowthRates_Strength = 45;
	GrowthRates_Magic = 45;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 45;
	GrowthRates_Luck = 40;
	GrowthRates_Defense = 15;
	GrowthRates_Resistance = 20;
}

void Stat::SetStat_BladeLord()
{
}

void Stat::SetStat_Cavalier()
{
	// male cavalier
	MainStatValue.HP = 20;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 6;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 9;
	ClassValue = BattleClass::Cavalier;
	Movement = 7;
	GrowthRates_HP = 75;
	GrowthRates_Strength = 35;
	GrowthRates_Magic = 25;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 28;
	GrowthRates_Luck = 30;
	GrowthRates_Defense = 15;
	GrowthRates_Resistance = 15;
}


void Stat::SetStat_PegasusKnight()
{
	// Pegasus Knight
	MainStatValue.HP = 14;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 5;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 2;
	MainStatValue.Constitution = 5;
	ClassValue = BattleClass::PegasusKnight;
	Movement = 7;
	GrowthRates_HP = 65;
	GrowthRates_Strength = 35;
	GrowthRates_Magic = 35;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 40;
	GrowthRates_Luck = 35;
	GrowthRates_Defense = 12;
	GrowthRates_Resistance = 35;
}

void Stat::SetStat_Archer()
{
	// Archer
	MainStatValue.HP = 18;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 4;
	MainStatValue.Dexterity = 3;
	MainStatValue.Speed = 3;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 7;
	ClassValue = BattleClass::Archer;
	Movement = 5;
	GrowthRates_HP = 70;
	GrowthRates_Strength = 35;
	GrowthRates_Magic = 25;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 32;
	GrowthRates_Luck = 35;
	GrowthRates_Defense = 15;
	GrowthRates_Resistance = 15;
}

void Stat::SetStat_Fighter()
{
	// Fighter
	MainStatValue.HP = 20;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 4;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 2;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 11;
	ClassValue = BattleClass::Fighter;
	Movement = 5;
	GrowthRates_HP = 85;
	GrowthRates_Strength = 55;
	GrowthRates_Magic = 25;
	GrowthRates_Dexterity = 30;
	GrowthRates_Speed = 30;
	GrowthRates_Luck = 15;
	GrowthRates_Defense = 15;
	GrowthRates_Resistance = 15;
}

void Stat::SetStat_Warrior()
{
}

void Stat::SetStat_Cleric()
{
	// Cleric
	MainStatValue.HP = 16;
	MainStatValue.Strength = 1;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 2;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 0;
	MainStatValue.Resistance = 6;
	MainStatValue.Constitution = 4;
	ClassValue = BattleClass::Cleric;
	Movement = 5;
	GrowthRates_HP = 50;
	GrowthRates_Strength = 10;
	GrowthRates_Magic = 30;
	GrowthRates_Dexterity = 35;
	GrowthRates_Speed = 32;
	GrowthRates_Luck = 45;
	GrowthRates_Defense = 8;
	GrowthRates_Resistance = 50;
}

void Stat::SetStat_Mage()
{
	// Mage
	MainStatValue.HP = 16;
	MainStatValue.Strength = 1;
	MainStatValue.Magic = 4;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 3;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 3;
	MainStatValue.Constitution = 6;
	ClassValue = BattleClass::Mage;
	Movement = 5;
	GrowthRates_HP = 55;
	GrowthRates_Strength = 10;
	GrowthRates_Magic = 55;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 35;
	GrowthRates_Luck = 20;
	GrowthRates_Defense = 5;
	GrowthRates_Resistance = 30;
}

void Stat::SetStat_Nomad()
{
	// Nomad
	MainStatValue.HP = 16;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 4;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 4;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 7;
	ClassValue = BattleClass::Nomad;
	Movement = 7;
	GrowthRates_HP = 65;
	GrowthRates_Strength = 30;
	GrowthRates_Magic = 20;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 45;
	GrowthRates_Luck = 30;
	GrowthRates_Defense = 12;
	GrowthRates_Resistance = 15;
}

void Stat::SetStat_Thief()
{
	// Thief
	MainStatValue.HP = 16;
	MainStatValue.Strength = 3;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 1;
	MainStatValue.Speed = 9;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 2;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 6;
	ClassValue = BattleClass::Thief;
	Movement = 5;
	GrowthRates_HP = 50;
	GrowthRates_Strength = 5;
	GrowthRates_Magic = 5;
	GrowthRates_Dexterity = 45;
	GrowthRates_Speed = 40;
	GrowthRates_Luck = 40;
	GrowthRates_Defense = 5;
	GrowthRates_Resistance = 20;
}

void Stat::SetStat_Assassin()
{
}

void Stat::SetStat_Dancer()
{
	// Dancer
	MainStatValue.HP = 14;
	MainStatValue.Strength = 1;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 7;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 0;
	MainStatValue.Resistance = 1;
	MainStatValue.Constitution = 4;
	ClassValue = BattleClass::Dancer;
	Movement = 5;
	GrowthRates_HP = 45;
	GrowthRates_Strength = 45;
	GrowthRates_Magic = 45;
	GrowthRates_Dexterity = 30;
	GrowthRates_Speed = 60;
	GrowthRates_Luck = 70;
	GrowthRates_Defense = 0;
	GrowthRates_Resistance = 13;
}

void Stat::SetStat_Monk()
{
	// Dancer
	MainStatValue.HP = 18;
	MainStatValue.Strength = 1;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 1;
	MainStatValue.Speed = 2;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 1;
	MainStatValue.Resistance = 5;
	MainStatValue.Constitution = 6;
	ClassValue = BattleClass::Monk;
	Movement = 5;
	GrowthRates_HP = 50;
	GrowthRates_Strength = 30;
	GrowthRates_Magic = 30;
	GrowthRates_Dexterity = 35;
	GrowthRates_Speed = 32;
	GrowthRates_Luck = 45;
	GrowthRates_Defense = 8;
	GrowthRates_Resistance = 40;
}

void Stat::SetStat_Knight()
{
	// Knight
	MainStatValue.HP = 17;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 0;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 9;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 13;
	ClassValue = BattleClass::Monk;
	Movement = 4;
	GrowthRates_HP = 80;
	GrowthRates_Strength = 40;
	GrowthRates_Magic = 30;
	GrowthRates_Dexterity = 30;
	GrowthRates_Speed = 15;
	GrowthRates_Luck = 25;
	GrowthRates_Defense = 28;
	GrowthRates_Resistance = 20;
}

void Stat::SetStat_General()
{
}

void Stat::SetStat_Brigand()
{
	// Brigand
	MainStatValue.HP = 20;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 1;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 12;
	ClassValue = BattleClass::Brigand;
	Movement = 5;
	GrowthRates_HP = 82;
	GrowthRates_Strength = 50;
	GrowthRates_Magic = 40;
	GrowthRates_Dexterity = 30;
	GrowthRates_Speed = 20;
	GrowthRates_Luck = 15;
	GrowthRates_Defense = 10;
	GrowthRates_Resistance = 13;
}

void Stat::SetStat_Soldier()
{
	// Soldier
	MainStatValue.HP = 20;
	MainStatValue.Strength = 3;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 0;
	MainStatValue.Speed = 1;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 0;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 6;
	ClassValue = BattleClass::Soldier;
	Movement = 5;
	GrowthRates_HP = 80;
	GrowthRates_Strength = 50;
	GrowthRates_Magic = 40;
	GrowthRates_Dexterity = 30;
	GrowthRates_Speed = 20;
	GrowthRates_Luck = 25;
	GrowthRates_Defense = 12;
	GrowthRates_Resistance = 15;
}

void Stat::SetStat_Mercenary()
{
}
