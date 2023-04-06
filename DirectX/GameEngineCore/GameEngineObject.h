#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// 설명 :
class GameEngineObject : public GameEngineObjectBase, public GameEngineNameObject
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

	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}


private:
	GameEngineTransform Transform;

};
