#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
// Ό³Έν :
class MapUnit : public GameEngineActor
{
public:
	// constrcuter destructer
	MapUnit();
	~MapUnit();

	void SetMapPos(int2 _Value);
	void MoveMapPos(int2 _Value);

	// delete Function
	MapUnit(const MapUnit& _Other) = delete;
	MapUnit(MapUnit&& _Other) noexcept = delete;
	MapUnit& operator=(const MapUnit& _Other) = delete;
	MapUnit& operator=(MapUnit&& _Other) noexcept = delete;

protected:
private:
	int2 MapPos = { 0 };
};

