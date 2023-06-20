#include "PrecompileHeader.h"
#include "TimeStoneUI.h"
#include "DialogueBox.h"
#include "TextRenderer.h"
#include "ContentsEnum.h"
TimeStoneUI::TimeStoneUI() 
{
}

TimeStoneUI::~TimeStoneUI() 
{
}

void TimeStoneUI::On()
{
	GameEngineActor::On();
	CommandList = &UnitCommand::GetCommandList();
}

void TimeStoneUI::Start()
{
	CommandBoxs.resize(5);
	for (int i = 0; i < 5; i++)
	{
		CommandBoxs[i] = CreateComponent<DialogueBox>(RenderOrder::UI);
		CommandBoxs[i]->SetSize({ 17, 2 });
		CommandBoxs[i]->GetTransform()->SetLocalPosition({ -432, i * -112.0f + 250.0f });
		CommandBoxs[i]->GetTextRender()->Setting("Silhoua14", 45, float4::White, float4::Black, FontAligned::Left);
		CommandBoxs[i]->GetTextRender()->SetText("Å×½ºÆ®");
		CommandBoxs[i]->SetOpacity(.2f);
	}
}

