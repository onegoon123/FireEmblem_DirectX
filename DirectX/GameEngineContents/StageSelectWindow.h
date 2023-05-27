#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <functional>
// Ό³Έν :
class StageSelectWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	StageSelectWindow();
	~StageSelectWindow();

	// delete Function
	StageSelectWindow(const StageSelectWindow& _Other) = delete;
	StageSelectWindow(StageSelectWindow&& _Other) noexcept = delete;
	StageSelectWindow& operator=(const StageSelectWindow& _Other) = delete;
	StageSelectWindow& operator=(StageSelectWindow&& _Other) noexcept = delete;

	std::function<void(int)> Funcions = nullptr;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};

