#include "PrecompileHeader.h"
#include "SelectUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsEnum.h"
#include "BattleUnit.h"
#include "NumberActor.h"
#include "TextRenderer.h"
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
		Goal->ChangeDir(UIDir::None);
		TerrainUI->ChangeDir(UIDir::None);
		UnitData->ChangeDir(UIDir::None);
		break;
	case UIDir::LeftUp:
		Goal->ChangeDir(UIDir::RightUp);
		TerrainUI->ChangeDir(UIDir::RightDown);
		//UnitData->ChangeDir(UIDir::LeftDown);
		break;
	case UIDir::LeftDown:
		Goal->ChangeDir(UIDir::RightUp);
		TerrainUI->ChangeDir(UIDir::RightDown);
		//UnitData->ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightUp:
		Goal->ChangeDir(UIDir::RightDown);
		TerrainUI->ChangeDir(UIDir::LeftDown);
		//UnitData->ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightDown:
		Goal->ChangeDir(UIDir::RightUp);
		TerrainUI->ChangeDir(UIDir::LeftDown);
		//UnitData->ChangeDir(UIDir::LeftUp);
		break;
	default:
		break;
	}


}

void SelectUI::SetTerrainData(Terrain _Data)
{
	std::string TerrainStr = "";
	switch (_Data)
	{
	case Terrain::Plain:
		TerrainStr = "ÆòÁö";
		break;
	case Terrain::Floor:
		TerrainStr = "¹Ù´Ú";
		break;
	case Terrain::Road:
		TerrainStr = "±æ";
		break;
	case Terrain::None:
		TerrainStr = "--";
		break;
	case Terrain::Forest:
		TerrainStr = "½£";
		break;
	case Terrain::Cliff:
		TerrainStr = "º­¶û";
		break;
	case Terrain::Mountain:
		TerrainStr = "»ê";
		break;
	case Terrain::Peak:
		TerrainStr = "³ôÀº »ê";
		break;
	case Terrain::Door:
		TerrainStr = "¹®";
		break;
	case Terrain::Gate:
		TerrainStr = "¹®";
		break;
	case Terrain::Ruins:
		TerrainStr = "ÆóÇã";
		break;
	case Terrain::House:
		TerrainStr = "¹Î°¡";
		break;
	case Terrain::Shop:
		TerrainStr = "»óÁ¡";
		break;
	case Terrain::Sea:
		TerrainStr = "¹Ù´Ù";
		break;
	case Terrain::Lake:
		TerrainStr = "È£¼ö";
		break;
	case Terrain::River:
		TerrainStr = "°­";
		break;
	case Terrain::Bridge:
		TerrainStr = "´Ù¸®";
		break;
	case Terrain::Wall:
		TerrainStr = "º®";
		break;
	case Terrain::Fort:
		TerrainStr = "¿ä»õ";
		break;
	case Terrain::Pillar:
		TerrainStr = "±âµÕ";
		break;
	case Terrain::Throne:
		TerrainStr = "¿ÁÁÂ";
		break;
	case Terrain::Fence :
		TerrainStr = "´ãÀå";
		break;
	default:
		break;
	}
	TerrainText->SetText(TerrainStr);
	TerrainDodge->SetValue(BattleMap::GetTerrainDodge(_Data));
	TerrainDef->SetValue(BattleMap::GetTerrainDef(_Data));
}

void SelectUI::On()
{
	GameEngineActor::On();
	Goal->On();
	Goal->Timer = 0;
	TerrainUI->On();
	TerrainUI->Timer = 0;
	UnitData->On();
	UnitData->Timer = 0;

	Goal->CurDir = UIDir::None;
	Goal->NextDir = UIDir::None;
	TerrainUI->CurDir = UIDir::None;
	TerrainUI->NextDir = UIDir::None;
	UnitData->ChangeDir(UIDir::None);
	CursorDir = UIDir::None;
}

void SelectUI::Off()
{
	GameEngineActor::Off();
	CursorDir = UIDir::None;
	Goal->Off();
	Goal->GetTransform()->SetLocalPosition(Goal->BenchmarkHidePos);
	TerrainUI->Off();
	TerrainUI->GetTransform()->SetLocalPosition(TerrainUI->BenchmarkHidePos);
	UnitData->Off();
	UnitData->GetTransform()->SetLocalPosition(UnitData->BenchmarkHidePos);
}

void SelectUI::SetHPBar(float _Value)
{
	HPBarRender->GetTransform()->SetWorldScale({ 168 * _Value, 8 });
	HPBarRender->GetTransform()->SetLocalPosition(float4(-20 + (84 * _Value), -48));
}

void SelectUI::SetHPLerp(int _Value)
{
	StartValue = (float)UnitHP->GetValue() / UnitMaxHP->GetValue();
	UnitHP->SetValueLerp(_Value);
	TargetValue = (float)_Value / UnitMaxHP->GetValue();
	IsLerp = true;
	Timer = 0;
}

void SelectUI::SetUnitData(std::shared_ptr<BattleUnit> _Unit)
{
	switch (CursorDir)
	{
	case UIDir::None:
		break;
	case UIDir::LeftUp:
		UnitData->ChangeDir(UIDir::LeftDown);
		break;
	case UIDir::LeftDown:
		UnitData->ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightUp:
		UnitData->ChangeDir(UIDir::LeftUp);
		break;
	case UIDir::RightDown:
		UnitData->ChangeDir(UIDir::LeftUp);
		break;
	default:
		break;
	}

	if (true == _Unit->GetIsPlayer())
	{
		UnitData->Render->SetTexture("ActorUI.png");
	}
	else
	{
		UnitData->Render->SetTexture("EnemyActorUI.png");
	}

	std::string TextureName = "BattleIcon_";
	TextureName += _Unit->GetUnitData().GetName().data();
	TextureName += ".png";
	PortraitRender->SetTexture(TextureName);

	SetHPBar(_Unit->GetUnitData().GetHP() / (float)_Unit->GetUnitData().GetMaxHP());
	UnitHP->SetValue(_Unit->GetUnitData().GetHP());
	UnitMaxHP->SetValue(_Unit->GetUnitData().GetMaxHP());
	UnitNameText->SetText(_Unit->GetName());
}

void SelectUI::UnitUIOff()
{
	UnitDataOn = true;
	UnitData->ChangeDir(UIDir::None);
}

void SelectUI::PotionUIOn()
{
	Goal->Off();
	TerrainUI->Off();
}

void SelectUI::PotionUIOff()
{
	Goal->On();
	TerrainUI->On();
}

void SelectUI::Start()
{
	Goal = GetLevel()->CreateActor<SelectUIObject>();
	Goal->GetTransform()->SetParent(GetTransform());

	Goal->Render = Goal->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Goal->Render->SetTexture("ClearGoal.png"); 
	Goal->Render->GetTransform()->SetLocalScale({ 344, 100, 100 });
	Goal->BenchmarkHidePos = { -300, 370 };
	Goal->BenchmarkShowPos = { -300, 254 };
	Goal->CurDir = UIDir::None;
	Goal->NextDir = UIDir::None;

	ClearTargetText = Goal->CreateComponent<TextRenderer>(RenderOrder::UIText);
	ClearTargetText->GetTransform()->SetLocalPosition({ 0, 28 });
	ClearTargetText->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
	ClearTargetText->SetText("¸ñÇ¥:Àû Àü¸ê");
	
	TerrainUI = GetLevel()->CreateActor<SelectUIObject>();
	TerrainUI->GetTransform()->SetParent(GetTransform());

	TerrainUI->Render = TerrainUI->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	TerrainUI->Render->SetTexture("TerrainUI.png");
	TerrainUI->Render->GetTransform()->SetLocalScale({ 192, 212 });
	TerrainUI->BenchmarkHidePos = { -576, 214 };
	TerrainUI->BenchmarkShowPos = { -384, 214 };
	TerrainUI->CurDir = UIDir::None;
	TerrainUI->NextDir = UIDir::None;

	TerrainDef = GetLevel()->CreateActor<NumberActor>();
	TerrainDef->SetBlackFont();
	TerrainDef->SetValue(0);
	TerrainDef->GetTransform()->SetParent(TerrainUI->GetTransform());
	TerrainDef->GetTransform()->SetLocalPosition({ 48, -32 });
	TerrainDef->GetTransform()->SetWorldRotation(float4::Zero);
	TerrainDef->GetTransform()->SetWorldScale({ 1, 0.8f });

	TerrainDodge = GetLevel()->CreateActor<NumberActor>();
	TerrainDodge->SetBlackFont();
	TerrainDodge->SetValue(0);
	TerrainDodge->GetTransform()->SetParent(TerrainUI->GetTransform());
	TerrainDodge->GetTransform()->SetLocalPosition({ 48, -64 });
	TerrainDodge->GetTransform()->SetWorldRotation(float4::Zero);
	TerrainDodge->GetTransform()->SetWorldScale({ 1, 0.8f });

	TerrainText = CreateComponent<TextRenderer>(RenderOrder::UIText);
	TerrainText->GetTransform()->SetParent(TerrainUI->GetTransform());
	TerrainText->GetTransform()->SetLocalPosition({ 0, 44 });
	TerrainText->GetTransform()->SetWorldScale(float4::One);
	TerrainText->GetTransform()->SetWorldRotation(float4::Zero);
	TerrainText->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	UnitData = GetLevel()->CreateActor<SelectUIObject>();
	UnitData->GetTransform()->SetParent(GetTransform());

	UnitData->Render = UnitData->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	UnitData->Render->SetTexture("ActorUI.png");
	UnitData->Render->GetTransform()->SetWorldScale({ 344, 152, 100 });
	UnitData->BenchmarkHidePos = { -652, 228 };
	UnitData->BenchmarkShowPos = { -292, 228 };
	UnitData->CurDir = UIDir::None;
	UnitData->NextDir = UIDir::None;

	UnitNameText = UnitData->CreateComponent<TextRenderer>(RenderOrder::UIText);
	UnitNameText->GetTransform()->SetParent(UnitData->GetTransform());
	UnitNameText->GetTransform()->SetLocalPosition({ 64, 58 });
	UnitNameText->GetTransform()->SetWorldScale(float4::One);
	UnitNameText->Setting("Silhoua14", 50, float4::Black, float4::Null, FontAligned::Center);

	HPBarRender = UnitData->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HPBarRender->SetTexture("HPBar.png");
	HPBarRender->GetTransform()->SetWorldScale({ 168, 8 });
	HPBarRender->GetTransform()->SetLocalPosition({ 64, -48 });

	PortraitRender = UnitData->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	PortraitRender->SetTexture("BattleIcon_Lyn.png");
	PortraitRender->GetTransform()->SetWorldScale({ 128, 128 });
	PortraitRender->GetTransform()->SetLocalPosition({ -96, 0 });
	CursorDir = UIDir::None;

	

	UnitHP = GetLevel()->CreateActor<NumberActor>();
	UnitHP->SetBlackFont();
	UnitHP->SetValue(20);
	UnitHP->GetTransform()->SetParent(UnitData->GetTransform());
	UnitHP->GetTransform()->SetLocalPosition({ 76, -16 });
	UnitHP->GetTransform()->SetWorldRotation(float4::Zero);
	UnitHP->GetTransform()->SetWorldScale({ .8f,.8f });

	UnitMaxHP = GetLevel()->CreateActor<NumberActor>();
	UnitMaxHP->SetBlackFont();
	UnitMaxHP->SetValue(20);
	UnitMaxHP->GetTransform()->SetParent(UnitData->GetTransform());
	UnitMaxHP->GetTransform()->SetLocalPosition({ 146, -16 });
	UnitMaxHP->GetTransform()->SetWorldRotation(float4::Zero);
	UnitMaxHP->GetTransform()->SetWorldScale({ .8f,.8f });

	Off();
}
static float Timer = 0;
void SelectUI::Update(float _DeltaTiime)
{

	if (true == IsLerp)
	{
		Timer += _DeltaTiime * 2;
		if (1 < Timer)
		{
			SetHPBar(TargetValue);
			IsLerp = false;
			return;
		}
		SetHPBar(std::lerp(StartValue, TargetValue, Timer));
	}

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
	GetTransform()->SetLocalPosition(float4::LerpClamp(StartPos, TargetPos, Timer));
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

void SelectUI::SetClearTarget(const std::string_view& _Text)
{
	ClearTargetText->SetText(_Text);
}
