#include "PrecompileHeader.h"
#include "TimeStoneUI.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "TimeCommand.h"
#include "TextRenderer.h"
#include "ContentsEnum.h"
#include "BattleLevel.h"
TimeStoneUI::TimeStoneUI()
{
}

TimeStoneUI::~TimeStoneUI()
{
}

void TimeStoneUI::Setting(BattleLevel* _Level)
{
	CurLevel = _Level;
	Rewind = std::bind(&BattleLevel::TimeStone_Rewind, _Level);
	Play = std::bind(&BattleLevel::TimeStone_Play, _Level);
	Select = std::bind(&BattleLevel::TimeStone_Select, _Level);
	Cancel = std::bind(&BattleLevel::TimeStone_Cancel, _Level);
}

void TimeStoneUI::On(bool _IsGameOver)
{
	GameEngineActor::On();
	CommandList = UnitCommand::GetCommandList();
	CommandSetting();
	IsGameOver = _IsGameOver;
}

void TimeStoneUI::Start()
{
	CommandRenders.resize(20);
	for (int i = 0; i < CommandRenders.size(); i++)
	{
		CommandRenders[i] = CreateComponent<TimeCommand>(RenderOrder::UI);
		CommandRenders[i]->GetTransform()->SetLocalPosition({ -480, i * -88.0f });
		CommandRenders[i]->GetTextRender()->Setting("Silhoua14", 45, float4::White, float4::Null, FontAligned::Left);
		CommandRenders[i]->GetTextRender()->SetText("Å×½ºÆ®");
	}

}

void TimeStoneUI::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(float4::LerpClamp(GetTransform()->GetLocalPosition(), MoveTarget, _DeltaTime * 5));
	Timer += _DeltaTime;
	if (Timer < WaitTime) { return; }

	if (PreesTime < GameEngineInput::GetPressTime("Up") || PreesTime < GameEngineInput::GetPressTime("Down"))
	{
		PressOK = true;
	}
	else if (GameEngineInput::IsFree("Up") && GameEngineInput::IsFree("Down"))
	{
		PressOK = false;
	}

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK) || GameEngineInput::IsDown("MiddleClick"))
	{
		CommandMoveUp();
		Rewind();
		return;
	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		CommandMoveDown();
		Play();
		return;
	}
	if ((GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick")) && CurFaction == Faction::Player)
	{
		if (true == IsGameOver && CurrentCursor == CommandList.size() - 1)
		{
			return;
		}
		GameEngineSound::Play("CommandSelect.wav");
		Select();
		return;
	}
	if ((GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick")) && false == IsGameOver)
	{
		GameEngineSound::Play("Cancel.wav");
		Cancel();
		return;
	}
}

void TimeStoneUI::CommandMoveUp()
{
	if (CurrentCursor == 0)
	{
		return;
	}
	GameEngineSound::Play("CommandMove.wav");
	switch (CommandList[CurrentCursor].GetTypeValue())
	{
	case CommandType::PlayerPhaseStart:
		CurFaction = Faction::Enemy;
		break;
	case CommandType::EnemyPhaseStart:
		CurFaction = Faction::Player;
		break;
	default:
		break;
	}
	CommandRenders[CurrentCursor]->Cancel();
	CurrentCursor--;
	CommandRenders[CurrentCursor]->Select(CurFaction);
	MoveTarget = { 0, 88.0f * (CurrentCursor + 1) - 40.0f };
	Timer = 0;
}

void TimeStoneUI::CommandMoveDown()
{
	if (CurrentCursor == CommandList.size() - 1)
	{
		return;
	}
	GameEngineSound::Play("CommandMove.wav");
	CommandRenders[CurrentCursor]->Cancel();
	CurrentCursor++;
	switch (CommandList[CurrentCursor].GetTypeValue())
	{
	case CommandType::PlayerPhaseStart:
		CurFaction = Faction::Player;
		break;
	case CommandType::EnemyPhaseStart:
		CurFaction = Faction::Enemy;
		break;
	default:
		break;
	}
	CommandRenders[CurrentCursor]->Select(CurFaction);
	MoveTarget = { 0, 88.0f * (CurrentCursor + 1) - 40.0f };
	Timer = 0;
}

void TimeStoneUI::CommandSetting()
{
	size_t CurSize = CommandRenders.size();

	if (CurSize < CommandList.size())
	{
		CommandRenders.resize(CommandList.size());
		for (int i = 0; i < CurSize; i++)
		{
			CommandRenders[i]->On();
			CommandRenders[i]->GetTextRender()->SetText(CommandList[i].GetRecord());
		}
		for (size_t i = CurSize; i < CommandRenders.size(); i++)
		{
			CommandRenders[i] = CreateComponent<TimeCommand>(RenderOrder::UI);
			CommandRenders[i]->GetTransform()->SetLocalPosition({ -480, i * -88.0f });
			CommandRenders[i]->GetTextRender()->Setting("Silhoua14", 45, float4::White, float4::Null, FontAligned::Left);
			CommandRenders[i]->GetTextRender()->SetText(CommandList[i].GetRecord());
		}
	}
	else
	{
		for (int i = 0; i < CommandList.size(); i++)
		{
			CommandRenders[i]->On();
			CommandRenders[i]->GetTextRender()->SetText(CommandList.operator[](i).GetRecord());
		}
		for (size_t i = CommandList.size(); i < CurSize; i++)
		{
			CommandRenders[i]->Off();
		}
	}

	CommandRenders[CurrentCursor]->Cancel();
	CurrentCursor = static_cast<int>(CommandList.size() - 1);

	CurFaction = CommandList[CurrentCursor].IsPlayerTurn() == true ? Faction::Player : Faction::Enemy;

	CommandRenders[CurrentCursor]->Select(CurFaction);
	GetTransform()->SetLocalPosition({ 0, 88.0f * (CurrentCursor + 1) - 40.0f });
	MoveTarget = { 0, 88.0f * (CurrentCursor + 1) - 40.0f };
	Timer = -0.5f;
}

