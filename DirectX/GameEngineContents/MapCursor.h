#pragma once

#include "MapUnit.h"

// 설명 : 커서 엑터
class GameEngineSpriteRenderer;
class MapCursor : public MapUnit
{
public:
	// constrcuter destructer
	MapCursor();
	~MapCursor();
	// delete Function
	MapCursor(const MapCursor& _Other) = delete;
	MapCursor(MapCursor&& _Other) noexcept = delete;
	MapCursor& operator=(const MapCursor& _Other) = delete;
	MapCursor& operator=(MapCursor&& _Other) noexcept = delete;

	void On();
	void Off();

	void Select();
	void Idle();
	void Enemy();

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> AnimationRender = nullptr;

};

