#include "PrecompileHeader.h"
#include "LevelUpUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "NumberActor.h"
#include "BattleAnimationLevel.h"
LevelUpUI::LevelUpUI()
{
}

LevelUpUI::~LevelUpUI()
{
}

void LevelUpUI::LevelUpStart(Unit& _UnitData)
{
	On();
	FSM.ChangeState("LevelUpText");

	// 초상화 지정
	std::string TextStr = "Portrait_";
	TextStr += _UnitData.GetName();
	TextStr += ".png";
	UIPortraitRender->SetTexture(TextStr);

	UpStat = _UnitData.GetLevelUpData();
	MainStat Stat = _UnitData.GetMainStat() - UpStat;

	Number_Level->SetValue(_UnitData.GetLevel() - 1);
	for (int i = 0; i < 8; i++)
	{
		Number_Stats[i]->SetValue(Stat.Array[i]);
	}
}

void LevelUpUI::ClassChangeStart(Unit& _UnitData)
{
	On();
	FSM.ChangeState("LevelUIOn");
	Count = 0;
	// 초상화 지정
	std::string TextStr = "Portrait_";
	TextStr += _UnitData.GetName();
	TextStr += ".png";
	UIPortraitRender->SetTexture(TextStr);

	UpStat = _UnitData.GetLevelUpData();
	MainStat Stat = _UnitData.GetMainStat() - UpStat;

	Number_Level->SetValue(_UnitData.GetLevel());
	for (int i = 0; i < 8; i++)
	{
		Number_Stats[i]->SetValue(Stat.Array[i]);
	}
}

void LevelUpUI::Start()
{
	CurLevel = dynamic_cast<BattleAnimationLevel*>(GetLevel());

	UIBack = CreateComponent<GameEngineUIRenderer>(14);
	UIBack->SetTexture("Black.png");
	UIBack->GetTransform()->SetLocalScale({ 960, 640 });
	UIBack->ColorOptionValue.MulColor.a = 0.0f;

	LevelUpImage = CreateComponent<GameEngineUIRenderer>(16);
	LevelUpImage->SetTexture("LevelUpText.png");
	LevelUpImage->GetTransform()->SetLocalScale({ 564, 124 });

	UIRender = CreateComponent<GameEngineUIRenderer>(15);
	UIRender->SetTexture("LevelUPUI.png");
	UIRender->GetTransform()->SetLocalPosition({ -178, -64 });
	UIRender->GetTransform()->SetLocalScale({ 540, 412 });
	UIRender->Off();

	UITextRender = CreateComponent<GameEngineUIRenderer>(17);
	UITextRender->SetTexture("LevelUPUIText.png");
	UITextRender->GetTransform()->SetParent(UIRender->GetTransform(), false);

	UIPortraitRender = CreateComponent<GameEngineUIRenderer>(15);
	UIPortraitRender->GetTransform()->SetWorldScale({ 384, 320 });
	UIPortraitRender->GetTransform()->SetLocalPosition({ 272, -160 });
	UIPortraitRender->Off();

	Number_Level = CurLevel->CreateActor<NumberActor>();
	Number_Level->NumberCreate(17);
	Number_Level->GetTransform()->SetParent(UIRender->GetTransform(), false);
	Number_Level->GetTransform()->SetLocalPosition({ 184, 156 });
	Number_Level->GetTransform()->SetWorldScale(float4::One);

	Number_Stats.resize(8);
	UpStatBacks.resize(8);
	UpStatArrows.resize(8);
	for (int i = 0; i < 4; i++)
	{
		Number_Stats[i] = CurLevel->CreateActor<NumberActor>();
		Number_Stats[i]->NumberCreate(17);
		Number_Stats[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		Number_Stats[i]->GetTransform()->SetLocalPosition({ -82, 32.0f - (64.0f * i)});
		Number_Stats[i]->GetTransform()->SetWorldScale(float4::One);

		UpStatBacks[i] = CreateComponent<GameEngineUIRenderer>(16);
		UpStatBacks[i]->SetTexture("StatUP.png");
		UpStatBacks[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		UpStatBacks[i]->GetTransform()->SetLocalPosition({ -132, 20.0f - (64.0f * i) });
		UpStatBacks[i]->GetTransform()->SetWorldScale({ 184, 16 });
		UpStatBacks[i]->Off();

		UpStatArrows[i] = CreateComponent<GameEngineUIRenderer>(18);
		UpStatArrows[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		UpStatArrows[i]->GetTransform()->SetLocalPosition({ -48, 32.0f - (64.0f * i) });
		UpStatArrows[i]->GetTransform()->SetWorldScale({ 28, 40 });
		UpStatArrows[i]->CreateAnimation({ .AnimationName = "Default", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		UpStatArrows[i]->ChangeAnimation("Default");
		UpStatArrows[i]->Off();
	}
	for (int i = 4; i < 8; i++)
	{
		Number_Stats[i] = CurLevel->CreateActor<NumberActor>();
		Number_Stats[i]->NumberCreate(17);
		Number_Stats[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		Number_Stats[i]->GetTransform()->SetLocalPosition({ 174, 32.0f - (64.0f * (i - 4)) });
		Number_Stats[i]->GetTransform()->SetWorldScale(float4::One);

		UpStatBacks[i] = CreateComponent<GameEngineUIRenderer>(16);
		UpStatBacks[i]->SetTexture("StatUP.png");
		UpStatBacks[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		UpStatBacks[i]->GetTransform()->SetLocalPosition({ 124, 20.0f - (64.0f * (i - 4)) });
		UpStatBacks[i]->GetTransform()->SetWorldScale({ 184, 16 });
		UpStatBacks[i]->Off();

		UpStatArrows[i] = CreateComponent<GameEngineUIRenderer>(18);
		UpStatArrows[i]->GetTransform()->SetParent(UIRender->GetTransform(), false);
		UpStatArrows[i]->GetTransform()->SetLocalPosition({ 208, 32.0f - (64.0f * (i - 4)) });
		UpStatArrows[i]->GetTransform()->SetWorldScale({ 28, 40 });
		UpStatArrows[i]->CreateAnimation({ .AnimationName = "Default", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		UpStatArrows[i]->ChangeAnimation("Default");
		UpStatArrows[i]->Off();
	}


	FSM.CreateState(
		{
			.Name = "LevelUpText",
			.Start = [this]()
		{
			UIRender->Off();
			UIPortraitRender->Off();
			LevelUpImage->GetTransform()->SetLocalPosition({762, 64});
			LevelUpImage->On();
			Timer = 0;
			Count = -1;
			TimeEvent.Clear();
			TimeEvent.AddEvent(1.2f, std::bind(&GameEngineFSM::ChangeState, &FSM, "LevelUpText2"));
		},
			.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 3.0f;
			LevelUpImage->GetTransform()->SetLocalPosition(float4::LerpClamp({ 762, 64 }, {0, 64}, Timer));

			if (1 < Timer)
			{
				LevelUpImage->ColorOptionValue.MulColor.a = 1.0f;
				UIBack->ColorOptionValue.MulColor.a = 0.5f;
			}
			else
			{
				LevelUpImage->ColorOptionValue.MulColor.a = 1.0f * Timer;
				UIBack->ColorOptionValue.MulColor.a = 0.5f * Timer;
			}
		},
			.End = [this]()
		{

		}
		});

	FSM.CreateState(
		{
			.Name = "LevelUpText2",
			.Start = [this]()
		{
			LevelUpImage->GetTransform()->SetLocalPosition({0, 64});
			Timer = 0;
			TimeEvent.AddEvent(1.0f, std::bind(&GameEngineFSM::ChangeState, &FSM, "LevelUIOn"));
		},
			.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 2.5f;
			LevelUpImage->GetTransform()->SetLocalPosition(float4::LerpClamp({ 0, 64 }, {-780, 64}, Timer));
			if (1 < Timer)
			{
				LevelUpImage->ColorOptionValue.MulColor.a = 0.0f;
			}
			else
			{
				LevelUpImage->ColorOptionValue.MulColor.a = 1 - Timer;
			}
		},
			.End = [this]()
		{
			LevelUpImage->GetTransform()->SetLocalPosition({-780, 64});
		}
		});

	FSM.CreateState(
		{
			.Name = "LevelUIOn",
			.Start = [this]()
		{
			LevelUpImage->Off();
			UIRender->On();
			UIPortraitRender->On();
			UIRender->GetTransform()->SetLocalPosition({ -612, -64 });
			UIPortraitRender->GetTransform()->SetLocalPosition({ 272, -500 });
			TimeEvent.AddEvent(0.6f, std::bind(&GameEngineFSM::ChangeState, &FSM, "StatCheck"));
			Timer = 0;
			for (int i = 0; i < 8; i++)
			{
				UpStatBacks[i]->Off();
				UpStatArrows[i]->Off();
			}
		},
			.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 3.0f;

			UIRender->GetTransform()->SetLocalPosition(float4::LerpClamp({ -612, -64 }, { -178, -64 }, Timer));
			UIPortraitRender->GetTransform()->SetLocalPosition(float4::LerpClamp({ 272, -500 }, { 272, -160 }, Timer));
		},
			.End = [this]()
		{

		}
		});

	FSM.CreateState(
		{
			.Name = "StatCheck",
			.Start = [this]()
		{
			if (Count == Number_Stats.size())
			{
				FSM.ChangeState("ButtonWait");
				return;
			}

			if (Count == -1)
			{
				Number_Level->SetValue(Number_Level->GetValue() + 1);
				TimeEvent.AddEvent(0.5f, std::bind(&GameEngineFSM::ChangeState, &FSM, "StatCheck"));
			}
			else if (0 < UpStat.Array[Count])
			{
				Number_Stats[Count]->SetValue(Number_Stats[Count]->GetValue() + UpStat.Array[Count]);
				UpStatBacks[Count]->On();
				UpStatArrows[Count]->On();
				TimeEvent.AddEvent(0.5f, std::bind(&GameEngineFSM::ChangeState, &FSM, "StatCheck"));
			}
			else
			{
				Count++;
				FSM.ChangeState("StatCheck");
				return;
			}
			Count++;

		},
			.Update = [this](float _DeltaTime)
		{

		},
			.End = [this]()
		{

		}
		});

	FSM.CreateState(
		{
			.Name = "ButtonWait",
			.Start = [this]()
		{
		},
			.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
			{
				CurLevel->BattleEnd();
				FSM.ChangeState("End");
			}
		},
			.End = [this]()
		{
		}
		});

	FSM.CreateState(
		{
			.Name = "End",
			.Start = [this]()
		{
		},
		.Update = [this](float _DeltaTime)
		{
		},
			.End = [this]()
		{
			UIRender->Off();
			UIPortraitRender->Off();
		}
		});
}

void LevelUpUI::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
	TimeEvent.Update(_DeltaTime);
}


