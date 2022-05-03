#pragma once
#include "Crops.h"

// Ό³Έν :
class Oaktree : public Crops
{
public:
	// constrcuter destructer
	Oaktree();
	~Oaktree();

	// delete Function
	Oaktree(const Oaktree& _Other) = delete;
	Oaktree(Oaktree&& _Other) noexcept = delete;
	Oaktree& operator=(const Oaktree& _Other) = delete;
	Oaktree& operator=(Oaktree&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;
	void Update() override;

private:

};

