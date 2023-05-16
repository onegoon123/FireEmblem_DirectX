#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"

enum class Diraction
{
	None,
	Up,
	Down,
	Left,
	Right
};

// Ό³Έν :
class SpriteRenderer;
class ArrowRender : public GameEngineActor
{
public:
	// constrcuter destructer
	ArrowRender();
	~ArrowRender();

	void Create(int2 _Scale);
	void Clear();
	void SetArrow(std::vector<int2>& _Value);

	// delete Function
	ArrowRender(const ArrowRender& _Other) = delete;
	ArrowRender(ArrowRender&& _Other) noexcept = delete;
	ArrowRender& operator=(const ArrowRender& _Other) = delete;
	ArrowRender& operator=(ArrowRender&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	std::vector <std::vector<std::shared_ptr<SpriteRenderer>>> Renders;

	Diraction DiractionCheck(int2 _BeforePos, int2 _CurPos);
};

