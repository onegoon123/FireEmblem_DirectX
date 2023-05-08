#include "PrecompileHeader.h"
#include "FieldCommandUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BattleLevel.h"
#include "SpriteRenderer.h"
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
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
	CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });
}

void FieldCommandUI::On()
{
	GameEngineActor::On();
	IsOnFrame = true;
	CurrentCursor = 0;
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
	CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });
}

void FieldCommandUI::Start()
{
	WindowRender = CreateComponent<SpriteRenderer>();
	WindowRender->GetTransform()->SetWorldScale({ 196, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 36 });
	WindowRender->GetTransform()->SetWorldRotation({ 0,0 });
	WindowRender->SetTexture("FieldCommand.png");

	SelectRender = CreateComponent<SpriteRenderer>();
	SelectRender->GetTransform()->SetWorldScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
	SelectRender->SetTexture("FieldCommandSelect.png");

	CursorRender = CreateComponent<SpriteRenderer>();
	CursorRender->GetTransform()->SetWorldScale({ 64, 64 });
	CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });
	CursorRender->SetTexture("CommandCursor.png");
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
		if (CurrentCursor == 0)
		{
			CurrentCursor = CommandFunctions.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition({ 330.0f, 152.0f - (64.0f * CurrentCursor) });
			CursorRender->GetTransform()->SetLocalPosition({ 224.0f, 144.0f - (64.0f * CurrentCursor) });
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->AddLocalPosition(float4::Up * 64);
		CursorRender->GetTransform()->AddLocalPosition(float4::Up * 64);

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		if (CurrentCursor == CommandFunctions.size() - 1)
		{
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
			CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->AddLocalPosition(float4::Down * 64);
		CursorRender->GetTransform()->AddLocalPosition(float4::Down * 64);

		return;
	}

}