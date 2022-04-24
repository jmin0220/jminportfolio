#pragma once
#include "Item.h"

// Ό³Έν :
class KaleFruit : public Item
{
public:
	// constrcuter destructer
	KaleFruit();
	~KaleFruit();

	// delete Function
	KaleFruit(const KaleFruit& _Other) = delete;
	KaleFruit(KaleFruit&& _Other) noexcept = delete;
	KaleFruit& operator=(const KaleFruit& _Other) = delete;
	KaleFruit& operator=(KaleFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

