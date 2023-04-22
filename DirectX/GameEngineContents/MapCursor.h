#pragma once

#include "MapUnit.h"

// 설명 : 커서 엑터
class GameEngineRenderer;
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

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineRenderer> AnimationRender = nullptr;

};

