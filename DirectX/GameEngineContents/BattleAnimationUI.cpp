#include "PrecompileHeader.h"
#include "BattleAnimationUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
BattleAnimationUI::BattleAnimationUI() 
{
}

BattleAnimationUI::~BattleAnimationUI() 
{
}

void BattleAnimationUI::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	FadeRenderer->ColorOptionValue.MulColor.a = 1;
}

void BattleAnimationUI::SetFadeOut(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
}


void BattleAnimationUI::Start()
{
	UIRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	UIRenderer->SetTexture("BattleUI.png");
	UIRenderer->GetTransform()->SetLocalScale({ 1024, 640 });

	FadeRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
	FadeRenderer->SetTexture("Black.png");
	FadeRenderer->GetTransform()->SetLocalScale({ 960, 640 });
	FadeRenderer->SetOrder(100);

}

void BattleAnimationUI::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeIn = false;
			FadeRenderer->ColorOptionValue.MulColor.a = 0;
			return;
		}
		FadeRenderer->ColorOptionValue.MulColor.a = FadeTimer;
	}

	if (true == IsFadeOut)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeOut = false;
			FadeRenderer->ColorOptionValue.MulColor.a = 1;
			return;
		}
		FadeRenderer->ColorOptionValue.MulColor.a = FadeTimer;
	}
}

