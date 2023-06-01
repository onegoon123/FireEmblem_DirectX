#include "PrecompileHeader.h"
#include "UIButtonSystem.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnum.h"
UIButtonSystem::UIButtonSystem() 
{
	Buttons.reserve(10);
}

UIButtonSystem::~UIButtonSystem() 
{
}

void UIButtonSystem::NewButton(std::shared_ptr<GameEngineCollision> _Collision, std::function<void()> _HoverFunction, std::function<void()> _ClickFunction)
{
	Button NewButton;
	NewButton.Col = _Collision;
	NewButton.HoverFunction = _HoverFunction;
	NewButton.ClickFunction = _ClickFunction;
	Buttons.push_back(NewButton);
}

void UIButtonSystem::Start()
{
	MouseCol = CreateComponent<GameEngineCollision>(CollisionOrder::Cursor);
	MouseCol->GetTransform()->SetWorldScale({ 1, 1 });
	MouseCol->SetColType(ColType::SPHERE2D);
}

void UIButtonSystem::Update(float _DeltaTime)
{
	static float Timer = 0.0f;
	Timer -= _DeltaTime;
	if (0 < Timer) { 
		return;
	}

	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x - 480, 320 - MousePos.y);
	MouseCol->GetTransform()->SetWorldPosition(MouseLocalPos);
	std::shared_ptr<GameEngineCollision> Col = MouseCol->Collision(CollisionOrder::Button);
	for (int i = 0; i < Buttons.size(); i++)
	{
		if (Col == Buttons[i].Col)
		{
			Buttons[i].HoverFunction();
			if (true == GameEngineInput::IsUp("LeftClick"))
			{
				Buttons[i].ClickFunction();
				Timer = 0.1f;
			}
			return;
		}
	}
}
