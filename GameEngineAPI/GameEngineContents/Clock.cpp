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
	SetPosition({ 1125, 129 });	
	CreateRendererToScale("Clock.bmp", { 288, 236 });
}

void Clock::Render()
{
	// DebugRectRender();
}