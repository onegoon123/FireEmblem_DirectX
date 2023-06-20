#pragma once
#include <GameEngineCore/GameEngineActor.h>
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
	std::shared_ptr<class GameEngineUIRenderer> Background;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> Icons;
	std::shared_ptr<class TextRenderer> Dialogue;
	std::vector<std::shared_ptr<class TextRenderer>> ItemNameTexts;
	std::vector<std::shared_ptr<class NumberActor>> ItemUses;
	std::vector<std::shared_ptr<class NumberActor>> ItemPrices;

};

