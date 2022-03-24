#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 : 게임 자체의 시작점과 끝점, 실행중을 담당. 인터페이스만을 제공
class GameEngineImage;
class GameEngineLevel;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	// 퓨어 virtual
	// 게임 초기화
	virtual void GameInit() = 0;

	// 게임 실행
	virtual void GameLoop() = 0;

	// 게임 종료
	virtual void GameEnd() = 0;

	// 프로그램 시작
	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		UserContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	static GameEngine& GlobalEngine()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert(DEBUG_MSG_GENGINE_NOT_START);
		}

		return *UserContents_;
	}

	// 레벨 전환
	void ChangeLevel(const std::string& _Name);

protected:
	// 레벨 생성함수
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		
		GameEngineLevel* Level = NewLevel;
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine*      UserContents_;

	static GameEngineImage* WindowMainImage_;
	static GameEngineImage* BackBufferImage_;

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

