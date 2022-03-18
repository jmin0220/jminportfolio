#pragma once

// Ό³Έν :
class Copper
{
public:
	// constrcuter destructer
	Copper();
	~Copper();

	// delete Function
	Copper(const Copper& _Other) = delete;
	Copper(Copper&& _Other) noexcept = delete;
	Copper& operator=(const Copper& _Other) = delete;
	Copper& operator=(Copper&& _Other) noexcept = delete;

protected:

private:

};

