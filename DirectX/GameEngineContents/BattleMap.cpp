#include "PrecompileHeader.h"
#include "BattleMap.h"
#include "SpriteRenderer.h"
#include "ContentsEnum.h"
BattleMap::BattleMap()
{
}

BattleMap::~BattleMap()
{
}

void BattleMap::Start()
{
	Renderer = CreateComponent<SpriteRenderer>(RenderOrder::Map);
	Renderer->SetTexture("Stage0.png");
	Renderer->SetWorldScale(MapScaleFloat4);
	
	//GetTransform()->SetLocalPosition({ 448, 288});
	GetTransform()->SetLocalPosition({ MapScaleFloat4.hx() - 32, MapScaleFloat4.hy() - 32 });


	TerrainData.resize(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	TerrainData[i].resize(15);
	//}

	TerrainData[0] = { Terrain::Cliff, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Cliff, Terrain::Cliff, Terrain::Cliff, Terrain::Plain, Terrain::House };
	TerrainData[1] = { Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Forest, Terrain::Plain };
	TerrainData[2] = { Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[6] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[7] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Gate, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Mountain };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Peak, Terrain::Peak };
	TerrainData[9] = { Terrain::Mountain, Terrain::Mountain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak };
}

int BattleMap::GetTerrainCostFoot(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::Plain:
	case Terrain::Fort:
	case Terrain::Gate:
	case Terrain::House:
	case Terrain::Bridge:
		return 1;
	case Terrain::Forest:
		return 2;
	case Terrain::Mountain:
		return 4;
	case Terrain::River:
		return 5;
	case Terrain::None:
	case Terrain::Cliff:
	case Terrain::Peak:
	case Terrain::Door:
	case Terrain::Sea:
	case Terrain::Wall:
	default:
		return 99;
	}
}

int BattleMap::GetTerrainDodge(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::Plain:
	case Terrain::None:
	case Terrain::Cliff:
	case Terrain::Door:
	case Terrain::Bridge:
	case Terrain::Wall:
		return 0;
	case Terrain::House:
	case Terrain::Sea:
	case Terrain::River:
		return 10;
	case Terrain::Gate:
	case Terrain::Forest:
	case Terrain::Fort:
		return 20;
	case Terrain::Mountain:
		return 30;
	case Terrain::Peak:
		return 40;
	default:
		return 0;
	}
}

int BattleMap::GetTerrainDef(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::Plain:
	case Terrain::None:
	case Terrain::Cliff:
	case Terrain::Door:
	case Terrain::Bridge:
	case Terrain::River:
	case Terrain::Wall:
	case Terrain::House:
	case Terrain::Sea:
		return 0;
	case Terrain::Forest:
	case Terrain::Mountain:
		return 1;
	case Terrain::Peak:
	case Terrain::Fort:
		return 2;
	case Terrain::Gate:
		return 3;
	default:
		return 0;
	}
}
