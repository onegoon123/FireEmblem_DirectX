#include "PrecompileHeader.h"
#include "UnitCommand.h"
#include "FERandom.h"
std::list<UnitCommand> UnitCommand::CommandList = std::list<UnitCommand>();

UnitCommand::UnitCommand() 
{
}

UnitCommand::~UnitCommand() 
{
}

std::list<AttackCommand> UnitCommand::Attack(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit)
{
	std::list<AttackCommand> AttackList;

	AttackCommand NewAttack;

	Unit SubjectUnit = _SubjectUnit->UnitData;
	Unit TargetUnit = _TargetUnit->UnitData;

	int UnitHit = SubjectUnit.UnitStat.GetHitPoint();
	int TargetDodge = TargetUnit.UnitStat.GetDodgePoint();
	int TerrainDodge = TargetUnit.TerrainDodge;

	int HitPercentage = UnitHit - (TargetDodge + TerrainDodge);
	int CriticalPercentage = SubjectUnit.UnitStat.GetCriticalPoint() - TargetUnit.UnitStat.GetCriticalDodgePoint();

	NewAttack.IsDodge = FERandom::RandomInt() < HitPercentage;
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;

	int Damage = (SubjectUnit.UnitStat.GetAttackPoint() * (NewAttack.IsCritical ? 3 : 1));

	if (true == NewAttack.IsDodge)
	{
		TargetUnit.CurrentHP = std::max<int>(0, TargetUnit.CurrentHP - Damage);
	}

	NewAttack.TargetUnit = TargetUnit;




	AttackList.push_back(NewAttack);

	

	return AttackList;
}
