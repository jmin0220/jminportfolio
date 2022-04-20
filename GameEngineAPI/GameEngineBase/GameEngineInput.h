#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 :
class GameEngineInput
{
private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
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

private:
	class GameEngineKey
	{
		friend GameEngineInput;

		// 키가 눌리는 순간
		bool Down_;
		// 키가 눌려있는 동안
		bool Press_;
		// 키가 떼지는 순간
		bool Up_;
		// 키가 안눌려있을 때
		bool Free_;
		// 입력된 시간
		float Time_;

		// 눌려있는 키에 대한 정보
		int Key_;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	};

	friend class GameEngineWindow;

public:
	void Update(float _DeltaTime = 0.0f);
	void CreateKey(const std::string& _Name, int _Key);

	float GetTime(const std::string& _Name);
	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);

	inline int GetMouseWheel()
	{
		return CurWheelValue;
	}

protected:

private:
	int WheelValue;
	int CurWheelValue;
	std::map<std::string, GameEngineKey> AllInputKey_;

	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

};

