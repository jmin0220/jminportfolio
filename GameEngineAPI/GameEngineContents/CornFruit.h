#pragma once
#include "Item.h"

// Ό³Έν :
class CornFruit : public Item
{
public:
	// constrcuter destructer
	CornFruit();
	~CornFruit();

	// delete Function
	CornFruit(const CornFruit& _Other) = delete;
	CornFruit(CornFruit&& _Other) noexcept = delete;
	CornFruit& operator=(const CornFruit& _Other) = delete;
	CornFruit& operator=(CornFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

