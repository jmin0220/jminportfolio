#include "FarmBuilding.h"

FarmBuilding::FarmBuilding() 
{
}

FarmBuilding::~FarmBuilding() 
{
}

void FarmBuilding::Start()
{
	Image_ = CreateRenderer(IMAGE_FARM_BUILDING);
	SetPosition({ 3046.0f, 608.0f });
}