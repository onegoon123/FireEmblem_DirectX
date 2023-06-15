#include "PrecompileHeader.h"
#include "BattleHPBar.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
BattleHPBar::BattleHPBar()
{
}

BattleHPBar::~BattleHPBar()
{
}

void BattleHPBar::Setting(int _HP, int _MaxHP)
{
	IsLerp = false;
	SetMaxHP(_MaxHP);
	SetCurrentHP(_HP);
}

void BattleHPBar::SetMaxHP(int _Value)
{

	for (int i = 0; i < _Value; i++)
	{
		Renders[i]->On();
	}
	for (int i = _Value; i < Renders.size(); i++)
	{
		Renders[i]->Off();
	}
	MaxHP = _Value;

	// 최대체력이 30이상일시 두 줄로 표시
	if (30 < MaxHP)
	{
		for (int i = 0; i < 30; i++)
		{
			Renders[i]->GetTransform()->SetLocalPosition({ 8.0f * i, 12 });
		}
		for (int i = 30; i < MaxHP; i++)
		{
			Renders[i]->GetTransform()->SetLocalPosition({ 8.0f * (i - 30), -12 });
		}
	}
	else
	{
		for (int i = 0; i < MaxHP; i++)
		{
			Renders[i]->GetTransform()->SetLocalPosition({ 8.0f * i, 0 });
		}
	}
}

void BattleHPBar::SetCurrentHP(int _Value)
{
	HP = _Value;

	if (MaxHP < _Value)
	{
		MsgAssert("최대체력 보다 높은 체력이 지정되었습니다.");
		return;
	}
	for (int i = 0; i < _Value; i++)
	{
		Renders[i]->SetFrame(1);
	}
	for (int i = _Value; i < MaxHP; i++)
	{
		Renders[i]->SetFrame(0);
	}
}

void BattleHPBar::SetHPAnimation(int _Value)
{
	if (HP == _Value) { return; }
	IsPlus = _Value > HP;
	TargetHP = _Value;
	Timer = Time;
	IsLerp = true;
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

	Renders.resize(60);
	for (int i = MaxHP; i < 60; i++)
	{
		Renders[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Renders[i]->SetSprite("BattleHPBar.png", 0);
		Renders[i]->GetTransform()->SetLocalPosition({ 8.0f * i, 0 });
		Renders[i]->GetTransform()->SetLocalScale({ 12, 24 });
		Renders[i]->Off();
	}
}

void BattleHPBar::Update(float _DeltaTime)
{
	if (false == IsLerp) { return; }

	Timer -= _DeltaTime;
	if (Timer < 0)
	{
		if (TargetHP == HP)
		{
			IsLerp = false;
			return;
		}
		SetCurrentHP(HP + (IsPlus ? 1 : -1));
		if (TargetHP == HP)
		{
			IsLerp = false;
			return;
		}
		Timer = Time;
	}
}

