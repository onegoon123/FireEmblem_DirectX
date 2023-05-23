#include "PrecompileHeader.h"
#include "NumberActor.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
NumberActor::NumberActor() 
{
}

NumberActor::~NumberActor() 
{
}

void NumberActor::SetValue(int _Value)
{
	int i = 0;
	while (0 < _Value)
	{
		int Num = _Value % 10;
		_Value /= 10;
		Renders[i]->SetFrame(Num);
		Renders[i]->On();
		i++;
	}
	for (; i < Renders.size(); i++)
	{
		Renders[i]->Off();
	}
}

void NumberActor::Start()
{
	if (nullptr == GameEngineSprite::Find("NumFont.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("NumFont.png").GetFullPath(), 10, 1);
	}

	Renders.resize(3);
	for (int i = 0; i < 3; i++)
	{
		Renders[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIText);
		Renders[i]->SetSprite("NumFont.png", 0);
		Renders[i]->GetTransform()->SetLocalScale({ 32, 40 });
		Renders[i]->GetTransform()->SetLocalPosition({ -32.0f * i, 0});
	}
}

