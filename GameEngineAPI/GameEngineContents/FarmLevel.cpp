#include "FarmLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "FarmBuilding.h"
#include <GameEngine/GameEngineRenderer.h>

FarmLevel::FarmLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONT);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
}

FarmLevel::~FarmLevel() 
{
}


void FarmLevel::LevelChangeStart()
{
	// ���� ���θ� ����
	CreateActor<FarmBuilding>((int)ORDER::BUIDING);

	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->SetPosition({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_FARM_BACKGORUND);
	BGBuilding_->SetPosition({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_FARM_BUILDING);
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 100.0f, 100.0f });
	BGFront_->SetPosition({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_FARM_FRONT);
	BGAlwaysFront_->SetPosition({ MAP_FARM_SIZE_W / 2, MAP_FARM_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_FARM_ALWAYSFRONT);
	
	this->Player_->SetPosition({ 3200.0f, 800.0f });
}

void FarmLevel::Loading()
{

}

void FarmLevel::Update()
{
	// CameraUpdate();
}
