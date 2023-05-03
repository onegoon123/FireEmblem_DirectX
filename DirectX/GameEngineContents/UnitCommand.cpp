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
	UnitCommand CommandRecord;
	Unit SubjectUnit = Unit(_SubjectUnit->GetUnitData());
	Unit TargetUnit = Unit(_TargetUnit->GetUnitData());

	CommandRecord.TypeValue = CommandType::Attack;
	CommandRecord.BeforeSubjectUnit = Unit(SubjectUnit);
	CommandRecord.BeforeTargetUnit = Unit(TargetUnit);
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();

	{
		AttackCommand NewAttack;
		int UnitHit = SubjectUnit.UnitStat.GetHitPoint();
		int TargetDodge = TargetUnit.UnitStat.GetDodgePoint();
		int TerrainDodge = TargetUnit.TerrainDodge;

		int HitPercentage = UnitHit - (TargetDodge + TerrainDodge);
		int CriticalPercentage = SubjectUnit.UnitStat.GetCriticalPoint() - TargetUnit.UnitStat.GetCriticalDodgePoint();

		NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
		NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;
		CommandRecord.RandomNum += 2;

		int Damage = (SubjectUnit.UnitStat.GetAttackPoint() * (NewAttack.IsCritical ? 3 : 1));
		Damage = std::max<int>(1, Damage - TargetUnit.UnitStat.MainStatValue.Defense);

		if (true == NewAttack.IsHit)
		{
			TargetUnit.CurrentHP = std::max<int>(0, TargetUnit.CurrentHP - Damage);
			SubjectUnit.UnitStat.EquipWeapon->Uses--;

			if (0 == TargetUnit.CurrentHP)
			{
				TargetUnit.IsDie = true;
			}
		}
		
		NewAttack.TargetUnit = TargetUnit;
		NewAttack.SubjectUnit = SubjectUnit;

		AttackList.push_back(NewAttack);

		//MessageBoxA(nullptr, SubjectUnit.ToString().c_str(), (std::string(_SubjectUnit->GetName()) + "(이)가 공격").c_str(), MB_OK);
		//MessageBoxA(nullptr, TargetUnit.ToString().c_str(), (std::string(_TargetUnit->GetName()) + "(이)가 대미지").c_str(), MB_OK);
	}

	if (true == TargetUnit.IsDie)
	{
		CommandRecord.AfterSubjectUnit = SubjectUnit;
		CommandRecord.AfterTargetUnit = TargetUnit;
		CommandList.push_back(CommandRecord);
		return AttackList;
	}

	{
		AttackCommand NewAttack;
		int UnitHit = TargetUnit.UnitStat.GetHitPoint();
		int TargetDodge = SubjectUnit.UnitStat.GetDodgePoint();
		int TerrainDodge = SubjectUnit.TerrainDodge;

		int HitPercentage = UnitHit - (TargetDodge + TerrainDodge);
		int CriticalPercentage = TargetUnit.UnitStat.GetCriticalPoint() - SubjectUnit.UnitStat.GetCriticalDodgePoint();

		NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
		NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;
		CommandRecord.RandomNum += 2;

		int Damage = (TargetUnit.UnitStat.GetAttackPoint() * (NewAttack.IsCritical ? 3 : 1));
		Damage = std::max<int>(1, Damage - SubjectUnit.UnitStat.MainStatValue.Defense);
		if (true == NewAttack.IsHit)
		{
			SubjectUnit.CurrentHP = std::max<int>(0, SubjectUnit.CurrentHP - Damage);
			TargetUnit.UnitStat.EquipWeapon->Uses--;
			if (0 == SubjectUnit.CurrentHP)
			{
				SubjectUnit.IsDie = true;
			}
		}

		NewAttack.TargetUnit = TargetUnit;
		NewAttack.SubjectUnit = SubjectUnit;
		AttackList.push_back(NewAttack);
		//MessageBoxA(nullptr, TargetUnit.ToString().c_str(), (std::string(_TargetUnit->GetName()) + "(이)가 공격").c_str(), MB_OK);
		//MessageBoxA(nullptr, SubjectUnit.ToString().c_str(), (std::string(_SubjectUnit->GetName()) + "(이)가 대미지").c_str(), MB_OK);
	}

	if (true == SubjectUnit.IsDie)
	{
		CommandRecord.AfterSubjectUnit = SubjectUnit;
		CommandRecord.AfterTargetUnit = TargetUnit;
		CommandList.push_back(CommandRecord);
		return AttackList;
	}

	if (TargetUnit.UnitStat.GetAttackSpeedPoint() + 4 <= SubjectUnit.UnitStat.GetAttackSpeedPoint())
	{
		AttackCommand NewAttack;
		int UnitHit = SubjectUnit.UnitStat.GetHitPoint();
		int TargetDodge = TargetUnit.UnitStat.GetDodgePoint();
		int TerrainDodge = TargetUnit.TerrainDodge;

		int HitPercentage = UnitHit - (TargetDodge + TerrainDodge);
		int CriticalPercentage = SubjectUnit.UnitStat.GetCriticalPoint() - TargetUnit.UnitStat.GetCriticalDodgePoint();

		NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
		NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;
		CommandRecord.RandomNum += 2;

		int Damage = (SubjectUnit.UnitStat.GetAttackPoint() * (NewAttack.IsCritical ? 3 : 1));
		Damage = std::max<int>(1, Damage - TargetUnit.UnitStat.MainStatValue.Defense);

		if (true == NewAttack.IsHit)
		{
			TargetUnit.CurrentHP = std::max<int>(0, TargetUnit.CurrentHP - Damage);
			SubjectUnit.UnitStat.EquipWeapon->Uses--;
			if (0 == TargetUnit.CurrentHP)
			{
				TargetUnit.IsDie = true;
			}
		}

		NewAttack.TargetUnit = TargetUnit;
		NewAttack.SubjectUnit = SubjectUnit;
		AttackList.push_back(NewAttack);
		//MessageBoxA(nullptr, SubjectUnit.ToString().c_str(), (std::string(_SubjectUnit->GetName()) + "(이)가 공격").c_str(), MB_OK);
		//MessageBoxA(nullptr, TargetUnit.ToString().c_str(), (std::string(_TargetUnit->GetName()) + "(이)가 대미지").c_str(), MB_OK);
	}
	else if (SubjectUnit.UnitStat.GetAttackSpeedPoint() + 4 <= TargetUnit.UnitStat.GetAttackSpeedPoint())
	{
		AttackCommand NewAttack;
		int UnitHit = TargetUnit.UnitStat.GetHitPoint();
		int TargetDodge = SubjectUnit.UnitStat.GetDodgePoint();
		int TerrainDodge = SubjectUnit.TerrainDodge;

		int HitPercentage = UnitHit - (TargetDodge + TerrainDodge);
		int CriticalPercentage = TargetUnit.UnitStat.GetCriticalPoint() - SubjectUnit.UnitStat.GetCriticalDodgePoint();

		NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
		NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;
		CommandRecord.RandomNum += 2;

		int Damage = (TargetUnit.UnitStat.GetAttackPoint() * (NewAttack.IsCritical ? 3 : 1));
		Damage = std::max<int>(1, Damage - SubjectUnit.UnitStat.MainStatValue.Defense);

		if (true == NewAttack.IsHit)
		{
			SubjectUnit.CurrentHP = std::max<int>(0, SubjectUnit.CurrentHP - Damage);
			TargetUnit.UnitStat.EquipWeapon->Uses--;
			if (0 == SubjectUnit.CurrentHP)
			{
				SubjectUnit.IsDie = true;
			}
		}

		NewAttack.TargetUnit = TargetUnit;
		NewAttack.SubjectUnit = SubjectUnit;
		AttackList.push_back(NewAttack);
		//MessageBoxA(nullptr, TargetUnit.ToString().c_str(), (std::string(_TargetUnit->GetName()) + "(이)가 공격").c_str(), MB_OK);
		//MessageBoxA(nullptr, SubjectUnit.ToString().c_str(), (std::string(_SubjectUnit->GetName()) + "(이)가 대미지").c_str(), MB_OK);
	}

	CommandRecord.AfterSubjectUnit = SubjectUnit;
	CommandRecord.AfterTargetUnit = TargetUnit;
	CommandRecord.Record = std::string(_TargetUnit->GetName()) + "에게 " + std::to_string(CommandRecord.BeforeTargetUnit.CurrentHP - CommandRecord.AfterTargetUnit.CurrentHP) + "의 대미지";
	CommandList.push_back(CommandRecord);
	return AttackList;
}

void UnitCommand::Wait(std::shared_ptr<BattleUnit> _SubjectUnit)
{
	UnitCommand CommandRecord;
	CommandRecord.TypeValue = CommandType::Wait;
	CommandRecord.BeforeSubjectUnit = Unit(_SubjectUnit->GetUnitData());
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();

	CommandList.push_back(CommandRecord);
}
