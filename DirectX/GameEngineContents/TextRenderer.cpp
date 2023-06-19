#include "PrecompileHeader.h"
#include "TextRenderer.h"
TextRenderer::TextRenderer() 
{
}

TextRenderer::~TextRenderer() 
{
}

void TextRenderer::Start()
{
	FontRender = GetActor()->CreateComponent<GameEngineFontRenderer>(1);
	FontRender->GetTransform()->SetParent(GetTransform());

	OutlineRenders.resize(4);
	float4 Pos[4] = { {4, 0}, {-4, 0}, {0, 4}, {0, -4} };
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i] = GetActor()->CreateComponent<GameEngineFontRenderer>(0);
		OutlineRenders[i]->GetTransform()->SetParent(GetTransform());
		OutlineRenders[i]->GetTransform()->SetLocalPosition(Pos[i]);
		OutlineRenders[i]->Off();
	}
}

void TextRenderer::Setting(const std::string_view& _Font, float _FontScale, float4 _FontColor, float4 _OutLineColor, FontAligned _Aligned)
{
	SetFont(_Font);
	SetScale(_FontScale);
	SetColor(_FontColor);
	if (_OutLineColor.a != 0)
	{
		SetOutLine(_OutLineColor);
	}
	SetAligned(_Aligned);
}

void TextRenderer::SetFont(const std::string_view& _Font)
{
	FontRender->SetFont(_Font);
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetFont(_Font);
	}
}

void TextRenderer::SetText(const std::string_view& _Text)
{
	FontRender->SetText(_Text);
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetText(_Text);
	}
}

void TextRenderer::SetScale(float _FontScale)
{
	FontRender->SetScale(_FontScale);
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetScale(_FontScale);
	}
}

void TextRenderer::SetColor(float4 _FontColor)
{
	FontRender->SetColor(_FontColor);
}

void TextRenderer::SetOutLine(float4 _FontColor)
{
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetColor(_FontColor);
		OutlineRenders[i]->On();
	}
}

void TextRenderer::SetAligned(FontAligned _Aligned)
{
	FontRender->SetAligned(_Aligned);
}
