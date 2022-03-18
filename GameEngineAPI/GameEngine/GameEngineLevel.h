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

protected:
	// �����Լ�. �������� ��� ����� �Ͼ�� ����, �ܰ�.
	virtual void Loading() = 0;
	virtual void Update() = 0;

	// ������ ����ɶ� ȣ��� �Լ�.
	// ������ ���۵� ��
	virtual void LevelChangeStart() {};
	// ������ ����� ��
	virtual void LevelChangeEnd() {};

	// ���� ����
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();

		// ������ �켱������ ���� ���͸� ����Ʈ�� �߰�
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return nullptr;
	}

private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

