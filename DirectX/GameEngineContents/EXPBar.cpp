#include "PrecompileHeader.h"
#include "EXPBar.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "NumberActor.h"
#include "ContentsEnum.h"
EXPBar::EXPBar() 
{
}

EXPBar::~EXPBar() 
{
}

void EXPBar::SetEXP(int _EXP)
{
	CurEXP = _EXP;
	Number->SetValue(CurEXP);
}

void EXPBar::AddEXP(int _EXP, std::function<void()> _EndEvent)
{
	if (nullptr != _EndEvent)
	{
		EndEvent = _EndEvent;
	}

	Number->StopLerp();
	Number->SetValue(CurEXP);

	PlusEXP = _EXP;

	BeforeEXP = CurEXP;

	IsLevelUp = 100 <= CurEXP + PlusEXP;
	if (true == IsLevelUp)
	{
		TargetEXP = 100;
		PlusEXP -= 100 - CurEXP;
		CurEXP = 0;
		Number->SetValueLerp(100);
	}
	else
	{
		TargetEXP = (CurEXP + PlusEXP);
		CurEXP += PlusEXP;
		PlusEXP = 0;
		Number->SetValueLerp(CurEXP);
	}

	IsLerp = true;
	Timer = 0;

}

void EXPBar::Start()
{
	if (nullptr == GameEngineSprite::Find("EXPBar.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("EXPBar.png").GetFullPath(), 3, 1);
	}

	Background = CreateComponent<GameEngineUIRenderer>(9);
	Background->SetTexture("EXPBackground.png");
	Background->GetTransform()->SetLocalScale({ 576, 96 });

	BarLeft = CreateComponent< GameEngineUIRenderer>(10);
	BarLeft->SetSprite("EXPBar.png", 0);
	BarLeft->GetTransform()->SetLocalPosition({ -244, -2 });
	BarLeft->GetTransform()->SetLocalScale({ 12, 28 });

	BarCenter = CreateComponent< GameEngineUIRenderer>(10);
	BarCenter->SetSprite("EXPBar.png", 1);
	BarCenter->GetTransform()->SetLocalPosition({ -238 + 200, -2 });
	BarCenter->GetTransform()->SetLocalScale({ 400, 28 });

	BarRight = CreateComponent< GameEngineUIRenderer>(10);
	BarRight->SetSprite("EXPBar.png", 2);
	BarRight->GetTransform()->SetLocalPosition({ -238 + 400, -2 });
	BarRight->GetTransform()->SetLocalScale({ 12, 28 });
	
	Number = GetLevel()->CreateActor<NumberActor>();
	Number->SetDamageFont();
	Number->SetTime(0.005f);
	Number->GetTransform()->SetParent(GetTransform());
	Number->GetTransform()->SetLocalPosition({ 224, 0 });

	SetEXP(0);
	SetEXPBar(0);
}

void EXPBar::Update(float _DeltaTime)
{
	if (false == IsLerp) { return; }

	Timer += _DeltaTime;
	if (Time < Timer)
	{
		if (TargetEXP == ++BeforeEXP)
		{
			IsLerp = false;
			if (true == IsLevelUp)
			{
				if (PlusEXP == 0)
				{
					SetEXPBar(0);
					Number->Setting(0);
					EndEvent();
					return;
				}
				AddEXP(PlusEXP);
			}
			else if (nullptr != EndEvent)
			{
				EndEvent();
			}
		}
		SetEXPBar(BeforeEXP);
		Timer = 0;
	}
}

void EXPBar::SetEXPBar(int _Value)
{
	BarCenter->GetTransform()->SetLocalPosition({ -238 + (1.94f * _Value), -2 });
	BarCenter->GetTransform()->SetLocalScale({ (3.88f * _Value), 28 });

	BarRight->GetTransform()->SetLocalPosition({ -238 + (3.88f * _Value), -2 });
	BarRight->GetTransform()->SetLocalScale({ 12, 28 });
}

