#include "PrecompileHeader.h"
#include "MapCursor.h"
#include <iostream>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>
#include <math.h>
#include "ContentsEnum.h"
#include "BattleMap.h"

MapCursor::MapCursor()
{
}

MapCursor::~MapCursor()
{
}

void MapCursor::On()
{
	AnimationRender->On();
}

void MapCursor::Off()
{
	AnimationRender->Off();
}

void MapCursor::Start()
{
	AnimationRender = CreateComponent<GameEngineRenderer>();
	AnimationRender->SetPipeLine("2DTexture");
	AnimationRender->GetShaderResHelper().SetTexture("DiffuseTex", "TestCursor.png");
	AnimationRender->GetTransform()->SetWorldScale({ 104, 104 });
	SetMapPos({ 1, 1 });
}
