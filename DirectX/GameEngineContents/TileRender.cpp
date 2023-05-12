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
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Map");
	if (nullptr == GameEngineSprite::Find(Dir.GetPlusFileName("Tile.png").GetFullPath()))
	{
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Tile.png").GetFullPath(), 16, 3);
	}

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
			Renders[y][x]->CreateAnimation({ "Move", "Tile.png", 0, 15, 0.1f, true, false });
			Renders[y][x]->CreateAnimation({ "Attack", "Tile.png", 16, 31, 0.1f, true, false });
			Renders[y][x]->CreateAnimation({ "Enemy", "Tile.png", 32, 47, 0.1f, true, false });
			Renders[y][x]->SetOpacity(0.8f);
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
				Renders[y][x]->OffLerp();
				Renders[y][x]->ChangeAnimation("Move", false);
				Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
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
			Renders[y][x]->OffLerp();
			if (true == _Move[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->ChangeAnimation("Move");
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
				}
			}
			else if (true == _Attack[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->ChangeAnimation("Attack");
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
				}
			}
			else if (true == EnemyTileValue[y][x])
			{
				Renders[y][x]->On();
				Renders[y][x]->ChangeAnimation("Move");
				Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
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
				Renders[y][x]->ChangeAnimation("Attack");
				if (true == EnemyTileValue[y][x])
				{
					Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
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
				Renders[y][x]->ChangeAnimation("Move");
				Renders[y][x]->SetLerp(float4(0.3f, 0, 0.8f), 0.5f);
			}
			else
			{
				Renders[y][x]->Off();
			}
		}
	}
}
