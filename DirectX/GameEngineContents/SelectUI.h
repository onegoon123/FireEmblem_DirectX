#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class UIDir
{
	None,
	LeftUp,
	LeftDown,
	RightUp,
	RightDown
};

class SpriteRenderer;
class SelectUIObject
{
public:
	SelectUIObject() {}
	~SelectUIObject() {}

	std::shared_ptr<SpriteRenderer> Render = nullptr;
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
	void UIOn();
	void UIOff();

	void SetHP(float _Value);
	void UnitUIOff();

protected:
	void Start() override;
	void Update(float _DeltaTiime) override;

private:
	SelectUIObject Goal;	// 목표 표시UI
	SelectUIObject Terrain;	// 지형 표시UI
	SelectUIObject UnitData;	// 유닛 표시UI

	std::shared_ptr<SpriteRenderer> HPBarRender = nullptr;
	bool UnitDataOn = false;
	UIDir CursorDir = UIDir::LeftUp;
};

