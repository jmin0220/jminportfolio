#include "EnergyBar.h"

EnergyBar::EnergyBar() 
{
}

EnergyBar::~EnergyBar() 
{
}

void EnergyBar::Start()
{
	// EnergyBar�������̽�������
	SetPosition({ IMAGE_ENERGYBAR_POS_W, IMAGE_ENERGYBAR_POS_H });
	CreateRenderer("EnergyBar.bmp");
}

void EnergyBar::Render()
{
	//DebugRectRender();
}