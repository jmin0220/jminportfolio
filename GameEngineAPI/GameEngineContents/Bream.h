#pragma once

// Ό³Έν :
class Bream
{
public:
	// constrcuter destructer
	Bream();
	~Bream();

	// delete Function
	Bream(const Bream& _Other) = delete;
	Bream(Bream&& _Other) noexcept = delete;
	Bream& operator=(const Bream& _Other) = delete;
	Bream& operator=(Bream&& _Other) noexcept = delete;

protected:

private:

};

