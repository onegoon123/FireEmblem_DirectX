#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"
#include <list>
#include <map>

// Ό³Έν :
class GameEngineRenderer;
class GameEngineRenderTarget;
class GameEngineCamera : public GameEngineActor
{
	friend GameEngineLevel;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	inline float4x4 GetView()
	{
		return View;
	}

	inline float4x4 GetProjection()
	{
		return Projection;
	}

	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}

	void Setting();

	void SetProjectionType(CameraType _Type)
	{
		ProjectionType = _Type;
	}

	inline bool IsFreeCamera()
	{
		return FreeCamera;
	}

	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void CameraTransformUpdate();

	std::shared_ptr<GameEngineRenderTarget> GetCamTarget()
	{
		return CamTarget;
	}

	bool IsView(const TransformData& _TransData);


protected:
	void Start() override;

private:
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;

	DirectX::BoundingOrientedBox Box;

	bool FreeCamera = false;

	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;

	TransformData OldData;

	CameraType ProjectionType = CameraType::None;

	D3D11_VIEWPORT ViewPortData;

	float Width = 0.0f;
	float Height = 0.0f;

	float FOV = 60.0f;
	float Near = 0.1f;
	float Far = 10000.0f;

	void PushRenderer(std::shared_ptr<GameEngineRenderer> _Render);

	void Release();

	std::shared_ptr<GameEngineRenderTarget> CamTarget;
};

