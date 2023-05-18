#include "PrecompileHeader.h"
#include "TestLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "DebugWindow.h"
TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}


void TestLevel::Start()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });


	// 타이틀 이미지
	std::shared_ptr<GameEngineActor> TitleActor = CreateActor<GameEngineActor>();
	std::shared_ptr<GameEngineSpriteRenderer> TitleRender = TitleActor->CreateComponent<GameEngineSpriteRenderer>();
	TitleRender->SetTexture("TitleImage.png");
	TitleRender->GetTransform()->SetWorldScale({ 960, 640 });

}

void TestLevel::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsAnyKey())
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}
}
