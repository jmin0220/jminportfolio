#pragma once

// Ό³Έν :
class Chiecken
{
public:
	// constrcuter destructer
	Chiecken();
	~Chiecken();

	// delete Function
	Chiecken(const Chiecken& _Other) = delete;
	Chiecken(Chiecken&& _Other) noexcept = delete;
	Chiecken& operator=(const Chiecken& _Other) = delete;
	Chiecken& operator=(Chiecken&& _Other) noexcept = delete;

protected:

private:

};

