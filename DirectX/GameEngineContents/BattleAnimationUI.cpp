#include "PrecompileHeader.h"
#include "BattleAnimationUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "Unit.h"
#include "NumberActor.h"
#include "BattleHPBar.h"
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

void BattleAnimationUI::SetData(Unit& _Unit1, Unit& _Unit2)
{
	Unit& Player = _Unit1.GetIsPlayer() == true ? _Unit1 : _Unit2;
	Unit& Enemy = _Unit2.GetIsPlayer() == true ? _Unit1 : _Unit2;

	PlayerHPBar->SetMaxHP(Player.GetMaxHP());
	PlayerHPBar->SetCurrentHP(Player.GetHP());

	Number_PlayerHP->SetValue(Player.GetHP());
	Number_PlayerDamage->SetValue(Player.GetAttackPoint(Enemy));
	Number_PlayerHit->SetValue(Player.GetHitPoint(Enemy));
	Number_PlayerCritical->SetValue(Player.GetCriticalPoint(Enemy));

	EnemyHPBar->SetMaxHP(Enemy.GetMaxHP());
	EnemyHPBar->SetCurrentHP(Enemy.GetHP());

	Number_EnemyHP->SetValue(Enemy.GetHP());
	Number_EnemyDamage->SetValue(Enemy.GetAttackPoint(Player));
	Number_EnemyHit->SetValue(Enemy.GetHitPoint(Player));
	Number_EnemyCritical->SetValue(Enemy.GetCriticalPoint(Player));
}

void BattleAnimationUI::SetDamage(Unit& _Unit)
{
	if (true == _Unit.GetIsPlayer())
	{
		Number_PlayerHP->SetValue(_Unit.GetHP());
		PlayerHPBar->SetHPAnimation(_Unit.GetHP());
	}
	else
	{
		Number_EnemyHP->SetValue(_Unit.GetHP());
		EnemyHPBar->SetHPAnimation(_Unit.GetHP());
	}
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

	PlayerHPBar = GetLevel()->CreateActor<BattleHPBar>();
	PlayerHPBar->GetTransform()->SetParent(GetTransform());
	PlayerHPBar->GetTransform()->SetLocalPosition({ -324, -272 });
	PlayerHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	PlayerHPBar->GetTransform()->SetWorldScale(float4::One);

	EnemyHPBar = GetLevel()->CreateActor<BattleHPBar>();
	EnemyHPBar->GetTransform()->SetParent(GetTransform());
	EnemyHPBar->GetTransform()->SetLocalPosition({ 164, -272 });
	EnemyHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	EnemyHPBar->GetTransform()->SetWorldScale(float4::One);

	Number_PlayerHP = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerHP->SetDamageFont();
	Number_PlayerHP->GetTransform()->SetParent(GetTransform());
	Number_PlayerHP->GetTransform()->SetLocalPosition({ -360, -272 });
	Number_PlayerHP->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerHP->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyHP = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyHP->SetDamageFont();
	Number_EnemyHP->GetTransform()->SetParent(GetTransform());
	Number_EnemyHP->GetTransform()->SetLocalPosition({ 128, -272 });
	Number_EnemyHP->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyHP->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_PlayerDamage = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerDamage->SetDamageFont();
	Number_PlayerDamage->GetTransform()->SetParent(GetTransform());
	Number_PlayerDamage->GetTransform()->SetLocalPosition({ -341, -144 });
	Number_PlayerDamage->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerDamage->GetTransform()->SetWorldScale({1, 0.8f});

	Number_PlayerHit = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerHit->SetDamageFont();
	Number_PlayerHit->GetTransform()->SetParent(GetTransform());
	Number_PlayerHit->GetTransform()->SetLocalPosition({ -341, -176 });
	Number_PlayerHit->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerHit->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_PlayerCritical = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerCritical->SetDamageFont();
	Number_PlayerCritical->GetTransform()->SetParent(GetTransform());
	Number_PlayerCritical->GetTransform()->SetLocalPosition({ -341, -208 });
	Number_PlayerCritical->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerCritical->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyDamage = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyDamage->SetDamageFont();
	Number_EnemyDamage->GetTransform()->SetParent(GetTransform());
	Number_EnemyDamage->GetTransform()->SetLocalPosition({ 456, -144 });
	Number_EnemyDamage->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyDamage->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyHit = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyHit->SetDamageFont();
	Number_EnemyHit->GetTransform()->SetParent(GetTransform());
	Number_EnemyHit->GetTransform()->SetLocalPosition({ 456, -176 });
	Number_EnemyHit->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyHit->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyCritical = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyCritical->SetDamageFont();
	Number_EnemyCritical->GetTransform()->SetParent(GetTransform());
	Number_EnemyCritical->GetTransform()->SetLocalPosition({ 456, -208 });
	Number_EnemyCritical->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyCritical->GetTransform()->SetWorldScale({ 1, 0.8f });
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

