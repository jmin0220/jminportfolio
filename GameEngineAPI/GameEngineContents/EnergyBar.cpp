#include "EnergyBar.h"

EnergyBar::EnergyBar() 
{
}

EnergyBar::~EnergyBar() 
{
}

void EnergyBar::Start()
{
	// EnergyBar�������̽��� ��ġ�� ũ��
	SetPosition({ 1249, 591 });
	SetScale({ 48, 224 });
}

void EnergyBar::Render()
{
	DebugRectRender();
}