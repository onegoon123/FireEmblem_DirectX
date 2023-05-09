#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class SpriteRenderer;
class UICursor : public GameEngineActor
{
public:
	// constrcuter destructer
	UICursor();
	~UICursor();

	// delete Function
	UICursor(const UICursor& _Other) = delete;
	UICursor(UICursor&& _Other) noexcept = delete;
	UICursor& operator=(const UICursor& _Other) = delete;
	UICursor& operator=(UICursor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<SpriteRenderer> CursorRender = nullptr;

};

