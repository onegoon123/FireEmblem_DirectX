#include "PrecompileHeader.h"
#include "TextRenderer.h"

GameEngineSoundPlayer TextRenderer::TalkSound;

TextRenderer::TextRenderer() 
{
}

TextRenderer::~TextRenderer() 
{
}

void TextRenderer::Start()
{
	OutlineRenders.resize(4);
	float4 Pos[4] = { {4, 0}, {-4, 0}, {0, 4}, {0, -4} };
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i] = GetActor()->CreateComponent<GameEngineFontRenderer>(GetOrder());
		OutlineRenders[i]->GetTransform()->SetParent(GetTransform());
		OutlineRenders[i]->GetTransform()->SetLocalPosition(Pos[i]);
		OutlineRenders[i]->Off();
	}
	FontRender = GetActor()->CreateComponent<GameEngineFontRenderer>(GetOrder());
	FontRender->GetTransform()->SetParent(GetTransform());

}

void TextRenderer::Update(float _DeltaTime)
{
	FadeUpdate(_DeltaTime);
	if (false == IsTextAnim) { return; }

	Timer -= _DeltaTime;
	if (0 < Timer) { return; }
	if (Index == AnimText.size())
	{
		IsTextAnim = false;
		TalkSound.Stop();
		return;
	}

	Index++;
	Timer = AnimTime;
	SetText(AnimText.substr(0, Index), false);
}

void TextRenderer::FadeUpdate(float _DeltaTime)
{

	if (true == IsFadeIn)
	{
		FadeTimer += FadeSpeed * _DeltaTime;
		if (1 < FadeTimer)
		{
			SetColorAlpha(1);
			IsFadeIn = false;
			return;
		}
		SetColorAlpha(FadeTimer);
	}
	else if (true == IsFadeOut)
	{
		FadeTimer -= FadeSpeed * _DeltaTime;
		if (FadeTimer < 0)
		{
			SetColorAlpha(0);
			IsFadeOut = false;
			return;
		}
		SetColorAlpha(FadeTimer);
	}

}

void TextRenderer::Off()
{
	GameEngineComponent::Off();
}

//Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
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

void TextRenderer::SetText(const std::string_view& _Text, bool _Clear)
{
	if (true == TalkSound.IsValid())
	{
		TalkSound.Stop();
	}
	if (_Clear == true)
	{
		IsTextAnim = false;
		
	}
	FontRender->SetText(_Text);
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetText(_Text);
	}
}

void TextRenderer::SetText(const std::wstring_view& _Text, bool _Clear)
{
	
	if (_Clear == true)
	{
		IsTextAnim = false;
		if (true == TalkSound.IsValid())
		{
			TalkSound.Stop();
		}
	}
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

void TextRenderer::SetColorAlpha(float _Alpha)
{
	FontRender->SetAlpha(_Alpha);
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetAlpha(_Alpha);
	}
}

void TextRenderer::SetFadeIn(float _Timer)
{
	IsFadeIn = true;
	FadeTimer = 0;
	FadeSpeed = 1 / _Timer;
	SetColorAlpha(FadeTimer);
}

void TextRenderer::SetFadeOut(float _Timer)
{
	IsFadeOut = true;
	FadeTimer = 1;
	FadeSpeed = 1 / _Timer;
	SetColorAlpha(FadeTimer);
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
	for (int i = 0; i < OutlineRenders.size(); i++)
	{
		OutlineRenders[i]->SetAligned(_Aligned);
	}
}

void TextRenderer::SetTextAnim(const std::wstring_view& _Text)
{
	if (true == TalkSound.IsValid())
	{
		TalkSound.Stop();
	}
	TalkSound = GameEngineSound::Play("Talk.wav");
	TalkSound.SetLoop();
	AnimText = _Text;
	Index = 0;
	IsTextAnim = true;
	Timer = AnimTime;

	SetText(L"", false);
}

bool TextRenderer::IsAnimEnd()
{
	return false == IsTextAnim;
}
