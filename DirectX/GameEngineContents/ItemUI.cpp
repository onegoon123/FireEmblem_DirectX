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
#include "TextRenderer.h"
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
	if (ItemSize == 0)
	{
		CancelFunction();
		return;
	}
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
	SetItemInfo();
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
		ItemNameTexts[i]->On();
		ItemNameTexts[i]->SetText(_Item->GetName());
		i++;
	}
	for (i = ItemSize; i < 5; i++)
	{
		Icons[i]->Off();
		ItemUses[i]->Off();
		ItemNameTexts[i]->Off();
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

	ItemInfoText = CreateComponent<TextRenderer>(RenderOrder::UIText);
	ItemInfoText->GetTransform()->SetLocalPosition({ 40, -74 });
	ItemInfoText->Setting("Silhoua14", 45, float4::White, float4::Black, FontAligned::Left);

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	ItemUseWindow = CreateComponent<GameEngineUIRenderer>(static_cast<int>(RenderOrder::UIText) + 1);
	ItemUseWindow->GetTransform()->SetWorldScale({ 160, 192 });
	ItemUseWindow->SetTexture("ItemUse.png");

	ItemUseText1 = CreateComponent<TextRenderer>(RenderOrder::UIText);
	ItemUseText1->GetTransform()->SetParent(ItemUseWindow->GetTransform());
	ItemUseText1->GetTransform()->SetLocalPosition({ 0, 64 });
	ItemUseText1->GetTransform()->SetWorldRotation(float4::Zero);
	ItemUseText1->GetTransform()->SetWorldScale(float4::One);
	ItemUseText1->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

	ItemUseText2 = CreateComponent<TextRenderer>(RenderOrder::UIText);
	ItemUseText2->GetTransform()->SetParent(ItemUseWindow->GetTransform());
	ItemUseText2->GetTransform()->SetLocalPosition({ 0, -12 });
	ItemUseText2->GetTransform()->SetWorldRotation(float4::Zero);
	ItemUseText2->GetTransform()->SetWorldScale(float4::One);
	ItemUseText2->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

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
	ItemNameTexts.resize(5);
	for (int i = 0; i < 5; i++)
	{
		Icons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Icons[i]->SetSprite("Items.png", 0);

		Icons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		Icons[i]->GetTransform()->SetLocalPosition({ -386.0f, 198.0f - (64.0f * i) });

		Icons[i]->Off();

		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -332, 220.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		ItemNameTexts[i]->Off();
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
				SetItemInfo();
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
		UseButtons[i]->GetTransform()->SetLocalPosition({ 80, 192.0f - (64 * i) });
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

	{
		// 무기 수치
		WeaponDamage = GetLevel()->CreateActor<NumberActor>();
		WeaponDamage->GetTransform()->SetParent(GetTransform());
		WeaponDamage->GetTransform()->SetLocalPosition({ 198, -156 });

		WeaponHit = GetLevel()->CreateActor<NumberActor>();
		WeaponHit->GetTransform()->SetParent(GetTransform());
		WeaponHit->GetTransform()->SetLocalPosition({ 198, -220 });

		WeaponCritical = GetLevel()->CreateActor<NumberActor>();
		WeaponCritical->GetTransform()->SetParent(GetTransform());
		WeaponCritical->GetTransform()->SetLocalPosition({ 384, -156 });

		WeaponWeight = GetLevel()->CreateActor<NumberActor>();
		WeaponWeight->GetTransform()->SetParent(GetTransform());
		WeaponWeight->GetTransform()->SetLocalPosition({ 384, -220 });
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

	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	CursorTimer += _DeltaTime * 10;
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
			SetItemInfo();
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetItemInfo();
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
			SetItemInfo();
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetItemInfo();
		return;
	}

}

void ItemUI::ItemSelect()
{
	Cursor->GetTransform()->SetLocalPosition(CursorPos);
	IsItemSelect = true;

	ItemUseWindow->GetTransform()->SetLocalPosition(float4(80.0f, 164.0f) + float4::Down * static_cast<float>(std::min<size_t>(CurrentCursor,2)) * 64);

	StartUseSelectPos = float4(80.0f, 198.0f) + float4::Down * static_cast<float>(std::min<size_t>(CurrentCursor, 2)) * 64;
	StartUseCursorPos = float4(2, 198.0f) + float4::Down * static_cast<float>(std::min<size_t>(CurrentCursor, 2)) * 64;

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
			ItemUseText1->SetText("장비");
			ItemUseText2->SetText("버리기");
		}
		else
		{
			UseFunctions.push_back(std::bind(&ItemUI::ItemUseCancel, this));
			UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
			Window->Text += "취소\n버리기";
			ItemUseText1->SetText("취소");
			ItemUseText2->SetText("버리기");
		}
		break;
	}
	case ItemType::Stave:
		UseFunctions.push_back(std::bind(&ItemUI::ItemUseCancel, this));
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "취소\n버리기";
		ItemUseText1->SetText("취소");
		ItemUseText2->SetText("버리기");
		break;
	case ItemType::Potion:
		UseFunctions.push_back(std::bind(&ItemUI::Use, this));
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "사용\n버리기";
		ItemUseText1->SetText("사용");
		ItemUseText2->SetText("버리기");
		break;
	case ItemType::Key:
		UseFunctions.push_back(std::bind(&ItemUI::ItemUseCancel, this));
		UseFunctions.push_back(std::bind(&ItemUI::Drop, this));
		Window->Text += "취소\n버리기";
		ItemUseText1->SetText("취소");
		ItemUseText2->SetText("버리기");
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
		UseButtons[i]->GetTransform()->SetLocalPosition({ 80, 192.0f - (64 * (i + std::min<size_t>(CurrentCursor,2)))});
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
		ItemUseCancel();
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

void ItemUI::SetItemInfo()
{
	ItemIter = SelectUnit->GetUnitData().GetItems().begin();
	std::advance(ItemIter, CurrentCursor);

	if ((*ItemIter)->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(*ItemIter);
		InfoRender->SetFrame(5);
		ItemInfoText->SetText("");
		WeaponDamage->On();
		WeaponHit->On();
		WeaponCritical->On();
		WeaponWeight->On();

		WeaponDamage->SetValue(_Weapon->GetDamage());
		WeaponHit->SetValue(_Weapon->GetHit());
		WeaponCritical->SetValue(_Weapon->GetCritical());
		WeaponWeight->SetValue(_Weapon->GetWeight());
		return;
	}
	WeaponDamage->Off();
	WeaponHit->Off();
	WeaponCritical->Off();
	WeaponWeight->Off();
	InfoRender->SetFrame(2);

	std::string InfoText = "";
	switch ((*ItemIter)->GetItemCode())
	{
	case ItemCode::Heal:
		InfoText = "아군의 HP를 회복합니다";
		break;
	case ItemCode::Rescue:
		break;
	case ItemCode::DoorKey:
		break;
	case ItemCode::ChestKey:
		break;
	case ItemCode::Vulnerary:
		InfoText = "HP를 10 회복합니다";
		break;
	case ItemCode::Elixir:
		InfoText = "HP를 30 회복합니다";
		break;
	case ItemCode::Ring1:
		break;
	case ItemCode::Ring2:
		break;
	case ItemCode::Torch:
		break;
	case ItemCode::GoldCard:
		break;
	case ItemCode::MasterSeal:
		InfoText = "상위 클래스로 전직합니다";
		break;
	default:
		break;
	}

	ItemInfoText->SetText(InfoText);

}

void ItemUI::ItemUseCancel()
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
}
