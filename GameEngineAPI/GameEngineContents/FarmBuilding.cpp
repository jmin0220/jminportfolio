#include "FarmBuilding.h"

FarmBuilding::FarmBuilding() 
{
}

FarmBuilding::~FarmBuilding() 
{
}

void FarmBuilding::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer(IMAGE_FARM_BUILDING);
	SetPosition({ 3046.0f, 608.0f });
}