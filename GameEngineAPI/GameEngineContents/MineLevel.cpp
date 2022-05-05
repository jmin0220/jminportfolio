#include "MineLevel.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

MineLevel::MineLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_MINES_SIZE_W / 2, MAP_MINES_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_MINES_BACKGROUND);
	BackGround_->TileMap_.TileRangeSetting(20, 77, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_MINES_SIZE_W / 2, MAP_MINES_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_MINES_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_MINES_SIZE_W / 2, MAP_MINES_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_MINES_FRONT);

	// Ÿ���� ������ ����
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	// Ÿ���� ���¸� ����
	TileRangeSetting(20, 77);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetCropsActorSize(20, 77);
}

MineLevel::~MineLevel() 
{
}


void MineLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void MineLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void MineLevel::Loading()
{

}

void MineLevel::Update()
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