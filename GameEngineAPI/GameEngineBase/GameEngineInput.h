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

		// 눌려있는 키에 대한 정보
		int Key_;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	};

public:
	void Update();
	void CreateKey(std::string _Name, int _Key);

	bool IsDown(std::string _Name);
	bool IsUp(std::string _Name);
	bool IsPress(std::string _Name);
	bool IsFree(std::string _Name);
	bool IsKey(std::string _Name);

protected:

private:
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

