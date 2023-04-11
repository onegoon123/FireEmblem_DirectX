#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}


void GameEngineRenderer::Render(float _Delta)
{
	// 여기서 랜더링 할수 있겠지만 랜더러 못받는다.
	//여기서 하고 싶다 모든 구조를 이해하고 다 직접
	//여기를 쓴다는 ???????


	const int VertexCount = 24;

	// float4 Pos = {640, 360};

	// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
	float4 ArrVertex[VertexCount];
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


	POINT ArrPoint[VertexCount];

	GetTransform()->SetLocalScale({ 100, 100, 100 });
	// GetTransform().AddLocalRotation({ _Delta * 360.0f, _Delta * 360.0f, _Delta * 360.0f });

	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		assert(false);
		return;
	}

	std::shared_ptr<GameEngineCamera> MainCamera = Level->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	// GetTransform().SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	// GetTransform().SetViewPort(GetLevel()->GetMainCamera()->GetViewPort());

	//  버텍스 쉐이더 단계
	for (size_t i = 0; i < VertexCount; i++)
	{
		// 버텍스 쉐이더
		ArrVertex[i] = ArrVertex[i] * GetTransform()->GetWorldViewProjectionMatrixRef();
	}

	// 레스터라이저 단계
	for (size_t i = 0; i < VertexCount; i++)
	{
		// w나누기는 레스터 라이저가하기로 약속함
		// 투영행렬의 핵심
		ArrVertex[i] /= ArrVertex[i].w;

		// TransformCoord
		ArrVertex[i].w = 1.0f;

		ArrVertex[i] *= MainCamera->GetViewPort();

		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	// 색깔정하기
	// 픽셀쉐이더

	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	for (size_t i = 0; i < 6; i++)
	{
		size_t Index = i * 4;

		float4 Vector0 = ArrVertex[Index + 0];
		float4 Vector1 = ArrVertex[Index + 1];
		float4 Vector2 = ArrVertex[Index + 2];

		float4 Dir0 = Vector0 - Vector1;
		float4 Dir1 = Vector1 - Vector2;

		float4 Cross = float4::Cross3DReturn(Dir0, Dir1);
		if (0 >= Cross.z)
		{
			continue;
		}

		Polygon(Dc, &ArrPoint[i * 4], 4);
	}
}