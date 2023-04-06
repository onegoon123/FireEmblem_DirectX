#pragma once
#include <GameEngineCore/GameEngineActor.h>
class BattleActor : public GameEngineActor
{
public:
	// constructer destructer
	BattleActor();
	~BattleActor();

	// delete Function
	BattleActor(const BattleActor& _Other) = delete;
	BattleActor(BattleActor&& _Other) = delete;
	BattleActor& operator=(const BattleActor& _Other) = delete;
	BattleActor& operator=(BattleActor&& _Other) = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineRenderer> Render0;
	std::shared_ptr<class GameEngineRenderer> Render1;
	std::shared_ptr<class GameEngineRenderer> Render2;

};

