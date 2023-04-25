#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// 설명 :
class GameEngineObject :
	public GameEngineObjectBase,
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject>
	// 침습형
{
	friend class GameEngineLevel;

public:

	GameEngineObject();
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

	template<typename PtrType>
	std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	{
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}


private:
	GameEngineTransform Transform;

};
