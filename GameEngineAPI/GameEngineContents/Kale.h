#pragma once
#include "Crops.h"

// Ό³Έν :
class Kale : public Crops
{
public:
	// constrcuter destructer
	Kale();
	~Kale();

	// delete Function
	Kale(const Kale& _Other) = delete;
	Kale(Kale&& _Other) noexcept = delete;
	Kale& operator=(const Kale& _Other) = delete;
	Kale& operator=(Kale&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

