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

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	SetPipeLine("2DTextureEffect");
	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("EffectData", EffectDataValue);
}

void SpriteRenderer::Update(float _Delta)
{
	GameEngineSpriteRenderer::Update(_Delta);
	//EffectDataValue.Saturation = 0;

}
