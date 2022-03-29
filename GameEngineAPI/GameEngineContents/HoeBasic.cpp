#include "HoeBasic.h"

HoeBasic::HoeBasic() 
{
}

HoeBasic::~HoeBasic() 
{
}

void HoeBasic::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer(IMAGE_TOOL_SET1);
	Renderer->SetIndex(0);

	Death(2.0f);
}

void HoeBasic::Update()
{
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}