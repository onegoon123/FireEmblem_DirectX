#include "BattleActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>6
BattleActor::BattleActor()
{
}

BattleActor::~BattleActor()
{
}

void BattleActor::Start()
{
}

void BattleActor::Update(float _DeltaTime)
{
}
float Angle = 0.0f;
float Scale = 100.0f;
void BattleActor::Render(float _DeltaTime)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// Rectangle(Dc, 0, 0, 100, 100);

	const int VertexCount = 4;

	float4 Pos = { 640, 360 };

	// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
	float4 ArrVertex[VertexCount];
	ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
	ArrVertex[1] = { 0.5f, -0.5f,0.5f };
	ArrVertex[2] = { 0.5f, 0.5f,0.5f };
	ArrVertex[3] = { -0.5f, 0.5f,0.5f };

	POINT ArrPoint[VertexCount];

	Angle += _DeltaTime * 360.0f;

	Scale += _DeltaTime * 10.0f;

	// 크자이공부

	// 크기를 키우고
	// 회전시킨다음
	// 이동하고
	// 공전시키고
	// 부모의 변환을 적용시킨다.
	// 공간변환의 순서.

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i] *= Scale;
		ArrVertex[i].RotaitonXDeg(Angle*0.1f);
		ArrVertex[i].RotaitonYDeg(Angle*0.2f);
		ArrVertex[i].RotaitonZDeg(Angle*0.3f);
		ArrVertex[i] += Pos;


		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	Polygon(Dc, ArrPoint, VertexCount);
}
