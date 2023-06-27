#include "PrecompileHeader.h"
#include "LevelUpUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "NumberActor.h"
#include "BattleAnimationLevel.h"
#include "TextRenderer.h"
LevelUpUI::LevelUpUI()
{
}

LevelUpUI::~LevelUpUI()
{
}

void LevelUpUI::LevelUpStart(Unit& _UnitData, const std::string_view& _Name)
{
	On();
	FSM.ChangeState("LevelUpText");

	UnitName->SetText(_Name);
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

void LevelUpUI::ClassChangeStart(Unit& _UnitData, const std::string_view& _Name)
{
	On();
	FSM.ChangeState("LevelUIOn");
	Count = 0;
	UnitName->SetText(_Name);
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
	UIRender->GetTransform()->SetLocalScale({ 540, 412, 1 });
	UIRender->Off();

	UITextRender = CreateComponent<GameEngineUIRenderer>(17);
	UITextRender->SetTexture("LevelUPUIText.png");
	UITextRender->GetTransform()->SetParent(UIRender->GetTransform(), false);

	UIPortraitRender = CreateComponent<GameEngineUIRenderer>(15);
	UIPortraitRender->GetTransform()->SetWorldScale({ 384, 320 });
	UIPortraitRender->GetTransform()->SetLocalPosition({ 272, -160 });
	UIPortraitRender->Off();

	UnitName = CreateComponent<TextRenderer>(16);
	UnitName->GetTransform()->SetParent(UIRender->GetTransform(), false);
	UnitName->GetTransform()->SetLocalPosition({ -0.34f, 0.45f });
	UnitName->GetTransform()->SetWorldScale(float4::One);
	UnitName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);

	Number_Level = CurLevel->CreateActor<NumberActor>();
	Number_Level->NumberCreate(17);
	Number_Level->GetTransform()->SetLocalPosition({ 184 -178, 156 -64 });
	Number_Level->GetTransform()->SetWorldScale(float4::One);
	Number_Level->GetTransform()->SetParent(UIRender->GetTransform());

	Number_Stats.resize(8);
	UpStatBacks.resize(8);
	UpStatArrows.resize(8);
	for (int i = 0; i < 4; i++)
	{
		Number_Stats[i] = CurLevel->CreateActor<NumberActor>();
		Number_Stats[i]->NumberCreate(17);
		Number_Stats[i]->GetTransform()->SetLocalPosition({ -82 - 178, 32.0f - 64.0f - (64.0f * i)});
		Number_Stats[i]->GetTransform()->SetWorldScale(float4::One);
		Number_Stats[i]->GetTransform()->SetParent(UIRender->GetTransform());

		UpStatBacks[i] = CreateComponent<GameEngineUIRenderer>(16);
		UpStatBacks[i]->SetTexture("StatUP.png");
		UpStatBacks[i]->GetTransform()->SetLocalPosition({ -132 - 178, 20.0f - 64.0f - (64.0f * i) });
		UpStatBacks[i]->GetTransform()->SetLocalScale({ 184, 16 });
		UpStatBacks[i]->GetTransform()->SetParent(UIRender->GetTransform());
		UpStatBacks[i]->Off();

		UpStatArrows[i] = CreateComponent<GameEngineUIRenderer>(18);
		UpStatArrows[i]->GetTransform()->SetLocalPosition({ -48 - 178, 32.0f - 64.0f - (64.0f * i) });
		UpStatArrows[i]->GetTransform()->SetLocalScale({ 28, 40 });
		UpStatArrows[i]->CreateAnimation({ .AnimationName = "Default", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		UpStatArrows[i]->ChangeAnimation("Default");
		UpStatArrows[i]->GetTransform()->SetParent(UIRender->GetTransform());
		UpStatArrows[i]->Off();
	}
	for (int i = 4; i < 8; i++)
	{
		Number_Stats[i] = CurLevel->CreateActor<NumberActor>();
		Number_Stats[i]->NumberCreate(17);
		Number_Stats[i]->GetTransform()->SetLocalPosition({ 174 - 178, 32.0f - 64.0f - (64.0f * (i - 4)) });
		Number_Stats[i]->GetTransform()->SetWorldScale(float4::One);
		Number_Stats[i]->GetTransform()->SetParent(UIRender->GetTransform());

		UpStatBacks[i] = CreateComponent<GameEngineUIRenderer>(16);
		UpStatBacks[i]->SetTexture("StatUP.png");
		UpStatBacks[i]->GetTransform()->SetLocalPosition({ 124 - 178, 20.0f - 64.0f- (64.0f * (i - 4)) });
		UpStatBacks[i]->GetTransform()->SetWorldScale({ 184, 16 });
		UpStatBacks[i]->GetTransform()->SetParent(UIRender->GetTransform());
		UpStatBacks[i]->Off();

		UpStatArrows[i] = CreateComponent<GameEngineUIRenderer>(18);
		UpStatArrows[i]->GetTransform()->SetLocalPosition({ 208 - 178, 32.0f - 64.0f - (64.0f * (i - 4)) });
		UpStatArrows[i]->GetTransform()->SetLocalScale({ 28, 40 });
		UpStatArrows[i]->CreateAnimation({ .AnimationName = "Default", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		UpStatArrows[i]->ChangeAnimation("Default");
		UpStatArrows[i]->GetTransform()->SetParent(UIRender->GetTransform());
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
			GameEngineSound::Play("LevelUp.wav");
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
				GameEngineSound::Play("StatUp.wav");

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


