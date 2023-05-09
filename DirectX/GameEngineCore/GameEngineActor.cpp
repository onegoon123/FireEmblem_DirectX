#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	ComponentsList.push_back(_Component);
}


void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Update(_DeltaTime);
	}
}

void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		if (false == Component->IsUpdate())
		{
			continue;
		}

		Component->Render(_DeltaTime);
	}
}

void GameEngineActor::AccLiveTime(float _LiveTime)
{
	GameEngineUpdateObject::AccLiveTime(_LiveTime);

	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->AccLiveTime(_LiveTime);
	}
}

void GameEngineActor::ComponentsRelease()
{
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComStartIter = ComponentsList.begin();
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComEndIter = ComponentsList.end();

	for (; ComStartIter != ComEndIter; )
	{
		std::shared_ptr<class GameEngineComponent>& ComPtr = *ComStartIter;

		if (false == ComPtr->IsDeath())
		{
			++ComStartIter;
			continue;
		}

		ComStartIter = ComponentsList.erase(ComStartIter);
	}

}