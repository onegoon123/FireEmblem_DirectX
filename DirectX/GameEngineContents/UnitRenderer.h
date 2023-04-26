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


protected:
	void Start() override;
private:
	struct EffectData
	{
		float4 FlashColor = float4::Zero;
		float t = 0;
		float a = 0;
		float b = 0;
		int IsGrayScale = false;
	};
	EffectData EffectDataValue;
};

