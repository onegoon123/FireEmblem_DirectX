#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class UnitInformationUI : public GameEngineActor
{
public:
	// constrcuter destructer
	UnitInformationUI();
	~UnitInformationUI();

	// delete Function
	UnitInformationUI(const UnitInformationUI& _Other) = delete;
	UnitInformationUI(UnitInformationUI&& _Other) noexcept = delete;
	UnitInformationUI& operator=(const UnitInformationUI& _Other) = delete;
	UnitInformationUI& operator=(UnitInformationUI&& _Other) noexcept = delete;
	
	void SetUnit(std::shared_ptr<class BattleUnit> _Unit);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class BattleLevel* CurLevel = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> Background = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PortraitBack = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fore = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PersonalDataWindow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PortraitRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UnitRenderer = nullptr;

	std::shared_ptr<class NumberActor> Number_Level = nullptr;
	std::shared_ptr<NumberActor> Number_Exp = nullptr;
	std::shared_ptr<NumberActor> Number_HP = nullptr;
	std::shared_ptr<NumberActor> Number_MaxHP = nullptr;

	std::shared_ptr<NumberActor> Number_Strength = nullptr;
	std::shared_ptr<NumberActor> Number_Magic = nullptr;
	std::shared_ptr<NumberActor> Number_Dexterity = nullptr;
	std::shared_ptr<NumberActor> Number_Speed = nullptr;
	std::shared_ptr<NumberActor> Number_Defense = nullptr;
	std::shared_ptr<NumberActor> Number_Resistance = nullptr;
	std::shared_ptr<NumberActor> Number_Luck = nullptr;
	std::shared_ptr<NumberActor> Number_Move = nullptr;
	std::shared_ptr<NumberActor> Number_Constitution = nullptr;
};

