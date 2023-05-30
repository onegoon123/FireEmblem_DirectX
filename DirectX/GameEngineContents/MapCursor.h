#pragma once

#include "MapUnit.h"

// 설명 : 커서 엑터
class GameEngineSpriteRenderer;
class GameEngineUIRenderer;
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

	void Setting(std::shared_ptr<MapUnit> _CameraUnit)
	{
		CameraUnit = _CameraUnit;
	}
	void On();
	void Off();

	void Select();
	void Idle();
	void Enemy();

	void SetCursorPos(int2 _Value);
	void MoveCursorPosLerp(int2 _Value);
	
	int2 WorldPos = int2::Zero;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> AnimationRender = nullptr;
	std::shared_ptr<MapUnit> CameraUnit = nullptr;

};

