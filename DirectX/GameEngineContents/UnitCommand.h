#pragma once
#include "BattleUnit.h"

	enum class CommandType
	{
		Attack,
		Item,
		Wait,
	};

struct AttackCommand
{
	Unit SubjectUnit = Unit();
	Unit TargetUnit = Unit();
	bool IsCritical = false;
	bool IsHit = false;
};
class UnitCommand
{
	friend class BattleLevel;
public:
	// constrcuter destructer
	UnitCommand();
	~UnitCommand();


	static std::list<AttackCommand> Attack(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit);
	static void Wait(std::shared_ptr<BattleUnit> _SubjectUnit);
	static void ItemUse() {}

	static std::list<UnitCommand> GetCommandList() { return CommandList; }
	static void ResetCommandList()
	{
		CommandList.clear();
	}
	static void PopCommandList()
	{
		CommandList.pop_back();
	}
protected:

private:
	static std::list<UnitCommand> CommandList;
	CommandType TypeValue = CommandType::Wait;
	Unit BeforeSubjectUnit = Unit();
	Unit BeforeTargetUnit = Unit();
	Unit AfterSubjectUnit = Unit();
	Unit AfterTargetUnit = Unit();
	int2 BeforeSubjectUnitPos = int2();
	int2 AfterSubjectUnitPos = int2();
	int RandomNum = 0;
	std::string Record = "";
};
