#include "PrecompileHeader.h"
#include "SpriteRenderer.h"
SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Start()
{
	GameEngineRenderer::Start();
	
	SetMesh("Rect");
	SetPipeLine("2DTextureEffect");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("EffectData", EffectDataValue);
	GetShaderResHelper().SetConstantBufferLink("FlipData", Flip);
}
