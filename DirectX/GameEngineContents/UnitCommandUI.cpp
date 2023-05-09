#include "PrecompileHeader.h"
#include "UnitCommandUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "SpriteRenderer.h"
#include "BattleLevel.h"
#include "UICursor.h"
UnitCommandUI::UnitCommandUI()
{
	CommandFunctions.reserve(5);
}

UnitCommandUI::~UnitCommandUI()
{
	LevelPtr = nullptr;
}

void UnitCommandUI::Setting(BattleLevel* _Level)
{
	LevelPtr = _Level;
	CancelFunction = std::bind(&BattleLevel::UnitCommand_Cancel, LevelPtr);
	Cursor = _Level->GetUICursor();
}

void UnitCommandUI::SetCommand(bool _IsAttackable, bool _IsCloseUnit)
{

	if (true == _IsAttackable)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Attack, LevelPtr));	// 공격 커맨드
	}
	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Item, LevelPtr));		// 소지품 커맨드
	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Exchange, LevelPtr));// 교환 커맨드
	}

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Wait, LevelPtr));// 대기 커맨드

	switch (CommandFunctions.size())
	{
	case 2:
		WindowRender->SetTexture("Select2.png");
		break;
	case 3:
		WindowRender->SetTexture("Select3.png");
		break;
	case 4:
		WindowRender->SetTexture("Select4.png");
		break;
	default:
		break;
	}

	CurrentCursor = 0;
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });

	Cursor->GetTransform()->SetParent(GetTransform());
	Cursor->GetTransform()->SetLocalPosition({ 224, 144 });
	CursorPos = { 224, 144 };
}

void UnitCommandUI::On()
{
	GameEngineActor::On();
	Cursor->On();
}
void UnitCommandUI::Off()
{
	GameEngineActor::Off();
	Cursor->Off();
}
void UnitCommandUI::Start()
{
	WindowRender = CreateComponent<SpriteRenderer>();
	WindowRender->GetTransform()->SetWorldScale({ 196, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 36 });
	WindowRender->GetTransform()->SetWorldRotation({ 0,0 });
	WindowRender->SetTexture("Select4.png");

	SelectRender = CreateComponent<SpriteRenderer>();
	SelectRender->GetTransform()->SetWorldScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
	SelectRender->SetTexture("CommandSelect.png");

	CursorPos = { 224, 144 };

	GameEngineActor::Off();
}

void UnitCommandUI::Update(float _DeltaTime)
{
	CursorTimer += _DeltaTime * 10;
	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));



	if (CursorTimer < 1) { return; }

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		CommandFunctions[CurrentCursor]();
		CommandFunctions.resize(0);
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		CommandFunctions.resize(0);
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
			CurrentCursor = CommandFunctions.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition({ 330.0f, 152.0f - (64.0f * CurrentCursor) });
			CursorPos = { 224.0f, 144.0f - (64.0f * CurrentCursor) };
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->AddLocalPosition(float4::Up * 64);
		CursorPos += float4::Up * 64;

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		CursorTimer = 0;
		if (CurrentCursor == CommandFunctions.size() - 1)
		{
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
			CursorPos = { 224, 144 };
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->AddLocalPosition(float4::Down * 64);
		CursorPos += float4::Down * 64;

		return;
	}

}