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
	// Idle 상태에서는 액션충돌체 끄기
	GetActionCollision()->Off();

	// 액션은 이동보다 우선순위가 높음.
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

// 클릭했을때 상태
void Player::ActionUpdate()
{
	// 애니메이션이 종료되면 액션 실행 후 Idle로 전환
	if (true == RendererBody_->IsEndAnimation())
	{
		float4 CheckLength = MoveDir_ * 24;
		float4 Pos = { GetPosition().x + CheckLength.x + MoveDir_.x * 30.0f, GetPosition().y + CheckLength.y + 16.0f };

		// 액션이 끝나는 순간에만 액션충돌체 켜기
		GetActionCollision()->On();

		// Hoe를 들고 있는경우
		if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
		{
			// 농작물일경우 부셔짐 처리
			if (GetActionCollision()->CollisionResult(COL_GROUP_CROPS, ActionColResult_, CollisionType::Rect, CollisionType::Rect))
			{
				std::vector<GameEngineCollision*>::iterator StartIter = ActionColResult_.begin();
				std::vector<GameEngineCollision*>::iterator EndIter = ActionColResult_.end();

				for (; StartIter != EndIter; ++StartIter)
				{
					Crops* ResultCrops = static_cast<Crops*>(StartIter[0]->GetActor());
					ResultCrops->SetHp(ResultCrops->GetHp() - 1);

					// Hp가 0이 되면 파괴
					if (ResultCrops->GetHp() <= 0)
					{
						ResultCrops->Destroy();

						// 최대 성장 상태에서 파괴되었을경우 아이템 생성
						if (ResultCrops->GetMaxLevel() == ResultCrops->GetGrowLevel())
						{
							int ItemNum = PlayerRandom_->RandomInt(1, 4);

							for (size_t i = 0; i < ItemNum; i++)
							{
								AddItem(ResultCrops->CreateItem());
							}
						}

						// 파괴처리 후 배열을 nullptr로 초기화
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

			// 충돌 결과 초기화
			ActionColResult_.clear();

			}
			else
			{
				// 타일생성
				CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOW, 0);
			}
		}
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
		{
			// 타일생성
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOWWET, 0);
		}
		// Axe를 들고 있는경우
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
		{
			// 나무일경우 부셔짐 처리
			if (GetActionCollision()->CollisionResult(COL_GROUP_TREES, ActionColResult_, CollisionType::Rect, CollisionType::Rect))
			{
				std::vector<GameEngineCollision*>::iterator StartIter = ActionColResult_.begin();
				std::vector<GameEngineCollision*>::iterator EndIter = ActionColResult_.end();

				for (; StartIter != EndIter; ++StartIter)
				{
					Crops* ResultCrops = static_cast<Crops*>(StartIter[0]->GetActor());
					ResultCrops->SetHp(ResultCrops->GetHp() - 1);

					// Hp가 0이 되면 파괴
					if (ResultCrops->GetHp() <= 0)
					{
						ResultCrops->Destroy();

						// 최대 성장 상태에서 파괴되었을경우 아이템 생성
						if (ResultCrops->GetMaxLevel() <= ResultCrops->GetGrowLevel())
						{
							int ItemNum = PlayerRandom_->RandomInt(1, 4);

							for (size_t i = 0; i < ItemNum; i++)
							{
								AddItem(ResultCrops->CreateItem());
							}
						}

						// 파괴처리 후 배열을 nullptr로 초기화
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
						// Hp가 4이하일경우 나무 밑둥만 남기기
						ResultCrops->SetGrowLevel(5);
						ResultCrops->GetRenderer()->SetIndex(ResultCrops->GetCropsRenderIndex() + ResultCrops->GetGrowLevel());

						// 밑둥만 남는 순간 한번 아이템 생성
						int ItemNum = PlayerRandom_->RandomInt(1, 4);

						for (size_t i = 0; i < ItemNum; i++)
						{
							AddItem(ResultCrops->CreateItem());
						}
					}

				}
			}

			// 충돌 결과 초기화
			ActionColResult_.clear();
		}
		// 나무, 씨앗일경우
		else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
		{
			// 타일생성
			CreatePlayerTileIndex(Pos, StringtoItemTable(Inventory_->GetSelectedItemName()), 1);
		}

		// Idle로 상태 전환
		StateChange(PlayerState::Idle);
	}
}

// 이동했을때 상태
void Player::MoveUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
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

	// 이동 상태에서 방향
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
	// 정지 상태에서 방향
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
	// TODO::문자열 분리 후 결합하여 애니메이션으로 넘겨줌.
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

