#include "Clock.h"

Clock::Clock() 
{
}

Clock::~Clock() 
{
}

void Clock::Start()
{
	// Clock�������̽��� ��ġ�� ũ��
	SetPosition({ 1125, 157 });
	SetScale({ 288, 292 });
}

void Clock::Render()
{
	DebugRectRender();
}