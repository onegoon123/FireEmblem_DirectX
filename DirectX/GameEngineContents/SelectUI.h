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

class GameEngineRenderer;
class SelectUIObject
{
public:
	SelectUIObject() {}
	~SelectUIObject() {}

	std::shared_ptr<GameEngineRenderer> Render = nullptr;
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
// ���� :
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


protected:
	void Start() override;
	void Update(float _DeltaTiime) override;

private:
	SelectUIObject Goal;	// ��ǥ ǥ��UI
	SelectUIObject Terrain;	// ���� ǥ��UI
	SelectUIObject UnitData;	// ���� ǥ��UI


	UIDir CursorDir = UIDir::LeftUp;
};
