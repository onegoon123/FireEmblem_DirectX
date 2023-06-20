#pragma once
#include <GameEngineCore/GameEngineComponent.h>	
#include "ContentsEnum.h"
// Ό³Έν :
class TimeCommand : public GameEngineComponent
{
public:
	// constrcuter destructer
	TimeCommand();
	~TimeCommand();

	// delete Function
	TimeCommand(const TimeCommand& _Other) = delete;
	TimeCommand(TimeCommand&& _Other) noexcept = delete;
	TimeCommand& operator=(const TimeCommand& _Other) = delete;
	TimeCommand& operator=(TimeCommand&& _Other) noexcept = delete;

	std::shared_ptr<class TextRenderer> GetTextRender()
	{
		return Text;
	}
	void Select(Faction _Value);
	void Select();
	void SelectEnemy();
	void Cancel();

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineUIRenderer> Render = nullptr;
	std::shared_ptr<class TextRenderer> Text = nullptr;

};

