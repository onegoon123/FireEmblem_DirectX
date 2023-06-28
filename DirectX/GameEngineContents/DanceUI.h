#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MapCursor;
class UICursor;
class GameEngineUIRenderer;
class BattleLevel;
class Item;
class BattleUnit;
class DanceUI : public GameEngineActor
{
public:
	// constrcuter destructer
	DanceUI();
	~DanceUI();

	// delete Function
	DanceUI(const DanceUI& _Other) = delete;
	DanceUI(DanceUI&& _Other) noexcept = delete;
	DanceUI& operator=(const DanceUI& _Other) = delete;
	DanceUI& operator=(DanceUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void On(std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void TargetSelectStart();
	void TargetSelectUpdate(float _DeltaTime);
	void TargetSelectEnd();
	void SetTarget();

	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::shared_ptr<BattleUnit>)> DanceFunction;
	std::function<void()> CancelFunction;

	std::shared_ptr<MapCursor> Cursor_Map = nullptr;	// 커서

	std::list<std::shared_ptr<BattleUnit>> TargetUnits;
	std::list<std::shared_ptr<BattleUnit>>::iterator TargetIter;
	std::shared_ptr<BattleUnit> TargetUnit;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
	bool IsClick = false;
};

