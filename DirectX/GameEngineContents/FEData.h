#pragma once
#include "Unit.h"
// Ό³Έν :
class FEData
{
public:
	// constrcuter destructer
	FEData();
	~FEData();

	// delete Function
	FEData(const FEData& _Other) = delete;
	FEData(FEData&& _Other) noexcept = delete;
	FEData& operator=(const FEData& _Other) = delete;
	FEData& operator=(FEData&& _Other) noexcept = delete;

	static void SetPlayerUnits(const std::list<Unit>& _Units)
	{
		PlayerUnits = _Units;
	}
	static std::list<Unit>& GetPlayerUnits()
	{
		return PlayerUnits;
	}

	static int GetMoney() { return Money; }
	static void SetMoney(int _Money) { Money = _Money; }
	static void AddMoney(int _Money) { Money += _Money; }

protected:

private:
	static std::list<Unit> PlayerUnits;
	static int Money;
};

