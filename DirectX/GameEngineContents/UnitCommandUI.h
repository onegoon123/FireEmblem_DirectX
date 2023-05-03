#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SpriteRenderer;
class BattleLevel;
class UnitCommandUI : public GameEngineActor
{
public:
	// constructer destructer
	UnitCommandUI();
	~UnitCommandUI();

	// delete Function
	UnitCommandUI(const UnitCommandUI& _Other) = delete;
	UnitCommandUI(UnitCommandUI&& _Other) = delete;
	UnitCommandUI& operator=(const UnitCommandUI& _Other) = delete;
	UnitCommandUI& operator=(UnitCommandUI&& _Other) = delete;

	void Setting(BattleLevel* _Level);
	void SetCommand(bool _IsAttackable, bool _IsCloseUnit);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	BattleLevel* LevelPtr = nullptr;
	std::shared_ptr<SpriteRenderer> CursorRender = nullptr;
	std::shared_ptr<SpriteRenderer> SelectRender = nullptr;
	std::shared_ptr<SpriteRenderer> WindowRender = nullptr;

	std::vector<std::function<void()>> CommandFunctions;
	size_t CurrentCursor = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;

};

