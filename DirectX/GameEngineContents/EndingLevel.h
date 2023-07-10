#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineFSM.h>
// Ό³Έν :
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
private:
	GameEngineFSM FSM;
	GameEngineSoundPlayer BgmPlayer;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGroundRenderer = nullptr;
	std::shared_ptr<class FadeEffect> Fade = nullptr;
	std::shared_ptr<class TextRenderer> Text = nullptr;
	float Timer = 0;
	void StateInit();
	void CreditsEventInit();
};

