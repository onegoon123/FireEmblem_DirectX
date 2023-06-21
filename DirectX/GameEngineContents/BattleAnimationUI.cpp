#include "PrecompileHeader.h"
#include "BattleAnimationUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "BattleAnimationLevel.h"
#include "Unit.h"
#include "NumberActor.h"
#include "BattleHPBar.h"
#include "EXPBar.h"
#include "LevelUpUI.h"
#include "TextRenderer.h"
#include "BattleUnit.h"
BattleAnimationUI::BattleAnimationUI()
{
}

BattleAnimationUI::~BattleAnimationUI()
{
}

void BattleAnimationUI::SetClassChange()
{
	UIRenderer->Off();
	PlayerHPBar->Off();
	EnemyHPBar->Off();
	Number_PlayerHP->Off();
	Number_PlayerDamage->Off();
	Number_PlayerHit->Off();
	Number_PlayerCritical->Off();
	Number_EnemyHP->Off();
	Number_EnemyDamage->Off();
	Number_EnemyHit->Off();
	Number_EnemyCritical->Off();
	PlayerWeaponIcon->Off();
	EnemyWeaponIcon->Off();
	PlayerTriangle->Off();
	EnemyTriangle->Off();

	EXPUI->Off();
	LevelUI->Off();
	WaitTimer = 0;
	IsFadeIn = false;
	IsFadeOut = false;
	FadeRenderer->On();
	Text_PlayerName->Off();
	Text_PlayerWeaponName->Off();
	Text_EnemyName->Off();
	Text_EnemyWeaponName->Off();
}

void BattleAnimationUI::SetDefault()
{
	UIRenderer->On();
	PlayerHPBar->On();
	EnemyHPBar->On();
	Number_PlayerHP->On();
	Number_PlayerDamage->On();
	Number_PlayerHit->On();
	Number_PlayerCritical->On();
	Number_EnemyHP->On();
	Number_EnemyDamage->On();
	Number_EnemyHit->On();
	Number_EnemyCritical->On();
	PlayerWeaponIcon->On();
	EnemyWeaponIcon->On();
	PlayerTriangle->On();
	EnemyTriangle->On();
	WaitTimer = 0;
	IsFadeIn = false;
	IsFadeOut = false;
	FadeRenderer->Off();
	FadeRenderer->ColorOptionValue.PlusColor = float4::Null;
	Text_PlayerName->On();
	Text_PlayerWeaponName->On();
	Text_EnemyName->On();
	Text_EnemyWeaponName->On();
}

void BattleAnimationUI::SetFadeWhite()
{
	FadeRenderer->ColorOptionValue.PlusColor = float4(1.0f, 1.0f, 1.0f, 0.0f);
}

void BattleAnimationUI::SetFadeWait(float _Timer)
{
	WaitTimer = _Timer;
}

void BattleAnimationUI::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	IsFadeOut = false;
	FadeRenderer->ColorOptionValue.MulColor.a = 1;
}

void BattleAnimationUI::SetFadeOut(float _Timer)
{
	WaitTimer = 0;
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	IsFadeIn = false;
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
}

void BattleAnimationUI::SetData(std::shared_ptr<BattleUnit> _Unit1, std::shared_ptr<BattleUnit> _Unit2, bool _Unit1Attackable, bool _Unit2Attackable)
{
	std::shared_ptr<BattleUnit> PlayerBattleUnit = _Unit1->GetUnitData().GetIsPlayer() == true ? _Unit1 : _Unit2;
	std::shared_ptr<BattleUnit> EnemyBattleUnit = _Unit1->GetUnitData().GetIsPlayer() == false ? _Unit1 : _Unit2;
	Unit& Player = PlayerBattleUnit->GetUnitData();
	Unit& Enemy = EnemyBattleUnit->GetUnitData();
	UnitName = PlayerBattleUnit->GetName();
	PlayerData = Player;
	PlayerHPBar->Setting(Player.GetHP(), Player.GetMaxHP());

	Text_PlayerName->SetText(PlayerBattleUnit->GetName());
	Text_EnemyName->SetText(EnemyBattleUnit->GetName());
	Text_PlayerWeaponName->SetText(Player.GetCurWeapon()->GetName());
	Text_EnemyWeaponName->SetText(Enemy.GetCurWeapon()->GetName());

	Number_PlayerHP->Setting(Player.GetHP());

	if (true == _Unit1Attackable)
	{
		Number_PlayerDamage->SetValue(Player.GetAttackPoint(Enemy));
		Number_PlayerHit->SetValue(Player.GetHitPoint(Enemy));
		Number_PlayerCritical->SetValue(Player.GetCriticalPoint(Enemy));
	}
	else
	{
		Number_PlayerDamage->SetValue(0);
		Number_PlayerHit->SetValue(0);
		Number_PlayerCritical->SetValue(0);
	}
	EnemyHPBar->Setting(Enemy.GetHP(), Enemy.GetMaxHP());

	Number_EnemyHP->Setting(Enemy.GetHP());
	if (true == _Unit2Attackable)
	{
		Number_EnemyDamage->SetValue(Enemy.GetAttackPoint(Player));
		Number_EnemyHit->SetValue(Enemy.GetHitPoint(Player));
		Number_EnemyCritical->SetValue(Enemy.GetCriticalPoint(Player));
	}
	else
	{
		Number_EnemyDamage->SetValue(0);
		Number_EnemyHit->SetValue(0);
		Number_EnemyCritical->SetValue(0);
	}

	if (nullptr == Player.GetCurWeapon())
	{
		PlayerWeaponIcon->Off();
	}
	else
	{
		PlayerWeaponIcon->On();
		PlayerWeaponIcon->SetFrame(Player.GetCurWeapon()->GetItemCodeToInt() - 1);
	}
	if (nullptr == Enemy.GetCurWeapon())
	{
		EnemyWeaponIcon->Off();
	}
	else
	{
		EnemyWeaponIcon->On();
		EnemyWeaponIcon->SetFrame(Enemy.GetCurWeapon()->GetItemCodeToInt() - 1);
	}

	// 무기 상성 값
	int TriangleValue = Weapon::GetWeaponeTriangle(Player.GetCurWeapon(), Enemy.GetCurWeapon());
	switch (TriangleValue)
	{
	case 0:
		PlayerTriangle->Off();
		EnemyTriangle->Off();
		break;
	case 1:
		PlayerTriangle->On();
		PlayerTriangle->ChangeAnimation("Advantage");
		EnemyTriangle->On();
		EnemyTriangle->ChangeAnimation("Disadvantage");
		break;
	case -1:
		PlayerTriangle->On();
		PlayerTriangle->ChangeAnimation("Disadvantage");
		EnemyTriangle->On();
		EnemyTriangle->ChangeAnimation("Advantage");
		break;
	default:
		break;
	}

	EXPUI->Off();
	EXPUI->SetEXP(Player.GetExp());

	LevelUI->Off();
}

void BattleAnimationUI::SetDataHeal(std::shared_ptr<BattleUnit> _Unit1, std::shared_ptr<BattleUnit> _Unit2)
{
	Unit& Player = _Unit1->GetUnitData();
	Unit& Enemy = _Unit2->GetUnitData();
	UnitName = _Unit1->GetName();
	PlayerData = Player;
	PlayerHPBar->Setting(Player.GetHP(), Player.GetMaxHP());

	Text_PlayerName->SetText(_Unit1->GetName());
	Text_EnemyName->SetText(_Unit2->GetName());
	Text_PlayerWeaponName->SetText("라이브");
	Text_EnemyWeaponName->SetText("");

	Number_PlayerHP->Setting(Player.GetHP());


	Number_PlayerDamage->SetValue(Player.GetMainStat().Magic + 10);
	Number_PlayerHit->SetValue(100);
	Number_PlayerCritical->SetValue(0);

	EnemyHPBar->Setting(Enemy.GetHP(), Enemy.GetMaxHP());

	Number_EnemyHP->Setting(Enemy.GetHP());

	Number_EnemyDamage->SetValue(0);
	Number_EnemyHit->SetValue(0);
	Number_EnemyCritical->SetValue(0);


	PlayerWeaponIcon->On();
	PlayerWeaponIcon->SetFrame(21);
	EnemyWeaponIcon->Off();

	PlayerTriangle->Off();
	EnemyTriangle->Off();


	EXPUI->Off();
	EXPUI->SetEXP(Player.GetExp());

	LevelUI->Off();
}

void BattleAnimationUI::SetDamage(Unit& _Unit)
{
	if (PlayerData.GetIdentityCode() == _Unit.GetIdentityCode())
	{
		Number_PlayerHP->SetValueLerp(_Unit.GetHP());
		PlayerHPBar->SetHPAnimation(_Unit.GetHP());
	}
	else
	{
		Number_EnemyHP->SetValueLerp(_Unit.GetHP());
		EnemyHPBar->SetHPAnimation(_Unit.GetHP());
	}
}

void BattleAnimationUI::SetEXP(int _Before, int _Get, Unit& _UnitData)
{
	PlayerData = _UnitData;
	EXPUI->SetEXP(_Before);
	EXPUI->AddEXP(_Get, [this] {
		TimeEvent->AddEvent(1.0f, std::bind(&BattleAnimationUI::EndExpUI, this));
		});
	EXPUI->On();
	IsLevelUp = 100 <= _Before + _Get;
}

void BattleAnimationUI::LevelUpStart(Unit& _UnitData)
{
	LevelUI->LevelUpStart(_UnitData, UnitName);
}

void BattleAnimationUI::ClassChangeStart(Unit& _UnitData, const std::string_view& _Name)
{
	LevelUI->ClassChangeStart(_UnitData, _Name);
}

bool BattleAnimationUI::IsTurnEnd()
{
	return false == PlayerHPBar->GetIsLerp() && false == Number_PlayerHP->GetIsLerp() && false == EnemyHPBar->GetIsLerp() && false == Number_EnemyHP->GetIsLerp();
}


void BattleAnimationUI::Start()
{
	CurLevel = dynamic_cast<BattleAnimationLevel*>(GetLevel());
	TimeEvent = &CurLevel->TimeEvent;

	UIRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	UIRenderer->SetTexture("BattleUI.png");
	UIRenderer->GetTransform()->SetLocalScale({ 1024, 640 });

	FadeRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
	FadeRenderer->SetTexture("Black.png");
	FadeRenderer->GetTransform()->SetLocalScale({ 960, 640 });

	PlayerHPBar = CurLevel->CreateActor<BattleHPBar>();
	PlayerHPBar->GetTransform()->SetParent(GetTransform());
	PlayerHPBar->GetTransform()->SetLocalPosition({ -324, -272 });
	PlayerHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	PlayerHPBar->GetTransform()->SetWorldScale(float4::One);

	EnemyHPBar = CurLevel->CreateActor<BattleHPBar>();
	EnemyHPBar->GetTransform()->SetParent(GetTransform());
	EnemyHPBar->GetTransform()->SetLocalPosition({ 164, -272 });
	EnemyHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	EnemyHPBar->GetTransform()->SetWorldScale(float4::One);

	Text_PlayerName = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_PlayerName->GetTransform()->SetLocalPosition({ -384, 282 });
	Text_PlayerName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	Text_EnemyName = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_EnemyName->GetTransform()->SetLocalPosition({ 384, 282 });
	Text_EnemyName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	Text_PlayerWeaponName = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_PlayerWeaponName->GetTransform()->SetLocalPosition({ -132, -178 });
	Text_PlayerWeaponName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	Text_EnemyWeaponName = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_EnemyWeaponName->GetTransform()->SetLocalPosition({ 172, -178 });
	Text_EnemyWeaponName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	Number_PlayerHP = CurLevel->CreateActor<NumberActor>();
	Number_PlayerHP->SetDamageFont();
	Number_PlayerHP->GetTransform()->SetParent(GetTransform());
	Number_PlayerHP->GetTransform()->SetLocalPosition({ -360, -272 });
	Number_PlayerHP->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_EnemyHP = CurLevel->CreateActor<NumberActor>();
	Number_EnemyHP->SetDamageFont();
	Number_EnemyHP->GetTransform()->SetParent(GetTransform());
	Number_EnemyHP->GetTransform()->SetLocalPosition({ 128, -272 });
	Number_EnemyHP->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_PlayerDamage = CurLevel->CreateActor<NumberActor>();
	Number_PlayerDamage->SetDamageFont();
	Number_PlayerDamage->GetTransform()->SetParent(GetTransform());
	Number_PlayerDamage->GetTransform()->SetLocalPosition({ -341, -144 });
	Number_PlayerDamage->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_PlayerHit = CurLevel->CreateActor<NumberActor>();
	Number_PlayerHit->SetDamageFont();
	Number_PlayerHit->GetTransform()->SetParent(GetTransform());
	Number_PlayerHit->GetTransform()->SetLocalPosition({ -341, -176 });
	Number_PlayerHit->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_PlayerCritical = CurLevel->CreateActor<NumberActor>();
	Number_PlayerCritical->SetDamageFont();
	Number_PlayerCritical->GetTransform()->SetParent(GetTransform());
	Number_PlayerCritical->GetTransform()->SetLocalPosition({ -341, -208 });
	Number_PlayerCritical->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_EnemyDamage = CurLevel->CreateActor<NumberActor>();
	Number_EnemyDamage->SetDamageFont();
	Number_EnemyDamage->GetTransform()->SetParent(GetTransform());
	Number_EnemyDamage->GetTransform()->SetLocalPosition({ 456, -144 });
	Number_EnemyDamage->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_EnemyHit = CurLevel->CreateActor<NumberActor>();
	Number_EnemyHit->SetDamageFont();
	Number_EnemyHit->GetTransform()->SetParent(GetTransform());
	Number_EnemyHit->GetTransform()->SetLocalPosition({ 456, -176 });
	Number_EnemyHit->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	Number_EnemyCritical = CurLevel->CreateActor<NumberActor>();
	Number_EnemyCritical->SetDamageFont();
	Number_EnemyCritical->GetTransform()->SetParent(GetTransform());
	Number_EnemyCritical->GetTransform()->SetLocalPosition({ 456, -208 });
	Number_EnemyCritical->GetTransform()->SetLocalScale({ 1, 0.8f, 1 });

	PlayerWeaponIcon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	PlayerWeaponIcon->GetTransform()->SetLocalPosition({ -272, -200 });
	PlayerWeaponIcon->GetTransform()->SetLocalScale({ 64, 64, 1 });
	PlayerWeaponIcon->SetSprite("Items.png", 0);

	EnemyWeaponIcon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	EnemyWeaponIcon->GetTransform()->SetLocalPosition({ 48, -200 });
	EnemyWeaponIcon->GetTransform()->SetLocalScale({ 64, 64 ,1 });
	EnemyWeaponIcon->SetSprite("Items.png", 0);

	// 무기 상성 이미지
	PlayerTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	PlayerTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
	PlayerTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
	PlayerTriangle->ChangeAnimation("Advantage");
	PlayerTriangle->GetTransform()->SetLocalPosition({ -248, -214 });
	PlayerTriangle->GetTransform()->SetLocalScale({ 28, 40,1 });

	EnemyTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	EnemyTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
	EnemyTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
	EnemyTriangle->ChangeAnimation("Advantage");
	EnemyTriangle->GetTransform()->SetLocalPosition({ 72, -214 });
	EnemyTriangle->GetTransform()->SetLocalScale({ 28, 40,1 });

	EXPUI = CurLevel->CreateActor<EXPBar>();
	EXPUI->GetTransform()->SetParent(GetTransform());
	EXPUI->GetTransform()->SetLocalPosition({ 0, -108 });
	EXPUI->Off();

	LevelUI = CurLevel->CreateActor<LevelUpUI>();
	LevelUI->GetTransform()->SetParent(GetTransform());
	LevelUI->Off();

}

void BattleAnimationUI::Update(float _DeltaTime)
{
	if (0 < WaitTimer)
	{
		WaitTimer -= _DeltaTime;
		return;
	}
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

void BattleAnimationUI::EndExpUI()
{
	if (true == IsLevelUp)
	{
		LevelUI->LevelUpStart(PlayerData, UnitName);
	}
}

