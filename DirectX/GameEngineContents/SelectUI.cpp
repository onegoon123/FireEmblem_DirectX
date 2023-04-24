#include "PrecompileHeader.h"
#include "SelectUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
SelectUI::SelectUI()
{
}

SelectUI::~SelectUI()
{
}

void SelectUI::SetCursorDir(UIDir _Dir)
{

	if (CursorDir == _Dir)
	{
		return;
	}

	switch (_Dir)
	{
	case UIDir::None:
		break;
	case UIDir::LeftUp:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::RightDown);
		UnitData.ChangeDir(UIDir::LeftDown);
		break;
	case UIDir::LeftDown:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::RightDown);
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightUp:
		Goal.ChangeDir(UIDir::RightDown);
		Terrain.ChangeDir(UIDir::LeftDown);
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightDown:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::LeftDown);
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	default:
		break;
	}

	CursorDir = _Dir;

}

void SelectUI::UIOn()
{
	Goal.Render->On();
	Terrain.Render->On();
	UnitData.Render->On();
}

void SelectUI::UIOff()
{
	Goal.ChangeDir(UIDir::None);
	Terrain.ChangeDir(UIDir::None);
	UnitData.ChangeDir(UIDir::None);
	CursorDir = UIDir::None;
	Goal.Render->Off();
	Terrain.Render->Off();
	UnitData.Render->Off();
}

void SelectUI::Start()
{
	Goal.Render = CreateComponent<GameEngineRenderer>();
	Goal.Render->SetPipeLine("2DTexture");
	Goal.Render->GetShaderResHelper().SetTexture("DiffuseTex", "ClearGoal.png"); 
	Goal.Render->GetTransform()->SetWorldScale({ 344, 100 });
	Goal.BenchmarkHidePos = { -300, 370 };
	Goal.BenchmarkShowPos = { -300, 254 };
	Goal.ChangeDir(UIDir::None);

	Terrain.Render = CreateComponent<GameEngineRenderer>();
	Terrain.Render->SetPipeLine("2DTexture");
	Terrain.Render->GetShaderResHelper().SetTexture("DiffuseTex", "terrainUI.png");
	Terrain.Render->GetTransform()->SetWorldScale({ 192, 212 });
	Terrain.BenchmarkHidePos = { -576, 214 };
	Terrain.BenchmarkShowPos = { -384, 214 };
	Terrain.ChangeDir(UIDir::None);

	UnitData.Render = CreateComponent<GameEngineRenderer>();
	UnitData.Render->SetPipeLine("2DTexture");
	UnitData.Render->GetShaderResHelper().SetTexture("DiffuseTex", "ActorUI.png");
	UnitData.Render->GetTransform()->SetWorldScale({ 344, 152 });
	UnitData.BenchmarkHidePos = { -636, 228 };
	UnitData.BenchmarkShowPos = { -292, 228 };
	UnitData.ChangeDir(UIDir::None);

	CursorDir = UIDir::None;

}

void SelectUI::Update(float _DeltaTiime)
{
	Goal.Update(_DeltaTiime);
	Terrain.Update(_DeltaTiime);
	UnitData.Update(_DeltaTiime);
}


static float AnimSpeed = 10.0f;
void SelectUIObject::Update(float _DeltaTime)
{
	if (1 <= Timer)
	{
		if (NextDir != UIDir::None)
		{
			ChangeDir(NextDir);
		}
		return;
	}
	Timer += _DeltaTime * AnimSpeed;
	Render->GetTransform()->SetLocalPosition(float4::LerpClamp(StartPos, TargetPos, Timer));
}

void SelectUIObject::ChangeDir(UIDir _Dir)
{
	if (CurDir == _Dir)
	{
		return;
	}
	if (_Dir == UIDir::None)
	{
		Timer = 1;
		Render->GetTransform()->SetWorldPosition(BenchmarkHidePos);
		CurDir = UIDir::None;
		return;
	}

	if (CurDir != UIDir::None)
	{
		switch (CurDir)
		{
		case UIDir::None:
			break;
		case UIDir::LeftUp:
			StartPos = BenchmarkShowPos;
			TargetPos = BenchmarkHidePos;
			break;
		case UIDir::LeftDown:
			StartPos = { BenchmarkShowPos.x , -BenchmarkShowPos.y };
			TargetPos = { BenchmarkHidePos.x , -BenchmarkHidePos.y };
			break;
		case UIDir::RightUp:
			StartPos = { -BenchmarkShowPos.x , BenchmarkShowPos.y };
			TargetPos = { -BenchmarkHidePos.x , BenchmarkHidePos.y };
			break;
		case UIDir::RightDown:
			StartPos = -BenchmarkShowPos;
			TargetPos = -BenchmarkHidePos;
			break;
		default:
			break;
		}

		CurDir = UIDir::None;
		NextDir = _Dir;
		Timer = 0;
		return;
	}

	switch (_Dir)
	{
	case UIDir::None:
		break;
	case UIDir::LeftUp:
		StartPos = BenchmarkHidePos;
		TargetPos = BenchmarkShowPos;
		break;
	case UIDir::LeftDown:
		StartPos = { BenchmarkHidePos.x ,  -BenchmarkHidePos.y };
		TargetPos = { BenchmarkShowPos.x , -BenchmarkShowPos.y };
		break;
	case UIDir::RightUp:
		StartPos = {-BenchmarkHidePos.x , BenchmarkHidePos.y };
		TargetPos = {-BenchmarkShowPos.x , BenchmarkShowPos.y };
		break;
	case UIDir::RightDown:
		StartPos = -BenchmarkHidePos;
		TargetPos = -BenchmarkShowPos;
		break;
	default:
		break;
	}

	CurDir = _Dir;
	NextDir = UIDir::None;
	Timer = 0;

}
