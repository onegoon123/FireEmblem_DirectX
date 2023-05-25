#include "PrecompileHeader.h"
#include "BattleHPBar.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
BattleHPBar::BattleHPBar() 
{
	Renders.reserve(50);
}

BattleHPBar::~BattleHPBar() 
{
}

void BattleHPBar::SetMaxHP(int _Value)
{
	
	if (Renders.size() < _Value)
	{
		for (int i = 0; i < Renders.size(); i++)
		{
			Renders[i]->On();
		}
		Renders.resize(_Value);
		for (int i = MaxHP; i < _Value; i++)
		{
			Renders[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
			Renders[i]->SetSprite("BattleHPBar.png", 0);
			Renders[i]->GetTransform()->SetLocalPosition({ 8.0f * i, 0});
			Renders[i]->GetTransform()->SetLocalScale({ 12, 24 });
		}
	}
	else
	{
		for (int i = 0; i < _Value; i++)
		{
			Renders[i]->On();
		}
		for (int i = _Value; i < Renders.size(); i++)
		{
			Renders[i]->Off();
		}
	}
	MaxHP = _Value;
}

void BattleHPBar::SetCurrentHP(int _Value)
{
	CurrentHP = _Value;
	if (MaxHP < CurrentHP)
	{
		MsgAssert("최대체력 보다 높은 체력이 지정되었습니다.");
		return;
	}
	for (int i = 0; i < CurrentHP; i++)
	{
		Renders[i]->SetFrame(1);
	}
	for (int i = CurrentHP; i < MaxHP; i++)
	{
		Renders[i]->SetFrame(0);
	}
}

void BattleHPBar::SetHPAnimation(int _Value)
{
}

void BattleHPBar::Start()
{
	if (nullptr == GameEngineSprite::Find("BattleHPBar.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("BattleHPBar.png").GetFullPath(), 2, 1);
	}
}

void BattleHPBar::Update(float _DeltaTime)
{
}

