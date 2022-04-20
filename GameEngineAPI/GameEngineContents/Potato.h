#pragma once
#include "Crops.h"

// ���� :
class Potato : public Crops
{
public:
	// constrcuter destructer
	Potato();
	~Potato();

	// delete Function
	Potato(const Potato& _Other) = delete;
	Potato(Potato&& _Other) noexcept = delete;
	Potato& operator=(const Potato& _Other) = delete;
	Potato& operator=(Potato&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};