#include "PrecompileHeader.h"
#include "Unit.h"
int Unit::UnitNum = 0;
Unit::Unit() 
{
	UnitCode = UnitNum++;
}

Unit::~Unit() 
{
}


