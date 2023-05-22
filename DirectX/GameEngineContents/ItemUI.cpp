#include "PrecompileHeader.h"
#include "ItemUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "DebugWindow.h"
ItemUI::ItemUI() 
{
}

ItemUI::~ItemUI() 
{
}

void ItemUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor = _Cursor;
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);
	UseFunction = std::bind(&BattleLevel::UnitCommand_ItemUse, _Level, std::placeholders::_1);
}

void ItemUI::On(std::shared_ptr<BattleUnit> _SelectUnit)
{
	GameEngineActor::On();

	SelectUnit = _SelectUnit;
	ItemSize = SelectUnit->GetUnitData().GetItems().size();
	switch (ItemSize)
	{
	case 0:
	case 1:
		WindowRender->SetTexture("ItemListUI1.png");
		break;
	case 2:
		WindowRender->SetTexture("ItemListUI2.png");
		break;
	case 3:
		WindowRender->SetTexture("ItemListUI3.png");
		break;
	case 4:
		WindowRender->SetTexture("ItemListUI4.png");
		break;
	case 5:
		WindowRender->SetTexture("ItemListUI5.png");
		break;
	default:
	{
		MsgAssert("정해진 아이템 갯수의 범위를 벗어났습니다.");
		return;
	}
	}
	std::string TextStr = "Portrait_";
	TextStr += SelectUnit->GetUnitData().GetName();
	TextStr += ".png";
	Portrait->SetTexture(TextStr);

	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);

	CurrentCursor = 0;
	Cursor->On();
	CursorPos = StartCursorPos;
	Cursor->GetTransform()->SetLocalPosition(StartCursorPos);

	ItemUseWindow->Off();
	ItemUseSelect->Off();

	IsOnFrame = true;
	IsItemSelect = false;

	size_t i = 0;
	for (std::shared_ptr<Item> _Item : SelectUnit->GetUnitData().GetItems())
	{
		Icons[i]->SetFrame(static_cast<size_t>(_Item->GetItemCode()) - 1);
		Icons[i]->On();
		i++;
	}
	for (i = ItemSize; i < 5; i++)
	{
		Icons[i]->Off();
	}

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";
	for (std::shared_ptr<Item> _Item : SelectUnit->GetUnitData().GetItems())
	{
		Window->Text += _Item->GetName();
		Window->Text += " ";
		Window->Text += std::to_string(_Item->GetUses());
		Window->Text += " / " + std::to_string(_Item->GetMaxUses()) + '\n';
	}
}

void ItemUI::Off()
{
	GameEngineActor::Off();
	Cursor->Off();
}

void ItemUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetWorldScale({ 420, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ -224, 64 });
	WindowRender->SetTexture("ItemListUI3.png");

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetWorldScale({ 368, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	InfoRender->GetTransform()->SetWorldScale({ 420, 356 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetTexture("ItemListUI3.png");

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	ItemUseWindow = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	ItemUseWindow->GetTransform()->SetWorldScale({ 160, 192 });
	ItemUseWindow->SetTexture("ItemUse.png");

	ItemUseSelect = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	ItemUseSelect->GetTransform()->SetWorldScale({ 76, 20 });
	ItemUseSelect->SetTexture("ItemUseSelect.png");

	if (nullptr == GameEngineSprite::Find("items.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Item");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("Items.png").GetFullPath(), 7, 5);
	}
	
	Icons.resize(5);
	for (int i = 0; i < 5; i++)
	{
		Icons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Icons[i]->SetSprite("Items.png", 0);

		Icons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		Icons[i]->GetTransform()->SetLocalPosition({ -386.0f, 198.0f - (64.0f * i)});

		Icons[i]->Off();
	}

	GameEngineActor::Off();
}

void ItemUI::Update(float _DeltaTime)
{
	if (true == IsItemSelect)
	{
		ItemUseUpdate(_DeltaTime);
		return;
	}
	ItemSelectUpdate(_DeltaTime);
}

void ItemUI::ItemSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		ItemSelect();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

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
			CurrentCursor = ItemSize - 1;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK) || GameEngineInput::IsUp("MiddleClick"))
	{
		CursorTimer = 0;
		if (CurrentCursor == ItemSize - 1)
		{
			if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos;
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);

		return;
	}

}

void ItemUI::ItemSelect()
{
	Cursor->GetTransform()->SetLocalPosition(CursorPos);
	IsItemSelect = true;
	ItemIter = SelectUnit->GetUnitData().GetItems().begin();
	std::advance(ItemIter, CurrentCursor);



	ItemUseWindow->GetTransform()->SetLocalPosition(float4(-80.0f, 164.0f) + float4::Down * static_cast<float>(CurrentCursor) * 64);

	StartUseSelectPos = float4(-80.0f, 198.0f) + float4::Down * static_cast<float>(CurrentCursor) * 64;
	StartUseCursorPos = float4(-158.0f, 198.0f) + float4::Down * static_cast<float>(CurrentCursor) * 64;

	ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos);
	Cursor->GetTransform()->SetLocalPosition(StartUseCursorPos);
	UseCursorPos = StartUseCursorPos;

	ItemUseWindow->On();
	ItemUseSelect->On();

	CursorTimer = 99;
	CurrentUseCursor = 0;
	UseFunctions.clear();

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";

	switch ((*ItemIter)->GetItemType())
	{
	case ItemType::None:
		break;
	case ItemType::Weapon:
		UseFunctions.push_back(std::bind(&ItemUI::Equipment, this));
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "장비\n버리기";
		break;
	case ItemType::Stave:
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "버리기";
		break;
	case ItemType::Potion:
		UseFunctions.push_back(std::bind(&ItemUI::Use, this));
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "사용\n버리기";
		break;
	case ItemType::Key:
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "버리기";
		break;
	default:
	{
		MsgAssert("지정되지 않은 아이템 타입입니다.");
	}
		break;
	}

}

void ItemUI::ItemUseUpdate(float _DeltaTime)
{

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		UseFunctions[CurrentUseCursor]();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		ItemUseWindow->Off();
		ItemUseSelect->Off();
		IsItemSelect = false;
		Cursor->GetTransform()->SetLocalPosition(StartCursorPos + float4::Down * (64.0f * CurrentCursor));
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), UseCursorPos, _DeltaTime * 20));

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
		if (CurrentUseCursor == 0)
		{
			if (false == GameEngineInput::IsDown("Up")) { return; }
			CurrentUseCursor = UseFunctions.size() - 1;
			ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos + float4::Down * (64.0f * CurrentUseCursor));
			UseCursorPos = StartUseCursorPos + float4::Down * (64.0f * CurrentUseCursor);
			return;
		}
		CurrentUseCursor--;
		ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos + float4::Down * (64.0f * CurrentUseCursor));
		UseCursorPos = StartUseCursorPos + float4::Down * (64.0f * CurrentUseCursor);

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK) || GameEngineInput::IsUp("MiddleClick"))
	{
		CursorTimer = 0;
		if (CurrentUseCursor == UseFunctions.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
			CurrentUseCursor = 0;
			ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos + float4::Down * (64.0f * CurrentUseCursor));
			UseCursorPos = StartUseCursorPos;
			return;
		}
		CurrentUseCursor++;
		ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos + float4::Down * (64.0f * CurrentUseCursor));
		UseCursorPos = StartUseCursorPos + float4::Down * (64.0f * CurrentUseCursor);

		return;
	}

}

void ItemUI::Equipment()
{
	//std::list<std::shared_ptr<Item>>& _Items = SelectUnit->GetUnitData().GetItems();
	//std::list<std::shared_ptr<Item>>::iterator Iter = std::find(_Items.begin(), _Items.end(), SelectItem);
	//_Items.splice(_Items.begin(), _Items, Iter);

	SelectUnit->GetUnitData().EquipWeapon(std::dynamic_pointer_cast<Weapon>(*ItemIter));

	ItemUseWindow->Off();
	ItemUseSelect->Off();
	IsItemSelect = false;
	Cursor->GetTransform()->SetLocalPosition(StartCursorPos + float4::Down * (64.0f * CurrentCursor));
}

void ItemUI::Drop()
{
	SelectUnit->GetUnitData().DropItem(ItemIter);

	ItemUseWindow->Off();
	ItemUseSelect->Off();
	IsItemSelect = false;
	Cursor->GetTransform()->SetLocalPosition(StartCursorPos + float4::Down * (64.0f * CurrentCursor));

	On(SelectUnit);
}

void ItemUI::Use()
{
	UseFunction(ItemIter);
}
