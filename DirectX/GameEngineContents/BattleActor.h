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
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

};

