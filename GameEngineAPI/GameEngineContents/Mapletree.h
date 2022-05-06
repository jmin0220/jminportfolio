#pragma once
#include "Crops.h"

// Ό³Έν :
class Mapletree : public Crops
{
public:
	// constrcuter destructer
	Mapletree();
	~Mapletree();

	// delete Function
	Mapletree(const Mapletree& _Other) = delete;
	Mapletree(Mapletree&& _Other) noexcept = delete;
	Mapletree& operator=(const Mapletree& _Other) = delete;
	Mapletree& operator=(Mapletree&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;
	void Update() override;

private:

};

