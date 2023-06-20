#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class BattleLevelUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleLevelUI();
	~BattleLevelUI();

	// delete Function
	BattleLevelUI(const BattleLevelUI& _Other) = delete;
	BattleLevelUI(BattleLevelUI&& _Other) noexcept = delete;
	BattleLevelUI& operator=(const BattleLevelUI& _Other) = delete;
	BattleLevelUI& operator=(BattleLevelUI&& _Other) noexcept = delete;

	void AllOff();

	void SelectOn();
	void SetUnitData(std::shared_ptr<class BattleUnit> _Unit);
	void UnitUIOff();
	void SetCursorDir(UIDir _Dir);
	void SetTerrain(Terrain _Value);
	void UnitCommandOn();
	void UnitCommandSet(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem);
	void UnitCommandHealSet(bool _IsCloseUnit, bool _IsItem);
	void UnitCommandConquer();
	void UnitCommandStore();
	void FieldCommandOn();
	void TimeStoneOn(bool _IsGameOver = false);
	void AttackOn(std::shared_ptr<class BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void HealOn(std::shared_ptr<class BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void ItemOn(std::shared_ptr<BattleUnit> _SelectUnit);
	void ExchangeOn(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void PhaseOn(Faction _Faction);
	void StoreOn(std::shared_ptr<BattleUnit> _Unit);
	bool IsPhaseEnd();
	void PhaseOff();
	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);
	void SetFadeWait(float _Timer);
	void PotionUIOn();
	void PotionUIOff();
	void SetHPLerp(int _Value);
	void SetClearTargetText(const std::string_view& _Text);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

	std::shared_ptr <class SelectUI> UI_Select = nullptr;
	std::shared_ptr <class UnitCommandUI> UI_UnitCommand = nullptr;
	std::shared_ptr <class FieldCommandUI> UI_FieldCommand = nullptr;
	std::shared_ptr <class AttackUI> UI_Attack = nullptr;
	std::shared_ptr <class HealUI> UI_Heal = nullptr;
	std::shared_ptr <class ItemUI> UI_Item = nullptr;
	std::shared_ptr <class ExchangeUI> UI_Exchange = nullptr;
	std::shared_ptr <class PhaseUI> UI_Phase = nullptr;
	std::shared_ptr <class UICursor> UI_Cursor = nullptr;
	std::shared_ptr <class GameEngineUIRenderer> UI_Fade = nullptr;
	std::shared_ptr <class TimeStoneUI> UI_TimeStone = nullptr;
	std::shared_ptr <class StoreUI> UI_Store = nullptr;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	float FadeWait = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

