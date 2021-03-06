#pragma once
#include <string>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Mouse.h"
#include "Item.h"
#include "Clock.h"
#include "EnergyBar.h"
#include "Inventory.h"
#include "PlayerTileIndex.h"
#include "Crops.h"
#include "FishingGame.h"
#include "SeedShop.h"

// 설명 :
class GameEngineImage;
class GameEngineCollision;
class GameEngineRendererTileMap;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	// 타일맵 설정
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		LevelTileMap_ = _TileMap;
	}

	// 다음 레벨 정보를 취득
	inline std::string GetNextLevel()
	{
		return NextLevel_;
	}

	// 다음레벨에서 플레이어가 시작될 위치
	inline float4 GetNextLevelPos()
	{
		return NextLevelPos_;
	}

	inline void SetNextLevelPos(float4 _Pos)
	{
		NextLevelPos_ = _Pos;
	}

	inline GameEngineCollision* GetCollision()
	{
		return PlayerCollision_;
	}

	inline void SetCollision(GameEngineCollision* _Collision)
	{
		PlayerCollision_ = _Collision;
	}

	inline float4 GetMoveDir() const
	{
		return MoveDir_;
	}

	// 플레이어 초기화
	void PlayerInit();

	// 플레이어의 위치에 따라서 Front레이어의 랜더 순서를 유동적으로 전환
	bool ColRenderOrderCheck();

	// 애니메이션 전환
	void PlayerAnimationChange(const std::string& _Name);
	void ToolAnimationChange(const std::string& _Name);
private:
	void Start() override;
	void Update() override;

	// 속도
	float Speed_;
	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;

	float4 GetPositionOnTilemap();

	// 플레이어의 충돌체
	GameEngineCollision* PlayerCollision_;
	std::vector<GameEngineCollision*> ActionColResult_;

	// 다음 레벨
	std::string NextLevel_;
	// 다음 레벨에서의 위치
	static float4 NextLevelPos_;

	// 카메라의 위치
	float4 CameraPos_;

	// 플레이어 자신의 렌더러
	GameEngineRenderer* RendererBody_;
	// 플레이어 장비의 렌더러
	GameEngineRenderer* RendererTool_;

	// 맵에서 사용될 충돌용 이미지
	GameEngineImage* MapColImage_;
	GameEngineImage* MapColOrderImage_;

	// 사운드 오브젝트
	GameEngineSound* SoundPlayer_;

	// 애니메이션 초기화
	void PlayerAnimationInit();
	// 키 초기화
	void PlayerKeyInit();
	// 카메라 업데이트
	void UpdateCamera();
	// 아이템 업데이트
	void ItemUpdate();

	// 플레이어가 움직일때 충돌감지
	float4 SetCheckPos(float4 _NextPos);

	void GetMapColImage();

	// 맵과의 충돌체크
	void ColCheck(float4 _MoveDir);

	// 현재 레벨
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// 키 입력
private:
	bool InventoryClickFlg_;
	int ItemSelectOrigin, ItemSelectTarget;
	Mouse* Mouse_;
	float4 CurserPosOnTileMap_;
	std::vector<GameEngineCollision*> MouseColResult_;

	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();

	// 마우스로 인벤토리의 셀렉트 박스를 컨트롤
	void ControlInventorySelectBoxWithMouse();

	// FSM
public:
	// 상태전환
	void StateChange(PlayerState _State);
	// 상태 업데이트
	void StateUpdate();
private:
	// 현재 상태
	PlayerState CurState_;

	void IdleStart();
	void ActionStart();
	void FishingStart();
	void ShopStart();
	void MoveStart();

	void IdleUpdate();
	void ActionUpdate();
	void FishingUpdate();
	void ShopUpdate();
	void MoveUpdate();

public:
	Inventory* GetInventory()
	{
		return Inventory_;
	}

	inline int GetGold()
	{
		return Gold_;
	}

	inline void SetGold(int _Gold)
	{
		GameEngineSound::SoundPlayOneShot(SOUND_COINS);
		Gold_ = _Gold;
	}

private:
	// 인터페이스
	Inventory* Inventory_;
	Clock* Clock_;
	EnergyBar* EnergyBar_;

	static int Gold_;

	// 타일맵 관련
private:
	// 플레이어가 가지고있을 타일 정보인덱스 생성
	// 타일의 랜더러는 각 레벨의 타일맵이 가지고 있지만,
	// 해당 위치의 '상태'는 해당 레벨의 플레이어가 가지고 있음.
	// 보이는 것과 상태가 일치하지 않을 수도 있다.
	// _TileActorSelecter = 0 -> Tile
	// _TileActorSelecter = 1 -> Actor
	void CreatePlayerTileIndex(float4 _Pos, int _EnvironemntTileIndex, int _TileActorSelecter);

	// 레벨의 타일맵을 저장
	GameEngineRendererTileMap* LevelTileMap_;
	// 필드에 보이는 아이템의 정보를 저장할 액터
	std::list<Item*> ItemList_;

	inline void AddItem(Item* _Actor)
	{
		ItemList_.push_back(_Actor);
	};

	void TileIndexSetting(int x, int y);

	// 타일맵의 스테이터스를 저장
	std::vector<std::vector<PlayerTileIndex*>> GroundTiles_;
	std::vector<std::vector<Crops*>> EnvironmentActor_;
	void SetGroundTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState);
	void SetCropsActor(int x, int y, Crops* _CropActor, std::string _ColGroup, int _CropType);

public:
	// 레벨에서 자신의 크기로 타일을 생성하여 플레이어에게 타일의 정보를 넘겨주기 위한 함수
	void SetGroundTiles(std::vector<std::vector<PlayerTileIndex*>> _GroundTiles)
	{
		GroundTiles_ = _GroundTiles;
	}
	void SetCropsActorSize(int _X, int _Y);

	void MineralInit(std::string _ColName);
private:
	int PlayerTime_;

	void CropsUpdate();

	GameEngineRandom* PlayerRandom_;

	FishingGame* FishingGame_;
	SeedShop* SeedShop_;
	bool FishingGameFlg;

};
