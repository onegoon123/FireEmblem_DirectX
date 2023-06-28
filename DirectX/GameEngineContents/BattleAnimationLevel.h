#pragma once
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "UnitCommand.h"
// Ό³Έν :
class BattleAnimationLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BattleAnimationLevel();
	~BattleAnimationLevel();

	// delete Function
	BattleAnimationLevel(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel(BattleAnimationLevel&& _Other) noexcept = delete;
	BattleAnimationLevel& operator=(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel& operator=(BattleAnimationLevel&& _Other) noexcept = delete;

	static void SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data, const std::string_view& _Level);
	static void SetDance(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::string_view& _Level);
	static void SetClassChange(std::shared_ptr<BattleUnit> _BattleUnit, BattleClass _ClassValue, const std::string_view& _Level);

	void HitEvent();
	void HealEvent();
	void TurnEnd();

	void BattleEnd();

	GameEngineTimeEvent TimeEvent;
	static GameEngineSoundPlayer BgmPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	static std::string_view ReturnLevelStr;
	static std::shared_ptr<class BattleUnit> SubjectUnit;
	static std::shared_ptr<BattleUnit> TargetUnit;
	static std::list<AttackCommand> BattleData;
	static std::list<AttackCommand>::iterator BattleIter;

	std::shared_ptr<class SpriteRenderer> BackgroundRender;
	std::shared_ptr<SpriteRenderer> TerrainLeft;
	std::shared_ptr<SpriteRenderer> TerrainRight;
	std::shared_ptr<class BattleAnimationUnit> SubjectAnimation;
	std::shared_ptr<BattleAnimationUnit> TargetAnimation;
	std::shared_ptr<BattleAnimationUnit> LeftUnit;
	std::shared_ptr<BattleAnimationUnit> RightUnit;
	std::shared_ptr<class BattleAnimationUI> UI;

	std::shared_ptr<class FadeEffect> FEffect;

	GameEngineTransform* CameraTransform = nullptr;

	bool IsTurnEnd = false;
	bool IsFadeOut = false;
	static bool IsClassChange;
	static BattleClass ChangeClass;

	void PlayAttack();
	void End();
	void FadeOut(float _Time);
	void ClassChangeEvent();

	void CameraShake(float _Time);
	void ShakeUpdate(float _DeltaTime);
	const float4 ShakeAmount = {16, 16};
	bool IsShake = false;
	float ShakeTimer = 0;
	const float ShakeDelay = 0.03f;
	float ShakeDelayTimer = 0;

	std::string_view GetTerrainTexture(Terrain _Value);
	std::string_view GetBackgroundTexture(Terrain _Value);
};

