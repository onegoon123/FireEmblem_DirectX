#include "PrecompileHeader.h"
#include "Stat.h"
#include "FERandom.h"

#include "Unit.h"
Stat::Stat()
{
	MaximumStat.HP = 60;
	MaximumStat.Strength = 20;
	MaximumStat.Magic = 20;
	MaximumStat.Dexterity = 20;
	MaximumStat.Speed = 20;
	MaximumStat.Luck = 30;
	MaximumStat.Defense = 20;
	MaximumStat.Resistance = 20;
	MaximumStat.Constitution = 20;
}
Stat::~Stat()
{
}
void Stat::SetIdentity(int _IdentityCode)
{
	SetIdentity(static_cast<UnitIdentityCode>(_IdentityCode));
}

void Stat::SetIdentity(UnitIdentityCode _IdentityCode)
{
	switch (_IdentityCode)
	{
	case UnitIdentityCode::Lyn:
	case UnitIdentityCode::BladeLordLyn:
		SetStat_Lyn();
		break;
	case UnitIdentityCode::Sain:
		SetStat_Sain();
		break;
	case UnitIdentityCode::Kent:
		SetStat_Kent();
		break;
	case UnitIdentityCode::Florina:
		SetStat_Florina();
		break;
	case UnitIdentityCode::Wil:
		SetStat_Wil();
		break;
	case UnitIdentityCode::Dorcas:
	case UnitIdentityCode::WarriorDorcas:
		SetStat_Dorcas();
		break;
	case UnitIdentityCode::Serra:
		SetStat_Serra();
		break;
	case UnitIdentityCode::Erk:
		SetStat_Erk();
		break;
	case UnitIdentityCode::Rath:
		SetStat_Rath();
		break;
	case UnitIdentityCode::Matthew:
		SetStat_Matthew();
		break;
	case UnitIdentityCode::AssassinMatthew:
		SetStat_Matthew();
		ClassChange_Assassin();
		break;
	case UnitIdentityCode::Ninian:
		SetStat_Ninian();
		break;
	case UnitIdentityCode::Lucius:
		SetStat_Lucius();
		break;
	case UnitIdentityCode::Wallace:
		SetStat_Wallace();
		break;
	case UnitIdentityCode::GeneralWallace:
		SetStat_Wallace();
		ClassChange_General();
		break;
	case UnitIdentityCode::Brigand:
		SetStat_Brigand();
		break;
	case UnitIdentityCode::Soldier:
		SetStat_Soldier();
		break;
	case UnitIdentityCode::Mercenary:
		SetStat_Mercenary();
		break;
	case UnitIdentityCode::Archer:
		SetStat_Archer();
		break;
	case UnitIdentityCode::Knight:
		SetStat_Knight();
		break;
	case UnitIdentityCode::Mage:
		SetStat_Mage();
		break;
	case UnitIdentityCode::Batta:
		SetStat_Batta();
		break;
	case UnitIdentityCode::Zugu:
		SetStat_Zugu();
		break;
	case UnitIdentityCode::Glass:
		SetStat_Glass();
		break;
	case UnitIdentityCode::Migal:
		SetStat_Migal();
		break;
	case UnitIdentityCode::Carjiga:
		SetStat_Carjiga();
		break;
	}

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
	Level++;

	// 성장률 확률만큼 레벨업시 스텟 성장
	MainStat UpValue;

	// 최대 수치만큼 찍은 스텟은 스킵
	if (MainStatValue.HP < MaximumStat.HP && FERandom::RandomInt() < GrowthRates_HP == true) { MainStatValue.HP++; UpValue.HP++; }
	if (MainStatValue.Strength < MaximumStat.Strength && FERandom::RandomInt() < GrowthRates_Strength == true) { MainStatValue.Strength++; UpValue.Strength++; }
	if (MainStatValue.Magic < MaximumStat.Magic && FERandom::RandomInt() < GrowthRates_Magic == true) { MainStatValue.Magic++; UpValue.Magic++; }
	if (MainStatValue.Dexterity < MaximumStat.Dexterity && FERandom::RandomInt() < GrowthRates_Dexterity == true) { MainStatValue.Dexterity++; UpValue.Dexterity++; }
	if (MainStatValue.Speed < MaximumStat.Speed && FERandom::RandomInt() < GrowthRates_Speed == true) { MainStatValue.Speed++; UpValue.Speed++; }
	if (MainStatValue.Luck < MaximumStat.Luck && FERandom::RandomInt() < GrowthRates_Luck == true) { MainStatValue.Luck++; UpValue.Luck++; }
	if (MainStatValue.Defense < MaximumStat.Defense && FERandom::RandomInt() < GrowthRates_Defense == true) { MainStatValue.Defense++; UpValue.Defense++; }
	if (MainStatValue.Resistance < MaximumStat.Resistance && FERandom::RandomInt() < GrowthRates_Resistance == true) { MainStatValue.Resistance++; UpValue.Resistance++; }

	return UpValue;
}

void Stat::SetStat_Lyn()
{
	Level = 1;
	MainStatValue.HP = 16;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 4;
	MainStatValue.Dexterity = 7;
	MainStatValue.Speed = 9;
	MainStatValue.Luck = 5;
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
	Level = 1;
	MainStatValue.HP = 19;
	MainStatValue.Strength = 8;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 4;
	MainStatValue.Speed = 6;
	MainStatValue.Luck = 4;
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
	// male cavalier
	Level = 1;
	MainStatValue.HP = 20;
	MainStatValue.Strength = 6;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 6;
	MainStatValue.Speed = 7;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 5;
	MainStatValue.Resistance = 1;
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


void Stat::SetStat_Florina()
{
	// Pegasus Knight
	Level = 1;
	MainStatValue.HP = 17;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 7;
	MainStatValue.Speed = 9;
	MainStatValue.Luck = 7;
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
	Level = 2;
	MainStatValue.HP = 20;
	MainStatValue.Strength = 6;
	MainStatValue.Magic = 5;
	MainStatValue.Dexterity = 5;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 6;
	MainStatValue.Defense = 5;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 6;
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
	Level = 3;
	MainStatValue.HP = 30;
	MainStatValue.Strength = 7;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 7;
	MainStatValue.Speed = 6;
	MainStatValue.Luck = 3;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 14;
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
	Level = 1;
	MainStatValue.HP = 17;
	MainStatValue.Strength = 2;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 5;
	MainStatValue.Speed = 8;
	MainStatValue.Luck = 6;
	MainStatValue.Defense = 2;
	MainStatValue.Resistance = 5;
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
	Level = 1;
	MainStatValue.HP = 17;
	MainStatValue.Strength = 2;
	MainStatValue.Magic = 5;
	MainStatValue.Dexterity = 6;
	MainStatValue.Speed = 7;
	MainStatValue.Luck = 3;
	MainStatValue.Defense = 2;
	MainStatValue.Resistance = 4;
	MainStatValue.Constitution = 5;
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
	Level = 7;
	MainStatValue.HP = 25;
	MainStatValue.Strength = 8;
	MainStatValue.Magic = 3;
	MainStatValue.Dexterity = 9;
	MainStatValue.Speed = 10;
	MainStatValue.Luck = 5;
	MainStatValue.Defense = 7;
	MainStatValue.Resistance = 2;
	MainStatValue.Constitution = 8;
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
	Level = 2;
	MainStatValue.HP = 18;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 4;
	MainStatValue.Speed = 11;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 7;
	ClassValue = BattleClass::Thief;
	Movement = 6;
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
	Level = 1;
	MainStatValue.HP = 14;
	MainStatValue.Strength = 0;
	MainStatValue.Magic = 0;
	MainStatValue.Dexterity = 0;
	MainStatValue.Speed = 12;
	MainStatValue.Luck = 10;
	MainStatValue.Defense = 5;
	MainStatValue.Resistance = 4;
	MainStatValue.Constitution = 3;
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
	Level = 3;
	MainStatValue.HP = 18;
	MainStatValue.Strength = 1;
	MainStatValue.Magic = 7;
	MainStatValue.Dexterity = 6;
	MainStatValue.Speed = 10;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 1;
	MainStatValue.Resistance = 6;
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
	Level = 12;
	MainStatValue.HP = 30;
	MainStatValue.Strength = 13;
	MainStatValue.Magic = 1;
	MainStatValue.Dexterity = 7;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 10;
	MainStatValue.Defense = 15;
	MainStatValue.Resistance = 2;
	MainStatValue.Constitution = 13;
	ClassValue = BattleClass::Knight;
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



MainStat Stat::ClassChange_BladeLord()
{
	MainStat UpStat;
	ClassValue = BattleClass::BladeLord;
	
	UpStat.HP = 3;
	UpStat.Strength = 2;
	UpStat.Magic = 1;
	UpStat.Dexterity = 2;
	UpStat.Defense = 3;
	UpStat.Resistance = 5;
	UpStat.Constitution = 1;
	MainStatValue += UpStat;
	Movement += 1;

	MaximumStat.Strength = 24;
	MaximumStat.Dexterity = 29;
	MaximumStat.Speed = 30;
	MaximumStat.Defense = 22;
	MaximumStat.Resistance = 22;
	MaximumStat.Constitution = 25;

	return UpStat;
}

MainStat Stat::ClassChange_Warrior()
{
	MainStat UpStat;
	ClassValue = BattleClass::Warrior;
	UpStat.HP = 3;
	UpStat.Strength = 1;
	UpStat.Dexterity = 2;
	UpStat.Defense = 3;
	UpStat.Resistance = 3;
	UpStat.Constitution = 2;
	MainStatValue += UpStat;

	Movement += 1;
	MaximumStat.Strength = 30;
	MaximumStat.Dexterity = 28;
	MaximumStat.Speed = 26;
	MaximumStat.Defense = 26;
	MaximumStat.Resistance = 22;

	return UpStat;
}

MainStat Stat::ClassChange_Assassin()
{
	MainStat UpStat;
	ClassValue = BattleClass::Assassin;
	UpStat.HP = 3;
	UpStat.Strength = 1;
	UpStat.Defense = 2;
	UpStat.Resistance = 2;
	MainStatValue += UpStat;

	MaximumStat.Dexterity = 30;
	MaximumStat.Speed = 30;

	return UpStat;
}

MainStat Stat::ClassChange_General()
{
	MainStat UpStat;
	ClassValue = BattleClass::General;
	UpStat.HP = 4;
	UpStat.Strength = 2;
	UpStat.Dexterity = 2;
	UpStat.Speed = 3;
	UpStat.Defense = 2;
	UpStat.Resistance = 3;
	UpStat.Constitution = 2;
	MainStatValue += UpStat;

	Movement += 1;

	MaximumStat.Strength = 29;
	MaximumStat.Dexterity = 27;
	MaximumStat.Speed = 24;
	MaximumStat.Defense = 30;
	MaximumStat.Resistance = 25;

	return UpStat;
}

void Stat::SetStat_Brigand()
{
	// Brigand
	Level = 1;
	MainStatValue.HP = 20;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 1;
	MainStatValue.Speed = 4;
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
	Level = 1;
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
	// Mercenary
	Level = 1;
	MainStatValue.HP = 18;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 8;
	MainStatValue.Speed = 8;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 4;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 9;
	ClassValue = BattleClass::Mercenary;
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

void Stat::SetStat_Archer()
{
	Level = 1;
	MainStatValue.HP = 18;
	MainStatValue.Strength = 4;
	MainStatValue.Magic = 3;
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

void Stat::SetStat_Knight()
{
	Level = 1;
	MainStatValue.HP = 23;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 2;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 10;
	MainStatValue.Resistance = 2;
	MainStatValue.Constitution = 7;
	ClassValue = BattleClass::Knight;
	Movement = 4;
	GrowthRates_HP = 70;
	GrowthRates_Strength = 35;
	GrowthRates_Magic = 25;
	GrowthRates_Dexterity = 40;
	GrowthRates_Speed = 32;
	GrowthRates_Luck = 35;
	GrowthRates_Defense = 35;
	GrowthRates_Resistance = 15;
}

void Stat::SetStat_Mage()
{
	// Mage
	Level = 1;
	MainStatValue.HP = 17;
	MainStatValue.Strength = 2;
	MainStatValue.Magic = 5;
	MainStatValue.Dexterity = 4;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 3;
	MainStatValue.Defense = 1;
	MainStatValue.Resistance = 4;
	MainStatValue.Constitution = 5;
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

void Stat::SetStat_Batta()
{
	Level = 2;
	MainStatValue.HP = 21;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 1;
	MainStatValue.Speed = 3;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 10;
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

void Stat::SetStat_Zugu()
{
	Level = 4;
	MainStatValue.HP = 23;
	MainStatValue.Strength = 6;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 2;
	MainStatValue.Speed = 4;
	MainStatValue.Luck = 1;
	MainStatValue.Defense = 4;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 11;
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

void Stat::SetStat_Glass()
{
	Level = 3;
	MainStatValue.HP = 20;
	MainStatValue.Strength = 5;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 4;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 0;
	MainStatValue.Defense = 3;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 9;
	ClassValue = BattleClass::Mercenary;
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

void Stat::SetStat_Migal()
{
	Level = 6;
	MainStatValue.HP = 25;
	MainStatValue.Strength = 7;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 3;
	MainStatValue.Speed = 5;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 5;
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

void Stat::SetStat_Carjiga()
{
	Level = 8;
	MainStatValue.HP = 27;
	MainStatValue.Strength = 6;
	MainStatValue.Magic = 2;
	MainStatValue.Dexterity = 5;
	MainStatValue.Speed = 4;
	MainStatValue.Luck = 2;
	MainStatValue.Defense = 7;
	MainStatValue.Resistance = 0;
	MainStatValue.Constitution = 15;
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

int MainStat::GetAttackStat(WeaponType _Value) const
{
	switch (_Value)
	{
	case WeaponType::None:
	case WeaponType::Sword:
	case WeaponType::LanceReaver:
	case WeaponType::Lance:
	case WeaponType::AxeReaver:
	case WeaponType::Axe:
	case WeaponType::SwordReaver:
	case WeaponType::Bow:
		return Strength;
	case WeaponType::AnimaTome:
	case WeaponType::DarkTome:
	case WeaponType::LightTome:
		return Magic;
	default:
		return Strength;
	}
}
