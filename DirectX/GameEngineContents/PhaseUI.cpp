#include"PrecompileHeader.h"
#include "PhaseUI.h"
#include "SpriteRenderer.h"
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
	Renderer->GetTransform()->SetLocalPosition({ 1316, 38 });
	Renderer->On();
	Timer = 0;
}

bool PhaseUI::PhaseUIEnd()
{
	if (1.5f < Timer)
	{
		Renderer->Off();
		return true;
	}
	return false;
}

void PhaseUI::Start()
{
	Renderer = CreateComponent<SpriteRenderer>();
	Renderer->GetTransform()->SetWorldScale({ 712, 76 });
	Renderer->Off();
}

void PhaseUI::Update(float _DeltaTiime)
{
	Timer += _DeltaTiime * 2;
	Renderer->GetTransform()->SetLocalPosition(float4::LerpClamp({1316, 0}, { 0,0 }, Timer));
}

