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

	// 메모리릭이 발생하는 위치에 브레이크 포인트
	// _crtBreakAlloc = 5015;
}

//void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
//{
//	// 알림음
//	MessageBeep(0);
//
//	// 윈도우 핸들을 안넣을경우 자동으로 생성된 자기자신을 띄움.
//	MessageBoxA(nullptr, _Text.c_str(), "Error", MB_OK);
//
//	// 프로그램 종료
//	assert(false);
//}