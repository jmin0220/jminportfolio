#include "FarmLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "FarmBuilding.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

FarmLevel::FarmLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
	BGCollisionMap_ = CreateActor<BackGround>((int)ORDER::COLLISION);
	BGCollisionMap_->Off();

	// ���� ���θ� ����
	FarmBuilding_ = CreateActor<FarmBuilding>((int)ORDER::FRONTA);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_FARM_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_FARM_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_FARM_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_FARM_ALWAYSFRONT);

	BGCollisionMap_->GetRenderer()->SetPivot({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGCollisionMap_->GetRenderer()->SetImage(MAP_FARM_COLLISION);


	// ���� ����
	BgmPlayer = GameEngineSound::SoundPlayControl("spring_day.wav");

	// Ÿ���� ������ ����
	this->Player_->SetTileMap(&BackGround_->TileMap_);

	// Ÿ���� ���¸� ����
	TileRangeSetting(80, 65);
	this->Player_->SetGroundTiles(this->GroundTiles_);
	this->Player_->SetCropsActorSize(80, 65);

	// �÷��̾ ó�� �����ϴ� ���̹Ƿ� PlayerInit�� �ѹ� ����.
	this->Player_->PlayerInit();
}

FarmLevel::~FarmLevel() 
{
}


void FarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	this->Player_->SetPosition(this->Player_->GetNextLevelPos());
}

void FarmLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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


	if (true == GameEngineInput::GetInst()->IsDown(KEY_DEBUG))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_COLLISIONMAP_UP)
		&& false == ColMapFlg_)
	{
		BGCollisionMap_->GetRenderer()->SetOrder((int)ORDER::FRONTA);
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
