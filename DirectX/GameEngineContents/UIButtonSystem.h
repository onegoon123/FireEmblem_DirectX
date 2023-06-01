#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
// Ό³Έν :
class UIButtonSystem : public GameEngineActor
{
public:
	// constrcuter destructer
	UIButtonSystem();
	~UIButtonSystem();

	// delete Function
	UIButtonSystem(const UIButtonSystem& _Other) = delete;
	UIButtonSystem(UIButtonSystem&& _Other) noexcept = delete;
	UIButtonSystem& operator=(const UIButtonSystem& _Other) = delete;
	UIButtonSystem& operator=(UIButtonSystem&& _Other) noexcept = delete;

	void NewButton(std::shared_ptr<GameEngineCollision> _Collision, std::function<void()> _HoverFunction, std::function<void()> _ClickFunction);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct Button
	{
		std::shared_ptr<GameEngineCollision> Col = nullptr;
		std::function<void()> HoverFunction = nullptr;
		std::function<void()> ClickFunction = nullptr;
	};

	std::vector<Button> Buttons;
	std::shared_ptr<GameEngineCollision> MouseCol;
};

