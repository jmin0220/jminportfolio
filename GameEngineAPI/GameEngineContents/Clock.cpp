#include "Clock.h"

Clock::Clock() 
{
}

Clock::~Clock() 
{
}

void Clock::Start()
{
	// Clock�������̽�������
	SetPosition({ IMAGE_CLOCK_POS_W, IMAGE_CLOCK_POS_H });
	CreateRendererToScale("Clock.bmp", { IMAGE_CLOCK_SIZE_W, IMAGE_CLOCK_SIZE_H });
}

void Clock::Render()
{
	// DebugRectRender();
}