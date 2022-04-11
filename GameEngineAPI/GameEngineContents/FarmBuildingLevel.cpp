#include "FarmBuildingLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

FarmBuildingLevel::FarmBuildingLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
}

FarmBuildingLevel::~FarmBuildingLevel() 
{
}


void FarmBuildingLevel::LevelChangeStart()
{
	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->SetPosition({ MAP_FARMBUILDING_SIZE_W / 2, MAP_FARMBUILDING_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_FARMBUILDING_BACKGROUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->SetPosition({ MAP_FARMBUILDING_SIZE_W / 2, MAP_FARMBUILDING_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_FARMBUILDING_BUILDING);

	BGFront_->SetPosition({ MAP_FARMBUILDING_SIZE_W / 2, MAP_FARMBUILDING_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_FARMBUILDING_FRONT);

	// �ø��� ����
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });

	this->Player_->SetTileMap(&BackGround_->TileMap_);
}

void FarmBuildingLevel::Loading()
{

}


void FarmBuildingLevel::Update()
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