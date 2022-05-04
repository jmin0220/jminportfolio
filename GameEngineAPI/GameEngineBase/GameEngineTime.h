#pragma once
#include <map>

// Ό³Έν :
class GameEngineTime
{
private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	void Reset();
	void Update();

	static inline float GetDeltaTime()
	{
		return Inst_->DeltaTime_;
	}

	static inline float GetDeltaTime(int _Key)
	{
		return Inst_->DeltaTime_ * Inst_->GetTimeScale(_Key);
	}

	void SetTimeScale(int _Key, float _TimeScale)
	{
		TimeScale_[_Key] = _TimeScale;
	}

	float GetTimeScale(int _Key)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			TimeScale_[_Key] = 1.0f;
		}

		return TimeScale_[_Key];
	}

protected:

private:
	__int64 SecondCount_;
	__int64 CurrentCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();
	std::map<int, float> TimeScale_;

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};
