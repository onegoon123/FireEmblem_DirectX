#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
// Ό³Έν :
class UnitRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	UnitRenderer();
	~UnitRenderer();

	// delete Function
	UnitRenderer(const UnitRenderer& _Other) = delete;
	UnitRenderer(UnitRenderer&& _Other) noexcept = delete;
	UnitRenderer& operator=(const UnitRenderer& _Other) = delete;
	UnitRenderer& operator=(UnitRenderer&& _Other) noexcept = delete;

	void SetGrayScale(bool _Value)
	{
		EffectDataValue.IsGrayScale = _Value;
	}
	void SetIsBlur(bool _Value)
	{
		EffectDataValue.IsBlur = _Value;
	}
	void SetBlurLevel(float _Value)
	{
		EffectDataValue.BlurLevel = _Value;
	}
	void SetLocalScale(float4 _Scale)
	{
		GetTransform()->SetLocalScale(_Scale);
		EffectDataValue.Scale = _Scale;
	}
	void SetWorldScale(float4 _Scale)
	{
		GetTransform()->SetWorldScale(_Scale);
		EffectDataValue.Scale = _Scale;
	}
protected:
	void Start() override;
private:
	struct EffectData
	{
		float4 FlashColor = float4::Zero;
		float t = 0;
		float BlurLevel = 0;
		int IsBlur = false;
		int IsGrayScale = false;
		float4 Scale;
	};
	EffectData EffectDataValue;
};

