#include "WateringCan.h"

WateringCan::WateringCan() 
{
	ItemName_ = ITEM_NAME_WATERINGCAN;
}

WateringCan::~WateringCan() 
{
}

void WateringCan::Start()
{
		ItemRenderer_ = CreateRenderer(IMAGE_TOOL_SET2);
		ItemRenderer_->SetIndex(0);

		IconRenderer_ = CreateRenderer(IMAGE_TOOL_SET2);
		IconRenderer_->SetIndex(2);
		IconRenderer_->CameraEffectOff();
}

void WateringCan::Update()
{

}