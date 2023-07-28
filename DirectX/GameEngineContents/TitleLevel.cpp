#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include "StageSelectWindow.h"

std::atomic_bool IsTextureLoadEnd = false;
std::atomic_bool IsSoundLoadEnd = false;

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	// 키 세팅
	{
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);
		GameEngineInput::CreateKey("Left", VK_LEFT);
		GameEngineInput::CreateKey("Right", VK_RIGHT);
		GameEngineInput::CreateKey("ButtonA", 'Z');
		GameEngineInput::CreateKey("ButtonB", 'X');
		GameEngineInput::CreateKey("ButtonY", 'C');
		GameEngineInput::CreateKey("ButtonX", 'V');
		GameEngineInput::CreateKey("ButtonL", 'A');
		GameEngineInput::CreateKey("ButtonR", 'S');
		GameEngineInput::CreateKey("Start", VK_ESCAPE);
		GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
		GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
		GameEngineInput::CreateKey("MiddleClick", VK_MBUTTON);
		GameEngineInput::CreateKey("Cheet1", VK_F1);
		GameEngineInput::CreateKey("Cheet2", VK_F2);
		GameEngineInput::CreateKey("Cheet3", VK_F3);
		GameEngineInput::CreateKey("Cheet4", VK_F4);
		GameEngineInput::CreateKey("Cheet5", '1');
	}

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });

	// 타이틀 리소스 로딩
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Title");
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		GameEngineSound::Load(Dir.GetPlusFileName("Title.mp3").GetFullPath());
	}

	// 타이틀 이미지 생성
	if (nullptr == TitleRenderer)
	{
		std::shared_ptr<GameEngineActor> TitleActor = CreateActor<GameEngineActor>();
		TitleRenderer = TitleActor->CreateComponent<GameEngineUIRenderer>();
		TitleRenderer->SetTexture("TitleImage.png");
		TitleRenderer->GetTransform()->SetWorldScale({ 960, 640 });
	}



	StateInit();

	StageResourceLoadStart();
}

void TitleLevel::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
	if (true == IsSoundLoadEnd && true == IsTextureLoadEnd)
	{
		StageSelectWindow::IsLoadingEnd = true;
	}
}

void TitleLevel::LevelChangeStart()
{
	FSM.ChangeState("Start");
	TestStage = false;
}

void TitleLevel::LevelChangeEnd()
{
	BgmPlayer.Stop();
}

void TitleLevel::StateInit()
{
	FSM.CreateState({ .Name = "Start",
		.Start = [this]
		{
			BgmPlayer = GameEngineSound::Play("Title.mp3");
			BgmPlayer.SetLoop();
			TitleRenderer->ColorOptionValue.MulColor = float4::Zero;
			Timer = 0;
		},
		.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 2;
			TitleRenderer->ColorOptionValue.MulColor = float4::One * Timer;
			if (1 < Timer)
			{
				FSM.ChangeState("Wait");
			}
		},
		.End = [this]
		{
			TitleRenderer->ColorOptionValue.MulColor = float4::One;
			Timer = 0;
		}
		});

	FSM.CreateState({ .Name = "Wait",
	.Start = [this]
	{
	},
	.Update = [this](float _DeltaTime)
	{
		if (true == GameEngineInput::IsAnyKey())
		{
			FSM.ChangeState("End");
			if (true == GameEngineInput::IsPress("Start"))
			{
				Exit = true;
			}
			if (true == GameEngineInput::IsPress("Cheet1"))
			{
				TestStage = true;
			}
		}
	},
	.End = [this]
	{
	}
		});

	FSM.CreateState({ .Name = "End",
	.Start = [this]
	{
		Timer = 0;
		BgmPlayer.SoundFadeOut(0.5f);
	},
	.Update = [this](float _DeltaTime)
	{
		if (true == GameEngineInput::IsPress("Start"))
		{
			Exit = true;
		}
		if (true == GameEngineInput::IsPress("Cheet1"))
		{
			TestStage = true;
		}
		Timer += _DeltaTime * 2;
		TitleRenderer->ColorOptionValue.MulColor = float4::One * (1.0f - Timer);
		if (1 < Timer && true == IsTextureLoadEnd && true == IsSoundLoadEnd)
		{
			FSM.ChangeState("LevelChange");
		}
	},
	.End = [this]
	{
		if (true == TestStage)
		{
			GameEngineCore::ChangeLevel("TestStage");
			return;
		}
		if (true == Exit)
		{
			GameEngineWindow::AppOff();
			return;
		}
		GameEngineCore::ChangeLevel("Stage0");

	}
		});

	FSM.CreateState({ .Name = "LevelChange",
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

	//FSM.ChangeState("Start");
}

void SoundLoad(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Battle");
	Dir.Move("Sound");
	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".mp3", ".wav" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineSound::Load(File[i].GetFullPath());
	}
	IsSoundLoadEnd = true;
}

void TextureLoad(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Character");
	std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png", });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("Battle");
	File = Dir.GetAllFile({ ".png", });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Event");
	File = Dir.GetAllFile({ ".png", });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
	IsTextureLoadEnd = true;
}


void TitleLevel::StageResourceLoadStart()
{
	GameEngineCore::JobQueue.Work(SoundLoad);
	GameEngineCore::JobQueue.Work(TextureLoad);
}

