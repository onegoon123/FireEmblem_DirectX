#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
// ���� :
class GameEngineUIRenderer;
class DialogueSystem : public GameEngineActor
{
public:
	// constrcuter destructer
	DialogueSystem();
	~DialogueSystem();

	// delete Function
	DialogueSystem(const DialogueSystem& _Other) = delete;
	DialogueSystem(DialogueSystem&& _Other) noexcept = delete;
	DialogueSystem& operator=(const DialogueSystem& _Other) = delete;
	DialogueSystem& operator=(DialogueSystem&& _Other) noexcept = delete;

	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);

	void SetSize(float4 _Size);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<GameEngineUIRenderer>> DialogueBoxRenders;
	std::shared_ptr<GameEngineUIRenderer> ArrowRender;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

