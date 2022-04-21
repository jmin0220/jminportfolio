#include "Crops.h"

Crops::Crops() 
{
	RandomItem_ = new GameEngineRandom();
}

Crops::~Crops() 
{
	delete RandomItem_;
	RandomItem_ = nullptr;
}

void Crops::Destroy()
{
	this->Death();
}