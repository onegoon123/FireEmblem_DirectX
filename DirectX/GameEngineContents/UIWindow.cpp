#include "PrecompileHeader.h"
#include "UIWindow.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "SpriteRenderer.h"
#include "ContentsEnum.h"
UIWindow::UIWindow()
{
}

UIWindow::~UIWindow()
{
}

static float RenderSize = 32.f;

void UIWindow::UISet(int2 Scale)
{
	CenterTopRender.reserve(Scale.x);
	LeftMiddleRender.reserve(Scale.y);
	CenterMiddleRender.reserve(Scale.x * Scale.y);
	RightMiddleRender.reserve(Scale.y);
	CenterBottomRender.reserve(Scale.x);


	LeftTopRender = CreateComponent<SpriteRenderer>();
	LeftTopRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
	LeftTopRender->GetTransform()->SetLocalPosition(float4::Zero);
	LeftTopRender->SetTexture("LeftUp.png");

	for (int x = 0; x < Scale.x; x++)
	{
		std::shared_ptr<SpriteRenderer> NewRender = CenterTopRender.emplace_back(CreateComponent<SpriteRenderer>());
		NewRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
		NewRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(x + 1));
		NewRender->SetTexture("CenterUp.png");
	}

	RightTopRender = CreateComponent<SpriteRenderer>();
	RightTopRender->SetTexture("RightUp.png");
	RightTopRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
	RightTopRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(Scale.x + 1));

	for (int y = 0; y < Scale.y; y++)
	{
		std::shared_ptr<SpriteRenderer> NewRender = LeftMiddleRender.emplace_back(CreateComponent<SpriteRenderer>());
		NewRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
		NewRender->GetTransform()->SetLocalPosition(float4::Down * RenderSize * (float)(y + 1));
		NewRender->SetTexture("LeftCenter.png");
	}

	for (int y = 0; y < Scale.y; y++)
	{
		for (int x = 0; x < Scale.x; x++)
		{
			std::shared_ptr<SpriteRenderer> NewRender = CenterMiddleRender.emplace_back(CreateComponent<SpriteRenderer>());
			NewRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
			NewRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(x + 1) + float4::Down * RenderSize * (float)(y + 1));
			NewRender->SetTexture("CenterCenter.png");
		}
	}
	//CenterMiddleRender = CreateComponent<SpriteRenderer>();
	//CenterMiddleRender->SetFrame(4);
	//CenterMiddleRender->SetScale(Scale);
	//CenterMiddleRender->SetPosition(float4::Down * RenderSize + float4::Right * RenderSize);


	for (int y = 0; y < Scale.y; y++)
	{
		std::shared_ptr<SpriteRenderer> NewRender = RightMiddleRender.emplace_back(CreateComponent<SpriteRenderer>());
		NewRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
		NewRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(Scale.x + 1) + float4::Down * RenderSize * (float)(y + 1));
		NewRender->SetTexture("RightCenter.png");
	}

	LeftBottomRender = CreateComponent<SpriteRenderer>();
	LeftBottomRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
	LeftBottomRender->GetTransform()->SetLocalPosition(float4::Down * RenderSize * (float)(Scale.y + 1));
	LeftBottomRender->SetTexture("LeftDown.png");


	for (int x = 0; x < Scale.x; x++)
	{
		std::shared_ptr<SpriteRenderer> NewRender = CenterBottomRender.emplace_back(CreateComponent<SpriteRenderer>());
		NewRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
		NewRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(x + 1) + float4::Down * RenderSize * (float)(Scale.y + 1));
		NewRender->SetTexture("CenterDown.png");
	}
	RightBottomRender = CreateComponent<SpriteRenderer>();
	RightBottomRender->GetTransform()->SetWorldScale({ RenderSize, RenderSize });
	RightBottomRender->GetTransform()->SetLocalPosition(float4::Right * RenderSize * (float)(Scale.x + 1) + float4::Down * RenderSize * (float)(Scale.y + 1));
	RightBottomRender->SetTexture("RightDown.png");
}

void UIWindow::Clear()
{
	for (int i = 0; i < CenterTopRender.size(); i++)
	{
		CenterTopRender[i]->Death();
		CenterTopRender[i] = nullptr;
	}
	CenterTopRender.clear();
	for (int i = 0; i < LeftMiddleRender.size(); i++)
	{
		LeftMiddleRender[i]->Death();
		LeftMiddleRender[i] = nullptr;
	}
	LeftMiddleRender.clear();
	for (int i = 0; i < CenterMiddleRender.size(); i++)
	{
		CenterMiddleRender[i]->Death();
		CenterMiddleRender[i] = nullptr;
	}
	CenterMiddleRender.clear();
	for (int i = 0; i < RightMiddleRender.size(); i++)
	{
		RightMiddleRender[i]->Death();
		RightMiddleRender[i] = nullptr;
	}
	RightMiddleRender.clear();
	for (int i = 0; i < CenterBottomRender.size(); i++)
	{
		CenterBottomRender[i]->Death();
		CenterBottomRender[i] = nullptr;
	}
	CenterBottomRender.clear();
	LeftTopRender->Death();
	LeftTopRender = nullptr;
	RightTopRender->Death();
	RightTopRender = nullptr;
	LeftBottomRender->Death();
	LeftBottomRender = nullptr;
	RightBottomRender->Death();
	RightBottomRender = nullptr;
}

