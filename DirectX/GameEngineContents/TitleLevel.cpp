#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "DebugWindow.h"
TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	// 리소스 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

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
		GameEngineInput::CreateKey("Start", VK_RETURN);
		GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
		GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
	}
	
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });


	// 타이틀 이미지
	std::shared_ptr<GameEngineActor> TitleActor = CreateActor<GameEngineActor>("TitleActor");
	std::shared_ptr<GameEngineSpriteRenderer> TitleRender = TitleActor->CreateComponent<GameEngineSpriteRenderer>();
	TitleRender->SetTexture("TitleImage.png");
	TitleRender->GetTransform()->SetWorldScale({ 960, 640 });


	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 테스트 코드 미작동");
		}

		std::function<void()> Function;
		Function = []() {
			MsgTextBox("버튼누름");
		};
		Window->Test = Function;

	}
}

void TitleLevel::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown("ButtonA") || true == GameEngineInput::IsDown("Start"))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}
}
