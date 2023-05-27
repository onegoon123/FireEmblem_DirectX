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
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage3()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage4()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage5()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage6()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage7()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage8()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage9()
{
	SetTerrainData_Stage0();
}

void BattleMap::SetTerrainData_Stage10()
{
	SetTerrainData_Stage0();
}
