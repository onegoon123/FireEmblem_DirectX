#pragma once
#include <list>
#include <GameEngineBase/GameEngineMath.h>

// 설명 : 특정한 문체의 크기 회전 이동에 관련된 기하속성을 관리해준다.
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;
		TransformUpdate();
	}

	void AddLocalScale(const float4& _Value)
	{
		LocalScale += _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const float4& _Value)
	{
		LocalRotation += _Value;
		TransformUpdate();
	}

	void AddLocalPosition(const float4& _Value)
	{
		LocalPosition += _Value;
		TransformUpdate();
	}

	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

protected:

private:
	void TransformUpdate();

	
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;

	float4x4 LocalWorldMatrix;
};

