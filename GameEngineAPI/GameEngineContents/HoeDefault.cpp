#include "HoeDefault.h"

HoeDefault::HoeDefault() 
{
}

HoeDefault::~HoeDefault() 
{
}

void HoeDefault::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer(IMAGE_TOOL_SET1);
	Renderer->SetIndex(0);

	Death(2.0f);
}

void HoeDefault::Update()
{
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}