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
		MsgAssert("���� �������� �ʴ� Faction�� ����߽��ϴ�.");
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
	Timer = 0;
}

bool PhaseUI::PhaseUIEnd()
{
	if (2.2f < Timer)
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
}

void PhaseUI::WaitUpdate(float _DeltaTime)
{
}

void PhaseUI::EndUpdate(float _DeltaTime)
{
}
