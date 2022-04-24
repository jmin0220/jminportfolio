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
		StateChange(PlayerState::Action);
		return;
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
		float4 CheckLength = MoveDir_ * 24;
		float4 Pos = { GetPosition().x + CheckLength.x + MoveDir_.x * 30.0f, GetPosition().y + CheckLength.y + 16.0f };

		// �׼��� ������ �������� �׼��浹ü �ѱ�
		GetActionCollision()->On();

		// Hoe�� ��� �ִ°��
		if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
		{
			// ���۹��ϰ�� �μ��� ó��
			if (GetActionCollision()->CollisionResult(COL_GROUP_CROPS, ActionColResult_, CollisionType::Rect, CollisionType::Rect))
			{
				std::vector<GameEngineCollision*>::iterator StartIter = ActionColResult_.begin();
				std::vector<GameEngineCollision*>::iterator EndIter = ActionColResult_.end();

				for (; StartIter != EndIter; ++StartIter)
				{
					Crops* ResultCrops = static_cast<Crops*>(StartIter[0]->GetActor());
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
				}

			// �浹 ��� �ʱ�ȭ
			ActionColResult_.clear();

			}
			else
			{
				// Ÿ�ϻ���
				CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOW, 0);
			}
		}
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOWWET, 0);
		}
		// Axe�� ��� �ִ°��
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
		{
			// �����ϰ�� �μ��� ó��
			if (GetActionCollision()->CollisionResult(COL_GROUP_TREES, ActionColResult_, CollisionType::Rect, CollisionType::Rect))
			{
				std::vector<GameEngineCollision*>::iterator StartIter = ActionColResult_.begin();
				std::vector<GameEngineCollision*>::iterator EndIter = ActionColResult_.end();

				for (; StartIter != EndIter; ++StartIter)
				{
					Crops* ResultCrops = static_cast<Crops*>(StartIter[0]->GetActor());
					ResultCrops->SetHp(ResultCrops->GetHp() - 1);

					// Hp�� 0�� �Ǹ� �ı�
					if (ResultCrops->GetHp() <= 0)
					{
						ResultCrops->Destroy();

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
			}

			// �浹 ��� �ʱ�ȭ
			ActionColResult_.clear();
		}
		// ����, �����ϰ��
		else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, StringtoItemTable(Inventory_->GetSelectedItemName()), 1);
		}

		// Idle�� ���� ��ȯ
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
		GetActionCollision()->SetPivot({ PLAYER_ACTION_COL_LENG , 0.0f});

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
}

void Player::ActionStart()
{
	std::string Anim = ANIM_KEYWARD_IDLE;
	std::string Dir = "";

	// Hoe�� ��� �ִ°��
	if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
	{
		Anim = ANIM_KEYWARD_HIT_HORIZON;
	}
	else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
	{
		Anim = ANIM_KEYWARD_WATERING;
	}
	// Axe�� ��� �ִ°��
	else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
	{
		Anim = ANIM_KEYWARD_HIT_HORIZON;
	}
	else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
	{
		// ���� �ɱ�� �ִϸ��̼�?
		Anim = ANIM_KEYWARD_IDLE;
	}

	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWARD_DIR_RIGHT;
	}
	else if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWARD_DIR_LEFT;
	}
	else if (float4::UP.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWARD_DIR_UP;
	}
	else if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		Dir = ANIM_KEYWARD_DIR_DOWN;
	}

	PlayerAnimationChange(Anim + Dir);
}

void Player::MoveStart()
{

}

