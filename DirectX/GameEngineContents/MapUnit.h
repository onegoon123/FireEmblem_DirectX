#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
// Ό³Έν :
class MapUnit : public GameEngineActor
{
	friend class BattleLevel;
public:
	// constrcuter destructer
	MapUnit();
	~MapUnit();
	// delete Function
	MapUnit(const MapUnit& _Other) = delete;
	MapUnit(MapUnit&& _Other) noexcept = delete;
	MapUnit& operator=(const MapUnit& _Other) = delete;
	MapUnit& operator=(MapUnit&& _Other) noexcept = delete;

	void SetMapPos(int2 _Value);
	void MoveMapPos(int2 _Value);
	int2 GetMapPos()
	{
		return MapPos;
	}

	void SetMapPosLerp(int2 _Value);
	void MoveMapPosLerp(int2 _Value);

	bool GetIsMove() {
		return IsMove;
	}

	void SetBeforeMapPos()
	{
		BeforeMapPos = MapPos;
	}
	int2 GetBeforeMapPos()
	{
		return BeforeMapPos;
	}

	void SetMoveSpeed(float _Speed)
	{
		MoveSpeed = _Speed;
	}
protected:
	void Update(float _DeltaTime) override;
	float MoveSpeed = 15.0f;

	virtual void SetMoveDir(int2 _Dir) {}
	virtual void MoveStart() {}
	virtual void MoveEnd() {}

private:
	int2 MapPos = { 0 };
	int2 BeforeMapPos = { 0 };
	bool IsMove = false;
	float MoveTimer = 0;
	float4 StartPos;
	float4 EndPos;
};

