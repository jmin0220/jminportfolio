#include "Clock.h"
#include <GameEngine/GameEngineRenderer.h>

Clock::Clock() 
{
}

Clock::~Clock() 
{
}

void Clock::Start()
{
	// Clock인터페이스렌더링
	SetPosition({ IMAGE_CLOCK_POS_W, IMAGE_CLOCK_POS_H });
	GameEngineRenderer* Renderer = CreateRendererToScale("Clock.bmp", { IMAGE_CLOCK_SIZE_W, IMAGE_CLOCK_SIZE_H });
	Renderer->CameraEffectOff();
}

void Clock::Render()
{
	// DebugRectRender();
}