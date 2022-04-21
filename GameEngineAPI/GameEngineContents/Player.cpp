#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
#include "ItemTable.h"
#include "Item.h"
#include "Parsnip.h"
#include "Oaktree.h"
#include "Potato.h"
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
int Player::Gold_ = 1234560;

Player::Player() 
	:Speed_(500.0f)
	, MoveDir_(float4::DOWN)
	, NextLevel_("")
	, InventoryClickFlg_(false)
	, ItemSelectOrigin(-1)
	, ItemSelectTarget(-1)
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
	Inventory_->AddItemToInventory((int)ITEMTABLE::PARSNIP);
	Inventory_->AddItemToInventory((int)ITEMTABLE::OAKTREE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
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

	// 플레이어의 충돌체 생성
	SetCollision(CreateCollision(COL_GROUP_PLAYER, { PLAYER_COL_SIZE, PLAYER_COL_SIZE }));
	SetActionCollision(CreateCollision(COL_GROUP_PLAYER_ACTION, { PLAYER_ACTION_COL_SIZE, PLAYER_ACTION_COL_SIZE }, { PLAYER_ACTION_COL_LENG, 0.0f}));
	GetActionCollision()->Off();
}

void Player::Update()
{
	Clock_->SetGold(Gold_);

	// 카메라 갱신
	UpdateCamera();

	// 마우스 클릭 이벤트
	ControlInventorySelectBoxWithMouse();

	// 농작물 업데이트
	CropsUpdate();

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


void Player::SetCropsActorSize(int _X, int _Y)
{
	EnvironmentActor_.resize(_Y);

	for (size_t y = 0; y < EnvironmentActor_.size(); y++)
	{
		EnvironmentActor_[y].resize(_X);

		for (size_t x = 0; x < EnvironmentActor_[y].size(); x++)
		{
			EnvironmentActor_[y][x] = nullptr;
		}
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
			// 마우스가 인벤토리 바와 겹쳐있을 경우 상태를 Action으로 변경하지 않음
			if (InventoryClickFlg_ == true || 
				(false == Inventory_->GetExtendFlg()
				&& true == Mouse_->GetCollision()->CollisionCheck(COL_GROUP_INVENTORY_BAR, CollisionType::Rect, CollisionType::Rect)))
			{
				return;
			}
			else if(InventoryClickFlg_ == true || 
				(true == Inventory_->GetExtendFlg()
				&&true == Mouse_->GetCollision()->CollisionCheck(COL_GROUP_INVENTORY_EXTEND_BAR, CollisionType::Rect, CollisionType::Rect)))
			{
				return;
			}
			else
			{
				ActionStart();
			}
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
void Player::ColCheck(float4 _MoveDir)
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
	if (RGB(0, 0, 0) != Color 
		&& !PlayerCollision_->NextPostCollisionCheck(COL_GROUP_CROPS, CheckLength, CollisionType::Rect, CollisionType::Rect)
		&& !PlayerCollision_->NextPostCollisionCheck(COL_GROUP_TREES, CheckLength, CollisionType::Rect, CollisionType::Rect))
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

// 액션키가 눌릴경우 True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

// 액션키가 눌리고 있을 경우
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

// 액션키가 떨어진 경우
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

void Player::CropsUpdate()
{
	for (std::vector<Crops*> Actors : EnvironmentActor_)
	{
		for (Crops* Actor_ : Actors)
		{
			// 플레이어의 위치에 따라서 렌더링 순서를 변경
			if (nullptr != Actor_
				&& Actor_->GetPosition().iy() >= GetPosition().y)
			{
				Actor_->GetRenderer()->SetOrder((int)ORDER::FRONTB);
			}
			else if (nullptr != Actor_
				&& Actor_->GetPosition().iy() < GetPosition().y)
			{
				Actor_->GetRenderer()->SetOrder((int)ORDER::FRONTA);
			}
				

			// 시간 관련 업데이트
			// 타일이 업데이트 활성화 상태일경우
			if ( nullptr != Actor_ && Actor_->GetIsTimeUpdate() )
			{
				Actor_->AddAccTime(GameEngineTime::GetDeltaTime());

				// 5초가 지났을 경우
				// && 땅타일이 HollowWet인 경우
				if (Actor_->GetAccTime() >= 5.0f
					// 생성시에 조정된 타일을 다시 되돌리기 위해 - TILEMAP_SIZE / 2만큼 조정
					&& GroundTiles_[(Actor_->GetPosition().iy() - TILEMAP_SIZE / 2) / TILEMAP_SIZE][(Actor_->GetPosition().ix() - TILEMAP_SIZE / 2) / TILEMAP_SIZE]->GetTileState() == (int)TILESTATE::HOLLOWWET)
				{
					// 1번 성장
					Actor_->SetGrowLevel(Actor_->GetGrowLevel() + 1);
					Actor_->GetRenderer()->SetIndex(Actor_->GetGrowLevel());
					Actor_->ReSetAccTime();

					// 설정한 최대 레벨에 도달했을 경우 시간 업데이트 끄기
					if (Actor_->GetGrowLevel() >= Actor_->GetMaxLevel())
					{
						Actor_->SetGrowLevel(Actor_->GetMaxLevel());
						Actor_->SetIsTimeUpdate(false);
					}
				}
				else if (Actor_->GetAccTime() >= 5.0f)
				{
					Actor_->ReSetAccTime();
				}
			}
		}
	}
}

// 마우스로 인벤토리 조작하기
void Player::ControlInventorySelectBoxWithMouse()
{
	if (true == IsActionKeyDown()
		&& Mouse_->GetCollision()->CollisionResult(COL_GROUP_INVENTORY_BOX, MouseColResult_, CollisionType::Rect, CollisionType::Rect))
	{
		std::vector<GameEngineCollision*>::iterator StartIter = MouseColResult_.begin();
		std::vector<GameEngineCollision*>::iterator EndIter = MouseColResult_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			for (size_t i = 0; i < 12; i++)
			{
				if (Inventory_->GetInventoryNormalCol()[i] == *StartIter)
				{
					ItemSelectOrigin = i;
					Inventory_->GetInventoryList()[i]->ClickedFlg = true;

					break;
				}
			}
		}

		InventoryClickFlg_ = true;
		// 충돌 결과 초기화
		MouseColResult_.clear();
	}

	// 기존에 아이템이 선택되어있으면서 마우스를 누르고 있는 상태
	if (true == IsActionKeyPress() && ItemSelectOrigin != -1)
	{
		// 아이템을 마우스에 따라다니도록 이동
		Inventory_->GetInventoryList()[ItemSelectOrigin]->GetIconRenderer().SetPivot(Mouse_->GetPosition());
	}


	if (true == IsActionKeyUp() 
		&& ItemSelectOrigin != -1
		&& Mouse_->GetCollision()->CollisionResult(COL_GROUP_INVENTORY_BOX, MouseColResult_, CollisionType::Rect, CollisionType::Rect))
	{
		// Collision배열에서 Collision의 순서는 실제 인벤토리의 아이템 순서와 항상 동일함.
		// 인벤토리 1칸은 충돌체 1칸이고, 충돌한 충돌체의 정보를 알아낼 수 있음.
		// 마우스와 충돌체가 충돌한 시점에서 가져온 충돌체의 정보를 비교하여,
		// 0번부터 12번까지 검색해서 마우스와 충돌한 충돌체와 동일한 충돌체를 가지고 있는 
		// Item의 번호로 SetItem함수를 호출함.
		std::vector<GameEngineCollision*>::iterator StartIter = MouseColResult_.begin();
		std::vector<GameEngineCollision*>::iterator EndIter = MouseColResult_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			for (size_t i = 0; i < 12; i++)
			{
				if (Inventory_->GetInventoryNormalCol()[i] == *StartIter)
				{
					ItemSelectTarget = i;

					if (ItemSelectOrigin == ItemSelectTarget)
					{
						Inventory_->SelectItem(i);
						Inventory_->GetInventoryList()[i]->ClickedFlg = false;
					}
					else if (ItemSelectOrigin != ItemSelectTarget)
					{
						Inventory_->SwapItem(ItemSelectOrigin, ItemSelectTarget);
						Inventory_->SelectItem(ItemSelectTarget);
					}

					// 충돌 결과 초기화
					MouseColResult_.clear();
					Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
					Inventory_->GetInventoryList()[ItemSelectTarget]->ClickedFlg = false;
					ItemSelectOrigin = -1, ItemSelectTarget = -1;

					return;
				}
			}
		}
	}
	else if (true == IsActionKeyUp())
	{
		Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
		InventoryClickFlg_ = false;
	}
}

// 타일맵 생성
void Player::CreatePlayerTileIndex(float4 _Pos, int _EnvironemntTileIndex)
{
	int PosX = static_cast<int>(_Pos.x / TILEMAP_SIZE);
	int PosY = static_cast<int>(_Pos.y / TILEMAP_SIZE);

	switch (_EnvironemntTileIndex)
	{
	case (int)TILESTATE::NONE:
		break;
	case (int)TILESTATE::HOLLOW:
		SetGroundTile(PosX, PosY,
			LevelTileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, IMAGE_TILESET_DIRT, 0, (int)ORDER::FRONTA), (int)TILESTATE::HOLLOW);
		break;
	case (int)TILESTATE::HOLLOWWET:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOW)
		{
			// 타일 생성
			SetGroundTile(PosX, PosY,
				LevelTileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, IMAGE_TILESET_DIRTWATERED, 0, (int)ORDER::FRONTA), (int)TILESTATE::HOLLOWWET);
		}

		break;
	case (int)TILESTATE::OAKTREE:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{
			// Crop 생성
			SetCropsActor(PosX, PosY, (int)TILESTATE::HOLLOWWET, static_cast<Crops*>(GetLevel()->CreateActor<Oaktree>()), COL_GROUP_TREES, 4);
		}

		break;
	case (int)TILESTATE::MAPLETREE:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{

		}

		break;
	case (int)TILESTATE::PINETREE:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{

		}

		break;
	case (int)TILESTATE::PARSNIP:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{
			// Crop 생성
			SetCropsActor(PosX, PosY,(int)TILESTATE::HOLLOWWET, static_cast<Crops*>(GetLevel()->CreateActor<Parsnip>()), COL_GROUP_CROPS, 5);
		}

		break;
	case (int)TILESTATE::POTATO:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{

		}

		break;
	case (int)TILESTATE::CORN:

		if (nullptr != GroundTiles_[PosY][PosX]
			&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOWWET)
		{

		}

		break;
	default:
		break;
	}

}

// 생성한 타일맵 정보를 플레이어에게 저장
void Player::SetGroundTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState)
{
	GroundTiles_[y][x] = _TileMap;
	GroundTiles_[y][x]->SetTileState(_TileState);
}

void Player::SetCropsActor(int x, int y, int _CropState, Crops* _CropActor, std::string _ColGroup, int _MaxLevel /* = 0 */)
{
	// 해당 위치가 비어있을때만 생성
	if (nullptr == EnvironmentActor_[y][x])
	{
		EnvironmentActor_[y][x] = _CropActor;
		EnvironmentActor_[y][x]->SetCropState(_CropState);
		EnvironmentActor_[y][x]->SetGrowLevel(0);
		EnvironmentActor_[y][x]->SetMaxLevel(_MaxLevel);
		EnvironmentActor_[y][x]->ReSetAccTime();
		EnvironmentActor_[y][x]->SetIsTimeUpdate(true);
		// 타일의 중앙으로 위치를 맞추기위해 TILEMAP_SIZE / 2만큼 조정
		EnvironmentActor_[y][x]->SetPosition({ static_cast<float>(x * TILEMAP_SIZE + TILEMAP_SIZE / 2), static_cast<float>(y * TILEMAP_SIZE + TILEMAP_SIZE / 2) });
		EnvironmentActor_[y][x]->CreateCollision(_ColGroup, { TILEMAP_SIZE - 18, TILEMAP_SIZE - 18 });
	}
}