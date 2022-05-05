#pragma once
#include "Item.h"

// Ό³Έν :
class Jade : public Item
{
public:
	// constrcuter destructer
	Jade();
	~Jade();

	// delete Function
	Jade(const Jade& _Other) = delete;
	Jade(Jade&& _Other) noexcept = delete;
	Jade& operator=(const Jade& _Other) = delete;
	Jade& operator=(Jade&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

