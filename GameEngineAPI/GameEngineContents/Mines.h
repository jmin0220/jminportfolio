#pragma once

// Ό³Έν :
class Mines
{
public:
	// constrcuter destructer
	Mines();
	~Mines();

	// delete Function
	Mines(const Mines& _Other) = delete;
	Mines(Mines&& _Other) noexcept = delete;
	Mines& operator=(const Mines& _Other) = delete;
	Mines& operator=(Mines&& _Other) noexcept = delete;

protected:

private:

};

