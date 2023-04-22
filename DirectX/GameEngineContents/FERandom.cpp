#include "PrecompileHeader.h"
#include "FERandom.h"

int FERandom::RandomCount = 0;

FERandom::FERandom()
{
	GameEngineRandom::MainRandom.SetSeed(Seed);
}

FERandom::~FERandom()
{
}
