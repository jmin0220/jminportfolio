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
		// 컬리전맵 취득
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
			//낚시를 던질때 충돌맵을 호출해서 낚시를 할 수 있는 곳이면 게임 스타트
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

// 클릭했을때 상태
void Player::ActionUpdate()
{
	// 애니메이션이 종료되면 액션 실행 후 Idle로 전환
	if (true == RendererBody_->IsEndAnimation())
	{
		// 액션이 끝나는 순간에만 액션충돌체 켜기
		GetActionCollision()->On();

		// Hoe를 들고 있는경우
		if (Inventory_->GetSelectedItemName() == ITEM_NAME_HOE)
		{
			// 플레이어에서 너무 멀리 떨어져있는 타일을 선택했을 경우, 플레이어가 바라보고 있는 방향의 타일맵에 Dirt를 생성
			// 플레이어 근처에서 선택할경우, 해당방향으로 변경되면서, 선택한 타일맵에 Dirt를 생성

			// 농작물일경우 부셔짐 처리
			if (EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x] != nullptr)
			{
				Crops* ResultCrops = EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x];
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

			// 충돌 결과 초기화
			ActionColResult_.clear();

			}
			else
			{
				// 타일생성
				CreatePlayerTileIndex(CurserPosOnTileMap_, (int)TILESTATE::HOLLOW, 0);
			}
		}
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_WATERINGCAN)
		{
			// 타일생성
			CreatePlayerTileIndex(CurserPosOnTileMap_, (int)TILESTATE::HOLLOWWET, 0);
		}
		// Axe를 들고 있는경우
		else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
		{
			// 플레이어가 선택한 위치에 있는 액터를 파괴
			// 나무일경우 부셔짐 처리
			if (EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x] != nullptr)
			{
				Crops* ResultCrops = EnvironmentActor_[CurserPosOnTileMap_.y][CurserPosOnTileMap_.x];
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

			// 충돌 결과 초기화
			ActionColResult_.clear();
		}
		// 나무, 씨앗일경우
		else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
		{
			// 타일생성
			CreatePlayerTileIndex(CurserPosOnTileMap_, StringtoItemTable(Inventory_->GetSelectedItemName()), 1);
		}

		// Idle로 상태 전환
		StateChange(PlayerState::Idle);
	}
}

// 낚시 업데이트
void Player::FishingUpdate()
{
	// 낚싯대 던지기 애니메이션이 종료되면
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
			// Idle로 상태 전환
			StateChange(PlayerState::Idle);
		}
	}
}

void Player::ShopUpdate()
{
	if (true == SeedShop_->ShopUpdate())
	{
		// Idle로 상태 전환
		SeedShop_->Death();
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

	ToolAnimationChange(TOOL_ANIM_IDLE);
}

void Player::ActionStart()
{
	// 마우스 클릭하는 포지션
	CurserPosOnTileMap_ = Mouse_->GetCurserPosOnTilemap();

	    // 클릭 위치가 오른쪽으로 멀리 떨어져있음
	if (GetPositionOnTilemap().x + 1 < CurserPosOnTileMap_.x
		// 왼쪽으로 멀리 떨어져있음
		|| GetPositionOnTilemap().x - 1 > CurserPosOnTileMap_.x
		// 위쪽으로 멀리 떨어져있음
		|| GetPositionOnTilemap().y - 1 > CurserPosOnTileMap_.y
		// 아래쪽으로 멀리 떨어져있음
		|| GetPositionOnTilemap().y + 1 < CurserPosOnTileMap_.y)
	{
		// 플레이어가 보고 있는 방향의 바로 앞 타일을 선택함
		if (MoveDir_.CompareInt2D(float4::RIGHT))
		{
			CurserPosOnTileMap_ = {GetPositionOnTilemap().x + 1.0f, GetPositionOnTilemap().y };
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

	// Hoe를 들고 있는경우
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
	// Axe를 들고 있는경우
	else if (Inventory_->GetSelectedItemName() == ITEM_NAME_AXE)
	{
		Anim = ANIM_KEYWORD_HIT_HORIZON;
		ToolAnim = ANIM_KEYWORD_TOOL_AXE;
	}
	else if ((int)ITEMTABLE::OAKTREE <= StringtoItemTable(Inventory_->GetSelectedItemName())
		&& StringtoItemTable(Inventory_->GetSelectedItemName()) <= (int)ITEMTABLE::CORN)
	{
		// 씨앗 심기용 애니메이션?
		Anim = ANIM_KEYWORD_IDLE;
		ToolAnim = ANIM_KEYWORD_TOOL_IDLE;
	}

	// 플레이어의 방향에 따라 애니메이션의 방향을 설정
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

	// 플레이어 애니메이션 전환
	PlayerAnimationChange(Anim + Dir);

	// 툴 애니메이션 전환
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
	// 애니메이션은 무조건 출력
	FishingGame_->GameStart();
}

void Player::ShopStart()
{
	// 씨앗상점 레벨에서만 SeedShop 액터를 생성
	SeedShop_ = GetLevel()->CreateActor<SeedShop>();
	SeedShop_->ShopStart();
}

void Player::MoveStart()
{

}

