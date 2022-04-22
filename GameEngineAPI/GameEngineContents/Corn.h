#pragma once
#include "Crops.h"

// Ό³Έν :
class Corn : public Crops
{
public:
	// constrcuter destructer
	Corn();
	~Corn();

	// delete Function
	Corn(const Corn& _Other) = delete;
	Corn(Corn&& _Other) noexcept = delete;
	Corn& operator=(const Corn& _Other) = delete;
	Corn& operator=(Corn&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

