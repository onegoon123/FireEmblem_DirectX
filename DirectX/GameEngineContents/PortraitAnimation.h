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

	void SetPortrait(UnitIdentityCode _Value);
	void SetLipAnimation(float _Time);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineUIRenderer> PortraitRender;
	std::shared_ptr<class GameEngineUIRenderer> LipRender;
	float Timer = 0;
};

