#include "PrecompileHeader.h"
#include "MapUnit.h"

MapUnit::MapUnit() 
{
}

MapUnit::~MapUnit() 
{
}

static const float TileScale = 64.0f;

void MapUnit::SetMapPos(int2 _Value)
{
	MapPos = _Value;
	EndPos = MapPos * TileScale;
	GetTransform()->SetLocalPosition(MapPos * TileScale);
}

void MapUnit::MoveMapPos(int2 _Value)
{
	SetMapPos(MapPos + _Value);
}

void MapUnit::SetMapPosLerp(int2 _Value)
{
	IsMove = true;
	int2 StartIntPos = MapPos;
	StartPos = GetTransform()->GetLocalPosition();
	MapPos = _Value;
	EndPos = MapPos * TileScale;
	MoveTimer = 0;

	int2 Dir = (MapPos - StartIntPos).Normalize();
	
	SetMoveDir(Dir);

}

void MapUnit::MoveMapPosLerp(int2 _Value)
{
	SetMapPosLerp(MapPos + _Value);
}

void MapUnit::Update(float _DeltaTime)
{
	if (false == IsMove) { return; }
	MoveTimer += MoveSpeed * _DeltaTime;
	GetTransform()->SetLocalPosition(float4::LerpClamp(StartPos, EndPos, MoveTimer));
	
	if (1 < MoveTimer)
	{
		IsMove = false;
	}
}


