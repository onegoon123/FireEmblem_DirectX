#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineUIRenderer;
class BattleUnit;
class SelectUIObject
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

	void Update(float _DeltaTime);
	void ChangeDir(UIDir _Dir);

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
	void UnitUIOff();

	void PotionUIOn();
	void PotionUIOff();

protected:
	void Start();
	void Update(float _DeltaTiime) override;

private:
	SelectUIObject Goal;	// 목표 표시UI
	SelectUIObject TerrainUI;	// 지형 표시UI
	SelectUIObject UnitData;	// 유닛 표시UI

	std::shared_ptr<GameEngineUIRenderer> HPBarRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PortraitRender = nullptr;
	std::shared_ptr<class NumberActor> TerrainDodge = nullptr;
	std::shared_ptr<class NumberActor> TerrainDef = nullptr;
	std::shared_ptr<class NumberActor> UnitHP = nullptr;
	std::shared_ptr<class NumberActor> UnitMaxHP= nullptr;

	bool UnitDataOn = false;
	UIDir CursorDir = UIDir::LeftUp;
	float Timer = 0;
	float StartValue = 0;
	float TargetValue = 0;
	bool IsLerp = false;
};

