#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	//template<typename VertexType>
	//static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	//{
	//	std::shared_ptr<GameEngineMesh> NewMesh = GameEngineResource::Create(_Name);
	//}


protected:

private:
	// std::vector<float4> Vertexs;

};

