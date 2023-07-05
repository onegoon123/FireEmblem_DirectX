#pragma once
#include <functional>
#include <Windows.h>
#include "GameEngineThread.h"

enum ThreadWorkType
{
	// 서버일때는 서버에서 날아온 바이트크기가 날아오기 때문에
	// 무조건
	UserWork = -1,
	Destroy = -2
};

// IOCP를 사용한 쓰레드 
class GameEngineThreadJobQueue
{
private:
	class Job
	{
	public:
		std::function<void(GameEngineThread*)> Function;
	};

public:
	// constrcuter destructer
	GameEngineThreadJobQueue();
	~GameEngineThreadJobQueue();

	// delete Function
	GameEngineThreadJobQueue(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue(GameEngineThreadJobQueue&& _Other) noexcept = delete;
	GameEngineThreadJobQueue& operator=(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue& operator=(GameEngineThreadJobQueue&& _Other) noexcept = delete;

	void Work(std::function<void(GameEngineThread*)> _Work);

	void Initialize(const std::string& _ThreadName, int _ThreadCount = 0);

protected:


private:

	HANDLE IOCPHandle = nullptr;
	int ThreadCount;

	static std::atomic_int RunningThreadCount;
	std::atomic_bool IsRun = true;
	std::vector<std::shared_ptr<GameEngineThread>> AllThread;

	static void ThreadPoolFunction(GameEngineThreadJobQueue* _ThreadPool, GameEngineThread* _Thread, HANDLE _IOCPHandle);
};

