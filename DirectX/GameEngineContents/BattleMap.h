#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
const static float TileScale = 64.0f;

enum class Terrain
{
	Plain,	//평지
	None,	//이동불가지역
	Forest,	//숲
	Cliff,	//벼랑
	Mountain,	//산
	Peak,		//높은 산
	Door,		//문 이동불가
	Gate,		//문 게이트 이동가능
	House,		//민가
	Sea,		//바다
	River,		//강
	Bridge,		//다리
	Wall,		//벽
};

class GameEngineRenderer;
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


protected:
	void Start() override;

	// 맵 정보
	std::vector<std::vector<Terrain>> TerrainData;
	// 이미지 이름
	std::string_view ImageName;
private:
	std::shared_ptr<GameEngineRenderer> MapRender = nullptr;

};

