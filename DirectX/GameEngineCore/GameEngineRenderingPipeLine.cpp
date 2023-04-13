#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// 매쉬 + 머티리얼

// 점에 대한 정보를 준비하고
void GameEngineRenderingPipeLine::InputAssembler1()
{

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBufferPtr->Setting();
	// GameEngineDevice::GetContext()->IASetVertexBuffers()
}
// 로컬에 존재하는 점을 우리가 만든 행렬을 통해서 변환하고.
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않아서 버텍스 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	VertexShaderPtr->Setting();
	// GameEngineDevice::GetContext()->VSSetShader
}

// 점의 정보를 토대로 어떤 순서로 그릴지 정하고
void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("인덱스 버퍼가 존재하지 않아서 인풋 어셈블러2 과정을 실행할 수 없습니다.");
		return;
	}

	IndexBufferPtr->Setting();
}

// 여기서부터
void GameEngineRenderingPipeLine::HullShader()
{

}
void GameEngineRenderingPipeLine::Tessellator()
{

}
void GameEngineRenderingPipeLine::DomainShader()
{

}
void GameEngineRenderingPipeLine::GeometryShaeder()
{

}
// 여기까지는 화면과는 사실

// w나누기를 해줍니다. 
// 뷰포트도 곱해줍니다.
// 화면 컬링 
// 픽셀 건지기
void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}


void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// GameEngineDevice::GetContext()->OMSetRenderTargets
}


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}


void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다.");
	}
}

// 매쉬 + 머티리얼
void GameEngineRenderingPipeLine::Render()
{
	// 랜더라고 하는 부분은 랜더링 파이프라인을 한바뀌 돌리는 것.
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	HullShader();
	Tessellator();
	DomainShader();
	GeometryShaeder();
	Rasterizer();
	PixelShader();
	OutputMerger();

	// 메쉬 <= 외형이 어떻게 보일것인가.
	//         픽셀건져내기할 범위를 지정하는 Rasterizer
	//         w나누기를 하고 뷰포트를 곱해서

	// 머티리얼 <= 색깔이 어떻게 나올것인가?
	//             레스터라이저 + 픽셀쉐이더 + 버텍스 쉐이더
}