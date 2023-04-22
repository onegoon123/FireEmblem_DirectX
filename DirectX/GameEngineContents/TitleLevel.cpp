#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
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
		GameEngineInput::CreateKey("UpMove", VK_UP);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
		GameEngineInput::CreateKey("OK", 'Z');
		GameEngineInput::CreateKey("Cancel", 'X');
	}
	
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });


	// 타이틀 이미지
	std::shared_ptr<GameEngineActor> TitleActor = CreateActor<GameEngineActor>("TitleActor");
	std::shared_ptr<GameEngineRenderer> TitleRender = TitleActor->CreateComponent<GameEngineRenderer>();
	TitleRender->SetPipeLine("2DTexture");
	TitleRender->GetShaderResHelper().SetTexture("DiffuseTex", "TitleImage.png");
	TitleRender->GetTransform()->SetWorldScale({ 960, 640 });
}

void TitleLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("OK"))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}
}
