#pragma once

// Ό³Έν :
class animals
{
public:
	// constrcuter destructer
	animals();
	~animals();

	// delete Function
	animals(const animals& _Other) = delete;
	animals(animals&& _Other) noexcept = delete;
	animals& operator=(const animals& _Other) = delete;
	animals& operator=(animals&& _Other) noexcept = delete;

protected:

private:

};

