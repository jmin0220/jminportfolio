#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
#include "Item.h"
#include "Hoe.h"
#include "Axe.h"
#include "WateringCan.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <vector>

float4 Player::NextLevelPos_ = { 3200.0f, 820.0f };
Inventory* Player::Inventory_;
Clock* Player::Clock_;
EnergyBar* Player::EnergyBar_;

Player::Player() 
	:Speed_(500.0f)
	, MoveDir_(float4::DOWN)
	, NextLevel_("")
{
}

Player::~Player() 
{
}

void Player::PlayerInit()
{

	// �κ��丮 �ʱ⼳��
	Hoe* hoe = this->GetLevel()->CreateActor<Hoe>((int)ORDER::UIICONS);
	Inventory_->AddItemToInventory(*hoe);

	Axe* axe = this->GetLevel()->CreateActor<Axe>((int)ORDER::UIICONS);
	Inventory_->AddItemToInventory(*axe);

	WateringCan* wateringCan = this->GetLevel()->CreateActor<WateringCan>((int)ORDER::UIICONS);
	Inventory_->AddItemToInventory(*wateringCan);
}

void Player::Start()
{
	// UI
	Inventory_ = this->GetLevel()->CreateActor<Inventory>((int)ORDER::UI);
	Clock_ = this->GetLevel()->CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = this->GetLevel()->CreateActor<EnergyBar>((int)ORDER::UI);

	// �ִϸ��̼� �ʱ�ȭ
	PlayerAnimationInit();
	// Ű���� �ʱ�ȭ
	PlayerKeyInit();
	// ī�޶� ��ġ �ʱ�ȭ
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// ī�޶� ����
	UpdateCamera();

	// ���� ������Ʈ
	StateUpdate();
}

// ���� ������Ʈ
void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Action:
		ActionUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}
}

// ���� ����
void Player::StateChange(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Action:
			ActionStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

// �ִϸ��̼� �ʱ�ȭ
void Player::PlayerAnimationInit()
{
	/*
	* https://stardewvalleywiki.com/Modding:Farmer_sprite
	The farmer sprite is drawn in several layers.On the bottom layer is the head, torso, and boots.
	The clothing, accessories, hair, and others are all drawn in multiple layers on top in this order:

	1. Head / Torso / Boots - Bottom layer
	2. Pants
	3. Shirt
	4. Accessories(e.g., glasses, makeup, earrings, facial hair)
	5. Hair
	6. Hat
	7. Arms - Top layer
	*/

	// TODO::����
	/*
	//int directionDown = 0;
	//int directionRight = 27;
	//int directionLeft = 54;
	//int directionUp = 81;

	//// �÷��̾� ĳ���� ������
	//RendererBody_ = CreateRenderer((int)ORDER::PLAYER);
	//RendererLegs_ = CreateRenderer((int)ORDER::PLAYER);
	//RendererCloth_ = CreateRenderer((int)ORDER::PLAYER);
	//RendererHair_ = CreateRenderer((int)ORDER::PLAYER);
	//RendererArms_ = CreateRenderer((int)ORDER::PLAYER);

	//IMAGE_PLAYER_MAN_BODY����
	//7 / 7 / 6 / 7 = 1�ٿ� 27��������Ʈ�� ����.
	//*
	//int SpriteLineNum = 27;
	//int up, down, left, right;

	//// Idle
	//// ����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);
	//// ��
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 7 + directionDown, 7 + directionDown, 0.2f, false);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 7 + directionRight, 7 + directionRight, 0.2f, false);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 7 + directionLeft, 7 + directionLeft, 0.2f, false);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 7 + directionUp, 7 + directionUp, 0.2f, false);
	//// �ٸ�
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 20 + directionDown, 20 + directionDown, 0.2f, false);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 20 + directionRight, 20 + directionRight, 0.2f, false);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 20 + directionLeft, 20 + directionLeft, 0.2f, false);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 20 + directionUp, 20 + directionUp, 0.2f, false);

	//// Walk
	//// ��
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 0 + directionDown, 3 + directionDown, 0.2f, true);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 0 + directionRight, 3 + directionRight, 0.2f, true);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 0 + directionLeft, 3 + directionLeft, 0.2f, true);
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 0 + directionUp, 3 + directionUp, 0.2f, true);
	//// ��
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 7 + directionDown, 10 + directionDown, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 7 + directionRight, 10 + directionRight, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 7 + directionLeft, 10 + directionLeft, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 7 + directionUp, 10 + directionUp, 0.2f, true);
	//// �ٸ�
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 20 + directionDown, 23 + directionDown, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 20 + directionRight, 23 + directionRight, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 20 + directionLeft, 23 + directionLeft, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 20 + directionUp, 23 + directionUp, 0.2f, true);

	//// ���η� �ֵθ���
	//down = 16 * SpriteLineNum;
	//right = 11 * SpriteLineNum;
	//left = 12 * SpriteLineNum;
	//up = 9 * SpriteLineNum;
	//// ����
	//// 16����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_DOWN, down, down + 6, 0.2f, true);
	//// 11����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_RIGHT, right, right + 6, 0.2f, true);
	//// 12����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_LEFT, left, left + 6, 0.2f, true);
	//// 9����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_UP, up, up + 6, 0.2f, true);
	//// ��
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_DOWN, down + 7, down + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_RIGHT, right + 7, right + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_LEFT, left + 7, left + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_UP, up + 7, up + 7 + 6, 0.2f, true);
	//// �ٸ�
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_DOWN, down + 20, down + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_RIGHT, right + 20, right + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_LEFT, left + 20, left + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_HORIZON_UP, up + 20, up + 20 + 6, 0.2f, true);


	//// ���η� �ֵθ���
	//down = 5 * SpriteLineNum;
	//right = 6 * SpriteLineNum;
	//left = 7 * SpriteLineNum;
	//up = 8 * SpriteLineNum;
	//// ����
	//// 6����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_DOWN, down, down + 6, 0.2f, true);
	//// 7����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_RIGHT, right, right + 6, 0.2f, true);
	//// 8����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_LEFT, left, left + 6, 0.2f, true);
	//// 9����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_UP, up, up + 6, 0.2f, true);
	//// ��
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_DOWN, down + 7, down + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_RIGHT, right + 7, right + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_LEFT, left + 7, left + 7 + 6, 0.2f, true);
	//RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_UP, up + 7, up + 7 + 6, 0.2f, true);
	//// �ٸ�
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_DOWN, down + 20, down + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_RIGHT, right + 20, right + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_LEFT, left + 20, left + 20 + 6, 0.2f, true);
	//RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_HIT_VERTICAL_UP, up + 20, up + 20 + 6, 0.2f, true);



	//// Hair
	//// Idle
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_RIGHT, 8, 8, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_LEFT, 16, 16, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_UP, 24, 24, 0.0f, false);
	//// Walk
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_DOWN, 0, 0, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_RIGHT, 8, 8, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_LEFT, 16, 16, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_UP, 24, 24, 0.0f, false);
	//// �׼�
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_HIT_HORIZON_DOWN, 0, 0, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_HIT_HORIZON_RIGHT, 8, 8, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_HIT_HORIZON_LEFT, 16, 16, 0.0f, false);
	//RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_HIT_HORIZON_UP, 24, 24, 0.0f, false);

	//// Cloth
	//// Idle
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_RIGHT, 16, 16, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_LEFT, 32, 32, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_UP, 48, 48, 0.0f, false);
	//// Walk
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_DOWN, 0, 0, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_RIGHT, 16, 16, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_LEFT, 32, 32, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_UP, 48, 48, 0.0f, false);

	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_HIT_HORIZON_DOWN, 0, 0, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_HIT_HORIZON_RIGHT, 16, 16, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_HIT_HORIZON_LEFT, 32, 32, 0.0f, false);
	//RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_HIT_HORIZON_UP, 48, 48, 0.0f, false);

	//// �ʱ� �ִϸ��̼�
	//RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	//RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	//RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
	//RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	//RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);
    */

	// 1�ٿ� 6���� ��������Ʈ
	int oneline = 6;
	RendererBody_ = CreateRenderer(IMAGE_PLAYER_MAN_TOTAL, (int)ORDER::PLAYER);
	RendererBody_->SetPivot({ 0.0f, -24.0f, });

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_IDLE_DOWN, 0, 0, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_IDLE_RIGHT, 1 * oneline, 1 * oneline, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_IDLE_LEFT, 2 * oneline, 2 * oneline, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_IDLE_UP, 3 * oneline, 3 * oneline, 0.2f, false);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WALK_DOWN, 0, 3, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WALK_RIGHT, 1 * oneline, 1 * oneline + 3, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WALK_LEFT, 2 * oneline, 2 * oneline + 3, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WALK_UP, 3 * oneline, 3 * oneline + 3, 0.2f, true);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_VERTICAL_DOWN, 4 * oneline, 4 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_VERTICAL_RIGHT, 5 * oneline, 5 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_VERTICAL_LEFT, 6 * oneline, 6 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_VERTICAL_UP, 7 * oneline, 7 * oneline + 5, 0.1f, true);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_RIGHT, 8 * oneline, 8 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_LEFT, 9 * oneline, 9 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_DOWN, 10 * oneline, 10 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_UP, 11 * oneline, 11 * oneline + 3, 0.1f, true);

	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
}

// �ִϸ��̼� ��ȯ
void Player::PlayerAnimationChange(const std::string& _Name)
{
	RendererBody_->ChangeAnimation(_Name);
	// TODO::����
	//RendererLegs_->ChangeAnimation(_Name);
	//RendererHair_->ChangeAnimation(_Name);
	//RendererCloth_->ChangeAnimation(_Name);
	//RendererArms_->ChangeAnimation(_Name);
}

// ����Ű �ʱ�ȭ
void Player::PlayerKeyInit()
{
	// Ű����
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, 'D');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_DOWN, 'S');

		// ��Ŭ���������� ��ȣ�ۿ�
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}
}

// ī�޶� �̵�
void Player::UpdateCamera()
{
	float CurrentLevelH = 0.0f;
	float CurrentLevelW = 0.0f;

	if (GetCurrentLevel() == LEVEL_FARM)
	{
		CurrentLevelH = MAP_FARM_SIZE_H;
		CurrentLevelW = MAP_FARM_SIZE_W;
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		CurrentLevelH = MAP_TOWN_SIZE_H;
		CurrentLevelW = MAP_TOWN_SIZE_W;
	}
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		CurrentLevelH = MAP_BEACH_SIZE_H;
		CurrentLevelW = MAP_BEACH_SIZE_W;
	}

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	// ī�޶� �� ������ �������� ����ġ
	if (CameraPos_.x <= 0)
	{
		CameraPos_.x = 0;
	}
	if (CameraPos_.x >= CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix())
	{
		CameraPos_.x = CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix();
	}
	if (CameraPos_.y <= 0)
	{
		CameraPos_.y = 0;
	}
	if (CameraPos_.y >= CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy())
	{
		CameraPos_.y = CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy();
	}

	// ī�޶� ��ġ ����
	GetLevel()->SetCameraPos(CameraPos_);
}

// �÷��̾��� ��ġ�� ���� Front���� ������ ������ ���������� ����
bool Player::ColRenderOrderCheck()
{
	// �ø����� ���
	if (GetCurrentLevel() == LEVEL_FARM)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARM_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_TOWN_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_BEACH_RENDER_ORDER_COLLISION);
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	// ����
	float4 CheckPos = { GetPosition().x - (TILEMAP_SIZE), GetPosition().y };
	int Color = MapColImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// ������
	CheckPos = { GetPosition().x + (TILEMAP_SIZE), GetPosition().y };
	Color = MapColImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// ��
	CheckPos = { GetPosition().x, GetPosition().y - ((TILEMAP_SIZE) / 2) };
	Color = MapColImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// �Ʒ�
	CheckPos = { GetPosition().x, GetPosition().y + ((TILEMAP_SIZE) / 2) };
	Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// �÷��̾��� ��ġ
	CheckPos = GetPosition();
	Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �浹üũ
void Player::ColWallCheck(float4 _MoveDir)
{
	// MoveDir�� ���� �̵��߿����� ���ŵ�.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// �ø����� ���
	if (GetCurrentLevel() == LEVEL_FARM)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARM_COLLISION); 
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_TOWN_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_FARMBUILDING)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARMBUILDING_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_BEACH_COLLISION);
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	float4 NextPos = GetPosition() + CheckLength;
	float4 CheckPos = SetCheckPos(NextPos);

	int Color = MapColImage_->GetImagePixel(CheckPos);
	
	// �浹����
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}


	if (GetCurrentLevel() == LEVEL_FARM)
	{
		// Ÿ������ �̵�
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 200.0f, 2600.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
		else if (RGB(0, 255, 0) == Color)
		{
			// ���Ҽ���
			//SetNextLevelPos({ MAP_FARMBUILDING_SIZE_W / 2, MAP_FARMBUILDING_SIZE_H / 2 });
			//GameEngine::GetInst().ChangeLevel(LEVEL_FARMBUILDING);
		}
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		// Ÿ������ �̵�
		if (RGB(255, 0, 0) == Color)
		{
			// �������� �̵�
			SetNextLevelPos({ 3730.0f, 850.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
		else if (RGB(0, 0, 255) == Color)
		{
			SetNextLevelPos({ 1870.0f, 50.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_BEACH);
		}
	}
	else if (GetCurrentLevel() == LEVEL_FARMBUILDING)
	{
		// �������� �̵�
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 3200.0f, 800.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
	}
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 2620.0f, 5180.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
	}
}

float4 Player::SetCheckPos(float4 _NextPos)
{
	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		return _NextPos + float4(0.0f, 24.0f);
	}
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		return _NextPos + float4(24.0f, 24.0f);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		return _NextPos + float4(-24.0f, 24.0f);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		return _NextPos + float4(0.0f, -0.0f);
	}

	return float4::ZERO;
}

// ������ �ʰ� �� Ű�� ������� True
bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_RIGHT) &&
		false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_UP) &&
		false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_DOWN)
		)
	{
		return false;
	}

	return true;
}

// ������ �� Ű�� ������� True
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_RIGHT) &&
		false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_UP) &&
		false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_DOWN)
		)
	{
		return false;
	}

	return true;
}

// ������ �ִ� Ű�� ������� True
bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT) &&
		false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP) &&
		false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN)
		)
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������� True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		return false;
	}

	return true;
}


void Player::CreatePlayerTileIndex(float4 _Pos, std::string _TileMapImageName)
{
	int PosX = static_cast<int>(_Pos.x / TILEMAP_SIZE);
	int PosY = static_cast<int>(_Pos.y / TILEMAP_SIZE);

	if (IMAGE_TILESET_DIRTWATERY == _TileMapImageName)
	{
		if (nullptr != AllTiles_[PosY][PosX] 
			&& AllTiles_[PosY][PosX]->GetTileState() == (int)TileState::Hollow)
		{
			// Ÿ�� ����
			SetTile(PosX, PosY,
				TileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, _TileMapImageName, 0, (int)ORDER::FRONTA), (int)TileState::Hollow);
		}
		else
		{
			return;
		}
	}
	else
	{
		// Ÿ�� ����
		SetTile(PosX, PosY,
			TileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, _TileMapImageName, 0, (int)ORDER::FRONTA), (int)TileState::Hollow);
	}
}

void Player::SetTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState)
{
	AllTiles_[y][x] = _TileMap;
	AllTiles_[y][x]->SetTileState_(_TileState);
}