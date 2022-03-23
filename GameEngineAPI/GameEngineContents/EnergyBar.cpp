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
	SetPosition({ 1249, 591 });
	CreateRenderer("EnergyBar.bmp");
}

void EnergyBar::Render()
{
	//DebugRectRender();
}