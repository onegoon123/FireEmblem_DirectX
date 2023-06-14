#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore/GameEngineFSM.h>
// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineFSM FSM;
	std::shared_ptr<class GameEngineUIRenderer> TitleRenderer = nullptr;
	float Timer = 0;
	void StateInit();
};

