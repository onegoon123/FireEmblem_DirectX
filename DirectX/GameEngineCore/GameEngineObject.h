#pragma once
#include <string_view>
#include <list>
#include <memory>

// 설명 :
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	//                 "드래곤"
	// 동적할당 1번을 줄이려고.
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; // 켜졌다 꺼졌다
	bool IsDeath = false; // 죽었다 살았다.

	GameEngineObject* Parent;

	std::list<std::shared_ptr<GameEngineObject>> Childs;
};