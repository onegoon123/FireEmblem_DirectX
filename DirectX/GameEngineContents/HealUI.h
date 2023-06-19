#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MapCursor;
class UICursor;
class GameEngineUIRenderer;
class BattleLevel;
class Item;
class BattleUnit;
class HealUI : public GameEngineActor
{
public:
	// constrcuter destructer
	HealUI();
	~HealUI();

	// delete Function
	HealUI(const HealUI& _Other) = delete;
	HealUI(HealUI&& _Other) noexcept = delete;
	HealUI& operator=(const HealUI& _Other) = delete;
	HealUI& operator=(HealUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void StaveSelectStart();
	void StaveSelectUpdate(float _DeltaTime);
	void StaveSelectEnd();
	void SetStave();
	void TargetSelectStart();
	void TargetSelectUpdate(float _DeltaTime);
	void TargetSelectEnd();
	void SetTarget();
	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::shared_ptr<BattleUnit>, std::list<std::shared_ptr<Item>>::iterator&)> HealFunction;
	std::function<void()> CancelFunction;

	std::shared_ptr<MapCursor> Cursor_Map = nullptr;	// 커서
	std::shared_ptr<UICursor> Cursor_UI = nullptr;	// 커서
	std::shared_ptr<GameEngineUIRenderer> SelectRender = nullptr; // 선택배경
	std::shared_ptr<GameEngineUIRenderer> WindowRender = nullptr;	// 배경창
	std::shared_ptr<GameEngineUIRenderer> InfoRender = nullptr;	// 스탯 정보
	std::shared_ptr<GameEngineUIRenderer> Portrait = nullptr;		// 초상화
	std::vector<std::shared_ptr<GameEngineUIRenderer>> StaveIcon;
	std::vector<std::shared_ptr<class NumberActor>> StaveUses;

	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;
	std::list<std::shared_ptr<BattleUnit>> TargetUnits;
	std::list<std::shared_ptr<Item>> Staves;
	std::shared_ptr<Item> SelectStave;

	std::list<std::shared_ptr<BattleUnit>> Targets;
	std::list<std::shared_ptr<BattleUnit>>::iterator TargetIter;
	std::shared_ptr<BattleUnit> TargetUnit;
	std::list <std::shared_ptr<Item>>* Items;
	std::list<std::shared_ptr<Item>>::iterator StaveIter;
	std::shared_ptr<class UIButtonSystem> ButtonSystem;
	std::vector<std::shared_ptr<class GameEngineCollision>> ButtonCols;

	std::vector<std::shared_ptr<class TextRenderer>> ItemNameTexts;
	std::shared_ptr<TextRenderer> ItemInfoText;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
	bool IsStaveSelect = false;// 무기를 선택했는가
	bool IsClick = false;
};

