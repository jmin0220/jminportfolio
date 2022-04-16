#pragma once
#include <string>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Mouse.h"
#include "Item.h"
#include "Clock.h"
#include "EnergyBar.h"
#include "Inventory.h"
#include "PlayerTileIndex.h"

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
		TileMap_ = _TileMap;
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

	// 플레이어 초기화
	void PlayerInit();

	// 플레이어의 위치에 따라서 Front레이어의 랜더 순서를 유동적으로 전환
	bool ColRenderOrderCheck();
private:
	void Start() override;
	void Update() override;

	// 속도
	float Speed_; 
	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;

	// 다음 레벨
	std::string NextLevel_;
	// 다음 레벨에서의 위치
	static float4 NextLevelPos_;

	// 카메라의 위치
	float4 CameraPos_;

	// 플레이어 자신의 렌더러
	GameEngineRenderer* RendererBody_;

	// 맵에서 사용될 충돌용 이미지
	GameEngineImage* MapColImage_;

	// 애니메이션 초기화
	void PlayerAnimationInit();
	// 애니메이션 전환
	void PlayerAnimationChange(const std::string& _Name);
	// 키 초기화
	void PlayerKeyInit();
	// 카메라 업데이트
	void UpdateCamera();

	// 플레이어가 움직일때 충돌감지
	float4 SetCheckPos(float4 _NextPos);

	// 맵과의 충돌체크
	void ColWallCheck(float4 _MoveDir);

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

	void IdleUpdate();
	void ActionUpdate();
	void MoveUpdate();

	void IdleStart();
	void ActionStart();
	void MoveStart();

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
	// 보이는 것과 상태가 일치하지 않을 수도 있다는 의미.
	void CreatePlayerTileIndex(float4 _Pos, std::string _TileMapImageName);

	// 레벨의 타일맵을 저장
	GameEngineRendererTileMap* TileMap_;

	// 타일맵의 스테이터스를 저장
	std::vector<std::vector<PlayerTileIndex*>> AllTiles_;
	void SetTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState);
public: 
	// 레벨에서 자신의 크기로 타일을 생성하여 플레이어에게 타일의 정보를 넘겨주기 위한 함수
	void SetAllTiles(std::vector<std::vector<PlayerTileIndex*>> _AllTiles)
	{
		AllTiles_ = _AllTiles;
	}

	// TODO::시간 관련 
private:
	int PlayerTime_;

	void TimeUpdate() {};
};
