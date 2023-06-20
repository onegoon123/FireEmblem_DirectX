#include "PrecompileHeader.h"
#include "TimeCommand.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "TextRenderer.h"
#include "ContentsEnum.h"
TimeCommand::TimeCommand() 
{
}

TimeCommand::~TimeCommand() 
{
}

void TimeCommand::Select(Faction _Value)
{
	switch (_Value)
	{
	case Faction::None:
		break;
	case Faction::Player:
		Render->SetFrame(1);
		break;
	case Faction::Enemy:
		Render->SetFrame(2);
		break;
	default:
		break;
	}
}

void TimeCommand::Select()
{
	Render->SetFrame(1);
}

void TimeCommand::SelectEnemy()
{
	Render->SetFrame(2);
}

void TimeCommand::Cancel()
{
	Render->SetFrame(0);
}

void TimeCommand::Start()
{
	if (nullptr == GameEngineSprite::Find("TimeCommand.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("TimeCommand.png").GetFullPath(), 1, 3);
	}

	Render = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Render->GetTransform()->SetParent(GetTransform());
	Render->GetTransform()->SetLocalScale({ 400, 80 });
	Render->GetTransform()->SetLocalPosition({ 200, -40 });
	Render->SetSprite("TimeCommand.png", 0);
	Render->ColorOptionValue.MulColor.a = 0.5f;

	Text = GetActor()->CreateComponent<TextRenderer>(RenderOrder::UIText);
	Text->GetTransform()->SetParent(GetTransform());
	Text->GetTransform()->SetLocalPosition({ 20, -20 });

}

