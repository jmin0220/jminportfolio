#pragma once
#include "Crops.h"

// Ό³Έν :
class Blueberry : public Crops
{
public:
	// constrcuter destructer
	Blueberry();
	~Blueberry();

	// delete Function
	Blueberry(const Blueberry& _Other) = delete;
	Blueberry(Blueberry&& _Other) noexcept = delete;
	Blueberry& operator=(const Blueberry& _Other) = delete;
	Blueberry& operator=(Blueberry&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

