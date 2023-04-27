#include "PrecompileHeader.h"
#include "UnitRenderer.h"
UnitRenderer::UnitRenderer() 
{
}

UnitRenderer::~UnitRenderer() 
{
}

void UnitRenderer::Start()
{
	SetPipeLine("2DTextureEffect");
	GetShaderResHelper().SetConstantBufferLink("EffectData", EffectDataValue);
}
