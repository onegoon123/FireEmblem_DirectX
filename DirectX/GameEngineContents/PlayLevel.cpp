#include "PlayLevel.h"
#include "BattleActor.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Loading()
{
	std::shared_ptr<BattleActor> NewPlayer = CreateActor<BattleActor>("Player");


}