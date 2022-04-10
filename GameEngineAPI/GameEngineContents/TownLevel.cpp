#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

TownLevel::TownLevel() 
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
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
	BackGround_->TileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_TOWN_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_TOWN_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_TOWN_ALWAYSFRONT);

	// 컬리전
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });
	BGFront_->CreateCollision(COL_GROUP_RENDER_ORDER, { 100.0f, 100.0f });

	this->Player_->SetPosition({ 300.0f, 2600.0f });
	this->Player_->SetTileMap(&BackGround_->TileMap_);
}


void TownLevel::Loading()
{

}


void TownLevel::Update()
{
	if (false == this->Player_->ColRenderOrderCheck())
	{
		BGFront_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTA);
	}
	else
	{
		BGFront_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTB);
	}
}