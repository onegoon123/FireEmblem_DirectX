#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
#include "ContentsEnum.h"

const static float TileScale = 64.0f;



class SpriteRenderer;
class BattleMap : public GameEngineActor
{
public:
	friend class BattleLevel;
	// constrcuter destructer
	BattleMap();
	~BattleMap();

	// delete Function
	BattleMap(const BattleMap& _Other) = delete;
	BattleMap(BattleMap&& _Other) noexcept = delete;
	BattleMap& operator=(const BattleMap& _Other) = delete;
	BattleMap& operator=(BattleMap&& _Other) noexcept = delete;

	float4 MapScaleFloat4 = { 960, 640 };
	int2 MapScaleInt2 = { 15, 10 };

	static int GetTerrainCostFoot(Terrain _Value);
	static int GetTerrainDodge(Terrain _Value);
	static int GetTerrainDef(Terrain _Value);

	std::shared_ptr<SpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;

	// 맵 정보
	std::vector<std::vector<Terrain>> TerrainData;
	// 이미지 이름
	std::string_view ImageName;
private:
	std::shared_ptr<SpriteRenderer> Renderer = nullptr;

};

