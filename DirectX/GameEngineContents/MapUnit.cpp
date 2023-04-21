#include "PrecompileHeader.h"
#include "MapUnit.h"

MapUnit::MapUnit() 
{
}

MapUnit::~MapUnit() 
{
}

static const float4 Origin = { -480, -320 };
static const float TileScale = 64.0f;

void MapUnit::SetMapPos(int2 _Value)
{
	MapPos = _Value;

	GetTransform()->SetWorldPosition(Origin + MapPos * TileScale);
}

void MapUnit::MoveMapPos(int2 _Value)
{
	SetMapPos(MapPos + _Value);
}


