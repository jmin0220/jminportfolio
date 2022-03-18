#pragma once

// Ό³Έν :
class Slime
{
public:
	// constrcuter destructer
	Slime();
	~Slime();

	// delete Function
	Slime(const Slime& _Other) = delete;
	Slime(Slime&& _Other) noexcept = delete;
	Slime& operator=(const Slime& _Other) = delete;
	Slime& operator=(Slime&& _Other) noexcept = delete;

protected:

private:

};

