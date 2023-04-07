#include "Unit.h"

void Stat::SetIdentity(int _IdentityCode)
{
}

bool Stat::AddExperience(int _Experience)
{
	return false;
}

MainStat Stat::LevelUp()
{
	return MainStat();
}

void Stat::SetStat_Lyn()
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

void Stat::SetStat_Sain()
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

void Stat::SetStat_Kent()
{
}

void Stat::SetStat_Fiora()
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

void Stat::SetStat_Wil()
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

void Stat::SetStat_Dorcas()
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

void Stat::SetStat_Serra()
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

void Stat::SetStat_Erk()
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

void Stat::SetStat_Rath()
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

void Stat::SetStat_Matthew()
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

void Stat::SetStat_Ninian()
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

void Stat::SetStat_Lucius()
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

void Stat::SetStat_Wallace()
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
