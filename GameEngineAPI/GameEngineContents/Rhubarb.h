#pragma once
#include "Crops.h"

// Ό³Έν :
class Rhubarb : public Crops
{
public:
	// constrcuter destructer
	Rhubarb();
	~Rhubarb();

	// delete Function
	Rhubarb(const Rhubarb& _Other) = delete;
	Rhubarb(Rhubarb&& _Other) noexcept = delete;
	Rhubarb& operator=(const Rhubarb& _Other) = delete;
	Rhubarb& operator=(Rhubarb&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

