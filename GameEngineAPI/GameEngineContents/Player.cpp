#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
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

#pragma region Crops
#include "ItemTable.h"
#include "Oaktree.h"
#include "Pinetree.h"
#include "Mapletree.h"
#include "Parsnip.h"
#include "Couliflower.h"
#include "Garlic.h"
#include "Rhubarb.h"
#include "Tomato.h"
#include "Hotpepper.h"
#include "Radish.h"
#include "Starfruit.h"
#include "Eggplant.h"
#include "Pumpkin.h"
#include "Yam.h"
#include "Beet.h"
#include "Sunflower.h"
#include "Greenbean.h"
#include "Potato.h"
#include "Kale.h"
#include "Melon.h"
#include "Blueberry.h"
#include "Redcabbage.h"
#include "Corn.h"
#pragma endregion Crops

#include "MineObject.h"
#include "Diamond.h"
#include "Ruby.h"
#include "Jade.h"
#include "Amethyst.h"
#include "Topaz.h"

float4 Player::NextLevelPos_ = { 3200.0f, 820.0f };
int Player::Gold_ = 1234560;

Player::Player()
	:Speed_(300.0f)
	, MoveDir_(float4::DOWN)
	, NextLevel_("")
	, InventoryClickFlg_(false)
	, ItemSelectOrigin(-1)
	, ItemSelectTarget(-1)
	, FishingGameFlg(false)
{
	PlayerRandom_ = new GameEngineRandom();
}

Player::~Player()
{
	delete PlayerRandom_;
	PlayerRandom_ = nullptr;
}

void Player::PlayerInit()
{
	// �κ��丮 �ʱ⼳��
	Inventory_->AddItemToInventory((int)ITEMTABLE::HOE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::WATERINGCAN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::AXE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::PICKAXE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::FISHINGROD);
	Inventory_->AddItemToInventory((int)ITEMTABLE::OAKTREE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::PINETREE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::KALE);
	Inventory_->AddItemToInventory((int)ITEMTABLE::PUMPKIN);
	Inventory_->AddItemToInventory((int)ITEMTABLE::GARLIC);
	Inventory_->AddItemToInventory((int)ITEMTABLE::RHUBARB);
	Inventory_->AddItemToInventory((int)ITEMTABLE::TOMATO);
	Inventory_->AddItemToInventory((int)ITEMTABLE::HOTPEPPER);
	Inventory_->AddItemToInventory((int)ITEMTABLE::RADISH);
	Inventory_->AddItemToInventory((int)ITEMTABLE::STARFRUIT);
	Inventory_->AddItemToInventory((int)ITEMTABLE::YAM);

	Inventory_->InventoryInit();
}

void Player::Start()
{
	// UI
	Inventory_ = this->GetLevel()->CreateActor<Inventory>((int)ORDER::UI);
	Mouse_ = this->GetLevel()->CreateActor<Mouse>((int)ORDER::UIMOUSE);
	Clock_ = this->GetLevel()->CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = this->GetLevel()->CreateActor<EnergyBar>((int)ORDER::UI);
	FishingGame_ = this->GetLevel()->CreateActor<FishingGame>((int)ORDER::UI);

	// �ִϸ��̼� �ʱ�ȭ
	PlayerAnimationInit();
	// Ű���� �ʱ�ȭ
	PlayerKeyInit();
	// ī�޶� ��ġ �ʱ�ȭ
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	// ������ ���͸� ����
	GetLevel()->RegistActor(ACTOR_PLAYER, this);
	GetLevel()->RegistActor(ACTOR_MOUSE, Mouse_);
	GetLevel()->RegistActor(ACTOR_INVENTORY, Inventory_);

	// YSort�ѱ�
	GetLevel()->YSortOn((int)ORDER::PLAYER);

	// �÷��̾��� �浹ü ����
	SetCollision(CreateCollision(COL_GROUP_PLAYER, { PLAYER_COL_SIZE, PLAYER_COL_SIZE }));
}

void Player::Update()
{
	Clock_->SetGold(Gold_);

	// ī�޶� ����
	UpdateCamera();

	// �κ��丮&���콺 �̺�Ʈ
	ControlInventorySelectBoxWithMouse();

	// ���۹� ������Ʈ
	CropsUpdate();

	// ������ ������Ʈ
	ItemUpdate();

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
	case PlayerState::Fishing:
		FishingUpdate();
		break;
	case PlayerState::Shop:
		ShopUpdate();
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
			// ���콺�� �κ��丮 �ٿ� �������� ��� ���¸� Action���� �������� ����
			if (InventoryClickFlg_ == true ||
				(false == Inventory_->GetExtendFlg()
					&& true == Mouse_->GetCollision()->CollisionCheck(COL_GROUP_INVENTORY_BAR, CollisionType::Rect, CollisionType::Rect))
				|| (true == Inventory_->GetExtendFlg()
					&& true == Mouse_->GetCollision()->CollisionCheck(COL_GROUP_INVENTORY_EXTEND_BAR, CollisionType::Rect, CollisionType::Rect)))
			{
				return;
			}
			else
			{
				ActionStart();
			}
			break;
		case PlayerState::Fishing:
			FishingStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Shop:
			ShopStart();
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

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_RIGHT, 4 * oneline, 4 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_LEFT, 5 * oneline, 5 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_DOWN, 6 * oneline, 6 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_HIT_HORIZON_UP, 7 * oneline, 7 * oneline + 3, 0.1f, true);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WATERING_RIGHT, 8 * oneline, 8 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WATERING_LEFT, 9 * oneline, 9 * oneline + 4, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WATERING_DOWN, 10 * oneline, 10 * oneline + 3, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_WATERING_UP, 11 * oneline, 11 * oneline + 3, 0.1f, true);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_DOWN, 12 * oneline, 12 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_RIGHT, 13 * oneline, 13 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_LEFT, 14 * oneline, 14 * oneline + 5, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_UP, 15 * oneline, 15 * oneline + 5, 0.1f, true);

	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_DOWN_WAIT, 12 * oneline, 12 * oneline, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_RIGHT_WAIT, 13 * oneline, 13 * oneline, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_LEFT_WAIT, 14 * oneline, 14 * oneline, 0.1f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_TOTAL, ANIM_FISHING_UP_WAIT, 15 * oneline, 15 * oneline, 0.1f, true);

	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);


	// ��� ������ �� �ִϸ��̼� ����
	RendererTool_ = CreateRenderer(IMAGE_TOOL_ANIM, (int)ORDER::TOOLB);
	RendererTool_->SetPivot({ 0.0f, -24.0f, });

	// ����, �ƹ��͵� ���� ĭ�� ����Ŵ
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_IDLE, 5, 5, 0.2f, false);

	// ���
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_HOE_RIGHT, 0, 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_HOE_LEFT, 1 * oneline, 1 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_HOE_DOWN, 2 * oneline, 2 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_HOE_UP, 3 * oneline, 3 * oneline + 3, 0.1f, true);

	// ����
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_AXE_RIGHT, 4 * oneline, 4 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_AXE_LEFT, 5 * oneline, 5 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_AXE_DOWN, 6 * oneline, 6 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_AXE_UP, 7 * oneline, 7 * oneline + 3, 0.1f, true);

	// ���Ѹ���
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_WATERINGCAN_RIGHT, 8 * oneline, 8 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_WATERINGCAN_LEFT, 9 * oneline, 9 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_WATERINGCAN_DOWN, 10 * oneline, 10 * oneline + 3, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_WATERINGCAN_UP, 11 * oneline, 11 * oneline + 3, 0.1f, true);

	// ���˴�
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_UP, 12 * oneline, 12 * oneline + 5, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_RIGHT, 13 * oneline, 13 * oneline + 5, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_LEFT, 14 * oneline, 14 * oneline + 5, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_DOWN, 5, 5, 1.0f, true);

	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_WAIT_RIGHT, 15 * oneline, 15 * oneline, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_WAIT_LEFT, 15 * oneline + 1, 15 * oneline + 1, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_WAIT_DOWN, 12 * oneline, 12 * oneline, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_FISHING_WAIT_UP, 5, 5, 1.0f, true);

	// ���
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_PICKAXE_RIGHT, 16 * oneline, 16 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_PICKAXE_LEFT, 17 * oneline, 17 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_PICKAXE_DOWN, 18 * oneline, 18 * oneline + 4, 0.1f, true);
	RendererTool_->CreateAnimation(IMAGE_TOOL_ANIM, TOOL_ANIM_PICKAXE_UP, 19 * oneline, 19 * oneline + 3, 0.1f, true);

	// �ƹ��͵� ���� ���·� ����
	RendererTool_->ChangeAnimation(TOOL_ANIM_IDLE);

}

// �ִϸ��̼� ��ȯ
void Player::PlayerAnimationChange(const std::string& _Name)
{
	RendererBody_->ChangeAnimation(_Name);
}

void Player::ToolAnimationChange(const std::string& _Name)
{
	RendererTool_->ChangeAnimation(_Name);
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
	else if (GetCurrentLevel() == LEVEL_SEEDSHOP)
	{
		CurrentLevelH = MAP_SEEDSHOP_SIZE_H;
		CurrentLevelW = MAP_SEEDSHOP_SIZE_W;
	}
	else if (GetCurrentLevel() == LEVEL_MINES)
	{
		CurrentLevelH = MAP_MINES_SIZE_H;
		CurrentLevelW = MAP_MINES_SIZE_W;
	}
	else if (GetCurrentLevel() == LEVEL_CAVE1)
	{
		CurrentLevelH = MAP_CAVE1_SIZE_H;
		CurrentLevelW = MAP_CAVE1_SIZE_W;
	}
	else if (GetCurrentLevel() == LEVEL_CAVE2)
	{
		CurrentLevelH = MAP_CAVE2_SIZE_H;
		CurrentLevelW = MAP_CAVE2_SIZE_W;
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
	// �ø��� ���
	GetMapColImage();

	// ����
	float4 CheckPos = { GetPosition().x - (TILEMAP_SIZE), GetPosition().y };
	int Color = MapColOrderImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// ������
	CheckPos = { GetPosition().x + (TILEMAP_SIZE), GetPosition().y };
	Color = MapColOrderImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// ��
	CheckPos = { GetPosition().x, GetPosition().y - ((TILEMAP_SIZE) / 2) };
	Color = MapColOrderImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// �Ʒ�
	CheckPos = { GetPosition().x, GetPosition().y + ((TILEMAP_SIZE) / 2) };
	Color = MapColOrderImage_->GetImagePixel(CheckPos);

	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}

	// �÷��̾��� ��ġ
	CheckPos = GetPosition();
	Color = MapColOrderImage_->GetImagePixel(CheckPos);

	if (RGB(255, 0, 0) == Color)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float4 Player::GetPositionOnTilemap()
{
	float4 tmp;

	tmp.x = static_cast<int>(GetPosition().x / TILEMAP_SIZE);
	tmp.y = static_cast<int>(GetPosition().y / TILEMAP_SIZE);

	return tmp;
}

void Player::GetMapColImage()
{
	// �ø����� ���
	if (GetCurrentLevel() == LEVEL_FARM)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARM_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_FARM_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_TOWN_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_TOWN_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_BEACH)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_BEACH_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_BEACH_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_SEEDSHOP)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_SEEDSHOP_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_SEEDSHOP_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_MINES)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_MINES_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_MINES_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_CAVE1)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_CAVE1_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_CAVE1_RENDER_ORDER_COLLISION);
	}
	else if (GetCurrentLevel() == LEVEL_CAVE2)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find(MAP_CAVE2_COLLISION);
		MapColOrderImage_ = GameEngineImageManager::GetInst()->Find(MAP_CAVE2_RENDER_ORDER_COLLISION);
	}

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}
}

// �浹üũ
void Player::ColCheck(float4 _MoveDir)
{
	// MoveDir�� ���� �̵��߿����� ���ŵ�.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// �ø����� ���
	GetMapColImage();

	float4 NextPos = GetPosition() + CheckLength;
	float4 CheckPos = SetCheckPos(NextPos);

	int Color = MapColImage_->GetImagePixel(CheckPos);

	// �浹����
	if (RGB(0, 0, 0) != Color && RGB(0, 0, 255) != Color
		&& !PlayerCollision_->NextPosCollisionCheck(COL_GROUP_CROPS, CheckLength, CollisionType::Rect, CollisionType::Rect)
		&& !PlayerCollision_->NextPosCollisionCheck(COL_GROUP_TREES, CheckLength, CollisionType::Rect, CollisionType::Rect)
		&& !PlayerCollision_->NextPosCollisionCheck(COL_GROUP_MINES, CheckLength, CollisionType::Rect, CollisionType::Rect))
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
			SetNextLevelPos({ 890.0f, 610.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_MINES);
		}
	}
	else if (GetCurrentLevel() == LEVEL_TOWN)
	{
		// �������� �̵�
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 3730.0f, 850.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
		// �غ����� �̵�
		else if (RGB(0, 255, 0) == Color)
		{
			SetNextLevelPos({ 1870.0f, 50.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_BEACH);
		}
		// ���ѻ������� �̵�
		else if (RGB(255, 255, 0) == Color)
		{
			SetNextLevelPos({ 310.0f, 1314.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_SEEDSHOP);
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
	else if (GetCurrentLevel() == LEVEL_SEEDSHOP)
	{
		if (RGB(0, 255, 0) == Color)
		{
			SetNextLevelPos({ 2112.0f, 2778.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
		}
	}
	else if (GetCurrentLevel() == LEVEL_MINES)
	{
		if (RGB(0, 255, 0) == Color)
		{
			SetNextLevelPos({ 1653.0f, 450.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
		}
		if (RGB(0, 255, 255) == Color)
		{
			SetNextLevelPos({ 660.0f, 230.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_CAVE1);
		}
	}
	else if (GetCurrentLevel() == LEVEL_CAVE1)
	{
		if (RGB(0, 255, 255) == Color)
		{
			SetNextLevelPos({ 1125.0f, 410.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_MINES);
		}
		if (RGB(0, 255, 0) == Color)
		{
			SetNextLevelPos({ 215.0f, 267.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_CAVE2);
		}
	}
	else if (GetCurrentLevel() == LEVEL_CAVE2)
	{
		if (RGB(255, 0, 0) == Color)
		{
			SetNextLevelPos({ 910.0f, 320.0f });
			GameEngine::GetInst().ChangeLevel(LEVEL_CAVE1);
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

// �׼�Ű�� ������� True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������ ���� ���
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������ ���
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_INTERACT))
	{
		return false;
	}

	return true;
}

// ���۹� ���� �� �ı� ��
void Player::CropsUpdate()
{
	for (std::vector<Crops*> Actors : EnvironmentActor_)
	{
		for (Crops* Actor_ : Actors)
		{
			// �ð� ���� ������Ʈ
			// Ÿ���� ������Ʈ Ȱ��ȭ �����ϰ��
			if (nullptr != Actor_ && Actor_->GetIsTimeUpdate())
			{
				Actor_->AddAccTime(GameEngineTime::GetDeltaTime());

				// 5�ʰ� ������ ���
				// && ��Ÿ���� HollowWet�� ���
				if (Actor_->GetAccTime() >= 5.0f
					// �����ÿ� ������ Ÿ���� �ٽ� �ǵ����� ���� - TILEMAP_SIZE / 2��ŭ ����
					&& GroundTiles_[(Actor_->GetPosition().iy() - TILEMAP_SIZE / 2) / TILEMAP_SIZE][(Actor_->GetPosition().ix() - TILEMAP_SIZE / 2) / TILEMAP_SIZE]->GetTileState() == (int)TILESTATE::HOLLOWWET)
				{
					// 1�� ����
					Actor_->SetGrowLevel(Actor_->GetGrowLevel() + 1);
					Actor_->GetRenderer()->SetIndex(Actor_->GetCropsRenderIndex() + Actor_->GetGrowLevel());
					Actor_->ReSetAccTime();

					// ������ �ִ� ������ �������� ��� �ð� ������Ʈ ����
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

// ���콺�� �κ��丮 �����ϱ�
void Player::ControlInventorySelectBoxWithMouse()
{
	// �κ��丮�� ��ҵǾ�����
	if (false == Inventory_->GetExtendFlg())
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
			// �浹 ��� �ʱ�ȭ
			MouseColResult_.clear();
		}

		// ������ �������� ���õǾ������鼭 ���콺�� ������ �ִ� ����
		if (true == IsActionKeyPress() && ItemSelectOrigin != -1)
		{
			// �������� ���콺�� ����ٴϵ��� �̵�
			Inventory_->GetInventoryList()[ItemSelectOrigin]->GetIconRenderer().SetPivot(Mouse_->GetPosition());
		}


		if (true == IsActionKeyUp()
			&& ItemSelectOrigin != -1
			&& Mouse_->GetCollision()->CollisionResult(COL_GROUP_INVENTORY_BOX, MouseColResult_, CollisionType::Rect, CollisionType::Rect))
		{
			// Collision�迭���� Collision�� ������ ���� �κ��丮�� ������ ������ �׻� ������.
			// �κ��丮 1ĭ�� �浹ü 1ĭ�̰�, �浹�� �浹ü�� ������ �˾Ƴ� �� ����.
			// ���콺�� �浹ü�� �浹�� �������� ������ �浹ü�� ������ ���Ͽ�,
			// 0������ 12������ �˻��ؼ� ���콺�� �浹�� �浹ü�� ������ �浹ü�� ������ �ִ� 
			// Item�� ��ȣ�� SetItem�Լ��� ȣ����.
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

						// �浹 ��� �ʱ�ȭ
						MouseColResult_.clear();
						Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
						Inventory_->GetInventoryList()[ItemSelectTarget]->ClickedFlg = false;
						ItemSelectOrigin = -1, ItemSelectTarget = -1;

						InventoryClickFlg_ = false;

						return;
					}
				}
			}
		}
		else if (true == IsActionKeyUp() && ItemSelectOrigin != -1)
		{
			Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
			InventoryClickFlg_ = false;
		}
	}
	// �κ��丮�� Ȯ��Ǿ�����
	else
	{
		if (true == IsActionKeyDown()
			&& Mouse_->GetCollision()->CollisionResult(COL_GROUP_INVENTORY_EXTEND_BOX, MouseColResult_, CollisionType::Rect, CollisionType::Rect))
		{
			std::vector<GameEngineCollision*>::iterator StartIter = MouseColResult_.begin();
			std::vector<GameEngineCollision*>::iterator EndIter = MouseColResult_.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				for (size_t i = 0; i < 36; i++)
				{
					if (Inventory_->GetInventoryExtendCol()[i] == *StartIter)
					{
						ItemSelectOrigin = i;
						Inventory_->GetInventoryList()[i]->ClickedFlg = true;

						break;
					}
				}
			}

			InventoryClickFlg_ = true;
			// �浹 ��� �ʱ�ȭ
			MouseColResult_.clear();
		}

		// ������ �������� ���õǾ������鼭 ���콺�� ������ �ִ� ����
		if (true == IsActionKeyPress() && ItemSelectOrigin != -1)
		{
			// �������� ���콺�� ����ٴϵ��� �̵�
			Inventory_->GetInventoryList()[ItemSelectOrigin]->GetIconRenderer().SetPivot(Mouse_->GetPosition());
		}


		if (true == IsActionKeyUp()
			&& ItemSelectOrigin != -1
			&& Mouse_->GetCollision()->CollisionResult(COL_GROUP_INVENTORY_EXTEND_BOX, MouseColResult_, CollisionType::Rect, CollisionType::Rect))
		{
			// Collision�迭���� Collision�� ������ ���� �κ��丮�� ������ ������ �׻� ������.
			// �κ��丮 1ĭ�� �浹ü 1ĭ�̰�, �浹�� �浹ü�� ������ �˾Ƴ� �� ����.
			// ���콺�� �浹ü�� �浹�� �������� ������ �浹ü�� ������ ���Ͽ�,
			// 0������ 36������ �˻��ؼ� ���콺�� �浹�� �浹ü�� ������ �浹ü�� ������ �ִ� 
			// Item�� ��ȣ�� SetItem�Լ��� ȣ����.
			std::vector<GameEngineCollision*>::iterator StartIter = MouseColResult_.begin();
			std::vector<GameEngineCollision*>::iterator EndIter = MouseColResult_.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				for (size_t i = 0; i < 36; i++)
				{
					if (Inventory_->GetInventoryExtendCol()[i] == *StartIter)
					{
						ItemSelectTarget = i;

						if (ItemSelectOrigin == ItemSelectTarget)
						{
							Inventory_->GetInventoryList()[i]->ClickedFlg = false;
						}
						else if (ItemSelectOrigin != ItemSelectTarget)
						{
							Inventory_->SwapItem(ItemSelectOrigin, ItemSelectTarget);
						}

						// �浹 ��� �ʱ�ȭ
						MouseColResult_.clear();
						Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
						Inventory_->GetInventoryList()[ItemSelectTarget]->ClickedFlg = false;
						ItemSelectOrigin = -1, ItemSelectTarget = -1;

						InventoryClickFlg_ = false;

						return;
					}
				}
			}
		}
		else if (true == IsActionKeyUp() && ItemSelectOrigin != -1)
		{
			Inventory_->GetInventoryList()[ItemSelectOrigin]->ClickedFlg = false;
			InventoryClickFlg_ = false;
		}
	}
}

// Ÿ�ϸ� ����
void Player::CreatePlayerTileIndex(float4 _Pos, int _EnvironemntTileIndex, int _TileActorSelecter)
{
	int PosX = _Pos.x; // static_cast<int>(_Pos.x / TILEMAP_SIZE);
	int PosY = _Pos.y; // static_cast<int>(_Pos.y / TILEMAP_SIZE);
	int Color = 0;

	if (_TileActorSelecter == 0)
	{
		switch (_EnvironemntTileIndex)
		{
		case (int)TILESTATE::NONE:
			break;
		case (int)TILESTATE::HOLLOW:
			// ���� �ȼ��� �����Ǿ��ִ� ��ġ���� ���� �ȼ� �ֵ���
			GetMapColImage();
			Color = MapColImage_->GetImagePixel({ (float)(PosX * TILEMAP_SIZE)  , (float)(PosY * TILEMAP_SIZE) });

			if (RGB(255, 255, 255) == Color)
			{
				SetGroundTile(PosX, PosY,
					LevelTileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, IMAGE_TILESET_DIRT, 0, (int)ORDER::FRONTA), (int)TILESTATE::HOLLOW);
			}

			break;
		case (int)TILESTATE::HOLLOWWET:

			if (nullptr != GroundTiles_[PosY][PosX]
				&& GroundTiles_[PosY][PosX]->GetTileState() == (int)TILESTATE::HOLLOW)
			{
				GameEngineSound::SoundPlayOneShot(SOUND_WATER);
				// Ÿ�� ����
				SetGroundTile(PosX, PosY,
					LevelTileMap_->CreateTile<PlayerTileIndex>(PosX, PosY, IMAGE_TILESET_DIRTWATERED, 0, (int)ORDER::FRONTA), (int)TILESTATE::HOLLOWWET);
			}
			break;
		default:
			break;
		}

	}
	else if (_TileActorSelecter == 1
		&& nullptr != GroundTiles_[PosY][PosX])
	{
		switch (_EnvironemntTileIndex)
		{
		case (int)ITEMTABLE::OAKTREE:
			// Crop ����
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Oaktree>()), COL_GROUP_TREES, 1);
			break;
		case (int)ITEMTABLE::MAPLETREE:
			// Crop ����
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Mapletree>()), COL_GROUP_TREES, 1);
			break;
		case (int)ITEMTABLE::PINETREE:
			// Crop ����
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Pinetree>()), COL_GROUP_TREES, 1);
			break;
		case (int)ITEMTABLE::PARSNIP:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Parsnip>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::COULIFLOWER:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Couliflower>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::GARLIC:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Garlic>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::RHUBARB:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Rhubarb>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::TOMATO:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Tomato>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::HOTPEPPER:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Hotpepper>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::RADISH:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Radish>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::STARFRUIT:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Starfruit>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::EGGPLANT:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Eggplant>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::PUMPKIN:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Pumpkin>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::YAM:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Yam>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::BEET:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Beet>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::SUNFLOWER:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Sunflower>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::GREENBEAN:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Greenbean>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::POTATO:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Potato>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::KALE:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Kale>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::MELON:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Melon>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::BLUEBERRY:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Blueberry>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::REDCABBAGE:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Redcabbage>()), COL_GROUP_CROPS, 0);
			break;
		case (int)ITEMTABLE::CORN:
			SetCropsActor(PosX, PosY, static_cast<Crops*>(GetLevel()->CreateActor<Corn>()), COL_GROUP_CROPS, 0);
			break;
		default:
			break;
		}
	}
}

// ������ Ÿ�ϸ� ������ �÷��̾�� ����
void Player::SetGroundTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState)
{
	GroundTiles_[y][x] = _TileMap;
	GroundTiles_[y][x]->SetTileState(_TileState);
	GroundTiles_[y][x]->SetIndexInfo(0);

	TileIndexSetting(x, y);
}

void Player::TileIndexSetting(int x, int y)
{
	PlayerTileIndex* Up = GroundTiles_[y - 1][x];
	PlayerTileIndex* Left = GroundTiles_[y][x - 1];
	PlayerTileIndex* Right = GroundTiles_[y][x + 1];
	PlayerTileIndex* Down = GroundTiles_[y + 1][x];

	bool UpFlg = false, LeftFlg = false, RightFlg = false, DownFlg = false;
	int PrevIndexInfo = GroundTiles_[y][x]->GetIndexInfo();

	// ���� Ÿ�ϵ鿡 ���� ���� ���
	if (nullptr != Up && 
		(Up->GetTileState() == (int)TILESTATE::HOLLOW
		|| Up->GetTileState() == (int)TILESTATE::HOLLOWWET))
	{
		UpFlg = true;
	}
	if (nullptr != Down && 
		(Down->GetTileState() == (int)TILESTATE::HOLLOW
		|| Down->GetTileState() == (int)TILESTATE::HOLLOWWET))
	{
		DownFlg = true;
	}
	if (nullptr != Left && 
		(Left->GetTileState() == (int)TILESTATE::HOLLOW
		|| Left->GetTileState() == (int)TILESTATE::HOLLOWWET))
	{
		LeftFlg = true;
	}
	if (nullptr != Right && 
		(Right->GetTileState() == (int)TILESTATE::HOLLOW
		|| Right->GetTileState() == (int)TILESTATE::HOLLOWWET))
	{
		RightFlg = true;
	}


	// ������ Ÿ�ϵ��� ������ ���� �ε��� ����
	// �Ʒ� ������
	if (DownFlg == true && RightFlg == true && UpFlg == false && LeftFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(1);
		GroundTiles_[y][x]->SetIndexInfo(1);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y + 1);
		TileIndexSetting(x + 1, y);
	}
	// ���� ������ �Ʒ�
	if (RightFlg == true && LeftFlg == true && DownFlg == true && UpFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(2);
		GroundTiles_[y][x]->SetIndexInfo(2);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x - 1, y);
		TileIndexSetting(x + 1, y);
		TileIndexSetting(x, y + 1);
	}
	// �Ʒ� ����
	if (DownFlg == true && LeftFlg == true && UpFlg == false && RightFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(3);
		GroundTiles_[y][x]->SetIndexInfo(3);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y + 1);
		TileIndexSetting(x - 1, y);
	}
	// �Ʒ�
	if (DownFlg == true && UpFlg == false && RightFlg == false && LeftFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(4);
		GroundTiles_[y][x]->SetIndexInfo(4);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y + 1);
	}
	// �� ������ �Ʒ�
	if (UpFlg == true && RightFlg == true && DownFlg == true && LeftFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(5);
		GroundTiles_[y][x]->SetIndexInfo(5);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y + 1);
		TileIndexSetting(x + 1, y);
		TileIndexSetting(x, y - 1);
	}
	// ��� ����
	if (UpFlg == true && LeftFlg == true && RightFlg == true && DownFlg == true)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(6);
		GroundTiles_[y][x]->SetIndexInfo(6);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x, y + 1);
		TileIndexSetting(x - 1, y);
		TileIndexSetting(x + 1, y);
	}
	// �� ���� �Ʒ�
	if (UpFlg == true && LeftFlg == true && DownFlg == true && RightFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(7);
		GroundTiles_[y][x]->SetIndexInfo(7);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x - 1, y);
		TileIndexSetting(x, y + 1);
	}
	// ���Ʒ�
	if (UpFlg == true && DownFlg == true && RightFlg == false && LeftFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(8);
		GroundTiles_[y][x]->SetIndexInfo(8);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x, y + 1);
	}
	// �� ������
	if (UpFlg == true && RightFlg == true && LeftFlg == false && DownFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(9);
		GroundTiles_[y][x]->SetIndexInfo(9);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x + 1, y);
	}
	// �� ���� ������
	if (UpFlg == true && LeftFlg == true && RightFlg == true && DownFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(10);
		GroundTiles_[y][x]->SetIndexInfo(10);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x - 1, y);
		TileIndexSetting(x + 1, y);
	}
	//�� ����
	if (UpFlg == true && LeftFlg == true && DownFlg == false && RightFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(11);
		GroundTiles_[y][x]->SetIndexInfo(11);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
		TileIndexSetting(x - 1, y);
	}
	// ��
	if (UpFlg == true && LeftFlg == false && DownFlg == false && RightFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(12);
		GroundTiles_[y][x]->SetIndexInfo(12);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x, y - 1);
	}
	// ������
	if (RightFlg == true && UpFlg == false && DownFlg == false && LeftFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(13);
		GroundTiles_[y][x]->SetIndexInfo(13);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x + 1, y);
	}
	// ���� ������
	if (RightFlg == true && LeftFlg == true && UpFlg == false && DownFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(14);
		GroundTiles_[y][x]->SetIndexInfo(14);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x - 1, y);
		TileIndexSetting(x + 1, y);
	}
	// ����
	if (LeftFlg == true && UpFlg == false && RightFlg == false && DownFlg == false)
	{
		GroundTiles_[y][x]->GetRenderer()->SetIndex(15);
		GroundTiles_[y][x]->SetIndexInfo(15);

		if (PrevIndexInfo == GroundTiles_[y][x]->GetIndexInfo())
		{
			return;
		}

		TileIndexSetting(x - 1, y);
	}
}

// ���۹� ��ġ
void Player::SetCropsActor(int x, int y, Crops* _CropActor, std::string _ColGroup, int _CropType)
{
	// �ش� ��ġ�� ����������� ����
	if (nullptr == EnvironmentActor_[y][x])
	{
		EnvironmentActor_[y][x] = _CropActor;
		EnvironmentActor_[y][x]->ReSetAccTime();
		EnvironmentActor_[y][x]->SetIsTimeUpdate(true);

		// Ÿ���� �߾����� ��ġ�� ���߱����� TILEMAP_SIZE / 2��ŭ ����
		EnvironmentActor_[y][x]->SetPosition({ static_cast<float>(x * TILEMAP_SIZE + TILEMAP_SIZE / 2), static_cast<float>(y * TILEMAP_SIZE + TILEMAP_SIZE / 2) });
		EnvironmentActor_[y][x]->CreateCollision(_ColGroup, { TILEMAP_SIZE - 18, TILEMAP_SIZE - 18 });

		EnvironmentActor_[y][x]->GetRenderer()->SetOrder((int)ORDER::PLAYER);
		EnvironmentActor_[y][x]->CropType_ = _CropType;

		// ���� �������� ���ڸ� ����
		Inventory_->GetInventoryList()[Inventory_->GetSelectedItemNum()]->SubCounter();

		// �������� 0�������ϰ�� �������� ����
		if (stoi(Inventory_->GetInventoryList()[Inventory_->GetSelectedItemNum()]->Counter_) <= 0)
		{
			Inventory_->DeleteItem(Inventory_->GetSelectedItemNum());
		}
	}
}

// �ʵ忡 �������ִ� �����۵�
void Player::ItemUpdate()
{
	float4 Dir = { 0.0f, 0.0f };
	float Check = 0.0f;

	std::list<Item*>::iterator Start = ItemList_.begin();
	std::list<Item*>::iterator End = ItemList_.end();

	for (; Start != End; )
	{
		Dir = this->GetPosition() - (*Start)->GetPosition();
		Check = Dir.Len2D();

		if (Check <= 20)
		{
			// �������� �ִ°Ϳ� �������� ��� �������� �ı�
			if (1 == Inventory_->AddItemToInventory(StringtoItemTable((*Start)->GetItemName())))
			{
				(*Start)->Death();
				Start = ItemList_.erase(Start);

				GameEngineSound::SoundPlayOneShot(SOUND_PICKUPITEM);

				continue;
			}
		}
		// �����۰� �÷��̾��� �Ÿ��� �ʹ� �ָ� ������� �������� ����.
		else if (Check <= 70)
		{
			Dir.Normal2D();
			(*Start)->SetMove(Dir * GameEngineTime::GetDeltaTime() * 300.0f);
		}

		++Start;
	}
}

// ���� �ʱ⼳��
void Player::MineralInit(std::string _ColName)
{
	// �ø������� �ѹ� ��ȯ�Ͽ� RGB(255, 0, 0)�ϰ�� �� ��ġ�� ���� ����
	GameEngineImage* MineralInitImage_ = GameEngineImageManager::GetInst()->Find(_ColName);
	float4 CheckPos = { 0.0f, 0.0f };
	int Color = 0;
	
	// EnvironmentActor_[y][x]
	for (int y = 0; y < EnvironmentActor_.size(); y++)
	{
		for (int x = 0; x < EnvironmentActor_[y].size(); x++)
		{
			CheckPos = { TILEMAP_SIZE * x + TILEMAP_SIZE / 2, TILEMAP_SIZE * y + TILEMAP_SIZE / 2 };
			Color = MineralInitImage_->GetImagePixel(CheckPos);

			if (RGB(255, 0, 0) == Color)
			{
				EnvironmentActor_[y][x] = static_cast<Crops*>(GetLevel()->CreateActor<MineObject>());
				EnvironmentActor_[y][x]->SetPosition({ TILEMAP_SIZE * x + TILEMAP_SIZE / 2, TILEMAP_SIZE * y + TILEMAP_SIZE / 2 });
				EnvironmentActor_[y][x]->CreateCollision(COL_GROUP_MINES, { TILEMAP_SIZE - 18, TILEMAP_SIZE - 18 });
				EnvironmentActor_[y][x]->CropType_ = 2;
			}
		}
	}
}