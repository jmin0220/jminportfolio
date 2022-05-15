#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

TownLevel::TownLevel() 
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
	BGCollisionMap_ = CreateActor<BackGround>((int)ORDER::COLLISION);
	BGCollisionMap_->Off();

	// 이미지의 좌상단이 0,0이 되도록
	BackGround_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_TOWN_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(120, 110, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_TOWN_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_TOWN_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_TOWN_ALWAYSFRONT);

	BGCollisionMap_->GetRenderer()->SetPivot({ MAP_TOWN_SIZE_W / 2, MAP_TOWN_SIZE_H / 2 });
	BGCollisionMap_->GetRenderer()->SetImage(MAP_TOWN_RENDER_ORDER_COLLISION);

	// 타일의 랜더를 저장
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	// 타일의 상태를 저장
	TileRangeSetting(120, 110);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetCropsActorSize(120, 110);
}

TownLevel::~TownLevel() 
{
}


void TownLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void TownLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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


	if (true == GameEngineInput::GetInst()->IsDown(KEY_DEBUG))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_COLLISIONMAP_UP)
		&& false == ColMapFlg_)
	{
		BGCollisionMap_->GetRenderer()->SetOrder((int)ORDER::FRONTB);
		BGCollisionMap_->On();
		ColMapFlg_ = true;
	}
	else if (true == GameEngineInput::GetInst()->IsDown(KEY_COLLISIONMAP_UP)
		&& true == ColMapFlg_)
	{
		BGCollisionMap_->GetRenderer()->SetOrder((int)ORDER::COLLISION);
		BGCollisionMap_->Off();
		ColMapFlg_ = false;
	}
}