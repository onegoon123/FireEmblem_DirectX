#pragma once
#include "BattleUnit.h"

	enum class CommandType
	{
		None,
		Attack,
		Item,
		Wait,
		PlayerPhaseStart,
		EnemyPhaseStart,
		Store,
	};

struct AttackCommand
{
	Unit SubjectUnit = Unit();
	Unit TargetUnit = Unit();
	bool IsCritical = false;
	bool IsHit = false;
	bool SubjectAttack = false;
	bool IsLevelUp = false;
	int Damage = 0;
	int Exp = 1;

	AttackCommand& ChangeOrder()
	{
		Unit Temp = SubjectUnit;
		SubjectUnit = TargetUnit;
		TargetUnit = Temp;
		return (*this);
	}
};
class UnitCommand
{
	friend class BattleLevel;
public:
	// constrcuter destructer
	UnitCommand();
	~UnitCommand();


	static std::list<AttackCommand> Attack(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit);
	// 공격시 결과를 미리 계산하는 기능
	static AttackCommand AttackSimulation(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit);
	// 일반적인 공격
	static AttackCommand AttackCalculation(Unit& _SubjectUnit, Unit& _TargetUnit);
	// 시뮬레이션용 랜덤을 사용하지 않는 공격
	static AttackCommand AttackCalculationNoRandom(Unit& _SubjectUnit, Unit& _TargetUnit);
	static void Wait(std::shared_ptr<BattleUnit> _SubjectUnit);
	static void ItemUse(std::shared_ptr<BattleUnit> _SubjectUnit, std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	static void ClassChange(std::shared_ptr<BattleUnit> _SubjectUnit, BattleClass _ClassValue, std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	static std::list<AttackCommand> Heal(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	static void PhaseStart(Faction _Faction);
	static void StoreUse(std::shared_ptr<BattleUnit> _SubjectUnit, std::list<std::shared_ptr<class Item>> _BeforeItems, int _BeforeMoney);
	static void Dance(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit);

	static int GetCountTurn();

	static std::vector<UnitCommand>& GetCommandList() { return CommandList;}
	static void SetCommandList(std::vector<UnitCommand> _Value) { CommandList = _Value; }
	static void ResetCommandList()
	{
		CommandList.clear();
	}
	static void PopCommandList()
	{
		CommandList.pop_back();
	}
	CommandType GetTypeValue()
	{
		return TypeValue;
	}
	std::string GetRecord()
	{
		return Record;
	}
	bool IsPlayerTurn()
	{
		switch (TypeValue)
		{
		case CommandType::PlayerPhaseStart:
			return true;
		case CommandType::EnemyPhaseStart:
			return false;
		}
		return BeforeSubjectUnit.GetIsPlayer();
	}
protected:

private:
	static std::vector<UnitCommand> CommandList;
	CommandType TypeValue = CommandType::Wait;
	Unit BeforeSubjectUnit = Unit();
	Unit BeforeTargetUnit = Unit();
	Unit AfterSubjectUnit = Unit();
	Unit AfterTargetUnit = Unit();
	std::list<Item> BeforeSubjectItems = std::list<Item>();
	std::list<Item> BeforeTargetItems = std::list<Item>();
	std::list<Item> AfterSubjectItems = std::list<Item>();
	std::list<Item> AfterTargetItems = std::list<Item>();
	int2 BeforeSubjectUnitPos = int2(-1, -1);
	int2 AfterSubjectUnitPos = int2(-1, -1);
	int RandomNum = 0;
	int UseMoney = 0;
	std::string Record = "";

	static std::list<AttackCommand>& AttackEnd(std::list<AttackCommand>& _AttackList, UnitCommand& _CommandRecord, Unit& _SubjectUnit, Unit& _TargetUnit);
};
