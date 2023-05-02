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
	SetPipeLine("2DTextureEffect");
	GetShaderResHelper().SetConstantBufferLink("EffectData", EffectDataValue);
}
