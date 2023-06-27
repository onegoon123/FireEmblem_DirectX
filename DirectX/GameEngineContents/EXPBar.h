#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class EXPBar : public GameEngineActor
{
public:
	// constrcuter destructer
	EXPBar();
	~EXPBar();

	// delete Function
	EXPBar(const EXPBar& _Other) = delete;
	EXPBar(EXPBar&& _Other) noexcept = delete;
	EXPBar& operator=(const EXPBar& _Other) = delete;
	EXPBar& operator=(EXPBar&& _Other) noexcept = delete;

	void SetEXP(int _EXP);
	void AddEXP(int _EXP, std::function<void()> _EndEvent = nullptr);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class GameEngineUIRenderer> Background = nullptr;
	std::shared_ptr<GameEngineUIRenderer> BarLeft = nullptr;
	std::shared_ptr<GameEngineUIRenderer> BarCenter = nullptr;
	std::shared_ptr<GameEngineUIRenderer> BarRight = nullptr;
	std::shared_ptr<class NumberActor> Number = nullptr;
	std::function<void()> EndEvent = nullptr;
	GameEngineSoundPlayer SoundPlayer;

	int CurEXP = 0;
	int PlusEXP = 0; 

	int BeforeEXP = 0;
	int TargetEXP = 0;
	float Timer = 0;
	float Time = 0.005f;
	bool IsLerp = false;
	bool IsLevelUp = false;

	void SetEXPBar(int _Value);
};

