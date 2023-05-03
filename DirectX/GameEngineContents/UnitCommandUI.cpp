#include "PrecompileHeader.h"
#include "UnitCommandUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "SpriteRenderer.h"
#include "BattleLevel.h"
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
	CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });

}

void UnitCommandUI::Start()
{
	WindowRender = CreateComponent<SpriteRenderer>();
	WindowRender->GetTransform()->SetWorldScale({ 196, 292 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 64 });
	WindowRender->GetTransform()->SetWorldRotation({ 0,0 });
	WindowRender->SetTexture("Select4.png");

	SelectRender = CreateComponent<SpriteRenderer>();
	SelectRender->GetTransform()->SetWorldScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition({ 330, 152 });
	SelectRender->SetTexture("CommandSelect.png");

	CursorRender = CreateComponent<SpriteRenderer>();
	CursorRender->GetTransform()->SetWorldScale({ 64, 64 });
	CursorRender->GetTransform()->SetLocalPosition({ 224, 144 });
	CursorRender->SetTexture("CommandCursor.png");

}

void UnitCommandUI::Update(float _DeltaTime)
{

	if (GameEngineInput::IsDown("ButtonA"))
	{
		CommandFunctions[CurrentCursor]();
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