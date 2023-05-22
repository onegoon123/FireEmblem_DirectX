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
	CursorRender->GetTransform()->SetLocalPosition({ 448, 288, 0 });
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
		CursorRender->GetTransform()->SetLocalPosition(float4::Lerp({ -16 + 448, 0  + 288}, { 448, 288, 0 }, AnimTimer - 1.0f));
	}
	else
	{
		CursorRender->GetTransform()->SetLocalPosition(float4::Lerp({ 448, 288, 0 }, { -16 + 448, 0 + 288}, AnimTimer));
	}
}

