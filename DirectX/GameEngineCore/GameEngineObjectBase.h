#pragma once
#include <list>
#include <memory>
#include <string_view>

// 설명 :
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	~GameEngineObjectBase();

	// delete Function
	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void On()
	{
		ActiveValue = true;
	}

	void Off()
	{
		ActiveValue = false;
	}

	void Death()
	{
		DeathValue = true;
	}


	void DebugOn()
	{
		DebugValue = true;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool ActiveValue = true; // 켜졌다 꺼졌다
	bool DeathValue = false; // 죽었다 살았다
	bool DebugValue = false;
	int Order = 0;
	////////////////////////////////////////////////////////////// Transform 기하구조
};

