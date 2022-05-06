#pragma once
#include "Crops.h"

// Ό³Έν :
class Pinetree : public Crops
{
public:
	// constrcuter destructer
	Pinetree();
	~Pinetree();

	// delete Function
	Pinetree(const Pinetree& _Other) = delete;
	Pinetree(Pinetree&& _Other) noexcept = delete;
	Pinetree& operator=(const Pinetree& _Other) = delete;
	Pinetree& operator=(Pinetree&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;
	void Update() override;
private:

};

