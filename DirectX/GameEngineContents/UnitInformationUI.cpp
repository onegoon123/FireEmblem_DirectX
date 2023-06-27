#include "PrecompileHeader.h"
#include "UnitInformationUI.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "BattleUnit.h"
#include "BattleLevel.h"
#include "NumberActor.h"
#include "StatBar.h"
#include "TextRenderer.h"

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

	Text_Name->SetText(_Unit->GetName());
	Text_Class->SetText(_Unit->GetUnitData().GetClassValueToString());

	Number_Level->SetValue(_Unit->GetUnitData().GetLevel());
	Number_Exp->SetValue(_Unit->GetUnitData().GetExp());
	Number_HP->SetValue(_Unit->GetUnitData().GetHP());
	Number_MaxHP->SetValue(_Unit->GetUnitData().GetMaxHP());

	Range->SetValue(_Unit->GetRangeStat());
	Attack->SetValue(_Unit->GetUnitData().GetAttackPoint());
	Critical->SetValue(_Unit->GetUnitData().GetCriticalPoint());
	Hit->SetValue(_Unit->GetUnitData().GetHitPoint());
	Dodge->SetValue(_Unit->GetUnitData().GetDodgePoint());
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

	// 아이템 세팅
	std::list<std::shared_ptr<Item>>& Items = _Unit->GetUnitData().GetItems();
	std::list<std::shared_ptr<Item>>::iterator ItemIter = Items.begin();

	for (size_t i = 0; i < Items.size(); i++)
	{
		ItemIcons[i]->On();
		ItemIcons[i]->SetFrame(static_cast<int>((*ItemIter)->GetItemCode()) - 1);
		ItemUses[i]->On();
		ItemUses[i]->SetValue((*ItemIter)->GetUses());
		ItemMaxUses[i]->On();
		ItemMaxUses[i]->SetValue((*ItemIter)->GetMaxUses());
		ItemUsesText[i]->On();
		ItemNames[i]->On();
		ItemNames[i]->SetText((*ItemIter)->GetName());
		ItemIter++;
	}
	for (size_t i = Items.size(); i < 5; i++)
	{
		ItemIcons[i]->Off();
		ItemUses[i]->Off();
		ItemMaxUses[i]->Off();
		ItemUsesText[i]->Off();
		ItemNames[i]->Off();
	}
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
	PersonalDataWindow->GetTransform()->SetLocalScale({ 548, 420, 1 });
	PersonalDataWindow->GetTransform()->SetLocalPosition({ 164, 32 });

	PortraitRenderer = CreateComponent<GameEngineUIRenderer>(2);
	PortraitRenderer->GetTransform()->SetLocalScale({ 384, 320 });
	PortraitRenderer->GetTransform()->SetLocalPosition({ -264, 128 });

	UnitRenderer = CreateComponent<GameEngineUIRenderer>(6);
	UnitRenderer->GetTransform()->SetLocalScale({ 192, 192 });
	UnitRenderer->GetTransform()->SetLocalPosition({ -168, -182 });

	Text_Name = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_Name->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
	Text_Name->GetTransform()->SetLocalPosition({-264, -12});

	Text_Class = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text_Class->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
	Text_Class->GetTransform()->SetLocalPosition({ -312, -112 });

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
		Number_Strength->GetTransform()->SetLocalPosition({ -100 + 164, 128 +32});
		Number_Strength->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Magic = CurLevel->CreateActor<NumberActor>();
		Number_Magic->GetTransform()->SetLocalPosition({ -100 + 164, 40 + 32});
		Number_Magic->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Dexterity = CurLevel->CreateActor<NumberActor>();
		Number_Dexterity->GetTransform()->SetLocalPosition({ -100 + 164, -48 +32});
		Number_Dexterity->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Speed = CurLevel->CreateActor<NumberActor>();
		Number_Speed->GetTransform()->SetLocalPosition({ -100 + 164, -136 +32});
		Number_Speed->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Defense = CurLevel->CreateActor<NumberActor>();
		Number_Defense->GetTransform()->SetLocalPosition({ 152 + 164, 152 + 32});
		Number_Defense->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Resistance = CurLevel->CreateActor<NumberActor>();
		Number_Resistance->GetTransform()->SetLocalPosition({ 152 + 164, 76 + 32});
		Number_Resistance->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Luck = CurLevel->CreateActor<NumberActor>();
		Number_Luck->GetTransform()->SetLocalPosition({ 152 + 164, 0 + 32});
		Number_Luck->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Move = CurLevel->CreateActor<NumberActor>();
		Number_Move->GetTransform()->SetLocalPosition({ 152 + 164, -76 + 32});
		Number_Move->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Number_Constitution = CurLevel->CreateActor<NumberActor>();
		Number_Constitution->GetTransform()->SetLocalPosition({ 152 + 164, -152 + 32});
		Number_Constitution->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
	}

	{
		Bar_Strength = CurLevel->CreateActor<StatBar>();
		Bar_Strength->GetTransform()->SetLocalPosition({ -164 + 164, 116 + 32});
		Bar_Strength->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Magic = CurLevel->CreateActor<StatBar>();
		Bar_Magic->GetTransform()->SetLocalPosition({ -164 + 164, 28 + 32});
		Bar_Magic->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Dexterity = CurLevel->CreateActor<StatBar>();
		Bar_Dexterity->GetTransform()->SetLocalPosition({ -164 + 164, -60 + 32});
		Bar_Dexterity->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Speed = CurLevel->CreateActor<StatBar>();
		Bar_Speed->GetTransform()->SetLocalPosition({ -164 + 164, -148 + 32});
		Bar_Speed->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Defense = CurLevel->CreateActor<StatBar>();
		Bar_Defense->GetTransform()->SetLocalPosition({ 88 + 164, 140 +32});
		Bar_Defense->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Resistance = CurLevel->CreateActor<StatBar>();
		Bar_Resistance->GetTransform()->SetLocalPosition({ 88 + 164, 64 + 32});
		Bar_Resistance->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Luck = CurLevel->CreateActor<StatBar>();
		Bar_Luck->GetTransform()->SetLocalPosition({ 88 + 164, -12 + 32});
		Bar_Luck->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Move = CurLevel->CreateActor<StatBar>();
		Bar_Move->GetTransform()->SetLocalPosition({ 88 + 164, -88 + 32});
		Bar_Move->GetTransform()->SetParent(PersonalDataWindow->GetTransform());

		Bar_Constitution = CurLevel->CreateActor<StatBar>();
		Bar_Constitution->GetTransform()->SetLocalPosition({ 88 + 164, -164 + 32});
		Bar_Constitution->GetTransform()->SetParent(PersonalDataWindow->GetTransform());
	}


	{
		// 아이템 데이터 창
		ItemDataWindow = CreateComponent<GameEngineUIRenderer>(3);
		ItemDataWindow->SetTexture("ItemDataWindow.png");
		ItemDataWindow->GetTransform()->SetLocalScale({ 536, 536, 1 });

		Range = GetLevel()->CreateActor<NumberActor>();
		Range->GetTransform()->SetLocalPosition({ 182, -96 });
		Range->GetTransform()->SetWorldRotation(float4::Zero);
		Range->GetTransform()->SetWorldScale(float4::One);
		Range->GetTransform()->SetParent(ItemDataWindow->GetTransform());

		Attack = GetLevel()->CreateActor<NumberActor>();
		Attack->GetTransform()->SetLocalPosition({ -42, -160 });
		Attack->GetTransform()->SetWorldRotation(float4::Zero);
		Attack->GetTransform()->SetWorldScale(float4::One);
		Attack->GetTransform()->SetParent(ItemDataWindow->GetTransform());

		Critical = GetLevel()->CreateActor<NumberActor>();
		Critical->GetTransform()->SetLocalPosition({ 182, -160 });
		Critical->GetTransform()->SetWorldRotation(float4::Zero);
		Critical->GetTransform()->SetWorldScale(float4::One);
		Critical->GetTransform()->SetParent(ItemDataWindow->GetTransform());

		Hit = GetLevel()->CreateActor<NumberActor>();
		Hit->GetTransform()->SetLocalPosition({ -42, -224 });
		Hit->GetTransform()->SetWorldRotation(float4::Zero);
		Hit->GetTransform()->SetWorldScale(float4::One);
		Hit->GetTransform()->SetParent(ItemDataWindow->GetTransform());

		Dodge = GetLevel()->CreateActor<NumberActor>();
		Dodge->GetTransform()->SetLocalPosition({ 182, -224 });
		Dodge->GetTransform()->SetWorldRotation(float4::Zero);
		Dodge->GetTransform()->SetWorldScale(float4::One);
		Dodge->GetTransform()->SetParent(ItemDataWindow->GetTransform());

		ItemIcons.resize(5);
		ItemNames.resize(5);
		for (int i = 0; i < 5; i++)
		{
			ItemIcons[i] = CreateComponent<GameEngineUIRenderer>(4);
			ItemIcons[i]->SetSprite("Items.png", 0);

			ItemIcons[i]->GetTransform()->SetLocalPosition({ -212, i * -64.0f + 220.0f});
			ItemIcons[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemIcons[i]->GetTransform()->SetWorldScale({ 64, 64 });
			ItemIcons[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());

			//ItemIcons[i]->Off();
			ItemNames[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
			ItemNames[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
			ItemNames[i]->GetTransform()->SetLocalPosition({ -164, i * -64.0f + 244.0f });
			ItemNames[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemNames[i]->GetTransform()->SetWorldScale(float4::One);
			ItemNames[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());
		}

		ItemUses.resize(5);
		ItemMaxUses.resize(5);
		ItemUsesText.resize(5);
		for (int i = 0; i < 5; i++)
		{
			ItemMaxUses[i] = GetLevel()->CreateActor<NumberActor>();

			ItemMaxUses[i]->GetTransform()->SetLocalPosition({ 208, i * -64.0f + 220.0f });
			ItemMaxUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemMaxUses[i]->GetTransform()->SetWorldScale(float4::One);
			ItemMaxUses[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());

			ItemMaxUses[i]->SetValue(25);

			ItemUses[i] = GetLevel()->CreateActor<NumberActor>();

			ItemUses[i]->GetTransform()->SetLocalPosition({ 116, i * -64.0f + 220.0f });
			ItemUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemUses[i]->GetTransform()->SetWorldScale(float4::One);
			ItemUses[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());

			ItemUses[i]->SetValue(25);

			ItemUsesText[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIText);
			ItemUsesText[i]->SetTexture("ItemUseText.png");
			ItemUsesText[i]->GetTransform()->SetLocalPosition({ 144, i * -64.0f + 220.0f });
			ItemUsesText[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemUsesText[i]->GetTransform()->SetWorldScale({24, 40});
			ItemUsesText[i]->GetTransform()->SetParent(ItemDataWindow->GetTransform());
		}


		ItemDataWindow->GetTransform()->SetLocalPosition({ 164, -26 });
		ItemDataWindow->GetTransform()->AddLocalPosition(float4::Right * 1000);

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

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsDown("RightClick"))
	{
		GameEngineSound::Play("Cancel.wav");
		CurLevel->UnitInformation_Cancel();
	}

	if (GameEngineInput::IsDown("Left") || GameEngineInput::IsDown("Right") || GameEngineInput::IsDown("LeftClick"))
	{
		GameEngineSound::Play("CommandMove.wav");
		Timer = 0;
		IsMove = true;
		IsItemWindow = !IsItemWindow;
	}
}

