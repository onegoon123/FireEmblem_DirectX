#pragma once
#include <GameEngineBase/GameEngineRandom.h>
static const int Seed = 0;
class FERandom
{
public:
	// constructer destructer
	FERandom()
	{
		GameEngineRandom::MainRandom.SetSeed(Seed);
	}
	~FERandom() {}

	// 0~99 반환 명중 수치가 반환값 보다 높으면 명중입니다.
	static int RandomInt()
	{
		RandomCount++;
		return GameEngineRandom::MainRandom.RandomInt(0, 99);
	}
	// 난수를 _Count번째 난수로 세팅합니다
	static void SetRandomCount(int _Count)
	{
		RandomCount = 0;
		GameEngineRandom::MainRandom.SetSeed(Seed);
		for (int i = 0; i < _Count; i++)
		{
			RandomInt();
		}
	}
	// 현재 몇번째 난수인지 반환합니다
	static int GetRandomCount()
	{
		return RandomCount;
	}

	// delete Function
	FERandom(const FERandom& _Other) = delete;
	FERandom(FERandom&& _Other) = delete;
	FERandom& operator=(const FERandom& _Other) = delete;
	FERandom& operator=(FERandom&& _Other) = delete;

protected:

private:
	static int RandomCount;	// 랜덤을 실행한 횟수
};

