#include "PrecompileHeader.h"
#include "AttackUI.h"

AttackUI::AttackUI() 
{
}

AttackUI::~AttackUI() 
{
}

void AttackUI::Setting(BattleLevel* _Level)
{
	LevelPtr = _Level;
}

void AttackUI::Start()
{
	Off();
}

void AttackUI::Update(float _DeltaTime)
{
}

