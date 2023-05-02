#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
// Ό³Έν :
class GameEngineSpriteRenderer;
class TileRender : public GameEngineActor
{
public:
	// constrcuter destructer
	TileRender();
	~TileRender();

	void Create(int2 _Scale);
	void Clear();
	void SetTileMove(const std::vector<std::vector<bool>>& _Value);
	void SetTileAttack(const std::vector<std::vector<bool>>& _Value);
	void SetTile(const std::vector<std::vector<bool>>& _Move, const std::vector<std::vector<bool>>& _Attack);

	// delete Function
	TileRender(const TileRender& _Other) = delete;
	TileRender(TileRender&& _Other) noexcept = delete;
	TileRender& operator=(const TileRender& _Other) = delete;
	TileRender& operator=(TileRender&& _Other) noexcept = delete;

protected:
private:
	std::vector <std::vector<std::shared_ptr<GameEngineSpriteRenderer>>> Renders;
};

