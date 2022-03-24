#pragma once
#include "GameEngineCustomStringSet.h"
#include <crtdbg.h>
#include <string>
#include <Windows.h>
#include <assert.h>

// 설명 :
class GameEngineDebug
{
public:
	static void LeakCheckOn();

	//static void MsgBoxAssert(const std::string& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

};

// 종료함수 매크로 작성
#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, DEBUG_ERROR, MB_OK); \
assert(false);

#define MsgBoxAssertString(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, (Text).c_str(), DEBUG_ERROR, MB_OK); \
assert(false); 