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
	ImGui::Text(GameEngineString::AnsiToUTF8("스테이지 선택").c_str());

	if (ImGui::Button(GameEngineString::AnsiToUTF8("테스트 스테이지").c_str()))
	{
		Funcions("TestStage");
	}

	for (int i = 0; i <= 10; i++)
	{
		std::string Str = "Stage " + std::to_string(i);
		if (ImGui::Button(Str.c_str()))
		{
			Funcions("Stage"+std::to_string(i));
		}
	}
}

