#include "PrecompileHeader.h"
#include "UnitInformationUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "BattleUnit.h"
#include "BattleLevel.h"
#include "NumberActor.h"
#include "StatBar.h"

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

	// 스텟 숫자
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

	// 스탯 게이지
	MainStat MaximumStat = _Unit->GetUnitData().GetMaximumStat();
	Bar_Strength->SetSize((float)MaximumStat.Strength * 5);
	Bar_Strength->SetValue((float)StatValue.Strength / MaximumStat.Strength);
	Bar_Magic->SetSize((float)MaximumStat.Magic * 5);
	Bar_Magic->SetValue((float)StatValue.Magic / MaximumStat.Magic);
	Bar_Dexterity->SetSize((float)MaximumStat.Dexterity * 5);
	Bar_Dexterity->SetValue((float)StatValue.Dexterity / MaximumStat.Dexterity);
	Bar_Speed->SetSize((float)MaximumStat.Speed * 5);
	Bar_Speed->SetValue((float)StatValue.Speed / MaximumStat.Speed);
	Bar_Defense->SetSize((float)MaximumStat.Defense * 5);
	Bar_Defense->SetValue((float)StatValue.Defense / MaximumStat.Defense);
	Bar_Resistance->SetSize((float)MaximumStat.Resistance * 5);
	Bar_Resistance->SetValue((float)StatValue.Resistance / MaximumStat.Resistance);
	Bar_Luck->SetSize((float)MaximumStat.Luck * 5);
	Bar_Luck->SetValue((float)StatValue.Luck / MaximumStat.Luck);
	Bar_Move->SetSize(70.0f);
	Bar_Move->SetValue((float)_Unit->GetMoveStat() / 10);
	Bar_Constitution->SetSize((float)MaximumStat.Constitution * 5);
	Bar_Constitution->SetValue((float)StatValue.Constitution / MaximumStat.Constitution);
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

	Number_Exp = CurLevel->CreateActor<NumberActor>();
	Number_Exp->GetTransform()->SetParent(GetTransform());
	Number_Exp->GetTransform()->SetLocalPosition({ -248, -196 });

	Number_HP = CurLevel->CreateActor<NumberActor>();
	Number_HP->GetTransform()->SetParent(GetTransform());
	Number_HP->GetTransform()->SetLocalPosition({ -364, -258 });

	Number_MaxHP = CurLevel->CreateActor<NumberActor>();
	Number_MaxHP->GetTransform()->SetParent(GetTransform());
	Number_MaxHP->GetTransform()->SetLocalPosition({ -248, -258 });

	{
		Number_Strength = CurLevel->CreateActor<NumberActor>();
		Number_Strength->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Strength->GetTransform()->SetLocalPosition({ -100, 128 });
		Number_Strength->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Strength->GetTransform()->SetWorldScale(float4::One);

		Number_Magic = CurLevel->CreateActor<NumberActor>();
		Number_Magic->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Magic->GetTransform()->SetLocalPosition({ -100, 40 });
		Number_Magic->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Magic->GetTransform()->SetWorldScale(float4::One);

		Number_Dexterity = CurLevel->CreateActor<NumberActor>();
		Number_Dexterity->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Dexterity->GetTransform()->SetLocalPosition({ -100, -48 });
		Number_Dexterity->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Dexterity->GetTransform()->SetWorldScale(float4::One);

		Number_Speed = CurLevel->CreateActor<NumberActor>();
		Number_Speed->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Speed->GetTransform()->SetLocalPosition({ -100, -136 });
		Number_Speed->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Speed->GetTransform()->SetWorldScale(float4::One);

		Number_Defense = CurLevel->CreateActor<NumberActor>();
		Number_Defense->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Defense->GetTransform()->SetLocalPosition({ 152, 152 });
		Number_Defense->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Defense->GetTransform()->SetWorldScale(float4::One);

		Number_Resistance = CurLevel->CreateActor<NumberActor>();
		Number_Resistance->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Resistance->GetTransform()->SetLocalPosition({ 152, 76 });
		Number_Resistance->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Resistance->GetTransform()->SetWorldScale(float4::One);

		Number_Luck = CurLevel->CreateActor<NumberActor>();
		Number_Luck->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Luck->GetTransform()->SetLocalPosition({ 152, 0 });
		Number_Luck->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Luck->GetTransform()->SetWorldScale(float4::One);

		Number_Move = CurLevel->CreateActor<NumberActor>();
		Number_Move->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Move->GetTransform()->SetLocalPosition({ 152, -76 });
		Number_Move->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Move->GetTransform()->SetWorldScale(float4::One);

		Number_Constitution = CurLevel->CreateActor<NumberActor>();
		Number_Constitution->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Number_Constitution->GetTransform()->SetLocalPosition({ 152, -152 });
		Number_Constitution->GetTransform()->SetWorldRotation(float4::Zero);
		Number_Constitution->GetTransform()->SetWorldScale(float4::One);
	}

	{
		Bar_Strength = CurLevel->CreateActor<StatBar>();
		Bar_Strength->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Strength->GetTransform()->SetLocalPosition({ -164, 116 });
		Bar_Strength->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Strength->GetTransform()->SetWorldScale(float4::One);

		Bar_Magic = CurLevel->CreateActor<StatBar>();
		Bar_Magic->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Magic->GetTransform()->SetLocalPosition({ -164, 28 });
		Bar_Magic->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Magic->GetTransform()->SetWorldScale(float4::One);

		Bar_Dexterity = CurLevel->CreateActor<StatBar>();
		Bar_Dexterity->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Dexterity->GetTransform()->SetLocalPosition({ -164, -60 });
		Bar_Dexterity->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Dexterity->GetTransform()->SetWorldScale(float4::One);

		Bar_Speed = CurLevel->CreateActor<StatBar>();
		Bar_Speed->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Speed->GetTransform()->SetLocalPosition({ -164, -148 });
		Bar_Speed->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Speed->GetTransform()->SetWorldScale(float4::One);

		Bar_Defense = CurLevel->CreateActor<StatBar>();
		Bar_Defense->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Defense->GetTransform()->SetLocalPosition({ 88, 140 });
		Bar_Defense->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Defense->GetTransform()->SetWorldScale(float4::One);

		Bar_Resistance = CurLevel->CreateActor<StatBar>();
		Bar_Resistance->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Resistance->GetTransform()->SetLocalPosition({ 88, 64 });
		Bar_Resistance->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Resistance->GetTransform()->SetWorldScale(float4::One);

		Bar_Luck = CurLevel->CreateActor<StatBar>();
		Bar_Luck->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Luck->GetTransform()->SetLocalPosition({ 88, -12 });
		Bar_Luck->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Luck->GetTransform()->SetWorldScale(float4::One);

		Bar_Move = CurLevel->CreateActor<StatBar>();
		Bar_Move->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Move->GetTransform()->SetLocalPosition({ 88, -88 });
		Bar_Move->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Move->GetTransform()->SetWorldScale(float4::One);

		Bar_Constitution = CurLevel->CreateActor<StatBar>();
		Bar_Constitution->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
		Bar_Constitution->GetTransform()->SetLocalPosition({ 88, -164 });
		Bar_Constitution->GetTransform()->SetWorldRotation(float4::Zero);
		Bar_Constitution->GetTransform()->SetWorldScale(float4::One);
	}


	{
		// 아이템 데이터 창
		ItemDataWindow = CreateComponent<GameEngineUIRenderer>(3);
		ItemDataWindow->SetTexture("ItemDataWindow.png");
		ItemDataWindow->GetTransform()->SetLocalScale({ 536, 536 });
		ItemDataWindow->GetTransform()->SetLocalPosition({ 164, -26 });
		ItemDataWindow->GetTransform()->AddLocalPosition(float4::Right * 1000);

		ItemIcons.resize(5);
		for (int i = 0; i < 5; i++)
		{
			ItemIcons[i] = CreateComponent<GameEngineUIRenderer>(4);
			ItemIcons[i]->SetSprite("Items.png", 0);

			ItemIcons[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());
			ItemIcons[i]->GetTransform()->SetLocalPosition({ -212, i * 64.0f - 32.0f});
			ItemIcons[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemIcons[i]->GetTransform()->SetWorldScale({ 64, 64 });

			//ItemIcons[i]->Off();
		}

		ItemUses.resize(5);
		ItemMaxUses.resize(5);
		for (int i = 0; i < 5; i++)
		{
			ItemMaxUses[i] = GetLevel()->CreateActor<NumberActor>();

			ItemMaxUses[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());
			ItemMaxUses[i]->GetTransform()->SetLocalPosition({ 212, i * 64.0f - 32.0f });
			ItemMaxUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemMaxUses[i]->GetTransform()->SetWorldScale(float4::One);

			ItemMaxUses[i]->SetValue(25);

			ItemUses[i] = GetLevel()->CreateActor<NumberActor>();

			ItemUses[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());
			ItemUses[i]->GetTransform()->SetLocalPosition({ 128, i * 64.0f - 32.0f });
			ItemUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemUses[i]->GetTransform()->SetWorldScale(float4::One);

			ItemUses[i]->SetValue(25);

			//ItemIcons[i]->Off();
		}



	}
	Off();
}

void UnitInformationUI::Update(float _DeltaTime)
{
	if (true == IsMove)
	{
		Timer += _DeltaTime * 2;
		if (true == IsItemWindow)
		{
			PersonalDataWindow->GetTransform()->SetLocalPosition(float4::LerpClamp(PersonalDataWindow->GetTransform()->GetLocalPosition(), {1164, 32}, _DeltaTime * 10));
			ItemDataWindow->GetTransform()->SetLocalPosition(float4::LerpClamp(ItemDataWindow->GetTransform()->GetLocalPosition(), { 164, -26 }, _DeltaTime * 10));

			if (1 < Timer)
			{
				PersonalDataWindow->GetTransform()->SetLocalPosition({ 1164, 32 });
				ItemDataWindow->GetTransform()->SetLocalPosition({ 164, -26 });
				IsMove = false;
			}
		}
		else
		{
			PersonalDataWindow->GetTransform()->SetLocalPosition(float4::LerpClamp(PersonalDataWindow->GetTransform()->GetLocalPosition(), { 164, 32 }, _DeltaTime * 10));
			ItemDataWindow->GetTransform()->SetLocalPosition(float4::LerpClamp(ItemDataWindow->GetTransform()->GetLocalPosition(), { 1164, -26 }, _DeltaTime * 10));

			if (1 < Timer)
			{
				PersonalDataWindow->GetTransform()->SetLocalPosition({ 164, 32 });
				ItemDataWindow->GetTransform()->SetLocalPosition({ 1164, -26 });
				IsMove = false;
			}
		}
		
		
		

		return;
	}

	if (GameEngineInput::IsDown("ButtonB"))
	{
		CurLevel->UnitInformation_Cancel();
	}

	if (GameEngineInput::IsDown("Left") || GameEngineInput::IsDown("Right"))
	{
		Timer = 0;
		IsMove = true;
		IsItemWindow = !IsItemWindow;
	}
}

