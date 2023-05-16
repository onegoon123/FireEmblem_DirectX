#include "PrecompileHeader.h"
#include "Unit.h"



int Unit::GetAttackPoint() const
{
	if (nullptr != CurWeapon)
	{
		int Result = UnitStat.MainStatValue.Strength + CurWeapon->GetDamage();
		return Result;
	}
	return 0;
}

int Unit::GetAttackPoint(BattleClass _TargetClass) const
{
	if (nullptr == CurWeapon)
	{
		return GetAttackPoint();
	}
	// 중갑 특효
	if (true == CurWeapon->GetValidArmour())
	{
		switch (_TargetClass)
		{
		case BattleClass::Knight:
		case BattleClass::General:
			return UnitStat.MainStatValue.Strength + CurWeapon->GetDamage() * 3;
		default:
			break;
		}
	}
	// 기마 특효
	if (true == CurWeapon->GetValidHorse())
	{
		switch (_TargetClass)
		{
		case BattleClass::Cavalier:
		case BattleClass::Nomad:
			return UnitStat.MainStatValue.Strength + CurWeapon->GetDamage() * 3;
		default:
			break;
		}
	}
	// 활 (공중 특효)
	if (WeaponType::Bow == CurWeapon->GetWeaponTypeValue())
	{
		switch (_TargetClass)
		{
		case BattleClass::PegasusKnight:
			return UnitStat.MainStatValue.Strength + CurWeapon->GetDamage() * 3;
		default:
			break;
		}
	}
	return GetAttackPoint();
}

int Unit::GetAttackPoint(const Unit& _Other) const
{
	int Result = GetAttackPoint(_Other.UnitStat.ClassValue);
	Result -= _Other.UnitStat.MainStatValue.Defense;
	Result -= _Other.TerrainDeffence;

	int Triangle;
	Triangle = Weapon::GetWeaponeTriangle(CurWeapon, _Other.CurWeapon);
	Result += Triangle;

	if (0 >= Result) { return 0; }
	return Result;
}

int Unit::GetDefPoint() const
{
	return UnitStat.MainStatValue.Defense + TerrainDeffence;
}

int Unit::GetMagicAttackPoint() const
{
	int Result = UnitStat.MainStatValue.Magic + CurWeapon->GetDamage();
	return Result;
}

int Unit::GetHitPoint() const
{
	if (nullptr != CurWeapon)
	{
		int Result = (UnitStat.MainStatValue.Dexterity * 2) + (UnitStat.MainStatValue.Luck / 2) + CurWeapon->GetHit();
		return Result;
	}
	return 0;
}

int Unit::GetHitPoint(const Unit& _Other) const
{
	int Result = GetHitPoint();
	Result -= _Other.GetDodgePoint();
	Result -= _Other.TerrainDodge;

	int Triangle;
	Triangle = Weapon::GetWeaponeTriangle(CurWeapon, _Other.CurWeapon);
	Result += Triangle * 15;

	if (0 >= Result) { return 0; }
	if (100 <= Result) { return 100; }
	return Result;
}

int Unit::GetCriticalPoint() const
{
	if (nullptr != CurWeapon)
	{
		int Result = UnitStat.MainStatValue.Dexterity / 2 + CurWeapon->GetCritical();
		return Result;
	}
	return 0;
}

int Unit::GetCriticalPoint(const Unit& _Other) const
{
	int Result = GetCriticalPoint();
	Result -= _Other.GetCriticalDodgePoint();

	if (0 >= Result) { return 0; }
	if (100 <= Result) { return 100; }
	return Result;
}

int Unit::GetAttackSpeedPoint() const
{
	int Result;
	if (nullptr != CurWeapon)
	{
		Result = UnitStat.MainStatValue.Speed - std::max<int>(0, CurWeapon->GetWeight() - UnitStat.MainStatValue.Constitution);
	}
	else
	{
		Result = UnitStat.MainStatValue.Speed;
	}
	return Result;
}

int Unit::GetDodgePoint() const
{
	int Result = 2 * GetAttackSpeedPoint() + UnitStat.MainStatValue.Luck / 2;
	Result += TerrainDodge;
	return Result;
}

int Unit::GetCriticalDodgePoint() const
{
	return UnitStat.MainStatValue.Luck;
}

bool Unit::IsDoubleAttack(const Unit& _Other) const
{
	return _Other.GetAttackSpeedPoint() + 4 <= GetAttackSpeedPoint();
}
