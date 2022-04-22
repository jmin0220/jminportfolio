#pragma once
#include "Crops.h"

// Ό³Έν :
class Greenbean : public Crops
{
public:
	// constrcuter destructer
	Greenbean();
	~Greenbean();

	// delete Function
	Greenbean(const Greenbean& _Other) = delete;
	Greenbean(Greenbean&& _Other) noexcept = delete;
	Greenbean& operator=(const Greenbean& _Other) = delete;
	Greenbean& operator=(Greenbean&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

