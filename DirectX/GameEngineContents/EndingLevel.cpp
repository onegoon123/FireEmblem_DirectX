#include "PrecompileHeader.h"
#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "FadeEffect.h"
#include "TextRenderer.h"
EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });
	Fade = GetLastTarget()->CreateEffect<FadeEffect>();
	StateInit();
}

void EndingLevel::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);



	if (GameEngineInput::IsDown("Start"))
	{
		FSM.ChangeState("End");
	}
}

void EndingLevel::LevelChangeStart()
{
	if (nullptr == BackGroundRenderer)
	{
		std::shared_ptr<GameEngineActor> Actor = CreateActor<GameEngineActor>();
		BackGroundRenderer = Actor->CreateComponent<GameEngineSpriteRenderer>();
		BackGroundRenderer->SetTexture("Ending.png");
		BackGroundRenderer->GetTransform()->SetLocalScale({ 960, 1280 });
		BackGroundRenderer->GetTransform()->SetLocalPosition({ 0, -320 });
		Text = Actor->CreateComponent<TextRenderer>();
		Text->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
		Text->GetTransform()->SetLocalPosition({ 0, 64 });
	}
	Fade->FadeIn(1.0f);
	FSM.ChangeState("Scroll");
}

void EndingLevel::StateInit()
{
	FSM.CreateState({ .Name = "Wait",
		.Start = [this]
		{
		},
		.Update = [this](float _DeltaTime)
		{
		},
		.End = [this]
		{
		}
		});
	FSM.CreateState({ .Name = "Scroll",
		.Start = [this]
		{
			Timer = 0;
			BgmPlayer = GameEngineSound::Play("EndingThema.mp3");
			CreditsEventInit();
		},
		.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 0.05f;
			BackGroundRenderer->GetTransform()->SetLocalPosition(float4::LerpClamp({ 0, -320 }, { 0, 320 }, Timer));

			if (1.0f < Timer)
			{
				FSM.ChangeState("End");
			}
		},
		.End = [this]
		{
		}
		});

	FSM.CreateState({ .Name = "End",
		.Start = [this]
		{
			TimeEvent.AddEvent(1.0f, std::bind(&GameEngineCore::ChangeLevel, "TitleLevel"));
			Fade->FadeOut(1.0f);
			BgmPlayer.SoundFadeOut(1.0f);
		},
		.Update = [this](float _DeltaTime)
		{
		},
		.End = [this]
		{
		}
		});

	FSM.ChangeState("Wait");
}

void EndingLevel::CreditsEventInit()
{
	TimeEvent.AddEvent(1.0f, [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
		{
			Text->SetText(L"원작\n\nIntelligent Systems Co., Ltd.");
			Text->SetFadeIn(1.0f);
		});
	TimeEvent.AddEvent(5.0f, [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
		{
			Text->SetFadeOut(1.0f);
		});
	TimeEvent.AddEvent(7.0f, [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
		{
			Text->SetText(L"제작\n\n김경학");
			Text->SetFadeIn(1.0f);
		});

	TimeEvent.AddEvent(11.0f, [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
		{
			Text->SetFadeOut(1.0f);
		});

	TimeEvent.AddEvent(12.5f, [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
		{
			Text->GetTransform()->SetLocalPosition(float4::Zero);
			Text->SetText(L"THANKS FOR PLAYING");
			Text->SetFadeIn(1.0f);
		});
}
