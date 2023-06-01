#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class NumberActor : public GameEngineActor
{
public:
	// constrcuter destructer
	NumberActor();
	~NumberActor();

	// delete Function
	NumberActor(const NumberActor& _Other) = delete;
	NumberActor(NumberActor&& _Other) noexcept = delete;
	NumberActor& operator=(const NumberActor& _Other) = delete;
	NumberActor& operator=(NumberActor&& _Other) noexcept = delete;
	
	void Setting(int _Value);
	void SetValue(int _Value);
	void SetValueLerp(int _Value);
	void SetBlackFont();
	void SetDamageFont();

	bool GetIsLerp()
	{
		return IsLerp;
	}

	int GetValue()
	{
		return Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> Renders;

	int Value = 0;
	int TargetValue = 0;
	const float Time = 0.05f;
	float Timer = 0;
	bool IsLerp = false;
	bool IsPlus = false;
};

