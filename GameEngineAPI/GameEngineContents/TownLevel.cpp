#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

TownLevel::TownLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_TOWN_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(120, 110, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_TOWN_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_TOWN_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_TOWN_ALWAYSFRONT);
	
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	TileRangeSetting(120, 110);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetEnvironmentTiles(this->EnvironmentTiles_);
}

TownLevel::~TownLevel() 
{
}


void TownLevel::LevelChangeStart()
{

	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void TownLevel::LevelChangeEnd()
{

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