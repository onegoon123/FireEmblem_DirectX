#pragma once
// Ό³Έν :
class FECore
{
public:
	// constrcuter destructer
	FECore();
	~FECore();

	// delete Function
	FECore(const FECore& _Other) = delete;
	FECore(FECore&& _Other) noexcept = delete;
	FECore& operator=(const FECore& _Other) = delete;
	FECore& operator=(FECore&& _Other) noexcept = delete;

	static void GameStart();
	static void GameEnd();

protected:

private:
};

