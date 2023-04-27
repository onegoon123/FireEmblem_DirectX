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
	};
	EffectData EffectDataValue;
};

