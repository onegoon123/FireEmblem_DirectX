#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "Int2.h"

class DialogueBox : public GameEngineComponent
{
public:
	// constrcuter destructer
	DialogueBox();
	~DialogueBox();

	// delete Function
	DialogueBox(const DialogueBox& _Other) = delete;
	DialogueBox(DialogueBox&& _Other) noexcept = delete;
	DialogueBox& operator=(const DialogueBox& _Other) = delete;
	DialogueBox& operator=(DialogueBox&& _Other) noexcept = delete;

	void SetSize(int2 _Size);
	void SetOpacity(float _Value);
	std::shared_ptr<class TextRenderer> GetTextRender()
	{
		return TextRender;
	}

protected:
	void Start() override;

private:
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> DialogueBoxRenders;
	std::shared_ptr<class TextRenderer> TextRender = nullptr;
};

