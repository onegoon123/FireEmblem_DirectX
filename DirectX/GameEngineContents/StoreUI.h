#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include "ContentsEnum.h"
// Ό³Έν :
class StoreUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StoreUI();
	~StoreUI();

	// delete Function
	StoreUI(const StoreUI& _Other) = delete;
	StoreUI(StoreUI&& _Other) noexcept = delete;
	StoreUI& operator=(const StoreUI& _Other) = delete;
	StoreUI& operator=(StoreUI&& _Other) noexcept = delete;

	void On(std::shared_ptr<class BattleUnit> _Unit);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::function<void()> EndFunction = nullptr;
	GameEngineFSM FSM;

	std::shared_ptr<class GameEngineUIRenderer> Background;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> Icons;
	std::shared_ptr<class UICursor> Cursor;
	std::shared_ptr<class TextRenderer> Dialogue;
	std::shared_ptr<class TextRenderer> Dialogue2;
	std::vector<std::shared_ptr<class TextRenderer>> ItemNameTexts;
	std::vector<std::shared_ptr<class NumberActor>> ItemUses;
	std::vector<std::shared_ptr<class NumberActor>> ItemPrices;

	const float4 StartCursorPos = { -284, 0 };
	float4 CursorPos;
	size_t CurrentCursor = 0;

	const std::vector<ItemCode> ItemList = { ItemCode::SteelSword, ItemCode::KillingSword, ItemCode::SilverLance, ItemCode::Elixir, ItemCode::MasterSeal };
	const std::vector<int> Price = {50, 125, 100, 30, 100};
	std::vector<std::shared_ptr<class Item>> StoreItems;
	int ItemSize = 5;

	bool IsSell = false;
};

