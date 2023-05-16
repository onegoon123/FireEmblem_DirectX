#include "PrecompileHeader.h"
#include "ArrowRender.h"
#include "ContentsEnum.h"
#include "SpriteRenderer.h"
ArrowRender::ArrowRender()
{
	Renders.reserve(150);
}

ArrowRender::~ArrowRender()
{
}

void ArrowRender::Create(int2 _Scale)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Map");

	if (nullptr == GameEngineSprite::Find("Arrow.png"))
	{
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Arrow.png").GetFullPath(), 14, 1);
	}

	Renders.resize(_Scale.y);
	for (int y = 0; y < _Scale.y; y++)
	{
		Renders[y].resize(_Scale.x);
		for (int x = 0; x < _Scale.x; x++)
		{
			Renders[y][x] = CreateComponent<SpriteRenderer>();
			Renders[y][x]->SetSprite("Arrow.png", 0);
			Renders[y][x]->GetTransform()->SetLocalScale({ 64,64 });
			Renders[y][x]->GetTransform()->SetLocalPosition(float4(x * 64.f,  y * 64.f));
			//Renders[y][x]->GetTransform()->SetLocalPosition(float4(x * 64.f + 32.f, (_Scale.y - y) * 64.f - 32.f));
			Renders[y][x]->Off();
		}
	}
}

void ArrowRender::Clear()
{
	for (int y = 0; y < Renders.size(); y++)
	{
		for (int x = 0; x < Renders[y].size(); x++)
		{
			Renders[y][x]->Off();
		}
	}
}

void ArrowRender::SetArrow(std::vector<int2>& _Value)
{
	Clear();
	Diraction BeforeDir = Diraction::None;
	std::vector<int2>::iterator BeforeArrow = _Value.begin();
	std::vector<int2>::iterator CurArrow = _Value.begin();
	CurArrow++;

	switch (DiractionCheck(*BeforeArrow, *CurArrow))
	{
	case Diraction::Up:
		BeforeDir = Diraction::Up;
		Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(0);
		break;
	case Diraction::Down:
		BeforeDir = Diraction::Down;
		Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(1);
		break;
	case Diraction::Left:
		BeforeDir = Diraction::Left;
		Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(2);
		break;
	case Diraction::Right:
		BeforeDir = Diraction::Right;
		Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(3);
		break;
	case Diraction::None:
	default:
		break;
	}
	Renders[(*BeforeArrow).y][(*BeforeArrow).x]->On();

	for (int i = 1; i < _Value.size() - 1; i++)
	{
		BeforeArrow++;
		CurArrow++;
		switch (DiractionCheck(*BeforeArrow, *CurArrow))
		{
		case Diraction::Up:
		{
			if (BeforeDir == Diraction::Up)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(4);
			}
			else if (BeforeDir == Diraction::Left)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(8);
			}
			else if (BeforeDir == Diraction::Right)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(9);
			}
			BeforeDir = Diraction::Up;
			break;
		}
		case Diraction::Down:
		{
			if (BeforeDir == Diraction::Down)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(4);
			}
			else if (BeforeDir == Diraction::Left)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(6);
			}
			else if (BeforeDir == Diraction::Right)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(7);
			}
			BeforeDir = Diraction::Down;
			break;
		}
		case Diraction::Left:
		{
			if (BeforeDir == Diraction::Left)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(5);
			}
			else if (BeforeDir == Diraction::Up)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(7);
			}
			else if (BeforeDir == Diraction::Down)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(9);
			}
			BeforeDir = Diraction::Left;
			break;
		}
		case Diraction::Right:
		{
			if (BeforeDir == Diraction::Right)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(5);
			}
			else if (BeforeDir == Diraction::Up)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(6);
			}
			else if (BeforeDir == Diraction::Down)
			{
				Renders[(*BeforeArrow).y][(*BeforeArrow).x]->SetFrame(8);
			}
			BeforeDir = Diraction::Right;
			break;
		}
		case Diraction::None:
		default:
			break;
		}
		Renders[(*BeforeArrow).y][(*BeforeArrow).x]->On();
	}
	//BeforeArrow;
	//CurArrow;
	switch (DiractionCheck(*BeforeArrow, *CurArrow))
	{
	case Diraction::Up:
		Renders[(*CurArrow).y][(*CurArrow).x]->SetFrame(10);
		break;
	case Diraction::Down:
		Renders[(*CurArrow).y][(*CurArrow).x]->SetFrame(11);
		break;
	case Diraction::Left:
		Renders[(*CurArrow).y][(*CurArrow).x]->SetFrame(12);
		break;
	case Diraction::Right:
		Renders[(*CurArrow).y][(*CurArrow).x]->SetFrame(13);
		break;
	case Diraction::None:
	default:
		break;
	}
	Renders[(*CurArrow).y][(*CurArrow).x]->On();
}


void ArrowRender::Start()
{
}

Diraction ArrowRender::DiractionCheck(int2 _BeforePos, int2 _CurPos)
{
	if (_BeforePos.x < _CurPos.x)
	{
		return Diraction::Right;
	}
	if (_BeforePos.x > _CurPos.x)
	{
		return Diraction::Left;
	}
	if (_BeforePos.y < _CurPos.y)
	{
		return Diraction::Up;
	}
	if (_BeforePos.y > _CurPos.y)
	{
		return Diraction::Down;
	}
	return Diraction::None;
}

