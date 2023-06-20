#include "PrecompileHeader.h"
#include "DialogueBox.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "TextRenderer.h"
#include "ContentsEnum.h"
DialogueBox::DialogueBox() 
{
}

DialogueBox::~DialogueBox() 
{
}

void DialogueBox::SetSize(int2 _Size)
{
	DialogueBoxRenders[1]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, 0 });
	DialogueBoxRenders[1]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24 });

	DialogueBoxRenders[2]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), 0 });
	DialogueBoxRenders[2]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[3]->GetTransform()->SetLocalPosition({ 0, -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[3]->GetTransform()->SetLocalScale({ 24.0f, 24.0f * _Size.y });

	DialogueBoxRenders[4]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[4]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24.0f * _Size.y });

	DialogueBoxRenders[5]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[5]->GetTransform()->SetLocalScale({ 24.0f, 24.0f * _Size.y });

	DialogueBoxRenders[6]->GetTransform()->SetLocalPosition({ 0, -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[6]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[7]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[7]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24 });

	DialogueBoxRenders[8]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[8]->GetTransform()->SetLocalScale({ 24, 24 });

	TextRender->GetTransform()->SetLocalPosition({24.0f, -24.0f * _Size.y * 0.5f + 12.0f });

}

void DialogueBox::SetOpacity(float _Value)
{
	for (int i = 0; i < 9; i++)
	{
		DialogueBoxRenders[i]->ColorOptionValue.PlusColor = { 0, 0, 0, -_Value };
	}
}

void DialogueBox::Start()
{
	DialogueBoxRenders.resize(9);
	if (nullptr == GameEngineSprite::Find("DialogueBox.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Event");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("DialogueBox.png").GetFullPath(), 3, 3);
	}

	DialogueBoxRenders[0] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[0]->SetSprite("DialogueBox.png", 0);
	DialogueBoxRenders[0]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[0]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[1] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[1]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[1]->SetSprite("DialogueBox.png", 1);

	DialogueBoxRenders[2] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[2]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[2]->SetSprite("DialogueBox.png", 2);

	DialogueBoxRenders[3] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[3]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[3]->SetSprite("DialogueBox.png", 3);

	DialogueBoxRenders[4] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[4]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[4]->SetSprite("DialogueBox.png", 4);

	DialogueBoxRenders[5] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[5]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[5]->SetSprite("DialogueBox.png", 5);

	DialogueBoxRenders[6] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[6]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[6]->SetSprite("DialogueBox.png", 6);

	DialogueBoxRenders[7] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[7]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[7]->SetSprite("DialogueBox.png", 7);

	DialogueBoxRenders[8] = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[8]->GetTransform()->SetParent(GetTransform());
	DialogueBoxRenders[8]->SetSprite("DialogueBox.png", 8);

	TextRender = GetActor()->CreateComponent<TextRenderer>(RenderOrder::UIText);
	TextRender->GetTransform()->SetParent(GetTransform());
}

