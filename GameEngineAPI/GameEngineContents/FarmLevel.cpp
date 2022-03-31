#include "FarmLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

FarmLevel::FarmLevel() 
{
}

FarmLevel::~FarmLevel() 
{
}


void FarmLevel::LevelChangeStart()
{
	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->SetPosition({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage("FarmBack.bmp");
}

void FarmLevel::Loading()
{

}

void FarmLevel::Update()
{
	// CameraUpdate();
}
