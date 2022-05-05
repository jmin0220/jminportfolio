#pragma once
#include "Item.h"

// Ό³Έν :
class Amethyst : public Item
{
public:
	// constrcuter destructer
	Amethyst();
	~Amethyst();

	// delete Function
	Amethyst(const Amethyst& _Other) = delete;
	Amethyst(Amethyst&& _Other) noexcept = delete;
	Amethyst& operator=(const Amethyst& _Other) = delete;
	Amethyst& operator=(Amethyst&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

