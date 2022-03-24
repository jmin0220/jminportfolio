#include "EnergyBar.h"

EnergyBar::EnergyBar() 
{
}

EnergyBar::~EnergyBar() 
{
}

void EnergyBar::Start()
{
	// EnergyBar인터페이스렌더링
	SetPosition({ IMAGE_ENERGYBAR_POS_W, IMAGE_ENERGYBAR_POS_H });
	CreateRenderer("EnergyBar.bmp");
}

void EnergyBar::Render()
{
	//DebugRectRender();
}