#pragma once
#include "GameEngineResource.h"

// Ό³Έν :
class GameEngineSampler : public GameEngineResource<GameEngineSampler>
{
	friend class GameEngineSamplerSetter;

public:
	// constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete Function
	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineSampler> Create(const std::string_view& _Name, const D3D11_SAMPLER_DESC& Desc)
	{
		std::shared_ptr<GameEngineSampler> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(Desc);
		return NewTexture;
	}


protected:

private:
	ID3D11SamplerState* State;
	D3D11_SAMPLER_DESC Desc;

	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

