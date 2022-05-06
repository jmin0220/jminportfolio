#include "Cave1.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

Cave1::Cave1() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_CAVE1_SIZE_W / 2, MAP_CAVE1_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_CAVE1_BACKGROUND);
	BackGround_->TileMap_.TileRangeSetting(26, 20, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_CAVE1_SIZE_W / 2, MAP_CAVE1_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_CAVE1_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_CAVE1_SIZE_W / 2, MAP_CAVE1_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_CAVE1_FRONT);

	// Ÿ���� ������ ����
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	// Ÿ���� ���¸� ����
	TileRangeSetting(26, 20);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetCropsActorSize(26, 20);
	this->Player_->MineralInit(MAP_CAVE1_COLLISION);
}

Cave1::~Cave1() 
{
}

void Cave1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void Cave1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Cave1::Loading()
{
}

void Cave1::Update()
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