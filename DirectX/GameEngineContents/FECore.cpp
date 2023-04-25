#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include "TitleLevel.h"
#include "BattleLevel.h"
#include "FERandom.h"
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
	FERandom::SetSeed(0);
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<BattleLevel>();
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
	GameEnginePixelShader::Load(NewDir.GetPlusFileName("TextureShaderGrayScale.hlsl").GetFullPath(), "TextureGray_PS");
	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureGray");
	
	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("TextureShaderGrayScale.hlsl");
	Pipe->SetBlend("AlphaBlend");

	GameEnginePixelShader::Load(NewDir.GetPlusFileName("EffectPixelShader.hlsl").GetFullPath(), "Texture_PS");
	Pipe = GameEngineRenderingPipeLine::Create("2DTextureEffect");

	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("EffectPixelShader.hlsl");
	Pipe->SetBlend("AlphaBlend");
}
