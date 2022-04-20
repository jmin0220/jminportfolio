#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::IdleUpdate()
{
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
		float4 Pos = { GetPosition().x + CheckLength.x, GetPosition().y + CheckLength.y + 12.0f };
		
		if (Inventory_->GetSelectedItem() == ITEM_NAME_HOE)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOW);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_WATERINGCAN)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOWWET);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_AXE)
		{
			// ����
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_OAKTREE)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, (int)TILESTATE::OAKTREE);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_PARSNIP)
		{
			// Ÿ�ϻ���
			CreatePlayerTileIndex(Pos, (int)TILESTATE::PARSNIP);
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

		ColCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		PlayerAnimationChange(ANIM_WALK_LEFT);

		ColCheck(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		PlayerAnimationChange(ANIM_WALK_UP);

		ColCheck(float4::UP);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		PlayerAnimationChange(ANIM_WALK_DOWN);

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
	// TODO::���ڿ� �и� �� �����Ͽ� �ִϸ��̼����� �Ѱ���.
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_RIGHT);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_LEFT);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_UP);
	}
	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_DOWN);
	}
}

void Player::MoveStart()
{

}

