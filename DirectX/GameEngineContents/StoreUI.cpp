#include "PrecompileHeader.h"
#include "StoreUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleUnit.h"
#include "TextRenderer.h"
#include "ContentsEnum.h"
#include "NumberActor.h"
#include "UICursor.h"
#include "BattleLevel.h"
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
	FSM.ChangeState("Start1");
	MoneyText->SetValue(Money, true);
}

void StoreUI::Start()
{
	BattleLevel* Level = dynamic_cast<BattleLevel*>(GetLevel());
	EndFunction = std::bind(&BattleLevel::UnitCommand_StoreEnd, Level);

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
	MoneyText->GetTransform()->SetLocalPosition({378, 98 });

	Cursor = GetLevel()->CreateActor<UICursor>(RenderOrder::UIText);
	Cursor->GetTransform()->SetParent(GetTransform());
	Cursor->Off();

	Icons.resize(5);
	ItemNameTexts.resize(5);
	ItemUses.resize(5);
	ItemPrices.resize(5);
	StoreItems.resize(5);
	for (int i = 0; i < 5; i++)
	{
		StoreItems[i] = Item::CreateItem(ItemList[i]);
		Icons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Icons[i]->SetSprite("Items.png", StoreItems[i]->GetItemCodeToInt() - 1);

		Icons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		Icons[i]->GetTransform()->SetLocalPosition({ -232, 8.0f - (64.0f * i) });

		//Icons[i]->Off();

		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -182, 32.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		ItemNameTexts[i]->SetText(StoreItems[i]->GetName());
		//ItemNameTexts[i]->Off();

		ItemUses[i] = GetLevel()->CreateActor<NumberActor>();
		ItemUses[i]->GetTransform()->SetParent(GetTransform());
		ItemUses[i]->GetTransform()->SetLocalPosition({ 84, 8.0f - (64 * i) });
		ItemUses[i]->SetValue(StoreItems[i]->GetMaxUses());

		ItemPrices[i] = GetLevel()->CreateActor<NumberActor>();
		ItemPrices[i]->GetTransform()->SetParent(GetTransform());
		ItemPrices[i]->GetTransform()->SetLocalPosition({ 284, 8.0f - (64 * i) });
		ItemPrices[i]->SetValue(Price[i], true);
	}


	FSM.CreateState({ .Name = "Start1",
		.Start = [this]
		{
			Dialogue->SetTextAnim(L"여기는 무기점이다");
			Dialogue2->SetText(" ");
			Cursor->Off();
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
			Cursor->GetTransform()->SetLocalPosition({ -172, 150 });
			CursorPos = { -172, 150 };
			IsSell = false;
		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));
			if (GameEngineInput::IsDown("Left") || GameEngineInput::IsDown("Right"))
			{
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
				EndFunction();
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

			for (int i = 0; i < 5; i++)
			{
				Icons[i]->SetSprite("Items.png", StoreItems[i]->GetItemCodeToInt() - 1);
				ItemNameTexts[i]->SetText(StoreItems[i]->GetName());
				ItemUses[i]->SetValue(StoreItems[i]->GetMaxUses());
				ItemPrices[i]->SetValue(Price[i], true);
			}
		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

			if (GameEngineInput::IsDown("Up"))
			{
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
				if (Money < Price[CurrentCursor])
				{
					Money += 300;	//임시용
					MoneyText->SetValue(Money, true);
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
				Dialogue->SetTextAnim(L"다른 것도 살 건가?");
				return;
			}
			if (GameEngineInput::IsDown("ButtonB"))
			{
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
			int i = 0;
			for (std::shared_ptr<Item> _Item : PlayerItems)
			{
				Icons[i]->SetSprite("Items.png", _Item->GetItemCodeToInt() - 1);
				ItemNameTexts[i]->SetText(_Item->GetName());
				ItemUses[i]->SetValue(_Item->GetMaxUses());
				ItemPrices[i]->SetValue(Item::GetItemPrice(_Item->GetItemCode()), true);
				i++;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			Cursor->GetTransform()->SetLocalPosition(float4::LerpClamp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

			if (GameEngineInput::IsDown("Up"))
			{
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
				if (Money < Price[CurrentCursor])
				{
					Money += 300;	//임시용
					MoneyText->SetValue(Money, true);
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
				Dialogue->SetTextAnim(L"다른 것도 살 건가?");
				return;
			}
			if (GameEngineInput::IsDown("ButtonB"))
			{
				FSM.ChangeState("BuyOrSell");
				return;
			}
		},
		.End = [this]
		{
		},
		});
	FSM.ChangeState("Start1");
}

void StoreUI::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
}

