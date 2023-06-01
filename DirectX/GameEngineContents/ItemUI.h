#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
class MapCursor;
class UICursor;
class GameEngineUIRenderer;
class BattleLevel;
class Weapon;
class BattleUnit;
class Item;
class ItemUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemUI();
	~ItemUI();

	// delete Function
	ItemUI(const ItemUI& _Other) = delete;
	ItemUI(ItemUI&& _Other) noexcept = delete;
	ItemUI& operator=(const ItemUI& _Other) = delete;
	ItemUI& operator=(ItemUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void On(std::shared_ptr<BattleUnit> _SelectUnit);
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void ItemSelectUpdate(float _DeltaTime);
	void ItemSelect();
	void ItemUseUpdate(float _DeltaTime);

	void Equipment();
	void Drop();
	void Use();

	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::list<std::shared_ptr<Item>>::iterator&)> UseFunction;
	std::function<void()> CancelFunction;
	std::vector<std::function<void()>> UseFunctions;

	std::shared_ptr<UICursor> Cursor = nullptr;	// 커서
	std::shared_ptr<GameEngineUIRenderer> SelectRender = nullptr; // 선택배경
	std::shared_ptr<GameEngineUIRenderer> WindowRender = nullptr;	// 배경창
	std::shared_ptr<GameEngineUIRenderer> InfoRender = nullptr;	// 아이템 정보
	std::shared_ptr<GameEngineUIRenderer> Portrait = nullptr;		// 초상화
	std::shared_ptr<GameEngineUIRenderer> ItemUseWindow = nullptr;	// 아이템 사용 창
	std::shared_ptr<GameEngineUIRenderer> ItemUseSelect = nullptr;	// 아이템 사용 선택
	std::vector<std::shared_ptr<GameEngineUIRenderer>> Icons;
	size_t ItemSize = 0;
	std::list<std::shared_ptr<Item>>::iterator ItemIter;
	std::vector<std::shared_ptr<class NumberActor>> ItemUses;
	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;

	std::shared_ptr<class UIButtonSystem> ButtonSystem;
	std::vector<std::shared_ptr<class GameEngineCollision>> ItemButtons;
	std::vector<std::shared_ptr<class GameEngineCollision>> UseButtons;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 StartUseCursorPos = {0,0};
	float4 StartUseSelectPos = {0,0};

	float4 UseCursorPos;
	float4 CursorPos;
	size_t CurrentCursor = 0;
	size_t CurrentUseCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
	bool IsItemSelect = false;// 아이템을 선택했는가
	bool IsClick = false;
};

