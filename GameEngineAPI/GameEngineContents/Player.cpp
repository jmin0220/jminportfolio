#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
#include "ItemTable.h"
#include "Item.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <vector>
#include <cstring>

float4 Player::NextLevelPos_ = { 3200.0f, 820.0f };

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
	// 인벤토리 초기설정
	Inventory_->AddItemToInventory((int)ITEMTABLE::HOE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::AXE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);

	Inventory_->InventoryInit();
}

void Player::Start()
{
	// UI
	Inventory_ = this->GetLevel()->CreateActor<Inventory>((int)ORDER::UI);
	Mouse_ = this->GetLevel()->CreateActor<Mouse>((int)ORDER::UIMOUSE);
	Clock_ = this->GetLevel()->CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = this->GetLevel()->CreateActor<EnergyBar>((int)ORDER::UI);

	// 애니메이션 초기화
	PlayerAnimationInit();
	// 키설정 초기화
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

	// 1줄에 6개의 스프라이트
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

// 애니메이션 전환
void Player::PlayerAnimationChange(const std::string& _Name)
{
	RendererBody_->ChangeAnimation(_Name);
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
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		CurrentLevelH = MAP_BEACH_SIZE_H;
		CurrentLevelW = MAP_BEACH_SIZE_W;
	}

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
	// 컬리전맵 취득
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
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	// 왼쪽
	float4 CheckPos = { GetPosition().x - (TILEMAP_SIZE), GetPosition().y };
	int Color = MapColImage_->GetImagePixel(CheckPos);

	// 충돌판정
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// 오른쪽
	CheckPos = { GetPosition().x + (TILEMAP_SIZE), GetPosition().y };
	Color = MapColImage_->GetImagePixel(CheckPos);

	// 충돌판정
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// 위
	CheckPos = { GetPosition().x, GetPosition().y - ((TILEMAP_SIZE) / 2) };
	Color = MapColImage_->GetImagePixel(CheckPos);

	// 충돌판정
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// 아래
	CheckPos = { GetPosition().x, GetPosition().y + ((TILEMAP_SIZE) / 2) };
	Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// 플레이어의 위치
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

// 충돌체크
void Player::ColWallCheck(float4 _MoveDir)
{
	// MoveDir은 오직 이동중에서만 갱신됨.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

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
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_BEACH_COLLISION);
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	float4 NextPos = GetPosition() + CheckLength;
	float4 CheckPos = SetCheckPos(NextPos);

	int Color = MapColImage_->GetImagePixel(CheckPos);
	
	// 충돌판정
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}


	if (GetCurrentLevel() == LEVEL_FARM)
	{
		// 타운으로 이동
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 200.0f, 2600.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
		else if (RGB(0, 255, 0) == Color)
		{
			// 안할수도
			//SetNextLevelPos({ MAP_FARMBUILDING_SIZE_W / 2, MAP_FARMBUILDING_SIZE_H / 2 });
			//GameEngine::GetInst().ChangeLevel(LEVEL_FARMBUILDING);
		}
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		// 타운으로 이동
		if (RGB(255, 0, 0) == Color)
		{
			// 농장으로 이동
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
		// 농장으로 이동
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


void Player::CreatePlayerTileIndex(float4 _Pos, std::string _TileMapImageName)
{
	int PosX = static_cast<int>(_Pos.x / TILEMAP_SIZE);
	int PosY = static_cast<int>(_Pos.y / TILEMAP_SIZE);

	if (IMAGE_TILESET_DIRTWATERY == _TileMapImageName)
	{
		if (nullptr != AllTiles_[PosY][PosX] 
			&& AllTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::Hollow)
		{
			// 타일 생성
			SetTile(PosX, PosY,
				TileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, _TileMapImageName, 0, (int)ORDER::FRONTA), (int)TILESTATE::Hollow);
		}
		else
		{
			return;
		}
	}
	else
	{
		// 타일 생성
		SetTile(PosX, PosY,
			TileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, _TileMapImageName, 0, (int)ORDER::FRONTA), (int)TILESTATE::Hollow);
	}
}

void Player::SetTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState)
{
	AllTiles_[y][x] = _TileMap;
	AllTiles_[y][x]->SetTileState_(_TileState);
}
