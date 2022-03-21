#include "EnergyBar.h"

EnergyBar::EnergyBar() 
{
}

EnergyBar::~EnergyBar() 
{
}

void EnergyBar::Start()
{
	// EnergyBar인터페이스의 위치와 크기
	SetPosition({ 1249, 591 });
	SetScale({ 48, 224 });
}

void EnergyBar::Render()
{
	DebugRectRender();
}