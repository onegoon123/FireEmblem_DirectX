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
	Cursor_UI->GetTransform()->SetLocalPosition(StartCursorPos);
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
	LeftWindow = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	LeftWindow->SetSprite("ItemUI.png", 4);
	LeftWindow->GetTransform()->SetLocalPosition({-228, -128});
	LeftWindow->GetTransform()->SetLocalScale({420, 356});

	LeftPortrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::Unit);
	LeftPortrait->GetTransform()->SetParent(LeftWindow->GetTransform());
	LeftPortrait->GetTransform()->SetWorldScale({ -384, 320 });
	LeftPortrait->GetTransform()->SetLocalPosition({ 0, 298 });
	LeftPortrait->GetTransform()->SetWorldRotation(float4::Zero);

	RightWindow = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	RightWindow->SetSprite("ItemUI.png", 4);
	RightWindow->GetTransform()->SetLocalPosition({ 228, -128 });
	RightWindow->GetTransform()->SetLocalScale({ 420, 356 });

	RightPortrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::Unit);
	RightPortrait->GetTransform()->SetParent(RightWindow->GetTransform());
	RightPortrait->GetTransform()->SetWorldScale({ 384, 320 });
	RightPortrait->GetTransform()->SetLocalPosition({ 0, 298 });
	RightPortrait->GetTransform()->SetWorldRotation(float4::Zero);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->SetTexture("ItemSelect.png");
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->GetTransform()->SetLocalScale({368, 20});

	CursorRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	CursorRender->SetTexture("CommandCursor.png");
	CursorRender->GetTransform()->SetLocalPosition(StartCursorPos);
	CursorRender->GetTransform()->SetLocalScale({64, 64});

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
	if (true == IsItemSelect)
	{
		ItemSelectUpdate(_DeltaTime);
	}
	else if (true == IsUnitSelect)
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
	SelectRender->Off();
	CursorRender->Off();
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
	for (int i = 0; i < (int)LeftItems.size(); i++)
	{
		LeftIcons[i]->SetFrame(static_cast<size_t>((*ItemIter)->GetItemCode()) - 1);
		LeftIcons[i]->On();
		LeftUses[i]->SetValue((*ItemIter)->GetUses());
		LeftUses[i]->On();
		ItemIter++;
	}
	for (int i = (int)LeftItems.size(); i < 5; i++)
	{
		LeftIcons[i]->Off();
		LeftUses[i]->Off();
	}
	ItemIter = RightItems.begin();
	for (int i = 0; i < (int)RightItems.size(); i++)
	{
		RightIcons[i]->SetFrame(static_cast<size_t>((*ItemIter)->GetItemCode()) - 1);
		RightIcons[i]->On();
		RightUses[i]->SetValue((*ItemIter)->GetUses());
		RightUses[i]->On();
		ItemIter++;
	}
	for (int i = (int)RightItems.size(); i < 5; i++)
	{
		RightIcons[i]->Off();
		RightUses[i]->Off();
	}

	IsUnitSelect = true;
	IsItemSelect = false;
	Cursor_Map->Off();
	Cursor_UI->On();
	SelectRender->On();
	CursorRender->Off();
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

	if (CurrentCursor.x == 0 && CurrentCursor.y == (int)LeftItems.size())
	{
		CurrentCursor.y = (int)LeftItems.size() - 1;
	}
	else if (CurrentCursor.x == 1 && CurrentCursor.y == (int)RightItems.size())
	{
		CurrentCursor.y = (int)RightItems.size() - 1;
	}
	CursorTimer = 0;
	CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
	//Cursor_UI->GetTransform()->SetLocalPosition(CursorPos);
}

void ExchangeUI::ExchangeUpdate(float _DeltaTime)
{
	Cursor_UI->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));
	CursorTimer += _DeltaTime * 10;
	if (CursorTimer < 1) { return; }

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		ItemSelectStart();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		TargetSelectStart();
		return;
	}

	if (PreesTime < GameEngineInput::GetPressTime("Up") || PreesTime < GameEngineInput::GetPressTime("Down"))
	{
		PressOK = true;
	}
	else if (GameEngineInput::IsFree("Up") && GameEngineInput::IsFree("Down"))
	{
		PressOK = false;
	}

	if (GameEngineInput::IsDown("Left") || GameEngineInput::IsDown("Right"))
	{
		if (CurrentCursor.x == 0)
		{ 
			CurrentCursor.x = 1;
			CurrentCursor.y = std::min<int>(CurrentCursor.y, (int)RightItems.size() - 1);
		}
		else
		{
			CurrentCursor.x = 0;
			CurrentCursor.y = std::min<int>(CurrentCursor.y, (int)LeftItems.size() - 1);
		}
			
		CursorTimer = 0;
		CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
		return;
	}

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{
		if (CurrentCursor.y == 0)
		{ 
			if (false == GameEngineInput::IsDown("Up")) { return; }
			if (CurrentCursor.x == 0)
			{
				CurrentCursor.y = (int)LeftItems.size() - 1;
			}
			else
			{
				CurrentCursor.y = (int)RightItems.size() - 1;
			}
		}
		else
		{
			CurrentCursor.y--;
		}
		CursorTimer = 0;
		CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
		return;
	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		if (CurrentCursor.x == 0 && CurrentCursor.y + 1 >= LeftItems.size() || (CurrentCursor.x == 1 && CurrentCursor.y + 1 >= RightItems.size()))
		{ 
			if (false == GameEngineInput::IsDown("Down")) { return; }
			CurrentCursor.y = 0;
		}
		else
		{
			CurrentCursor.y++;
		}
		CursorTimer = 0;
		CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
		return;
	}
}

void ExchangeUI::ItemSelectStart()
{
	IsItemSelect = true;
	CursorRender->On();
	ItemCursor = CurrentCursor;
	CursorRender->GetTransform()->SetLocalPosition(StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));

	if (CurrentCursor.x == 0)
	{
		CurrentCursor.x = 1;
		CurrentCursor.y = std::min<int>(4, (int)RightItems.size());
	}
	else
	{
		CurrentCursor.x = 0;
		CurrentCursor.y = std::min<int>(4, (int)LeftItems.size());
	}
	CursorTimer = 0;
	CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
}

void ExchangeUI::ItemSelectUpdate(float _DeltaTime)
{
	Cursor_UI->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));
	CursorTimer += _DeltaTime * 10;
	if (CursorTimer < 1) { return; }

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		ItemChange();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		ExchangeStart();
		return;
	}

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
		if (CurrentCursor.y == 0)
		{
			if (false == GameEngineInput::IsDown("Up")) { return; }
			if (CurrentCursor.x == 0)
			{
				CurrentCursor.y = (int)LeftItems.size();
			}
			else
			{
				CurrentCursor.y = (int)RightItems.size();
			}
		}
		else
		{
			CurrentCursor.y--;
		}
		CursorTimer = 0;
		CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
		return;
	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		if (CurrentCursor.x == 0 && CurrentCursor.y == std::min<int>((int)LeftItems.size(), 4))
		{
			if (false == GameEngineInput::IsDown("Down")) { return; }
			CurrentCursor.y = 0;
		}
		else if (CurrentCursor.x == 1 && CurrentCursor.y == std::min<int>((int)RightItems.size(), 4))
		{
			if (false == GameEngineInput::IsDown("Down")) { return; }
			CurrentCursor.y = 0;
		}
		else
		{
			CurrentCursor.y++;
		}
		CursorTimer = 0;
		CursorPos = StartCursorPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y);
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4(456.0f * CurrentCursor.x, -64.0f * CurrentCursor.y));
		return;
	}
}

void ExchangeUI::SetTarget()
{
	RightUnit = *TargetIter;
	Cursor_Map->SetMapPos(RightUnit->GetMapPos());
}

void ExchangeUI::ItemChange()
{
	std::list<std::shared_ptr<Item>>::iterator LeftItemIter = LeftItems.begin();
	std::list<std::shared_ptr<Item>>::iterator RightItemIter = RightItems.begin();
	int LeftIndex = -1;
	int RightIndex = -1;
	LeftItem = nullptr;
	RightItem = nullptr;
	if (ItemCursor.x == 0)
	{
		LeftIndex = ItemCursor.y;
		std::advance(LeftItemIter, ItemCursor.y);
		LeftItem = *LeftItemIter;
		if (CurrentCursor.y != RightItems.size())
		{
			RightIndex = CurrentCursor.y;
			std::advance(RightItemIter, CurrentCursor.y);
			RightItem = *RightItemIter;
		}
	}
	else
	{
		RightIndex = ItemCursor.y;
		std::advance(RightItemIter, ItemCursor.y);
		RightItem = *RightItemIter;
		if (CurrentCursor.y != LeftItems.size())
		{
			LeftIndex = CurrentCursor.y;
			std::advance(LeftItemIter, CurrentCursor.y);
			LeftItem = *LeftItemIter;
		}
	}
	
	if (nullptr == LeftItem)
	{
		LeftUnit->GetUnitData().AddItem(RightItem);
		RightUnit->GetUnitData().DropItem(RightItem);
	}
	else if (nullptr == RightItem)
	{
		RightUnit->GetUnitData().AddItem(LeftItem);
		LeftUnit->GetUnitData().DropItem(LeftItem);
	}
	else
	{
		LeftUnit->GetUnitData().ChangeItem(RightItem, LeftIndex);
		RightUnit->GetUnitData().ChangeItem(LeftItem, RightIndex);
	}

	LeftItems = LeftUnit->GetUnitData().GetItems();
	ExchangeStart();
}
