#pragma once
#include "Item.h"

// Ό³Έν :
class Topaz : public Item
{
public:
	// constrcuter destructer
	Topaz();
	~Topaz();

	// delete Function
	Topaz(const Topaz& _Other) = delete;
	Topaz(Topaz&& _Other) noexcept = delete;
	Topaz& operator=(const Topaz& _Other) = delete;
	Topaz& operator=(Topaz&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

