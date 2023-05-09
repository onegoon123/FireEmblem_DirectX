#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UICursor;
class SpriteRenderer;
class BattleLevel;
class FieldCommandUI : public GameEngineActor
{
public:
	// constrcuter destructer
	FieldCommandUI();
	~FieldCommandUI();

	// delete Function
	FieldCommandUI(const FieldCommandUI& _Other) = delete;
	FieldCommandUI(FieldCommandUI&& _Other) noexcept = delete;
	FieldCommandUI& operator=(const FieldCommandUI& _Other) = delete;
	FieldCommandUI& operator=(FieldCommandUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level);
	void On();
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BattleLevel* LevelPtr = nullptr;
	std::shared_ptr<UICursor> Cursor = nullptr;
	std::shared_ptr<SpriteRenderer> SelectRender = nullptr;
	std::shared_ptr<SpriteRenderer> WindowRender = nullptr;

	std::vector<std::function<void()>> CommandFunctions;
	std::function<void()> CancelFunction;

	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
};

