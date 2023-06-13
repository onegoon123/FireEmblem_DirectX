#include "PrecompileHeader.h"
#include "ItemUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "DebugWindow.h"
#include "NumberActor.h"
#include "UIButtonSystem.h"
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

	WindowRender->SetFrame(ItemSize - 1);
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
		ItemUses[i]->SetValue(_Item->GetUses());
		ItemUses[i]->On();
		i++;
	}
	for (i = ItemSize; i < 5; i++)
	{
		Icons[i]->Off();
		ItemUses[i]->Off();
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

	for (int i = 0; i < ItemSize; i++)
	{
		ItemButtons[i]->On();
	}
	for (size_t i = ItemSize; i < 5; i++)
	{
		ItemButtons[i]->Off();
	}
	for (int i = 0; i < 2; i++)
	{
		UseButtons[i]->Off();
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
	WindowRender->SetSprite("ItemUI.png", 0);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetWorldScale({ 368, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	InfoRender->GetTransform()->SetWorldScale({ 420, 356 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetSprite("ItemUI.png", 2);

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	ItemUseWindow = CreateComponent<GameEngineUIRenderer>(static_cast<int>(RenderOrder::UIText) + 1);
	ItemUseWindow->GetTransform()->SetWorldScale({ 160, 192 });
	ItemUseWindow->SetTexture("ItemUse.png");

	ItemUseSelect = CreateComponent<GameEngineUIRenderer>(static_cast<int>(RenderOrder::UIText) + 2);
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
		Icons[i]->GetTransform()->SetLocalPosition({ -386.0f, 198.0f - (64.0f * i) });

		Icons[i]->Off();
	}

	{
		// 아이템 내구도
		ItemUses.resize(5);
		for (int i = 0; i < 5; i++)
		{
			ItemUses[i] = GetLevel()->CreateActor<NumberActor>();
			ItemUses[i]->GetTransform()->SetParent(WindowRender->GetTransform());
			ItemUses[i]->GetTransform()->SetLocalPosition({ 172, 128.0f - i * 64 });
			ItemUses[i]->GetTransform()->SetWorldRotation(float4::Zero);
			ItemUses[i]->GetTransform()->SetWorldScale(float4::One);
			ItemUses[i]->SetValue(0);
			ItemUses[i]->Off();
		}
	}

	ButtonSystem = GetLevel()->CreateActor<UIButtonSystem>();
	ButtonSystem->GetTransform()->SetParent(GetTransform());

	ItemButtons.resize(5);
	for (int i = 0; i < 5; i++)
	{
		ItemButtons[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		ItemButtons[i]->GetTransform()->SetLocalPosition({ -250, 192.0f - (64 * i) });
		ItemButtons[i]->GetTransform()->SetLocalScale({ 400, 64 });
		ItemButtons[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(ItemButtons[i],
			[=] {
				CurrentCursor = i;
				SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
			},
			[this]
			{
				ItemSelect();
			}
			);
	}

	UseButtons.resize(2);
	for (int i = 0; i < 2; i++)
	{
		UseButtons[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		UseButtons[i]->GetTransform()->SetLocalPosition({ -75, 192.0f - (64 * i) });
		UseButtons[i]->GetTransform()->SetLocalScale({ 250, 64 });
		UseButtons[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(UseButtons[i],
			[=] {
				CurrentUseCursor = i;
				ItemUseSelect->GetTransform()->SetLocalPosition(StartUseSelectPos + float4::Down * (64.0f * CurrentUseCursor));
				UseCursorPos = StartUseCursorPos + float4::Down * (64.0f * CurrentUseCursor);
			},
			[this]
			{
				UseFunctions[CurrentUseCursor]();
			}
			);
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

	if (GameEngineInput::IsDown("ButtonA"))
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
	{
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(*ItemIter);
		if (true == _Weapon->IsUseWeapon(SelectUnit->GetUnitData().GetClassValue()))
		{
			UseFunctions.push_back(std::bind(&ItemUI::Equipment, this));
			UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
			Window->Text += "장비\n버리기";
		}
		else
		{
			UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
			Window->Text += "버리기";
		}
		break;
	}
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

	for (int i = 0; i < ItemSize; i++)
	{
		ItemButtons[i]->Off();
	}
	for (int i = 0; i < UseFunctions.size(); i++)
	{
		UseButtons[i]->On();
		UseButtons[i]->GetTransform()->SetLocalPosition({ -75, 192.0f - (64 * (i + CurrentCursor))});
	}
	for (size_t i = UseFunctions.size(); i < 2; i++)
	{
		UseButtons[i]->Off();
	}
}

void ItemUI::ItemUseUpdate(float _DeltaTime)
{

	if (GameEngineInput::IsDown("ButtonA"))
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
		for (int i = 0; i < ItemSize; i++)
		{
			ItemButtons[i]->On();
		}
		for (size_t i = ItemSize; i < 5; i++)
		{
			ItemButtons[i]->Off();
		}
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
	On(SelectUnit);
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
