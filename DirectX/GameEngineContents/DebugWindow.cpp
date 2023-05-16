#include "PrecompileHeader.h"
#include "DebugWindow.h"
#include <GameEngineBase/GameEngineString.h>
DebugWindow::DebugWindow() 
{
}

DebugWindow::~DebugWindow() 
{
}

void DebugWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (Text == "") { return; }
	ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
}

