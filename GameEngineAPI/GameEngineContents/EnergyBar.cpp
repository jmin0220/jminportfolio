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
	SetPosition({ 1249, 591 });
	CreateRenderer("EnergyBar.bmp");
}

void EnergyBar::Render()
{
	//DebugRectRender();
}