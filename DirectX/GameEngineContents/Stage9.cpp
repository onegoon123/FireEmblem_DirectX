#include "PrecompileHeader.h"
#include "Stage9.h"

Stage9::Stage9()
{
	// юс╫ц
	StartPos.push_back({ 3, 3 });
	StartPos.push_back({ 2, 4 });
	StartPos.push_back({ 3, 5 });
	StartPos.push_back({ 2, 2 });
	StartPos.push_back({ 1, 3 });
	StartPos.push_back({ 3, 1 });
	StartPos.push_back({ 4, 1 });
	StartPos.push_back({ 5, 1 });
	StartPos.push_back({ 7, 1 });
}

Stage9::~Stage9()
{
}

void Stage9::StageSetting()
{
	SetStage(9);
}

