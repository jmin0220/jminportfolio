#include "Player.h"
#include "PlayLevel.h"
#include "ItemTable.h"
#include "TileStateTable.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::IdleUpdate()
{
	// Idle ���¿����� �׼��浹ü ����
	GetActionCollision()->Off();

	// �׼��� �̵����� �켱������ ����.
	if (true == IsActionKeyDown())
	{
		// �ø����� ���
		GetMapColImage();

		if (GetCurrentLevel() == LEVEL_SEEDSHOP)
		{
			float4 CheckPos = SetCheckPos(GetPosition());
			int Color = MapColImage_->GetImagePixel(CheckPos);

			if (RGB(100, 100, 100) == Color)
			{
				StateChange(PlayerState::Shop);
			}

			return;
		}

		if (Inventory_->GetSelectedItemName() == ITEM_NAME_FISHINGROD)
		{
			//���ø� ������ �浹���� ȣ���ؼ� ���ø� �� �� �ִ� ���̸� ���� ��ŸƮ
			float4 CheckLength = MoveDir_ * 50.0f;
			float4 NextPos = GetPosition() + CheckLength;
			float4 CheckPos = SetCheckPos(NextPos);
			int Color = MapColImage_->GetImagePixel(CheckPos);

			if (RGB(0, 0, 255) == Color)
			{
				std::string Dir = "";

				if (float4::RIGHT.CompareInt2D(MoveDir_))
				{
					Dir = ANIM_KEYWORD_DIR_RIGHT;
				}
				else if (float4::LEFT.CompareInt2D(MoveDir_))
				{
					Dir = ANIM_KEYWORD_DIR_LEFT;
				}
				else if (float4::UP.CompareInt2D(MoveDir_))
				{
					Dir = ANIM_KEYWORD_DIR_UP;
				}
				else if (float4::DOWN.CompareInt2D(MoveDir_))
				{
					Dir = ANIM_KEYWORD_DIR_DOWN;
				}

				PlayerAnimationChange(ANIM_KEYWORD_FISHING + Dir);
				ToolAnimationChange(ANIM_KEYWORD_TOOL_FISHING + Dir);

				StateChange(PlayerState::Fishing);
			}

			return;
		}
		else
		{
			StateChange(PlayerState::Action);
			return;
		}
	}

	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		StateChange(PlayerState::Action);
		return;
	}
}

// Ŭ�������� ����
void Player::ActionUpdate()
{
	// �ִϸ��̼��� ����Ǹ� �׼� ���� �� Idle�� ��ȯ
	if (true == RendererBody_->IsEndAnimation())
	{
		// �׼��� ������ �������� �׼��浹ü �ѱ�
		GetActionCollision()->On();

		// Hoe�� ��� �ִ°��
		if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
		{
			// �÷��̾�� �ʹ� �ָ� �������ִ� Ÿ���� �������� ���, �÷��̾ �ٶ󺸰� �ִ� ������ Ÿ�ϸʿ� Dirt�� ����
			// �÷��̾� ��ó���� �����Ұ��, �ش�������� ����Ǹ鼭, ������ Ÿ�ϸʿ� Dirt�� ����

			// ���۹��ϰ�� �μ��� ó��
			if (EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x] != nullptr)
			{
				Crops* ResultCrops = EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x];
				ResultCrops->SetHp(ResultCrops->GetHp() - 1);

				// Hp�� 0�� �Ǹ� �ı�
				if (ResultCrops->GetHp() <= 0)
				{
					ResultCrops->Destroy();

					// �ִ� ���� ���¿��� �ı��Ǿ������ ������ ����
					if (ResultCrops->GetMaxLevel() == ResultCrops->GetGrowLevel())
					{
						int ItemNum = PlayerRandom_->RandomInt(1, 4);

						for (size_t i = 0; i < ItemNum; i++)
						{
							AddItem(ResultCrops->CreateItem());
						}
					}

					// �ı�ó�� �� �迭�� nullptr�� �ʱ�ȭ
					for (size_t i = 0; i < EnvironmentActor_.size(); i++)
					{
						for (size_t j = 0; j < EnvironmentActor_[i].size(); j++)
						{
							if (ResultCrops == EnvironmentActor_[i][j])
							{
								EnvironmentActor_[i][j] = nullptr;
								break;
							}
						}
					}
				}

				// �浹 ��� �ʱ�ȭ
				ActionColResult_.clear();
				GameEngineSound::SoundPlayOneShot(SOUND_HOEHIT);
			}
			else
			{
				// Ÿ�ϻ���
				CreatePlayerTileIndex(CurserPosOnTileMap_, (int)TILESTATE::HOLLOW, 0);
				GameEngineSound::SoundPlayOneShot(SOUND_HOE);
			}
		}
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(CurserPosOnTileMap_, (int)TILESTATE::HOLLOWWET, 0);
		}
		// Axe�� ��� �ִ°��
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
		{
			// �÷��̾ ������ ��ġ�� �ִ� ���͸� �ı�
			// �����ϰ�� �μ��� ó��
			if (EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x] != nullptr)
			{
				Crops* ResultCrops = EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x];
				ResultCrops->SetHp(ResultCrops->GetHp() - 1);
				ResultCrops->SetVibrate(true);

				// Hp�� 0�� �Ǹ� �ı�
				if (ResultCrops->GetHp() <= 0)
				{
					ResultCrops->Destroy();
					GameEngineSound::SoundPlayOneShot(SOUND_STUMPCRACK);

					// �ִ� ���� ���¿��� �ı��Ǿ������ ������ ����
					if (ResultCrops->GetMaxLevel() <= ResultCrops->GetGrowLevel())
					{
						int ItemNum = PlayerRandom_->RandomInt(1, 4);

						for (size_t i = 0; i < ItemNum; i++)
						{
							AddItem(ResultCrops->CreateItem());
						}
					}

					// �ı�ó�� �� �迭�� nullptr�� �ʱ�ȭ
					for (size_t i = 0; i < EnvironmentActor_.size(); i++)
					{
						for (size_t j = 0; j < EnvironmentActor_[i].size(); j++)
						{
							if (ResultCrops == EnvironmentActor_[i][j])
							{
								EnvironmentActor_[i][j] = nullptr;
								break;
							}
						}
					}
				}
				else if (ResultCrops->GetHp() == 4)
				{
					// Hp�� 4�����ϰ�� ���� �صո� �����
					ResultCrops->SetGrowLevel(5);
					ResultCrops->GetRenderer()->SetIndex(ResultCrops->GetCropsRenderIndex() + ResultCrops->GetGrowLevel());

					// �صո� ���� ���� �ѹ� ������ ����
					int ItemNum = PlayerRandom_->RandomInt(1, 4);

					for (size_t i = 0; i < ItemNum; i++)
					{
						AddItem(ResultCrops->CreateItem());
					}
				}
			}

			GameEngineSound::SoundPlayOneShot(SOUND_AXE);

			// �浹 ��� �ʱ�ȭ
			ActionColResult_.clear();
		}
		// ����, �����ϰ��
		else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
			&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(CurserPosOnTileMap_, StringtoItemTable(Inventory_->GetSelectedItemName()), 1);
		}


		// Idle�� ���� ��ȯ
		StateChange(PlayerState::Idle);
	}
}

// ���� ������Ʈ
void Player::FishingUpdate()
{
	// ���˴� ������ �ִϸ��̼��� ����Ǹ�
	if (true == RendererBody_->IsEndAnimation() && FishingGameFlg == false)
	{
		FishingGameFlg = true;
	}

	if (true == FishingGameFlg)
	{
		if (true == FishingGame_->GameUpdate())
		{
			FishingGame_->GameEnd();
			FishingGameFlg = false;
			// Idle�� ���� ��ȯ
			StateChange(PlayerState::Idle);
		}
	}
}

void Player::ShopUpdate()
{
	if (true == SeedShop_->ShopUpdate())
	{
		// Idle�� ���� ��ȯ
		SeedShop_->Death();
		StateChange(PlayerState::Idle);
	}
}

// �̵������� ����
void Player::MoveUpdate()
{
	// �׼��� �̵����� �켱������ ����.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	if (true == IsMoveKeyUp() && false == IsMoveKeyPress())
	{
		StateChange(PlayerState::Idle);
		return;
	}

	// �̵� ���¿��� ����
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		PlayerAnimationChange(ANIM_WALK_RIGHT);
		GetActionCollision()->SetPivot({ PLAYER_ACTION_COL_LENG , 0.0f });

		ColCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		PlayerAnimationChange(ANIM_WALK_LEFT);
		GetActionCollision()->SetPivot({ -PLAYER_ACTION_COL_LENG , 0.0f });

		ColCheck(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		PlayerAnimationChange(ANIM_WALK_UP);
		GetActionCollision()->SetPivot({ 0.0f, -PLAYER_ACTION_COL_LENG });

		ColCheck(float4::UP);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		PlayerAnimationChange(ANIM_WALK_DOWN);
		GetActionCollision()->SetPivot({ 0.0f, PLAYER_ACTION_COL_LENG });

		ColCheck(float4::DOWN);
	}
}


//////////////////////////////////////// State
void Player::IdleStart()
{
	// ���� ���¿��� ����
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_RIGHT);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_LEFT);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_UP);
	}
	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_DOWN);
	}

	ToolAnimationChange(TOOL_ANIM_IDLE);
}

void Player::ActionStart()
{
	// ���콺 Ŭ���ϴ� ������
	CurserPosOnTileMap_ = Mouse_->GetCurserPosOnTilemap();

	// Ŭ�� ��ġ�� ���������� �ָ� ����������
	if (GetPositionOnTilemap().x + 1 < CurserPosOnTileMap_.x
		// �������� �ָ� ����������
		|| GetPositionOnTilemap().x - 1 > CurserPosOnTileMap_.x
		// �������� �ָ� ����������
		|| GetPositionOnTilemap().y - 1 > CurserPosOnTileMap_.y
		// �Ʒ������� �ָ� ����������
		|| GetPositionOnTilemap().y + 1 < CurserPosOnTileMap_.y)
	{
		// �÷��̾ ���� �ִ� ������ �ٷ� �� Ÿ���� ������
		if (MoveDir_.CompareInt2D(float4::RIGHT))
		{
			CurserPosOnTileMap_ = { GetPositionOnTilemap().x + 1.0f, GetPositionOnTilemap().y };
		}
		else if (MoveDir_.CompareInt2D(float4::LEFT))
		{
			CurserPosOnTileMap_ = { GetPositionOnTilemap().x - 1.0f, GetPositionOnTilemap().y };
		}
		else if (MoveDir_.CompareInt2D(float4::UP))
		{
			CurserPosOnTileMap_ = { GetPositionOnTilemap().x, GetPositionOnTilemap().y - 1.0f };
		}
		else if (MoveDir_.CompareInt2D(float4::DOWN))
		{
			CurserPosOnTileMap_ = { GetPositionOnTilemap().x, GetPositionOnTilemap().y + 1.0f };
		}
	}
	else
	{
		if (GetPositionOnTilemap().x + 1 == CurserPosOnTileMap_.x)
		{
			MoveDir_ = float4::RIGHT;
		}
		else if (GetPositionOnTilemap().x - 1 == CurserPosOnTileMap_.x)
		{
			MoveDir_ = float4::LEFT;
		}
		else if (GetPositionOnTilemap().y - 1 == CurserPosOnTileMap_.y)
		{
			MoveDir_ = float4::UP;
		}
		else if (GetPositionOnTilemap().y + 1 == CurserPosOnTileMap_.y)
		{
			MoveDir_ = float4::DOWN;
		}
	}

	std::string Anim = ANIM_KEYWORD_IDLE;
	std::string ToolAnim = ANIM_KEYWORD_TOOL_IDLE;
	std::string Dir = "";
	RendererTool_->SetOrder((int)ORDER::TOOLB);

	// Hoe�� ��� �ִ°��
	if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
	{
		Anim = ANIM_KEYWORD_HIT_HORIZON;
		ToolAnim = ANIM_KEYWORD_TOOL_HOE;
	}
	else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
	{
		Anim = ANIM_KEYWORD_WATERING;
		ToolAnim = ANIM_KEYWORD_TOOL_WATERING;
	}
	// Axe�� ��� �ִ°��
	else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
	{
		Anim = ANIM_KEYWORD_HIT_HORIZON;
		ToolAnim = ANIM_KEYWORD_TOOL_AXE;
	}
	else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
	{
		// ���� �ɱ�� �ִϸ��̼�?
		Anim = ANIM_KEYWORD_IDLE;
		ToolAnim = ANIM_KEYWORD_TOOL_IDLE;
	}

	// �÷��̾��� ���⿡ ���� �ִϸ��̼��� ������ ����
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWORD_DIR_RIGHT;
	}
	else if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWORD_DIR_LEFT;
	}
	else if (float4::UP.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWORD_DIR_UP;
		RendererTool_->SetOrder((int)ORDER::TOOLA);
	}
	else if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWORD_DIR_DOWN;
	}

	// �÷��̾� �ִϸ��̼� ��ȯ
	PlayerAnimationChange(Anim + Dir);

	// �� �ִϸ��̼� ��ȯ
	if (ToolAnim == ANIM_KEYWORD_TOOL_IDLE)
	{
		ToolAnimationChange(ToolAnim);
	}
	else
	{
		ToolAnimationChange(ToolAnim + Dir);
	}
}

void Player::FishingStart()
{
	// �ִϸ��̼��� ������ ���
	FishingGame_->GameStart();
}

void Player::ShopStart()
{
	// ���ѻ��� ���������� SeedShop ���͸� ����
	SeedShop_ = GetLevel()->CreateActor<SeedShop>();
	SeedShop_->ShopStart();
}

void Player::MoveStart()
{

}

