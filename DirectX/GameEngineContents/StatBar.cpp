#include "PrecompileHeader.h"
#include "StatBar.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
StatBar::StatBar() 
{
}

StatBar::~StatBar() 
{
}

void StatBar::SetSize(float _Value)
{
	Center->GetTransform()->SetLocalPosition({ 4.0f + _Value * 0.5f, 0 });
	Center->GetTransform()->SetLocalScale({ _Value, 20 });

	Right->GetTransform()->SetLocalPosition({ Center->GetTransform()->GetLocalScale().x + 4, 0 });
}

void StatBar::SetValue(float _Value)
{
	float4 Scale = Center->GetTransform()->GetLocalScale();
	Scale.x *= _Value;
	Fill->GetTransform()->SetLocalScale(Scale);
	Fill->GetTransform()->SetLocalPosition({ 4.0f + Fill->GetTransform()->GetLocalScale().x * 0.5f, 0 });
}

void StatBar::Start()
{
	if (nullptr == GameEngineSprite::Find("StatSlider.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		Dir.Move("UnitInfo");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("StatSlider.png").GetFullPath(), 4, 1);
	}

	Left = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Left->SetSprite("StatSlider.png", 0);
	Left->GetTransform()->SetLocalScale({ 8, 20 });

	Center = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Center->SetSprite("StatSlider.png", 2);
	Center->GetTransform()->SetLocalPosition({ 8, 0 });
	Center->GetTransform()->SetLocalScale({ 8, 20 });

	Fill = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Fill->SetSprite("StatSlider.png", 1);
	Fill->GetTransform()->SetLocalPosition({ 8, 0 });
	Fill->GetTransform()->SetLocalScale({ 8, 20 });

	Right = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Right->SetSprite("StatSlider.png", 3);
	Right->GetTransform()->SetLocalPosition({ Center->GetTransform()->GetLocalScale().x + 4, 0});
	Right->GetTransform()->SetLocalScale({ 8, 20 });
}

