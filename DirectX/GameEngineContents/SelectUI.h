#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineUIRenderer;
class BattleUnit;
class TextRenderer;
class SelectUIObject : public GameEngineActor
{
public:
	SelectUIObject() {}
	~SelectUIObject() {}

	std::shared_ptr<GameEngineUIRenderer> Render = nullptr;
	UIDir CurDir = UIDir::None;
	UIDir NextDir = UIDir::None;

	float Timer = 0;
	float4 StartPos = float4::Zero;
	float4 TargetPos = float4::Zero;
	float4 BenchmarkShowPos = float4::Zero;
	float4 BenchmarkHidePos = float4::Zero;

	void ChangeDir(UIDir _Dir);

protected:
	void Update(float _DeltaTime) override;
private:

};
// 설명 :
class SelectUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectUI();
	~SelectUI();

	// delete Function
	SelectUI(const SelectUI& _Other) = delete;
	SelectUI(SelectUI&& _Other) noexcept = delete;
	SelectUI& operator=(const SelectUI& _Other) = delete;
	SelectUI& operator=(SelectUI&& _Other) noexcept = delete;

	void SetCursorDir(UIDir _Dir);
	void SetTerrainData(Terrain _Data);
	void On();
	void Off();

	void SetHPBar(float _Value);
	void SetHPLerp(int _Value);
	void SetUnitData(std::shared_ptr<BattleUnit> _Unit);
	void SetClearTarget(const std::string_view& _Text);
	void UnitUIOff();

	void PotionUIOn();
	void PotionUIOff();

protected:
	void Start();
	void Update(float _DeltaTiime) override;

private:
	std::shared_ptr<SelectUIObject> Goal = nullptr;	// 목표 표시UI
	std::shared_ptr<SelectUIObject> TerrainUI = nullptr;	// 지형 표시UI
	std::shared_ptr<SelectUIObject> UnitData = nullptr;	// 유닛 표시UI

	std::shared_ptr<GameEngineUIRenderer> HPBarRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PortraitRender = nullptr;
	std::shared_ptr<class NumberActor> TerrainDodge = nullptr;
	std::shared_ptr<class NumberActor> TerrainDef = nullptr;
	std::shared_ptr<class NumberActor> UnitHP = nullptr;
	std::shared_ptr<class NumberActor> UnitMaxHP= nullptr;

	std::shared_ptr<TextRenderer> UnitNameText = nullptr;
	std::shared_ptr<TextRenderer> ClearTargetText = nullptr;
	std::shared_ptr<TextRenderer> TerrainText = nullptr;

	bool UnitDataOn = false;
	UIDir CursorDir = UIDir::LeftUp;
	float Timer = 0;
	float StartValue = 0;
	float TargetValue = 0;
	bool IsLerp = false;
};

