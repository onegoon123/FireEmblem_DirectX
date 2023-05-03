#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
// Ό³Έν :

class SpriteRenderer;
class UIWindow : public GameEngineActor
{
public:
	// constrcuter destructer
	UIWindow();
	~UIWindow();

	// delete Function
	UIWindow(const UIWindow& _Other) = delete;
	UIWindow(UIWindow&& _Other) noexcept = delete;
	UIWindow& operator=(const UIWindow& _Other) = delete;
	UIWindow& operator=(UIWindow&& _Other) noexcept = delete;

	void UISet(int2 Scale);
protected:


private:

	std::vector<std::shared_ptr<SpriteRenderer>> CenterTopRender;
	std::vector<std::shared_ptr<SpriteRenderer>> LeftMiddleRender;
	std::vector<std::shared_ptr<SpriteRenderer>> CenterMiddleRender;
	std::vector<std::shared_ptr<SpriteRenderer>> RightMiddleRender;
	std::vector<std::shared_ptr<SpriteRenderer>> CenterBottomRender;
	std::shared_ptr<SpriteRenderer> LeftTopRender = nullptr;
	std::shared_ptr<SpriteRenderer> RightTopRender = nullptr;
	std::shared_ptr<SpriteRenderer> LeftBottomRender = nullptr;
	std::shared_ptr<SpriteRenderer> RightBottomRender = nullptr;

	void Clear();
};

