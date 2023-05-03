#include "PrecompileHeader.h"	
#include "BattleAnimationLevel.h"

std::shared_ptr<BattleUnit> BattleAnimationLevel::SubjectUnit = nullptr;
std::shared_ptr<BattleUnit> BattleAnimationLevel::TargetUnit = nullptr;
std::list<AttackCommand> BattleAnimationLevel::BattleData = std::list<AttackCommand>();

BattleAnimationLevel::BattleAnimationLevel()
{
}

BattleAnimationLevel::~BattleAnimationLevel()
{
}

void BattleAnimationLevel::SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data)
{
	SubjectUnit = _SubjectUnit;
	TargetUnit = _TargetUnit;
	BattleData = _Data; 
}

void BattleAnimationLevel::Start()
{
}

void BattleAnimationLevel::Update(float _DeltaTime)
{
}

void BattleAnimationLevel::LevelChangeStart()
{
}
