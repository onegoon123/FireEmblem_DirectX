#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"


enum class SAVEMODE
{
	Text,
	Bin,
};

// Ό³Έν :
class GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineFile();
	~GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);

	// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	std::string GetFullPath()
	{
		return Path.Path.string();
	}

	void SaveBin(const GameEngineSerializer& _Data);
	void SaveText(const std::string_view& _View);

	void LoadBin(GameEngineSerializer& _Data);

protected:

private:
	GameEnginePath Path;
};

