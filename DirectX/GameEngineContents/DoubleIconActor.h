#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class DoubleIconActor : public GameEngineActor
{
public:
	// constrcuter destructer
	DoubleIconActor();
	~DoubleIconActor();

	// delete Function
	DoubleIconActor(const DoubleIconActor& _Other) = delete;
	DoubleIconActor(DoubleIconActor&& _Other) noexcept = delete;
	DoubleIconActor& operator=(const DoubleIconActor& _Other) = delete;
	DoubleIconActor& operator=(DoubleIconActor&& _Other) noexcept = delete;

	void On();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> Renderer = nullptr;
	bool Minus = false;

};

