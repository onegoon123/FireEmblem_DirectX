#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class NumberActor : public GameEngineActor
{
public:
	// constrcuter destructer
	NumberActor();
	~NumberActor();

	// delete Function
	NumberActor(const NumberActor& _Other) = delete;
	NumberActor(NumberActor&& _Other) noexcept = delete;
	NumberActor& operator=(const NumberActor& _Other) = delete;
	NumberActor& operator=(NumberActor&& _Other) noexcept = delete;

	void SetValue(int _Value);
	void SetBlackFont();
	void SetDamageFont();

protected:
	void Start() override;

private:
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> Renders;
};

