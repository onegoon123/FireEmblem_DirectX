#include "PrecompileHeader.h"
#include "FieldCommandUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BattleLevel.h"
#include "SpriteRenderer.h"
#include "UICursor.h"

FieldCommandUI::FieldCommandUI() 
{
	CommandFunctions.reserve(5);
}

FieldCommandUI::~FieldCommandUI() 
{
}

void FieldCommandUI::Setting(BattleLevel* _Level)
{
	LevelPtr = _Level;
	CancelFunction = std::bind(&BattleLevel::FieldCommand_Cancel, LevelPtr);
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_TimeStone, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_ArmyUnit, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_Setting, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_Exit, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_PhaseEnd, LevelPtr));
	CurrentCursor = 0;
	Cursor = _Level->GetUICursor();
}

void FieldCommandUI::On()
{
	GameEngineActor::On();
	IsOnFrame = true;
	CurrentCursor = 0;
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);

	CursorPos = StartCursorPos;
	Cursor->On();
	Cursor->GetTransform()->SetParent(GetTransform());
	Cursor->GetTransform()->SetLocalPosition(StartCursorPos);
}

void FieldCommandUI::Off()
{
	GameEngineActor::Off();
	Cursor->Off();
}

void FieldCommandUI::Start()
{
	WindowRender = CreateComponent<SpriteRenderer>();
	WindowRender->GetTransform()->SetWorldScale({ 196, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 36 });
	WindowRender->GetTransform()->SetWorldRotation({ 0,0 });
	WindowRender->SetTexture("Select5.png");

	SelectRender = CreateComponent<SpriteRenderer>();
	SelectRender->GetTransform()->SetWorldScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("CommandSelect.png");

	GameEngineActor::Off();
}

void FieldCommandUI::Update(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		CommandFunctions[CurrentCursor]();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		return;
	}
	CursorTimer += _DeltaTime * 10;
	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

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
			CurrentCursor = CommandFunctions.size() - 1;
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
		if (CurrentCursor == CommandFunctions.size() - 1)
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