#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineVertexShader.h"


void GameEngineCore::CoreResourcesInit()
{
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f,0.0f }, float4::Red };
		ArrVertex[2] = { { 0.5f, -0.5f,0.0f }, float4::Red };
		ArrVertex[3] = { { -0.5f, -0.5f,0.0f }, float4::Red };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 3, 2 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);

	}

	{
		// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// 앞면
		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		// 뒷면
		ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

		// 왼쪽면
		ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

		// 오른쪽
		ArrVertex[12] = ArrVertex[0].RotaitonYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotaitonYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotaitonYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotaitonYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotaitonXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotaitonXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotaitonXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotaitonXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotaitonXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotaitonXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotaitonXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotaitonXDegReturn(-90.0f);

	}

	// 버텍스 쉐이더 컴파일
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");


		//for (size_t i = 0; i < Files.size(); i++)
		//{
		//}

	}

	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
		}
	}

}

void GameEngineCore::CoreResourcesEnd()
{
	GameEngineResource<GameEngineVertexShader>::ResourcesClear();
	GameEngineResource<GameEngineVertexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
	GameEngineResource<GameEngineRenderTarget>::ResourcesClear();
}