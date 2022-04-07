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


	// 카메라 위치 초기화
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// 카메라 갱신
	UpdateCamera();

	// 상태 업데이트
	StateUpdate();
}

// 상태 업데이트
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

// 상태 변경
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

// 애니메이션 초기화
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

	// 플레이어 캐릭터 렌더링
	RendererBody_ = CreateRenderer((int)ORDER::PLAYER);
	RendererLegs_ = CreateRenderer((int)ORDER::PLAYER);
	RendererCloth_ = CreateRenderer((int)ORDER::PLAYER);
	RendererHair_ = CreateRenderer((int)ORDER::PLAYER);
	RendererArms_ = CreateRenderer((int)ORDER::PLAYER);

	RendererCloth_->SetPivot(ClothPos_);

	/*
	IMAGE_PLAYER_MAN_BODY파일
	7 / 7 / 6 / 7 = 1줄에 27스프라이트로 구성.
	*/

	// Idle
	// 몸통
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);
	// 팔
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 7 + directionDown, 7 + directionDown, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 7 + directionRight, 7 + directionRight, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 7 + directionLeft, 7 + directionLeft, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 7 + directionUp, 7 + directionUp, 0.2f, false);
	// 다리
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 20 + directionDown, 20 + directionDown, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 20 + directionRight, 20 + directionRight, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 20 + directionLeft, 20 + directionLeft, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 20 + directionUp, 20 + directionUp, 0.2f, false);

	// Walk
	// 몸
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 0 + directionDown, 3 + directionDown, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 0 + directionRight, 3 + directionRight, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 0 + directionLeft, 3 + directionLeft, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 0 + directionUp, 3 + directionUp, 0.2f, true);
	// 팔
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 7 + directionDown, 10 + directionDown, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 7 + directionRight, 10 + directionRight, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 7 + directionLeft, 10 + directionLeft, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 7 + directionUp, 10 + directionUp, 0.2f, true);
	// 다리
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 20 + directionDown, 23 + directionDown, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 20 + directionRight, 23 + directionRight, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 20 + directionLeft, 23 + directionLeft, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 20 + directionUp, 23 + directionUp, 0.2f, true);

	// 세로로 휘두르기
	// 몸통
	// 16라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	//// 11라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	//// 12라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	//// 9라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);

	//// 팔
	//// 다리


	//// 가로로 휘두르기
	//// 몸통
	//// 6라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	//// 7라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	//// 8라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	//// 9라인
	//RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);

	// 팔
	// 다리



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

	// 초기 애니메이션
	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);

}

// 애니메이션 전환
void Player::PlayerAnimationChange(const std::string& _Name)
{
	RendererBody_->ChangeAnimation(_Name);
	RendererLegs_->ChangeAnimation(_Name);
	RendererHair_->ChangeAnimation(_Name);
	RendererCloth_->ChangeAnimation(_Name);
	RendererArms_->ChangeAnimation(_Name);
}

// 조작키 초기화
void Player::PlayerKeyInit()
{
	// 키설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, 'D');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_DOWN, 'S');

		// 왼클릭했을때의 상호작용
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}
}

// 카메라 이동
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

	// 플레이어의 위치에 맞춰서 카메라 이동
	// 플레이어가 카메라가 움직이는 범위 안에 있을경우 카메라 좌표 갱신
	//if ((GetPosition().iy() >= GameEngineWindow::GetInst().GetScale().Half().iy()
	//	&& GetPosition().iy() <= CurrentLevelH - GameEngineWindow::GetInst().GetScale().Half().iy()))
	//{
	//	CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy();
	//}
	//if ((GetPosition().ix() >= GameEngineWindow::GetInst().GetScale().Half().ix()
	//	&& GetPosition().ix() <= CurrentLevelW - GameEngineWindow::GetInst().GetScale().Half().ix()))
	//{
	//	CameraPos_.x = GetPosition().ix() - GameEngineWindow::GetInst().GetScale().Half().ix();
	//}

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	// 카메라가 맵 범위를 벗어났을경우 재위치
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

	// 카메라 위치 갱신
	GetLevel()->SetCameraPos(CameraPos_);
}

// 플레이어의 위치에 따라서 Front맵의 렌더링 순서를 유동적으로 변경
bool Player::ColRenderOrderCheck()
{
	float4 CheckLengthLeft = {GetPosition().x - (TILEMAP_SIZE), GetPosition().y};
	float4 CheckLengthRight = { GetPosition().x + (TILEMAP_SIZE), GetPosition().y };

	// 컬리전맵 취득
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
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	// 왼쪽
	float4 CheckPos = CheckLengthLeft + float4(0.0f, 48.0f);
	int Color = MapColImage_->GetImagePixel(CheckPos);

	// 충돌판정
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// 오른쪽
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

// 충돌체크
void Player::ColWallCheck(float4 _MoveDir)
{
	float4 MoveDir = _MoveDir;
	float4 CheckLength = MoveDir * GameEngineTime::GetDeltaTime() * Speed_;

	// 컬리전맵 취득
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
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	float4 NextPos = GetPosition() + CheckLength;
	float4 CheckPos = NextPos + float4(0.0f, 20.0f);

	int Color = MapColImage_->GetImagePixel(CheckPos);
	
	// 충돌판정
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (GetCurrentLevel() == LEVEL_FARM)
	{
		// 타운으로 이동
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
		// 타운으로 이동
		if (RGB(255, 0, 0) == Color)
		{
			// 농장으로 이동
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
		else if (RGB(0, 0, 255) == Color)
		{
			// GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
	}
	else if (GetCurrentLevel() == LEVEL_FARMBUILDING)
	{
		// 농장으로 이동
		if (RGB(255, 0, 0) == Color)
		{
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
	}
}

// 눌리지 않게 된 키가 있을경우 True
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

// 눌리게 된 키가 있을경우 True
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

// 눌리고 있는 키가 있을경우 True
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

// 액션키가 눌릴경우 True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		return false;
	}

	return true;
}