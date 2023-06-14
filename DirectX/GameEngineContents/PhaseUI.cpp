#include"PrecompileHeader.h"
#include "PhaseUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
PhaseUI::PhaseUI() 
{
}

PhaseUI::~PhaseUI() 
{
}

void PhaseUI::PhaseOn(Faction _Faction)
{
	switch (_Faction)
	{
	case Faction::None:
	{
		MsgAssert("값이 지정되지 않는 Faction을 사용했습니다.");
		return;
	}
	case Faction::Player:
		Renderer->SetTexture("PlayerPhase.png");
		break;
	case Faction::Enemy:
		Renderer->SetTexture("EnemyPhase.png");
		break;
	default:
		break;
	}
	Renderer->GetTransform()->SetLocalPosition({ 1316, 0 });
	Renderer->On();
	CurState = PhaseState::Start;
	On();
	Timer = 0;
}

bool PhaseUI::PhaseUIEnd()
{
	if (CurState == PhaseState::End)
	{
		PhaseOff();
		return true;
	}
	return false;
}

void PhaseUI::PhaseOff()
{
	Renderer->Off();
	Off();
}

void PhaseUI::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Renderer->GetTransform()->SetWorldScale({ 712, 76 });
	Renderer->Off();

	Off();
}

void PhaseUI::Update(float _DeltaTime)
{
	switch (CurState)
	{
	case PhaseUI::PhaseState::Start:
		StartUpdate(_DeltaTime);
		break;
	case PhaseUI::PhaseState::Wait:
		WaitUpdate(_DeltaTime);
		break;
	case PhaseUI::PhaseState::Disapear:
		DisapearUpdate(_DeltaTime);
		break;
	case PhaseUI::PhaseState::End:
		EndUpdate(_DeltaTime);
		break;
	default:
		break;
	}

	
}

void PhaseUI::StartUpdate(float _DeltaTime)
{
	Timer += _DeltaTime * 3;
	Renderer->GetTransform()->SetLocalPosition(float4::LerpClamp({ 1316, 0 }, { 0,0 }, Timer));
	if (1 < Timer)
	{
		Timer = 0;
		CurState = PhaseState::Wait;
		return;
	}
}

void PhaseUI::WaitUpdate(float _DeltaTime)
{
	Timer += _DeltaTime;
	if (0.5f < Timer)
	{
		Timer = 0;
		CurState = PhaseState::Disapear;
		return;
	}
}

void PhaseUI::DisapearUpdate(float _DeltaTime)
{
	Timer += _DeltaTime * 3;
	Renderer->GetTransform()->SetLocalPosition(float4::LerpClamp({ 0, 0 }, { -1316,0 }, Timer));
	if (1 < Timer)
	{
		Renderer->Off();
		Timer = 0;
		CurState = PhaseState::End;
		return;
	}
}

void PhaseUI::EndUpdate(float _DeltaTime)
{
}

