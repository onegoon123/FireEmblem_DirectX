#include "PrecompileHeader.h"
#include "FieldCommandUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleLevel.h"
#include "UICursor.h"
#include "UIButtonSystem.h"
FieldCommandUI::FieldCommandUI() 
{
	CommandFunctions.reserve(5);
}

FieldCommandUI::~FieldCommandUI() 
{
}

void FieldCommandUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	CancelFunction = std::bind(&BattleLevel::FieldCommand_Cancel, LevelPtr);
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_TimeStone, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_ArmyUnit, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_Setting, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_Exit, LevelPtr));
	CommandFunctions.push_back(std::bind(&BattleLevel::FieldCommand_PhaseEnd, LevelPtr));
	CurrentCursor = 0;
	Cursor = _Cursor;
}

void FieldCommandUI::On()
{
	GameEngineActor::On();
	IsOnFrame = true;
	CurrentCursor = 0;
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);

	CursorPos = StartCursorPos;
	Cursor->On();
	Cursor->GetTransform()->SetLocalPosition(StartCursorPos);
}

void FieldCommandUI::Off()
{
	GameEngineActor::Off();
	Cursor->Off();
}

void FieldCommandUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetWorldScale({ 196, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 36 });
	WindowRender->SetSprite("CommandUI.png", 4);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetWorldScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("CommandSelect.png");

	ButtonSystem = GetLevel()->CreateActor<UIButtonSystem>();
	ButtonSystem->GetTransform()->SetParent(GetTransform());

	ButtonCols.resize(5);
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		ButtonCols[i]->GetTransform()->SetLocalPosition({ 330, 164.0f - (64 * i) });
		ButtonCols[i]->GetTransform()->SetLocalScale({ 200, 64 });
		ButtonCols[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(ButtonCols[i],
			[=] {
				CurrentCursor = i;
				SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
				CursorPos = { StartCursorPos + float4::Down * (64.0f * CurrentCursor) };
			},
			[this] {
				CommandFunctions[CurrentCursor]();
			}
			);

	}

	GameEngineActor::Off();
}

void FieldCommandUI::Update(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA"))
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

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		CursorTimer = 0;
		if (CurrentCursor == CommandFunctions.size() - 1)
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