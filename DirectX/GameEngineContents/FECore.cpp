#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include "TitleLevel.h"
#include "BattleLevel.h"
#include "BattleAnimationLevel.h"
#include "FERandom.h"
#include "DebugWindow.h"
#include "StageSelectWindow.h"
#include "Stage0.h"
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

		Window->Funcions[0] = [] {
			GameEngineCore::ChangeLevel("Stage0");
		};

	}
	

	FERandom::SetSeed(0);
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<BattleLevel>();
	GameEngineCore::CreateLevel<BattleAnimationLevel>();
	GameEngineCore::CreateLevel<Stage0>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void FECore::GameEnd()
{

}

void FECore::ResourcesCreate()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Shader");

	std::shared_ptr<GameEnginePixelShader> Shader = GameEnginePixelShader::Load(NewDir.GetPlusFileName("EffectPixelShader.hlsl").GetFullPath(), "Texture_PS");
 	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureEffect");

	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("EffectPixelShader.hlsl");
	Pipe->SetBlendState("AlphaBlend");
	Pipe->SetDepthState("EngineDepth");
}
