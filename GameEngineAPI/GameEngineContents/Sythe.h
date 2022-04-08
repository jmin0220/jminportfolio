#pragma once
#include "Tool.h"

// Ό³Έν :
class Sythe : public Tool
{
public:
	// constrcuter destructer
	Sythe();
	~Sythe();

	// delete Function
	Sythe(const Sythe& _Other) = delete;
	Sythe(Sythe&& _Other) noexcept = delete;
	Sythe& operator=(const Sythe& _Other) = delete;
	Sythe& operator=(Sythe&& _Other) noexcept = delete;

protected:

private:

};

