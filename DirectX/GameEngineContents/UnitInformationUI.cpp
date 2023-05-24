#include "PrecompileHeader.h"
#include "UnitInformationUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "BattleUnit.h"
#include "BattleLevel.h"
#include "NumberActor.h"

UnitInformationUI::UnitInformationUI()
{
}

UnitInformationUI::~UnitInformationUI()
{
}

void UnitInformationUI::SetUnit(std::shared_ptr<BattleUnit> _Unit)
{
	std::string ImageName = "Portrait_";

	if (std::string(_Unit->GetUnitData().GetName()) == "Enemy")
	{
		switch (_Unit->GetUnitData().GetClassValue())
		{
		case BattleClass::Archer:
			ImageName += "Archer.png";
			break;
		case BattleClass::Brigand:
			ImageName += "Brigand.png";
			break;
		case BattleClass::Knight:
			ImageName += "Knight.png";
			break;
		case BattleClass::Mage:
			ImageName += "Mage.png";
			break;
		case BattleClass::Mercenary:
			ImageName += "Mercenary.png";
			break;
		case BattleClass::Soldier:
			ImageName += "Soldier.png";
			break;
		default:
			break;
		}

		PortraitRenderer->GetTransform()->SetLocalPosition({ -268, 144 });
		PortraitRenderer->GetTransform()->SetLocalScale({ 320, 320 });
		PortraitBack->SetTexture("PortraitBackground_Enemy.png");
	}
	else
	{
		ImageName += _Unit->GetUnitData().GetName().data();
		ImageName += ".png";
		PortraitRenderer->GetTransform()->SetLocalPosition({ -264, 128 });
		PortraitRenderer->GetTransform()->SetLocalScale({ 384, 320 });
		PortraitBack->SetTexture("PortraitBackground.png");
	}

	PortraitRenderer->SetTexture(ImageName);
	std::shared_ptr<AnimationInfo> AnimInfo = UnitRenderer->FindAnimation(_Unit->GetMapSpriteName());
	if (nullptr == AnimInfo)
	{
		UnitRenderer->CreateAnimation({ .AnimationName = _Unit->GetMapSpriteName(), .SpriteName = _Unit->GetMapSpriteName(), .FrameIndex = {0, 1, 2, 1}, .FrameTime = {0.5f, 0.1f, 0.5f, 0.1f} });
	}
	UnitRenderer->ChangeAnimation(_Unit->GetMapSpriteName());
	Number_Level->SetValue(_Unit->GetUnitData().GetLevel());
	Number_Exp->SetValue(_Unit->GetUnitData().GetExp());
	Number_HP->SetValue(_Unit->GetUnitData().GetHP());
	Number_MaxHP->SetValue(_Unit->GetUnitData().GetMaxHP());

	MainStat StatValue = _Unit->GetUnitData().GetMainStat();
	Number_Strength->SetValue(StatValue.Strength);
	Number_Magic->SetValue(StatValue.Magic);
	Number_Dexterity->SetValue(StatValue.Dexterity);
	Number_Speed->SetValue(StatValue.Speed);
	Number_Defense->SetValue(StatValue.Defense);
	Number_Resistance->SetValue(StatValue.Resistance);
	Number_Luck->SetValue(StatValue.Luck);
	Number_Move->SetValue(_Unit->GetMoveStat());
	Number_Constitution->SetValue(StatValue.Constitution);
}

void UnitInformationUI::Start()
{
	CurLevel = dynamic_cast<BattleLevel*>(GetLevel());
	if (nullptr == CurLevel)
	{
		MsgAssert("이 UI는 BattleLevel에서만 생성 가능합니다.");
	}

	Background = CreateComponent<GameEngineUIRenderer>(0);
	Background->SetTexture("UnitInfoBackground.png");
	Background->GetTransform()->SetLocalScale({ 960, 640 });

	PortraitBack = CreateComponent<GameEngineUIRenderer>(1);
	PortraitBack->SetTexture("PortraitBackground.png");
	PortraitBack->GetTransform()->SetLocalScale({ 320, 288 });
	PortraitBack->GetTransform()->SetLocalPosition({ -264, 148 });

	Fore = CreateComponent<GameEngineUIRenderer>(5);
	Fore->SetTexture("Info1.png");
	Fore->GetTransform()->SetLocalScale({ 960, 640 });

	PersonalDataWindow = CreateComponent<GameEngineUIRenderer>(3);
	PersonalDataWindow->SetTexture("PersonalDataWindow.png");
	PersonalDataWindow->GetTransform()->SetLocalScale({ 548, 420 });
	PersonalDataWindow->GetTransform()->SetLocalPosition({ 164, 32 });

	PortraitRenderer = CreateComponent<GameEngineUIRenderer>(2);
	PortraitRenderer->GetTransform()->SetLocalScale({ 384, 320 });
	PortraitRenderer->GetTransform()->SetLocalPosition({ -264, 128 });

	UnitRenderer = CreateComponent<GameEngineUIRenderer>(6);
	UnitRenderer->GetTransform()->SetLocalScale({ 192, 192 });
	UnitRenderer->GetTransform()->SetLocalPosition({ -168, -182 });

	Number_Level = CurLevel->CreateActor<NumberActor>();
	Number_Level->GetTransform()->SetParent(GetTransform());
	Number_Level->GetTransform()->SetLocalPosition({ -364, -196 });
	Number_Level->SetValue(11);

	Number_Exp = CurLevel->CreateActor<NumberActor>();
	Number_Exp->GetTransform()->SetParent(GetTransform());
	Number_Exp->GetTransform()->SetLocalPosition({ -248, -196 });
	Number_Exp->SetValue(11);

	Number_HP = CurLevel->CreateActor<NumberActor>();
	Number_HP->GetTransform()->SetParent(GetTransform());
	Number_HP->GetTransform()->SetLocalPosition({ -364, -258 });
	Number_HP->SetValue(11);

	Number_MaxHP = CurLevel->CreateActor<NumberActor>();
	Number_MaxHP->GetTransform()->SetParent(GetTransform());
	Number_MaxHP->GetTransform()->SetLocalPosition({ -248, -258 });
	Number_MaxHP->SetValue(11);

	{
		Number_Strength = CurLevel->CreateActor<NumberActor>();
		Number_Strength->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Strength->GetTransform()->SetLocalPosition({ -100, 128 });
		Number_Strength->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Strength->GetTransform()->SetWorldScale(float4::One);
		Number_Strength->SetValue(0);

		Number_Magic = CurLevel->CreateActor<NumberActor>();
		Number_Magic->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Magic->GetTransform()->SetLocalPosition({ -100, 40 });
		Number_Magic->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Magic->GetTransform()->SetWorldScale(float4::One);
		Number_Magic->SetValue(0);

		Number_Dexterity = CurLevel->CreateActor<NumberActor>();
		Number_Dexterity->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Dexterity->GetTransform()->SetLocalPosition({ -100, -48 });
		Number_Dexterity->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Dexterity->GetTransform()->SetWorldScale(float4::One);
		Number_Dexterity->SetValue(0);

		Number_Speed = CurLevel->CreateActor<NumberActor>();
		Number_Speed->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Speed->GetTransform()->SetLocalPosition({ -100, -136 });
		Number_Speed->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Speed->GetTransform()->SetWorldScale(float4::One);
		Number_Speed->SetValue(0);

		Number_Defense = CurLevel->CreateActor<NumberActor>();
		Number_Defense->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Defense->GetTransform()->SetLocalPosition({ 152, 152 });
		Number_Defense->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Defense->GetTransform()->SetWorldScale(float4::One);
		Number_Defense->SetValue(0);

		Number_Resistance = CurLevel->CreateActor<NumberActor>();
		Number_Resistance->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Resistance->GetTransform()->SetLocalPosition({ 152, 76 });
		Number_Resistance->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Resistance->GetTransform()->SetWorldScale(float4::One);
		Number_Resistance->SetValue(0);

		Number_Luck = CurLevel->CreateActor<NumberActor>();
		Number_Luck->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Luck->GetTransform()->SetLocalPosition({ 152, 0 });
		Number_Luck->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Luck->GetTransform()->SetWorldScale(float4::One);
		Number_Luck->SetValue(0);

		Number_Move = CurLevel->CreateActor<NumberActor>();
		Number_Move->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Move->GetTransform()->SetLocalPosition({ 152, -76 });
		Number_Move->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Move->GetTransform()->SetWorldScale(float4::One);
		Number_Move->SetValue(0);

		Number_Constitution = CurLevel->CreateActor<NumberActor>();
		Number_Constitution->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Constitution->GetTransform()->SetLocalPosition({ 152, -152 });
		Number_Constitution->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Constitution->GetTransform()->SetWorldScale(float4::One);
		Number_Constitution->SetValue(0);
	}
	Off();
}

void UnitInformationUI::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonB"))
	{
		CurLevel->UnitInformation_Cancel();
	}
}

