#include "PrecompileHeader.h"
#include "DebugWindow.h"

DebugWindow::DebugWindow() 
{
}

DebugWindow::~DebugWindow() 
{
}

void DebugWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	ImGui::Text("123455");
}

