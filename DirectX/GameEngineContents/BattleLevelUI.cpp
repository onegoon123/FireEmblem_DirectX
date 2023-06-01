#include "PrecompileHeader.h"
#include "BattleLevelUI.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleLevel.h"
#include "SelectUI.h"
#include "UnitCommandUI.h"
#include "FieldCommandUI.h"
#include "PhaseUI.h"
#include "AttackUI.h"
#include "ItemUI.h"
#include "UICursor.h"
BattleLevelUI::BattleLevelUI()
{
}

BattleLevelUI::~BattleLevelUI()
{
	UI_Select->Death();
	UI_Select = nullptr;
	UI_UnitCommand->Death();
	UI_UnitCommand = nullptr;
	UI_FieldCommand->Death();
	UI_FieldCommand = nullptr;
	UI_Attack->Death();
	UI_Attack = nullptr;
	UI_Item->Death();
	UI_Item = nullptr;
	UI_Phase->Death();
	UI_Phase = nullptr;
	UI_Cursor->Death();
	UI_Cursor = nullptr;
	UI_Fade->Death();
	UI_Fade = nullptr;
}

void BattleLevelUI::AllOff()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();
}

void BattleLevelUI::SelectOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Select->On();
}

void BattleLevelUI::SetUnitData(std::shared_ptr<BattleUnit> _Unit)
{
	UI_Select->SetUnitData(_Unit);
}

void BattleLevelUI::UnitUIOff()
{
	UI_Select->UnitUIOff();
}

void BattleLevelUI::SetCursorDir(UIDir _Dir)
{
	UI_Select->SetCursorDir(_Dir);
	switch (_Dir)
	{
	case UIDir::None:
		break;
	case UIDir::LeftUp:
	case UIDir::LeftDown:
		UI_UnitCommand->SetRight();
		UI_Attack->SetRight();
		break;
	case UIDir::RightUp:
	case UIDir::RightDown:
		UI_UnitCommand->SetLeft();
		UI_Attack->SetLeft();
		break;
	default:
		break;
	}
}

void BattleLevelUI::SetTerrain(Terrain _Value)
{
	UI_Select->SetTerrainData(_Value);
}

void BattleLevelUI::UnitCommandOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_UnitCommand->On();
}

void BattleLevelUI::UnitCommandSet(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_UnitCommand->On();
	UI_UnitCommand->SetCommand(_IsAttackable, _IsCloseUnit, _IsItem);
}

void BattleLevelUI::UnitCommandConquer()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_UnitCommand->On();
	UI_UnitCommand->SetConquer();
}

void BattleLevelUI::FieldCommandOn()
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_FieldCommand->On();
}

void BattleLevelUI::AttackOn(std::shared_ptr<class BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Attack->On(_SelectUnit, _TargetUnits);
}

void BattleLevelUI::ItemOn(std::shared_ptr<BattleUnit> _SelectUnit)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Item->On(_SelectUnit);
}

void BattleLevelUI::PhaseOn(Faction _Faction)
{
	UI_Select->Off();
	UI_UnitCommand->Off();
	UI_Attack->Off();
	UI_Item->Off();
	UI_FieldCommand->Off();
	UI_Phase->Off();

	UI_Phase->PhaseOn(_Faction);
}

bool BattleLevelUI::IsPhaseEnd()
{
	return UI_Phase->PhaseUIEnd();
}

void BattleLevelUI::PhaseOff()
{
	UI_Phase->PhaseOff();
}

void BattleLevelUI::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	UI_Fade->ColorOptionValue.MulColor.a = 1;
}

void BattleLevelUI::SetFadeOut(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	UI_Fade->ColorOptionValue.MulColor.a = 0;
}

void BattleLevelUI::PotionUIOn()
{
	UI_Select->On();
	UI_Select->SetCursorDir(UIDir::LeftUp);
	UI_Select->PotionUIOn();
}

void BattleLevelUI::PotionUIOff()
{
	UI_Select->PotionUIOff();
	UI_Select->Off();
}

void BattleLevelUI::SetHPLerp(int _Value)
{
	UI_Select->SetHPLerp(_Value);
}


void BattleLevelUI::Start()
{
	if (nullptr == GameEngineSprite::Find("ItemUI.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("ItemUI.png").GetFullPath(), 3, 2);
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("CommandUI.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Triangle.png").GetFullPath(), 3, 2);

		Dir.MoveParent();
		Dir.Move("Item");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Items.png").GetFullPath(), 7, 5);
	}

	if (nullptr == UI_Select)
	{
		BattleLevel* CurLevel = dynamic_cast<BattleLevel*>(GetLevel());
		if (nullptr == CurLevel)
		{
			MsgAssert("BattleLevelUI는 BattleLevel에서만 생성할 수 있습니다.");
		}
		UI_Select = CurLevel->CreateActor<SelectUI>();
		UI_UnitCommand = CurLevel->CreateActor<UnitCommandUI>();
		UI_Attack = CurLevel->CreateActor<AttackUI>();
		UI_Item = CurLevel->CreateActor<ItemUI>();
		UI_FieldCommand = CurLevel->CreateActor<FieldCommandUI>();
		UI_Phase = CurLevel->CreateActor<PhaseUI>();

		UI_Cursor = CurLevel->CreateActor<UICursor>();

		UI_UnitCommand->Setting(CurLevel, UI_Cursor);
		UI_Attack->Setting(CurLevel, UI_Cursor);
		UI_Item->Setting(CurLevel, UI_Cursor);
		UI_FieldCommand->Setting(CurLevel, UI_Cursor);

		UI_Fade = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
		UI_Fade->ColorOptionValue.MulColor.a = 0;
		UI_Fade->SetTexture("Black.png");
		UI_Fade->GetTransform()->SetLocalScale({ 960, 640 });
		UI_Fade->SetOrder(100);

	}
}

void BattleLevelUI::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeIn = false;
			UI_Fade->ColorOptionValue.MulColor.a = 0;
			return;
		}
		UI_Fade->ColorOptionValue.MulColor.a = FadeTimer;
	}

	if (true == IsFadeOut)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeOut = false;
			UI_Fade->ColorOptionValue.MulColor.a = 1;
			return;
		}
		UI_Fade->ColorOptionValue.MulColor.a = FadeTimer;
	}
}
