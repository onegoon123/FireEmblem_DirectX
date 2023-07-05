#include "PrecompileHeader.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

std::atomic_bool GameEngineThread::End = false;

GameEngineThread::GameEngineThread()
{
}

GameEngineThread::GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	Start(_ThreadName, _CallBack);
}

GameEngineThread::~GameEngineThread()
{
	Join();
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	CallBack = _CallBack;
	Thread = std::thread(ThreadBaseFunction, this, _ThreadName);

}

void GameEngineThread::ThreadBaseFunction(GameEngineThread* Thread, std::string Name)
{
	std::wstring WName = GameEngineString::AnsiToUniCode(Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	Thread->CallBack(Thread);
}

void GameEngineThread::Join()
{
	if (nullptr != CallBack)
	{
		// Sleep(0);
		Thread.join();
		CallBack = nullptr;
	}
}