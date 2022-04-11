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
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
}

FarmLevel::~FarmLevel() 
{
}


void FarmLevel::LevelChangeStart()
{
	// 목장 오두막 생성
	FarmBuilding_ = CreateActor<FarmBuilding>((int)ORDER::FRONTA);

	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_FARM_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });
	
	BGBuilding_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_FARM_BUILDING);
	
	BGFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_FARM_FRONT);
	
	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_FARM_ALWAYSFRONT);
	

	// 플레이어와 맵의 충돌 처리
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });
	// 플레이어와 건물의 렌더링 순서
	BGFront_->CreateCollision(COL_GROUP_RENDER_ORDER, { 100.0f, 100.0f });

	// 사운드 설정
	BgmPlayer = GameEngineSound::SoundPlayControl("spring_day.wav");

	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
	this->Player_->SetTileMap(&BackGround_->TileMap_);

}

void FarmLevel::LevelChangeEnd()
{

}

void FarmLevel::Loading()
{

}

void FarmLevel::Update()
{
	if (false == this->Player_->ColRenderOrderCheck())
	{
		BGFront_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTA);
		FarmBuilding_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTA);
	}
	else
	{
		BGFront_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTB);
		FarmBuilding_->GetRenderer()->GameEngineRenderer::SetOrder((int)ORDER::FRONTB);
	}
}
