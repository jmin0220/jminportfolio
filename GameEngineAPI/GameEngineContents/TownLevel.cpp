#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

TownLevel::TownLevel() 
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONT);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
}

TownLevel::~TownLevel() 
{
}


void TownLevel::LevelChangeStart()
{
	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_TOWN_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { 48, 48 });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_TOWN_BUILDING);
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });

	BGFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_TOWN_FRONT);
	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_TOWN_ALWAYSFRONT);

	this->Player_->SetPosition({ 700.0f, 2600.0f });
}


void TownLevel::Loading()
{

}


void TownLevel::Update()
{

}