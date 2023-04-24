#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include "TitleLevel.h"
#include "BattleLevel.h"
FECore::FECore()
{
}

FECore::~FECore()
{
}

void FECore::GameStart()
{
	new int();

	CreatePipeLine();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<BattleLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void FECore::GameEnd()
{

}

void FECore::CreatePipeLine()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Shader");
	GameEnginePixelShader::Load(NewDir.GetPlusFileName("TextureShaderGrayScale.hlsl").GetFullPath(), "TextureGray_PS");
	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureGray");
	
	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("EngineBase");
	Pipe->SetPixelShader("TextureShaderGrayScale.hlsl");

	GameEnginePixelShader::Load(NewDir.GetPlusFileName("EffectPixelShader.hlsl").GetFullPath(), "Texture_PS");
	Pipe = GameEngineRenderingPipeLine::Create("2DTextureEffect");

	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("EngineBase");
	Pipe->SetPixelShader("EffectPixelShader.hlsl");
}
