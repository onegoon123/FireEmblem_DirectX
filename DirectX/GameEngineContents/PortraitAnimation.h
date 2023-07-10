#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "ContentsEnum.h"
class PortraitAnimation : public GameEngineComponent
{
public:
	// constructer destructer
	PortraitAnimation();
	~PortraitAnimation();

	// delete Function
	PortraitAnimation(const PortraitAnimation& _Other) = delete;
	PortraitAnimation(PortraitAnimation&& _Other) = delete;
	PortraitAnimation& operator=(const PortraitAnimation& _Other) = delete;
	PortraitAnimation& operator=(PortraitAnimation&& _Other) = delete;

	void SetTexture(const std::string_view& _Texture);
	void SetPortrait(UnitIdentityCode _Value);
	void SetLipAnimation(float _Time);
	void SetFadeIn(float _Timer);
	void SetFadeOut(float _Timer);
	void SetLerpPos(const float4& _Pos, float _Time);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void LerpUpdate(float _DeltaTime);
	void FadeUpdate(float _DeltaTime);

	std::shared_ptr<class GameEngineUIRenderer> PortraitRender;
	std::shared_ptr<class GameEngineUIRenderer> LipRender;
	float Timer = 0;
	float4 LerpStartPos;
	float4 LerpEndPos;
	float LerpSpeed = 0;
	float LerpTimer = 0;
	float FadeTimer = 0;
	float FadeSpeed = 0;
	bool IsLerp = false;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

