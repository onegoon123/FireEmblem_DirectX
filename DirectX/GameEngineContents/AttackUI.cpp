#include "PrecompileHeader.h"
#include "AttackUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "SpriteRenderer.h"
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "MapCursor.h"
AttackUI::AttackUI() 
{
}

AttackUI::~AttackUI() 
{
}

void AttackUI::Setting(BattleLevel* _Level)
{
	LevelPtr = _Level;
	UICursor = _Level->GetUICursor();
	Cursor = _Level->GetMapCursor();
	AttackFunction = std::bind(&BattleLevel::UnitCommand_TargetAttack, _Level, std::placeholders::_1);
	CancelFunction = std::bind(&BattleLevel::UnitCommand_AttackCancel, _Level);
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
	UICursor->On();
	CursorPos = StartCursorPos;
	UICursor->GetTransform()->SetParent(GetTransform());
	UICursor->GetTransform()->SetLocalPosition(StartCursorPos);

	IsOnFrame = true;
	IsWeaponSelect = false;
	WeaponSelectStart();
}


void AttackUI::Off()
{
	GameEngineActor::Off();
	UICursor->Off();
}

void AttackUI::Start()
{
	WindowRender = CreateComponent<SpriteRenderer>();
	WindowRender->GetTransform()->SetWorldScale({ 420, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ -224, 64 });
	//WindowRender->GetTransform()->SetWorldRotation({ 0,0 });
	WindowRender->SetTexture("ItemListUI3.png");

	SelectRender = CreateComponent<SpriteRenderer>();
	SelectRender->GetTransform()->SetWorldScale({ 368, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<SpriteRenderer>();
	InfoRender->GetTransform()->SetWorldScale({ 420, 356 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetTexture("ItemListUI3.png");

	Portrait = CreateComponent<SpriteRenderer>();
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	BattleEx = CreateComponent<SpriteRenderer>();
	BattleEx->GetTransform()->SetWorldScale({ 292, 484 });
	BattleEx->GetTransform()->SetLocalPosition({ -318, 62 });
	BattleEx->GetTransform()->SetWorldRotation(float4::Zero);
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
	UICursor->On();
	BattleEx->Off();
}

void AttackUI::WeaponSelectUpdate(float _DeltaTime)
{

	CursorTimer += _DeltaTime * 10;
	UICursor->GetTransform()->SetLocalPosition(float4::Lerp(UICursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	if (CursorTimer < 1) { return; }

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

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		CursorTimer = 0;
		if (CurrentCursor == Weapons.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down")) { return; }
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
	UICursor->Off();
	BattleEx->On();
}

void AttackUI::TargetSelectStart()
{
	std::list<std::shared_ptr<Weapon>>::iterator StartIter = Weapons.begin();
	std::advance(StartIter, CurrentCursor);
	SelectWeapon = *StartIter;
	SelectUnit->GetUnitData().UnitStat.EquipWeapon = SelectWeapon;
	IsWeaponSelect = true;

	TargetIter = TargetUnits.begin();
	TargetUnit = *TargetIter;
	Cursor->On();
	Cursor->SetMapPos(TargetUnit->GetMapPos());
}

void AttackUI::TargetSelectUpdate(float _DeltaTime)
{
	if (Cursor->GetIsMove()) { return; }

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		AttackFunction(TargetUnit);
		Cursor->Off();
		Off();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		WeaponSelectStart();
		return;
	}

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
	if (GameEngineInput::IsDown("Down") || GameEngineInput::IsDown("Right"))
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
	Cursor->SetMapPosLerp(TargetUnit->GetMapPos());
}

