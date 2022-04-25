#pragma once

// Ό³Έν :
class FishingRod
{
public:
	// constrcuter destructer
	FishingRod();
	~FishingRod();

	// delete Function
	FishingRod(const FishingRod& _Other) = delete;
	FishingRod(FishingRod&& _Other) noexcept = delete;
	FishingRod& operator=(const FishingRod& _Other) = delete;
	FishingRod& operator=(FishingRod&& _Other) noexcept = delete;

protected:

private:

};

