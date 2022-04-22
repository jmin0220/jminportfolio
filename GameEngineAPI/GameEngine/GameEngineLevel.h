#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject; // 이녀석을
	int ChangeOrder; // 이렇게 바꿔라.
};

class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	static void IsDebugModeOn()
	{
		IsDebug = true;
	}

	static void IsDebugModeOff()
	{
		IsDebug = false;
	}

	static void IsDebugModeSwitch()
	{
		IsDebug = !IsDebug;
	}

	// 액터 생성
	template<typename ActorType>
	ActorType* CreateActor( int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();

		// 랜더링 우선순위에 맞춰 액터를 리스트에 추가
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	// 액터 찾기
	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}

	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

protected:
	// 시점함수. 엔진에서 어떠한 사건이 일어나는 시점, 단계.
	virtual void Loading() = 0;
	virtual void Update() = 0;

	// 레벨이 변경될때 호출될 함수.
	// 레벨이 시작될 때	
	void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) {}

	// 레벨이 종료될 때
	void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) {}

	void ObjectLevelMoveCheck(GameEngineLevel* _NextLevel);

private:
	static bool IsDebug;
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	std::map<std::string, GameEngineActor*> RegistActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeUpdateOrder(GameEngineActor* _Actor, int _Oreder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

private:
	// 삭제는 액터가 하지만 실제 사용은 Level
	// 여기서 함부로 GameEngineCollision*을 delete 하는 일이 있으면 안된다.
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

