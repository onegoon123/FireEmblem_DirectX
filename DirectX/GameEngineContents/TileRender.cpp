#include "PrecompileHeader.h"
#include "TileRender.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "SpriteRenderer.h"
TileRender::TileRender()
{
}

TileRender::~TileRender()
{
}

void TileRender::Create(int2 _Scale)
{
	EnemyTileValue = std::vector<std::vector<bool>>(_Scale.y, std::vector<bool>(_Scale.x, false));
	Renders.resize(_Scale.y);

	for (int y = 0; y < _Scale.y; y++)
	{
		Renders[y].resize(_Scale.x);
		for (int x = 0; x < _Scale.x; x++)
		{
			Renders[y][x] = CreateComponent<SpriteRenderer>();
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
			if (true == EnemyTileValue[y][x]) { 
				Renders[y][x]->OffFlashColor();
				Renders[y][x]->SetTexture("EnemyAttackTile.png");
				continue;
			}
			Renders[y][x]->Off();
		}
	}
}

void TileRender::EnemyTileClear()
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			EnemyTileValue[y][x] = false;
			Renders[y][x]->Off();
		}
	}
}


void TileRender::SetTile(const std::vector<std::vector<bool>>& _Move, const std::vector<std::vector<bool>>& _Attack)
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			Renders[y][x]->OffFlashColor();
			if (true == _Move[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("MoveTile.png");
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetFlash(float4(0.3f, 0, 0.8f), 0.5f);
				}
			}
			else if (true == _Attack[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("AttackTile.png");
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetFlash(float4(0.3f, 0, 0.8f), 0.5f);
				}
			}
			else if (true == EnemyTileValue[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("EnemyAttackTile.png");
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
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetFlash(float4(0.3f, 0, 0.8f), 0.5f);
				}
			}
		}
	}
}

void TileRender::SetEnemyTile(const std::vector<std::vector<bool>>& _Value)
{
	
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			EnemyTileValue[y][x] = EnemyTileValue[y][x] || _Value[y][x];

			if (true == EnemyTileValue[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->SetTexture("EnemyAttackTile.png");
			}
			else
			{
				Renders[y][x]->Off();
			}
		}
	}
}
