#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <list>
#include <map>

class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;

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

	void ActorUpdate();
	void ActorRender();
	void ActorRelease();
};

