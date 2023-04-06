#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	LocalScaleMatrix.Scale(LocalScale);

	LocalRotation.w = 0.0f;
	LocalQuaternion = LocalRotation.EulerDegToQuaternion();
	LocalRotationMatrix = LocalQuaternion.QuaternionToRotationMatrix();
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;

	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}
	else
	{
		WorldMatrix = LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	Parent = _Parent;

	// 내가 이미 다른 부모가 있다면

	Parent->Child.push_back(this);
}


