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

		PortraitRenderer->GetTransform()->SetLocalPosition({ -264, 148 });
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
	Number_Level->SetValue(_Unit->GetUnitData().GetLevel());
	Number_Exp->SetValue(_Unit->GetUnitData().GetExp());
	Number_HP->SetValue(_Unit->GetUnitData().GetHP());
	Number_MaxHP->SetValue(_Unit->GetUnitData().GetMaxHP());
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
	PersonalDataWindow->GetTransform()->SetLocalScale({ 960, 640 });

	PortraitRenderer = CreateComponent<GameEngineUIRenderer>(2);
	PortraitRenderer->GetTransform()->SetLocalScale({ 384, 320 });
	PortraitRenderer->GetTransform()->SetLocalPosition({-264, 128});

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

	Off();
}

void UnitInformationUI::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonB"))
	{
		CurLevel->UnitInformation_Cancel();
	}
}

