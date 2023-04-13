#pragma once

// 설명 :
class GameEngineShader
{
public:
	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	void CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigt = 5, UINT _VersionLow = 0);
	inline void SetEntryPoint(const std::string_view& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

protected:
	// 쉐이더 코드를 2진데이터로 변형했을때 그걸 그래픽카드가 내부에 숨기고
	// 우리에게는 
	ID3DBlob* BinaryCode = nullptr;
	std::string Version = "";
	std::string EntryPoint = "";

private:
};

