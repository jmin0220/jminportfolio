#pragma once

// Ό³Έν :
class Fishes
{
public:
	// constrcuter destructer
	Fishes();
	~Fishes();

	// delete Function
	Fishes(const Fishes& _Other) = delete;
	Fishes(Fishes&& _Other) noexcept = delete;
	Fishes& operator=(const Fishes& _Other) = delete;
	Fishes& operator=(Fishes&& _Other) noexcept = delete;

protected:

private:

};

