#include "PrecompileHeader.h"
#include "SelectUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
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
	return;

	Goal.Render = CreateComponent<GameEngineRenderer>();
	Goal.Render->SetPipeLine("2DTexture");
	// "ClearGoal.bmp", RenderOrder::UI
	Goal.Render->GetTransform()->SetWorldScale({ 344, 100 });
	Goal.BenchmarkHidePos = { 178, -64 };
	Goal.BenchmarkShowPos = { 178, 64 };
	Goal.ChangeDir(UIDir::None);

	Terrain.Render = CreateComponent<GameEngineRenderer>();
	Terrain.Render->SetPipeLine("2DTexture");
	//"terrainUI.bmp", RenderOrder::UI
	Terrain.Render->GetTransform()->SetWorldScale({ 192, 212 });
	//Terrain.Render->SetPosition({ 864, 532 });
	Terrain.BenchmarkHidePos = { -96, 108 };
	Terrain.BenchmarkShowPos = { 96, 108 };
	Terrain.ChangeDir(UIDir::None);

	UnitData.Render = CreateComponent<GameEngineRenderer>();
	UnitData.Render->SetPipeLine("2DTexture");
	//"ActorUI.bmp", RenderOrder::UI
	UnitData.Render->GetTransform()->SetWorldScale({ 344, 152 });
	//UnitData.Render->SetPosition({ 192, 542 });
	UnitData.BenchmarkHidePos = { -172, 98 };
	UnitData.BenchmarkShowPos = { 192, 98 };
	UnitData.ChangeDir(UIDir::None);

	CursorDir = UIDir::None;

}

void SelectUI::Update(float _DeltaTiime)
{
	return;

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
	Render->GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, TargetPos, Timer));
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
			StartPos = { BenchmarkShowPos.x , GameEngineWindow::GetScreenSize().y - BenchmarkShowPos.y };
			TargetPos = { BenchmarkHidePos.x , GameEngineWindow::GetScreenSize().y - BenchmarkHidePos.y };
			break;
		case UIDir::RightUp:
			StartPos = { GameEngineWindow::GetScreenSize().x - BenchmarkShowPos.x , BenchmarkShowPos.y };
			TargetPos = { GameEngineWindow::GetScreenSize().x - BenchmarkHidePos.x , BenchmarkHidePos.y };
			break;
		case UIDir::RightDown:
			StartPos = GameEngineWindow::GetScreenSize() - BenchmarkShowPos;
			TargetPos = GameEngineWindow::GetScreenSize() - BenchmarkHidePos;
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
		StartPos = { BenchmarkHidePos.x , GameEngineWindow::GetScreenSize().y - BenchmarkHidePos.y };
		TargetPos = { BenchmarkShowPos.x , GameEngineWindow::GetScreenSize().y - BenchmarkShowPos.y };
		break;
	case UIDir::RightUp:
		StartPos = { GameEngineWindow::GetScreenSize().x - BenchmarkHidePos.x , BenchmarkHidePos.y };
		TargetPos = { GameEngineWindow::GetScreenSize().x - BenchmarkShowPos.x , BenchmarkShowPos.y };
		break;
	case UIDir::RightDown:
		StartPos = GameEngineWindow::GetScreenSize() - BenchmarkHidePos;
		TargetPos = GameEngineWindow::GetScreenSize() - BenchmarkShowPos;
		break;
	default:
		break;
	}

	CurDir = _Dir;
	NextDir = UIDir::None;
	Timer = 0;

}
