#include "PrecompileHeader.h"
#include "StageSelectWindow.h"

StageSelectWindow::StageSelectWindow() 
{
}

StageSelectWindow::~StageSelectWindow() 
{
}

void StageSelectWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::Button("Stage 1"))
	{
		Funcions[0]();
	}
	if (ImGui::Button("Stage 2"))
	{

	}
	if (ImGui::Button("Stage 3"))
	{

	}
	if (ImGui::Button("Stage 4"))
	{

	}
	if (ImGui::Button("Stage 5"))
	{

	}
	if (ImGui::Button("Stage 6"))
	{

	}
	if (ImGui::Button("Stage 7"))
	{

	}
	if (ImGui::Button("Stage 8"))
	{

	}
	if (ImGui::Button("Stage 9"))
	{

	}
	if (ImGui::Button("Stage 10"))
	{

	}
}

