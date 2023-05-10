#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UICursor;
class SpriteRenderer;
class BattleLevel;
class Weapon;
class BattleUnit;
class AttackUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AttackUI();
	~AttackUI();

	// delete Function
	AttackUI(const AttackUI& _Other) = delete;
	AttackUI(AttackUI&& _Other) noexcept = delete;
	AttackUI& operator=(const AttackUI& _Other) = delete;
	AttackUI& operator=(AttackUI&& _Other) noexcept = delete;

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

	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;
	std::list<std::shared_ptr<Weapon>> Weapons;
	std::list<std::shared_ptr<BattleUnit>> Targets;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
};

