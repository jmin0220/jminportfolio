#include "Clock.h"

Clock::Clock() 
{
}

Clock::~Clock() 
{
}

void Clock::Start()
{
	// Clock인터페이스의 위치와 크기
	SetPosition({ 1125, 157 });
	SetScale({ 288, 292 });
}

void Clock::Render()
{
	DebugRectRender();
}