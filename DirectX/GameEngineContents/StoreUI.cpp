#include "PrecompileHeader.h"
#include "StoreUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleUnit.h"
#include "TextRenderer.h"
#include "ContentsEnum.h"
#include "NumberActor.h"
StoreUI::StoreUI() 
{
}

StoreUI::~StoreUI() 
{
}

void StoreUI::On(std::shared_ptr<BattleUnit> _Unit)
{
	GameEngineActor::On();
	Dialogue->SetTextAnim(L"여기는 무기점이다");
}

void StoreUI::Start()
{
	Background = CreateComponent<GameEngineUIRenderer>(RenderOrder::UIBackground);
	Background->SetTexture("StoreUI.png");
	Background->GetTransform()->SetLocalScale({ 960, 640 });

	Dialogue = CreateComponent<TextRenderer>(RenderOrder::UIText);
	Dialogue->GetTransform()->SetLocalPosition({ -200, 256 });
	Dialogue->Setting("Silhoua14", 60, float4::White, float4::Null, FontAligned::Left);

	Icons.resize(5);
	ItemNameTexts.resize(5);
	ItemUses.resize(5);
	ItemPrices.resize(5);
	for (int i = 0; i < 5; i++)
	{
		Icons[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Icons[i]->SetSprite("Items.png", 0);

		Icons[i]->GetTransform()->SetWorldScale({ 64, 64 });
		Icons[i]->GetTransform()->SetLocalPosition({ -232, 8.0f - (64.0f * i) });

		//Icons[i]->Off();

		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -182, 32.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		ItemNameTexts[i]->SetText("철의 검");
		//ItemNameTexts[i]->Off();

		ItemUses[i] = GetLevel()->CreateActor<NumberActor>();
		ItemUses[i]->GetTransform()->SetParent(GetTransform());
		ItemUses[i]->GetTransform()->SetLocalPosition({ 84, 8.0f - (64 * i) });
		ItemUses[i]->SetValue(45);

		ItemPrices[i] = GetLevel()->CreateActor<NumberActor>();
		ItemPrices[i]->GetTransform()->SetParent(GetTransform());
		ItemPrices[i]->GetTransform()->SetLocalPosition({ 284, 8.0f - (64 * i) });
		ItemPrices[i]->SetValue(999, true);
	}
}

void StoreUI::Update(float _DeltaTime)
{

}

