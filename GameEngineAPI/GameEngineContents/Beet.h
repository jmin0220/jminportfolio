#pragma once
#include "Crops.h"

// Ό³Έν :
class Beet : public Crops
{
public:
	// constrcuter destructer
	Beet();
	~Beet();

	// delete Function
	Beet(const Beet& _Other) = delete;
	Beet(Beet&& _Other) noexcept = delete;
	Beet& operator=(const Beet& _Other) = delete;
	Beet& operator=(Beet&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

