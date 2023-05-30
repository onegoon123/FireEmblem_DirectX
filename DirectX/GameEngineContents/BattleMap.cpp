#include "PrecompileHeader.h"
#include "BattleMap.h"
#include "SpriteRenderer.h"
#include "ContentsEnum.h"
BattleMap::BattleMap()
{
}

BattleMap::~BattleMap()
{
	if (nullptr != Renderer)
	{
		Renderer->Death();
		Renderer = nullptr;
	}
}

void BattleMap::SetMap(int _StageNum)
{
	std::string TextureStr = "Stage" + std::to_string(_StageNum) + ".png";

	Renderer->SetScaleToTexture(TextureStr);
	MapScaleFloat4 = Renderer->GetTransform()->GetLocalScale() * 4;
	int2 Scale = int2(static_cast<int>(MapScaleFloat4.x) / 64, static_cast<int>(MapScaleFloat4.y) / 64);
	MapScaleInt2 = Scale;
	Renderer->SetLocalScale(MapScaleFloat4);
	GetTransform()->SetLocalPosition({ MapScaleFloat4.hx() - 32, MapScaleFloat4.hy() - 32 });

	TerrainData.resize(MapScaleInt2.y);

	switch (_StageNum)
	{
	case 0:
		SetTerrainData_Stage0();
		break;
	case 1:
		SetTerrainData_Stage1();
		break;
	case 2:
		SetTerrainData_Stage2();
		break;
	case 3:
		SetTerrainData_Stage3();
		break;
	case 4:
		SetTerrainData_Stage4();
		break;
	case 5:
		SetTerrainData_Stage5();
		break;
	case 6:
		SetTerrainData_Stage6();
		break;
	case 7:
		SetTerrainData_Stage7();
		break;
	case 8:
		SetTerrainData_Stage8();
		break;
	case 9:
		SetTerrainData_Stage9();
		break;
	case 10:
		SetTerrainData_Stage10();
		break;
	default:
		break;
	}

}

void BattleMap::Start()
{
	Renderer = CreateComponent<SpriteRenderer>(RenderOrder::Map);
}

int BattleMap::GetTerrainCostFoot(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::Plain:
	case Terrain::Floor:
	case Terrain::Road:
	case Terrain::Fort:
	case Terrain::Gate:
	case Terrain::House:
	case Terrain::Shop:
	case Terrain::Bridge:
	case Terrain::Ruins:
	case Terrain::Throne:
		return 1;
	case Terrain::Pillar:
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
	case Terrain::Lake:
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
	case Terrain::Floor:
	case Terrain::Road:
	case Terrain::None:
	case Terrain::Cliff:
	case Terrain::Door:
	case Terrain::Bridge:
	case Terrain::Wall:
		return 0;
	case Terrain::House:
	case Terrain::Shop:
	case Terrain::Lake:
	case Terrain::Sea:
	case Terrain::Ruins:
	case Terrain::River:
		return 10;
	case Terrain::Throne:
	case Terrain::Gate:
	case Terrain::Pillar:
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
	case Terrain::Floor:
	case Terrain::Road:
	case Terrain::None:
	case Terrain::Cliff:
	case Terrain::Door:
	case Terrain::Bridge:
	case Terrain::River:
	case Terrain::Wall:
	case Terrain::Ruins:
	case Terrain::House:
	case Terrain::Shop:
	case Terrain::Lake:
	case Terrain::Sea:
		return 0;
	case Terrain::Pillar:
	case Terrain::Forest:
	case Terrain::Mountain:
		return 1;
	case Terrain::Throne:
	case Terrain::Peak:
	case Terrain::Fort:
		return 2;
	case Terrain::Gate:
		return 3;
	default:
		return 0;
	}
}



void BattleMap::SetTerrainData_Stage0()
{
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

void BattleMap::SetTerrainData_Stage1()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Cliff, Terrain::Cliff, Terrain::Cliff, Terrain::Sea, Terrain::Sea };
	TerrainData[1] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Cliff };
	TerrainData[2] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain };
	TerrainData[3] = { Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Bridge, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain };
	TerrainData[6] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[7] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Bridge, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[8] = { Terrain::Wall, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Peak };
	TerrainData[9] = { Terrain::Wall, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::River, Terrain::Peak, Terrain::Peak, Terrain::Peak };
}

void BattleMap::SetTerrainData_Stage2()
{
	TerrainData[0] = { Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Plain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[1] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Wall, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest };
	TerrainData[2] = { Terrain::House, Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Mountain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Wall };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Wall };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall };
	TerrainData[5] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall };
	TerrainData[6] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Pillar, Terrain::Floor, Terrain::Pillar, Terrain::Floor, Terrain::Wall };
	TerrainData[7] = { Terrain::Plain , Terrain::Plain, Terrain::Fort, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Throne, Terrain::Floor, Terrain::Floor, Terrain::Wall };
	TerrainData[9] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall };
}

void BattleMap::SetTerrainData_Stage3()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Peak, Terrain::Peak };
	TerrainData[1] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Peak };
	TerrainData[2] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::None, Terrain::Shop, Terrain::None };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::House, Terrain::None, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Forest, Terrain::Road, Terrain::None, Terrain::None, Terrain::None };
	TerrainData[4] = { Terrain::Plain, Terrain::Peak, Terrain::None, Terrain::None, Terrain::None, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[5] = { Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Road, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Plain, Terrain::Road };
	TerrainData[6] = { Terrain::Forest, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Forest, Terrain::Road, Terrain::Road, Terrain::Road };
	TerrainData[7] = { Terrain::Plain, Terrain::None, Terrain::House, Terrain::None, Terrain::Road, Terrain::Wall, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Ruins, Terrain::Ruins, Terrain::Ruins, Terrain::Wall };
	TerrainData[8] = { Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Forest, Terrain::Plain, Terrain::Road, Terrain::Ruins, Terrain::Ruins, Terrain::Ruins, Terrain::Road };
	TerrainData[9] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Forest, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Peak };
}

void BattleMap::SetTerrainData_Stage4()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[2] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[6] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[7] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[9] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Forest };
	TerrainData[10] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[11] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Pillar, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Pillar, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[12] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Forest };
	TerrainData[13] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Plain, Terrain::Plain, Terrain::Plain };
}

void BattleMap::SetTerrainData_Stage5()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Lake, Terrain::Cliff, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Cliff , Terrain::Lake, Terrain::Cliff, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest };
	TerrainData[2] = { Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Cliff, Terrain::Cliff, Terrain::Cliff, Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Forest, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Forest };
	TerrainData[6] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::House, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Shop };
	TerrainData[7] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::House, Terrain::Plain };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Peak };
	TerrainData[9] = { Terrain::Mountain, Terrain::Mountain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak };
}

void BattleMap::SetTerrainData_Stage6()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[1] = { Terrain::Road, Terrain::None, Terrain::None, Terrain::None, Terrain::House, Terrain::None, Terrain::Road, Terrain::Road, Terrain::Forest, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[2] = { Terrain::Road, Terrain::None, Terrain::None, Terrain::None, Terrain::None, Terrain::None, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest };
	TerrainData[3] = { Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Forest, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Forest, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain };
	TerrainData[4] = { Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall };
	TerrainData[5] = { Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Road, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[6] = { Terrain::None, Terrain::House, Terrain::None, Terrain::Road, Terrain::Forest, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Road, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[7] = { Terrain::None, Terrain::None, Terrain::None, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall };
	TerrainData[8] = { Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[9] = { Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Plain, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[10] = { Terrain::Plain, Terrain::Plain, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Road, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Wall, Terrain::Floor, Terrain::Wall };
	TerrainData[11] = { Terrain::Plain, Terrain::None, Terrain::House, Terrain::None, Terrain::None, Terrain::None, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[12] = { Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::None, Terrain::None, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor, Terrain::Wall, Terrain::Floor, Terrain::Floor, Terrain::Floor };
	TerrainData[13] = { Terrain::Forest, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall, Terrain::Wall };
}

void BattleMap::SetTerrainData_Stage7()
{
	TerrainData[0] = { Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Bridge, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[2] = { Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::Forest, Terrain::Plain };
	TerrainData[3] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Forest, Terrain::None, Terrain::Fort, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[4] = { Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Fort, Terrain::Bridge, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest };
	TerrainData[5] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Peak, Terrain::Peak, Terrain::None, Terrain::None, Terrain::None, Terrain::Peak, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain };
	TerrainData[6] = { Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Plain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[7] = { Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::River, Terrain::River, Terrain::Bridge, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[9] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Bridge, Terrain::River, Terrain::River };
	TerrainData[10] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[11] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Shop, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::House, Terrain::None, Terrain::Plain };
	TerrainData[12] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Mountain, Terrain::Peak, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Peak };
	TerrainData[13] = { Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Peak };
}

void BattleMap::SetTerrainData_Stage8()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Bridge, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Fort, Terrain::Plain };
	TerrainData[2] = { Terrain::Plain, Terrain::Forest, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[3] = { Terrain::Forest, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River, Terrain::Bridge, Terrain::Bridge, Terrain::River, Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Fort, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Forest, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain };
	TerrainData[6] = { Terrain::River, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River };
	TerrainData[7] = { Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[8] = { Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain };
	TerrainData[9] = { Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Cliff, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Peak, Terrain::Mountain, Terrain::Mountain };
	TerrainData[10] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak };
	TerrainData[11] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain };
	TerrainData[12] = { Terrain::Cliff, Terrain::Floor, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[13] = { Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[14] = { Terrain::Plain, Terrain::Shop, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::House, Terrain::None };
	TerrainData[15] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None };
	TerrainData[16]= {Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::None, Terrain::None, Terrain::None};
	TerrainData[17] = { Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak };
}

void BattleMap::SetTerrainData_Stage9()
{
	TerrainData[0] = { Terrain::Peak, Terrain::Fort, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Fort, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::Fort, Terrain::None, Terrain::Plain };
	TerrainData[2] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain };
	TerrainData[3] = { Terrain::Peak, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain };
	TerrainData[4] = { Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Bridge, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Peak, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Plain };
	TerrainData[6] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[7] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Fort, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[8] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain };
	TerrainData[9] = { Terrain::None, Terrain::House, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Fort, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain };
	TerrainData[10] = { Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[11] = { Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain };
	TerrainData[12] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Cliff, Terrain::Plain, Terrain::Plain };
	TerrainData[13] = { Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::House, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Plain };
	TerrainData[14] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Cliff, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
}

void BattleMap::SetTerrainData_Stage10()
{
	TerrainData[0] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[1] = { Terrain::Plain, Terrain::None, Terrain::Fort, Terrain::None, Terrain::Plain, Terrain::Fort, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::River, Terrain::River, Terrain::River, Terrain::River };
	TerrainData[2] = { Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::Shop, Terrain::Shop, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[3] = { Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[4] = { Terrain::Mountain, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Fort, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[5] = { Terrain::Peak, Terrain::Peak, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::House, Terrain::None, Terrain::Plain };
	TerrainData[6] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Bridge, Terrain::Plain, Terrain::Plain, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain };
	TerrainData[7] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Mountain, Terrain::Plain, Terrain::Mountain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::River, Terrain::Forest, Terrain::Forest, Terrain::None, Terrain::None, Terrain::None, Terrain::Plain };
	TerrainData[8] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Mountain, Terrain::Forest, Terrain::Mountain, Terrain::River, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[9] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Forest, Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::River, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain };
	TerrainData[10] = { Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Mountain, Terrain::Forest, Terrain::Forest, Terrain::Bridge, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain };
	TerrainData[11] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::River, Terrain::River, Terrain::Peak, Terrain::Peak, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::River, Terrain::Forest, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Bridge, Terrain::River };
	TerrainData[12] = { Terrain::Peak, Terrain::Peak, Terrain::Peak, Terrain::Mountain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::Forest, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[13] = { Terrain::Peak, Terrain::Peak, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::River, Terrain::River, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[14] = { Terrain::Peak, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[15] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Bridge, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::Plain };
	TerrainData[16] = { Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::House, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::River, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
	TerrainData[17] = { Terrain::Mountain, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Mountain, Terrain::River, Terrain::Mountain, Terrain::Plain, Terrain::Plain, Terrain::Forest, Terrain::Forest, Terrain::Forest, Terrain::Plain, Terrain::Plain, Terrain::Plain, Terrain::Plain };
}
