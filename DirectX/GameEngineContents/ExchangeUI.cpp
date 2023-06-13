#include "PrecompileHeader.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ExchangeUI.h"
#include "MapCursor.h"
#include "BattleLevel.h"
#include "NumberActor.h"
#include "UICursor.h"
ExchangeUI::ExchangeUI()
{
}

ExchangeUI::~ExchangeUI()
{
}

void ExchangeUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_UI = _Cursor;
	Cursor_Map = _Level->GetMapCursor();
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);
}

void ExchangeUI::On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	GameEngineActor::On();

	IsOnFrame = true;
	LeftUnit = _SelectUnit;
	LeftItems = LeftUnit->GetUnitData().GetItems();
	TargetUnits = _TargetUnits;
	TargetIter = TargetUnits.begin();
	SetTarget();
	TargetSelectStart();
}

void ExchangeUI::Off()
{
	GameEngineActor::Off();
	Cursor_UI->Off();
}

void ExchangeUI::Start()
{
	LeftWindow = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	LeftWindow->SetSprite("ItemUI.png", 4);
	LeftWindow->GetTransform()->SetLocalPosition({-228, -128});
	LeftWindow->GetTransform()->SetLocalScale({420, 356});

	LeftPortrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	LeftPortrait->GetTransform()->SetParent(LeftWindow->GetTransform());
	LeftPortrait->GetTransform()->SetWorldScale({ -384, 320 });
	LeftPortrait->GetTransform()->SetLocalPosition({ 0, 298 });
	LeftPortrait->GetTransform()->SetWorldRotation(float4::Zero);

	RightWindow = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	RightWindow->SetSprite("ItemUI.png", 4);
	RightWindow->GetTransform()->SetLocalPosition({ 228, -128 });
	RightWindow->GetTransform()->SetLocalScale({ 420, 356 });

	RightPortrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	RightPortrait->GetTransform()->SetParent(RightWindow->GetTransform());
	RightPortrait->GetTransform()->SetWorldScale({ 384, 320 });
	RightPortrait->GetTransform()->SetLocalPosition({ 0, 298 });
	RightPortrait->GetTransform()->SetWorldRotation(float4::Zero);

	if (nullptr == GameEngineSprite::Find("items.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Item");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Items.png").GetFullPath(), 7, 5);
	}

	LeftIcons.resize(5);
	RightIcons.resize(5);
	LeftUses.resize(5);
	RightUses.resize(5);
	for (int i = 0; i < 5; i++)
	{
		LeftIcons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIText);
		LeftIcons[i]->GetTransform()->SetParent(LeftWindow->GetTransform());
		LeftIcons[i]->GetTransform()->SetLocalPosition({ -160, 128.0f - (i * 64.0f) });
		LeftIcons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		LeftIcons[i]->GetTransform()->SetWorldRotation(float4::Zero);
		LeftIcons[i]->SetSprite("items.png", 0);
		LeftIcons[i]->Off();

		LeftUses[i] = GetLevel()->CreateActor<NumberActor>();
		LeftUses[i]->NumberCreate(RenderOrder::UIText);
		LeftUses[i]->GetTransform()->SetParent(LeftWindow->GetTransform());
		LeftUses[i]->GetTransform()->SetLocalPosition({ 160, 128.0f - (i * 64.0f) });
		LeftUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
		LeftUses[i]->GetTransform()->SetWorldScale(float4::One);
		LeftUses[i]->Off();

		RightIcons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIText);
		RightIcons[i]->GetTransform()->SetParent(RightWindow->GetTransform());
		RightIcons[i]->GetTransform()->SetLocalPosition({ -160, 128.0f - (i * 64.0f) });
		RightIcons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		RightIcons[i]->GetTransform()->SetWorldRotation(float4::Zero);
		RightIcons[i]->SetSprite("items.png", 0);
		RightIcons[i]->Off();

		RightUses[i] = GetLevel()->CreateActor<NumberActor>();
		RightUses[i]->NumberCreate(RenderOrder::UIText);
		RightUses[i]->GetTransform()->SetParent(RightWindow->GetTransform());
		RightUses[i]->GetTransform()->SetLocalPosition({ 160, 128.0f - (i * 64.0f) });
		RightUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
		RightUses[i]->GetTransform()->SetWorldScale(float4::One);
		RightUses[i]->Off();
	}
}

void ExchangeUI::Update(float _DeltaTime)
{
	if (true == IsUnitSelect)
	{
		ExchangeUpdate(_DeltaTime);
	}
	else
	{
		TargetSelectUpdate(_DeltaTime);
	}
}

void ExchangeUI::TargetSelectStart()
{
	IsUnitSelect = false;
	Cursor_Map->On();
	Cursor_UI->Off();
	LeftWindow->Off();
	RightWindow->Off();
}

void ExchangeUI::TargetSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		ExchangeStart();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		Cursor_Map->SetCursorPos(LeftUnit->GetMapPos());
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

void ExchangeUI::ExchangeStart()
{
	// 아이템 목록 세팅
	RightItems = RightUnit->GetUnitData().GetItems();

	std::list<std::shared_ptr<Item>>::iterator ItemIter = LeftItems.begin();
	for (int i = 0; i < LeftItems.size(); i++)
	{
		LeftIcons[i]->SetFrame(static_cast<size_t>((*ItemIter)->GetItemCode()) - 1);
		LeftIcons[i]->On();
		LeftUses[i]->SetValue((*ItemIter)->GetUses());
		LeftUses[i]->On();
		ItemIter++;
	}
	ItemIter = RightItems.begin();
	for (int i = 0; i < RightItems.size(); i++)
	{
		RightIcons[i]->SetFrame(static_cast<size_t>((*ItemIter)->GetItemCode()) - 1);
		RightIcons[i]->On();
		RightUses[i]->SetValue((*ItemIter)->GetUses());
		RightUses[i]->On();
		ItemIter++;
	}

	IsUnitSelect = true;
	Cursor_Map->Off();
	Cursor_UI->On();

	LeftWindow->On();
	RightWindow->On();

	// 초상화 변경
	std::string TextStr = "Portrait_";
	TextStr += LeftUnit ->GetUnitData().GetName();
	TextStr += ".png";
	LeftPortrait->SetTexture(TextStr);

	TextStr = "Portrait_";
	TextStr += RightUnit->GetUnitData().GetName();
	TextStr += ".png";
	RightPortrait->SetTexture(TextStr);

	CurrentCursor = { 0, 0 };
	CursorPos = StartCursorPos + float4(456 * CurrentCursor.x, -64 * CurrentCursor.y);
	Cursor_UI->GetTransform()->SetLocalPosition(CursorPos);
}

void ExchangeUI::ExchangeUpdate(float _DeltaTime)
{
	Cursor_UI->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		//ExchangeStart();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		TargetSelectStart();
		return;
	}

	if (GameEngineInput::IsDown("Left"))
	{
		CurrentCursor += int2::Left;
		CursorPos = StartCursorPos + float4(456 * CurrentCursor.x, -64 * CurrentCursor.y);
		return;
	}
	if (GameEngineInput::IsDown("Right"))
	{
		CurrentCursor += int2::Right;
		CursorPos = StartCursorPos + float4(456 * CurrentCursor.x, -64 * CurrentCursor.y);
		return;
	}
	if (GameEngineInput::IsDown("Up"))
	{
		CurrentCursor += int2::Down;
		CursorPos = StartCursorPos + float4(456 * CurrentCursor.x, -64 * CurrentCursor.y);
		return;
	}
	if (GameEngineInput::IsDown("Down"))
	{
		CurrentCursor += int2::Up;
		CursorPos = StartCursorPos + float4(456 * CurrentCursor.x, -64 * CurrentCursor.y);
		return;
	}
}

void ExchangeUI::SetTarget()
{
	RightUnit = *TargetIter;
	Cursor_Map->SetMapPos(RightUnit->GetMapPos());
}
