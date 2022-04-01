#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// 액터 생성
	template<typename ActorType>
	ActorType* CreateActor( int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
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

protected:
	// 시점함수. 엔진에서 어떠한 사건이 일어나는 시점, 단계.
	virtual void Loading() = 0;
	virtual void Update() = 0;

	// 레벨이 변경될때 호출될 함수.
	// 레벨이 시작될 때
	virtual void LevelChangeStart() {};
	// 레벨이 종료될 때
	virtual void LevelChangeEnd() {};

private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	// 삭제는 액터가 하지만 실제 사용은 Level
	// 여기서 함부로 GameEngineCollision*을 delete 하는 일이 있으면 안된다.,
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

