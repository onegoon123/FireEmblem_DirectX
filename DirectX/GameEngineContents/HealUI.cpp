#include "PrecompileHeader.h"
#include "HealUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "MapCursor.h"
#include "DebugWindow.h"
#include "NumberActor.h"
#include "DoubleIconActor.h"
#include "UIButtonSystem.h"
#include "TextRenderer.h"
HealUI::HealUI()
{
}

HealUI::~HealUI()
{
}

void HealUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_UI = _Cursor;
	Cursor_Map = _Level->GetMapCursor();
	HealFunction = std::bind(&BattleLevel::UnitCommand_TargetHeal, _Level, std::placeholders::_1, std::placeholders::_2);
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);

}

void HealUI::On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	GameEngineActor::On();

	SelectUnit = _SelectUnit;
	TargetUnits = _TargetUnits;
	Items = &SelectUnit->GetUnitData().GetItems();
	Staves.clear();
	for (std::shared_ptr<Item> _Item : *Items)
	{
		if (_Item->GetItemType() == ItemType::Stave)
		{
			Staves.push_back(_Item);
		}
	}

	if (Staves.size() == 0)
	{
		CancelFunction();
		return;
	}
	// 무기 갯수만큼 UI창 지정
	WindowRender->SetFrame(Staves.size() - 1);

	// 초상화 지정
	std::string TextStr = "Portrait_";
	TextStr += SelectUnit->GetUnitData().GetName();
	TextStr += ".png";
	Portrait->SetTexture(TextStr);

	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	CurrentCursor = 0;
	Cursor_UI->On();
	CursorPos = StartCursorPos;
	Cursor_UI->GetTransform()->SetLocalPosition(StartCursorPos);

	IsOnFrame = true;
	IsStaveSelect = false;
	StaveSelectStart();

	// 무기 아이콘 지정
	size_t i = 0;
	for (std::shared_ptr<Item> _Item : Staves)
	{
		StaveIcon[i]->SetFrame(static_cast<size_t>(_Item->GetItemCode()) - 1);
		StaveIcon[i]->On();
		ItemNameTexts[i]->SetText(_Item->GetName());

		switch (_Item->GetItemCode())
		{
		case ItemCode::Heal:
			ItemInfoText->SetText("아군의 HP를 회복합니다");
			break;
		case ItemCode::Rescue:
			break;
		default:
			break;
		}
		i++;
	}
	for (i = Staves.size(); i < 5; i++)
	{
		StaveIcon[i]->Off();
	}
	std::list<std::shared_ptr<Item>>::iterator StavesIter = Staves.begin();
	// 무기 내구도 표기
	for (int i = 0; i < Staves.size(); i++)
	{
		StaveUses[i]->On();
		StaveUses[i]->SetValue((*StavesIter)->GetUses());
		StavesIter++;
	}


	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";
	for (std::shared_ptr<Item> _Stave : Staves)
	{
		Window->Text += _Stave->GetName();
		Window->Text += " ";
		Window->Text += std::to_string(_Stave->GetUses());
		Window->Text += " / " + std::to_string(_Stave->GetMaxUses()) + '\n';
	}

	for (int i = 0; i < Staves.size(); i++)
	{
		ButtonCols[i]->On();
		ItemNameTexts[i]->On();
	}
	for (size_t i = Staves.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
		ItemNameTexts[i]->Off();
	}
}


void HealUI::Off()
{
	GameEngineActor::Off();
	Cursor_UI->Off();
	for (int i = 0; i < 5; i++)
	{
		StaveUses[i]->Off();
	}
}


void HealUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetLocalScale({ 420, 356, 1 });
	
	WindowRender->SetSprite("ItemUI.png", 2);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetLocalScale({ 368, 20, 1 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	InfoRender->GetTransform()->SetLocalScale({ 420, 356,1 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetSprite("ItemUI.png", 2);

	ItemInfoText = CreateComponent<TextRenderer>(RenderOrder::UIText);
	ItemInfoText->GetTransform()->SetLocalPosition({ 40, -74});
	ItemInfoText->GetTransform()->SetParent(InfoRender->GetTransform());
	ItemInfoText->Setting("Silhoua14", 45, float4::White, float4::Black, FontAligned::Left);

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetLocalScale({ 384, 320,1 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	StaveIcon.resize(5);
	for (int i = 0; i < 5; i++)
	{
		StaveIcon[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		StaveIcon[i]->SetSprite("Items.png", 0);

		StaveIcon[i]->GetTransform()->SetLocalScale({ 64, 64 });
		StaveIcon[i]->GetTransform()->SetLocalPosition({ -386.0f, 198.0f - (64.0f * i) });

		StaveIcon[i]->Off();
	}

	{
		// 무기 내구도
		StaveUses.resize(5);
		for (int i = 0; i < 5; i++)
		{
			StaveUses[i] = GetLevel()->CreateActor<NumberActor>();
			StaveUses[i]->GetTransform()->SetLocalPosition({ 172, 128.0f - i * 64 });
			StaveUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			StaveUses[i]->GetTransform()->SetLocalScale(float4::One);
			StaveUses[i]->GetTransform()->SetParent(WindowRender->GetTransform());
			StaveUses[i]->SetValue(0);
			StaveUses[i]->Off();
		}
	}
	WindowRender->GetTransform()->SetLocalPosition({ -224, 64 });
	ButtonSystem = GetLevel()->CreateActor<UIButtonSystem>();
	ButtonSystem->GetTransform()->SetParent(GetTransform());

	ButtonCols.resize(5);
	ItemNameTexts.resize(5);
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		ButtonCols[i]->GetTransform()->SetLocalPosition({ -250, 192.0f - (64 * i) });
		ButtonCols[i]->GetTransform()->SetLocalScale({ 400, 64 });
		ButtonCols[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(ButtonCols[i],
			[=] {
				CurrentCursor = i;
				SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
				SetStave();
			},
			[this]
			{
				IsClick = true;
			}
			);
		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -332, 220.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		ItemNameTexts[i]->Off();
	}

	GameEngineActor::Off();
}

void HealUI::Update(float _DeltaTime)
{
	if (true == IsStaveSelect)
	{
		TargetSelectUpdate(_DeltaTime);
		return;
	}
	StaveSelectUpdate(_DeltaTime);
}

void HealUI::StaveSelectStart()
{
	IsStaveSelect = false;
	SelectRender->On();
	WindowRender->On();
	InfoRender->On();
	Portrait->On();
	Cursor_UI->On();

	for (int i = 0; i < Staves.size(); i++)
	{
		StaveIcon[i]->On();
	}
	SetStave();

	for (int i = 0; i < Staves.size(); i++)
	{
		ButtonCols[i]->On();
		ItemNameTexts[i]->On();
	}
	for (size_t i = Staves.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
		ItemNameTexts[i]->Off();
	}
}

void HealUI::StaveSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || true == IsClick)
	{
		IsClick = false;
		StaveSelectEnd();
		TargetSelectStart();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor_UI->GetTransform()->SetLocalPosition(float4::Lerp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	if (CursorTimer < 1) { return; }



	if (PreesTime < GameEngineInput::GetPressTime("Up") || PreesTime < GameEngineInput::GetPressTime("Down"))
	{
		PressOK = true;
	}
	else if (GameEngineInput::IsFree("Up") && GameEngineInput::IsFree("Down"))
	{
		PressOK = false;
	}

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{
		CursorTimer = 0;
		if (CurrentCursor == 0)
		{
			if (false == GameEngineInput::IsDown("Up")) { return; }
			CurrentCursor = Staves.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
			SetStave();
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetStave();
		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK) || GameEngineInput::IsUp("MiddleClick"))
	{
		CursorTimer = 0;
		if (CurrentCursor == Staves.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos;
			SetStave();
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetStave();
		return;
	}

}

void HealUI::StaveSelectEnd()
{
	SelectRender->Off();
	WindowRender->Off();
	InfoRender->Off();
	Portrait->Off();
	Cursor_UI->Off();
	for (int i = 0; i < Staves.size(); i++)
	{
		StaveIcon[i]->Off();
	}
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i]->Off();
		ItemNameTexts[i]->Off();
	}
}

void HealUI::SetStave()
{
	std::list<std::shared_ptr<Item>>::iterator StartIter = Staves.begin();
	std::advance(StartIter, CurrentCursor);
	if (StartIter == Staves.end())
	{
		MsgAssert("선택한 무기를 무기리스트에서 찾지 못했습니다.");
		return;
	}
	SelectStave = *StartIter;

	StaveIter = Items->begin();
	for (; StaveIter != Items->end(); StaveIter++)
	{
		if (SelectStave == *StaveIter)
		{
			break;
		}
	}
}

void HealUI::TargetSelectStart()
{
	IsStaveSelect = true;

	TargetIter = TargetUnits.begin();
	Cursor_Map->On();

	SetTarget();
}

void HealUI::TargetSelectUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		HealFunction(TargetUnit, StaveIter);
		Cursor_Map->Off();
		Off();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		StaveSelectStart();
		Cursor_Map->SetCursorPos(SelectUnit->GetMapPos());
		Cursor_Map->Off();
		return;
	}
	if (Cursor_Map->GetIsMove()) { return; }


	if (GameEngineInput::IsDown("Up") || GameEngineInput::IsDown("Left"))
	{
		if (TargetIter == TargetUnits.begin())
		{
			TargetIter = TargetUnits.end();
		}
		TargetIter--;
		SetTarget();
		return;
	}
	if (GameEngineInput::IsDown("Down") || GameEngineInput::IsDown("Right") || GameEngineInput::IsUp("MiddleClick"))
	{
		TargetIter++;
		if (TargetIter == TargetUnits.end())
		{
			TargetIter = TargetUnits.begin();
		}
		SetTarget();
		return;
	}
}

void HealUI::TargetSelectEnd()
{
}

void HealUI::SetTarget()
{

	TargetUnit = *TargetIter;
	Cursor_Map->SetCursorPos(TargetUnit->GetMapPos());
}
