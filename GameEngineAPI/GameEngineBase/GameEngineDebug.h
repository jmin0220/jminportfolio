#pragma once
#include <crtdbg.h>
#include <string>
#include <Windows.h>
#include <assert.h>

// ���� :
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

// �����Լ� ��ũ�� �ۼ�
#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false);