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
	// �̹����� �»���� 0,0�� �ǵ���
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
