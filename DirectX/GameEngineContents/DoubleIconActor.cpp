#include "PrecompileHeader.h"
#include "DoubleIconActor.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
DoubleIconActor::DoubleIconActor() 
{
}

DoubleIconActor::~DoubleIconActor() 
{
}

void DoubleIconActor::On()
{
	GameEngineActor::On();
	Renderer->ColorOptionValue.MulColor.a = 1.0f;
	Minus = false;
}
void DoubleIconActor::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIText);
	Renderer->SetTexture("DoubleAttack.png");
	Renderer->GetTransform()->SetLocalScale({ 52, 40 });
}

void DoubleIconActor::Update(float _DeltaTime)
{
	if (true == Minus)
	{
		Renderer->ColorOptionValue.MulColor.a -= _DeltaTime;
		if (0.3f > Renderer->ColorOptionValue.MulColor.a)
		{
			Renderer->ColorOptionValue.MulColor.a = 0.3f;
			Minus = false;
		}
		return;
	}

	Renderer->ColorOptionValue.MulColor.a += _DeltaTime;
	if (1.5f < Renderer->ColorOptionValue.MulColor.a)
	{
		Renderer->ColorOptionValue.MulColor.a = 1.0f;
		Minus = true;
	}
	
}

