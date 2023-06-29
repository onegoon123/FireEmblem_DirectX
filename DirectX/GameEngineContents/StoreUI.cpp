#include "PrecompileHeader.h"
#include "StoreUI.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleUnit.h"
#include "TextRenderer.h"
#include "ContentsEnum.h"
#include "NumberActor.h"
#include "UICursor.h"
#include "BattleLevel.h"
#include "FEData.h"

std::vector<ItemCode> StoreUI::ItemList = { ItemCode::SteelSword, ItemCode::KillingSword, ItemCode::SilverLance, ItemCode::Elixir, ItemCode::MasterSeal };

StoreUI::StoreUI()
{
}

StoreUI::~StoreUI()
{
}

void StoreUI::On(std::shared_ptr<BattleUnit> _Unit)
{
	GameEngineActor::On();
	SelectUnit = _Unit;
	BeforeItems = SelectUnit->GetUnitData().GetItems();
	FSM.ChangeState("Start1");
	Money = FEData::GetMoney();
	BeforeMoney = Money;
	MoneyText->SetValue(Money, true);
	for (int i = 0; i < ItemList.size(); i++)
	{
		Icons[i]->SetSprite("Items.png", StoreItems[i]->GetItemCodeToInt() - 1);
		ItemNameTexts[i]->SetText(StoreItems[i]->GetName());
		ItemUses[i]->SetValue(StoreItems[i]->GetMaxUses());
		Price[i] = Item::GetItemPrice(ItemList[i]);
		ItemPrices[i]->SetValue(Price[i], true);

		Icons[i]->On();
		ItemNameTexts[i]->On();
		ItemUses[i]->On();
		ItemPrices[i]->On();
	}
	for (size_t i = ItemList.size(); i < 5; i++)
	{
		Icons[i]->Off();
		ItemNameTexts[i]->Off();
		ItemUses[i]->Off();
		ItemPrices[i]->Off();
	}
}

void StoreUI::Start()
{
	BattleLevel* Level = dynamic_cast<BattleLevel*>(GetLevel());
	EndFunction = std::bind(&BattleLevel::UnitCommand_StoreEnd, Level, std::placeholders::_1, std::placeholders::_2);

	Background = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	Background->SetTexture("StoreUI.png");
	Background->GetTransform()->SetLocalScale({ 960, 640 });

	Dialogue = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Dialogue->GetTransform()->SetLocalPosition({ -200, 256 });
	Dialogue->Setting("Silhoua14", 60, float4::White, float4::Null, FontAligned::Left);

	Dialogue2 = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Dialogue2->GetTransform()->SetLocalPosition({ -200, 184 });
	Dialogue2->Setting("Silhoua14", 60, float4::White, float4::Null, FontAligned::Left);

	MoneyText = GetLevel()->CreateActor<NumberActor>();
	MoneyText->GetTransform()->SetParent(GetTransform());
	MoneyText->GetTransform()->SetLocalPosition({ 378, 98 });

	Cursor = GetLevel()->CreateActor<UICursor>(RenderOrder::UIText);
	Cursor->GetTransform()->SetParent(GetTransform());
	Cursor->Off();

	Icons.resize(5);
	ItemNameTexts.resize(5);
	ItemUses.resize(5);
	ItemPrices.resize(5);
	StoreItems.resize(5);
	Price.resize(5);
	for (int i = 0; i < 5; i++)
	{
		Icons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Icons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		Icons[i]->GetTransform()->SetLocalPosition({ -232, 8.0f - (64.0f * i) });

		//Icons[i]->Off();

		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -182, 32.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		//ItemNameTexts[i]->Off();

		ItemUses[i] = GetLevel()->CreateActor<NumberActor>();
		ItemUses[i]->GetTransform()->SetParent(GetTransform());
		ItemUses[i]->GetTransform()->SetLocalPosition({ 84, 8.0f - (64 * i) });
		ItemPrices[i] = GetLevel()->CreateActor<NumberActor>();
		ItemPrices[i]->GetTransform()->SetParent(GetTransform());
		ItemPrices[i]->GetTransform()->SetLocalPosition({ 284, 8.0f - (64 * i) });
		if (i < ItemList.size())
		{
			StoreItems[i] = Item::CreateItem(ItemList[i]);
			Price[i] = Item::GetItemPrice(ItemList[i]);
			Icons[i]->SetSprite("Items.png", StoreItems[i]->GetItemCodeToInt() - 1);
			ItemNameTexts[i]->SetText(StoreItems[i]->GetName());
			ItemUses[i]->SetValue(StoreItems[i]->GetMaxUses());
			ItemPrices[i]->SetValue(Price[i], true);
		}
	}

	FSM.CreateState({ .Name = "Off",
		.Start = [this]
		{
		},
		.Update = [this](float _DeltaTime)
		{
		},
		.End = [this]
		{
		},
		});


	FSM.CreateState({ .Name = "Start1",
		.Start = [this]
		{
			Dialogue->SetTextAnim(L"여기는 무기점이다");
			Dialogue2->SetText(" ");
			Cursor->Off();
			IsSell = false;
		},
		.Update = [this](float _DeltaTime)
		{
			if (Dialogue->IsAnimEnd() && GameEngineInput::IsDown("ButtonA"))
			{
				FSM.ChangeState("Start2");
			}
		},
		.End = [this]
		{
		},
		});

	FSM.CreateState({ .Name = "Start2",
		.Start = [this]
		{
			Dialogue->SetTextAnim(L"천천히 둘러보게");
		},
		.Update = [this](float _DeltaTime)
		{
			if (Dialogue->IsAnimEnd())
			{
				FSM.ChangeState("BuyOrSell");
			}
		},
		.End = [this]
		{
		},
		});

	FSM.CreateState({ .Name = "BuyOrSell",
		.Start = [this]
		{
			Dialogue->SetText(L"천천히 둘러보게");
			Dialogue2->SetText("  구입    판매");
			Cursor->On();
			if (true == IsSell)
			{
				Cursor->GetTransform()->SetLocalPosition({ 4, 150 });
				CursorPos = { 4, 150 };
			}
			else
			{
				Cursor->GetTransform()->SetLocalPosition({ -172, 150 });
				CursorPos = { -172, 150 };
			}
		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));
			if (GameEngineInput::IsDown("Left") || GameEngineInput::IsDown("Right"))
			{
				GameEngineSound::Play("CommandMove.wav");
				IsSell = !IsSell;
				if (true == IsSell)
				{
					CursorPos = { 4, 150 };
				}
				else
				{
					CursorPos = { -172, 150 };
				}
			}
			if (GameEngineInput::IsDown("ButtonA"))
			{
				GameEngineSound::Play("CommandSelect.wav");
				if (true == IsSell)
				{
					FSM.ChangeState("Sell");
				}
				else
				{
					FSM.ChangeState("Buy");
				}
			}
			if (GameEngineInput::IsDown("ButtonB"))
			{
				GameEngineSound::Play("Cancel.wav");
				EndFunction(BeforeItems, BeforeMoney);
			}
		},
		.End = [this]
		{
		},
		});

	FSM.CreateState({ .Name = "Buy",
		.Start = [this]
		{
			Cursor->GetTransform()->SetLocalPosition({ -284, 0 });
			CursorPos = StartCursorPos;
			CurrentCursor = 0;
			Dialogue->SetTextAnim(L"무엇을 사겠나?");
			Dialogue2->SetText(" ");
			ItemSize = static_cast<int>(StoreItems.size());
			for (int i = 0; i < ItemList.size(); i++)
			{
				Icons[i]->SetSprite("Items.png", StoreItems[i]->GetItemCodeToInt() - 1);
				ItemNameTexts[i]->SetText(StoreItems[i]->GetName());
				ItemUses[i]->SetValue(StoreItems[i]->GetMaxUses());
				Price[i] = Item::GetItemPrice(ItemList[i]);
				ItemPrices[i]->SetValue(Price[i], true);

				Icons[i]->On();
				ItemNameTexts[i]->On();
				ItemUses[i]->On();
				ItemPrices[i]->On();
			}
			for (size_t i = ItemList.size(); i < 5; i++)
			{
				Icons[i]->Off();
				ItemNameTexts[i]->Off();
				ItemUses[i]->Off();
				ItemPrices[i]->Off();
			}
		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

			if (GameEngineInput::IsDown("Up"))
			{
				GameEngineSound::Play("CommandMove.wav");
				if (CurrentCursor == 0)
				{
					if (false == GameEngineInput::IsDown("Up")) { return; }
					CurrentCursor = ItemSize - 1;
					CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
					return;
				}
				CurrentCursor--;
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
				return;
			}

			if (GameEngineInput::IsDown("Down"))
			{
				GameEngineSound::Play("CommandMove.wav");
				if (CurrentCursor == ItemSize - 1)
				{
					if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
					CurrentCursor = 0;
					CursorPos = StartCursorPos;
					return;
				}
				CurrentCursor++;
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
				return;
			}

			if (GameEngineInput::IsDown("ButtonA"))
			{
				GameEngineSound::Play("CommandSelect.wav");
				if (Money < Price[CurrentCursor])
				{
					Dialogue->SetTextAnim(L"돈이 부족하네");
					return;
				}
				if (5 == SelectUnit->GetUnitData().GetItems().size())
				{
					Dialogue->SetTextAnim(L"가방이 가득찼다네");
					return;
				}
				SelectUnit->GetUnitData().NewItem(ItemList[CurrentCursor]);
				Money -= Price[CurrentCursor];
				MoneyText->SetValue(Money, true);
				GameEngineSound::Play("Buy.wav");
				Dialogue->SetTextAnim(L"다른 것도 살 건가?");
				return;
			}
			if (GameEngineInput::IsDown("ButtonB"))
			{
				GameEngineSound::Play("Cancel.wav");
				FSM.ChangeState("BuyOrSell");
				return;
			}
		},
		.End = [this]
		{
		},
		});

	FSM.CreateState({ .Name = "Sell",
		.Start = [this]
		{
			Cursor->GetTransform()->SetLocalPosition({ -284, 0 });
			CursorPos = StartCursorPos;
			CurrentCursor = 0;
			Dialogue->SetTextAnim(L"무엇을 팔겠나?");
			Dialogue2->SetText(" ");
			PlayerItems = SelectUnit->GetUnitData().GetItems();
			ItemSize = static_cast<int>(PlayerItems.size());
			int i = 0;
			for (std::shared_ptr<Item> _Item : PlayerItems)
			{
				Icons[i]->SetSprite("Items.png", _Item->GetItemCodeToInt() - 1);
				ItemNameTexts[i]->SetText(_Item->GetName());
				ItemUses[i]->SetValue(_Item->GetUses());
				Price[i] = static_cast<int>(Item::GetItemPrice(_Item->GetItemCode()) * (static_cast<float>(_Item->GetUses()) / _Item->GetMaxUses()));
				ItemPrices[i]->SetValue(Price[i], true);

				Icons[i]->On();
				ItemNameTexts[i]->On();
				ItemUses[i]->On();
				ItemPrices[i]->On();
				i++;
			}
			for (; i < 5; i++)
			{
				Icons[i]->Off();
				ItemNameTexts[i]->Off();
				ItemUses[i]->Off();
				ItemPrices[i]->Off();
			}

		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

			if (GameEngineInput::IsDown("Up"))
			{
				GameEngineSound::Play("CommandMove.wav");
				if (CurrentCursor == 0)
				{
					if (false == GameEngineInput::IsDown("Up")) { return; }
					CurrentCursor = ItemSize - 1;
					CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
					return;
				}
				CurrentCursor--;
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
				return;
			}

			if (GameEngineInput::IsDown("Down"))
			{
				GameEngineSound::Play("CommandMove.wav");
				if (CurrentCursor == ItemSize - 1)
				{
					if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
					CurrentCursor = 0;
					CursorPos = StartCursorPos;
					return;
				}
				CurrentCursor++;
				CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
				return;
			}

			if (GameEngineInput::IsDown("ButtonA"))
			{
				GameEngineSound::Play("CommandSelect.wav");
				if (999 < Money + Price[CurrentCursor])
				{
					Dialogue->SetTextAnim(L"지갑이 가득찼네");
					return;
				}
				Money += Price[CurrentCursor];
				std::list<std::shared_ptr<Item>>::iterator ItemIter = SelectUnit->GetUnitData().GetItems().begin();
				std::advance(ItemIter, CurrentCursor);
				SelectUnit->GetUnitData().DropItem(ItemIter);

				MoneyText->SetValue(Money, true);
				GameEngineSound::Play("Buy.wav");
				Dialogue->SetTextAnim(L"다른 것도 팔 건가?");

				PlayerItems = SelectUnit->GetUnitData().GetItems();
				int i = 0;
				for (std::shared_ptr<Item> _Item : PlayerItems)
				{
					Icons[i]->SetSprite("Items.png", _Item->GetItemCodeToInt() - 1);
					ItemNameTexts[i]->SetText(_Item->GetName());
					ItemUses[i]->SetValue(_Item->GetMaxUses());
					Price[i] = Item::GetItemPrice(_Item->GetItemCode());
					ItemPrices[i]->SetValue(Price[i], true);

					Icons[i]->On();
					ItemNameTexts[i]->On();
					ItemUses[i]->On();
					ItemPrices[i]->On();
					i++;
				}
				for (; i < 5; i++)
				{
					Icons[i]->Off();
					ItemNameTexts[i]->Off();
					ItemUses[i]->Off();
					ItemPrices[i]->Off();
				}

				return;
			}
			if (GameEngineInput::IsDown("ButtonB"))
			{
				GameEngineSound::Play("Cancel.wav");
				FSM.ChangeState("BuyOrSell");
				return;
			}
		},
		.End = [this]
		{
		},
		});
	FSM.ChangeState("Off");
}

void StoreUI::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
}

