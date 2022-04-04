#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <vector>
#include "PlayLevel.h"
#include "HoeBasic.h"

Player::Player() 
	:Speed_(200.0f)
	, ClothPos_({0.0f, 9.0f})
{
}

Player::~Player() 
{
}

void Player::Start()
{
	PlayerAnimationInit();
	PlayerKeyInit();


	// ī�޶� ��ġ �ʱ�ȭ
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// ī�޶� ����
	UpdateCamera();

	// Ű �Է�
	PlayerControl();

}

// ������
void Player::Render()
{
	// DebugRectRender();

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");

	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�̹��� �ε� ����");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
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

	int directionDown = 0;
	int directionRight = 27;
	int directionLeft = 54;
	int directionUp = 81;

	// �÷��̾� ĳ���� ������
	RendererBody_ = CreateRenderer();
	RendererLegs_ = CreateRenderer();
	RendererCloth_ = CreateRenderer();
	RendererHair_ = CreateRenderer();
	RendererArms_ = CreateRenderer();

	RendererCloth_->SetPivot(ClothPos_);

	/*
	IMAGE_PLAYER_MAN_BODY����
	7 / 7 / 6 / 7 = 1�ٿ� 27��������Ʈ�� ����.
	*/

	// Idle
	// ����
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);
	// ��
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 7 + directionDown, 7 + directionDown, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 7 + directionRight, 7 + directionRight, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 7 + directionLeft, 7 + directionLeft, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 7 + directionUp, 7 + directionUp, 0.2f, false);
	// �ٸ�
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 20 + directionDown, 20 + directionDown, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 20 + directionRight, 20 + directionRight, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 20 + directionLeft, 20 + directionLeft, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 20 + directionUp, 20 + directionUp, 0.2f, false);

	// Walk
	// ��
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 0 + directionDown, 3 + directionDown, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 0 + directionRight, 3 + directionRight, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 0 + directionLeft, 3 + directionLeft, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 0 + directionUp, 3 + directionUp, 0.2f, true);
	// ��
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 7 + directionDown, 10 + directionDown, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 7 + directionRight, 10 + directionRight, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 7 + directionLeft, 10 + directionLeft, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 7 + directionUp, 10 + directionUp, 0.2f, true);
	// �ٸ�
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 20 + directionDown, 23 + directionDown, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 20 + directionRight, 23 + directionRight, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 20 + directionLeft, 23 + directionLeft, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 20 + directionUp, 23 + directionUp, 0.2f, true);

	// ���η� �ֵθ���
	// ����
	// 16����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	//// 11����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	//// 12����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	//// 9����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);

	//// ��
	//// �ٸ�


	//// ���η� �ֵθ���
	//// ����
	//// 6����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	//// 7����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	//// 8����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	//// 9����
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);

	// ��
	// �ٸ�



	// Hair
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_RIGHT, 8, 8, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_LEFT, 16, 16, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_UP, 24, 24, 0.0f, false);

	// Cloth
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_RIGHT, 16, 16, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_LEFT, 32, 32, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_UP, 48, 48, 0.0f, false);

	// �ʱ� �ִϸ��̼�
	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);

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

// Ű�Է�
void Player::PlayerControl()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		//HoeBasic* Ptr = GetLevel()->CreateActor<HoeBasic>();
		//Ptr->SetPosition(GetPosition());
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_RIGHT))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererArms_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_RIGHT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_RIGHT);

			ColWallCheck(float4::ZERO);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_LEFT))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererArms_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_LEFT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_LEFT);

			ColWallCheck(float4::ZERO);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_UP))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_UP);
			RendererArms_->ChangeAnimation(ANIM_IDLE_UP);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_UP);

			RendererHair_->ChangeAnimation(ANIM_IDLE_UP);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_UP);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_DOWN))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);

			RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);

			ColWallCheck(float4::ZERO);
		}


		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_RIGHT);
			RendererArms_->ChangeAnimation(ANIM_WALK_RIGHT);
			RendererLegs_->ChangeAnimation(ANIM_WALK_RIGHT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_RIGHT);

			ColWallCheck(float4::RIGHT);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_LEFT);
			RendererArms_->ChangeAnimation(ANIM_WALK_LEFT);
			RendererLegs_->ChangeAnimation(ANIM_WALK_LEFT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_LEFT);

			ColWallCheck(float4::LEFT);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_UP);
			RendererArms_->ChangeAnimation(ANIM_WALK_UP);
			RendererLegs_->ChangeAnimation(ANIM_WALK_UP);

			RendererHair_->ChangeAnimation(ANIM_IDLE_UP);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_UP);

			ColWallCheck(float4::UP);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_DOWN);
			RendererArms_->ChangeAnimation(ANIM_WALK_DOWN);
			RendererLegs_->ChangeAnimation(ANIM_WALK_DOWN);

			RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);

			ColWallCheck(float4::DOWN);
		}
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

	// �÷��̾��� ��ġ�� ���缭 ī�޶� �̵�
	// �÷��̾ ī�޶� �����̴� ���� �ȿ� ������� ī�޶� ��ǥ ����
	if ((GetPosition().iy() >= GameEngineWindow::GetInst().GetScale().Half().iy()
		&& GetPosition().iy() <= CurrentLevelH - GameEngineWindow::GetInst().GetScale().Half().iy()))
	{
		CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy();
	}

	if ((GetPosition().ix() >= GameEngineWindow::GetInst().GetScale().Half().ix()
		&& GetPosition().ix() <= CurrentLevelW - GameEngineWindow::GetInst().GetScale().Half().ix()))
	{
		CameraPos_.x = GetPosition().ix() - GameEngineWindow::GetInst().GetScale().Half().ix();
	}

	// ī�޶� ��ġ ����
	GetLevel()->SetCameraPos(CameraPos_);
}

void Player::ColWallCheck(float4 _MoveDir)
{
	float4 MoveDir_ = _MoveDir;

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

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = NextPos + float4(0.0f, 20.0f);

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
			GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
		else if (RGB(0, 255, 0) == Color)
		{
			GameEngine::GetInst().ChangeLevel(LEVEL_FARMBUILDING);
		}
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		// Ÿ������ �̵�
		if (RGB(255, 0, 0) == Color)
		{
			// �������� �̵�
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
		else if (RGB(0, 0, 255) == Color)
		{
			// GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
	}
	else if (GetCurrentLevel() == LEVEL_FARMBUILDING)
	{
		// �������� �̵�
		if (RGB(255, 0, 0) == Color)
		{
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
	}
}