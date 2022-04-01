#pragma once
#include <string>
#include "GameEngineTime.h"


class GameEngineUpdateObject
{
public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	inline void On()
	{
		IsUpdate_ = true;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}

	inline virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}

	inline void Death(float _Time)
	{
		IsReleaseUpdate_ = true;
		DeathTime_ = _Time;
	}

	inline virtual bool IsDeath()
	{
		return IsDeath_;
	}

	void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= DeathTime_)
		{
			IsDeath_ = true;
		}
	}

protected:

private:
	// 오브젝트가 Release할때까지의 시간
	float DeathTime_;
	// Release트리거 설정
	bool IsReleaseUpdate_;

	bool IsUpdate_;
	bool IsDeath_;
};

