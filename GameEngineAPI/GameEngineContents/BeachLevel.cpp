#include "BeachLevel.h"

BeachLevel::BeachLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_BEACH_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(104, 49, { TILEMAP_SIZE, TILEMAP_SIZE });
	BackGround_->EnvironmentTileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_BEACH_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_BEACH_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_BEACH_ALWAYSFRONT);

	// Ÿ���� ������ ����
	this->Player_->SetTileMap(&BackGround_->TileMap_);
	this->Player_->SetEnvironmentTileMap(&BackGround_->EnvironmentTileMap_);

	// Ÿ���� ���¸� ����
	TileRangeSetting(104, 49);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetEnvironmentTiles(this->EnvironmentTiles_);
}

BeachLevel::~BeachLevel() 
{
}


void BeachLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void BeachLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void BeachLevel::Loading()
{

}

void BeachLevel::Update()
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
