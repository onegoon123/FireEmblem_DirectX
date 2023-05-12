#include "PrecompileHeader.h"
#include "SelectUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpriteRenderer.h"
#include "ContentsEnum.h"
#include "BattleUnit.h"
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
	CursorDir = _Dir;

	switch (CursorDir)
	{
	case UIDir::None:
		Goal.ChangeDir(UIDir::None);
		Terrain.ChangeDir(UIDir::None);
		UnitData.ChangeDir(UIDir::None);
		break;
	case UIDir::LeftUp:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::RightDown);
		//UnitData.ChangeDir(UIDir::LeftDown);
		break;
	case UIDir::LeftDown:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::RightDown);
		//UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightUp:
		Goal.ChangeDir(UIDir::RightDown);
		Terrain.ChangeDir(UIDir::LeftDown);
		//UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightDown:
		Goal.ChangeDir(UIDir::RightUp);
		Terrain.ChangeDir(UIDir::LeftDown);
		//UnitData.ChangeDir(UIDir::LeftUp);
		break;
	default:
		break;
	}


}

void SelectUI::On()
{
	GameEngineActor::On();
	Goal.Render->On();
	Goal.Timer = 0;
	Terrain.Render->On();
	Terrain.Timer = 0;
	UnitData.Render->On();
	UnitData.Timer = 0;
	HPBarRender->On();
	PortraitRender->On();

	Goal.CurDir = UIDir::None;
	Goal.NextDir = UIDir::None;
	Terrain.CurDir = UIDir::None;
	Terrain.NextDir = UIDir::None;
	UnitData.ChangeDir(UIDir::None);
	CursorDir = UIDir::None;
}

void SelectUI::Off()
{
	GameEngineActor::Off();
	CursorDir = UIDir::None;
	Goal.Render->Off();
	Goal.Render->GetTransform()->SetLocalPosition(Goal.BenchmarkHidePos);
	Terrain.Render->Off();
	Terrain.Render->GetTransform()->SetLocalPosition(Terrain.BenchmarkHidePos);
	UnitData.Render->Off();
	UnitData.Render->GetTransform()->SetLocalPosition(UnitData.BenchmarkHidePos);
	HPBarRender->Off();
	PortraitRender->Off();
}

void SelectUI::SetHPBar(float _Value)
{
	HPBarRender->GetTransform()->SetWorldScale({ 168 * _Value, 8 });
	HPBarRender->GetTransform()->SetLocalPosition(float4(-20 + (84 * _Value), -48));
}

void SelectUI::SetUnitData(std::shared_ptr<BattleUnit> _Unit)
{
	switch (CursorDir)
	{
	case UIDir::None:
		break;
	case UIDir::LeftUp:
		UnitData.ChangeDir(UIDir::LeftDown);
		break;
	case UIDir::LeftDown:
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightUp:
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightDown:
		UnitData.ChangeDir(UIDir::LeftUp);
		break;
	default:
		break;
	}

	if (true == _Unit->GetIsPlayer())
	{
		UnitData.Render->SetTexture("ActorUI.png");
	}
	else
	{
		UnitData.Render->SetTexture("EnemyActorUI.png");
	}

	std::string TextureName = "BattleIcon_";
	TextureName += _Unit->GetUnitData().GetName().data();
	TextureName += ".png";
	PortraitRender->SetTexture(TextureName);

	SetHPBar(_Unit->GetUnitData().GetHP() / (float)_Unit->GetUnitData().GetMaxHP());
}

void SelectUI::UnitUIOff()
{
	UnitDataOn = true;
	UnitData.ChangeDir(UIDir::None);
}

void SelectUI::Start()
{
	Goal.Render = CreateComponent<SpriteRenderer>();
	Goal.Render->SetTexture("ClearGoal.png"); 
	Goal.Render->GetTransform()->SetWorldScale({ 344, 100 });
	Goal.BenchmarkHidePos = { -300, 370 };
	Goal.BenchmarkShowPos = { -300, 254 };
	Goal.CurDir = UIDir::None;
	Goal.NextDir = UIDir::None;

	Terrain.Render = CreateComponent<SpriteRenderer>();
	Terrain.Render->SetTexture("terrainUI.png");
	Terrain.Render->GetTransform()->SetWorldScale({ 192, 212 });
	Terrain.BenchmarkHidePos = { -576, 214 };
	Terrain.BenchmarkShowPos = { -384, 214 };
	Terrain.CurDir = UIDir::None;
	Terrain.NextDir = UIDir::None;

	UnitData.Render = CreateComponent<SpriteRenderer>();
	UnitData.Render->SetTexture("ActorUI.png");
	UnitData.Render->GetTransform()->SetWorldScale({ 344, 152, 100 });
	UnitData.BenchmarkHidePos = { -652, 228 };
	UnitData.BenchmarkShowPos = { -292, 228 };
	UnitData.CurDir = UIDir::None;
	UnitData.NextDir = UIDir::None;

	std::shared_ptr<GameEngineActor> _Actor = GetLevel()->CreateActor<GameEngineActor>();
	_Actor->GetTransform()->SetParent(UnitData.Render->GetTransform());
	_Actor->GetTransform()->SetLocalPosition(float4::Zero);
	HPBarRender = _Actor->CreateComponent<SpriteRenderer>();
	HPBarRender->SetTexture("HPBar.png");
	HPBarRender->GetTransform()->SetWorldScale({ 168, 8 });
	HPBarRender->GetTransform()->SetLocalPosition({ 64, -48 });

	PortraitRender = _Actor->CreateComponent<SpriteRenderer>();
	PortraitRender->SetTexture("BattleIcon_Lyn.png");
	//PortraitRender->GetTransform()->SetParent(UnitData.Render->GetTransform());
	PortraitRender->GetTransform()->SetWorldScale({ 128, 128 });
	PortraitRender->GetTransform()->SetLocalPosition({ -96, 0 });
	CursorDir = UIDir::None;

	Off();
}
static float Timer = 0;
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
	if (_Dir == UIDir::None)
	{
		switch (CurDir)
		{
		case UIDir::None:
			StartPos = BenchmarkHidePos;
			TargetPos = BenchmarkHidePos;
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

	if (CurDir == _Dir)
	{
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
