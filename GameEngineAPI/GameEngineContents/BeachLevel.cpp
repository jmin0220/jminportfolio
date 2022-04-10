#include "BeachLevel.h"

BeachLevel::BeachLevel() 
{
	// ���
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONTA);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);
}

BeachLevel::~BeachLevel() 
{
}


void BeachLevel::LevelChangeStart()
{
	// �̹����� �»���� 0,0�� �ǵ���
	BackGround_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BackGround_->GetRenderer()->SetImage(MAP_BEACH_BACKGORUND);
	BackGround_->TileMap_.TileRangeSetting(80, 65, { TILEMAP_SIZE, TILEMAP_SIZE });

	BGBuilding_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGBuilding_->GetRenderer()->SetImage(MAP_BEACH_BUILDING);

	BGFront_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGFront_->GetRenderer()->SetImage(MAP_BEACH_FRONT);

	BGAlwaysFront_->GetRenderer()->SetPivot({ MAP_BEACH_SIZE_W / 2, MAP_BEACH_SIZE_H / 2 });
	BGAlwaysFront_->GetRenderer()->SetImage(MAP_BEACH_ALWAYSFRONT);


	// �÷��̾�� ���� �浹 ó��
	BGBuilding_->CreateCollision(COL_GROUP_WALL, { 0.0f, 0.0f });
	// �÷��̾�� �ǹ��� ������ ����
	BGFront_->CreateCollision(COL_GROUP_RENDER_ORDER, { 0.0f, 0.0f });

	this->Player_->SetPosition({ 1870.0f, 50.0f });
	this->Player_->SetTileMap(&BackGround_->TileMap_);

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
