#include "GameEngineDebug.h"

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// �޸𸮸��� �߻��ϴ� ��ġ�� �극��ũ ����Ʈ
	// _crtBreakAlloc = 5015;
}

//void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
//{
//	// �˸���
//	MessageBeep(0);
//
//	// ������ �ڵ��� �ȳ������ �ڵ����� ������ �ڱ��ڽ��� ���.
//	MessageBoxA(nullptr, _Text.c_str(), "Error", MB_OK);
//
//	// ���α׷� ����
//	assert(false);
//}