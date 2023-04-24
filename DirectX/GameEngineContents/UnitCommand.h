#pragma once
#include "BattleUnit.h"


struct AttackCommand
{
	Unit TargetUnit = Unit();
	bool IsCritical = false;
	bool IsDodge = false;
};
class UnitCommand
{
public:
	// constrcuter destructer
	UnitCommand();
	~UnitCommand();

	// delete Function
	UnitCommand(const UnitCommand& _Other) = delete;
	UnitCommand(UnitCommand&& _Other) noexcept = delete;
	UnitCommand& operator=(const UnitCommand& _Other) = delete;
	UnitCommand& operator=(UnitCommand&& _Other) noexcept = delete;

	static std::list<AttackCommand> Attack(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit);
	static void ItemUse() {}



protected:

private:
	static std::list<UnitCommand> CommandList;

	BattleUnit BeforeSubjectUnit = BattleUnit();
	BattleUnit BeforeTargetUnit = BattleUnit();
	BattleUnit AfterSubjectUnit = BattleUnit();
	BattleUnit AfterTargetUnit = BattleUnit();
	int RandomNum = 0;
	std::string Record = "";
};
