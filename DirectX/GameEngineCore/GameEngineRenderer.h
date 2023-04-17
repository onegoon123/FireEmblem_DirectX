#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// 설명 :
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// 파이프라인이 세팅되어 있고
	// 어떤 쉐이더를 사용했다는 걸 알아야 하고
	// 그 쉐이더에서 어떤 텍스처를 사용했고
	// 어떤 샘플러 어떤 상수버퍼를 사용했는지를 알아야 한다.
	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _Delta) override;

private:
	// Pipe와
	// GameEngineShaderResHelper 가 합쳐져야 랜더링 이 되는 식이 됩니다.
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe;

	GameEngineShaderResHelper ShaderResHelper;
};

