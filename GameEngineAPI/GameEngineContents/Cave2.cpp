#include "Cave2.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

Cave2::Cave2() 
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);

	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->GetRenderer()->SetPivot({ MAP_CAVE2_SIZE_W / 2, MAP_CAVE2_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_CAVE2_BACKGROUND);
	BackGround_->TileMap_.TileRangeSetting(35, 35, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_CAVE2_SIZE_W / 2, MAP_CAVE2_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_CAVE2_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_CAVE2_SIZE_W / 2, MAP_CAVE2_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_CAVE2_FRONT);

	// 타일의 랜더를 저장
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	// 타일의 상태를 저장
	TileRangeSetting(35, 35);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetCropsActorSize(35, 35);
	this->Player_->MineralInit(MAP_CAVE2_COLLISION);
}

Cave2::~Cave2() 
{
}

void Cave2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void Cave2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void Cave2::Loading()
{

}

void Cave2::Update()
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
