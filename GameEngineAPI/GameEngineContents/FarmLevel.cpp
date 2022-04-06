#include "FarmLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "FarmBuilding.h"
#include <GameEngine/GameEngineRenderer.h>

FarmLevel::FarmLevel() 
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONT);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
}

FarmLevel::~FarmLevel() 
{
}


void FarmLevel::LevelChangeStart()
{
	// 목장 오두막 생성
	CreateActor<FarmBuilding>((int)ORDER::BUIDING);

	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_FARM_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { 48, 48});
	
	BGBuilding_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_FARM_BUILDING);
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });

	BGFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_FARM_FRONT);
	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_FARM_ALWAYSFRONT);
	
	this->Player_->SetPosition({ 3200.0f, 800.0f });
	this->Player_->SetTileMap(&BackGround_->TileMap_);
}

void FarmLevel::Loading()
{

}

void FarmLevel::Update()
{
	// CameraUpdate();
}
