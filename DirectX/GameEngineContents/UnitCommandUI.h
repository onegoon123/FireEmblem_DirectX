#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UICursor;
class GameEngineUIRenderer;
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

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void SetCommand(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem);
	void SetCommandHeal(bool _IsCloseUnit, bool _IsItem);
	void SetConquer();	// 목표 점령시 나오는 커맨드

	void On();

	void SetLeft()
	{
		GetTransform()->SetLocalPosition({-668, 0});
		StartCursorPos = { -420, 152 };
	}
	void SetRight()
	{
		GetTransform()->SetLocalPosition({ 0, 0 });
		StartCursorPos = { 224, 152 };
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	BattleLevel* LevelPtr = nullptr;
	std::shared_ptr<UICursor> Cursor = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SelectRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> WindowRender = nullptr;
	std::vector<std::function<void()>> CommandFunctions;

	std::shared_ptr<class UIButtonSystem> ButtonSystem;
	std::vector<std::shared_ptr<class GameEngineCollision>> ButtonCols;
	std::vector<std::shared_ptr<class TextRenderer>> FontRenders;


	std::function<void()> CancelFunction;
	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	float4 StartCursorPos = { 224, 152 };
	float4 StartSelectPos = { 330, 152 };

	const float PreesTime = 0.2f;
	bool PressOK = false;
};

