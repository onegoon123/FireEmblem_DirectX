#include "PrecompileHeader.h"
#include "AttackUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "MapCursor.h"
#include "DebugWindow.h"
AttackUI::AttackUI() 
{
}

AttackUI::~AttackUI() 
{
}

void AttackUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_UI = _Cursor;
	Cursor_Map = _Level->GetMapCursor();
	AttackFunction = std::bind(&BattleLevel::UnitCommand_TargetAttack, _Level, std::placeholders::_1);
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);
}

void AttackUI::On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	GameEngineActor::On();

	SelectUnit = _SelectUnit;
	TargetUnits = _TargetUnits;
	Weapons = SelectUnit->GetUnitData().GetWeapons();
	switch (Weapons.size())
	{
	case 1:
		WindowRender->SetTexture("ItemListUI1.png");
		break;
	case 2:
		WindowRender->SetTexture("ItemListUI2.png");
		break;
	case 3:
		WindowRender->SetTexture("ItemListUI3.png");
		break;
	case 4:
		WindowRender->SetTexture("ItemListUI4.png");
		break;
	case 5:
		WindowRender->SetTexture("ItemListUI5.png");
		break;
	default:
	{
		MsgAssert("정해진 무기 갯수의 범위를 벗어났습니다.");
		return;
	}
	}
	std::string TextStr = "Portrait_";
	TextStr += SelectUnit->GetUnitData().GetName();
	TextStr += ".png";
	Portrait->SetTexture(TextStr);

	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);

	CurrentCursor = 0;
	Cursor_UI->On();
	CursorPos = StartCursorPos;
	Cursor_UI->GetTransform()->SetLocalPosition(StartCursorPos);

	IsOnFrame = true;
	IsWeaponSelect = false;
	WeaponSelectStart();

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";
	for (std::shared_ptr<Weapon> _Weapon : Weapons)
	{
		Window->Text += _Weapon->GetName();
		Window->Text += " ";
		Window->Text += std::to_string(_Weapon->GetUses());
		Window->Text += " / " + std::to_string(_Weapon->GetMaxUses()) + '\n';
	}
}


void AttackUI::Off()
{
	GameEngineActor::Off();
	Cursor_UI->Off();
}

void AttackUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetWorldScale({ 420, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ -224, 64 });
	WindowRender->SetTexture("ItemListUI3.png");

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetWorldScale({ 368, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	InfoRender->GetTransform()->SetWorldScale({ 420, 356 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetTexture("ItemListUI3.png");

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	BattleEx = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BattleEx->GetTransform()->SetWorldScale({ 292, 484 });
	BattleEx->GetTransform()->SetLocalPosition({ -318, 62 });
	BattleEx->SetTexture("BattleExUI.png");

	GameEngineActor::Off();
}

void AttackUI::Update(float _DeltaTime)
{
	if (true == IsWeaponSelect)
	{
		TargetSelectUpdate(_DeltaTime);
		return;
	}
	WeaponSelectUpdate(_DeltaTime);
}

void AttackUI::WeaponSelectStart()
{
	IsWeaponSelect = false;
	SelectRender->On();
	WindowRender->On();
	InfoRender->On();
	Portrait->On();
	Cursor_UI->On();
	BattleEx->Off();
}

void AttackUI::WeaponSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		WeaponSelectEnd();
		TargetSelectStart();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor_UI->GetTransform()->SetLocalPosition(float4::Lerp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	if (CursorTimer < 1) { return; }



	if (PreesTime < GameEngineInput::GetPressTime("Up") || PreesTime < GameEngineInput::GetPressTime("Down"))
	{
		PressOK = true;
	}
	else if (GameEngineInput::IsFree("Up") && GameEngineInput::IsFree("Down"))
	{
		PressOK = false;
	}

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{
		CursorTimer = 0;
		if (CurrentCursor == 0)
		{
			if (false == GameEngineInput::IsDown("Up")) { return; }
			CurrentCursor = Weapons.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK) || GameEngineInput::IsUp("MiddleClick"))
	{
		CursorTimer = 0;
		if (CurrentCursor == Weapons.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos;
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);

		return;
	}

}

void AttackUI::WeaponSelectEnd()
{
	SelectRender->Off();
	WindowRender->Off();
	InfoRender->Off();
	Portrait->Off();
	Cursor_UI->Off();
	BattleEx->On();
}

void AttackUI::TargetSelectStart()
{
	std::list<std::shared_ptr<Weapon>>::iterator StartIter = Weapons.begin();
	std::advance(StartIter, CurrentCursor);
	if (StartIter == Weapons.end())
	{
		MsgAssert("선택한 무기를 무기리스트에서 찾지 못했습니다.");
		return;
	}
	SelectWeapon = *StartIter;
	SelectUnit->GetUnitData().EquipWeapon(SelectWeapon);
	IsWeaponSelect = true;

	TargetIter = TargetUnits.begin();
	Cursor_Map->On();

	SetTarget();
}

void AttackUI::TargetSelectUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		AttackFunction(TargetUnit);
		Cursor_Map->Off();
		Off();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		WeaponSelectStart();
		return;
	}
	if (Cursor_Map->GetIsMove()) { return; }


	if (GameEngineInput::IsDown("Up") || GameEngineInput::IsDown("Left"))
	{
		if (TargetIter == TargetUnits.begin())
		{
			TargetIter = TargetUnits.end();
		}
		TargetIter--;
		SetTarget();
		return;
	}
	if (GameEngineInput::IsDown("Down") || GameEngineInput::IsDown("Right") || GameEngineInput::IsUp("MiddleClick"))
	{
		TargetIter++;
		if (TargetIter == TargetUnits.end())
		{
			TargetIter = TargetUnits.begin();
		}
		SetTarget();
		return;
	}
}

void AttackUI::TargetSelectEnd()
{
}

void AttackUI::SetTarget()
{
	TargetUnit = *TargetIter;
	Cursor_Map->SetMapPosLerp(TargetUnit->GetMapPos());

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = SelectUnit->GetName();
	Window->Text += "\n HP : ";
	Window->Text += std::to_string(SelectUnit->GetUnitData().GetHP());
	Window->Text += "\n 위력 : ";
	Window->Text += std::to_string(SelectUnit->GetUnitData().GetAttackPoint(TargetUnit->GetUnitData()));
	if (true == SelectUnit->GetUnitData().IsDoubleAttack(TargetUnit->GetUnitData()))
	{
		Window->Text += " × 2";
	}
	Window->Text += "\n 명중 : ";
	Window->Text += std::to_string(SelectUnit->GetUnitData().GetHitPoint(TargetUnit->GetUnitData()));
	Window->Text += "\n 필살 : ";
	Window->Text += std::to_string(SelectUnit->GetUnitData().GetCriticalPoint(TargetUnit->GetUnitData()));

	Window->Text += "\n\n";

	Window->Text += TargetUnit->GetName();
	Window->Text += "\n HP : ";
	Window->Text += std::to_string(TargetUnit->GetUnitData().GetHP());
	Window->Text += "\n 위력 : ";
	Window->Text += std::to_string(TargetUnit->GetUnitData().GetAttackPoint(SelectUnit->GetUnitData()));
	if (true == TargetUnit->GetUnitData().IsDoubleAttack(SelectUnit->GetUnitData()))
	{
		Window->Text += " × 2";
	}
	Window->Text += "\n 명중 : ";
	Window->Text += std::to_string(TargetUnit->GetUnitData().GetHitPoint(SelectUnit->GetUnitData()));
	Window->Text += "\n 필살 : ";
	Window->Text += std::to_string(TargetUnit->GetUnitData().GetCriticalPoint(SelectUnit->GetUnitData()));
}

