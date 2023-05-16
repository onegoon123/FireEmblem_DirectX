#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
// 설명 :
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

	void SetIsBlur(bool _Value)
	{
		EffectDataValue.IsBlur = _Value;
	}
	void SetBlurLevel(float _Value)
	{
		EffectDataValue.BlurLevel = _Value;
	}

	void SetLerp(float4 _Color, float _t)
	{
		EffectDataValue.LerpColor = _Color;
		EffectDataValue.LerpT = _t;
	}
	void OffLerp()
	{
		EffectDataValue.LerpColor = float4::Null;
		EffectDataValue.LerpT = 0;
	}
	void SetLerpT(float _t)
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


	// 색조 지정
	void SetHue(float _Value)
	{
		EffectDataValue.Hue = _Value;
	}
	// 색조 더하기
	void AddHue(float _Value)
	{
		EffectDataValue.Hue += _Value;
	}

	// 채도 지정
	void SetSaturation(float _Value)
	{
		EffectDataValue.Saturation = _Value;
	}
	// 채도 더하기
	void AddSaturation(float _Value)
	{
		EffectDataValue.Saturation += _Value;
	}

	// 밝기 지정
	void SetBrightness(float _Value)
	{
		EffectDataValue.Brightness = _Value;
	}
	// 밝기 더하기
	void AddBrightness(float _Value)
	{
		EffectDataValue.Brightness += _Value;
	}

	// 불투명도 지정
	void SetOpacity(float _Value)
	{
		EffectDataValue.Opacity = _Value;
	}
	// 불투명도 더하기
	void AddOpacity(float _Value)
	{
		EffectDataValue.Opacity += _Value;
	}


protected:
	void Start() override;
private:
	struct EffectData
	{
		float4 Scale;
		float4 LerpColor = float4::Null;
		float LerpT = 0.0f;
		int IsBlur = false;
		float BlurLevel = 0;
		float Hue = 0.0f;			// 색조
		float Saturation = 1.0f;	// 채도
		float Brightness = 0.0f;	// 밝기
		float Opacity = 1.0f;		// 불투명도
		float None;
	};
	EffectData EffectDataValue;
};

