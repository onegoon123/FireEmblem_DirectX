#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineFont.h>
#include "TitleLevel.h"
#include "BattleAnimationLevel.h"
#include "FERandom.h"
#include "DebugWindow.h"
#include "StageSelectWindow.h"
#include "Stage0.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Stage7.h"
#include "Stage8.h"
#include "Stage9.h"
#include "Stage10.h"
#include "TestStage.h"

FECore::FECore()
{
	
}

FECore::~FECore()
{
}

void FECore::GameStart()
{
	new int();
	ResourcesCreate();

	GameEngineGUI::GUIWindowCreate<DebugWindow>("DebugWindow");
	GameEngineGUI::GUIWindowCreate<StageSelectWindow>("StageSelectWindow");

	std::shared_ptr<StageSelectWindow> Window = GameEngineGUI::FindGUIWindowConvert<StageSelectWindow>("StageSelectWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 생성 실패");
		}

		Window->Funcions = [](const std::string_view& _Name) {
			GameEngineCore::ChangeLevel(_Name);
		};

	}


	FERandom::SetSeed(0);
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<BattleAnimationLevel>();
	GameEngineCore::CreateLevel<Stage0>();
	GameEngineCore::CreateLevel<Stage1>();
	GameEngineCore::CreateLevel<Stage2>();
	GameEngineCore::CreateLevel<Stage3>();
	GameEngineCore::CreateLevel<Stage4>();
	GameEngineCore::CreateLevel<Stage5>();
	GameEngineCore::CreateLevel<Stage6>();
	GameEngineCore::CreateLevel<Stage7>();
	GameEngineCore::CreateLevel<Stage8>();
	GameEngineCore::CreateLevel<Stage9>();
	GameEngineCore::CreateLevel<Stage10>();
	GameEngineCore::CreateLevel<TestStage>();
	GameEngineCore::ChangeLevel("TitleLevel");

	GameEngineFont::Load("Silhoua14");
}

void FECore::GameEnd()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Font");
	if (0 == RemoveFontResourceA(NewDir.GetPlusFileName("Silhoua14.ttf").GetFullPath().data()))
	{
		MsgTextBox("폰트삭제에 실패했습니다.");
	}
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);
}

void FECore::ResourcesCreate()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Font");
	if (0 == AddFontResourceA(NewDir.GetPlusFileName("Silhoua14.ttf").GetFullPath().data()))
	{
		MsgTextBox("폰트설치에 실패했습니다.");
	}
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);
	

	NewDir.MoveParent();
	NewDir.Move("Shader");

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}

	}


	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureEffect");

	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("EffectPixelShader.hlsl");
	Pipe->SetBlendState("AlphaBlend");
	Pipe->SetDepthState("EngineDepth");


	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Fade");

		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}



	return;
}
