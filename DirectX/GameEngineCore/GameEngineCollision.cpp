#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}


void GameEngineCollision::Start()
{
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			return _OtherCol;
		}
	}

	return nullptr;
}

void GameEngineCollision::SetOrder(int _Order)
{
	std::shared_ptr<GameEngineCollision> ConThis = DynamicThis<GameEngineCollision>();

	// 기존의 그룹에서 나를 지우고
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[GetOrder()];
	Group.remove(ConThis);

	GameEngineObjectBase::SetOrder(_Order);

	// 새로운 그룹에 나를 추가한다.
	GetLevel()->PushCollision(ConThis);
}

bool GameEngineCollision::CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
{
	_Col.clear();

	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			_Col.push_back(_OtherCol);
		}
	}

	return _Col.size() != 0;

}