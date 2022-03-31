#include "EnergyBar.h"
#include <GameEngine/GameEngineRenderer.h>

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
	GameEngineRenderer* Renderer = CreateRenderer("EnergyBar.bmp");
	Renderer->CameraEffectOff();
}

void EnergyBar::Render()
{
	//DebugRectRender();
}