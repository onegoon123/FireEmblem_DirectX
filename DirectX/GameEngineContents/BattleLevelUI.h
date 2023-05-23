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
	void UnitCommandOn();
	void UnitCommandSet(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem);
	void FieldCommandOn();
	void AttackOn(std::shared_ptr<class BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void ItemOn(std::shared_ptr<BattleUnit> _SelectUnit);
	void PhaseOn(Faction _Faction);
	bool IsPhaseEnd();
	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

	std::shared_ptr <class SelectUI> UI_Select = nullptr;
	std::shared_ptr <class UnitCommandUI> UI_UnitCommand = nullptr;
	std::shared_ptr <class FieldCommandUI> UI_FieldCommand = nullptr;
	std::shared_ptr <class AttackUI> UI_Attack = nullptr;
	std::shared_ptr <class ItemUI> UI_Item = nullptr;
	std::shared_ptr <class PhaseUI> UI_Phase = nullptr;
	std::shared_ptr <class UICursor> UI_Cursor = nullptr;
	std::shared_ptr <class GameEngineUIRenderer> UI_Fade = nullptr;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

