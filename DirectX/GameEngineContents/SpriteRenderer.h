#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
// Ό³Έν :
class SpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	SpriteRenderer();
	~SpriteRenderer();

	// delete Function
	SpriteRenderer(const SpriteRenderer& _Other) = delete;
	SpriteRenderer(SpriteRenderer&& _Other) noexcept = delete;
	SpriteRenderer& operator=(const SpriteRenderer& _Other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& _Other) noexcept = delete;

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
	void SetFlash(float4 _Color, float _t)
	{
		EffectDataValue.LerpColor = _Color;
		EffectDataValue.LerpT = _t;
	}
	void OffFlashColor()
	{
		EffectDataValue.LerpColor = float4::Null;
		EffectDataValue.LerpT = 0;
	}
	void SetFlashLevel(float _t)
	{
		EffectDataValue.LerpT = _t;
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
		float4 LerpColor = float4::Zero;
		float LerpT = 0;
		float BlurLevel = 0;
		int IsBlur = false;
		int IsGrayScale = false;
		float4 Scale;
	};
	EffectData EffectDataValue;
};

