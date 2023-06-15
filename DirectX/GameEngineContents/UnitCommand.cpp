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
	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "이(가) 공격했다.";

	CommandRecord.BeforeSubjectItems = Item::SaveItemDataList(SubjectUnit.GetItems());
	CommandRecord.BeforeTargetItems = Item::SaveItemDataList(TargetUnit.GetItems());

	if (nullptr != SubjectUnit.GetCurWeapon() && SubjectUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
	{
		AttackCommand NewAttack = AttackCalculation(SubjectUnit, TargetUnit);
		NewAttack.SubjectAttack = true;
		AttackList.push_back(NewAttack);
		CommandRecord.RandomNum += 2;

		if (true == TargetUnit.GetIsDie())
		{
			return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
		}
	}

	if (nullptr != TargetUnit.GetCurWeapon() && TargetUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
	{
		AttackCommand NewAttack = AttackCalculation(TargetUnit, SubjectUnit);
		NewAttack.ChangeOrder();
		AttackList.push_back(NewAttack);
		CommandRecord.RandomNum += 2;

		if (true == SubjectUnit.GetIsDie())
		{
			return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
		}
	}


	if (TargetUnit.GetAttackSpeedPoint() + 4 <= SubjectUnit.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.GetCurWeapon() && SubjectUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
		{
			AttackCommand NewAttack = AttackCalculation(SubjectUnit, TargetUnit);
			NewAttack.SubjectAttack = true;
			AttackList.push_back(NewAttack);
			CommandRecord.RandomNum += 2;
		}
	}
	else if (SubjectUnit.GetAttackSpeedPoint() + 4 <= TargetUnit.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.GetCurWeapon() && TargetUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
		{
			AttackCommand NewAttack = AttackCalculation(TargetUnit, SubjectUnit);
			NewAttack.ChangeOrder();
			AttackList.push_back(NewAttack);
			CommandRecord.RandomNum += 2;
		}
	}

	return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
}

AttackCommand UnitCommand::AttackSimulation(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit)
{
	Unit SubjectUnit = Unit(_SubjectUnit->GetUnitData());
	Unit TargetUnit = Unit(_TargetUnit->GetUnitData());
	AttackCommand NewAttack;

	if (nullptr != SubjectUnit.GetCurWeapon())
	{
		NewAttack = AttackCalculationNoRandom(SubjectUnit, TargetUnit);

		if (true == TargetUnit.GetIsDie())
		{
			return NewAttack;
		}
	}

	if (nullptr != TargetUnit.GetCurWeapon())
	{
		NewAttack = AttackCalculationNoRandom(TargetUnit, SubjectUnit);
		NewAttack.ChangeOrder();

		if (true == SubjectUnit.GetIsDie())
		{
			return NewAttack;
		}
	}


	if (TargetUnit.GetAttackSpeedPoint() + 4 <= SubjectUnit.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.GetCurWeapon())
		{
			NewAttack = AttackCalculationNoRandom(SubjectUnit, TargetUnit);
			NewAttack.SubjectAttack = true;
			return NewAttack;
		}
	}
	else if (SubjectUnit.GetAttackSpeedPoint() + 4 <= TargetUnit.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.GetCurWeapon())
		{
			NewAttack = AttackCalculationNoRandom(TargetUnit, SubjectUnit);
			NewAttack.ChangeOrder();
			return NewAttack;
		}
	}

	return NewAttack;
}

AttackCommand UnitCommand::AttackCalculation(Unit& _SubjectUnit, Unit& _TargetUnit)
{

	AttackCommand NewAttack;

	int HitPercentage = _SubjectUnit.GetHitPoint(_TargetUnit);
	int CriticalPercentage = _SubjectUnit.GetCriticalPoint(_TargetUnit);

	NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage && NewAttack.IsHit;

	// 공격력 계산
	NewAttack.Damage = _SubjectUnit.GetAttackPoint(_TargetUnit);	// 대미지 계산
	NewAttack.Damage *= NewAttack.IsCritical ? 3 : 1;	// 치명타 시 3배로 적용

	// 대미지가 0이하 일때
	if (0 >= NewAttack.Damage)
	{
		// No Damage
		NewAttack.Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.Damage(NewAttack.Damage);
		_SubjectUnit.GetCurWeapon()->Use();
	}

	NewAttack.TargetUnit = _TargetUnit;
	NewAttack.SubjectUnit = _SubjectUnit;

	return NewAttack;
}

AttackCommand UnitCommand::AttackCalculationNoRandom(Unit& _SubjectUnit, Unit& _TargetUnit)
{
	AttackCommand NewAttack;

	int HitPercentage = _SubjectUnit.GetHitPoint(_TargetUnit);
	int CriticalPercentage = _SubjectUnit.GetCriticalPoint(_TargetUnit);

	NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage && NewAttack.IsHit;

	// 공격력 계산
	NewAttack.Damage = _SubjectUnit.GetAttackPoint(_TargetUnit);	// 대미지 계산
	NewAttack.Damage *= NewAttack.IsCritical ? 3 : 1;	// 치명타 시 3배로 적용

	NewAttack.IsHit = 0 < HitPercentage;
	NewAttack.IsCritical = 50 < CriticalPercentage && NewAttack.IsHit;

	// 공격력 계산
	NewAttack.Damage = _SubjectUnit.GetAttackPoint(_TargetUnit);	// 상성에 따른 대미지 적용
	NewAttack.Damage *= NewAttack.IsCritical ? 3 : 1;	// 치명타 시 3배로 적용

	// 대미지가 0이하 일때
	if (0 >= NewAttack.Damage)
	{
		// No Damage
		NewAttack.Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.Damage(NewAttack.Damage);
	}

	NewAttack.TargetUnit = _TargetUnit;
	NewAttack.SubjectUnit = _SubjectUnit;

	return NewAttack;
}

void UnitCommand::Wait(std::shared_ptr<BattleUnit> _SubjectUnit)
{
	UnitCommand CommandRecord;
	CommandRecord.TypeValue = CommandType::Wait;
	CommandRecord.BeforeSubjectUnit = Unit(_SubjectUnit->GetUnitData());
	CommandRecord.AfterSubjectUnit = CommandRecord.BeforeSubjectUnit;
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();
	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "이(가) 대기했다";
	CommandList.push_back(CommandRecord);
}

void UnitCommand::ItemUse(std::shared_ptr<BattleUnit> _SubjectUnit, std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	UnitCommand CommandRecord;
	CommandRecord.TypeValue = CommandType::Item;
	CommandRecord.BeforeSubjectUnit = Unit(_SubjectUnit->GetUnitData());
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.BeforeSubjectItems = Item::SaveItemDataList(CommandRecord.BeforeSubjectUnit.GetItems());

	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "이(가) " + std::string((*_ItemIter)->GetName()) + "를(을) 사용했다.";
	_SubjectUnit->GetUnitData().UseItem(_ItemIter);

	CommandRecord.AfterSubjectItems = Item::SaveItemDataList(_SubjectUnit->GetUnitData().GetItems());
	CommandRecord.AfterSubjectUnit = CommandRecord.BeforeSubjectUnit;
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	CommandList.push_back(CommandRecord);
}

std::list<AttackCommand> UnitCommand::Heal(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
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
	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "이(가) " + std::string((*_ItemIter)->GetName()) + "을(를) 사용";

	CommandRecord.BeforeSubjectItems = Item::SaveItemDataList(SubjectUnit.GetItems());
	CommandRecord.BeforeTargetItems = Item::SaveItemDataList(TargetUnit.GetItems());

	_SubjectUnit->GetUnitData().UseItem(_ItemIter);
	TargetUnit.Recover(10 + SubjectUnit.GetMainStat().Magic);
	SubjectUnit.SetIsTurnEnd(true);

	AttackCommand NewAttackCommand;
	NewAttackCommand.SubjectAttack = true;
	NewAttackCommand.SubjectUnit = SubjectUnit;
	NewAttackCommand.TargetUnit = TargetUnit;
	NewAttackCommand.IsHit = true;
	NewAttackCommand.Exp = 20;
	AttackList.push_back(NewAttackCommand);

	CommandRecord.AfterSubjectItems = Item::SaveItemDataList(_SubjectUnit->GetUnitData().GetItems());
	CommandRecord.AfterSubjectUnit = CommandRecord.BeforeSubjectUnit;
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);

	CommandRecord.AfterTargetItems = Item::SaveItemDataList(TargetUnit.GetItems());
	CommandRecord.AfterTargetUnit = CommandRecord.BeforeSubjectUnit;
	
	CommandList.push_back(CommandRecord);
	return AttackList;
}

void UnitCommand::PhaseStart(Faction _Faction)
{
	UnitCommand CommandRecord;
	switch (_Faction)
	{
	case Faction::None:
	{
		MsgAssert("Faction을 지정하지 않았습니다.");
		break;
	}
	case Faction::Player:
		CommandRecord.TypeValue = CommandType::PlayerPhaseStart;
		CommandRecord.Record = "PLAYER PHASE 개시";
		break;
	case Faction::Enemy:
		CommandRecord.TypeValue = CommandType::EnemyPhaseStart;
		CommandRecord.Record = "ENEMY PHASE 개시";
		break;
	default:
		break;
	}
	CommandList.push_back(CommandRecord);
}

std::list<AttackCommand>& UnitCommand::AttackEnd(std::list<AttackCommand>& _AttackList, UnitCommand& _CommandRecord, Unit& _SubjectUnit, Unit& _TargetUnit)
{
	_CommandRecord.AfterSubjectUnit = _SubjectUnit;
	_CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	_CommandRecord.AfterTargetUnit = _TargetUnit;
	_CommandRecord.AfterSubjectItems = Item::SaveItemDataList(_SubjectUnit.GetItems());
	_CommandRecord.AfterTargetItems = Item::SaveItemDataList(_TargetUnit.GetItems());
	CommandList.push_back(_CommandRecord);

	// 경험치 계산
	int SumDamage = 0;
	for (AttackCommand _Attack : _AttackList)
	{
		if (true == _Attack.SubjectAttack && false == _SubjectUnit.GetIsPlayer()) { continue; }
		if (false == _Attack.SubjectAttack && true == _SubjectUnit.GetIsPlayer()) { continue; }
		// 플레이어 유닛이 공격한 대미지를 더함
		SumDamage += _Attack.Damage;
	}

	Unit& Player = _AttackList.back().SubjectUnit.GetIsPlayer() == true ? _AttackList.back().SubjectUnit : _AttackList.back().TargetUnit;
	Unit& Enemy = _AttackList.back().SubjectUnit.GetIsPlayer() == false ? _AttackList.back().SubjectUnit : _AttackList.back().TargetUnit;

	if (1 <= SumDamage)
	{
		_AttackList.back().Exp = SumDamage + Enemy.GetLevel() - Player.GetLevel() + 20;
	}
	_AttackList.back().IsLevelUp = Player.AddExp(_AttackList.back().Exp);

	if (true == Enemy.GetIsDie())
	{
		std::list<std::shared_ptr<Item>> Items = Enemy.GetItems();
		if (1 < Items.size())
		{
			std::list<std::shared_ptr<Item>>::iterator ItemIter = Items.begin();
			ItemIter++;

			for (; ItemIter != Items.end(); ItemIter++)
			{
				Player.NewItem((*ItemIter)->GetItemCode());
			}
		}
	}

	return _AttackList;

}

