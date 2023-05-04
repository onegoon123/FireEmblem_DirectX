#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class DebugWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	DebugWindow();
	~DebugWindow();

	// delete Function
	DebugWindow(const DebugWindow& _Other) = delete;
	DebugWindow(DebugWindow&& _Other) noexcept = delete;
	DebugWindow& operator=(const DebugWindow& _Other) = delete;
	DebugWindow& operator=(DebugWindow&& _Other) noexcept = delete;

	std::function<void()> Test;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};

