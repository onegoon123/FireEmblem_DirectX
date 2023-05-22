#include "PrecompileHeader.h"
#include "UICursor.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
UICursor::UICursor() 
{
}

UICursor::~UICursor() 
{
}

void UICursor::Start()
{
	CursorRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	CursorRender->GetTransform()->SetWorldScale({ 64, 64 });
	CursorRender->SetTexture("CommandCursor.png");

	Off();
}

float AnimTimer = 0;
void UICursor::Update(float _DeltaTime)
{
	AnimTimer += _DeltaTime * 5;
	if (2 < AnimTimer)
	{
		AnimTimer = 0;
	}
	if (1 < AnimTimer)
	{
		CursorRender->GetTransform()->SetLocalPosition(float4::Lerp({ -16, 0, 0}, float4::Zero, AnimTimer - 1.0f));
	}
	else
	{
		CursorRender->GetTransform()->SetLocalPosition(float4::Lerp(float4::Zero, { -16, 0, 0}, AnimTimer));
	}
}

