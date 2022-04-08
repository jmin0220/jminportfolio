#include "Player.h"
#include "PlayLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <vector>

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

	int directionDown = 0;
	int directionRight = 27;
	int directionLeft = 54;
	int directionUp = 81;

	// �÷��̾� ĳ���� ������
	RendererBody_ = CreateRenderer((int)ORDER::PLAYER);
	RendererLegs_ = CreateRenderer((int)ORDER::PLAYER);
	RendererCloth_ = CreateRenderer((int)ORDER::PLAYER);
	RendererHair_ = CreateRenderer((int)ORDER::PLAYER);
	RendererArms_ = CreateRenderer((int)ORDER::PLAYER);

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
	// Idle
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_RIGHT, 8, 8, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_LEFT, 16, 16, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_UP, 24, 24, 0.0f, false);
	// Walk
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_DOWN, 0, 0, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_RIGHT, 8, 8, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_LEFT, 16, 16, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_WALK_UP, 24, 24, 0.0f, false);

	// Cloth
	// Idel
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_RIGHT, 16, 16, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_LEFT, 32, 32, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_UP, 48, 48, 0.0f, false);
	// Walk
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_DOWN, 0, 0, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_RIGHT, 16, 16, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_LEFT, 32, 32, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_WALK_UP, 48, 48, 0.0f, false);

	// �ʱ� �ִϸ��̼�
	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);

}

// �ִϸ��̼� ��ȯ
void Player::PlayerAnimationChange(const std::string& _Name)
{
	RendererBody_->ChangeAnimation(_Name);
	RendererLegs_->ChangeAnimation(_Name);
	RendererHair_->ChangeAnimation(_Name);
	RendererCloth_->ChangeAnimation(_Name);
	RendererArms_->ChangeAnimation(_Name);
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
	float4 CheckLengthLeft = {GetPosition().x - (TILEMAP_SIZE), GetPosition().y};
	float4 CheckLengthRight = { GetPosition().x + (TILEMAP_SIZE), GetPosition().y };

	// �ø����� ���
	if (GetCurrentLevel() == LEVEL_FARM)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARM_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_TOWN_RENDER_ORDER_COLLISION);
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}

	// ����
	float4 CheckPos = CheckLengthLeft + float4(0.0f, 48.0f);
	int Color = MapColImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// ������
	CheckPos = CheckLengthRight + float4(0.0f, 20.0f);
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
	float4 MoveDir = _MoveDir;
	float4 CheckLength = MoveDir * GameEngineTime::GetDeltaTime() * Speed_;

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

	float4 NextPos = GetPosition() + CheckLength;
	float4 CheckPos = NextPos + float4(0.0f, 20.0f);

	int Color = MapColImage_->GetImagePixel(CheckPos);
	
	// �浹����
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
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