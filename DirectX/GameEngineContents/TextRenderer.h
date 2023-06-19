#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
// ���� :
class TextRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	TextRenderer();
	~TextRenderer();

	// delete Function
	TextRenderer(const TextRenderer& _Other) = delete;
	TextRenderer(TextRenderer&& _Other) noexcept = delete;
	TextRenderer& operator=(const TextRenderer& _Other) = delete;
	TextRenderer& operator=(TextRenderer&& _Other) noexcept = delete;

	void Setting(const std::string_view& _Font, float _FontScale, float4 _FontColor, float4 _OutLineColor, FontAligned _Aligned);
	void SetFont(const std::string_view& _Font);
	void SetText(const std::string_view& _Text);
	void SetScale(float _FontScale);
	void SetColor(float4 _FontColor);
	void SetOutLine(float4 _FontColor);
	void SetAligned(FontAligned _Aligned);

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineFontRenderer> FontRender;
	std::vector<std::shared_ptr<GameEngineFontRenderer>> OutlineRenders;
};
