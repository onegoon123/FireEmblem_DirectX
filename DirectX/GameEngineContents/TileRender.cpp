#include "PrecompileHeader.h"
#include "TileRender.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
TileRender::TileRender()
{
}

TileRender::~TileRender()
{
}

void TileRender::Create(int2 _Scale)
{
	Renders.resize(_Scale.y);
	for (int y = 0; y < _Scale.y; y++)
	{
		Renders[y].resize(_Scale.x);
		for (int x = 0; x < _Scale.x; x++)
		{
			Renders[y][x] = CreateComponent<GameEngineSpriteRenderer>();
			Renders[y][x]->GetTransform()->SetLocalScale({ 64,64 });
			Renders[y][x]->GetTransform()->SetLocalPosition(float4(x * 64.f, y * 64.f));
			Renders[y][x]->SetTexture("MoveTile.png");
			Renders[y][x]->Off();
		}
	}
}

void TileRender::Clear()
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			Renders[y][x]->Off();
		}
	}
}

void TileRender::SetTileMove(const std::vector<std::vector<bool>>& _Value)
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			if (true == _Value[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("MoveTile.png");
			}
			else
			{
				Renders[y][x]->Off();
			}
		}
	}
}

void TileRender::SetTileAttack(const std::vector<std::vector<bool>>& _Value)
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			if (true == _Value[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("AttackTile.png");
			}
		}
	}
}

void TileRender::SetTile(const std::vector<std::vector<bool>>& _Move, const std::vector<std::vector<bool>>& _Attack)
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			if (true == _Move[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("MoveTile.png");
			}
			else if (_Attack[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("AttackTile.png");
			}
			else
			{
				Renders[y][x]->Off();
			}
		}
	}
}
