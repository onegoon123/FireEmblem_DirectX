#pragma once
#include <string>
#include "Stat.h"
// 유닛 클래스
// 배틀 시 화면에 나타날 플레이어, 적, 기타 오브젝트의 부모 클래스
class Unit
{
public:
	// constructer destructer
	Unit();
	~Unit();

	

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) = delete;

protected:

private:
	int IdentityCode = 0;
	std::string UnitName = "";
	Stat UnitStat;
};

