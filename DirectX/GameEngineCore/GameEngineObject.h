#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

// 설명 :
class GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineObject();
	// 소멸자에 virtual붙이는 이유 => 자식소멸자가 제대로 호출되게 하기 위해서
	// 순수가상함수 쓰는 이유 => 자식에게 인터페이스를 강요하기 위해서
	// 순수가상함수 쓰는 이유 => 그 클래스를 객체화 할수 없게 만들기 위해서.
	// 소멸자를 순수가상함수를 만드는 이유? => 추상화 할만한게 딱히 없어서.
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

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
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	void Death()
	{
		IsDeath = true;
	}

	//                 "드래곤"
	// 동적할당 1번을 줄이려고.
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	GameEngineObject* GetParent()
	{
		return Parent;
	}

	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	std::string Name = "";
	bool IsActive = true; // 켜졌다 꺼졌다
	bool IsDeath = false; // 죽었다 살았다
	int Order = 0;

	GameEngineObject* Parent = nullptr;

	std::list<std::shared_ptr<GameEngineObject>> Child;

	////////////////////////////////////////////////////////////// Transform 기하구조

private:
	GameEngineTransform Transform;

};
