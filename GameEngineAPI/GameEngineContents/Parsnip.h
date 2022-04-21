#pragma once
#include "Crops.h"

// Ό³Έν :
class Parsnip : public Crops
{
public:
	// constrcuter destructer
	Parsnip();
	~Parsnip();

	// delete Function
	Parsnip(const Parsnip& _Other) = delete;
	Parsnip(Parsnip&& _Other) noexcept = delete;
	Parsnip& operator=(const Parsnip& _Other) = delete;
	Parsnip& operator=(Parsnip&& _Other) noexcept = delete;

protected:
	void Start() override;
	void CreateItem() override;

private:

};

